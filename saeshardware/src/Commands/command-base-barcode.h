/**
 * @file	command-base-barcode.h
 *
 * @brief	Declares the command base barcode class.
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

#ifndef _COMMAND_BASE_BARCODE_H_
#define _COMMAND_BASE_BARCODE_H_
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
				 * @brief	Gets the sender of the barcode.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderSenderBarcode: public IProviderSender
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderSenderBarcode() {}

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
				 * @brief	Gets the length of the barcode.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderLenghtBarcode: public IProviderLenght
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderLenghtBarcode() {}

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
				 * @brief	Gets the checksum of the barcode.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderCheckSumBarcode: public IProviderCheckSum
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderCheckSumBarcode() {}

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
				 * @brief	Gets the trailer of the barcode.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class ProviderTrailerBarcode: public IProviderTrailer
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					ProviderTrailerBarcode() {}

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
				 * @brief	Base class for managing the barcode commands and its properties.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class CommandBaseBarcode: public CommandStructure
				{
				public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				CommandBaseBarcode();

				/**
				 * @brief	Executes the barcode in the connection provider.
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



#endif // _COMMAND_BASE_BARCODE_H_
