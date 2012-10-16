/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	InitializationStatus.hxx
 *
 * @brief	initialization status class.
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INITIALIZATION_RESULT_H_
#define _INITIALIZATION_RESULT_H_

#include <iostream>
#include <string.h>
#include <map>

namespace Smartmatic
{
	namespace SAES 
	{
		namespace Operation
		{
            namespace Initiator
            {
			namespace TestStatus
			{
				enum Tests
				{
					DirectoryStructure,
					FilesPresence,
					FlashPresence,
					FlashStructure,
					MemoryUsed,
					MemoryComplete,
					FilesValidation,
					ConfigurationLoad,
					Passed,
					Failed,
					NotTested
				};
			};

			/**
			 * @class	InitializationStatus
			 *
			 * @brief	Initialization status. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class InitializationStatus
			{
			public:

				/**
				 * @fn	InitializationStatus::InitializationStatus();
				 *
				 * @brief	Default constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				InitializationStatus();

				/**
				 * @fn	InitializationStatus::~InitializationStatus();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				~InitializationStatus();

				/**
				 * @fn	bool InitializationStatus::getSuccess();
				 *
				 * @brief	Gets the success.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getSuccess();

				/**
				 * @fn	std::string InitializationStatus::getMessage();
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
				 * @fn	std::map<TestStatus::Tests, TestStatus::Tests>* InitializationStatus::getStatuses();
				 *
				 * @brief	Gets the statuses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	null if it fails, else the statuses.
				 */

				std::string getImageFileName();

				std::string getImageErrorFileName();

				std::map<TestStatus::Tests, TestStatus::Tests> & getStatuses();

				/**
				 * @fn	void InitializationStatus::setSuccess(bool result);
				 *
				 * @brief	Sets the success.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	result	true to result.
				 */

				void setSuccess(bool result);

				/**
				 * @fn	void InitializationStatus::setMessage(std::string msg);
				 *
				 * @brief	Sets a message.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	msg	The message.
				 */

				void setMessage(std::string msg);

				void setImageFileName(std::string img);

				void setImageErrorFileName(std::string imgErrorFileName);

				/**
				 * @fn	void InitializationStatus::setStatuses(TestStatus::Tests test, TestStatus::Tests status);
				 *
				 * @brief	Sets the statuses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	test  	The test.
				 * @param	status	The status.
				 */

				void setStatuses(TestStatus::Tests test, TestStatus::Tests status);
					
			protected:

			private:
				std::map<TestStatus::Tests, TestStatus::Tests> initializationStatus;   ///< The initialization status
				bool isSuccess; ///< true if the is operation was a success, false if it failed
				std::string message;	///< The message
				std::string imageFileName; 	///< The image running
				std::string imageErrorFileName;	///< The image of error
			};
            }
		}
	}
}


#endif // _INITIALIZATION_RESULT_H_
