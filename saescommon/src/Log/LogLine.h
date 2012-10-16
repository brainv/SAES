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

#ifndef _LOGLINE_H_
#define _LOGLINE_H_
#include <string>
#include <vector>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			/**
			 * @class LogLine
			 * @brief Header class LogLine
			 * @author Rafael Ferrero <rafael.ferrero@smartmatic.com>
			 */
			class LogLine
			{
				public:

					enum LevelLog
					{ 
						TRACE,
						DEBUG,
						INFO,
						WARNING,
						ERROR,
						FATAL
					};

					/**
					 * @fn	std::string LogLine::getDate();
					 *
					 * @brief	Gets the date.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The date.
					 */

					std::string getDate();

					/**
					 * @fn	void LogLine::setDate(std::string date);
					 *
					 * @brief	Sets a date.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	date	The date.
					 */

					void setDate(std::string date);

					/**
					 * @fn	std::string LogLine::getLibrary();
					 *
					 * @brief	Gets the library.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The library.
					 */

					std::string getLibrary();

					/**
					 * @fn	void LogLine::setLibrary(std::string library);
					 *
					 * @brief	Sets a library.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	library	The library.
					 */

					void setLibrary(std::string library);

					/**
					 * @fn	std::string LogLine::getMessage();
					 *
					 * @brief	Gets the message.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The message.
					 */

					std::string getMessage();

					/**
					 * @fn	void LogLine::setMessage(std::string message);
					 *
					 * @brief	Sets a message.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	message	The message.
					 */

					void setMessage(std::string message);

					/**
					 * @fn	std::vector<std::string> LogLine::getMessageParams();
					 *
					 * @brief	Gets the message parameters.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The message parameters.
					 */

					std::vector<std::string> getMessageParams();

					/**
					 * @fn	void LogLine::setMessageParams(std::vector<std::string> messageParams);
					 *
					 * @brief	Sets a message parameters.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	messageParams	Options for controlling the message.
					 */

					void setMessageParams(std::vector<std::string> messageParams);

					/**
					 * @fn	LevelLog LogLine::getLevel();
					 *
					 * @brief	Gets the level.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The level.
					 */

					LevelLog getLevel();

					/**
					 * @fn	void LogLine::setLevel(LevelLog level);
					 *
					 * @brief	Sets a level.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	level	The level.
					 */

					void setLevel(LevelLog level);

					/**
					 * @fn	std::string LogLine::getTimeSinceStart();
					 *
					 * @brief	Gets the time since start.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The time since start.
					 */

					std::string getTimeSinceStart();

					/**
					 * @fn	void LogLine::setTimeSinceStart(std::string time);
					 *
					 * @brief	Sets a time since start.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	time	The time.
					 */

					void setTimeSinceStart(std::string time);					
				protected:

				private:
					std::string date;   ///< The date
					std::string library;	///< The library
					std::string message;	///< The message
					std::vector<std::string> messageParams; ///< Options for controlling the message
					LevelLog level; ///< The level
					std::string timeSinceStart; ///< The time since start
			};
		}
	}
}

#endif // _LOGLINE_H_
