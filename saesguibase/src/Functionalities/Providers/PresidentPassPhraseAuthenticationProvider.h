/*
 * PresidentPassPhraseAuthenticationProvider.h
 *
 *  Created on: Apr 26, 2011
 *      Author: ghernandez
 */

#include "Functionalities/FunctionalityAuthenticationProvider.h"

#ifndef PRESIDENTPASSPHRASEAUTHENTICATIONPROVIDER_H_

/**
 * @brief	Gets the presidentpassphraseauthenticationprovider h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define PRESIDENTPASSPHRASEAUTHENTICATIONPROVIDER_H_

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				namespace Providers
				{
					class PresidentPassPhraseAuthenticationProvider : public Smartmatic::Functionality::FunctionalityAuthenticationProvider
					{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Luiggi.mendez
							 * @date	28/04/2011
							 */

							PresidentPassPhraseAuthenticationProvider();

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Luiggi.mendez
							 * @date	28/04/2011
							 */

							virtual ~PresidentPassPhraseAuthenticationProvider();

							 /**
							  * @brief	Authenticates.
							  *
							  * @author	Luiggi.mendez
							  * @date	28/04/2011
							  *
							  * @param	key	The key.
							  *
							  * @return	true if it succeeds, false if it fails.
							  */

							 bool Authenticate(std::string key);
					};
				}
			}
		}
	}
}

#endif /* PRESIDENTPASSPHRASEAUTHENTICATIONPROVIDER_H_ */
