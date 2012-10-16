/**
 * @file	smartmatic-language-controller.h
 *
 * @brief	Header fie to the smartmatic language controller class.
 */

#ifndef _SMARTMATIC_LANGUAGE_CONTROLLER_H_
#define _SMARTMATIC_LANGUAGE_CONTROLLER_H_

#include "Environment/Configurations/base-language-controller.h"



namespace Smartmatic
{
	namespace Configuration
	{
		/**
		 * @brief	Smartmatic language controller class. 
		 *
		 * @author	Rafael.gasperi
		 * 			
		 * @date	28/04/2011
		 */

		class SmartmaticLanguageController: public Smartmatic::Environment::BaseLanguageController
		{
		public:

				/**
				 * @brief	Gets the package name.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 *
				 * @return	The package name.
				 */

				std::string getPackageName();

                /**
                 * @brief	Gets the locale dir.
                 *
                 * @author	Rafael.gasperi
                 * 			 
				 * @date	28/04/2011
                 *
                 * @return	The locale dir.
                 */

                std::string getLocaleDir();

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 */

				SmartmaticLanguageController();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * 			 
				 * @date	28/04/2011
				 */

				virtual ~SmartmaticLanguageController();
		protected:
				
		private:

		};
	}
}

#endif // _SMARTMATIC_LANGUAGE_CONTROLLER_H_
