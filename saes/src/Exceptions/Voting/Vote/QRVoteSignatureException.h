/*
 * QRVoteSignatureException.h
 *
 *  Created on: Oct 28, 2011
 *      Author: fgomez
 */

#ifndef QRVOTESIGNATUREEXCEPTION_H_
#define QRVOTESIGNATUREEXCEPTION_H_

#include <System/Exception/BaseException.hxx>

namespace Smartmatic
{

namespace SAES
{

namespace Exceptions
{

namespace Voting
{

namespace Vote
{


class QRVoteSignatureException : public Smartmatic::System::Exception::BaseException
{
public:
	QRVoteSignatureException(std::string message, std::string code,
			Smartmatic::Log::ISMTTLog* logger);
	//virtual ~QRVoteSignatureException();
};

}
}
}
}
}

#endif /* QRVoteSignatureException_H_ */
