/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ELECTION_STRING_RESOURCES_MANAGER_H_
#define _ELECTION_STRING_RESOURCES_MANAGER_H_

#include "Resources/string-resources-manager-base.h"
#include "Runtime/Environment/saes-directories.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Resources
		{
			/**
			 * @class ElectionStringResourcesManager
			 * @brief	Manager for election string resources. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 * @see StringResourcesManagerBase
			 */

			class ElectionStringResourcesManager: public StringResourcesManagerBase
			{
			public:

					/**
					 * @brief	Gets the current Election String Resources Manager.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the Election String Resources Manager.
					 */

					static ElectionStringResourcesManager* Current();

					/**
					 * @brief	Initialises this object.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	saesDir	The saes dir.
					 */

					void init(Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDir,
							Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
			protected:

			private:

					/**
					 * @brief	Gets the file name.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The file name.
					 */

					std::string & getFileName();

					/**
					 * @brief	Gets the full folder path.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The full folder path.
					 */

					std::string & getFullFolderPath();
					std::string fileName;   ///< Filename of the file
					std::string folderPath; ///< Full pathname of the folder file

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */
					ElectionStringResourcesManager();

					/**
					 * @brief	Class destroy
					 *
					 * @author	Yadickson Soto
					 * @date	16/02/2012
					 */
					virtual ~ElectionStringResourcesManager();

					static ElectionStringResourcesManager * singleton_instance; ///< The singleton instance of the Election String Resources Manager
			};
		}
	}
}

#endif // _ELECTION_STRING_RESOURCES_MANAGER_H_
