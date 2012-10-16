/**
 * @file TransmissionPackageWrapper.cxx
 * @brief Body class voting centers
 */

#include "TransmissionPackageWrapper.hxx"
#include "StationTallyWrapper.hxx"
#include <fstream>
#include <gtkmm.h>
#include <Security/Encryption.hxx>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <System/guid-class.h>
#include <System/Security/Cryptography/RsaUtil.h>
#include <System/Security/Cryptography/PBEKeyDerivatorHMAC.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include <System/SafeBuffer.h>
#include <System/Security/Crypto.hxx>
#include <System/Security/Cryptography/CertUtil.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* TransmissionPackageWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper",GETTEXT_PACKAGE);

TransmissionPackageWrapper * TransmissionPackageWrapper::instance = NULL;

TransmissionPackageWrapper * TransmissionPackageWrapper::getInstance()
{
    if (instance == NULL)
        instance = new TransmissionPackageWrapper();

    return instance;
}

TransmissionPackageWrapper::TransmissionPackageWrapper()
{
	this->electoralConfiguration = NULL;
	this->directories = NULL;
	this->stationTally = NULL;
	this->codiFiles = NULL;
	this->enableCodi = SAESConfigurationManager::Current()->getCodiFileConfiguration().getEnableCodi();
}

TransmissionPackageWrapper::~TransmissionPackageWrapper()
{
    dispose();
}

void TransmissionPackageWrapper::dispose()
{
    votes.clear();
    demoVotes.clear();

    if (stationTally)
    {
    	delete stationTally;
    	stationTally = NULL;
    }
    if (codiFiles)
    {
    	delete codiFiles;
    	codiFiles = NULL;
    }
}

void TransmissionPackageWrapper::init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
		Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories)
{
    dispose();
	this->electoralConfiguration = electoralConfiguration;
	this->directories = directories;
	this->stationTally = new StationTallyWrapper(electoralConfiguration, enableCodi);

	if (enableCodi)
	{
		codiFiles = new CodiFileWrapper();
		codiFiles->init(electoralConfiguration, directories);
	}
}

void TransmissionPackageWrapper::addVote(Vote &vote)
{
	switch(vote.getMode())
	{
	case VoteMode::VOTE_D:
		if(SAESConfigurationManager::Current()->getSaveDemoVotesInTransmissionPackage())
		{
			votes.push_back(vote);
		}
		demoVotes.push_back(vote);
		break;
	case VoteMode::VOTE_O:
	case VoteMode::VOTE_R:
		votes.push_back(vote);
		break;
	case VoteMode::VOTE_S:
		break;
	}
}

void TransmissionPackageWrapper::deleteVotes()
{
	votes.clear();
	demoVotes.clear();

	if (stationTally)
	{
		stationTally->clear();
	}
}

const std::list<Vote> & TransmissionPackageWrapper::getAllVote()
{
    return votes;
}

const std::list<Vote> & TransmissionPackageWrapper::getAllVoteDemo()
{
    return demoVotes;
}

void TransmissionPackageWrapper::persistTransmissionPackage()
    throw (CryptoException,
           SignedException,
           XmlException,
           CodiException)
{
	if (codiFiles)
	{
		codiFiles->update();
		stationTally->setCodiMachine(codiFiles->getCodiMachine());
		stationTally->setCodiVotingType(codiFiles->getCodiVotingType());
		stationTally->setCustomniscode(codiFiles->getCustomniscode());
	}

	stationTally->init();

	Transmission transmission;
    TransmissionPackage transmissionPackage;
    StationTallyPackages stnTlyPcks;
    StationTallyPackages::Stn_tly_pckSequence sequence;

    StationTallyPackage stnTlyPck;

    ValidVotes validVotes;
    ValidVotes::VSequence vsequence;

    std::list <Vote>::iterator it;

    for (it = votes.begin();
         it != votes.end();
         it++)
    {
    	Vote & vote (*it);
        vsequence.push_back(vote);
       	stationTally->update(vote);
    }

    // Calculate checksums

    StationTallyPackage::Stn_tlySequence stnSequence;
    std::list <StationTally*> listStationTally;
    std::list <StationTally*>::iterator itst;

   	stationTally->getStationTally(listStationTally);

	if (codiFiles)
	{
		codiFiles->persistCodiFiles(stationTally);
	}

    for (itst = listStationTally.begin();
    	 itst != listStationTally.end();
    	 itst++)
    {
    	stnSequence.push_back(*(*itst));
    }

    stnTlyPck.setStationTally(stnSequence);


    stnTlyPck.setVoting_device_code(electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getCode());
    validVotes.setVotes(vsequence);
    stnTlyPck.setValidVotes(validVotes);

    sequence.push_back(stnTlyPck);
    stnTlyPcks.setStationTallyPackage(sequence);
    transmissionPackage.setStationTallyPackages(stnTlyPcks);
    transmission.setTransmissionPackage(transmissionPackage);

    std::ostringstream os;

    try
    {
        Smartmatic::SAES::Voting::VoteTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_VOTING_VOTE;
        map[""].schema = "";

        serializeTransmission(os, transmission, map);
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
		ss<< "FATAL - " << __func__ << e.what();
		logger->Debug(ss.str());
        
        throw XmlException(_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorSerializaData"),
                          N_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorSerializaData"),
                          logger);
    }
    catch (...)
    {
        std::stringstream ss;
		ss<< "FATAL - " << __func__ << __LINE__;
		logger->Debug(ss.str());
        throw XmlException(_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorSerializaData"),
                          N_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorSerializaData"),
                          logger);
    }

    std::string data = os.str();

    if (!SAESCommonConfigurationManager::Current()->isUseAsimetricKeyForTransmissionPackages())
    {
        logger->Debug("Start persistence transmission package with secret-key");
        persistTransmissionPackageSecretKey(data);
        logger->Debug("Success persistence transmission package with secret-key");
    }
    else
    {
        logger->Debug("Start persistence transmission package with asimetric-key");
        persistTransmissionPackageAsimetricKey(data);
        logger->Debug("Success persistence transmission package with asimetric-key");
    }

    persistTransmissionPackageHash();
}

void TransmissionPackageWrapper::persistTransmissionPackageSecretKey(std::string & data)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    std::string devicePathDom = directories->getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories->getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
        Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
        		Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);
        File::copyFile(fileFlash, fileDom);
    }
}

void TransmissionPackageWrapper::persistTransmissionPackageAsimetricKey(std::string & data)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::System::SafeBuffer dataTransmissionPackage;
    Smartmatic::System::SafeBuffer asimetricKeyCrypto;

    //---------------------------------------------------------

    bool isSignedData = Smartmatic::SAES::Security::Encryption::getInstance()->signedData(
            Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

    if (isSignedData)
    {
        Smartmatic::SAES::Security::Encryption::getInstance()->signedXml(
                data,
                Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);
    }

    Smartmatic::System::SafeBuffer dataIn((unsigned char *)data.c_str(), data.length());

    //---------------------------------------------------------

    bool isCryptoFile = Smartmatic::SAES::Security::Encryption::getInstance()->cryptoData(
            Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

    if (isCryptoFile)
    {
        Smartmatic::System::Security::Cryptography::PBEKeyDerivatorHMAC pbe;

        Glib::ustring passPhrase = Smartmatic::System::GuidClass::NewGuid().ToString();
        Glib::ustring salt = Smartmatic::System::GuidClass::NewGuid().ToString();

        unsigned char outkey[32];
        int keyLen = sizeof(outkey)/sizeof(char);
        int iterations = 2048;

        pbe.SetSalt(salt);
        pbe.GenerateKey(passPhrase, outkey, keyLen, iterations);

        Smartmatic::System::SafeBuffer asimetricKey(outkey, keyLen);
		Smartmatic::System::SafeBuffer iv;
		Smartmatic::SAES::Security::Encryption::getInstance()->getUseIV(asimetricKey, iv);

        //---------------------------------------------------------

        Glib::ustring certPath = directories->getTransmissionPackagesCrtFileFullPath();
                //directories->getMachineKeysFileFullPath();

        if (!Smartmatic::System::IO::File::canOpenFile(certPath))
        {
            logger->Debug("Fatal - file cert not found : " + certPath);

            throw CryptoException(
                    _("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorCertNotFound"),
                    N_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorCertNotFound"),
                    logger);
        }

        Smartmatic::System::Security::Cryptography::RsaUtil util;

        util.SetPublicKey_FromCert(certPath, "no password", Smartmatic::System::Security::Cryptography::CertUtil::CertFormat_PEM);
        util.SetPaddingType(Smartmatic::System::Security::Cryptography::RsaUtil::RSAPAD_PKCS1);

        Smartmatic::System::SafeBuffer dataToCrypto;

        try
        {
            //util.SetPrivateKey_PKCS12(certPath, Smartmatic::SAES::Security::Encryption::getInstance()->getSecretKey().getKeyBase64());

        	if (Smartmatic::SAES::Security::Encryption::getInstance()->getModeType() ==
        			Smartmatic::System::Security::Crypto::MODE_AES_CBC)
        	{
        		dataToCrypto.AddData(asimetricKey);
        		dataToCrypto.AddData(iv);
        	}
        	else
        	{
        		dataToCrypto.AddData(asimetricKey);
        	}

            asimetricKeyCrypto = util.PublicEncrypt(dataToCrypto);

        }
        catch(...)
        {
            logger->Debug("Fatal - error cert.");

            throw CryptoException(
                    _("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorCert"),
                    N_("Smartmatic.SAES.Voting.Vote.TransmissionPackageWrapper.ErrorCert"),
                    logger);
        }

        //---------------------------------------------------------

        Smartmatic::System::Security::Crypto crypto;

        crypto.init (Smartmatic::SAES::Security::Encryption::getInstance()->getKeySize(),
				Smartmatic::SAES::Security::Encryption::getInstance()->getModeType(), true);

        crypto.cryptoBufferToBuffer(dataIn, dataTransmissionPackage, (unsigned char*)asimetricKey.GetData(), (unsigned char*)iv.GetData());
    }
    else
    {
        dataTransmissionPackage.AddData(dataIn);
    }

    //---------------------------------------------------------

    std::string devicePathDom = directories->getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories->getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileTransDom = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileTransKeyDom = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_DOM);

    std::string fileTransFlash = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_FLASH);
    std::string fileTransKeyFlash = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	Smartmatic::System::IO::File::saveBufferToFile(dataTransmissionPackage, fileTransDom);
    	Smartmatic::System::IO::File::saveBufferToFile(asimetricKeyCrypto, fileTransKeyDom);

    	Smartmatic::System::IO::File::copyFile(fileTransDom, fileTransFlash);
    	Smartmatic::System::IO::File::copyFile(fileTransKeyDom, fileTransKeyFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::System::IO::File::saveBufferToFile(dataTransmissionPackage, fileTransFlash);
    	Smartmatic::System::IO::File::saveBufferToFile(asimetricKeyCrypto, fileTransKeyFlash);

    	Smartmatic::System::IO::File::copyFile(fileTransFlash, fileTransDom);
    	Smartmatic::System::IO::File::copyFile(fileTransKeyFlash, fileTransKeyDom);
    }
}

void TransmissionPackageWrapper::persistTransmissionPackageHash()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    std::string devicePathDom = directories->getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories->getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDOM = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::string fileHashDom = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileHashFlash = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
        Smartmatic::System::SafeBuffer bufferFile;
    	Smartmatic::System::IO::File::getHashFile(fileDOM, bufferFile);
    	std::string hash = bufferFile.GetBase64Data();

    	Smartmatic::SAES::Security::Encryption::getInstance()->cryptoStringToFile(hash, fileHashDom,
    	            Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);
        File::copyFile(fileHashDom, fileHashFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
        Smartmatic::System::SafeBuffer bufferFile;
    	Smartmatic::System::IO::File::getHashFile(fileFlash, bufferFile);
    	std::string hash = bufferFile.GetBase64Data();

    	Smartmatic::SAES::Security::Encryption::getInstance()->cryptoStringToFile(hash, fileHashFlash,
    	            Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);
        File::copyFile(fileHashFlash, fileHashDom);
    }
}

bool TransmissionPackageWrapper::validate()
{
    bool validate = false;
    bool validateKey = true;

    try
    {
        std::string dom = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_DOM);
        std::string flash = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_FLASH);

        std::string fileDom = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_DOM);
        std::string fileFlash = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_FLASH);

        std::string hashDom;
        std::string hashFlash;

        Smartmatic::System::SafeBuffer bufferFile;
        Smartmatic::System::IO::File::getHashFile(fileDom, bufferFile);
        std::string hash = bufferFile.GetBase64Data();

        logger->Debug("hash: " + hash);

        Smartmatic::SAES::Security::Encryption::getInstance()->decryptoFileToString(
                dom,
                hashDom,
                Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);

        logger->Debug("hashDom: " + hashDom);

        Smartmatic::SAES::Security::Encryption::getInstance()->decryptoFileToString(
                flash,
                hashFlash,
                Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);

        logger->Debug("hashFlash: " + hashFlash);

        bool isCryptoFile = Smartmatic::SAES::Security::Encryption::getInstance()->cryptoData(
                Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

        if (isCryptoFile && SAESCommonConfigurationManager::Current()->isUseAsimetricKeyForTransmissionPackages())
        {
            std::string domKey = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_DOM);
            std::string flashKey = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_FLASH);

            validateKey = Smartmatic::System::IO::File::compareFiles(domKey, flashKey);
        }

        validate = validateKey &&
                Smartmatic::System::IO::File::compareFiles(dom, flash) &&
                Smartmatic::System::IO::File::compareFiles(fileDom, fileFlash) &&
                hashDom == hashFlash &&
                hashDom == hash;
    }
    catch(...)
    {
        logger->Debug("Fatal - " + std::string(__func__) + " Error decrypto data.");
    }

	if (codiFiles)
	{
		codiFiles->update();
		validate = validate && codiFiles->validate();
	}

    return validate;
}

void TransmissionPackageWrapper::deleteFiles()
{
    std::string transmissionPackageDom = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string transmissionPackageHashDom = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string transmissionPackageKeyDom = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_DOM);

    Smartmatic::System::IO::File::DeleteFile(transmissionPackageDom);
    Smartmatic::System::IO::File::DeleteFile(transmissionPackageHashDom);
    Smartmatic::System::IO::File::DeleteFile(transmissionPackageKeyDom);

    std::string transmissionPackageFlash = directories->getTransmissionPackagesFileFullPath(BasePathType::CONFIGURATION_FLASH);
    std::string transmissionPackageHashFlash = directories->getTransmissionPackagesHashFileFullPath(BasePathType::CONFIGURATION_FLASH);
    std::string transmissionPackageKeyFlash = directories->getTransmissionPackagesKeyFileFullPath(BasePathType::CONFIGURATION_FLASH);

    Smartmatic::System::IO::File::DeleteFile(transmissionPackageFlash);
    Smartmatic::System::IO::File::DeleteFile(transmissionPackageHashFlash);
    Smartmatic::System::IO::File::DeleteFile(transmissionPackageKeyFlash);

    deleteVotes();

	if (codiFiles)
	{
		codiFiles->update();
		codiFiles->deleteFiles();
	}
}
