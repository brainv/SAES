/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C)  2011 <>
 * 
 * @file	saes-temporal-directories.h
 *
 * @brief	Declares the saes temporal directories class.
 * 
 * saescommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saescommon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SAES_TEMPORAL_DIRECTORIES_H_
#define _SAES_TEMPORAL_DIRECTORIES_H_
#include <string>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include "Runtime/Environment/SaesInstallDirectories.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Runtime
		{
			namespace Environment
			{
				/**
				 * @class	SaesTemporalDirectories
				 *
				 * @brief	Saes temporal directories. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class SaesTemporalDirectories: public SaesInstallDirectories
				{
                   public:

							SaesTemporalDirectories();
							virtual ~SaesTemporalDirectories();

		                    /**
		                     * @fn	std::string SaesTemporalDirectories::getWorkingDirectoryFolderName();
		                     *
		                     * @brief	overrides the working directory
		                     *
		                     * @author	Freddy.Gomez
		                     * @date	5/18/2011
		                     *
		                     * @return	The master configuration base path.
		                     */
		                    std::string getWorkingDirectoryFolderName();
                };
			}
		}
	}
}


#endif // _SAES_TEMPORAL_DIRECTORIES_H_
