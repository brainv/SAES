/**
 * @file FOPTransformer.cxx
 * @brief Body class FOPTransformer, xml to pdf runtime
 * @date 27/10/2011
 * @author Yadickson Soto
 */

#include "FOPTransformer.hxx"
#include <System/Runtime/ProcessLauncher.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/Directory.h>

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

using namespace Smartmatic::System::XSLFO;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;

ISMTTLog* FOPTransformer::logger = SMTTLogManager::GetLogger("Smartmatic.System.XSLFO.FOPTransformer",GETTEXT_PACKAGE);
std::string FOPTransformer::configFile = "fop.xconf";

FOPTransformer::FOPTransformer()
{

}

FOPTransformer::~FOPTransformer()
{

}

void FOPTransformer::setConfigFile(std::string configFile)
{
	FOPTransformer::configFile = configFile;
}

bool FOPTransformer::transformFile(std::string outputFile, std::string inputFile, std::string templateFile)
{
	logger->Debug("Execute transformation");

	std::string command;
	command.append("fop");
	command.append(" -xml ");
	command.append(inputFile);
	command.append(" -xsl ");
	command.append(templateFile);
	command.append(" -pdf ");
	command.append(outputFile);

	if (!configFile.empty() && Directory::FileExists(configFile))
	{
		command.append(" -c ");
		command.append(configFile);
	}

	return Smartmatic::System::Runtime::ProcessLauncher::RunProcessThroughSystem(command) == 0;
}
