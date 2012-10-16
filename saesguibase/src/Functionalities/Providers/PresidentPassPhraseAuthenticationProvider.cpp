/*
 * PresidentPassPhraseAuthenticationProvider.cpp
 *
 *  Created on: Apr 26, 2011
 *      Author: ghernandez
 */

#include "PresidentPassPhraseAuthenticationProvider.h"
#include "Security/Encryption.hxx"

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::GUI::Functionality::Providers;

PresidentPassPhraseAuthenticationProvider::PresidentPassPhraseAuthenticationProvider() {
	// TODO Auto-generated constructor stub

}

PresidentPassPhraseAuthenticationProvider::~PresidentPassPhraseAuthenticationProvider() {
	// TODO Auto-generated destructor stub
}

bool PresidentPassPhraseAuthenticationProvider::Authenticate(std::string key)
{
	bool result = false;

	if(Encryption::getInstance()->getSecretKey().getPlainPassphrase() == key)
		result = true;

	return result;
}
