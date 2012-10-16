/*
 * QRVoteSignatureException.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: fgomez
 */

#include "Exceptions/Voting/Vote/QRVoteSignatureException.h"

#include <Log/ISMTTLog.h>


using namespace Smartmatic::SAES::Exceptions::Voting::Vote;

QRVoteSignatureException::QRVoteSignatureException(std::string message, std::string code,
                        Smartmatic::Log::ISMTTLog* logger): BaseException( message, code, logger) {
	// TODO Auto-generated constructor stub

}

/*QRVoteSignatureException::~QRVoteSignatureException() {
	// TODO Auto-generated destructor stub
}*/

