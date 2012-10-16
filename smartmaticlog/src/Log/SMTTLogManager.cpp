/**
 * @file	SMTTLogManager.cpp
 * @brief	Declares the smtt log manager class.
 * @date 8/07/2011
 * @author gerardohernandez
 */

#include "SMTTLogManager.h"
#include <string>
#include "LogImpl.h"
#include "ISMTTLog.h"
#include <log4cxx/helpers/pool.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/layout.h>
#include <log4cxx/patternlayout.h>

using namespace std;
using namespace Smartmatic::Log;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::rolling;
using namespace log4cxx::helpers;

#define LOG_CONF_FILENAME "log4-configuration.xml" ///< file name logger

std::string SMTTLogManager::fullFilePath = LOG_CONF_FILENAME;

ISMTTLog* SMTTLogManager::Exist(std::string name)
{
	return Exist(name, NULL);
}

ISMTTLog* SMTTLogManager::Exist(std::string name, std::string domain)
{
	return NULL;
}

vector<ISMTTLog*> SMTTLogManager::GetCurrentLoggers()
{
	vector<ISMTTLog*> v;
	return v;	
}

vector<ISMTTLog*> SMTTLogManager::GetCurrentLoggers(std::string domain)
{
	vector<ISMTTLog*> v;
	return v;
}

ISMTTLog* SMTTLogManager::GetLogger(std::string name, std::string domain)
{	
	LoggerPtr loggerError = LogManager::getLogger(name);
	LoggerPtr loggerInfo = LogManager::getLogger(name);
	LoggerPtr loggerWarn = LogManager::getLogger(name);

	Pool* pool = new Pool();	
	return new LogImpl(loggerInfo, loggerError, loggerWarn, *pool, name, domain);
}

void SMTTLogManager::Configure(std::string fileName)
{
    fullFilePath = fileName;
	DOMConfigurator::configure(fileName);
}

void SMTTLogManager::Reconfigure()
{
    DOMConfigurator::configure(fullFilePath);
}

void SMTTLogManager::Configure()
{
	BasicConfigurator::configure();
}

void SMTTLogManager::shutdown()
{
	LogManager::shutdown();
}

const std::string & SMTTLogManager::getConfigFile()
{
	return fullFilePath;
}
