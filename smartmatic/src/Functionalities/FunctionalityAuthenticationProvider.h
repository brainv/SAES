/*
 * FunctionalityAuthenticationProvider.h
 *
 *  Created on: Apr 26, 2011
 *      Author: ghernandez
 */

#include <string>

#ifndef FUNCTIONALITYAUTHENTICATIONPROVIDER_H_
#define FUNCTIONALITYAUTHENTICATIONPROVIDER_H_


namespace Smartmatic
{
	namespace Functionality
	{
		/**
		 * @brief	Functionality authentication provider class. 
		 *
		 * @author	ghernandez
		 * @date	28/04/2011
		 */

		class FunctionalityAuthenticationProvider
		{
			public:

				FunctionalityAuthenticationProvider();
				virtual ~FunctionalityAuthenticationProvider();

				/**
				 * @brief	Authenticates.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	key	The key.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				virtual bool Authenticate(std::string key) = 0;
		};
	}
}

#endif /* FUNCTIONALITYAUTHENTICATIONPROVIDER_H_ */
