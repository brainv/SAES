/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMTT_GUI_IMAGE_RESOURCE_MANAGER_H_

/**
 * @brief	Gets the smtt graphical user interface image resource manager h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMTT_GUI_IMAGE_RESOURCE_MANAGER_H_
#include "config.h"
#include "Environment/Configurations/image-resources-manager-base.h"
namespace Smartmatic
{
	namespace GUI
	{
		namespace Configuration
		{
			
			class SmttGuiImageResourceManager: public Smartmatic::Environment::ImageResourcesManagerBase
			{
			public:

				/**
				 * @brief	Gets the current.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static SmttGuiImageResourceManager* Current();

				/**
				 * @brief	Initialises this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void  init();
				

			protected:

				/**
				 * @brief	Gets the package name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
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
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmttGuiImageResourceManager()
				{
				}

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~SmttGuiImageResourceManager()
				{
				}
				static SmttGuiImageResourceManager * singleton_instance;	///< The singleton instance

			private:

			};
		}
	}
}



#endif // _SMTT_GUI_IMAGE_RESOURCE_MANAGER_H_
