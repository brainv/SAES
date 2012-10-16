/*
 * AuditLogPrintDocument.h
 *
 *  Created on: May 4, 2011
 *      Author: root
 */

#ifndef AUDITLOGPRINTDOCUMENT_H_
#define AUDITLOGPRINTDOCUMENT_H_

#include <Voting/ElectoralConfiguration.hxx>
#include "Printing/LogPrintDocument.h"

namespace Smartmatic
{

namespace SAES
{

namespace Printing
{

class AuditLogPrintDocument : public LogPrintDocument
{
public:

	AuditLogPrintDocument(Smartmatic::SAES::Log::LogReader* reader,
			Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);
	virtual ~AuditLogPrintDocument();

protected:

	virtual std::string GetLogDocName ();

};

}

}

}

#endif /* AUDITLOGPRINTDOCUMENT_H_ */
