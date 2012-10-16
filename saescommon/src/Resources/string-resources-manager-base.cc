/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * saescommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saescommon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Resources/string-resources-manager-base.h"
#include <Security/Encryption.hxx>
#include <gtkmm.h>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <Log/SMTTLogManager.h>

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

using namespace std;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::Log;

ISMTTLog* StringResourcesManagerBase::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Resources.StringResourcesManagerBase",GETTEXT_PACKAGE);

void StringResourcesManagerBase::Initialize()
{
    cultureMap.clear();
	vector<string> files = vector<string>();

	if (Directory::DirectoryExists(this->getFullFolderPath()))
	{
	    logger->Debug("Open directory: " + this->getFullFolderPath());
	}
	else
	{
        logger->Debug("Directory " + this->getFullFolderPath() + " not found.");
	    return;
	}

	Directory::GetFiles(this->getFullFolderPath(), files, false,true);
    int size = files.size();
    bool errorLoading = false;
    bool fileLoaded = false;
	for(int i=0; i < size;i++)
	{
		std::string fileToLook = this->getFileName();
		fileToLook.erase(fileToLook.end()-4,fileToLook.end());	
		std::string fileLooked = files[i];		
		std::transform(fileToLook.begin(), fileToLook.end(), fileToLook.begin(), ::toupper);
		std::transform(fileLooked.begin(), fileLooked.end(), fileLooked.begin(), ::toupper);
		int pos = fileLooked.find(fileToLook);
		if(pos>=0)
		{
			try
			{
				std::string file = Path::Combine(this->getFullFolderPath(), files[i]);
			    logger->Debug("Open file: " + file);

				std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file, Smartmatic::SAES::Security::Encryption::RESOURCE_FILE);

				std::istringstream istr (data);
				auto_ptr< Strings_resources> resources =  parseStrings_resources(istr,ResourcesTypes::Flags::dont_validate );
				
				files[i].erase(files[i].begin(),files[i].begin()+fileToLook.size());
				files[i].erase(files[i].end()-4,files[i].end());
				Glib::ustring culture = files[i];
				culture = culture.lowercase().c_str();

				map<string, string> *cultureResources = new map<string,string>();
				Strings_resources::String_resourceIterator iterator(resources->getString_resource().begin());
				Strings_resources::String_resourceIterator enditerator(resources->getString_resource().end());

				std::stringstream ss;
				ss << "Load culture: " << culture << " - number resources keys: " << resources->getString_resource().size();
                logger->Debug(ss.str());

				while(iterator != enditerator)
				{
					const String_resource & resource (*iterator++);
					(*cultureResources)[resource.getKey()] = resource.getValue();
				}
				cultureMap[culture] = cultureResources;
				fileLoaded = true;

			}
			catch (const ::xsd::cxx::tree::exception< char >& e)
			{
				errorLoading = true;
		        std::stringstream ss;
			 	ss<< "FATAl - " << __func__ << " " << e;
				logger->Debug(ss.str());

			}
			catch (Smartmatic::System::Exception::CryptoException & e)
			{
				errorLoading = true;
		        std::stringstream ss;
			 	ss<< "FATAl - " << __func__ << " " << e.what();
				logger->Debug(ss.str());
			}
			catch (Smartmatic::System::Exception::SignedException & e)
			{
				errorLoading = true;
		        std::stringstream ss;
			 	ss<< "FATAl - " << __func__ << " " << e.what();
				logger->Debug(ss.str());
			}
			catch (Smartmatic::System::Exception::XmlException & e)
			{
				errorLoading = true;
		        std::stringstream ss;
			 	ss<< "FATAl - " << __func__ << " " << e.what();
				logger->Debug(ss.str());
			}
			catch (...)
			{
				errorLoading = true;
		        std::stringstream ss;
			 	ss<< "FATAl - " << __func__;
				logger->Debug(ss.str());
			}

		}
	}
	if(fileLoaded == true  && errorLoading == false)
	{
		resourcesLoaded = true;
	}
	//job done
	
}

const string& StringResourcesManagerBase::getResource(const string & key, const string culture) const
{
        Glib::ustring cultureStr(culture);
        string fixedCulture = cultureStr.lowercase().c_str();
	map<string , map<string,string>* >::const_iterator cultureResources = cultureMap.find(fixedCulture);
	map<string, string> *resources = NULL; 
	if(cultureResources != cultureMap.end())
	{
		resources = cultureResources->second;
	}

	if(resources!= NULL && (*resources).find(key) != (*resources).end())
	{
		return (*resources).find(key)->second;
	}
	else
	{
		map<string , map<string,string>* >::const_iterator cultureCurrentResources = cultureMap.find(getCurrentCulture());
		if(cultureCurrentResources != cultureMap.end())
		{
			resources = cultureCurrentResources->second;
		}
		if(resources!= NULL && (*resources).find(key) != (*resources).end())
		{
			return (*resources).find(key)->second;
		}
		else
		{
			map<string , map<string,string>* >::const_iterator cultureDefaultResources = cultureMap.find(getDefaultCulture());
			if(cultureDefaultResources != cultureMap.end())
			{
				resources = cultureDefaultResources->second;
			}
			
			if(resources!= NULL && (*resources).find(key) != (*resources).end())
			{
				return (*resources).find(key)->second;
			}
			else
			{
					map<string , map<string,string>* >::const_iterator cultureGlobalResources = cultureMap.find("");
					if(cultureGlobalResources != cultureMap.end())
					{
					resources = cultureGlobalResources->second;
					}
					if(resources!= NULL && (*resources).find(key) != (*resources).end())
					{
						return (*resources).find(key)->second;
					}
					else
					{
						return key;
					}
			}
		}
	}

}

void StringResourcesManagerBase::setCurrentCulture(const string& newCulture)
{
	Glib::ustring culture = newCulture;
	currentCulture = culture.lowercase().c_str();
}

StringResourcesManagerBase::~StringResourcesManagerBase()
{
	delete(&cultureMap);
}
