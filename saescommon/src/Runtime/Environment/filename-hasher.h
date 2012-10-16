/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * @file	filename-hasher.h
 *
 * @brief	Declares the filename hasher class.
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

#include <System/Security/Cryptography/MsgDigestUtil.h>
#include <string>
#include <glib.h>

#ifndef _FILE_NAME_HASHER_H_
#define _FILE_NAME_HASHER_H_

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
				/**
				 * @class	FileNameHasher
				 *
				 * @brief	File name hasher. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class FileNameHasher
				{
					public:

						/**
						 * @fn	FileNameHasher::FileNameHasher();
						 *
						 * @brief	Default constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						FileNameHasher();

						/**
						 * @fn	FileNameHasher::~FileNameHasher();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						~FileNameHasher();

						/**
						 * @fn	std::string FileNameHasher::GetFileNameHasher(std::string name);
						 *
						 * @brief	Gets a file name hasher.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	name	The name.
						 *
						 * @return	The file name hasher.
						 */

						std::string GetFileNameHasher(std::string name);

						/**
						 * @fn	std::string FileNameHasher::GetFileNameHasher(unsigned char * name, int nameLeng);
						 *
						 * @brief	Gets a file name hasher.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param [in,out]	name	If non-null, the name.
						 * @param	nameLeng		The name leng.
						 *
						 * @return	The file name hasher.
						 */

						std::string GetFileNameHasher(unsigned char * name, int nameLeng);

						
					protected:

					private:

						/**
						 * @fn	std::string FileNameHasher::GetValidBase64(SafeBuffer buffer_inner);
						 *
						 * @brief	Gets a valid base 64.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	buffer_inner	The buffer inner.
						 *
						 * @return	The valid base 64.
						 */

						std::string GetValidBase64(Smartmatic::System::SafeBuffer & buffer_inner);

						/**
						 * @fn	std::string FileNameHasher::ReplaceInvalidCharacters(std::string name);
						 *
						 * @brief	Replace invalid characters.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	name	The name.
						 *
						 * @return	.
						 */

						std::string ReplaceInvalidCharacters(std::string name);

				};
			}
		}
	}
}

#endif // _FILE_NAME_HASHER_H_
