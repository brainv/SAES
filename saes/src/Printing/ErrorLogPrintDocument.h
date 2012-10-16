/*
 * ErrorLogPrintDocument.h
 *
 *  Created on: May 4, 2011
 *      Author: root
 */

#ifndef ERRORLOGPRINTDOCUMENT_H_
#define ERRORLOGPRINTDOCUMENT_H_

#include "Printing/LogPrintDocument.h"

namespace Smartmatic
{

namespace SAES
{

namespace Printing
{

class ErrorLogPrintDocument : public LogPrintDocument
{
public:

	ErrorLogPrintDocument(Smartmatic::SAES::Log::LogReader* reader,
			Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

	virtual ~ErrorLogPrintDocument();

protected:

	virtual std::string GetLogDocName ();

};

}

}

}

#endif /* ERRORLOGPRINTDOCUMENT_H_ */
