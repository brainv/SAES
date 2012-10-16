/**
 * @file ElectionInstalationLanguages.cpp
 * @brief Body class election installation languages
 * @date 10/03/2011
 * @author Freddy Gomez
 */

#include "ElectionInstalationLanguages.h"
#include "Voting/Election/election-schema.hxx"
#include <fstream>
#include <glibmm.h>
#include <Security/Encryption.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Runtime/Environment/DirectoryManager.hxx>
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

using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;

#define LOGGER_PROJECT "Smartmatic.SAES.Voting.Election.ElectionInstalationLanguages" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* ElectionInstalationLanguages::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* ElectionInstalationLanguages::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

ElectionInstalationLanguages * ElectionInstalationLanguages::instance = NULL;

ElectionInstalationLanguages * ElectionInstalationLanguages::getInstance()
{
    if (instance == NULL)
        instance = new ElectionInstalationLanguages();

    return instance;
}

ElectionInstalationLanguages::ElectionInstalationLanguages()
{
	ReloadLanguages();
}

ElectionInstalationLanguages::~ElectionInstalationLanguages()
{
    languages.clear();
}

void ElectionInstalationLanguages::clearLanguage()
{
	languages.clear();
}

void ElectionInstalationLanguages::ReloadLanguages()
{
	languages.clear();

	Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
	std::string installFile = directories.getLanguageInstalationFileFullPath();
	std::string localFileDom = directories.getLanguageLocalFileFullPath(BasePathType::CONFIGURATION_DOM);
	std::string localFileFlash = directories.getLanguageLocalFileFullPath(BasePathType::CONFIGURATION_FLASH);

	if (LoadFile(localFileDom))
	{
		logger->Debug("Load languages in DOM");
	}
	else if (LoadFile(localFileFlash))
	{
		logger->Debug("Load languages in Flash");
	}
	else
	{
		LoadFile(installFile);
	}
}

bool ElectionInstalationLanguages::LoadFile(std::string file)
{
    if (Smartmatic::System::IO::File::canOpenFile(file))
    {
       try
       {
    	   std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file,
                   Smartmatic::SAES::Security::Encryption::INSTALL_FILE,
                   Smartmatic::SAES::Security::Encryption::INIT_KEY);
            std::istringstream istrLanguage (data);

            std::auto_ptr< Smartmatic::SAES::Voting::Election::Languages > configuration(
            Smartmatic::SAES::Voting::Election::parseLanguages ( istrLanguage, Smartmatic::SAES::Voting::ElectionLanguageTypes::Flags::dont_validate ));

            Smartmatic::SAES::Voting::Election::Languages langConfig (*configuration.get());
            Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & sequence (langConfig.getLanguage());
            Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

            for (it = sequence.begin();
                 it != sequence.end();
                 ++it)
            {
                this->languages.push_back(*it);
            }

            return true;

        }
        catch (CryptoException & e)
        {
            std::stringstream ss;
			ss<< "FATAL - " << __func__<<" "<< e.what();
			logger->Debug(ss.str());
        }
        catch (SignedException & e)
        {
            std::stringstream ss;
			ss<< "FATAL - " << __func__<<" "<< e.what();
			logger->Debug(ss.str());
        }
        catch (XmlException & e)
        {
            std::stringstream ss;
			ss<< "FATAL - " << __func__<<" "<< e.what();
			logger->Debug(ss.str());
        }
        catch (...)
        {
            std::stringstream ss;
			ss<< "FATAL " << __func__ << " error load file " << file;
			logger->Debug(ss.str());			
        }
    }

    return false;
}

std::list<Smartmatic::SAES::Voting::Election::Language> ElectionInstalationLanguages::getLanguages()
{
  return this->languages;
}

void ElectionInstalationLanguages::setInstallationLanguages(Smartmatic::SAES::Voting::Election::Language& lang)
{
  std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;
  //Look the language in the list and set it as default
  for(it = languages.begin(); it != languages.end(); it++)
    {
      	if((*it).getCode() == lang.getCode())
        {
          (*it).setIs_default(true);
        }
        else
        {
          (*it).setIs_default(false);
        }
    }
}

void ElectionInstalationLanguages::addInstallationLanguages(Smartmatic::SAES::Voting::Election::Language& lang)
{
	bool addLang = true;
	std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;
	//Look the language in the list to see if it is already added
	for(it = languages.begin(); it != languages.end(); it++)
	{
		if((*it).getCode() == lang.getCode() || (*it).getCustom_code() == lang.getCustom_code())
		{
			addLang = false;
		}
	}
	if(addLang)
		languages.push_back(lang);
}

void ElectionInstalationLanguages::persistLanguage()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Voting::Election::Languages toSave;
    std::ostringstream os;

    try
    {
        Smartmatic::SAES::Voting::ElectionLanguageTypes::NamespaceInfomap map;

#ifdef NAMESPACE_VOTING_ELECTION
        map[""].name = NAMESPACE_VOTING_ELECTION;
#endif
        map[""].schema = "";

        Smartmatic::SAES::Voting::Election::Languages::LanguageSequence langSec;

        std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

        for(it = languages.begin(); it != languages.end(); it++)
        {
          langSec.push_back(*it);
        }

        toSave.setLanguage(langSec);
        serializeLanguages (os, toSave, map);
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
        ss<< "FATAL - " << __func__<<" "<< e.what();
		logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.Election.ElectionInstalationLanguages.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.Election.ElectionInstalationLanguages.ErrorSerializaData"), logger);
    }
    catch (...)
    {
        std::stringstream ss;
        ss<< "FATAL - " << __func__<<" "<<__LINE__;
		logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.Election.ElectionInstalationLanguages.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.Election.ElectionInstalationLanguages.ErrorSerializaData"), logger);
    }

    std::string data = os.str();

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getLanguageLocalFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getLanguageLocalFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
        Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INSTALL_FILE,
                Smartmatic::SAES::Security::Encryption::INIT_KEY);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
                Smartmatic::SAES::Security::Encryption::INSTALL_FILE,
                Smartmatic::SAES::Security::Encryption::INIT_KEY);
        File::copyFile(fileFlash, fileDom);
    }
}

std::list <std::string> ElectionInstalationLanguages::getStringLanguages()
{
    std::list <std::string> list;
    std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

    for(it = languages.begin();
        it != languages.end();
        it++)
    {
      Glib::ustring lang = (*it).getLanguage();
      Glib::ustring country = (*it).getCountry();

      if (country.length() == 0)
      {
          country = lang;
      }

      lang = lang.lowercase();
      country = country.uppercase();

      if(country.empty())
    	  list.push_back(lang);
      else
    	  list.push_back(lang + "_" + country);
    }

    return list;
}

std::list<Smartmatic::SAES::Voting::Election::Language> ElectionInstalationLanguages::GetOperatingLanguages(std::list<Smartmatic::SAES::Voting::Election::Language> allLang)
{
	std::list<Smartmatic::SAES::Voting::Election::Language> retVal;
	std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

	//Look the language in the list and register them
	for(it = allLang.begin(); it != allLang.end(); it++)
	{
		if( (it)->getIs_default() )
		{
			retVal.push_back(*it);
		}
	}

	return retVal;
}
