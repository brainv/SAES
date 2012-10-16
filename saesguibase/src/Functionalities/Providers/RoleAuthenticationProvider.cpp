/*
 * RoleAuthenticationProvider.cpp
 *
 *  Created on: Apr 26, 2011
 *      Author: ghernandez
 */

#include "RoleAuthenticationProvider.h"
#include "Operation/MachineOperationManager.hxx"

using namespace Smartmatic::SAES::GUI::Functionality::Providers;
using namespace Smartmatic::SAES::Operation;

RoleAuthenticationProvider::RoleAuthenticationProvider() {
	// TODO Auto-generated constructor stub

}

RoleAuthenticationProvider::~RoleAuthenticationProvider() {
	// TODO Auto-generated destructor stub
}

bool RoleAuthenticationProvider::Authenticate(std::string key)
{
	bool result = false;
	if(MachineOperationManager::getInstance()->getAuthenticator()->validate(key))
	{
		result = true;
	}
	else
		result = false;

	return result;
}
