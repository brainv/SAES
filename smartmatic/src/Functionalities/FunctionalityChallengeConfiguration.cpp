/*
 * FunctionalityChallengeConfiguration.cpp
 *
 *  Created on: Apr 25, 2011
 *      Author: ghernandez
 */

#include "FunctionalityChallengeConfiguration.h"

using namespace Smartmatic::Functionality;


FunctionalityChallengeConfiguration::FunctionalityChallengeConfiguration()
{

}


FunctionalityChallengeConfiguration::FunctionalityChallengeConfiguration(std::string titleArg, std::string passwordArg,
		std::string messageOKArg, std::string messageErrorArg)
{
	title = titleArg;
	password = passwordArg;
	messageOK = messageOKArg;
	messageError = messageErrorArg;
}


FunctionalityChallengeConfiguration::~FunctionalityChallengeConfiguration() {

}


std::string FunctionalityChallengeConfiguration::getTitle()
{
	return title;
}


std::string FunctionalityChallengeConfiguration::getPassword()
{
	return password;
}


std::string FunctionalityChallengeConfiguration::getMessageOK()
{
	return messageOK;
}


std::string FunctionalityChallengeConfiguration::getMessageError()
{
	return messageError;
}


void FunctionalityChallengeConfiguration::setTitle(std::string arg)
{
	title = arg;
}


void FunctionalityChallengeConfiguration::setPassword(std::string arg)
{
	password = arg;
}


void FunctionalityChallengeConfiguration::setMessageOK(std::string arg)
{
	messageOK = arg;
}


void FunctionalityChallengeConfiguration::setMessageError(std::string arg)
{
	messageError = arg;
}


void FunctionalityChallengeConfiguration::setDescriptionMessage(std::string arg)
{
	descriptionMessage = arg;
}


std::string FunctionalityChallengeConfiguration::getDescriptionMessage()
{
	return descriptionMessage;
}


FunctionalityAuthenticationProvider* FunctionalityChallengeConfiguration::getAuthenticationProvider()
{
	return authenticationProvider;
}


void FunctionalityChallengeConfiguration::setAuthenticationProvider(FunctionalityAuthenticationProvider* arg)
{
	authenticationProvider = arg;
}
