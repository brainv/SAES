/**
 * @file	smartmatic-conf-manager.h
 *
 * @brief	Declares the smartmatic conf manager class.
 */

#ifndef _SMARTMATIC_CONFIGURATION_MANAGER_H_
#define _SMARTMATIC_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SmartmaticConfiguration-schema.hxx>
#include <Configuration/ConfigurationBase-schema.hxx>
#include <Configuration/configuration-persistence-manager.h>
#include <System/Sounds/beep-descriptor.h>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

    namespace Configuration
	{
		/**
		 * @brief	Manager for smartmatic configurations class. 
		 *
		 * @author	Rafael.gasperi
		 * 		
		 * @date	28/04/2011
		 */

		class SmartmaticConfigurationManager
		{
		public:

				/**
				 * @brief	Gets the current Smartmatic Configuration Manager.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static SmartmaticConfigurationManager *Current();

				/**
				 * @brief	Gets the configuration.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else the configuration.
				 */

				std::auto_ptr<Smartmatic::Configuration::SmartmaticConfiguration>* getConfiguration();

				/**
				 * @brief	Loads the default.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 */

				void LoadDefault();

				/**
				 * @brief	Gets the list of resources paths.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 *
				 * @return	The list of resources paths.
				 */

				std::vector<std::string> getListOfResourcesPaths();

				/**
				 * @brief	Gets the image storage in memory.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getImageStorageInMemory();

				/**
				 * @brief	Gets a sound configuration.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 *
				 * @param	sound	The sound.
				 *
				 * @return	The sound configuration.
				 */

				std::vector<Smartmatic::System::Sounds::BeepDescriptor> GetSoundConfiguration(std::string sound);

				/**
				 * @brief method getter is use beep
				 * @return true is use beep
				 * @date 19/07/2012
				 * @author Yadickson Soto
				 */
				bool isUseBeep();

				/**
				 * @brief method getter app sound
				 * @return app sound
				 * @date 19/07/2012
				 * @author Yadickson Soto
				 */
				std::string getAppSound();

				/**
				 * @brief method getter sound file
				 * @param sound
				 * @return sound file
				 * @date 19/07/2012
				 * @author Yadickson Soto
				 */
				std::string getSoundFile(std::string sound);

		protected:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 */

				SmartmaticConfigurationManager();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * 		
				 * @date	28/04/2011
				 */

				~SmartmaticConfigurationManager();

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Rafael.gasperi
				 * 		
				 * @date	28/04/2011
				 */

				void Initialize();

				
				static SmartmaticConfigurationManager * singleton_instance; ///< The singleton instance
		private:

				
				std::auto_ptr<Smartmatic::Configuration::SmartmaticConfiguration> *configuration; ///< The configuration

				
				static Smartmatic::Log::ISMTTLog* logger;  ///< The logger
		};
	}

}

#endif // _S_A_E_S_HARDWARE_CONFIGURATION_MANAGER_H_
