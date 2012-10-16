/**
 * @file	image-resources-manager-base.h
 *
 * @brief	Header file to the image resources manager base class.
 */

#ifndef _IMAGE_RESOURCES_MANAGER_BASE_H_
#define _IMAGE_RESOURCES_MANAGER_BASE_H_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <glibmm.h>
#include <gtkmm.h>
#include <Configuration/smartmatic-conf-manager.h>
namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace Environment
	{
		/**
		 * @brief	Image resources manager base class. 
		 *
		 * @author	Rafael.gasperi
		 * 		
		 * @date	28/04/2011
		 */

		class ImageResourcesManagerBase
		{
				public:

					/**
					 * @brief	Sets a current culture.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	newCulture	The new culture.
					 */

					void setCurrentCulture(std::string newCulture)
					{
						currentCulture = newCulture;
					}

					/**
					 * @brief	Gets the current culture.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @return	The current culture.
					 */

					std::string  getCurrentCulture() 
					{
						return currentCulture;
					}

					/**
					 * @brief	Sets a default culture.
					 *
					 * @author	Rafael.gasperi
					 * 			
					 * @date	28/04/2011
					 *
					 * @param	newDefault	The new default.
					 */

					void setDefaultCulture(std::string newDefault)
					{
						defaultCulture = newDefault;
					}

					/**
					 * @brief	Gets the default culture.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @return	The default culture.
					 */

					std::string  getDefaultCulture() 
					{
						return defaultCulture;
					}

					/**
					 * @brief	Gets a resource.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	key	The key of a resource.
					 *
					 * @return	The resource.
					 */

					Glib::RefPtr<Gdk::Pixbuf>  getResource(std::string  key) 
					{
						return getResource(key, currentCulture);
					}

					/**
					 * @brief	Gets a resource.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	key	   	The key of a resource.
					 * @param	culture	The culture.
					 *
					 * @return	The resource.
					 */

					Glib::RefPtr<Gdk::Pixbuf> getResource(std::string key, std::string culture);
				
				protected:

					/**
					 * @brief	Gets the package name.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @return	The package name.
					 */

					virtual std::string getPackageName() = 0;

					/**
					 * @brief	Gets all possible paths.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @return	all possible paths.
					 */

					virtual std::vector<std::string> getAllPossiblePaths()
					{
						std::vector<std::string> list;
						list = Smartmatic::Configuration::SmartmaticConfigurationManager::Current()->getListOfResourcesPaths();
						return list;
					}

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 */

					~ImageResourcesManagerBase();

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 */

					ImageResourcesManagerBase():
						currentCulture("en"),defaultCulture("en"),temp("")
					{
						storeInCache = Smartmatic::Configuration::SmartmaticConfigurationManager::Current()->getImageStorageInMemory();
					};
				private:

					/**
					 * @brief	Registers the key.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	key					The key.
					 * @param	cultureOfCurrent	The culture of current.
					 * @param	pixBuff				Buffer for pix data.
					 */

					void registerKey(std::string key,std::string cultureOfCurrent,  Glib::RefPtr<Gdk::Pixbuf> pixBuff);

					
					bool storeInCache; ///< true to store in cache

					/**
					 * @brief	Look in map.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	key	   	The key.
					 * @param	culture	The culture.
					 *
					 * @return	.
					 */

					Glib::RefPtr<Gdk::Pixbuf> lookInMap(std::string key, std::string culture);

					/**
					 * @brief	Look in all paths.
					 *
					 * @author	Rafael.gasperi
					 * 			 
					 * @date	28/04/2011
					 *
					 * @param	key	   	The key.
					 * @param	culture	The culture.
					 *
					 * @return	.
					 */

					Glib::RefPtr<Gdk::Pixbuf> lookInAllPaths(std::string key, std::string culture);

					
					std::map<std::string , std::map<std::string,Glib::RefPtr<Gdk::Pixbuf> >* > cultureMap; ///< The culture map

					
					std::string currentCulture; ///< The current culture

					
					std::string defaultCulture; ///< The default culture

					
					std::string temp; ///< The temp

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
		};
	}
}

#endif // _IMAGE_RESOURCES_MANAGER_BASE_H_
