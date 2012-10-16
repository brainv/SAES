/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#ifndef _ELECTION_IMAGE_RESOURCES_MANAGER_H_
#define _ELECTION_IMAGE_RESOURCES_MANAGER_H_
#include "config.h"
#include "Environment/Configurations/image-resources-manager-base.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace Resources
		{
			/**
			 * @brief	Manager for election image resources. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class ElectionImageResourcesManager: public Smartmatic::Environment::ImageResourcesManagerBase
			{
			public:

				/**
				 * @brief	Gets the current  Election Image Resources Manager.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else the  Election Image Resources Manager.
				 */

				static ElectionImageResourcesManager* Current();

				/**
				 * @brief	Initialises this object.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void  init();
				

			protected:

				/**
				 * @brief	Gets the package name.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The package name.
				 */

				std::string getPackageName()
				{
					std::string packageName("");
					return packageName;
				}

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				ElectionImageResourcesManager()
				{
				}

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				~ElectionImageResourcesManager()
				{
				}
				static ElectionImageResourcesManager * singleton_instance;  ///< The singleton instance of the Election Image Resources Manage

			private:

			};					
		}
	}
}


#endif // _ELECTION_IMAGE_RESOURCES_MANAGER_H_
