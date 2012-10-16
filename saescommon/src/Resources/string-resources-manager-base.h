/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saescommon
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 *
 * @file	string-resources-manager-base.h
 *
 * @brief	Declares the string resources manager base class.
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

#ifndef _STRING_RESOURCES_MANAGER_BASE_H_
#define _STRING_RESOURCES_MANAGER_BASE_H_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <Resources/strings-resources-schema.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Resources
		{
			/**
			 * @class	StringResourcesManagerBase
			 *
			 * @brief	String resources manager base. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class StringResourcesManagerBase
			{
				public:

					/**
					 * @fn	virtual string & StringResourcesManagerBase::getFileName() = 0;
					 *
					 * @brief	Gets the file name.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The file name.
					 */

					virtual std::string & getFileName() = 0;

					/**
					 * @fn	virtual string & StringResourcesManagerBase::getFullFolderPath() = 0;
					 *
					 * @brief	Gets the full folder path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The full folder path.
					 */

					virtual std::string & getFullFolderPath() = 0;

					/**
					 * @fn	void StringResourcesManagerBase::setCurrentCulture(const string& newCulture);
					 *
					 * @brief	Sets a current culture.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	newCulture	The new culture.
					 */

					void setCurrentCulture(const std::string& newCulture);

					/**
					 * @fn	const string & StringResourcesManagerBase::getCurrentCulture() const
					 *
					 * @brief	Gets the current culture.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The current culture.
					 */

					const std::string & getCurrentCulture() const
					{
						return currentCulture;
					}

					/**
					 * @fn	void StringResourcesManagerBase::setDefaultCulture(const string& newDefault)
					 *
					 * @brief	Sets a default culture.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	newDefault	The new default.
					 */

					void setDefaultCulture(const std::string& newDefault)
					{
						defaultCulture = newDefault;
					}

					/**
					 * @fn	const string & StringResourcesManagerBase::getDefaultCulture() const
					 *
					 * @brief	Gets the default culture.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The default culture.
					 */

					const std::string & getDefaultCulture() const
					{
						return defaultCulture;
					}

					/**
					 * @fn	const string & StringResourcesManagerBase::getResource(const string & key) const
					 *
					 * @brief	Gets a resource.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	key	The key.
					 *
					 * @return	The resource.
					 */

					const std::string & getResource(const std::string & key) const
					{
						return getResource(key, currentCulture);
					}

					/**
					 * @fn	const string & StringResourcesManagerBase::getResource(const string & key,
					 * 		const string culture) const;
					 *
					 * @brief	Gets a resource.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	key	   	The key.
					 * @param	culture	The culture.
					 *
					 * @return	The resource.
					 */

					const std::string & getResource(const std::string & key, const std::string culture) const;

					/**
					 * @fn	StringResourcesManagerBase::~StringResourcesManagerBase();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					virtual ~StringResourcesManagerBase();
				protected:

					/**
					 * @fn	void StringResourcesManagerBase::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void Initialize();

					/**
					 * @fn	StringResourcesManagerBase::StringResourcesManagerBase()
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					StringResourcesManagerBase():
						currentCulture("en"),defaultCulture("en"),temp(""),resourcesLoaded(false)
					{}
				private:
					std::map<std::string , std::map<std::string,std::string>* > cultureMap;  ///< The culture map
					std::string currentCulture;  ///< The current culture
					std::string defaultCulture;  ///< The default culture
					std::string temp;	///< The temp
					bool resourcesLoaded;   ///< true to resources loaded
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
			};
		}
	}
}

#endif // _STRING_RESOURCES_MANAGER_BASE_H_
