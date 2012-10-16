/*
 * QRVoteInvalidFormatException.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: fgomez
 */

#include "Exceptions/Voting/Vote/QRVoteInvalidFormatException.h"

#include <Log/ISMTTLog.h>


using namespace Smartmatic::System::Exception;

using namespace Smartmatic::SAES::Exceptions::Voting::Vote;


QRVoteInvalidFormatException::QRVoteInvalidFormatException(std::string message, std::string code,
        Smartmatic::Log::ISMTTLog* logger) : BaseException( message, code, logger)
{
	// TODO Auto-generated constructor stub

}

/*QRVoteInvalidFormatException::~QRVoteInvalidFormatException() {
	// TODO Auto-generated destructor stub
}*/

