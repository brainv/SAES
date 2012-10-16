/*
 * CodiRegisterBase.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#include "CodiRegisterBase.h"

using namespace Smartmatic::SAES::Voting::Codi;

CodiRegisterBase::CodiRegisterBase (
		  const std::string & contestCode
		, const std::string & customCode
		, const std::string & contestClassCode)
{
    contest_code = contestCode;
    setCustomCode(customCode);
    contest_class_code = contestClassCode;
}

CodiRegisterBase::~CodiRegisterBase()
{

}

std::string CodiRegisterBase::getContestClassCode() const
{
	return contest_class_code;
}

std::string CodiRegisterBase::getContestCode() const
{
	return contest_code;
}

void CodiRegisterBase::setContestClassCode(std::string contestClassCode)
{
	contest_class_code = contestClassCode;
}

void CodiRegisterBase::setContestCode(std::string contestCode)
{
	contest_code = contestCode;
}

void CodiRegisterBase::setCustomCode(std::string customCode)
{
	this->customCode = customCode;
}
std::string CodiRegisterBase::getCustomCode() const
{
	return customCode;
}
