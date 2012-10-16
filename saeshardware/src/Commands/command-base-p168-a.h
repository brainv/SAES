/**
 * @file	command-base-p168-a.h
 *
 * @brief	Declares the command base p 168 the class.
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

#ifndef _COMMAND_BASE_P168_A_H_
#define _COMMAND_BASE_P168_A_H_
#include "Commands/command-structure.h"


namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Gets the sender for the P168A.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderSenderP168A: public IProviderSender
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderSenderP168A() {}

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
				 * @brief	Gets the length for the P168A.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderLenghtP168A: public IProviderLenght
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderLenghtP168A() {}

					/**
					 * @brief	Gets the lenght of the command data.
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
				 * @brief	Gets the CheckSum for the P168A.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderCheckSumP168A: public IProviderCheckSum
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderCheckSumP168A() {}

					/**
					 * @brief	Gets the check sum of the data.
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
				 * @brief	Gets the trailer for the P168A.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderTrailerP168A: public IProviderTrailer
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderTrailerP168A() {}

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
				 * @brief	Base class for managing the P168A commands and its properties.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class CommandBaseP168A: public CommandStructure
				{
				public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				CommandBaseP168A();

				/**
				 * @brief	Executes the P168 command on the connection provider.
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
				private:

					std::vector<unsigned char> result;  ///< The result of the command executed.

					/**
					 * @brief	Gets the order of command.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void getOrderOfCommand();

				};
			};
		};
	};
};



#endif // _COMMAND_BASE_P168_A_H_
