/*
 * FunctionalityChallengeConfiguration.h
 *
 *  Created on: Apr 25, 2011
 *      Author: ghernandez
 */

#include <string>
#include "FunctionalityAuthenticationProvider.h"

#ifndef FUNCTIONALITYCHALLENGECONFIGURATION_H_
#define FUNCTIONALITYCHALLENGECONFIGURATION_H_

namespace Smartmatic
{
	namespace Functionality
	{
		/**
		 * @brief	Functionality challenge configuration class. 
		 *
		 * @author	ghernandez
		 * @date	28/04/2011
		 */

		class FunctionalityChallengeConfiguration
		{
			public:

			/**
			 * @brief	Default constructor.
			 *
			 * @author	ghernandez
			 * @date	28/04/2011
			 */

			FunctionalityChallengeConfiguration();

				/**
				 * @brief	Constructor.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	titleArg	   	The title argument.
				 * @param	passwordArg	   	The password argument.
				 * @param	messageOKArg   	The message ok argument.
				 * @param	messageErrorArg	The message error argument.
				 */

				FunctionalityChallengeConfiguration(std::string titleArg, std::string passwordArg, std::string messageOKArg, std::string messageErrorArg);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 */

				virtual ~FunctionalityChallengeConfiguration();

				/**
				 * @brief	Gets the title.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	The title.
				 */

				std::string getTitle();

				/**
				 * @brief	Gets the password.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	The password.
				 */

				std::string getPassword();

				/**
				 * @brief	Gets the message ok.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	The message ok.
				 */

				std::string getMessageOK();

				/**
				 * @brief	Gets the error message.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	The message error.
				 */

				std::string getMessageError();

				/**
				* @brief	Gets the description message.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	The description message.
				 */

				std::string getDescriptionMessage();

				/**
				 * @brief	Sets a title.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	arg	The argument title.
				 */

				void setTitle(std::string arg);

				/**
				 * @brief	Sets a password.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	arg	The argument password.
				 */

				void setPassword(std::string arg);

				/**
				 * @brief	Sets a ok message.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	arg	The argument ok message.
				 */

				void setMessageOK(std::string arg);

				/**
				 * @brief	Sets a error message.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	arg	The argument error message.
				 */

				void setMessageError(std::string arg);

				/**
				 * @brief	Sets a description message.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param	arg	The argument description message.
				 */

				void setDescriptionMessage(std::string arg);

				/**
				 * @brief	Gets the authentication provider.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else the authentication provider.
				 */

				FunctionalityAuthenticationProvider* getAuthenticationProvider();

				/**
				 * @brief	Sets an authentication provider.
				 *
				 * @author	ghernandez
				 * @date	28/04/2011
				 *
				 * @param [in,out]	arg	If non-null, the argument.
				 */

				void setAuthenticationProvider(FunctionalityAuthenticationProvider* arg);
			private:

				
				std::string title; ///< The title

				
				std::string password; ///< The password

				
				std::string messageOK; ///< The ok message 

				
				std::string messageError; ///< The  error message 

				
				std::string descriptionMessage; ///< Message describing the description

				
				FunctionalityAuthenticationProvider* authenticationProvider; ///< The authentication provider
		};
	}
}

#endif /* FUNCTIONALITYCHALLENGECONFIGURATION_H_ */
