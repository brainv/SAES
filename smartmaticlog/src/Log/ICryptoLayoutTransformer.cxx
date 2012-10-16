/**
 * @file  ICryptoLayoutTransformer.cxx
 * @brief	Body ICryptoLayoutTransformer class.
 *
 * @author	Yadickson Soto
 * @date	15-07-2011
 *
 */

#include "ICryptoLayoutTransformer.hxx"
#include <log4cxx/helpers/synchronized.h>

using namespace Smartmatic::Log;
using namespace log4cxx::helpers;

ICryptoLayoutTransformer::ICryptoLayoutTransformer(std::string code)
	: LogInterface(code),
	  pool(),
	  mutex(pool)
{
	synchronized sync(mutex);
}

ICryptoLayoutTransformer::~ICryptoLayoutTransformer()
{

}

log4cxx::helpers::Mutex & ICryptoLayoutTransformer::getMutex()
{
	return mutex;
}
