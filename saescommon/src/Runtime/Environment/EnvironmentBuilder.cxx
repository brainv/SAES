/**
 * @file EnvironmentBuilder.cxx
 * @brief Body class environment build
 * @date 15/11/2011
 * @author Yadickson Soto
 */

#include "EnvironmentBuilder.hxx"
#include <System/IO/File.h>
#include <System/IO/Path.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/Runtime/ProcessLauncher.h>

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

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Runtime;

ISMTTLog* EnvironmentBuilder::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Runtime.Environment.EnvironmentBuilder",GETTEXT_PACKAGE);

EnvironmentBuilder::EnvironmentBuilder()
{

}

EnvironmentBuilder::~EnvironmentBuilder()
{

}

bool EnvironmentBuilder::install(
		SaesInstallDirectories * orig,
		SaesDirectories * dest)
{
	logger->Debug("Copy dir " + orig->getBasePath() + " to " + dest->getBasePath());

	std::string moveDir = "cp -R " + Path::Combine(orig->getBasePath(), "*") + " " + dest->getBasePath();

	(void)ProcessLauncher::RunProcessThroughSystem(moveDir.c_str());

	std::vector <std::string> listOrig;
	std::vector <std::string> listDest;

	getFileList (orig, listOrig);
	getFileList (dest, listDest);

	for (unsigned int i = 0;i < listDest.size();i++)
	{
		std::string fileDest = listDest[i];
		std::string fileOrig = listOrig[i];

		if (File::canOpenFile(fileOrig) && !File::canOpenFile(fileDest))
		{
			File::copyFile(fileOrig, fileDest);
			logger->Debug("Copy file " + fileOrig + " to " + fileDest);
		}
	}

	return true;
}

void EnvironmentBuilder::getFileList ( SaesDirectories * dir, std::vector <std::string> & list )
{
	list.clear();
	list.push_back(dir->getElectionFileFullPath());
}

void EnvironmentBuilder::getFolderList ( SaesDirectories * dir, std::vector <std::string> & list )
{
	list.clear();
}
