/**
 * @file LogInterface.cxx
 * @brief Body Log Interface
 * @date 8/07/2011
 * @author Yadickson Soto
 */

#include "LogInterface.hxx"

using namespace Smartmatic::Log;

LogInterface::LogInterface(std::string code)
{
	this->code = code;
}

std::string LogInterface::getCode()
{
	return this->code;
}
