
#include "image-resources-manager-base.h"
#include "System/IO/Directory.h"
#include "System/IO/Path.h"
#include <Log/ISMTTLog.h>
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

using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace std;
using namespace Smartmatic::Log;

ISMTTLog* ImageResourcesManagerBase::logger = SMTTLogManager::GetLogger("Smartmatic.Environment.ImageResourcesManagerBase",GETTEXT_PACKAGE);

void ImageResourcesManagerBase::Initialize()
{
	//job done
}


Glib::RefPtr<Gdk::Pixbuf> ImageResourcesManagerBase::lookInAllPaths(std::string key, string culture)
{
	Glib::RefPtr<Gdk::Pixbuf> pixBuff;
	Glib::RefPtr<Gdk::Pixbuf> defaultPixBuff;
	bool found = false;
	string packageName(this->getPackageName());
	string pathToUse;
	vector<string> filesList = this->getAllPossiblePaths();
	vector<string> filesListInner;
	for(unsigned int i=0;i< filesList.size() ;i++)
	{		
		pathToUse.clear();
		string packageName = this->getPackageName();
		pathToUse =  filesList[i];
		if(packageName.compare("")!=0)
		{
			if(pathToUse.at(pathToUse.size()-1)!='/' && pathToUse.at(pathToUse.size()-1)!='\\')
			{
				pathToUse.append("/");
			}
			pathToUse.append(packageName);
		}
		
		if(pathToUse.at(pathToUse.size()-1) !='/' && pathToUse.at(pathToUse.size()-1) !='\\')
		{
			pathToUse.append("/");
		}
		
		if(pathToUse.at(0)!='/')
		{
			pathToUse.insert(0,Path::GetCurrentDirectory());
		}

		vector<string> files = vector<string>();
		Directory::GetFiles(pathToUse, files, false,true);
		int size = files.size();

		for(int h=0; h < size;h++)
		{
			std::string fileToLook = key;
			std::string fileLooked = files[h];
			int pos = fileLooked.find(".");	
			files[h].erase(files[h].begin(),files[h].begin()+files[h].find_last_of('.')+1);
			string cultureOfCurrent = files[h]; 
			logger->Debug("Culture of current file is: " + cultureOfCurrent);
			logger->Debug("Looked culture is: " + culture);
			if(fileLooked.substr(0,pos).compare(fileToLook)==0)
			{		
				std::string fileToOpen;
				if(cultureOfCurrent.compare(culture)==0)
				{
					fileToOpen = pathToUse + fileLooked;
					logger->Debug("File to open is: " + fileToOpen);
					pixBuff =Gdk::Pixbuf::create_from_file(fileToOpen);
					found = true;
					if(storeInCache)
					{
						registerKey(key,cultureOfCurrent, pixBuff);
					}						
				}	
				else if(storeInCache)
				{
					fileToOpen = pathToUse + fileLooked;
					logger->Debug("File to store in registry is: " + fileToOpen);
					Glib::RefPtr<Gdk::Pixbuf> pixBuffRegistry =Gdk::Pixbuf::create_from_file(fileToOpen);
					registerKey(key, cultureOfCurrent, pixBuffRegistry);													
				}
				if(cultureOfCurrent.compare("")==0)
				{
					logger->Debug("Store as global culture : " + fileToOpen);
					defaultPixBuff =Gdk::Pixbuf::create_from_file(fileToOpen);
				}
			}
		}
	}
	if(found)
	{
		logger->Debug("File was found and returned, with culture given");
		return pixBuff;
	}
	else
	{
		logger->Debug("File was not found (trying to return default culture, if exists)");
		return defaultPixBuff;
	}
	
}

void ImageResourcesManagerBase::registerKey(std::string key,std::string cultureOfCurrent,  Glib::RefPtr<Gdk::Pixbuf> pixBuff)
{
	if(cultureMap[cultureOfCurrent] == NULL)
	{
		map<string, Glib::RefPtr<Gdk::Pixbuf> > *cultureResources = new map<string,Glib::RefPtr<Gdk::Pixbuf> >();
		cultureMap[cultureOfCurrent] = cultureResources;
		(*cultureResources)[key] = pixBuff;
	}
	else if(cultureMap[cultureOfCurrent] != NULL)
	{
		map<string, Glib::RefPtr<Gdk::Pixbuf> >::const_iterator  pairKeyImage =  cultureMap[cultureOfCurrent]->find(key);
		if(pairKeyImage ==  cultureMap[cultureOfCurrent]->end())
		{
			  (*cultureMap[cultureOfCurrent])[key] = pixBuff;
		}
	}		
}


Glib::RefPtr<Gdk::Pixbuf> ImageResourcesManagerBase::lookInMap(string key, string culture)
{
	map<string , map<string,Glib::RefPtr<Gdk::Pixbuf> >* >::const_iterator cultureResources = cultureMap.find(culture);
	map<string, Glib::RefPtr<Gdk::Pixbuf> > *resources = NULL; 
	if(cultureResources != cultureMap.end())
	{
		resources = cultureResources->second;
	}

	if(resources!= NULL && (*resources).find(key) != (*resources).end())
	{
		logger->Debug("Found in map with given culture");
		return (*resources).find(key)->second;
	}
	else
	{
		map<string , map<string,Glib::RefPtr<Gdk::Pixbuf> >* >::const_iterator cultureCurrentResources = cultureMap.find(getCurrentCulture());
		if(cultureCurrentResources != cultureMap.end())
		{
			resources = cultureCurrentResources->second;
		}
		if(resources!= NULL && (*resources).find(key) != (*resources).end())
		{
			logger->Debug("Found in map with current culture");
			return (*resources).find(key)->second;
		}
		else
		{
			map<string , map<string,Glib::RefPtr<Gdk::Pixbuf> >* >::const_iterator cultureDefaultResources = cultureMap.find(getDefaultCulture());
			if(cultureDefaultResources != cultureMap.end())
			{
				resources = cultureDefaultResources->second;
			}
			
			if(resources!= NULL && (*resources).find(key) != (*resources).end())
			{
				logger->Debug("Found in map with default culture");
				return (*resources).find(key)->second;
			}
			else
			{
					map<string , map<string,Glib::RefPtr<Gdk::Pixbuf> >* >::const_iterator cultureGlobalResources = cultureMap.find("");
					if(cultureGlobalResources != cultureMap.end())
					{
					resources = cultureGlobalResources->second;
					}
					if(resources!= NULL && (*resources).find(key) != (*resources).end())
					{
						logger->Debug("Found in map with global culture");
						return (*resources).find(key)->second;
					}
					else
					{
						Glib::RefPtr<Gdk::Pixbuf> empty;
						logger->Debug("Not found in map for culture: " + culture + " - key: " + key);
						return empty;
					}
			}
		}
	}
}


Glib::RefPtr<Gdk::Pixbuf> ImageResourcesManagerBase::getResource(std::string  key, std::string culture) 
{
	Glib::RefPtr<Gdk::Pixbuf> pixBufResult;
	if(storeInCache)
	{
		pixBufResult = lookInMap(key,culture);
	}
	if(!pixBufResult)
	{
		pixBufResult = lookInAllPaths(key,culture);
	}
	return pixBufResult;
}


ImageResourcesManagerBase::~ImageResourcesManagerBase()
{
	delete(&cultureMap);
}

