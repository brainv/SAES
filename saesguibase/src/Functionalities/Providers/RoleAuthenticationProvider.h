/*
 * RoleAuthenticationProvider.h
 *
 *  Created on: Apr 26, 2011
 *      Author: ghernandez
 */

#include "Functionalities/FunctionalityAuthenticationProvider.h"

#ifndef ROLEAUTHENTICATIONPROVIDER_H_

/**
 * @brief	Gets the roleauthenticationprovider h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define ROLEAUTHENTICATIONPROVIDER_H_

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
					class RoleAuthenticationProvider : public Smartmatic::Functionality::FunctionalityAuthenticationProvider
					{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Luiggi.mendez
							 * @date	28/04/2011
							 */

							RoleAuthenticationProvider();

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Luiggi.mendez
							 * @date	28/04/2011
							 */

							virtual ~RoleAuthenticationProvider();

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

#endif /* ROLEAUTHENTICATIONPROVIDER_H_ */
