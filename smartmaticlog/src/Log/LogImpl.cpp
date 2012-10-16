/**
 * @file LogImpl.cpp
 * @brief Body file class LogImpl, declares the log implementation class.
 * @date 08-03-2011
 * @author gerardohernandez
 */

#include "LogImpl.h"
#include <iostream>
#include <dirent.h>
#include <vector>
#include "log4cxx/rollingfileappender.h"
#include "log4cxx/helpers/transcoder.h"
#include <typeinfo>

using namespace Smartmatic::Log;
using namespace log4cxx::helpers;
using namespace log4cxx::spi;
using namespace log4cxx;
using namespace std;

LogImpl::LogImpl(log4cxx::LoggerPtr loggerInfoArg,
	log4cxx::LoggerPtr loggerErrorArg,
	log4cxx::LoggerPtr loggerWarnArg,
	log4cxx::helpers::Pool& pool,
	const log4cxx::LogString& name,
	std::string domain)
: Logger(pool, name)
{
	loggerError = loggerErrorArg;
	loggerInfo = loggerInfoArg;
	loggerWarn = loggerWarnArg;
	currentName = name;
	useResourceManager = false;
	this->domain = domain;
	activatePathValidation = false;
}

void LogImpl::doLog(log4cxx::LevelPtr level,
	std::string messageCode,
	std::map < std::string, std::string > properties,
	std::exception t,
	std::vector < std::string > messageArgument)
{	
	if(loggerPtr->isEnabledFor(level))
		return;

	if(messageCode == "")
		return;

	string message;

	if(useResourceManager)
	{
		//TODO:agregar el uso de archivos de recursos
	}
	else
		message = messageCode;

	if(messageArgument.size() > 0)
	{
		//TODO:agregar el uso de formatos
	}

	try
	{
	    LoggingEventPtr loggingEvent = new LoggingEvent(LOG4CXX_STR(currentName), level,
	                                                 LOG4CXX_STR(message), LocationInfo::getLocationUnavailable());

	    loggingEvent->setProperty(LOG4CXX_STR("SMTTMessageCode"), LOG4CXX_STR(messageCode));

	    loggerPtr->log(level, message);
	}
	catch(std::exception & ex)
	{
	    std::cerr << __LINE__ << " LogImpl: FATAL - " << ex.what() << std::endl;
	}
}

void LogImpl::doLog(log4cxx::LevelPtr level,
	std::string messageCode)
{
	if(messageCode == "")
		return;

	string message;

	if(useResourceManager)
	{
		//TODO:agregar el uso de archivos de recursos
	}
	else
		message = messageCode;

	try
	{
        LoggingEventPtr loggingEvent = new LoggingEvent(LOG4CXX_STR(currentName), level,
                                                     LOG4CXX_STR(message), LocationInfo::getLocationUnavailable());

        loggingEvent->setProperty(LOG4CXX_STR("SMTTMessageCode"), LOG4CXX_STR(messageCode));

        if(level == Level::getDebug())
        {
        	if(validatePath(loggerInfo))
        	{
        		LOG4CXX_DEBUG(loggerInfo, message);
        	}
        }

        if(level == Level::getInfo())
        {
        	if(validatePath(loggerInfo))
        	{
        		LOG4CXX_INFO(loggerInfo, message);
        	}
        }

        if(level == Level::getTrace())
        {
        	if(validatePath(loggerError))
        	{
        		LOG4CXX_TRACE(loggerError, message);
        	}
        }

        if(level == Level::getWarn())
        {
        	if(validatePath(loggerWarn))
        	{
        		LOG4CXX_WARN(loggerWarn, message);
        	}
        }

        if(level == Level::getError())
        {
        	if(validatePath(loggerWarn))
        	{
        		LOG4CXX_ERROR(loggerWarn, message);
        	}
        }

        if(level == Level::getFatal())
        {
        	if(validatePath(loggerWarn))
        	{
        		LOG4CXX_FATAL(loggerWarn, message);
        	}
        }
	}
    catch(std::exception & ex)
    {
	    std::cerr << " LogImpl: FATAL - " << ex.what() << std::endl;
    }
}

void LogImpl::Debug(std::string messageCode)
{
	doLog(Level::getDebug(), messageCode);
}

void LogImpl::Debug(std::string messageCode,
	std::exception errorEntry)
{	
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	
	doLog(Level::getDebug(), messageCode, currentProperties, errorEntry, currentmessageArguments);
}

void LogImpl::Info(std::string messageCode)
{
	doLog(Level::getInfo(), messageCode);
}

void LogImpl::Info(std::string messageCode,
	std::exception errorEntry)
{
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	
	doLog(Level::getInfo(), messageCode, currentProperties, errorEntry, currentmessageArguments); 
}

void LogImpl::Audit(std::string messageCode)
{
	if(domain != "")
		doLog(Level::getWarn(), domain+"#"+messageCode);
	else
		doLog(Level::getWarn(), messageCode);
}

void LogImpl::Audit(std::string messageCode,
	std::exception errorEntry)
{
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	

	if(domain != "")
		doLog(Level::getWarn(), domain+"#"+messageCode, currentProperties, errorEntry, currentmessageArguments);
	else
		doLog(Level::getWarn(), messageCode, currentProperties, errorEntry, currentmessageArguments);
}

void LogImpl::Warn(std::string messageCode)
{
	doLog(Level::getWarn(), messageCode);
}

void LogImpl::Warn(std::string messageCode,
	std::exception errorEntry)
{
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	
	doLog(Level::getWarn(), messageCode, currentProperties, errorEntry, currentmessageArguments);
}

void LogImpl::Error(std::string messageCode)
{
	if(domain != "")
		doLog(Level::getError(), domain+"#"+messageCode);
	else
		doLog(Level::getError(), messageCode);
}

void LogImpl::Error(std::string messageCode,
	std::exception errorEntry)
{
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	

	if(domain != "")
		doLog(Level::getError(), domain+"#"+messageCode, currentProperties, errorEntry, currentmessageArguments);
	else
		doLog(Level::getError(), messageCode, currentProperties, errorEntry, currentmessageArguments);
}

void LogImpl::Fatal(std::string messageCode)
{
	doLog(Level::getFatal(), messageCode);
}

void LogImpl::Fatal(std::string messageCode,
	std::exception errorEntry)
{
	map<string, string> currentProperties;
	vector<string> currentmessageArguments;	
	doLog(Level::getFatal(), messageCode, currentProperties, errorEntry, currentmessageArguments);
}

bool LogImpl::validatePath(log4cxx::LoggerPtr logger)
{
	if(activatePathValidation)
	{
		vector<AppenderPtr> appenders = logger->getAllAppenders();
		RollingFileAppender* appenderTemp = new RollingFileAppender();

		for(int i = 0; i < (int)appenders.size(); i++)
		{
			std::string currentAppenderName = typeid(*appenders[i]).name();
			std::string typeName = typeid(*appenderTemp).name();

			//RollingFile
			if(currentAppenderName.find("RollingFile") != string::npos)
			{
				RollingFileAppender* apender = (RollingFileAppender*) &appenders[i];

				std::string currentFile;
				log4cxx::helpers::Transcoder::encode(apender->getFile(), currentFile);

				if(DirectoryExists(currentFile))
				{
					return true;
				}
			}
		}

		delete(appenderTemp);
	}
	else
		return true;

	return false;

}

bool LogImpl::DirectoryExists(const std::string & path)
{
	DIR *dp;
	if((dp  = opendir(path.c_str())) == NULL)
	{
		return false;
	}
	else
	{
		closedir(dp);
		return true;
	}
}

