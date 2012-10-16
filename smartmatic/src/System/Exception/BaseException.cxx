/**
 * @file BaseException.cxx
 * @brief Body class base for exceptions
 * @date 24/02/2011
 * @author Yadickson Soto
 */

#include "BaseException.hxx"
#include <Log/ISMTTLog.h>

using namespace Smartmatic::System::Exception;

BaseException::BaseException( std::string message, std::string code, 
                             Smartmatic::Log::ISMTTLog* logger)
{
   if(logger!= NULL)
   		logger->Error(code);
	
   this->message = message;
	this->code = code;
}

BaseException::~BaseException() throw ()
{
}

std::string BaseException::getMessage() const
{
   return this->message;
}

std::string BaseException::getCode() const
{
   return this->code;
}

const char* BaseException::what() const throw()
{
   return this->message.c_str();
}
