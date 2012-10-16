/**
 * @file OptParser.cxx
 * @brief Body class OptParser
 * @author Yadickson Soto
 * @date 23/08/2011
 */

#include "OptParser.hxx"
#include "Configuration/configuration-persistence-manager.h"
#include <getopt.h>
#include <sstream>
#include <glibmm.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <System/ZenityWrapper.hxx>
#include <System/XSLFO/FOPTransformer.hxx>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///< Macro gettext
#else
#define _(String) (String) ///< Macro not gettext
#endif

#define CONFIG_FILENAME "configuration-miscellaneous.xml" ///< config file base
#define LOG_CONFIG_FILENAME "log4-configuration.xml" ///< logger file
#define XSLFO_CONFIG_FILENAME "fop.xconf" ///< fop config file

using namespace Smartmatic::System;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::XSLFO;

static struct option long_options[] =
{
    {"config", 1, 0, 0},
    {"logger", 1, 0, 0},
    {"xslfo", 1, 0, 0},
    {"mode", 1, 0, 0 },
    {"help", 0, 0, OptParser::HELP},
    {"version", 0, 0, OptParser::VERS},
    {0, 0, 0, 0}
}; ///< Option values

ISMTTLog* OptParser::logger = SMTTLogManager::GetLogger("Smartmatic.System.OptParser",GETTEXT_PACKAGE);

OptParser::OptParser(int argc, char **argv, const std::string & package, const std::string & version, std::string basepath)
{
    this->argc = argc;
    this->argv = argv;

    processArgs(package, version, basepath);
}

bool OptParser::isSet(OptParser::Options opt)
{
    if (argc <= 1) return false;
    int c;

    optarg = NULL;
    optind = opterr = optopt = 0;

    while (1)
    {
        int option_index = 0;

        c = getopt_long_only(argc, argv, "hcv", long_options, &option_index);
        if (c == -1) break;
        if (option_index == (int)opt) return true;
        if (c == (int) HELP && opt == HELP) return true;
        if (c == (int) VERS && opt == VERS) return true;
    }

    return false;
}

void OptParser::getArg(OptParser::Options opt, std::string & str)
{
	str = "";

    if (argc <= 1) return;

    int c;

    optarg = NULL;
    optind = opterr = optopt = 0;

    while (1)
    {
        int option_index = 0;

        c = getopt_long_only(argc, argv, "hcv", long_options, &option_index);
        if (c == -1) break;
        if (!optarg) continue;
        if (option_index == (int)opt)
        {
        	str = optarg;
        	break;
        }
    }
}

bool OptParser::getConfigOption(std::string & config)
{
	return getStringOption(OptParser::CONFIG, config);
}

bool OptParser::getLoggerOption(std::string & logger)
{
	return getStringOption(OptParser::LOGGER, logger);
}

bool OptParser::getHelpOption(std::string & help)
{
	return getStringOption(OptParser::HELP, help);
}

bool OptParser::getVersionOption(std::string & version)
{
	return getStringOption(OptParser::VERS, version);
}

bool OptParser::getStringOption(OptParser::Options opt, std::string & str)
{
	bool validate = isSet(opt);

	if (validate)
	{
		switch (opt)
		{
			case OptParser::CONFIG:
			case OptParser::LOGGER:
			case OptParser::MODE:
			case OptParser::XSLFO:
				getArg(opt, str);
				validate = !str.empty();
				break;
			case OptParser::HELP:
				{
					std::stringstream ss;
					ss << "  --config f         " << "f: path config file" << std::endl;
					ss << "  --logger f         " << "f: path logger file" << std::endl;
					ss << "  --xslfo  f         " << "f: path xslfo file" << std::endl;
					ss << "  --mode   mp|mv     " << "mode for mp or mv" << std::endl;
					ss << "  -h, --help         " << "this help application" << std::endl;
					ss << "  -v, --version      " << "version application" << std::endl;
					str = ss.str();
				}
				break;
			case OptParser::VERS:
				str = VERSION;
				break;
		}
	}

	return validate;
}

void OptParser::processArgs(const std::string & package, const std::string & version, std::string basepath)
{
	std::string configFile = "";
	std::string loggerFile = "";
	std::string xslfoFile = "";
	std::string helpStr = "";
	std::string mode;

	if ( getHelpOption( helpStr ) )
	{
		std::cout << "Program name: " << package << std::endl;
		std::cout << "Version: " << version << std::endl;
		std::cout << std::endl;
		std::cout << " " << package << " " << "[options]" << std::endl;
		std::cout << " " << "options" << std::endl;
		std::cout << helpStr << std::endl;
		exit (0);
	}
	else if ( isSet( OptParser::VERS ) )
	{
		std::cout << "Program name: " << package << std::endl;
		std::cout << "Version: " << version << std::endl;
		std::cout << std::endl;
		exit (0);
	}
	else if ( isSet( OptParser::MODE ) )
	{
		getArg( OptParser::MODE, mode);

		Glib::ustring str = mode;
		mode = str.uppercase();
	}

	if ( ! getConfigOption(configFile) )
	{
		configFile = Path::Combine(Path::Combine(basepath, mode), CONFIG_FILENAME);
	}
	if ( ! getLoggerOption(loggerFile) )
	{
		loggerFile = Path::Combine(Path::Combine(basepath, mode), LOG_CONFIG_FILENAME);
	}
	if ( ! getStringOption(OptParser::XSLFO, xslfoFile) )
	{
		xslfoFile = Path::Combine(Path::Combine(basepath, mode), XSLFO_CONFIG_FILENAME);
	}

	if(Directory::FileExists(CONFIG_FILENAME))
	{
		ConfigurationPersistenceManager::filePath = CONFIG_FILENAME;
	}
	else if(Directory::FileExists(configFile))
	{
		ConfigurationPersistenceManager::filePath = configFile;
	}
	else
	{
		ZenityWrapper::showError("Error load config file (" + std::string(CONFIG_FILENAME) + ")", "Error");
		exit(0);
	}

	if(Directory::FileExists(LOG_CONFIG_FILENAME))
	{
		SMTTLogManager::Configure(LOG_CONFIG_FILENAME);
	}
	else if(Directory::FileExists(loggerFile))
	{
		SMTTLogManager::Configure(loggerFile);
	}
	else
	{
		ZenityWrapper::showError("Error load logger file (" + std::string(LOG_CONFIG_FILENAME) + ")", "Error");
		exit(0);
	}

	if (Directory::FileExists(XSLFO_CONFIG_FILENAME))
	{
		FOPTransformer::setConfigFile(XSLFO_CONFIG_FILENAME);
	}
	else if(Directory::FileExists(xslfoFile))
	{
		FOPTransformer::setConfigFile(xslfoFile);
	}
}
