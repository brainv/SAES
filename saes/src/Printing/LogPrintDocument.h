/*
 * LogPrintDocument.h
 *
 *  Created on: May 4, 2011
 *      Author: root
 */

#ifndef LOGPRINTDOCUMENT_H_
#define LOGPRINTDOCUMENT_H_

#include <gtkmm.h>
#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Printing/BasePrintDocument.h>
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Log/LogReader.h>
#include <Log/LogLine.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{

namespace SAES
{

namespace Printing
{

class LogPrintDocument : public BasePrintDocument
{
public:

	LogPrintDocument ();

	LogPrintDocument(Smartmatic::SAES::Log::LogReader* reader, Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

	virtual ~LogPrintDocument();

protected:

	virtual std::string GetLogDocName () = 0;

	virtual void PrintDoc();

	virtual void BeginPrint();

	virtual void EndPrint();

private:

	std::vector<Smartmatic::SAES::Log::LogLine> m_Entries;
	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
	Smartmatic::SAES::Voting::ElectoralConfiguration * _electoralConfiguration;

	void AddHeaderTextBlock (
			  const std::string& text
			, const Smartmatic::SAES::Configuration::TextConfiguration& textConf);
};

}

}

}

#endif /* LOGPRINTDOCUMENT_H_ */
