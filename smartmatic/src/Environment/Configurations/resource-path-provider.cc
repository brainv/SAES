
#include "resource-path-provider.h"
#include <Environment/Configurations/base-language-controller.h>
#include "Configuration/smartmatic-conf-manager.h"
#include <cerrno>
#include <string>
#include <stdio.h>

#include "System/IO/Path.h"
#include "System/IO/File.h"

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

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;


ResourcePathProvider::ResourcePathProvider()
{
	dirPaths.push_back(DATADIR);
	::xsd::cxx::tree::sequence< ::Smartmatic::ConfigurationTypes::String > *pathsSequence = &((*SmartmaticConfigurationManager::Current()->getConfiguration())->getResourcePaths().getResourcePath());
	int size = pathsSequence->size();
	for(int i=0;i < size;i++)
	{
		dirPaths.push_back((*pathsSequence)[i]);	
	}
	//	dirPaths.push_back("/usr/local/share/");
	//	dirPaths.push_back("/usr/local/");
}


string ResourcePathProvider::GetResourcePath(const string& libDirectory, const string& relativePath)
{

	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{

	}

	string currentPath;
	currentPath.append(cCurrentPath);

	string path = Path::Combine(currentPath,libDirectory);
	path = Path::Combine(path,relativePath);

	if (!File::canOpenFile(path))
	{
        int size = dirPaths.size();

		for(int i=0;i<size;i++)
		{
			path.clear();
			path = Path::Combine(dirPaths[i],Path::Combine(libDirectory,relativePath));
		
			if (File::canOpenFile(path))
			{
				break;
			}
			else
			{
				path.clear();
			}
		}
	}

	if (!path.empty())
	{
		std::string extension = Path::GetFileExtension(path);
		std::string langFile = Path::GetFullFileNameWithOutExtension(path) + BaseLanguageController::getActualLanguage() + extension;

		if(File::canOpenFile(langFile))
		{
			path = langFile;
		}
	}

	return path;
}



ResourcePathProvider * ResourcePathProvider::singleton_instance = NULL; ///< The resource path provider singleton instance


ResourcePathProvider *ResourcePathProvider::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new ResourcePathProvider ();

	return singleton_instance;
}
