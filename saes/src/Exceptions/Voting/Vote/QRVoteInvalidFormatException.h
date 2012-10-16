/*
 * QRVoteInvalidFormatException.h
 *
 *  Created on: Oct 28, 2011
 *      Author: fgomez
 */

#ifndef QRVOTEINVALIDFORMATEXCEPTION_H_
#define QRVOTEINVALIDFORMATEXCEPTION_H_

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


class QRVoteInvalidFormatException : public Smartmatic::System::Exception::BaseException
{
public:
	QRVoteInvalidFormatException(std::string message, std::string code,
			Smartmatic::Log::ISMTTLog* logger);
	//virtual ~QRVoteInvalidFormatException();
};
}
}
}
}
}

#endif /* QRVOTEINVALIDFORMATEXCEPTION_H_ */
