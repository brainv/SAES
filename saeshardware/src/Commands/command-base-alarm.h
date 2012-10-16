/**
 * @file	command-base-alarm.h
 *
 * @brief	Declares the command base alarm class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saeshardware
 * Copyright (C)  2011 <>
 * 
 * saeshardware is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saeshardware is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COMMAND_BASE_ALARM_H_
#define _COMMAND_BASE_ALARM_H_

#include "Commands/command-structure.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Gets the sender for the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderSenderAlarm: public IProviderSender
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderSenderAlarm() {}

						/**
						 * @brief	Gets the sender.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @return	The sender.
						 */

						std::vector<unsigned char> getSender();
				};

				/**
				 * @brief	Gets the length for the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderLenghtAlarm: public IProviderLenght
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderLenghtAlarm() {}

					/**
					 * @brief	Gets a lenght.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	commandDataSize	Size of the command data.
					 *
					 * @return	The lenght.
					 */

					std::vector<unsigned char> getLenght(int commandDataSize);
				};

				/**
				 * @brief	Gets the CheckSum for the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderCheckSumAlarm: public IProviderCheckSum
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderCheckSumAlarm() {}

					/**
					 * @brief	Gets a check sum.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 *
					 * @return	The check sum.
					 */

					std::vector<unsigned char> getCheckSum(std::vector<unsigned char> data);
				};

				/**
				 * @brief	Gets the trailer for the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderTrailerAlarm: public IProviderTrailer
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderTrailerAlarm() {}

					/**
					 * @brief	Gets the trailer.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The trailer.
					 */

					std::vector<unsigned char> getTrailer();
				};

				/**
				 * @brief	Base class for managing the alarm commands and its properties.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class CommandBaseAlarm: public CommandStructure
				{
				public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				CommandBaseAlarm();

				/**
				 * @brief	Execute an alarm on the connection provider.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param [in,out]	connectionProvider	If non-null, the connection provider.
				 *
				 * @return	.
				 */

				std::vector<unsigned char> Execute(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider);

				protected:

					std::vector<unsigned char> rawResponse; ///< The raw response

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual void Initialize()=0;

					/**
					 * @brief	Gets the specific response from raw.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual void GetSpecificResponseFromRaw()=0;

					/**
					 * @brief	Gets the order of command.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual void getOrderOfCommand();
				private:
					std::vector<unsigned char> result;  ///< The result of the command executed.
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				};
			};
		};
	};
};

#endif // _COMMAND_BASE_ALARM_H_

