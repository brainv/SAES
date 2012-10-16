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

#ifndef _LOGREADER_H_
#define _LOGREADER_H_

#include "Log/LogLine.h"
#include <Log/LogPage.h>
#include <vector>
#include <string>
#include <Log/ISMTTLog.h>
#include <System/Exception/LogReaderException.h>
#include <Configuration/SaesCommonConfiguration-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			/**
			 * @class LogReader
			 * @brief Header class LogReader
			 * @author Rafael Ferrero <rafael.ferrero@smartmatic.com>
			 */
			class LogReader
			{
				public:
					/**
					 * @brief Class constructor
					 * @param logFile path of the log file to read
					 */
					LogReader(std::string logFile, unsigned int sizePage, Smartmatic::SAES::Common::Configuration::CryptoType type );

					/**
					 * @brief method to obtain a LogLine list
					 * @return vector of LogLine in the logfile
					 */
					std::vector<LogLine> getLogLines();
					
					/**
					 * @brief count of total pages for paging
					 * @return int total of pages
					 */					 
					unsigned int getPageCount();

					/**
					 * @brief method to obtain a object of page.
					 * @return LogPage page
					 */					 
					LogPage getPage(unsigned int page)
                        throw(Smartmatic::System::Exception::LogReaderException);

				protected:

				private:

                    void StringToMessagelog(std::string line, LogLine & logLine);

                    /**
					 * @brief transfor a string into a LevelLog 
					 * if not match return LevelLog::TRACE
					 * @param string to transform
					 * @return LevelLog  
					 */					 
					LogLine::LevelLog StringToLevelLog(std::string level);
					/**
					 * @brief read a line of log and return a LogLine 
					 * @param line of log
					 * @return LogLine  
					 */			
					LogLine ReadLine(std::string line);

					/**
					 * @brief Procces file to obtain all lines
					 * @return vector of LogLine in the log file
					 */
					std::vector<LogLine> ProcessFilesToGetLogLines(std::string logFile);
					
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
					std::vector<LogLine> logLines; /**<loglines*/
					unsigned int sizePage; /**<sizePage*/
					Smartmatic::SAES::Common::Configuration::CryptoType type;

			};
		}
	}
}

#endif // _LOGREADER_H_
