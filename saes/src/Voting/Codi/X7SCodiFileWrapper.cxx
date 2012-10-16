/**
 * @file X7SCodiFileWrapper.cxx
 * @brief Body class x7s codi file
 * @date 01/03/2012
 * @author Yadickson Soto
 */

#include "X7SCodiFileWrapper.hxx"
#include "X7SSecurity.hxx"
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <Configuration/saes-language-controller.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <System/SafeBuffer.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting;

ISMTTLog* X7SCodiFileWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper",GETTEXT_PACKAGE);

X7SCodiFileWrapper::X7SCodiFileWrapper()
{
	this->electoralConfiguration = NULL;
	this->directories = NULL;
	this->addPV = SAESConfigurationManager::Current()->getCodiFileConfiguration().getX7SAddPVReport();
}

X7SCodiFileWrapper::~X7SCodiFileWrapper()
{

}

void X7SCodiFileWrapper::init(ElectoralConfiguration * electoralConfiguration, SaesDirectories * directories)
{
	this->electoralConfiguration = electoralConfiguration;
	this->directories = directories;
}

void X7SCodiFileWrapper::persistX7SCodiFile(std::string & codiFile, std::string & codiX7SFile, std::string & pvformFile)
	throw (CryptoException,
			SignedException,
			XmlException,
			CodiException)
{
	logger->Debug("Persistence codi file " + codiFile + " to " + codiX7SFile + " with " + codiX7SFile + ".PDF");

	std::string outputDirDom = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_DOM);
	std::string outputDirFlash = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_FLASH);

	std::string inputFileDom = Path::Combine(directories->getDocsFolderFullPath(BasePathType::CONFIGURATION_DOM), pvformFile);
	std::string inputFileFlash = Path::Combine(directories->getDocsFolderFullPath(BasePathType::CONFIGURATION_FLASH), pvformFile);

	std::string pvreportDom = Path::Combine(outputDirDom, codiX7SFile + ".PDF");
	std::string pvreportFlash = Path::Combine(outputDirFlash, codiX7SFile + ".PDF");

	File::copyFile(inputFileDom, pvreportDom);
	File::copyFile(inputFileFlash, pvreportFlash);

	std::string codiFileDom = Path::Combine(outputDirDom, codiFile);

    X7SCodiFile x7sCodi;

    if (addPV)
    {
    	SafeBuffer pvBuffer;

    	if (!File::openFileToBuffer(pvreportDom, pvBuffer))
    	{
    		logger->Debug("ERROR - Load pv report " + pvreportDom + " not found.");

    		throw CodiException (
    				_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorLoadPVReport"),
    				N_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorLoadPVReport"),
    				logger);
    	}

    	PVFile pvFile;
    	Base64Binary pvBinary(pvBuffer.GetData(), pvBuffer.GetSize());

        pvFile.setPVType(PVType::PDF);
        pvFile.setOriginialFileName(pvformFile);
        pvFile.setData(pvBinary);
        x7sCodi.setPVFile(pvFile);
    }
    else
    {
    	PVFile pvFile;
    	Base64Binary pvBinary(0);

        pvFile.setPVType(PVType::PDF);
        pvFile.setOriginialFileName("");
        pvFile.setData(pvBinary);
        x7sCodi.setPVFile(pvFile);
    }

	SafeBuffer codiBuffer;

	if (!File::openFileToBuffer(codiFileDom, codiBuffer))
	{
		logger->Debug("ERROR - Load codi file " + codiFileDom + " not found.");

		throw CodiException (
				_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorLoadCodiFile"),
				N_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorLoadCodiFile"),
				logger);
	}

	FormatF codiF;
    Base64Binary codiBinary(codiBuffer.GetData(), codiBuffer.GetSize());

    codiF.setOriginialFileName(codiFile);
    codiF.setData(codiBinary);

    x7sCodi.setFormatF(codiF);

    std::string dataXml;
    x7sCodiToString(x7sCodi, dataXml);

    SafeBuffer fileBuffer(dataXml);
    SafeBuffer sign;
	SafeBuffer crypto;

    X7SSecurity x7sSecurity;
    x7sSecurity.init(electoralConfiguration, directories);
    x7sSecurity.signedBuffer(fileBuffer, sign);
    x7sSecurity.cryptoBuffer(sign, crypto);

	std::string x7sDom = Path::Combine(outputDirDom, codiX7SFile);
	std::string x7sFlash = Path::Combine(outputDirFlash, codiX7SFile);

	File::saveBufferToFile(crypto, x7sDom);
    File::copyFile(x7sDom, x7sFlash);

    logger->Debug("Success persistence X7S codi file " + codiFile);
}

void X7SCodiFileWrapper::x7sCodiToString(const X7SCodiFile & x7sCodi, std::string& outString)
   throw (XmlException)
{
   std::ostringstream str;

   NamespaceInfomap mapv;
   mapv[""].name = NAMESPACE_VOTING_CODI;
   mapv[""].schema = "";

   try
   {
	   serializeFinalData(str, x7sCodi, mapv, "UTF-8", Flags::dont_validate);
	   outString = str.str();
   }
   catch (const ::xsd::cxx::tree::exception< char >& e)
   {
       std::stringstream ss;
       ss << "FATAL - " << __func__ << e;
       logger->Error(ss.str());
       throw XmlException(
    		   _("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorSerializaData"),
    		   N_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorSerializaData"),
    		   logger);
   }
   catch (...)
   {
       std::stringstream ss;
       ss << "FATAL - " << __func__;
       logger->Error(ss.str());
       throw XmlException(
    		   _("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorSerializaData"),
    		   N_("Smartmatic.SAES.Voting.Codi.X7SCodiFileWrapper.ErrorSerializaData"),
    		   logger);
   }
}
