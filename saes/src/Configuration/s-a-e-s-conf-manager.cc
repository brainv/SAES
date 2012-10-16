/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "s-a-e-s-conf-manager.h"
#include <Configuration/configuration-persistence-manager.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>

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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

#define LOGGER_PROJECT "Smartmatic.Configuration.SAESConfigurationManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* SAESConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* SAESConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

SAESConfigurationManager::SAESConfigurationManager()
{
	configuration = NULL;
	Initialize();
}

auto_ptr<SaesConfiguration>* SAESConfigurationManager::getConfiguration()
{
	return configuration;
}

void SAESConfigurationManager::Initialize()
{
	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SAES"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SaesConfiguration>(parseSaesConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
		}
		else
		{
			LoadDefault();
			Initialize();
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAES Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAES Error", "Error");
		exit (0);
	}
}

unsigned int SAESConfigurationManager::getCardValidity()
{
	return (*configuration)->getConfigurationCard().getTimeOfValidity();
}

bool SAESConfigurationManager::getAllowRecoveryCardGenerationOfConsolidatedVotes()
{
	return (*configuration)->getConfigurationCard().getAllowRecoveryCardGenerationOfConsolidatedVotes();
}

bool SAESConfigurationManager::getSaveDemoVotesInTransmissionPackage()
{
	return (*configuration)->getTransmissionPackageConfiguration().getSaveDemoVotesInTransmissionPackage();
}

CodiFileConfiguration & SAESConfigurationManager::getCodiFileConfiguration()
{
	return (*configuration)->getCodiFileConfiguration();
}

SAESConfigurationManager::~SAESConfigurationManager()
{
	if(configuration!= NULL)
	{
		delete(configuration);
	}
}

ConfigurationVote& SAESConfigurationManager::getPrintVoteConfiguration()
{
	 return ((*configuration)->getConfigurationPrinter().getConfigurationVote());
}

ConfigurationVote& SAESConfigurationManager::getPrintScreenVoteConfiguration()
{
	 return ((*configuration)->getConfigurationScreenPreview().getConfigurationVote());
}

void SAESConfigurationManager::LoadDefault()
{
	SaesConfiguration *configSAES = new SaesConfiguration();

	ConfigurationReportPrinting report_conf;
	ConfigurationReportFile file_conf1;

	file_conf1.setFileDescription(N_("Smartmatic.SAES.Printing.ClosedPrintDocument.PVDescription"));
	file_conf1.setFileName("pv-report.pdf");
	file_conf1.setReportTitle (N_("Smartmatic.SAES.Printing.ClosedPrintDocument.PVTitle"));
	file_conf1.setNumCopies (1);

	/*ConfigurationReportFile file_conf2;
	file_conf2.setFileDescription("test file 2");
	file_conf2.setFileName("file2.pdf");
	file_conf2.setReportTitle ("file2_title");
	file_conf2.setNumCopies (3);*/

	ConfigurationReportPrinting::ReportFilesSequence rceq;
	rceq.push_back(file_conf1);
	//rceq.push_back(file_conf2);

	report_conf.setReportFiles(rceq);


	ConfigurationPrinter *configurationPrinter = new ConfigurationPrinter();
	ConfigurationScreenPreview *configurationScreenPreview = new ConfigurationScreenPreview();
	ConfigurationCard *configurationCard = new ConfigurationCard();
	ConfigurationVote *configurationVote = new ConfigurationVote();
	ConfigurationTimeout *configurationTimeout = new ConfigurationTimeout();
	ConfigurationSmartcardRemoved *configurationSmartcardRemoved = new ConfigurationSmartcardRemoved();
	ConfigurationInstallation *configurationInstallation = new ConfigurationInstallation();
	ConfigurationContingency* configurationContingency = new ConfigurationContingency ();
	LogPrintDocumentConfiguration *logPrintDocConf = new LogPrintDocumentConfiguration ();
	
	TextConfiguration *textHeader1   = new TextConfiguration();
	TextConfiguration *textHeader2   = new TextConfiguration();
	TextConfiguration *textHeader3   = new TextConfiguration();
	TextConfiguration *textHeader4	 = new TextConfiguration();
	TextConfiguration *textHeader5	 = new TextConfiguration();
	TextConfiguration *textHeader6	 = new TextConfiguration();
	TextConfiguration *textHeader7	 = new TextConfiguration();
	TextConfiguration *textHeaderCustomAtt = new TextConfiguration();
	
	
	TextConfiguration *textBallotName	 = new TextConfiguration();
	TextConfiguration *textRegionName	 = new TextConfiguration();
	TextConfiguration *textContestName1  = new TextConfiguration();
	TextConfiguration *textContestName2  = new TextConfiguration();
	TextConfiguration *textContestName3  = new TextConfiguration();
	TextConfiguration *textParentOptionSelected  = new TextConfiguration();
	TextConfiguration *textPrincipalsMessage  = new TextConfiguration();
	TextConfiguration *textStandInMessage  = new TextConfiguration();
	TextConfiguration *textBallotOption = new TextConfiguration();
	TextConfiguration *textGeneric		= new TextConfiguration();
	TextConfiguration *textBlankVote	= new TextConfiguration();

	TextConfiguration *textTitleTimeout			 = new TextConfiguration();
	TextConfiguration *textElectionNameTimeout   = new TextConfiguration();
	TextConfiguration *textVotingBoothTimeout    = new TextConfiguration();
	TextConfiguration *textVoteIDTimeout		 = new TextConfiguration();
	TextConfiguration *textDescriptionTimeout	 = new TextConfiguration();

	TextConfiguration *textTitleSmartcardRemoved		  = new TextConfiguration();
	TextConfiguration *textElectionNameSmartcardRemoved   = new TextConfiguration();
	TextConfiguration *textVotingBoothSmartcardRemoved    = new TextConfiguration();
	TextConfiguration *textVoteIDSmartcardRemoved		  = new TextConfiguration();
	TextConfiguration *textDescriptionSmartcardRemoved	  = new TextConfiguration();

	TextConfiguration *textInstallationTitleLevel1	=  new TextConfiguration();
	TextConfiguration *textInstallationTitleLevel2  =  new TextConfiguration();
	TextConfiguration *textInstallationTitleLevel3	=  new TextConfiguration();
	TextConfiguration *textInstallationInfo			=  new TextConfiguration();

	TextConfiguration *textContingencyTitleLevel1	=  new TextConfiguration();
	TextConfiguration *textContingencyTitleLevel2   =  new TextConfiguration();
	TextConfiguration *textContingencyTitleLevel3	=  new TextConfiguration();
	TextConfiguration *textContingencyInfo			=  new TextConfiguration();


	TextConfiguration *textLogTitleLevel1	=  new TextConfiguration();
	TextConfiguration *textLogTitleLevel2   =  new TextConfiguration();
	TextConfiguration *textLogTitleLevel3	=  new TextConfiguration();
	TextConfiguration *textLogTitleLevel4	=  new TextConfiguration();
	TextConfiguration *textLogTitleLevel5	=  new TextConfiguration();
	TextConfiguration *textLogEntry			=  new TextConfiguration();

	LayoutContestConfiguration layoutContestConfiguration;;
		
	try
	{
		stringstream ss;
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");

				textHeader1->setSize(12);
				textHeader1->setFontFamily("FreeSans");
				textHeader1->setBold(false);
				textHeader1->setItalic(false);
				textHeader1->setHPandding(0);
				textHeader1->setVPandding(1);
				textHeader1->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader1->setLevelPaddingSpaceChar(0);
				textHeader1->setVisible(true);

				textHeader2->setSize(8);
				textHeader2->setFontFamily("FreeSans");
				textHeader2->setBold(true);
				textHeader2->setItalic(true);
				textHeader2->setHPandding(0);
				textHeader2->setVPandding(1);
				textHeader2->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader2->setLevelPaddingSpaceChar(0);
				textHeader2->setVisible(true);

				textHeader3->setSize(9);
				textHeader3->setFontFamily("FreeSans");
				textHeader3->setBold(false);
				textHeader3->setItalic(false);
				textHeader3->setHPandding(0);
				textHeader3->setVPandding(0);
				textHeader3->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader3->setLevelPaddingSpaceChar(0);
				textHeader3->setVisible(true);

				textHeader4->setSize(9);
				textHeader4->setFontFamily("FreeSans");
				textHeader4->setBold(false);
				textHeader4->setItalic(false);
				textHeader4->setHPandding(0);
				textHeader4->setVPandding(1);
				textHeader4->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader4->setLevelPaddingSpaceChar(0);
				textHeader4->setVisible(true);

				
				textHeader5->setSize(9);
				textHeader5->setFontFamily("FreeSans");
				textHeader5->setBold(false);
				textHeader5->setItalic(false);
				textHeader5->setHPandding(0);
				textHeader5->setVPandding(1);
				textHeader5->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader5->setLevelPaddingSpaceChar(0);
				textHeader5->setVisible(true);

				textHeader6->setSize(9);
				textHeader6->setFontFamily("FreeSans");
				textHeader6->setBold(false);
				textHeader6->setItalic(false);
				textHeader6->setHPandding(0);
				textHeader6->setVPandding(1);
				textHeader6->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader6->setLevelPaddingSpaceChar(0);
				textHeader6->setVisible(true);

				textHeader7->setSize(9);
				textHeader7->setFontFamily("FreeSans");
				textHeader7->setBold(false);
				textHeader7->setItalic(false);
				textHeader7->setHPandding(0);
				textHeader7->setVPandding(1);
				textHeader7->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeader7->setLevelPaddingSpaceChar(0);
				textHeader7->setVisible(true);

				textHeaderCustomAtt->setSize(9);
				textHeaderCustomAtt->setFontFamily("FreeSans");
				textHeaderCustomAtt->setBold(false);
				textHeaderCustomAtt->setItalic(false);
				textHeaderCustomAtt->setHPandding(0);
				textHeaderCustomAtt->setVPandding(1);
				textHeaderCustomAtt->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textHeaderCustomAtt->setLevelPaddingSpaceChar(0);
				textHeaderCustomAtt->setVisible(true);

				textBallotName->setSize(12);
				textBallotName->setFontFamily("FreeSans");
				textBallotName->setBold(true);
				textBallotName->setItalic(false);
				textBallotName->setHPandding(0);
				textBallotName->setVPandding(1);
				textBallotName->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textBallotName->setLevelPaddingSpaceChar(0);
				textBallotName->setVisible(false);

				textRegionName->setSize(5);
				textRegionName->setFontFamily("FreeSans");
				textRegionName->setBold(false);
				textRegionName->setItalic(false);
				textRegionName->setHPandding(0);
				textRegionName->setVPandding(1);
				textRegionName->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textRegionName->setLevelPaddingSpaceChar(1);
				textRegionName->setVisible(true);

				textContestName1->setSize(9);
				textContestName1->setFontFamily("FreeSans");
				textContestName1->setBold(true);
				textContestName1->setItalic(false);
				textContestName1->setHPandding(0);
				textContestName1->setVPandding(1);
				textContestName1->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textContestName1->setLevelPaddingSpaceChar(2);
				textContestName1->setVisible(true);

				textContestName2->setSize(9);
				textContestName2->setFontFamily("FreeSans");
				textContestName2->setBold(true);
				textContestName2->setItalic(false);
				textContestName2->setHPandding(0);
				textContestName2->setVPandding(1);
				textContestName2->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_RIGHT);
				textContestName2->setLevelPaddingSpaceChar(2);
				textContestName2->setVisible(true);

				textContestName3->setSize(9);
				textContestName3->setFontFamily("FreeSans");
				textContestName3->setBold(true);
				textContestName3->setItalic(false);
				textContestName3->setHPandding(0);
				textContestName3->setVPandding(1);
				textContestName3->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textContestName3->setLevelPaddingSpaceChar(2);
				textContestName3->setVisible(true);

				textParentOptionSelected->setSize(12);
				textParentOptionSelected->setFontFamily("FreeSans");
				textParentOptionSelected->setBold(true);
				textParentOptionSelected->setItalic(false);
				textParentOptionSelected->setHPandding(0);
				textParentOptionSelected->setVPandding(1);
				textParentOptionSelected->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textParentOptionSelected->setLevelPaddingSpaceChar(2);
				textParentOptionSelected->setVisible(true);

				textPrincipalsMessage->setSize(12);
				textPrincipalsMessage->setFontFamily("FreeSans");
				textPrincipalsMessage->setBold(true);
				textPrincipalsMessage->setItalic(false);
				textPrincipalsMessage->setHPandding(0);
				textPrincipalsMessage->setVPandding(1);
				textPrincipalsMessage->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textPrincipalsMessage->setLevelPaddingSpaceChar(2);
				textPrincipalsMessage->setVisible(true);

				textStandInMessage->setSize(12);
				textStandInMessage->setFontFamily("FreeSans");
				textStandInMessage->setBold(true);
				textStandInMessage->setItalic(false);
				textStandInMessage->setHPandding(0);
				textStandInMessage->setVPandding(1);
				textStandInMessage->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textStandInMessage->setLevelPaddingSpaceChar(2);
				textStandInMessage->setVisible(true);

				textBallotOption->setSize(9);
				textBallotOption->setFontFamily("FreeSans");
				textBallotOption->setBold(false);
				textBallotOption->setItalic(true);
				textBallotOption->setHPandding(14);
				textBallotOption->setVPandding(1);
				textBallotOption->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textBallotOption->setLevelPaddingSpaceChar(1);
				textBallotOption->setVisible(true);

				textGeneric->setSize(9);
				textGeneric->setFontFamily("FreeSans");
				textGeneric->setBold(false);
				textGeneric->setItalic(false);
				textGeneric->setHPandding(0);
				textGeneric->setVPandding(1);
				textGeneric->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textGeneric->setLevelPaddingSpaceChar(0);
				textGeneric->setVisible(true);		

				textBlankVote->setSize(12);
				textBlankVote->setFontFamily("FreeSans");
				textBlankVote->setBold(true);
				textBlankVote->setItalic(false);
				textBlankVote->setHPandding(0);
				textBlankVote->setVPandding(1);
				textBlankVote->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textBlankVote->setLevelPaddingSpaceChar(0);
				textBlankVote->setVisible(true);		
		
				layoutContestConfiguration.setLayoutContestType(Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_TRUNCATED);
				layoutContestConfiguration.setCompleteWithSpaces(true);
				layoutContestConfiguration.setTextBallotOption(*textBallotOption);
		
		
			configurationVote->setTextHeader1(*textHeader1);
			configurationVote->setTextHeader2(*textHeader2);
			configurationVote->setTextHeader3(*textHeader3);
			configurationVote->setTextHeader4(*textHeader4);
			configurationVote->setTextHeader5(*textHeader5);
			configurationVote->setTextHeader6(*textHeader6);
			configurationVote->setTextHeader7(*textHeader7);
			configurationVote->setTextHeaderCustomAttributes(*textHeaderCustomAtt);
		
		
			configurationVote->setTextBallotName(*textBallotName);
			configurationVote->setTextRegionName(*textRegionName);
			configurationVote->setTextContestName1(*textContestName1);
			configurationVote->setTextContestName2(*textContestName2);
			configurationVote->setTextContestName3(*textContestName3);

			configurationVote->setIsTextContestName1CustomAttribute(false);
			configurationVote->setIsTextContestName2CustomAttribute(true);
			configurationVote->setIsTextContestName3CustomAttribute(false);

			configurationVote->setTextParentOptionSelected(*textParentOptionSelected);
			configurationVote->setTextPrincipalsMessage(*textPrincipalsMessage);
			configurationVote->setTextStandInMessage(*textStandInMessage);
			configurationVote->setTextGeneric(*textGeneric);
			configurationVote->setTextBlankVote(*textBlankVote);

			configurationVote->setLayoutContestConfiguration(layoutContestConfiguration);

		configurationVote->setPaddingChar(" ");
		configurationVote->setPrintToPdf(false);
		configurationVote->setQRcodePosition(Smartmatic::SAES::Configuration::QRcodePosition::CONFIGURATION_TOP_ALL);
		configurationVote->setQRCodePrintingMode(Smartmatic::SAES::Configuration::QRCodePrintingModeType::CONFIGURATION_IMAGE_BASED);

		configurationVote->setMaxBallotOptionLastNameChars(22);
		configurationVote->setMaxBallotOptionNameChars(1);
		configurationVote->setMaxBallotOptionCodeChars(4);
		configurationVote->setBallotOptionNameSeparator("#");
		configurationVote->setDirectPrinting(true);		
		configurationVote->setLevelPaddingSpaceCharSize(2);
		configurationVote->setCompleteVoteWithSpaces(true);
		configurationVote->setUseMaxSizeBlankVote(false);
		configurationVote->setShowBallotLines(true);
		configurationVote->setLayoutBallotOptiontType(Smartmatic::SAES::Configuration::LayoutBallotOptiontType::CONFIGURATION_SEPARATEPRINCIPALANDSTANDIN);
		configurationVote->setLayoutSuperBlankType(Smartmatic::SAES::Configuration::LayoutSuperBlankType::CONFIGURATION_JUSTCONTESTCLASS);
		configurationVote->setVoteChecksum(Smartmatic::SAES::Configuration::VoteChecksumType::CONFIGURATION_MD5);
		configurationVote->setVoteEncodeMode (Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_BITWISE);
		configurationVote->setAddBlankSpaceFullContest (1);

		MultiLanguageConfiguration multiLanguageConfiguration (false, "/", 25);
		configurationVote->setMultiLanguageConfiguration(multiLanguageConfiguration);

        QRCodeVoteList qrCodeVoteList;
        QRCodeVoteConfig qrCodeVoteConfig1;
        QRCodeVoteConfig qrCodeVoteConfig2;
        QRCodeVoteList::QRCodeVoteConfigSequence seqQRCodeVote;
        QRCodeConfig qrConfig1;

        qrConfig1.setSizeQRCode(3);
        qrConfig1.setMarginQRCode(2);
        qrConfig1.setCorrectionModeQRCode(CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_L);
        qrConfig1.setVersionQRCode(0);

        QRCodeConfig qrConfig2;

        qrConfig2.setSizeQRCode(3);
        qrConfig2.setMarginQRCode(0);
        qrConfig2.setCorrectionModeQRCode(CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_L);
        qrConfig2.setVersionQRCode(21);

        qrCodeVoteConfig1.setMaxSize(1000);
        qrCodeVoteConfig1.setQRCodeConfig(qrConfig1);

        qrCodeVoteConfig2.setMaxSize(3500);
        qrCodeVoteConfig2.setQRCodeConfig(qrConfig2);

        seqQRCodeVote.push_back(qrCodeVoteConfig1);
        seqQRCodeVote.push_back(qrCodeVoteConfig2);

        qrCodeVoteList.setQRCodeVoteConfig(seqQRCodeVote);

        configurationVote->setVoteQRCodeMode(Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_XMLFULL);
        configurationVote->setQRCodeVoteList(qrCodeVoteList);
        configurationVote->setUseBackgroundImageForQR(true);
        configurationVote->setPositionImageInBackgroundQR(Smartmatic::SAES::Configuration::PositionImage::CONFIGURATION_MIDDLE_CENTER);

        VoteCodeConfig voteCodeConfig;
        voteCodeConfig.setUseShortVoteCode(true);
        voteCodeConfig.setCountGroupVoteCode(11);
        voteCodeConfig.setCharSeparatorVoteCode(" ");

        configurationVote->setVoteCodeConfig(voteCodeConfig);

				textTitleTimeout->setSize(12);
				textTitleTimeout->setFontFamily("FreeSans");
				textTitleTimeout->setBold(true);
				textTitleTimeout->setItalic(false);
				textTitleTimeout->setHPandding(0);
				textTitleTimeout->setVPandding(1);
				textTitleTimeout->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textTitleTimeout->setLevelPaddingSpaceChar(0);
				textTitleTimeout->setVisible(true);		

				textElectionNameTimeout->setSize(12);
				textElectionNameTimeout->setFontFamily("FreeSans");
				textElectionNameTimeout->setBold(true);
				textElectionNameTimeout->setItalic(true);
				textElectionNameTimeout->setHPandding(0);
				textElectionNameTimeout->setVPandding(1);
				textElectionNameTimeout->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textElectionNameTimeout->setLevelPaddingSpaceChar(0);
				textElectionNameTimeout->setVisible(true);

				textVotingBoothTimeout->setSize(12);
				textVotingBoothTimeout->setFontFamily("FreeSans");
				textVotingBoothTimeout->setBold(false);
				textVotingBoothTimeout->setItalic(false);
				textVotingBoothTimeout->setHPandding(0);
				textVotingBoothTimeout->setVPandding(0);
				textVotingBoothTimeout->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textVotingBoothTimeout->setLevelPaddingSpaceChar(0);
				textVotingBoothTimeout->setVisible(true);

				textVoteIDTimeout->setSize(12);
				textVoteIDTimeout->setFontFamily("FreeSans");
				textVoteIDTimeout->setBold(false);
				textVoteIDTimeout->setItalic(false);
				textVoteIDTimeout->setHPandding(0);
				textVoteIDTimeout->setVPandding(1);
				textVoteIDTimeout->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textVoteIDTimeout->setLevelPaddingSpaceChar(0);
				textVoteIDTimeout->setVisible(true);

				textDescriptionTimeout->setSize(9);
				textDescriptionTimeout->setFontFamily("FreeSans");
				textDescriptionTimeout->setBold(false);
				textDescriptionTimeout->setItalic(false);
				textDescriptionTimeout->setHPandding(0);
				textDescriptionTimeout->setVPandding(1);
				textDescriptionTimeout->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textDescriptionTimeout->setLevelPaddingSpaceChar(0);
				textDescriptionTimeout->setVisible(true);

		
		configurationTimeout->setTextTitle(*textTitleTimeout);
		configurationTimeout->setTextElectionName(*textElectionNameTimeout);
		configurationTimeout->setTextVotingBooth(*textVotingBoothTimeout);
		configurationTimeout->setTextVoteID(*textVoteIDTimeout);
		configurationTimeout->setTextDescription(*textDescriptionTimeout);


				textTitleSmartcardRemoved->setSize(12);
				textTitleSmartcardRemoved->setFontFamily("FreeSans");
				textTitleSmartcardRemoved->setBold(true);
				textTitleSmartcardRemoved->setItalic(false);
				textTitleSmartcardRemoved->setHPandding(0);
				textTitleSmartcardRemoved->setVPandding(1);
				textTitleSmartcardRemoved->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textTitleSmartcardRemoved->setLevelPaddingSpaceChar(0);
				textTitleSmartcardRemoved->setVisible(true);		

				textElectionNameSmartcardRemoved->setSize(12);
				textElectionNameSmartcardRemoved->setFontFamily("FreeSans");
				textElectionNameSmartcardRemoved->setBold(true);
				textElectionNameSmartcardRemoved->setItalic(true);
				textElectionNameSmartcardRemoved->setHPandding(0);
				textElectionNameSmartcardRemoved->setVPandding(1);
				textElectionNameSmartcardRemoved->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textElectionNameSmartcardRemoved->setLevelPaddingSpaceChar(0);
				textElectionNameSmartcardRemoved->setVisible(true);

				textVotingBoothSmartcardRemoved->setSize(12);
				textVotingBoothSmartcardRemoved->setFontFamily("FreeSans");
				textVotingBoothSmartcardRemoved->setBold(false);
				textVotingBoothSmartcardRemoved->setItalic(false);
				textVotingBoothSmartcardRemoved->setHPandding(0);
				textVotingBoothSmartcardRemoved->setVPandding(0);
				textVotingBoothSmartcardRemoved->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textVotingBoothSmartcardRemoved->setLevelPaddingSpaceChar(0);
				textVotingBoothSmartcardRemoved->setVisible(true);

				textVoteIDSmartcardRemoved->setSize(12);
				textVoteIDSmartcardRemoved->setFontFamily("FreeSans");
				textVoteIDSmartcardRemoved->setBold(false);
				textVoteIDSmartcardRemoved->setItalic(false);
				textVoteIDSmartcardRemoved->setHPandding(0);
				textVoteIDSmartcardRemoved->setVPandding(1);
				textVoteIDSmartcardRemoved->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
				textVoteIDSmartcardRemoved->setLevelPaddingSpaceChar(0);
				textVoteIDSmartcardRemoved->setVisible(true);

				textDescriptionSmartcardRemoved->setSize(9);
				textDescriptionSmartcardRemoved->setFontFamily("FreeSans");
				textDescriptionSmartcardRemoved->setBold(false);
				textDescriptionSmartcardRemoved->setItalic(false);
				textDescriptionSmartcardRemoved->setHPandding(0);
				textDescriptionSmartcardRemoved->setVPandding(1);
				textDescriptionSmartcardRemoved->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textDescriptionSmartcardRemoved->setLevelPaddingSpaceChar(0);
				textDescriptionSmartcardRemoved->setVisible(true);

		configurationSmartcardRemoved->setTextTitle(*textTitleSmartcardRemoved);
		configurationSmartcardRemoved->setTextElectionName(*textElectionNameSmartcardRemoved);
		configurationSmartcardRemoved->setTextVotingBooth(*textVotingBoothSmartcardRemoved);
		configurationSmartcardRemoved->setTextVoteID(*textVoteIDSmartcardRemoved);
		configurationSmartcardRemoved->setTextDescription(*textDescriptionSmartcardRemoved);
		

				textInstallationTitleLevel1->setSize(12);
				textInstallationTitleLevel1->setFontFamily("FreeSans");
				textInstallationTitleLevel1->setBold(false);
				textInstallationTitleLevel1->setItalic(false);
				textInstallationTitleLevel1->setHPandding(0);
				textInstallationTitleLevel1->setVPandding(1);
				textInstallationTitleLevel1->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textInstallationTitleLevel1->setLevelPaddingSpaceChar(0);
				textInstallationTitleLevel1->setVisible(true);

				textInstallationTitleLevel2->setSize(12);
				textInstallationTitleLevel2->setFontFamily("FreeSans");
				textInstallationTitleLevel2->setBold(false);
				textInstallationTitleLevel2->setItalic(false);
				textInstallationTitleLevel2->setHPandding(0);
				textInstallationTitleLevel2->setVPandding(1);
				textInstallationTitleLevel2->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textInstallationTitleLevel2->setLevelPaddingSpaceChar(0);
				textInstallationTitleLevel2->setVisible(true);

				textInstallationTitleLevel3->setSize(9);
				textInstallationTitleLevel3->setFontFamily("FreeSans");
				textInstallationTitleLevel3->setBold(false);
				textInstallationTitleLevel3->setItalic(false);
				textInstallationTitleLevel3->setHPandding(0);
				textInstallationTitleLevel3->setVPandding(10);
				textInstallationTitleLevel3->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_RIGHT);
				textInstallationTitleLevel3->setLevelPaddingSpaceChar(0);
				textInstallationTitleLevel3->setVisible(true);

				textInstallationInfo->setSize(9);
				textInstallationInfo->setFontFamily("FreeSans");
				textInstallationInfo->setBold(false);
				textInstallationInfo->setItalic(false);
				textInstallationInfo->setHPandding(0);
				textInstallationInfo->setVPandding(10);
				textInstallationInfo->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
				textInstallationInfo->setLevelPaddingSpaceChar(0);
				textInstallationInfo->setVisible(true);

		configurationInstallation->setTextInstallationTitleLevel1(*textInstallationTitleLevel1);
		configurationInstallation->setTextInstallationTitleLevel2(*textInstallationTitleLevel2);
		configurationInstallation->setTextInstallationTitleLevel3(*textInstallationTitleLevel3);
		configurationInstallation->setTextInstallationInfo(*textInstallationInfo);
		configurationInstallation->setShowBarCode(true);
		configurationInstallation->setBase64QRCode(false);
		configurationInstallation->setQRcodePosition(Smartmatic::SAES::Configuration::QRcodePosition::CONFIGURATION_BOTTOM_ALL);

						textContingencyTitleLevel1->setSize(12);
						textContingencyTitleLevel1->setFontFamily("FreeSans");
						textContingencyTitleLevel1->setBold(false);
						textContingencyTitleLevel1->setItalic(false);
						textContingencyTitleLevel1->setHPandding(0);
						textContingencyTitleLevel1->setVPandding(1);
						textContingencyTitleLevel1->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
						textContingencyTitleLevel1->setLevelPaddingSpaceChar(0);
						textContingencyTitleLevel1->setVisible(true);

						textContingencyTitleLevel2->setSize(12);
						textContingencyTitleLevel2->setFontFamily("FreeSans");
						textContingencyTitleLevel2->setBold(false);
						textContingencyTitleLevel2->setItalic(false);
						textContingencyTitleLevel2->setHPandding(0);
						textContingencyTitleLevel2->setVPandding(1);
						textContingencyTitleLevel2->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
						textContingencyTitleLevel2->setLevelPaddingSpaceChar(0);
						textContingencyTitleLevel2->setVisible(true);

						textContingencyTitleLevel3->setSize(9);
						textContingencyTitleLevel3->setFontFamily("FreeSans");
						textContingencyTitleLevel3->setBold(false);
						textContingencyTitleLevel3->setItalic(false);
						textContingencyTitleLevel3->setHPandding(0);
						textContingencyTitleLevel3->setVPandding(10);
						textContingencyTitleLevel3->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_RIGHT);
						textContingencyTitleLevel3->setLevelPaddingSpaceChar(0);
						textContingencyTitleLevel3->setVisible(true);

						textContingencyInfo->setSize(9);
						textContingencyInfo->setFontFamily("FreeSans");
						textContingencyInfo->setBold(false);
						textContingencyInfo->setItalic(false);
						textContingencyInfo->setHPandding(0);
						textContingencyInfo->setVPandding(10);
						textContingencyInfo->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_LEFT);
						textContingencyInfo->setLevelPaddingSpaceChar(0);
						textContingencyInfo->setVisible(true);

		configurationContingency->setTextContingencyTitleLevel1 (*textContingencyTitleLevel1);
		configurationContingency->setTextContingencyTitleLevel2 (*textContingencyTitleLevel2);
		configurationContingency->setTextContingencyTitleLevel3 (*textContingencyTitleLevel3);
		configurationContingency->setTextContingencyInfo (*textContingencyInfo);
		configurationContingency->setIncludeHelp (true);
		configurationContingency->setIncludeRegionSection (true);
		
        QRCodeConfig qrConfigInstall;

        qrConfigInstall.setSizeQRCode(3);
        qrConfigInstall.setMarginQRCode(0);
        qrConfigInstall.setCorrectionModeQRCode(CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_L);
        qrConfigInstall.setVersionQRCode(21);

		configurationInstallation->setQRCodeConfig(qrConfigInstall);

			textLogTitleLevel1->setSize(10);
			textLogTitleLevel1->setFontFamily("FreeSans");
			textLogTitleLevel1->setBold(true);
			textLogTitleLevel1->setItalic(false);
			textLogTitleLevel1->setHPandding(0);
			textLogTitleLevel1->setVPandding(10);
			textLogTitleLevel1->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
			textLogTitleLevel1->setLevelPaddingSpaceChar(0);
			textLogTitleLevel1->setVisible(true);

			textLogTitleLevel2->setSize(8);
			textLogTitleLevel2->setFontFamily("FreeSans");
			textLogTitleLevel2->setBold(false);
			textLogTitleLevel2->setItalic(false);
			textLogTitleLevel2->setHPandding(0);
			textLogTitleLevel2->setVPandding(10);
			textLogTitleLevel2->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
			textLogTitleLevel2->setLevelPaddingSpaceChar(0);
			textLogTitleLevel2->setVisible(true);

			textLogTitleLevel3->setSize(8);
			textLogTitleLevel3->setFontFamily("FreeSans");
			textLogTitleLevel3->setBold(false);
			textLogTitleLevel3->setItalic(false);
			textLogTitleLevel3->setHPandding(0);
			textLogTitleLevel3->setVPandding(10);
			textLogTitleLevel3->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
			textLogTitleLevel3->setLevelPaddingSpaceChar(0);
			textLogTitleLevel3->setVisible(true);

			textLogTitleLevel4->setSize(8);
			textLogTitleLevel4->setFontFamily("FreeSans");
			textLogTitleLevel4->setBold(false);
			textLogTitleLevel4->setItalic(false);
			textLogTitleLevel4->setHPandding(0);
			textLogTitleLevel4->setVPandding(10);
			textLogTitleLevel4->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
			textLogTitleLevel4->setLevelPaddingSpaceChar(0);
			textLogTitleLevel4->setVisible(true);

			textLogTitleLevel5->setSize(8);
			textLogTitleLevel5->setFontFamily("FreeSans");
			textLogTitleLevel5->setBold(false);
			textLogTitleLevel5->setItalic(false);
			textLogTitleLevel5->setHPandding(0);
			textLogTitleLevel5->setVPandding(10);
			textLogTitleLevel5->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_CENTER);
			textLogTitleLevel5->setLevelPaddingSpaceChar(0);
			textLogTitleLevel5->setVisible(true);

			textLogEntry->setSize(6);
			textLogEntry->setFontFamily("FreeSans");
			textLogEntry->setBold(false);
			textLogEntry->setItalic(false);
			textLogEntry->setHPandding(0);
			textLogEntry->setVPandding(10);
			textLogEntry->setAlign(Smartmatic::SAES::Configuration::AlignType::CONFIGURATION_RIGHT);
			textLogEntry->setLevelPaddingSpaceChar(0);
			textLogEntry->setVisible(true);

			//logDocColLayout->setColumnLayout (DocumentColumnLayout::CONFIGURATION_DOUBLECOLUMN);

		logPrintDocConf->setTextLogTitleLevel1 (*textLogTitleLevel1);
		logPrintDocConf->setTextLogTitleLevel2 (*textLogTitleLevel2);
		logPrintDocConf->setTextLogTitleLevel3 (*textLogTitleLevel3);
		logPrintDocConf->setTextLogTitleLevel4 (*textLogTitleLevel4);
		logPrintDocConf->setTextLogTitleLevel5 (*textLogTitleLevel5);
		logPrintDocConf->setTextLogEntry (*textLogEntry);
		logPrintDocConf->setColumnLayout (DocumentColumnLayout::CONFIGURATION_SINGLECOLUMN);

		configurationPrinter->setConfigurationTimeout(*configurationTimeout);
		configurationPrinter->setConfigurationVote(*configurationVote);
		configurationPrinter->setConfigurationInstallation(*configurationInstallation);
		configurationPrinter->setConfigurationContingency(*configurationContingency);
		configurationPrinter->setConfigurationSmartcardRemoved(*configurationSmartcardRemoved);
		configurationPrinter->setLogPrintDocConfiguration (*logPrintDocConf);

		configurationScreenPreview->setConfigurationVote(*configurationVote);

		configurationCard->setTimeOfValidity(0);
		configurationCard->setAllowRecoveryCardGenerationOfConsolidatedVotes(true);
		
		VoteDummyConfiguration vdc;
        vdc.setLogicalVoterGroupCode("0000");
        vdc.setContestCode("0000");
        vdc.setBallotOptionCode("0000");

        StatisticConfiguration statistic;
        StatisticConfiguration::StatisticGroupsSequence groupSeq;

        /************************************************************************************/

        StatisticItem notInitiated;
        notInitiated.setCode("1");
        notInitiated.setNameKey(N_("Smartmatic.SAES.StatisticGroup.BeforeOpenElection.ActivationCardsReceived.ItemName"));
        notInitiated.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.BeforeOpenElection.ActivationCardsReceived.ItemDescription"));
        notInitiated.setType(StatisticElementType::CONFIGURATION_NUMERIC);
        notInitiated.setMax(4);

        StatisticGroups groupNotInitiated;
        groupNotInitiated.setNameKey(N_("Smartmatic.SAES.StatisticGroup.BeforeOpenElection.Name"));
        groupNotInitiated.setEditInfoKey(N_("Smartmatic.SAES.StatisticGroup.BeforeOpenElection.EditableStateInstruction"));
        groupNotInitiated.setBlockerInfoKey(N_("Smartmatic.SAES.StatisticGroup.BeforeOpenElection.NonEditableNotification"));
        groupNotInitiated.setVerticalFilling(false);
        groupNotInitiated.setPivot(2);

        StatisticGroups::StatisticItemSequence groupNotInitiatedSeq;
        groupNotInitiatedSeq.push_back(notInitiated);
        groupNotInitiated.setStatisticItem(groupNotInitiatedSeq);

        StatisticGroups::StatisticEditTypeSequence groupNotInitiatedStatisticEditTypeSeq;
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINSTALLED);
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTPOLLWORKERREGISTERED);
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTDEMOSTRATIONVOTE);
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINITIATED);
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_INITIATED);
        groupNotInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_CLOSED);
        groupNotInitiated.setStatisticEditType(groupNotInitiatedStatisticEditTypeSeq);

        groupSeq.push_back(groupNotInitiated);

        /************************************************************************************/

        StatisticItem initiated2;
        initiated2.setCode("2");
        initiated2.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.DamagedCardsOnPorpuse.ItemName"));
        initiated2.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.DamagedCardsOnPorpuse.ItemDescription"));
        initiated2.setType(StatisticElementType::CONFIGURATION_NUMERIC);
        initiated2.setMax(4);

		StatisticItem initiated3;
		initiated3.setCode("3");
		initiated3.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.ActivatedCardsWithProblems.ItemName"));
		initiated3.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.ActivatedCardsWithProblems.ItemDescription"));
		initiated3.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		initiated3.setMax(4);

		StatisticItem initiated4;
		initiated4.setCode("4");
		initiated4.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.TotalCardsWithProblems.ItemName"));
		initiated4.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.TotalCardsWithProblems.ItemDescription"));
		initiated4.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		initiated4.setMax(4);

		StatisticItem::AddStatisticCodeSequence codeSeq;
		codeSeq.push_back("2");
		codeSeq.push_back("3");
		initiated4.setAddStatisticCode(codeSeq);

		StatisticItem initiated5;
		initiated5.setCode("5");
		initiated5.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.VisualizationProblems.ItemName"));
		initiated5.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.VisualizationProblems.ItemDescription"));
		initiated5.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		initiated5.setMax(4);

		StatisticItem initiated6;
		initiated6.setCode("6");
		initiated6.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.RevealedVotes.ItemName"));
		initiated6.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.RevealedVotes.ItemDescription"));
		initiated6.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		initiated6.setMax(4);

		StatisticItem initiated7;
		initiated7.setCode("7");
		initiated7.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.AnnuledVotes.ItemName"));
		initiated7.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.AnnuledVotes.ItemDescription"));
		initiated7.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		initiated7.setMax(4);

		StatisticGroups groupInitiated;
		groupInitiated.setNameKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.Name"));
		groupInitiated.setEditInfoKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.EditableStateInstruction"));
		groupInitiated.setBlockerInfoKey(N_("Smartmatic.SAES.StatisticGroup.VotingProcess.NonEditableNotification"));
        groupInitiated.setVerticalFilling(false);
        groupInitiated.setPivot(2);

		StatisticGroups::StatisticItemSequence groupInitiatedSeq;
		groupInitiatedSeq.push_back(initiated2);
		groupInitiatedSeq.push_back(initiated3);
		groupInitiatedSeq.push_back(initiated4);
		groupInitiatedSeq.push_back(initiated5);
		groupInitiatedSeq.push_back(initiated6);
		groupInitiatedSeq.push_back(initiated7);
		groupInitiated.setStatisticItem(groupInitiatedSeq);

	    StatisticGroups::StatisticEditTypeSequence groupInitiatedStatisticEditTypeSeq;
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINSTALLED);
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTPOLLWORKERREGISTERED);
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTDEMOSTRATIONVOTE);
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINITIATED);
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_INITIATED);
        groupInitiatedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_CLOSED);
        groupInitiated.setStatisticEditType(groupInitiatedStatisticEditTypeSeq);

		groupSeq.push_back(groupInitiated);

        /************************************************************************************/

        StatisticItem close8;
		close8.setCode("8");
		close8.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.UnusedActivationCards.ItemName"));
		close8.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.UnusedActivationCards.ItemDescription"));
		close8.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close8.setMax(4);

        StatisticItem close9;
        close9.setCode("9");
        close9.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.RegisteredActivationCardsWithVotes.ItemName"));
        close9.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.RegisteredActivationCardsWithVotes.ItemDescription"));
		close9.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close9.setMax(4);

        StatisticItem close10;
        close10.setCode("10");
        close10.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.ValidatedActivationCardsByUrn.ItemName"));
        close10.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.ValidatedActivationCardsByUrn.ItemDescription"));
		close10.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close10.setMax(4);

        StatisticItem close11;
        close11.setCode("11");
        close11.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsDueToProblems.ItemName"));
        close11.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsDueToProblems.ItemDescription"));
		close11.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close11.setMax(4);

        StatisticItem close12;
        close12.setCode("12");
        close12.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsDueToInvalidaVote.ItemName"));
        close12.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsDueToInvalidaVote.ItemDescription"));
		close12.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close12.setMax(4);

        StatisticItem close13;
        close13.setCode("13");
        close13.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsUnderReview.ItemName"));
        close13.setDescriptionKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.AnnuledActivationCardsUnderReview.ItemDescription"));
		close13.setType(StatisticElementType::CONFIGURATION_NUMERIC);
		close13.setMax(4);

        StatisticGroups groupClosed;
        groupClosed.setNameKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.Name"));
        groupClosed.setEditInfoKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.EditableStateInstruction"));
        groupClosed.setBlockerInfoKey(N_("Smartmatic.SAES.StatisticGroup.AfterClose.NonEditableNotification"));
        groupClosed.setVerticalFilling(false);
        groupClosed.setPivot(2);

        StatisticGroups::StatisticItemSequence groupClosedSeq;
        groupClosedSeq.push_back(close8);
        groupClosedSeq.push_back(close9);
        groupClosedSeq.push_back(close10);
        groupClosedSeq.push_back(close11);
        groupClosedSeq.push_back(close12);
        groupClosedSeq.push_back(close13);
        groupClosed.setStatisticItem(groupClosedSeq);

        StatisticGroups::StatisticEditTypeSequence groupClosedStatisticEditTypeSeq;
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINSTALLED);
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTPOLLWORKERREGISTERED);
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTDEMOSTRATIONVOTE);
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_NOTINITIATED);
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_INITIATED);
        groupClosedStatisticEditTypeSeq.push_back(StatisticEditType::CONFIGURATION_CLOSED);
        groupClosed.setStatisticEditType(groupClosedStatisticEditTypeSeq);

        groupSeq.push_back(groupClosed);

        statistic.setStatisticGroups(groupSeq);

        /************************************************************************************/

        TransmissionPackageConfiguration transmissionConfig;
        transmissionConfig.setSaveDemoVotesInTransmissionPackage(false);

        /************************************************************************************/

    	RuleCodiFileNameConfiguration ruleCodiFile(RuleCodiFileNameConfiguration::CONFIGURATION_CODE_MACHINE);
    	RegionNameCodiConfig regionNameCodiConfig(RegionNameCodiConfig::CONFIGURATION_VOTING_VOTE_CUSTOM_CODE);

    	RegisterCodiConfig registerS(false, true, true, true);
    	RegisterCodiConfig registerL(false, true, false, true);
    	RegisterCodiConfig registerC(false, true, true, true);
    	registerC.setFillLastFields(true);

    	CodiFileConfiguration codiFileConfiguration;
        codiFileConfiguration.setEnableCodi(true);
        codiFileConfiguration.setPersistenceCodi(true);
        codiFileConfiguration.setSeparatorVotingDevice("_");
    	codiFileConfiguration.setFirstStringFileName("V");
    	codiFileConfiguration.setRuleCodiFileName(ruleCodiFile);
    	codiFileConfiguration.setRegionName(regionNameCodiConfig);
    	codiFileConfiguration.setPersistenceX7SCodi(true);
        codiFileConfiguration.setX7SAddPVReport(true);
        codiFileConfiguration.setX7SSigned(X7SSigned::CONFIGURATION_PKCS7_SIGNER);
        codiFileConfiguration.setX7SCrypto(X7SCrypto::CONFIGURATION_PKCS7_CRYPTO);
        codiFileConfiguration.setX7SSignedCertified(X7SSecurityType::CONFIGURATION_MACHINE_KEYS_FILE);
        codiFileConfiguration.setX7SCryptoCertified(X7SSecurityType::CONFIGURATION_PEM_FILES);

        codiFileConfiguration.setRegisterS(registerS);
		codiFileConfiguration.setRegisterL(registerL);
		codiFileConfiguration.setRegisterC(registerC);

        QRCodeConfig qrConfigBarcode;

        qrConfigBarcode.setSizeQRCode(3);
        qrConfigBarcode.setMarginQRCode(2);
        qrConfigBarcode.setCorrectionModeQRCode(CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_L);
        qrConfigBarcode.setVersionQRCode(0);

        /************************************************************************************/

        configSAES->setBarcodeQRCodeConfig(qrConfigBarcode);
        configSAES->setStatisticConfiguration(statistic);
        configSAES->setTransmissionPackageConfiguration(transmissionConfig);
        configSAES->setCodiFileConfiguration(codiFileConfiguration);
        configSAES->setVoteDummy(vdc);
		configSAES->setConfigurationPrinter(*configurationPrinter);
		configSAES->setConfigurationScreenPreview(*configurationScreenPreview);
		configSAES->setConfigurationCard(*configurationCard);
		configSAES->setReportPrinting(report_conf);

        Smartmatic::ConfigurationTypes::NamespaceInfomap map;

#ifdef NAMESPACE_CONFIGURATION
        map[""].name = NAMESPACE_CONFIGURATION;
#endif
        map[""].schema = "";

		serializeSaesConfiguration(ss,*configSAES, map, "UTF-8");
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SAES",ss.str());
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAES Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch(...)
	{
		ZenityWrapper::showError("Config SAES Error", "Error");
		exit (0);
	}

	delete (configSAES);
	delete (configurationPrinter);
	delete (configurationScreenPreview);
	delete (configurationCard);
	delete (configurationTimeout);
	delete (configurationVote);
	
	delete (textHeader1);
	delete (textHeader2);
   	delete (textHeader3);
	delete (textHeader4);
	delete (textHeader5);
	delete (textHeader6);
	delete (textHeader7);
	delete (textHeaderCustomAtt);
	
	delete (textBallotName);
	delete (textRegionName);
	delete (textContestName1);
	delete (textContestName2);
	delete (textContestName3);
	delete (textParentOptionSelected);
	delete (textPrincipalsMessage);
	delete (textStandInMessage);
	delete (textBallotOption);

	delete(textTitleTimeout);
	delete(textElectionNameTimeout);
	delete(textVotingBoothTimeout);
	delete(textVoteIDTimeout);
	delete(textDescriptionTimeout);

	delete (textTitleSmartcardRemoved);
	delete (textElectionNameSmartcardRemoved);
	delete (textVotingBoothSmartcardRemoved);
	delete (textVoteIDSmartcardRemoved);		 
	delete (textDescriptionSmartcardRemoved);

	delete (textInstallationTitleLevel1);
	delete (textInstallationTitleLevel2);
	delete (textInstallationTitleLevel3);
	delete (textInstallationInfo);

	delete (textGeneric);
	delete (textBlankVote);
	
}

QRCodeConfig SAESConfigurationManager::getQRCodeBarcodeConfig()
{
    return ((*configuration)->getBarcodeQRCodeConfig());
}

QRCodeConfig SAESConfigurationManager::getQRCodeVoteConfig(int size)
{

    QRCodeVoteList & qrCodeVoteList((*configuration)->getConfigurationPrinter().getConfigurationVote().getQRCodeVoteList());
    QRCodeVoteList::QRCodeVoteConfigSequence & seqQRCodeVoteConfig (qrCodeVoteList.getQRCodeVoteConfig());
    QRCodeVoteList::QRCodeVoteConfigIterator it;
    QRCodeConfig qrCodeConfig;

    std::map <int, QRCodeConfig> mapConfig;
    std::map <int, QRCodeConfig>::iterator mapIt;

    for (it = seqQRCodeVoteConfig.begin();
         it != seqQRCodeVoteConfig.end();
         it++)
    {
        mapConfig[(*it).getMaxSize()] = (*it).getQRCodeConfig();
    }

    bool found = false;

    for (mapIt = mapConfig.begin();
         mapIt != mapConfig.end();
         mapIt++)
    {
        qrCodeConfig = ((*mapIt).second);

        if (size <= ((*mapIt).first))
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        qrCodeConfig.setVersionQRCode(0);
    }

    return qrCodeConfig;
}

QRCodeConfig SAESConfigurationManager::getQRCodeInstallConfig()
{
    return ((*configuration)->getConfigurationPrinter().getConfigurationInstallation().getQRCodeConfig());
}

QRecLevel SAESConfigurationManager::GetCorrectionModeQRCode(CorrectionModeQRCode & correction)
{
	if(correction == CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_L)
		return QR_ECLEVEL_L;
	else if(correction == CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_M)
		return QR_ECLEVEL_M;
	else if(correction == CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_Q)
		return QR_ECLEVEL_Q;
	else if(correction == CorrectionModeQRCode::CONFIGURATION_QR_ECLEVEL_H)
		return QR_ECLEVEL_H;

	return QR_ECLEVEL_L;
}

VoteDummyConfiguration SAESConfigurationManager::getVoteDummyConfiguration()
{
    return ((*configuration)->getVoteDummy());
}

VoteEncodeModeType SAESConfigurationManager::getEncodingMode ()
{
    return (*SAESConfigurationManager::Current()->getConfiguration())-> getConfigurationPrinter().getConfigurationVote().getVoteEncodeMode ();
}

VoteChecksumType SAESConfigurationManager::getVoteChecksum()
{
    return (*SAESConfigurationManager::Current()->getConfiguration())-> getConfigurationPrinter().getConfigurationVote().getVoteChecksum();
}

bool SAESConfigurationManager::isUseShortVoteCode()
{
    return getVoteCodeConfig().getUseShortVoteCode();
}

bool SAESConfigurationManager::showBarCodeInstallationReport()
{
    return (*configuration)->getConfigurationPrinter().getConfigurationInstallation().getShowBarCode();
}

VoteCodeConfig & SAESConfigurationManager::getVoteCodeConfig()
{
	return ((*configuration)->getConfigurationPrinter().getConfigurationVote().getVoteCodeConfig());
}

LayoutContestConfiguration & SAESConfigurationManager::getLayoutContestConfiguration()
{
	return ((*configuration)->getConfigurationPrinter().getConfigurationVote().getLayoutContestConfiguration());
}

LayoutBallotOptiontType & SAESConfigurationManager::getLayoutBallotOptiontType()
{
	return ((*configuration)->getConfigurationPrinter().getConfigurationVote().getLayoutBallotOptiontType());
}

LayoutContestConfiguration & SAESConfigurationManager::getLayoutContestConfigurationPreviewScreen()
{
	return getPrintScreenVoteConfiguration().getLayoutContestConfiguration();
}

LayoutBallotOptiontType & SAESConfigurationManager::getLayoutBallotOptiontTypePreviewScreen()
{
	return getPrintScreenVoteConfiguration().getLayoutBallotOptiontType();
}


SAESConfigurationManager * SAESConfigurationManager::singleton_instance = NULL;

SAESConfigurationManager *SAESConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SAESConfigurationManager ();

	return singleton_instance;
}
