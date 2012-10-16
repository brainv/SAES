/**
 * @file	base-language-controller.h
 *
 * @brief	Header file to the base language controller class.
 */

#ifndef _BASE_LANGUAGE_CONTROLLER_H_
#define _BASE_LANGUAGE_CONTROLLER_H_

#include "Configuration/smartmatic-conf-manager.h"
#include "System/IO/Directory.h"
#include "System/IO/Path.h"

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

    namespace Environment
	{
		/**
		 * @brief	Base language controller class. 
		 *
		 * @author	Rafael.gasperi
		 * 			 
		 * @date	28/04/2011
		 */

		class BaseLanguageController
		{
		public:

			/**
			 * @brief	Initializes the language.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 */

			void InitializeLanguage();

			/**
			 * @brief	Localize application Language.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 *
			 * @param	newLanguage	The new language to be set.
			 * @param	newCountry 	The new country to be set.
			 */

			static void LocalizeApplication(const char * newLanguage, const char * newCountry);

			/**
			 * @brief	Localize application Language.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 *
			 * @param [in,out]	newLanguage	The new language to be set.
			 * @param [in,out]	newCountry 	The new country to be set.
			 */

			static void LocalizeApplication(std::string& newLanguage, std::string& newCountry);

            /**
             * @brief   Full localize application Language.
             *
             * @author  Yadickson.soto
             *
             * @date    14/05/2011
             *
             * @param fullLanguage The new language to be set.
             */

            static void FullLocalizeApplication(std::string fullLanguage);

			/**
			 * @brief	Gets the actual application Language.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 *
			 * @param [in,out]	actualLanguage	 The actual language found .
			 * @param [in,out]	actualCountry 	The actual country found.
			 */

			static void GetActualLanguage(std::string& actualLanguage, std::string& actualCountry);

            /**
             * @brief   Gets the actual application Language.
             *
             * @author  Yadickson Soto yadickson.soto@gmail.com
             * @date    07/05/2011
             * @return  actual application Language in format ll_CC.
             */

			static std::string getActualLanguage();

			static bool setLanguage; ///< The flag set language

		protected:

				/**
				 * @brief	Default constructor.
				 *
			     * @author	Rafael.gasperi
			     * 			
				 * @date	28/04/2011
				 */

				BaseLanguageController();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 */

				~BaseLanguageController();

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
                 * @brief	Gets the locale dir.
                 *
                 * @author	Rafael.gasperi
                 * 			 
				 * @date	28/04/2011
                 *
                 * @return	The locale dir.
                 */

                virtual std::string getLocaleDir() = 0;
		private:

			
			static std::string actLanguage; ///< The act language
			static std::string actCountry; ///< The act country
			
			static Smartmatic::Log::ISMTTLog* logger; ///< The logger
		};
	}
}

#endif // _BASE_LANGUAGE_CONTROLLER_H_
