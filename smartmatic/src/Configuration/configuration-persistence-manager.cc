

#include "configuration-persistence-manager.h"
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
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

#define CONFIG_FILE "configuration-miscellaneous.xml" ///< config file base

using namespace std;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

std::string ConfigurationPersistenceManager::filePath = CONFIG_FILE;
ConfigurationPersistenceManager * ConfigurationPersistenceManager::singleton_instance = NULL; ///< The configuration persistence manager singleton instance
ISMTTLog* ConfigurationPersistenceManager::logger = SMTTLogManager::GetLogger("Smartmatic.Configuration.ConfigurationPersistenceManager",GETTEXT_PACKAGE); ///< The configuration persistence manager logger

ConfigurationPersistenceManager::ConfigurationPersistenceManager()
{

}

void ConfigurationPersistenceManager::Initialize(std::string filePath)
{
	try
	{
	      cr = auto_ptr<ConfigurationBase>(parseConfigurationBaseRoot(filePath.c_str(),ConfigurationTypes::Flags::dont_validate ));
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
	    logger->Debug("Config file not found");
	}
}

void ConfigurationPersistenceManager::LoadDefault()
{
	try
	{
        filebuf fb;
		fb.open (filePath.c_str(),ios::out);
	    ostream os(&fb);
		ConfigurationBase *base = new ConfigurationBase();

		Smartmatic::ConfigurationTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_CONFIGURATION;
        map[""].schema = "";

		serializeConfigurationBaseRoot(os,*base, map, "UTF-8");
		fb.close();
		delete(base);
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config Error", "Error");
		exit (0);
	}
}

ConfigurationPersistenceManager& ConfigurationPersistenceManager::Current ()
{ 
	if ( ! singleton_instance )
	{
		singleton_instance = new ConfigurationPersistenceManager ();
		singleton_instance->Initialize(filePath);
	}

	return *singleton_instance;
}

string ConfigurationPersistenceManager::GetLibraryConfigFile(string nameOfLibrary)
{
	std::string out;
	if(cr.get() == 0)
		return out;
	ConfigurationBase::ConfigurationTypeConstIterator iterator(cr->getConfigurationType().begin());
	const ConfigurationBase::ConfigurationTypeConstIterator enditerator (cr->getConfigurationType().end());

	while(iterator != enditerator)
	{
		const ConfigurationType & ct (*iterator++);		
		if (nameOfLibrary.compare(ct.getName()) == 0)
		{
            std::stringstream message;
            message << "Name of Library: " << ct.getName();
            logger->Debug(message.str());
			out.append(ct.getConfiguration());
			break;
		}
	}
	
	return out;
}

void ConfigurationPersistenceManager::SetLibraryConfigFile(string nameOfLibrary, string on)
{
	if(cr.get() == NULL)
	{
		cr =auto_ptr<ConfigurationBase>(new ConfigurationBase());
	}
	ConfigurationBase::ConfigurationTypeIterator iterator(cr->getConfigurationType().begin());
	const ConfigurationBase::ConfigurationTypeIterator enditerator (cr->getConfigurationType().end());
	
	while(iterator != enditerator)
	{		
		if (nameOfLibrary.compare(iterator->getName()) == 0)
		{
		    std::stringstream message;
            message << "Name of Library: " << iterator->getName();
            logger->Debug(message.str());
			iterator->setConfiguration (on);
			return;
		}
		iterator++;
	}
	ConfigurationType *type = new ConfigurationType();
	type->setConfiguration(on);
	type->setName(nameOfLibrary);
	type->setDescription("");
	cr->getConfigurationType().push_back(*type);
	delete(type);
	
}

void ConfigurationPersistenceManager::SaveFile()
{
	try
	{
        filebuf fb;
		fb.open (filePath.c_str(),ios::out);
	    ostream os(&fb);

	    Smartmatic::ConfigurationTypes::NamespaceInfomap map;
	        map[""].name = NAMESPACE_CONFIGURATION;
	        map[""].schema = "";

		serializeConfigurationBaseRoot(os,*cr, map, "UTF-8");
		fb.close();
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Save Config Error", "Error");
		exit (0);
	}
}
