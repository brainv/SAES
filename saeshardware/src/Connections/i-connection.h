/**
 * @file	i-connection.h
 *
 * @brief	Declares the i-connection interface.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * commandstructure
 * Copyright (C)  2010 <>
 * 
 * commandstructure is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * commandstructure is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _I_CONNECTION_H_
#define _I_CONNECTION_H_

#include <vector>
#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>
#include <algorithm>
#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Connections
			{
				/**
				 * @brief	Interface to define the contract that each connection should accomplish.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class IConnection
				{
				public:

					IConnection();

					virtual ~IConnection();

				/**
				 * @brief	Send this message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 *
				 * @return	.
				 */

				virtual int Send(std::vector<unsigned char> data) = 0;

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				virtual bool Initialize()= 0;

				/**
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				virtual void Dispose()= 0;

				/**
				 * @brief	Flushs the read buffer.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				virtual void FlushReadBuffer()= 0;		

				/**
				 * @brief	Reads the data.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				virtual std::vector<unsigned char> Read()= 0;

				/**
				 * @brief	Close the connection.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				virtual int Close()= 0;

				/**
				 * @brief	Opens the connections.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				virtual bool Open()= 0;

				/**
				 * @brief	Starts a peeking.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				virtual int StartPeeking()= 0;
				protected:

				private:

				};
			}
		}
	}
}

#endif // _I_CONNECTION_H_
