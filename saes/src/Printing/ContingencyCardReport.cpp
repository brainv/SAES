/**
 * @file ContingencyCardReport.cpp
 * @brief Body class contingency card report printing
 * @date 19/10/2011
 * @author Marcel Cordovi
 */

#include <Environment/Configurations/resource-path-provider.h>
#include <vector>
#include <list>
#include "Printing/TranslatorTextConfiguration.h"
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include "Resources/election-string-resources-manager.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Log/LogReader.h>
#include "ContingencyCardReport.h"

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

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* ContingencyCardReport::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.ContingencyCardReport",GETTEXT_PACKAGE);

//=============================================================================
//============================== Life Cycle ===================================
//=============================================================================

ContingencyCardReport::ContingencyCardReport(const std::string& pin, ElectoralConfiguration* conf)
{
	m_Pin = pin;
	m_ElectoralConf = conf;
}

ContingencyCardReport::~ContingencyCardReport()
{
	// TODO Auto-generated destructor stub
}


//=============================================================================
//========================= Base Implementation ===============================
//=============================================================================

void ContingencyCardReport::PrintDoc()
{
	ConfigurationContingency configurationContingency = (*SAESConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getConfigurationContingency();

	DocumentTextOptions textInstallationTitleLevel1 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationContingency.getTextContingencyTitleLevel1());
	DocumentTextOptions textInstallationTitleLevel2 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationContingency.getTextContingencyTitleLevel2());
	DocumentTextOptions textInstallationTitleLevel3 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationContingency.getTextContingencyTitleLevel3());
	DocumentTextOptions textInstallationInfo = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationContingency.getTextContingencyInfo());

	PrintHeader (
			  textInstallationTitleLevel1
			, textInstallationTitleLevel2
			, textInstallationTitleLevel3
			, textInstallationInfo);

	PrintCardInfoSection (
			  textInstallationTitleLevel1
			, textInstallationTitleLevel2
			, textInstallationTitleLevel3
			, textInstallationInfo);

	if ( configurationContingency.getIncludeRegionSection() )
	{
		PrintRegionInfo (
				textInstallationTitleLevel1
				, textInstallationTitleLevel2
				, textInstallationTitleLevel3
				, textInstallationInfo);
	}

	logger->Audit(N_("Smartmatic.SAES.Printing.ContingencyCardReport.PrintContingencyReport"));
}

void ContingencyCardReport::BeginPrint()
{

}

void ContingencyCardReport::EndPrint()
{

}


//=============================================================================
//================================ Auxiliar ===================================
//=============================================================================


void ContingencyCardReport::PrintCardInfoSection (
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{
	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	if ((*SAESConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getConfigurationContingency().getIncludeHelp())
	{
		this->NewTextBlock(textInstallationTitleLevel2);
		this->DrawString(_("Smartmatic.SAES.Printing.ContingencyCardReport.ContingencyHelpTitle"),true);

		this->NewTextBlock(textInstallationInfo);
		this->DrawString(" ",true);
		this->DrawString(_("Smartmatic.SAES.Printing.ContingencyCardReport.ContingencyHelpText"),true);
		this->DrawString(" ",true);
		this->DrawString(" ",true);
	}

	NewTextBlock(textInstallationTitleLevel2);
	this->Indent(2);
	Glib::ustring strDeviceStatus = _("Smartmatic.SAES.Printing.ContingencyCardReport.ContingencyCardInfoTitle");
	this->DrawString(strDeviceStatus,true);
	this->DrawString(" ",true);
	this->UnIndent(2);

	this->NewTextColunmsBlock(listDocumentTextOptions);
	this->Indent(4);

	this->DrawString(_("Smartmatic.SAES.Printing.ContingencyCardReport.ContingencyCardPinTitle"),false);
	this->DrawString(m_Pin,false);

	this->UnIndent(4);

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",true);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);
}

void ContingencyCardReport::PrintHeader(
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{

	Voting_booth votingBooth;

	if(m_ElectoralConf != NULL)
		votingBooth = (m_ElectoralConf->getVotingDevice()->
				getFirstVotingDevice().getVoting_booths().getVoting_booth())[0];

	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	Glib::RefPtr<Gdk::Pixbuf> pixBuff  = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/ContingencyReportHeader.img"));
	this->DrawImage(pixBuff, Left, InLineWithText, Border_Right, 10, 20, 10, 10);

	NewTextBlock(textInstallationTitleLevel1);

	this->DrawString(" ",false);
	this->Indent(4);
	this->DrawString(_("Smartmatic.SAES.Printing.ContingencyCardReport.InstallationReportTitle"),false);
	this->UnIndent(4);

	this->DrawString(" ",false);
	if(m_ElectoralConf != NULL)
	{
		// Election Name
		Smartmatic::SAES::Voting::Election::Election election =
				m_ElectoralConf->getElection()->getElection();

		Glib::ustring strElectionName =
				ElectionStringResourcesManager::Current()->
				getResource(election.getName_key());

		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		this->DrawString(strElectionName,false);
		this->UnIndent(6);

		// Voting booths
		Glib::ustring strVotingBooth = ElectionStringResourcesManager::Current()->getResource(votingBooth.getCustom_code());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strTitle = _("Smartmatic.SAES.Printing.ContingencyCardReport.VotingBoothTitle");

		this->DrawString((Glib::ustring::compose(strTitle,strVotingBooth)),false);
		this->UnIndent(6);

		Glib::ustring votingCenterValue = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_name ());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strVotingCenter = _("Smartmatic.SAES.Printing.ContingencyCardReport.VotingCenter");
		Glib::ustring composedVotingCenter = (Glib::ustring::compose(strVotingCenter,votingCenterValue));
		this->DrawString(composedVotingCenter,false);
		this->UnIndent(6);

		Glib::ustring votingCenterAddress = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_address ());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strVotingCenterAddress = _("Smartmatic.SAES.Printing.ContingencyCardReport.VotingCenterAddress");
		Glib::ustring composedVotingCenterAddress = (Glib::ustring::compose(strVotingCenterAddress,votingCenterAddress));
		this->DrawString(composedVotingCenterAddress,false);
		this->UnIndent(6);
	}
//	else
//	{
//		std::string line = _("Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine1");
//		this->NewTextBlock(textInstallationTitleLevel2);
//		this->Indent(6);
//		if(line.size() > 0 &&  line != "Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine1")
//		{
//			this->DrawString(line,false);
//		}
//
//		line = _("Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine2");
//		if(line.size() > 0 &&  line != "Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine2")
//		{
//			this->DrawString(line,false);
//		}
//
//		line = _("Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine3");
//		if(line.size() > 0 &&  line != "Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine3")
//		{
//			this->DrawString(line,false);
//		}
//		line = _("Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine4");
//		if(line.size() > 0 &&  line != "Smartmatic.SAES.Printing.ContingencyCardReport.DiagnosticAppReportDescLine4")
//		{
//			this->DrawString(line,false);
//		}
//		this->UnIndent(6);
//	}

	this->AddBreak ();

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);
}

void ContingencyCardReport::PrintRegionInfo (
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{
	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	Voting_device device = m_ElectoralConf->getVotingDevice ()->getFirstVotingDevice ();
	Voting_booth votingBooth = (device.getVoting_booths().getVoting_booth())[0];


	NewTextBlock(textInstallationTitleLevel2);
	this->Indent(2);
	Glib::ustring strRegion = _("Smartmatic.SAES.Printing.ContingencyCardReport.RegionTitle");
	this->DrawString(strRegion,true);
	this->DrawString(" ",true);
	this->UnIndent(2);

	this->NewTextColunmsBlock(listDocumentTextOptions);
	this->Indent(4);

	std::vector<Glib::ustring> vRegions = GetRegionsStrings(votingBooth);

	std::list<Glib::ustring> composedRegions;
	if(vRegions.size() == 8)
	{
		Glib::ustring messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region1");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region2");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region3");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region4");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region5");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region6");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region7");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.ContingencyCardReport.Region8");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}
	}

	this->DrawStrings(composedRegions);
	this->UnIndent(4);
	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",true);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);
}

std::vector<Glib::ustring> ContingencyCardReport::GetRegionsStrings(
		const Voting_booth & votingBooth)
{
    std::list <Region_category> & listCategoryRegion (m_ElectoralConf->getRegionCategoryList());
    std::list <Region_category>::reverse_iterator it;
	std::list <Region_category> regionCategorytoShow;

	// get the last regionCategories
	const int maxRegions = 4;
	int aux =0;

	for ( it = listCategoryRegion.rbegin() ; it != listCategoryRegion.rend(); ++it )
	{
		regionCategorytoShow.push_back(*it);
		aux++;
		if(aux == maxRegions)
			break;
	}

	std::vector<Glib::ustring> vectorRegions;

	// get strings to show
	for(it = regionCategorytoShow.rbegin(); it != regionCategorytoShow.rend(); ++it)
	{
		vectorRegions.push_back(ElectionStringResourcesManager::Current()->getResource((*it).getName_key()));
		vectorRegions.push_back(ElectionStringResourcesManager::Current()->getResource((*it).getRegion().getName_key()));
	}

	int size = regionCategorytoShow.size();
	if(size < maxRegions)
	{
		for(int i=0;i<(maxRegions-size);i++)
		{
			vectorRegions.push_back("");
			vectorRegions.push_back("");
		}
	}

	return vectorRegions;
}
