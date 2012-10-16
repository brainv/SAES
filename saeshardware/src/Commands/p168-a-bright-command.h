/**
 * @file	p168-a-bright-command.h
 *
 * @brief	Declares the 168 a bright command class.
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

#ifndef _P168_A_BRIGHT_COMMAND_H_
#define _P168_A_BRIGHT_COMMAND_H_

#include "command-base-p168-a.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Manage the bright command on the P168A.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class P168ABrightCommand: public CommandBaseP168A
				{
	
				public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	brightness	The brightness.
				 */

				P168ABrightCommand(unsigned char brightness);

				/**
				 * @brief	Gets the specific response from raw.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void GetSpecificResponseFromRaw();
	
				protected:

				private:

				std::vector<unsigned char> result;  ///< The result

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Initialize();	

				/**
				 * @brief	Proccess response.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	response	The response.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool ProccessResponse(std::vector<unsigned char> response);

				unsigned char bright;   ///< The bright level of the P168.
				};
			}
		}
	}
}



#endif // _P168_A_BRIGHT_COMMAND_H_
