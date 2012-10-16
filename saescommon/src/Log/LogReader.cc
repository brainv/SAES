/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C) Rafael Ferrero 2011 <rafael.ferrero@smartmatic.com>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogReader.h"
#include "LogCryptoPool.hxx"
#include <System/IO/File.h>
#include <System/Utils/StringUtils.hxx>
#include <Log/ICryptoLayoutTransformer.hxx>
#include <Log/SMTTLogManager.h>
#include <fstream>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Utils;

ISMTTLog* LogReader::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Log.LogReader",GETTEXT_PACKAGE);

enum LogPart
{
     LOG_DATE
    ,LOG_MESSAGE
    ,LOG_LEVEL
    ,LOG_TIME_STAMP
    ,LOG_END
};

enum LogMessagePart
{
     LOG_MESSAGE_LIBRARY
    ,LOG_MESSAGE_STR
};

LogReader::LogReader(std::string logFile, unsigned int sizePage, Smartmatic::SAES::Common::Configuration::CryptoType type)
{
	this->sizePage = sizePage;
	this->type = type;
	this->logLines = ProcessFilesToGetLogLines(logFile);
}

std::vector<LogLine> LogReader::getLogLines()
{
	return this->logLines;
}

std::vector<LogLine> LogReader::ProcessFilesToGetLogLines(std::string logFile)
{
    std::vector<LogLine> logLines;

    std::ifstream ifs(logFile.c_str());

    if (ifs.is_open())
    {
        while(ifs.good())
        {
            std::string line;
            getline(ifs, line);

            if (line.empty()) continue;

            ICryptoLayoutTransformer * interface = LogCryptoPool::getInstance()->getLogCrypto(type);

            if (interface)
            {
                line = interface->decode(line);
            }

            LogLine log = ReadLine(line);
            if (!log.getDate().empty())logLines.push_back(log);
        }

        ifs.close();
    }
	
	return logLines;
}

LogLine LogReader::ReadLine(std::string line)
{
	std::list<std::string> lines = StringUtils::split(line,"@");
    std::list<std::string>::iterator it;

	LogLine logLine;
	int count = LOG_DATE;

	for (it = lines.begin();
	     it != lines.end();
	     it++, count++)
	{

	    switch((LogPart)count)
	    {
	        case LOG_DATE:
	            logLine.setDate(*it);
	            break;

            case LOG_MESSAGE:
                StringToMessagelog(*it, logLine);
                break;

            case LOG_LEVEL:
                 logLine.setLevel(StringToLevelLog(*it));
                 break;

            case LOG_TIME_STAMP:
                 logLine.setTimeSinceStart(*it);
                 break;

            default:
                break;
	    }
	}

	return logLine;
}

void LogReader::StringToMessagelog(std::string line, LogLine & logLine)
{
    std::list<std::string> list = StringUtils::split(line,"#");
    std::list<std::string>::iterator it;

    int count = LOG_MESSAGE_LIBRARY;

    for (it = list.begin();
         it != list.end();
         it++, count++)
    {
        switch((LogMessagePart)count)
        {
            case LOG_MESSAGE_LIBRARY:
                logLine.setLibrary(*it);
                break;
            case LOG_MESSAGE_STR:
                logLine.setMessage(dgettext(logLine.getLibrary().c_str(), (*it).c_str()));
                break;
        }
    }
}

LogLine::LevelLog LogReader::StringToLevelLog(std::string level)
{
	LogLine::LevelLog result;
	
	if(level == "TRACE")
		result = LogLine::TRACE;
	else if(level == "DEBUG")
		result = LogLine::DEBUG;
	else if(level == "INFO")
		result = LogLine::INFO;
	else if(level == "WARN")
		result = LogLine::WARNING;
	else if(level == "ERROR")
		result = LogLine::ERROR;
	else if(level == "FATAL")
		result = LogLine::FATAL;
	else
		result = LogLine::TRACE;
	
	return result;
}

LogPage LogReader::getPage(unsigned int page)
    throw(LogReaderException)
{
	if(page <= 0 || page > getPageCount())
	{
	    page = 1;
	}

	unsigned int start = (page-1)*this->sizePage;

	std::vector<LogLine> logLinesPage;
	for(unsigned int i = start; 
	    i < start + this->sizePage &&
	    i < logLines.size(); i++)
	{
		logLinesPage.push_back(this->logLines[i]);
	}
	
	LogPage logPage(page, logLinesPage);
	return logPage;
}

unsigned int LogReader::getPageCount()
{
	int result = 0;
	
	int sizeTotal = this->logLines.size();
	if(sizeTotal==0 )
		result = 1;
	else
	{
		result = sizeTotal/this->sizePage;
		if(sizeTotal%this->sizePage!=0)
			result++;
	}	
	return result;
}

