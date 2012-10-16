/**
 * @file LogPrintDocument.cpp
 * @brief Body class log print document
 * @date 04/05/2011
 * @author Rafael Ferrero
 */

#include <iostream>
#include "Printing/DocumentOptions.h"
#include <Environment/Configurations/resource-path-provider.h>
#include "Printing/TranslatorTextConfiguration.h"
#include "LogPrintDocument.h"
#include <Log/SMTTLogManager.h>
#include "Resources/election-string-resources-manager.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace std;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting::VotingDevice;

ISMTTLog* LogPrintDocument::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.LogPrintDocument",GETTEXT_PACKAGE);

//============================= LIFE CYCLE ===================================//

LogPrintDocument::LogPrintDocument()
: BasePrintDocument ()
{
	// TODO Auto-generated constructor stub
}

LogPrintDocument::LogPrintDocument (LogReader* reader, Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
: BasePrintDocument ()
{
	_electoralConfiguration = electoralConfiguration;

    if (reader != NULL)
	{
        m_Entries = reader->getLogLines ();
	}
}

LogPrintDocument::~LogPrintDocument()
{
	m_Entries.clear();
}


//=============== BASEPRINTDOCUMENT INTERFACE IMPLEMENTATION =================//

void LogPrintDocument::PrintDoc()
{
	LogPrintDocumentConfiguration doc_conf =
		(*SAESConfigurationManager::Current ()->
			getConfiguration ())->
			getConfigurationPrinter ().getLogPrintDocConfiguration ();

	DocumentTextOptions log_entry_options = TranslatorTextConfiguration
			::TextConfigurationToDocumentTextOptions(doc_conf.getTextLogEntry());

	Glib::RefPtr<Gdk::Pixbuf> pixBuf = Gdk::Pixbuf::create_from_file (ResourcePathProvider::Current()->
			GetResourcePath(PACKAGE_NAME,"ui/LogPrintDocumentHeader.img"));

	this->DrawImage(pixBuf, Left, InLineWithText, Border_Right, 10, 20, 10, 10);

	this->DrawLine (550.0, Center);

	NewTextBlock  (log_entry_options);
	this->NewLine ();
	this->NewLine ();

	Voting_device device;
	Voting_booth votingBooth;


	device = _electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
	votingBooth = (device.getVoting_booths().getVoting_booth())[0];


	Smartmatic::SAES::Voting::Election::Election election = _electoralConfiguration->getElection()->getElection();
	std::string electionName = ElectionStringResourcesManager::Current()->getResource(election.getName_key());
	std::string pollingPlaceName = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_name ());
	std::string pollingPlaceAdress = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_address());
	std::string electoralOrganization = ElectionStringResourcesManager::Current()->getResource(election.getElectoral_organization());
	std::string deviceCode = ElectionStringResourcesManager::Current()->getResource(device.getCustom_code());


	std::string electionNameValue = Glib::ustring::compose(_("Smartmatic.SAES.Printing.LogPrintDocument.ElectionName"),
			electionName, pollingPlaceName, pollingPlaceAdress, electoralOrganization, deviceCode);

	std::string electoralOrganizationValue = Glib::ustring::compose(_("Smartmatic.SAES.Printing.LogPrintDocument.ElectoralOrganization"),
			electionName, pollingPlaceName, pollingPlaceAdress, electoralOrganization, deviceCode);

	std::string deviceCodeValue = Glib::ustring::compose(_("Smartmatic.SAES.Printing.LogPrintDocument.DeviceCode"),
			electionName, pollingPlaceName, pollingPlaceAdress, electoralOrganization, deviceCode);

	std::string pollingPlaceValue = Glib::ustring::compose(_("Smartmatic.SAES.Printing.LogPrintDocument.PollingPlace"),
			electionName, pollingPlaceName, pollingPlaceAdress, electoralOrganization, deviceCode);

	std::string pollingPlaceAddresssValue = Glib::ustring::compose(_("Smartmatic.SAES.Printing.LogPrintDocument.PollingPlaceAddresss"),
			electionName, pollingPlaceName, pollingPlaceAdress, electoralOrganization, deviceCode);


	AddHeaderTextBlock (GetLogDocName (), doc_conf.getTextLogTitleLevel1());
	AddHeaderTextBlock (electionNameValue, doc_conf.getTextLogTitleLevel2());
	AddHeaderTextBlock (electoralOrganizationValue, doc_conf.getTextLogTitleLevel2());
	AddHeaderTextBlock (deviceCodeValue, doc_conf.getTextLogTitleLevel3());
	AddHeaderTextBlock (pollingPlaceValue, doc_conf.getTextLogTitleLevel4());
	AddHeaderTextBlock (pollingPlaceAddresssValue, doc_conf.getTextLogTitleLevel5());

	this->AddBreak ();

	this->DrawLine (550.0, Center);

	NewTextBlock (log_entry_options);
	this->NewLine ();

	NewTextBlock (log_entry_options);

	/*if (doc_conf.getColumnLayout() == DocumentColumnLayout::CONFIGURATION_DOUBLECOLUMN)
		this->SetDoubleColumnLayout ();
	else
		this->SetSingleColumnLayout ();*/

    for (size_t i=0; i<m_Entries.size (); i++)
	{
		Glib::ustring text_line;

		text_line = Glib::ustring::compose ("%1 - %2", m_Entries[i].getDate (), m_Entries[i].getMessage ());
		//text_line = Glib::ustring::compose (_("Smartmatic.SAES.Printing.LogPrintDocument.LogEntryFormat"), m_Entries[i].getDate (), m_Entries[i].getMessage ());

		this->DrawString (text_line, false);
	}

	this->AddBreak ();
}

void LogPrintDocument::AddHeaderTextBlock (const std::string& text, const TextConfiguration& textConf)
{
	if (textConf.getVisible ())
	{
		DocumentTextOptions  options =
				TranslatorTextConfiguration
				::TextConfigurationToDocumentTextOptions(textConf);

		this->NewTextBlock (options);
		this->DrawString (text, false);
	}
}

void LogPrintDocument::BeginPrint()
{

}

void LogPrintDocument::EndPrint()
{

}
