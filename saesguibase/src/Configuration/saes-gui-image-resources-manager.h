/**
 * @file	saes-gui-image-resources-manager.h
 *
 * @brief	Declares the saes graphical user interface image resources manager class.
 */

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

#ifndef _SAES_GUI_IMAGE_RESOURCES_MANAGER_H_
#define _SAES_GUI_IMAGE_RESOURCES_MANAGER_H_
#include "config.h"
#include "Environment/Configurations/image-resources-manager-base.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Configuration
			{
				/**
				 * @brief	Manager for saes graphical user interface image resources.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class SaesGuiImageResourcesManager: public Smartmatic::Environment::ImageResourcesManagerBase
				{
				public:

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static SaesGuiImageResourcesManager* Current();

					/**
					 * @brief	Initialises this resource manager.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 */

					void  init();
				

				protected:

					/**
					 * @brief	Gets the package name.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 *
					 * @return	The package name.
					 */

					std::string getPackageName()
					{
						std::string packageName(PACKAGE_NAME);
						packageName.append("/ui");
						return packageName;
					}

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 */

					SaesGuiImageResourcesManager()
					{
					}

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 */

					~SaesGuiImageResourcesManager()
					{
					}

					static SaesGuiImageResourcesManager * singleton_instance;   ///< The singleton instance

				private:

				};
			}
		}
	}
}


#endif // _SAES_GUI_IMAGE_RESOURCES_MANAGER_H_
