/**
 * @file	configuration-persistence-manager.h
 *
 * @brief	Header file to the configuration persistence manager class.
 */

#ifndef _CONFIGURATION_PERSISTENCE_MANAGER_H_
#define _CONFIGURATION_PERSISTENCE_MANAGER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <Configuration/ConfigurationBase-schema.hxx>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

	namespace Configuration
	{
		/**
		 * @brief	Manager for configuration persistences class. 
		 *
		 * @author	Rafael.gasperi
		 *
		 * @date	28/04/2011
		 */

		class ConfigurationPersistenceManager
		{
		public:

			/**
			 * @brief	Gets the current Configuration Persistence Manager.
			 *
			 * @author	Rafael.gasperi
			 
			 * @date	28/04/2011
			 *
			 * @return	.
			 */

			static ConfigurationPersistenceManager& Current();

			/**
			 * @brief	Initializes this object.
			 *
			 * @author	Rafael.gasperi
			 * 		
			 * @date	28/04/2011
			 *
			 * @param	filePath	Full pathname of the file.
			 */

			void Initialize(std::string filePath);

			/**
			 * @brief	Gets a library configuration file.
			 *
			 * @author	Rafael.gasperi
			 *
			 * @date	28/04/2011
			 *
			 * @param	nameOfLibrary	Name of the library.
			 *
			 * @return	The library configuration file.
			 */

			std::string GetLibraryConfigFile(std::string nameOfLibrary);

			/**
			 * @brief	Sets a library configuration file.
			 *
			 * @author	Rafael.gasperi
			 * 		
			 * @date	28/04/2011
			 *
			 * @param	nameOfLibrary	Name of the library.
			 * @param	on			 	The on.
			 */

			void SetLibraryConfigFile(std::string nameOfLibrary, std::string on);

			/**
			 * @brief	Saves the file.
			 *
			 * @author	Rafael.gasperi
			 *
			 * @date	28/04/2011
			 */

			void SaveFile();
			
            static std::string filePath;  ///< Full pathname of the file

		protected:

		private:	

			/**
			 * @brief	Loads the default.
			 *
			 * @author	Rafael.gasperi
			 * 		
			 * @date	28/04/2011
			 */

			void LoadDefault();

			std::auto_ptr<Smartmatic::Configuration::ConfigurationBase> cr;		///< The carriage return

			/**
			 * @brief	Default constructor.
			 *
			 * @author	Rafael.gasperi
			 * 		
			 * @date	28/04/2011
			 */

			ConfigurationPersistenceManager();

			static ConfigurationPersistenceManager * singleton_instance;	///< The singleton instance
            static Smartmatic::Log::ISMTTLog* logger; ///< The logger
		};
	}
}

#endif // _CONFIGURATION_PERSISTENCE_MANAGER_H_
