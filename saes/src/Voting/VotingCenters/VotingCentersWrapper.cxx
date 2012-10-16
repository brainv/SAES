/**
 * @file VotingCentersWrapper.cxx
 * @brief Body class voting centers
 */

#include "VotingCentersWrapper.hxx"
#include <fstream>
#include <gtkmm.h>
#include <Security/Encryption.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>

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
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

ISMTTLog* VotingCentersWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.VotingCenters.VotingCentersWrapper",GETTEXT_PACKAGE);

VotingCentersWrapper * VotingCentersWrapper::instance = NULL;

VotingCentersWrapper * VotingCentersWrapper::getInstance()
{
    if (instance == NULL)
        instance = new VotingCentersWrapper();

    return instance;
}

VotingCentersWrapper::VotingCentersWrapper()
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    std::string installFileFullPath = directories.getVotingCentersInstalationFileFullPath();
    std::string localFileDom = directories.getVotingCentersLocalFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string localFileFlash = directories.getVotingCentersLocalFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (LoadFile(localFileDom))
    {
    	logger->Debug("Load voting center in DOM");
    	install = true;
    	type = BasePathType::CONFIGURATION_DOM;
    }
    else if (LoadFile(localFileFlash))
    {
    	logger->Debug("Load voting center in Flash");
    	install = true;
    	type = BasePathType::CONFIGURATION_FLASH;
    }
    else if (LoadFile(installFileFullPath))
    {
    	logger->Debug("Load voting center in SAES");
        install = false;
    	type = BasePathType::CONFIGURATION_DOM;
    }
    else
    {
		ZenityWrapper::showError("Error load file (" + installFileFullPath + ")", "Error");
        exit (0);
    }
}

VotingCentersWrapper::~VotingCentersWrapper()
{
}

bool VotingCentersWrapper::isInstall()
{
	return install;
}

BasePathType VotingCentersWrapper::getMasterDevice()
{
	return type;
}

std::list <VotingCenter> & VotingCentersWrapper::getVotingCenters()
{
    return this->votingCenters;
}

bool VotingCentersWrapper::LoadFile(std::string path)
{
	votingCenters.clear();

    if (Smartmatic::System::IO::File::canOpenFile(path))
    {
       try
       {
    	   std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(path,
                   Smartmatic::SAES::Security::Encryption::INSTALL_FILE,
                   Smartmatic::SAES::Security::Encryption::INIT_KEY);
            std::istringstream istrVotingCenters (data);

            Smartmatic::SAES::Voting::VotingCenters::VotingCenters votingC(
                       *(Smartmatic::SAES::Voting::VotingCenters::parseVotingCenters(
                               istrVotingCenters, Smartmatic::SAES::Voting::VotingCenters::Flags::dont_validate)));

            Smartmatic::SAES::Voting::VotingCenters::VotingCenters::VotingCenterSequence & sequence (votingC.getVotingCenter());
            Smartmatic::SAES::Voting::VotingCenters::VotingCenters::VotingCenterIterator it;

            for (it = sequence.begin();
                 it != sequence.end();
                 ++it)
            {
                this->votingCenters.push_back(*it);
                this->votingCenter = (*it);
            }

            return true;

        }
        catch (CryptoException & ex)
        {
            std::stringstream ss;
		 	ss<< "FATAL - " << __func__ << ex.what();
			logger->Debug(ss.str());
        }
        catch (SignedException & ex)
        {
            std::stringstream ss;
		 	ss<< "FATAL - " << __func__ << ex.what();
			logger->Debug(ss.str());
        }
        catch (XmlException & ex)
        {
            std::stringstream ss;
		 	ss<< "FATAL - " << __func__ << ex.what();
			logger->Debug(ss.str());
        }
        catch (std::exception & ex)
        {
            std::stringstream ss;
            ss<< "FATAl - " << __func__ << " error data file " << path << " : " << ex.what();
            logger->Debug(ss.str());
        }
        catch (...)
        {
            std::stringstream ss;
		 	ss<< "FATAl - " << __func__ << " error load file " << path;
			logger->Debug(ss.str());
        }
    }
    else
    {
    	logger->Debug("File " + path + " not found.");
    }

    return false;
}

void VotingCentersWrapper::setInstallationVotingCenter(VotingCenter &votingCenter)
{
    this->votingCenter = votingCenter;
}

void VotingCentersWrapper::getInstallationVotingCenter(VotingCenter &votingCenter)
{
    votingCenter = this->votingCenter;
}

void VotingCentersWrapper::persistVotingCenters()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Voting::VotingCenters::VotingCenters toSave;
    std::ostringstream os;

    try
    {
        Smartmatic::SAES::Voting::VotingCenters::NamespaceInfomap map;
        map[""].name = NAMESPACE_VOTING_CENTERS;
        map[""].schema = "";

        Smartmatic::SAES::Voting::VotingCenters::VotingCenters::VotingCenterSequence sequence;
        sequence.push_back(votingCenter);

        toSave.setVotingCenter(sequence);
        serializeVotingCenters (os, toSave, map);
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
	 	ss<< "FATAl - " << __func__ << " " << e;
		logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.VotingCenters.VotingCentersWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.VotingCenters.VotingCentersWrapper.ErrorSerializaData"), logger);
    }
    catch (...)
    {
        std::stringstream ss;
	 	ss<< "FATAl - " << __func__;
		logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.VotingCenters.VotingCentersWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.VotingCenters.VotingCentersWrapper.ErrorSerializaData"), logger);
    }

    std::string data = os.str();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    std::string file = directories.getVotingCentersLocalFileFullPath(type);

	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, file,
			Smartmatic::SAES::Security::Encryption::INSTALL_FILE,
			Smartmatic::SAES::Security::Encryption::INIT_KEY);

}

