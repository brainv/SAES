/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file time-functionality.h
 * @brief functionality to trace time stamp
 * @author Juan Delgado 2011 <juan.delgado@smartmatic.com>
 */

#ifndef _TIME_FUNCTIONALITY_H_
#define _TIME_FUNCTIONALITY_H_

#include <time.h>
#include <iostream>
#include <sstream>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace Functionality
	{
		/**
		 * @brief	Time functionality class. 
		 *
		 * @author	Juan Delgado
		 * @date	28/04/2011
		 */

		class TimeFunctionality
		{
		public:

			/**
			 * @brief	Gets a difference between two times given.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @param	start	The start time.
			 * @param	end  	The end time.
			 *
			 * @return	The difference.
			 */

			static timespec GetDifference(timespec& start, timespec& end);

			/**
			* @brief	Gets the current time.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @return	The current time.
			 */

			static std::string GetCurrentTime();

			/**
			 * @brief	Starts a time.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @return	The current time at String.
			 */

			static std::string StartTime();

			/**
			 * @brief	Gets the start time difference.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @return	The start time difference.
			 */

			static std::string GetStartTimeDifference();

			/**
			 * @brief	Convert time to string.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @param	timestring	The timestring.
			 *
			 * @return	The current time at String.
			 */

			static std::string ConvertTimeToString(timespec timestring);

			/**
			 * @brief	Gets the time.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @return	The time.
			 */

			static timespec GetTime();

			/**
			 * @brief	Gets a date time.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 *
			 * @param [in,out]	strDateTime	Time of the string date.
			 */

			static void GetDateTime(std::string& strDateTime);

			/**
			 * @brief	Starts a time print out.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 */

			static void StartTimePrintOut();

			/**
			 * @brief	Gets the start time difference print out.
			 *
			 * @author	Juan Delgado
			 * @date	28/04/2011
			 */

			static void GetStartTimeDifferencePrintOut();

		private:

			
			static timespec time1; ///< The first time
			static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
		};
	}
}

#endif // _TIME_FUNCTIONALITY_H_
