/**
 * @file	smart-card-reader.h
 *
 * @brief	Declares the smart card reader class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk-foobar
 * Copyright (C)  2011 <>
 * 
 * gtk-foobar is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-foobar is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMART_CARD_READER_H_
#define _SMART_CARD_READER_H_

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				/**
				 * @brief	Handle the communications medium between the smart card and a machine.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class SmartCardReader
				{
	
				public:

				bool init();

				/**
				 * @brief	Tests this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Test();

				/**
				 * @brief	Reads the object at the given address.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address	The address to read.
				 * @param	count  	Number of bytes to read.
				 *
				 * @return	.
				 */

				bool Read(int address, int count, std::vector<unsigned char> & buffer);

				/**
				 * @brief	Writes to the reader on the given address.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address	The address to write.
				 * @param	buffer 	The buffer of data to write.
				 * @param	offset 	The offset to write.
				 * @param	count  	Number of bytes to write.
				 */

				bool Write(int address, std::vector<unsigned char> & buffer, int offset, int count);

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool Initialize();

				/**
				 * @brief	Gets the card present.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getCardPresent();

				/**
				 * @brief	Indicates if the reader is connected.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getConnected();

				/**
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Dispose();

				/**
				 * @brief	Gets the current object of the reader.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static SmartCardReader *Current();
						
				protected:
	



				private:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					SmartCardReader();	

					static SmartCardReader *current_instance;   ///< The current instance of the reader.
			
	
				};
			}
		}
	}
}

#endif // _SMART_CARD_READER_H_
