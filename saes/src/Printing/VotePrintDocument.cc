/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Functionalities/time-functionality.h"
#include "Voting/ElectoralConfiguration.hxx"
#include "Voting/VotingDevice/voting-devices-schema.hxx"
#include "Resources/election-string-resources-manager.h"
#include "System/Compression/compression-class.h"
#include "Graphics/Encoding2D/QREncoding.h"
#include <stdlib.h>
#include "Printing/TranslatorTextConfiguration.h"
#include <set>
#include <Security/Encryption.hxx>
#include <System/XML/Serialization/DomWriter.h>
#include <qrencode.h>
#include <Graphics/Encoding2D/QREncoding.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Graphics/Image/Compose.hxx>
#include <Voting/Vote/VoteCode.hxx>
#include <System/SafeBuffer.h>
#include <System/IO/File.h>
#include "Printing/VotePrintDocument.h"
#include <Voting/Vote/VoteWrapper.hxx>
#include "Voting/set-language-functionality.h"
#include <System/Utils/StringUtils.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) EvaluateText(String) ///<macro for evaluate text to translate

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::XML::Serialization;
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::System;
using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Utils;

int VotePrintDocument::maxList = 0;
int VotePrintDocument::maxBallotOptions = 0;
std::map < std::string, int > VotePrintDocument::maxLineListOptions;
std::map < std::string, int > VotePrintDocument::maxLineBallotOptions;

ISMTTLog* VotePrintDocument::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.VotePrintDocument",GETTEXT_PACKAGE);

void VotePrintDocument::PrintDoc()
{
  PrintVote(_vote);
}

void VotePrintDocument::BeginPrint()
{

}

void VotePrintDocument::EndPrint()
{

}

VotePrintDocument::VotePrintDocument ( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, 
    const Vote::Vote & vote, bool forceGtkPrinting, bool showBarCode, bool screenPreview) : BasePrintDocument(forceGtkPrinting), _vote(vote)
{
	this->showBarCode = showBarCode;
	this->electoralConfiguration = electoralConfiguration;
	this->recoveryVoteMap = electoralConfiguration->getVoteRecovery()->LogicalToRecovery (vote);
    
    if(screenPreview)
    {
        logger->Debug("Loading screen preview configuration layout");
        this->printConfiguration = SAESConfigurationManager::Current()->getPrintScreenVoteConfiguration();
        layout = SAESConfigurationManager::Current()->getLayoutContestConfigurationPreviewScreen();
    } 
    else
    {
        logger->Debug("Loading print configuration and layout");
        this->printConfiguration = SAESConfigurationManager::Current()->getPrintVoteConfiguration();
        layout = SAESConfigurationManager::Current()->getLayoutContestConfiguration();
    }

	this->_maxBallotOptionLastNameChars = printConfiguration.getMaxBallotOptionLastNameChars();
	this->_maxBallotOptionNameChars = printConfiguration.getMaxBallotOptionNameChars();
	this->_maxBallotOptionCodeChars = printConfiguration.getMaxBallotOptionCodeChars();
	this->_textOptionGeneric = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextGeneric());
	this->_charPadding = printConfiguration.getPaddingChar();
	this->separatorName = printConfiguration.getBallotOptionNameSeparator();

	this->isMultiLanguage = printConfiguration.getMultiLanguageConfiguration().getEnable() && electoralConfiguration->getLanguages().getLanguage().size() > 1;
	this->maxCharByLanguage = printConfiguration.getMultiLanguageConfiguration().getMaxCharsByLanguage();

	QRCodePrintingModeType qr_print_mode = printConfiguration.getQRCodePrintingMode();

	if (qr_print_mode == QRCodePrintingModeType::CONFIGURATION_IMAGE_BASED)
	{
		  pixbufBarCode = GetQRCodeVote(vote);
	}

	Voting_booths::Voting_boothSequence & votingBooths =  electoralConfiguration->getVotingDevice()->getVotingBooths().getVoting_booth();

	if (votingBooths.size() > 0)
	{
		this->votingBooth = votingBooths[0];
	}
	else
	{
		logger->Debug("FATAL - Error not found voting booths.");
	}

	this->customAttributeDefinition = electoralConfiguration->getVotingDevice()->getCustomAttributeDefinitionList( Machine_type::VOTING_DEVICES_PM );
}

Glib::ustring VotePrintDocument::EvaluateText(Glib::ustring key)
{
  Glib::ustring translated = _(key.c_str());
  if(key == translated)
    return "";
  return translated;
}

void VotePrintDocument::AddVoteText(Glib::ustring toCompose, 
    TextConfiguration textConfiguration,
    vector<Glib::ustring> & vParam)
{
  if(!toCompose.empty() && toCompose != " ")
    {
      int paramSize = vParam.size();
      if(paramSize < 9)
        for(int i = paramSize;i<9;i++)
          vParam.push_back("");

      DocumentTextOptions textOption = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(textConfiguration);
      if(textConfiguration.getVisible())
        {
          Glib::ustring composed = Glib::ustring::compose(toCompose,vParam[0],
              vParam[1],vParam[2],
              vParam[3],vParam[4],
              vParam[5],vParam[6],
              vParam[7],vParam[8]);
          if(!composed.empty() && composed != " ")
            {
              this->NewTextBlock(textOption);
              this->DrawString(composed,true);
            }
        }
    }
}

void VotePrintDocument::AddVoteHeader(const Vote::Vote & vote)
{
	Smartmatic::SAES::Voting::Election::Election & election( electoralConfiguration->getElection()->getElection());

	strElectionName = getResource(election.getName_key());
	strElectoralOrg =  getResource(election.getElectoral_organization());
	strPollingPlaceName = getResource(votingBooth.getPolling_place_name());
	strPollingPlaceAddres = getResource(votingBooth.getPolling_place_address());

	// Voting booths
	Glib::ustring strVotingBooth = vote.getVotingDeviceCode();

	//lvg code
	Glib::ustring strLVGCode = vote.getLogicalVoterGroup();

	// Vote Code
	std::string strVoteCode = vote.getCode();

	Vote::VoteCode::encode (strVoteCode);

	SafeBuffer checksumBuffer;
	Vote::VoteCode::getChecksum(vote, checksumBuffer);
	// Checksum
	Glib::ustring strVoteChecksum = checksumBuffer.GetBase64Data();

	this->NewTextBlock(_textOptionGeneric);

	switch(vote.getMode())
	{
	case Vote::VoteMode::VOTE_D:
		this->DrawString("", true);
		this->DrawString("", true);
		this->DrawString(strDemoTitle,true);
		break;

	case Vote::VoteMode::VOTE_R:
		this->DrawString("", true);
		this->DrawString("", true);
		this->DrawString(strRecoveryTitle,true);
		break;
	case Vote::VoteMode::VOTE_S:
		this->DrawString("", true);
		this->DrawString("", true);
		this->DrawString(strSimulatedTitle,true);
		break;

	case Vote::VoteMode::VOTE_O:
		break;
	}

	this->NewTextBlock(_textOptionGeneric);
	Glib::ustring line = N_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineBeginHeader");

	if(!line.empty() && line != " ")
	{
	  this->DrawString(line,true);
	}

	vector<Glib::ustring> vHeaderParams;

	vHeaderParams.push_back(strElectionName);
	vHeaderParams.push_back(strElectoralOrg);
	vHeaderParams.push_back(strVotingBooth);
	vHeaderParams.push_back(strPollingPlaceName);
	vHeaderParams.push_back(strVoteCode);
	vHeaderParams.push_back(strVoteChecksum);
	vHeaderParams.push_back(strPollingPlaceAddres);
	vHeaderParams.push_back(strLVGCode);

	if(vote.getMode() == Vote::VoteMode::VOTE_D)
	{
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo1"),printConfiguration.getTextHeader1(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo2"),printConfiguration.getTextHeader2(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo3"),printConfiguration.getTextHeader3(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo4"),printConfiguration.getTextHeader4(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo5"),printConfiguration.getTextHeader5(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo6"),printConfiguration.getTextHeader6(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.HeaderDemo7"),printConfiguration.getTextHeader7(),vHeaderParams);
	}
	else
	{
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header1"),printConfiguration.getTextHeader1(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header2"),printConfiguration.getTextHeader2(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header3"),printConfiguration.getTextHeader3(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header4"),printConfiguration.getTextHeader4(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header5"),printConfiguration.getTextHeader5(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header6"),printConfiguration.getTextHeader6(),vHeaderParams);
	  AddVoteText(N_("Smartmatic.SAES.Printing.VotePrintDocument.Header7"),printConfiguration.getTextHeader7(),vHeaderParams);
	}

	addCustomAttributesHeader(vote);
}

void VotePrintDocument::setBallotTitle( const Ballot & ballot)
{
    if (printConfiguration.getShowBallotLines())
    {
        this->NewTextBlock(_textOptionGeneric);
        Glib::ustring line = N_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineBallotNameBegin");

        if (!line.empty() && line != " ")
        {
            this->DrawString(line, true);
        }
    }

    if (printConfiguration.getTextBallotName().getVisible())
    {
        DocumentTextOptions textOptionBallotTitle =
                TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(
                printConfiguration.getTextBallotName());

        Glib::ustring strBallotTitle = getResource(ballot.getTitle_key());

        this->NewTextBlock(textOptionBallotTitle);

        if (!strBallotTitle.empty() && strBallotTitle != " ")
        {
        	this->DrawString(strBallotTitle, true);
        }
    }

    if (printConfiguration.getShowBallotLines())
    {
        this->NewTextBlock(_textOptionGeneric);
        Glib::ustring line = N_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineBallotNameEnd");

        if (!line.empty() && line != " ")
        {
            this->DrawString(line, true);
        }
    }
}

void VotePrintDocument::PrintVote(const Vote::Vote & vote )
{
	translateText();
	setTopVote(vote);
	setCenterVote(vote);
	setBlankSpaceVote();
	setBottomVote(vote);
}

void VotePrintDocument::setTopVote(const Vote::Vote & vote)
{
	QRCodePrintingModeType qr_print_mode = printConfiguration.getQRCodePrintingMode();

	if (qr_print_mode == QRCodePrintingModeType::CONFIGURATION_IMAGE_BASED)
	{
		if((printConfiguration.getQRcodePosition() == QRcodePosition::CONFIGURATION_TOP_ALL) && showBarCode)
		{
			this->DrawImage(pixbufBarCode,Smartmatic::SAES::Printing::Center);
		}

		AddVoteHeader(vote);

		if((printConfiguration.getQRcodePosition() == QRcodePosition::CONFIGURATION_BOTTOM_HEADER) && showBarCode)
		{
			this->DrawImage(pixbufBarCode,Smartmatic::SAES::Printing::Center);
		}
	}
	else if (qr_print_mode == QRCodePrintingModeType::CONFIGURATION_COMMAND_BASED)
	{
		if((printConfiguration.getQRcodePosition() == QRcodePosition::CONFIGURATION_TOP_ALL) && showBarCode)
		{
			CommandPrintQRCode (vote);
		}

		AddVoteHeader(vote);

		if((printConfiguration.getQRcodePosition() == QRcodePosition::CONFIGURATION_BOTTOM_HEADER) && showBarCode)
		{
			CommandPrintQRCode (vote);
		}
	}
}

void VotePrintDocument::setCenterVote(const Vote::Vote & vote)
{
	std::list < Smartmatic::SAES::Voting::Election::Ballot > & sequenceBallot ( electoralConfiguration->getBallots() );
	std::list < Smartmatic::SAES::Voting::Election::Ballot >::iterator ballotIt;

    Vote::Vote::SSequence sequenceS = vote.getSelections ();
    Vote::Vote::SIterator its;

    int count = sequenceS.size();
    this->countContest = sequenceS.size();
    this->countLinesTotalList = 0;
	this->countLinesTotalBallotOption = 0;
	this->countContestName1 = 0;
	this->countContestName2 = 0;
	this->countContestName3 = 0;

	for (ballotIt = sequenceBallot.begin();
	   ballotIt != sequenceBallot.end();
	   ballotIt++)
	{
		setBallotTitle ((*ballotIt));

		Ballot_cards::Ballot_cardSequence  & ballotCardSequence ( electoralConfiguration->getElection()->getBallotCards( *ballotIt ).getBallot_card () );
		Ballot_cards::Ballot_cardIterator ballotCardIt;

		for (ballotCardIt = ballotCardSequence.begin();
		  ballotCardIt != ballotCardSequence.end();
		  ballotCardIt++)
		{
			Contests::ContestSequence & contestSequence ( electoralConfiguration->getElection()->getContests( *ballotCardIt ).getContest () );
			Contests::ContestIterator contestIt;

			for (its = sequenceS.begin();
				 its != sequenceS.end();
				 its++)
			{
				for (contestIt = contestSequence.begin();
					 contestIt != contestSequence.end();
					 contestIt++)
				{
					if ((*its).getContest() != (*contestIt).getCode()) continue;

					count--;
					setContest( vote, *contestIt, *its );
					setContestBlankSpace( (*contestIt).getCode(), count > 0 );

					if (count <= 0) return;
				}
			}
		}
	}
}

void VotePrintDocument::setSuperNull()
{

}

void VotePrintDocument::setContest( const Vote::Vote & vote, Contest & contest, const Vote::Selection & selection )
{
	setBallotOptionInfo(vote, contest, selection);
	setContestTitle(vote, contest);

	bool isQuestion = contest.getIs_question();

	this->countLinesList = 0;
	this->countLinesBallotOption = 0;
	this->viewPrincipalTitle = false;
	this->viewStandInTitle = false;

    if (selection.getBallotOptions().size() == 0)
	{
		DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextBlankVote());
		this->NewTextBlock(format);

		if (isQuestion)
		{
			this->DrawString(strNullReferendum,true);
		}
		else
		{
			this->DrawString(strNullVote,true);
		}

		this->countLinesList = 1;

		countLinesTotalList += maxLineListOptions[ contest.getCode() ];
		countLinesTotalBallotOption += maxLineBallotOptions[ contest.getCode() ];
	}
	else
	{
	    std::list < Ballot_option > & listBallotOptionPartyList = electoralConfiguration->getEligibleOptionsListByContestCode(contest.getCode());

		if (isQuestion)
		{
			std::list < Ballot_option > listBallotOptionStandIn;
			setTitleReferendum();
			setContestBallotOption(vote, contest, selection, listBallotOptionPartyList, listBallotOptionStandIn, isQuestion);
		}
		else
		{
			std::list < Ballot_option > & listBallotOptionPrincipal = electoralConfiguration->getEligibleOptionsPrincipalByContestCode(contest.getCode());
			std::list < Ballot_option > & listBallotOptionStandIn = electoralConfiguration->getEligibleOptionsStandInByContestCode(contest.getCode());

			setContestList(vote, contest, listBallotOptionPartyList, selection);
			setContestBallotOption(vote, contest, selection, listBallotOptionPrincipal, listBallotOptionStandIn, isQuestion);
		}

		countLinesTotalList += maxLineListOptions[ contest.getCode() ];
		countLinesTotalBallotOption += maxLineBallotOptions[ contest.getCode() ];
	}
}

void VotePrintDocument::setBallotOptionInfo( const Vote::Vote & vote, Contest & contest, const Vote::Selection & selection )
{
	strEligibleOptionBallotName = "";
	strBallotOptionPartyName = "";
	strBallotOptionPartyAbbreviation = "";

	Vote::Selection::BSequence seq = selection.getBallotOptions();
	Vote::Selection::BIterator itb;

	for (itb = seq.begin();
		 itb != seq.end();
		 itb++)
	{
		Voting::Election::Eligible_option & eligibleOption ( electoralConfiguration->getEligibleOptionFromBallotOptionCode ( contest.getCode(), (*itb) ) );
		Voting::Election::Ballot_options & ballots ( eligibleOption.getBallot_options() );

		if (ballots.getBallot_option().size() > 0)
		{
			Voting::Election::Ballot_option & ballotOption ( ballots.getBallot_option()[0] );
			strEligibleOptionBallotName = getResource(eligibleOption.getBallot_name_key());
			strBallotOptionPartyName = ElectionStringResourcesManager::Current()->getResource((ballotOption.getParty().getName() != NULL ? ballotOption.getParty().getName().get() : ""));
			strBallotOptionPartyAbbreviation = ElectionStringResourcesManager::Current()->getResource((ballotOption.getParty().getAbbreviation() != NULL ? ballotOption.getParty().getAbbreviation().get() : ""));
			return;
		}
	}
}

void VotePrintDocument::setContestTitle( const Vote::Vote & vote, Contest & contest )
{
    bool isSuperBlank =  vote.getLogicalVoterGroup() == SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();
	Contest_class & contestClass ( electoralConfiguration->getElection()->getContestClass(contest.getContest_class_code()) );

	strContestClassName = getResource( contestClass.getName_key() );
	strContestClassDescription = getResource( contestClass.getDescription_key() );
	strContestTitle = getResource(contest.getTitle_key());
	strContestAbstract = getResource(contest.getAbstract_key());
	strContestHelp = getResource(contest.getHelp_key());
	strContestBinaryRecovery =  "";

	if(vote.getMode() != Vote::VoteMode::VOTE_D)
	{
		map<std::string,std::string>::iterator contestBinaryIterator;
		contestBinaryIterator = recoveryVoteMap.find(contest.getCode());
		if(contestBinaryIterator != recoveryVoteMap.end())
		{
			strContestBinaryRecovery = contestBinaryIterator->second;
		}
	}

	int countBallot = vote.getSelections().size();

	// CustomAtributeValue
	customAttributeValue = GetCustomAttributeValue(contest, vote, contestClass);

	if(!customAttributeValue.empty() && customAttributeValue != " ")
	{
		customAttributeValue = getResource(customAttributeValue);
	}

	// Contest Name 1
	if(printConfiguration.getTextContestName1().getVisible())
	{
		Glib::ustring messageToCompose = "";

		if(isSuperBlank)
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName1SuperBlankVote");
		}
		else if (contest.getIs_question())
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName1Referendum");
		}
		else if (countBallot == 0)
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName1NullVote");
		}
		else
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName1NormalVote");
		}

		Glib::ustring strMessage = getComposeMessage(messageToCompose);

		if (!strMessage.empty() && strMessage != " ")
		{
			DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName1());
			this->NewTextBlock(textOptionContestTitle);
			this->DrawString(strMessage,true);
			countContestName1++;
		}
	}

	// Contest Name 2
	if(printConfiguration.getTextContestName2().getVisible())
	{
		Glib::ustring messageToCompose = "";

		if(isSuperBlank)
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName2SuperBlankVote");
		}
		else if (contest.getIs_question())
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName2Referendum");
		}
		else if (countBallot == 0)
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName2NullVote");
		}
		else
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName2NormalVote");
		}

		Glib::ustring strMessage = getComposeMessage(messageToCompose);

		if (!strMessage.empty() && strMessage != " ")
		{
			DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName2());
			this->NewTextBlock(textOptionContestTitle);
			this->DrawString(strMessage,true);
			countContestName2++;
		}
	}

	// Contest Name 3
	if(printConfiguration.getTextContestName3().getVisible())
	{
		Glib::ustring messageToCompose = "";

		if(isSuperBlank)
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName3SuperBlankVote");
		}
		else if (contest.getIs_question())
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName3Referendum");
		}
		else if (countBallot == 0 )
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName3NullVote");
		}
		else
		{
			messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ContestName3NormalVote");
		}

		Glib::ustring strMessage = getComposeMessage(messageToCompose);

		if (!strMessage.empty() && strMessage != " ")
		{
			DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName3());
			this->NewTextBlock(textOptionContestTitle);
			this->DrawString(strMessage,true);
			countContestName3++;
		}
	}
}

Glib::ustring VotePrintDocument::getComposeMessage( Glib::ustring messageToCompose )
{
	Glib::ustring strMessage = Glib::ustring::compose(
			messageToCompose,
			strContestClassName,
			strContestClassDescription,
			strContestTitle,
			strContestAbstract,
			strContestHelp,
			customAttributeValue,
			strEligibleOptionBallotName,
			strBallotOptionPartyName,
			strBallotOptionPartyAbbreviation);

	return Glib::ustring::compose(strMessage, strContestBinaryRecovery);
}

void VotePrintDocument::setContestBlankSpace( Glib::ustring contestCode, bool addEndSpace )
{
	//LayoutContestConfiguration & layout (this->printConfiguration.getLayoutContestConfiguration());

	if(layout.getCompleteWithSpaces())
	{
		int maxListContest = maxLineListOptions [ contestCode ];
		int maxBallotOptionContest = maxLineBallotOptions[ contestCode ];
/*
		logger->Debug("-----------------------------------------------------------------------------");

		{
			std::stringstream ss;
			ss << "ContestCode : " << contestCode;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "ViewPrincipalTitle : " << viewPrincipalTitle;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "ViewStandInTitle : " << viewStandInTitle;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "maxListContest : " << maxListContest;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "CountLinesList selected : " << countLinesList;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "MaxBallotOptionContest : " << maxBallotOptionContest;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "CountLinesBallotOption selected : " << countLinesBallotOption;
			logger->Debug(ss.str());
		}
*/
		if (!viewPrincipalTitle)
		{
			setContestTitlePrincipalSpace ();
		}

		if (!viewStandInTitle)
		{
			setContestTitleStandInSpace();
		}

		if (addEndSpace)
		{
			setContestEndSpace();
		}
		setContestListSpace(maxListContest - countLinesList);
		setContestBallotSpace(maxBallotOptionContest - countLinesBallotOption);
	}
}

void VotePrintDocument::setContestTitlePrincipalSpace( int count )
{
	if(printConfiguration.getTextPrincipalsMessage().getVisible())
	{
		DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextPrincipalsMessage());
		this->NewTextBlock(format);

		for (int i = 0;i < count;i++)
		{
			this->DrawString(_charPadding,true);
		}
	}
}

void VotePrintDocument::setContestTitleStandInSpace( int count )
{
	if(printConfiguration.getTextStandInMessage().getVisible())
	{
		DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextStandInMessage());
		this->NewTextBlock(format);
		for (int i = 0;i < count;i++)
		{
			this->DrawString(_charPadding,true);
		}
	}
}

void VotePrintDocument::setContestEndSpace(int count)
{
	for (int i = 0;i < count;i++)
	{
		// espacios al final de la contienda configurables
		static int spaceAdd = printConfiguration.getAddBlankSpaceFullContest();
		setContestBallotSpace (spaceAdd);
	}
}

void VotePrintDocument::setContestListSpace(int countList)
{
	if (printConfiguration.getTextParentOptionSelected().getVisible())
	{
		DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextParentOptionSelected());
		this->NewTextBlock(textOptionContestTitle);

		for(int iterador = 0;iterador < countList;iterador++)
		{
			this->DrawString(_charPadding,true);
		}
	}
}

void VotePrintDocument::setContestBallotSpace(int countBallot)
{
	this->NewTextBlock(_textOptionGeneric);

	for(int iterador = 0;iterador < countBallot;iterador++)
	{
		this->DrawString(_charPadding,true);
	}
}

void VotePrintDocument::setBlankSpaceVote()
{
	if(printConfiguration.getCompleteVoteWithSpaces())
	{
		int maxContest = electoralConfiguration->getMaxContestByVote();
		int maxCustomAttribute = electoralConfiguration->getMaxCustomAttributeByVote();
/*
		{
			std::stringstream ss;
			ss << "maxContest : " << maxContest;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "maxCustomAttribute : " << maxCustomAttribute;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "countContestName1 : " << countContestName1;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "countContestName2 : " << countContestName2;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "countContestName3 : " << countContestName3;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "maxBallotOptions : " << maxBallotOptions;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "countLinesTotalList : " << countLinesTotalList;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "countLinesTotalBallotOption : " << countLinesTotalBallotOption;
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "Line spaces principal title : " << (maxContest - countContest);
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "Line spaces stand in title : " << (maxContest - countContest);
			logger->Debug(ss.str());
		}
		{
			std::stringstream ss;
			ss << "Line spaces ballot options : " << (maxBallotOptions - countLinesTotalBallotOption);
			logger->Debug(ss.str());
		}
*/
		// Contest Name 1
		if(printConfiguration.getTextContestName1().getVisible())
		{
			int count = (printConfiguration.getIsTextContestName1CustomAttribute() ? maxCustomAttribute : maxContest);

			DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName1());
			this->NewTextBlock(format);

			for (int i = 0 ; i < count - countContestName1;i++)
			{
				this->DrawString(_charPadding,true);
			}
		}

		// Contest Name 2
		if(printConfiguration.getTextContestName2().getVisible())
		{
			int count = (printConfiguration.getIsTextContestName2CustomAttribute() ? maxCustomAttribute : maxContest);

			DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName2());
			this->NewTextBlock(format);

			for (int i = 0 ; i < count - countContestName2;i++)
			{
				this->DrawString(_charPadding,true);
			}
		}

		// Contest Name 3
		if(printConfiguration.getTextContestName3().getVisible())
		{
			int count = (printConfiguration.getIsTextContestName3CustomAttribute() ? maxCustomAttribute : maxContest);

			DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextContestName3());
			this->NewTextBlock(format);

			for (int i = 0 ; i < count - countContestName3;i++)
			{
				this->DrawString(_charPadding,true);
			}
		}

		setContestTitlePrincipalSpace(maxContest - countContest);
		setContestTitleStandInSpace(maxContest - countContest);
		setContestEndSpace(maxContest - countContest);
		setContestListSpace((maxList * maxContest) - countLinesTotalList);
		setContestBallotSpace (maxBallotOptions - countLinesTotalBallotOption);
	}
}

void VotePrintDocument::setTitleReferendum()
{
	if(printConfiguration.getTextParentOptionSelected().getVisible())
	{
		if (!strTitleReferendum.empty() && strTitleReferendum != " ")
		{
			DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextParentOptionSelected());
			this->NewTextBlock(format);
			this->DrawString(strTitleReferendum,true);
			countLinesList++;
		}
	}
}

void VotePrintDocument::setContestList( const Vote::Vote & vote, Contest & contest, std::list < Ballot_option > & list, const Vote::Selection & selection )
{
	if(printConfiguration.getTextParentOptionSelected().getVisible())
	{
		Glib::ustring messageToCompose;
		messageToCompose = _("Smartmatic.SAES.Printing.VotePrintDocument.ParentOptionWasSelected");

		std::list < Ballot_option >::iterator it;

		Vote::Selection::BSequence seq = selection.getBallotOptions();
		Vote::Selection::BIterator itb;

		for (itb = seq.begin();
			 itb != seq.end();
			 itb++)
		{
			for(it = list.begin();
				it != list.end();
				it++)
			{
				if ((*it).getCode() != (*itb)) continue;

				Voting::Election::Eligible_option & eligibleOption ( electoralConfiguration->getEligibleOptionFromBallotOptionCode ( contest.getCode(), (*itb) ) );
				Voting::Election::Ballot_options & ballots ( eligibleOption.getBallot_options() );

				if (ballots.getBallot_option().size() > 0)
				{
					Voting::Election::Ballot_option & ballotOption ( ballots.getBallot_option()[0] );
					strEligibleOptionBallotName = ElectionStringResourcesManager::Current()->getResource(eligibleOption.getBallot_name_key());
					strBallotOptionPartyName = ElectionStringResourcesManager::Current()->getResource((ballotOption.getParty().getName() != NULL ? ballotOption.getParty().getName().get() : ""));
					strBallotOptionPartyAbbreviation = ElectionStringResourcesManager::Current()->getResource((ballotOption.getParty().getAbbreviation() != NULL ? ballotOption.getParty().getAbbreviation().get() : ""));

					Glib::ustring strMessage = getComposeMessage(messageToCompose);

					if (!strMessage.empty() && strMessage != " ")
					{
						DocumentTextOptions format = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextParentOptionSelected());
						this->NewTextBlock(format);
						strMessage = strParentOptionMessage + strMessage;
						this->DrawString(strMessage,true);
						countLinesList++;
					}
				}
			}
		}
	}
}

void VotePrintDocument::setContestBallotOption( const Vote::Vote & vote,
		Contest & contest,
		const Vote::Selection & selection,
		std::list < Ballot_option > & listBallotOptionPrincipal,
		std::list < Ballot_option > & listBallotOptionStandIn, bool isQuestion)
{
	try
	{
		//LayoutContestConfiguration & layout (this->printConfiguration.getLayoutContestConfiguration());

		Vote::Selection::BSequence sequenceB = selection.getBallotOptions();

		std::vector <Ballot_option > listBallotOptionSelected;
		std::vector < Ballot_option > listBallotOptionStandInSelected;

		if(sequenceB.size() != 0)
		{
			list< Ballot_option>::iterator pos;

			for (unsigned int var = 0; var < sequenceB.size(); ++var)
			{
				for(pos = listBallotOptionPrincipal.begin();
					pos != listBallotOptionPrincipal.end();
					pos++)
				{
					if(pos->getCode() == sequenceB[var])
					{
						listBallotOptionSelected.push_back(*pos);
						break;
					}
				}
			}

			for (unsigned int var = 0; var < sequenceB.size(); ++var)
			{
				for(pos = listBallotOptionStandIn.begin();
					pos != listBallotOptionStandIn.end();
					pos++)
				{
					if(pos->getCode() == sequenceB[var])
					{
						listBallotOptionStandInSelected.push_back(*pos);
						break;
					}
				}
			}

			//Getting Sorted for two columns vertical distribution
			if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_TRUNCATED)
			{
				std::vector <Ballot_option > listBallotOptionSelectedTemp;
				std::vector < Ballot_option > listBallotOptionStandInSelectedTemp;

				unsigned int principalsFirstHalf = listBallotOptionSelected.size();
				unsigned int standInFirstHalf = listBallotOptionStandInSelected.size();
				principalsFirstHalf = (principalsFirstHalf/2) + (principalsFirstHalf%2);
				standInFirstHalf = (standInFirstHalf/2) + (standInFirstHalf%2);

				for(unsigned int i=0; i<principalsFirstHalf; i++)
				{
					listBallotOptionSelectedTemp.push_back(listBallotOptionSelected[i]);
					if( (principalsFirstHalf + i) < listBallotOptionSelected.size())
					{
						listBallotOptionSelectedTemp.push_back(listBallotOptionSelected[principalsFirstHalf + i]);
					}
				}
				for(unsigned int i=0; i<standInFirstHalf; i++)
				{
					listBallotOptionStandInSelectedTemp.push_back(listBallotOptionStandInSelected[i]);
					if( (standInFirstHalf + i) < listBallotOptionStandInSelected.size())
					{
						listBallotOptionStandInSelectedTemp.push_back(listBallotOptionStandInSelected[standInFirstHalf + i]);
					}
				}
				listBallotOptionSelected = listBallotOptionSelectedTemp;
				listBallotOptionStandInSelected = listBallotOptionStandInSelectedTemp;
			}
		}

		// BALLOT OPTION
		//
		DocumentTextOptions textOptionBallotOption = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(layout.getTextBallotOption());

		if(printConfiguration.getLayoutBallotOptiontType() == ConfigurationVote::LayoutBallotOptiontTypeType::CONFIGURATION_SEPARATEPRINCIPALANDSTANDIN)
		{
			//The List should be printed separated

			//Principals
			if(printConfiguration.getTextPrincipalsMessage().getVisible())
			{
				Glib::ustring message;

				if(isQuestion)
				{
					message = strPrincipalTitleReferendum;
				}
				else if(listBallotOptionSelected.size() == 0)
				{
					message = strPrincipalNoSelectectedMessage;
				}
				else
				{
					message = strPrincipalMessage;
				}

				if (!message.empty() && message != " ")
				{
					DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextPrincipalsMessage());
					this->NewTextBlock(textOptionContestTitle);
					this->DrawString(message,true);
					viewPrincipalTitle = true; // bandera para indicar que el titulo de principal esta presente
				}
			}

			std::list<DocumentTextOptions> listDocumentTextOptions;

			if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_SIMPLE)
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}
			else
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}

			this->NewTextColunmsBlock(listDocumentTextOptions);
			setBallotOptions (contest, listBallotOptionSelected, layout, true, isQuestion);

			//Stand In
			if(printConfiguration.getTextStandInMessage().getVisible())
			{
				Glib::ustring message;

				if(isQuestion)
				{
					message = strStandInTitleReferendum;
				}
				else if(listBallotOptionStandInSelected.size() == 0)
				{
					message = strStandInNoSelectedMessage;
				}
				else
				{
					message = strStandInMessage;
				}

				if (!message.empty() && message != " ")
				{
					DocumentTextOptions textOptionContestTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(printConfiguration.getTextStandInMessage());
					this->NewTextBlock(textOptionContestTitle);
					this->DrawString(message,true);
					viewStandInTitle = true; // bandera para indicar que el titulo de suplente esta presente
				}
			}

			listDocumentTextOptions.clear();
			if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_SIMPLE)
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}
			else
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}

			this->NewTextColunmsBlock(listDocumentTextOptions);
			setBallotOptions (contest, listBallotOptionStandInSelected, layout, false, isQuestion);
		}
		else
		{
			std::list<DocumentTextOptions> listDocumentTextOptions;

			if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_SIMPLE)
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}
			else
			{
				listDocumentTextOptions.push_back (textOptionBallotOption);
				listDocumentTextOptions.push_back (textOptionBallotOption);
			}

			this->NewTextColunmsBlock(listDocumentTextOptions);

			setBallotOptions (contest, listBallotOptionSelected, layout, true, isQuestion);
			setBallotOptions (contest, listBallotOptionStandInSelected, layout, false, isQuestion);
		}
	}
	catch (...)
	{
		std::stringstream ss;
	    ss << "FATAL - Error contest not found.";
	    logger->Debug(ss.str());
	}
}

void VotePrintDocument::setBallotOptions(Contest & contest,
		std::vector < Ballot_option > & list,
		LayoutContestConfiguration & layout,
		bool isPrincipal,
		bool isQuestion)
{
	std::vector < Ballot_option >::iterator it;
	std::list < Glib::ustring > text;

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		Eligible_option eligibleOption =  electoralConfiguration->getEligibleOptionFromBallotOptionCode ( contest.getCode(), (*it).getCode() );

		Glib::ustring strEligibleOption = ElectionStringResourcesManager::Current()->getResource(eligibleOption.getBallot_name_key());
		Glib::ustring strBallotOptionCustomCode = Glib::ustring::format((*it).getTally_position());

		Glib::ustring str;

		if (isQuestion)
		{
			Glib::ustring strPartyName = getResource((*it).getParty().getName() != NULL ? (*it).getParty().getName().get() : "");

			str = Glib::ustring::compose(_("Smartmatic.SAES.Printing.VotePrintDocument.FormatReferendum"),
				  strBallotOptionCustomCode, strEligibleOption, strPartyName );
		}
		else
		{
		    str = ProcessTextBallotOption(isPrincipal, strBallotOptionCustomCode,strEligibleOption,_maxBallotOptionLastNameChars,_maxBallotOptionNameChars,_maxBallotOptionCodeChars);
		}

		text.push_back (str);

		if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_SIMPLE)
		{
			this->DrawString(str);
			countLinesBallotOption++; // contador de lineas impresas relacionadas a ballot options
		}
	}

	if(layout.getLayoutContestType() == Smartmatic::SAES::Configuration::LayoutContestType::CONFIGURATION_TRUNCATED)
	{
		this->DrawStrings(text);
		int elements = text.size();
		elements = (elements % 2 != 0 ? elements + 1 : elements);
		countLinesBallotOption += elements / 2; // contador de lineas impresas relacionadas a ballot options
	}
}

void VotePrintDocument::setBottomVote(const Vote::Vote & vote)
{
	this->NewTextBlock(_textOptionGeneric);
	this->DrawString(".",true);

	if((printConfiguration.getQRcodePosition() == QRcodePosition::CONFIGURATION_BOTTOM_ALL) && showBarCode)
	{
		this->DrawImage(pixbufBarCode,Smartmatic::SAES::Printing::Center);
	}

	this->NewTextBlock(_textOptionGeneric);


	switch(vote.getMode())
	{
	case Vote::VoteMode::VOTE_D:
		this->DrawString(strDemoEnd,true);
		break;

	case Vote::VoteMode::VOTE_R:
		this->DrawString(strRecoveryEnd,true);
		break;

	case Vote::VoteMode::VOTE_S:
		this->DrawString(strSimulatedEnd,true);
		break;

	case Vote::VoteMode::VOTE_O:
		break;
	}
}

Glib::ustring VotePrintDocument::ProcessTextBallotOption(bool principal, Glib::ustring code, Glib::ustring fullName, int maxLastNameChars, int maxNameChars, int maxCodeChars)
{
  Glib::ustring messageToCompose =  principal ?
      _("Smartmatic.SAES.Printing.VotePrintDocument.PrincipalFormat") :
      _("Smartmatic.SAES.Printing.VotePrintDocument.StandInFormat");

  int posCode = code.find(separatorName);

  Glib::ustring codeOut;
  if(posCode>=0)
    {
      codeOut = code.substr(posCode+1);
    }
  else
    {
      codeOut = code;
    }

  if((int)codeOut.length() > maxCodeChars)
    {
      int dif = codeOut.length() - maxCodeChars;
      codeOut = codeOut.substr(dif);
    }

  Glib::ustring lastName, name, initialname;

	std::vector <std::string> parts;
	StringUtils::split (fullName, separatorName, parts);

	if (parts.size() >= 1)
	{
		lastName = parts[0];
	}
	if (parts.size() >= 2)
	{
		name = parts[1];
	}
	if (parts.size() >= 3)
	{
		initialname = parts[2];
	}
	else
	{
		initialname = StringUtils::trim(name).substr(0, 1);
	}

  if(maxLastNameChars > 0)
    lastName= lastName.substr(0,maxLastNameChars);

  if(maxNameChars > 0)
    name =  name.substr(0,maxNameChars);

  Glib::ustring result = Glib::ustring::compose(messageToCompose,
      codeOut,
      lastName,
      name,
      initialname);

  return result;
}

void VotePrintDocument::getQRCodeData (const Vote::Vote & vote, SafeBuffer & dataOut)
{
	Voting::Vote::VoteWrapper::packVoteForQR(electoralConfiguration, vote, dataOut);
}

void VotePrintDocument::CommandPrintQRCode (const Vote::Vote & vote)
{
	Glib::RefPtr<Gdk::Pixbuf> backgroundImage;

	Smartmatic::System::SafeBuffer digest;
	getQRCodeData(vote, digest);

	Smartmatic::SAES::Configuration::QRCodeConfig config =
			SAESConfigurationManager::Current()->getQRCodeVoteConfig(digest.GetSize());

	int pixel_size = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();
	QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());

	logger->Debug("----------QRCodeConfig-----------");

	{
		std::stringstream ss;
		ss << "DataSize             : " << digest.GetSize();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "CorrectionModeQRCode : " << config.getCorrectionModeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "Pixel                : " << config.getSizeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "VersionQRCode        : " << config.getVersionQRCode();
		logger->Debug(ss.str());
	}

	if (digest.GetSize() > 0)
	{
		this->DrawQRCode (
				  digest
				, pixel_size
				, margin
				, correctionLevel
				, version
				// Image content
				, backgroundImage
				, Smartmatic::SAES::Printing::Center);
	}
}

Glib::RefPtr<Gdk::Pixbuf> VotePrintDocument::GetQRCodeVote(const Vote::Vote & vote)
{
    bool useBackGroundImage = printConfiguration.getUseBackgroundImageForQR();

    Smartmatic::System::SafeBuffer digest;
    getQRCodeData(vote, digest);

    Smartmatic::SAES::Configuration::QRCodeConfig config =
            SAESConfigurationManager::Current()->getQRCodeVoteConfig(digest.GetSize());

	Glib::RefPtr<Gdk::Pixbuf> pixBuf;

	int pixelSize = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();
	QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());

	logger->Debug("----------QRCodeConfig-----------");

	{
		std::stringstream ss;
		ss << "DataSize             : " << digest.GetSize();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "CorrectionModeQRCode : " << config.getCorrectionModeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "Pixel                : " << config.getSizeQRCode();
		logger->Debug(ss.str());
	}
	{
		std::stringstream ss;
		ss << "VersionQRCode        : " << config.getVersionQRCode();
		logger->Debug(ss.str());
	}

	if (digest.GetSize() == 0)
	{
		return pixBuf;
	}

	Glib::RefPtr<Gdk::Drawable> drwptr;
	gint width(0);
	gint height(0);

	try
	{
		Glib::RefPtr<Gdk::Bitmap> bitmap(QREncoding::GenerateSymbol((guchar*)digest.GetData(),digest.GetSize(),pixelSize,margin,correctionLevel,version));
		bitmap->get_size(width,height);
		drwptr = bitmap;
	}
	catch(QREncodingException & ex)
	{
		std::stringstream ss;
		ss << "ERROR - " <<ex.what();
		logger->Debug(ss.str());
	}

	pixBuf =  Gdk::Pixbuf::create(drwptr,0,0,width,height);

	if(useBackGroundImage)
	{
		Smartmatic::Graphics::Image::PixbufComposer::ComposePosition position;

		switch((PositionImage)printConfiguration.getPositionImageInBackgroundQR())
		{
		  case PositionImage::CONFIGURATION_TOP_LEFT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::TOP_LEFT;
			  break;
		  case PositionImage::CONFIGURATION_TOP_CENTER:
			  position = Smartmatic::Graphics::Image::PixbufComposer::TOP_CENTER;
			  break;
		  case PositionImage::CONFIGURATION_TOP_RIGHT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::TOP_RIGHT;
			  break;
		  case PositionImage::CONFIGURATION_MIDDLE_LEFT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::MIDDLE_LEFT;
			  break;
		  case PositionImage::CONFIGURATION_MIDDLE_CENTER:
			  position = Smartmatic::Graphics::Image::PixbufComposer::MIDDLE_CENTER;
			  break;
		  case PositionImage::CONFIGURATION_MIDDLE_RIGHT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::MIDDLE_RIGHT;
			  break;
		  case PositionImage::CONFIGURATION_BOTTOM_LEFT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::BOTTOM_LEFT;
			  break;
		  case PositionImage::CONFIGURATION_BOTTOM_CENTER:
			  position = Smartmatic::Graphics::Image::PixbufComposer::BOTTOM_CENTER;
			  break;
		  case PositionImage::CONFIGURATION_BOTTOM_RIGHT:
			  position = Smartmatic::Graphics::Image::PixbufComposer::BOTTOM_RIGHT;
			  break;
		  default:
			  position = Smartmatic::Graphics::Image::PixbufComposer::RANDOM;
			  break;
		}

		std::string bkFilename = Smartmatic::Environment::ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/qrbkground.bmp");
		if(bkFilename.size() > 0 &&  Smartmatic::System::IO::File::canOpenFile(bkFilename))
		{
		  Glib::RefPtr<Gdk::Pixbuf> backGround = Gdk::Pixbuf::create_from_file(bkFilename);
		  pixBuf = Smartmatic::Graphics::Image::PixbufComposer::compose(backGround,pixBuf, position);
		}
	}

	return pixBuf;
}

void VotePrintDocument::addCustomAttributesHeader(const Smartmatic::SAES::Voting::Vote::Vote & vote )
{
  Glib::ustring logicalVoterGroupCode = vote.getLogicalVoterGroup ();

  Logical_voter_group lvg;

  try
  {
      lvg = electoralConfiguration->getVotingDevice()->getLogicalVoterGroup( logicalVoterGroupCode );
  }
  catch (const std::exception & e)
  {
	  std::stringstream ss;
      ss << "ERROR - " <<e.what();
      logger->Debug(ss.str());
      return;
  }

  std::list < Custom_attribute > customAttributes = electoralConfiguration->getVotingDevice()->getCustomAttributeList(lvg);

  list<Custom_attribute>::iterator itAtt;

  for (itAtt=customAttributes.begin(); itAtt!=customAttributes.end(); itAtt++)
  {
      list<Custom_attribute_definition>::iterator itDefinitions;

      for(itDefinitions = customAttributeDefinition.begin(); itDefinitions != customAttributeDefinition.end(); itDefinitions++)
      {
          if((*itDefinitions).getCode() == (*itAtt).getCode())
          {
              Glib::ustring messageToCompose =  N_("Smartmatic.SAES.Printing.VotePrintDocument.CustomAttributeHeader");
              
			  if(!messageToCompose.empty() && messageToCompose != " ")
			  {
	 			  this->NewTextBlock(_textOptionGeneric);
		          Glib::ustring CustomAttributeMessage = Glib::ustring::compose(messageToCompose,
		        		  getResource((*itDefinitions).getName_key()),
		        		  getResource((*itDefinitions).getDescription_key()),
		        		  getResource((*itAtt).getValue()));

		          if (!CustomAttributeMessage.empty() && CustomAttributeMessage != " ")
		          {
		        	  this->DrawString(CustomAttributeMessage,true);
		          }
			  }
          }
      }
  }
}


Glib::ustring VotePrintDocument::GetCustomAttributeValue(
		const Contest & contest,
		const Vote::Vote & vote,
		const Contest_class & contestClass)
{
  Glib::ustring customAttributeValue = "";

  Glib::ustring contestClassCode = contest.getContest_class_code ();

  if (contestClass.getCustom_code() == NULL)
  {
	  return customAttributeValue;
  }

  Glib::ustring customCodeContestClass = contestClass.getCustom_code().get();

  Logical_voter_groups logicalVoterGroups = electoralConfiguration->getVotingDevice()->getLogicalVoterGroups();

  Custom_attribute_definitions CustomAttributeDefinitions;

  if(logicalVoterGroups.getCustom_attribute_definitions().present())
  {
	  CustomAttributeDefinitions = logicalVoterGroups.getCustom_attribute_definitions().get();
  }
  else
  {
	  return customAttributeValue;
  }

  Custom_attribute_definitions::Custom_attribute_definitionSequence CustomAttributeDefinitionSequence = CustomAttributeDefinitions.getCustom_attribute_definition();

  Glib::ustring logicalVoterGroupCode = vote.getLogicalVoterGroup ();

  if(logicalVoterGroupCode == SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode())
  {
      return customAttributeValue;
  }

  Logical_voter_group lvg;

  try
  {
      lvg = electoralConfiguration->getVotingDevice()->getLogicalVoterGroup( logicalVoterGroupCode );
  }
  catch (const std::exception & e)
  {
      return customAttributeValue;
  }

  Custom_attributes customAttributes = lvg.getCustom_attributes ().get();
  Custom_attributes::Custom_attributeSequence & customAttributeSequence (customAttributes.getCustom_attribute () );

  int sizeCustomAttributeSequence = customAttributeSequence.size();
  int	SizeCustomAttributeDefinitionSequence = CustomAttributeDefinitionSequence.size();

  for(int i = 0; i<SizeCustomAttributeDefinitionSequence;i++)
    {
      if(CustomAttributeDefinitionSequence[i].getCode() == customCodeContestClass)
        {

          for(int j = 0 ;j<sizeCustomAttributeSequence;j++)
            {
              if(CustomAttributeDefinitionSequence[i].getCode() == customAttributeSequence[j].getCode())
                {
                  if(CustomAttributeDefinitionSequence[i].getValue().size()>1)
                    {
                      customAttributeValue.append(customAttributeSequence[j].getValue());
                    }
                  break;
                }
            }
          break;
        }
    }

  return customAttributeValue;
}

void VotePrintDocument::AddFinalSpaces()
{


}

void VotePrintDocument::calculateMax(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
{
	LayoutContestConfiguration & layout (SAESConfigurationManager::Current()->getLayoutContestConfiguration());
	maxBallotOptions = electoralConfiguration->getMaxBallotOptionsByVote();

	switch (layout.getLayoutContestType())
	{
		case LayoutContestType::CONFIGURATION_SIMPLE:
			maxLineBallotOptions = electoralConfiguration->getMaxBallotOptionByContestCode();
			calculateMaxBySimpleLayout(electoralConfiguration);
			break;

		case LayoutContestType::CONFIGURATION_TRUNCATED:
			maxLineBallotOptions = electoralConfiguration->getMaxBallotOptionByContestCode();
			calculateMaxByTruncateLayout(electoralConfiguration);
			break;

		case LayoutContestType::CONFIGURATION_SELECTED:
		case LayoutContestType::CONFIGURATION_VERTICAL:
			break;
	}

}

void VotePrintDocument::calculateMaxBySimpleLayout(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
{
	logger->Debug("Start calculate max by simple layout");

    try
    {
    	std::map < std::string, int >::iterator it;

    	for ( it = maxLineBallotOptions.begin();
             it != maxLineBallotOptions.end();
             it++)
    	{
    		Glib::ustring contestCode = (*it).first;

            std::list < Smartmatic::SAES::Voting::Election::Party > & partys = electoralConfiguration->getListPartyByContestCode(contestCode);
            std::list < Smartmatic::SAES::Voting::Election::Party >::iterator itp;

            int mList = 0;

            for (itp = partys.begin();
         		itp != partys.end();
         		itp++)
            {
         	   Glib::ustring partyCode = (*itp).getCode();
         	   int countList;

         	   countList = electoralConfiguration->getCountListBallotOptionByContestParty(contestCode, partyCode);

         	   if (countList > mList)
         	   {
         		   mList = countList;
         	   }

         	   if (countList > maxList)
         	   {
         		   maxList = countList;
         	   }
            }

            maxLineListOptions[contestCode] = mList;
            maxLineBallotOptions[contestCode] -= mList;
    	}
    }
    catch(ElectionException & ex)
    {
	   std::stringstream ss;
	   ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << ex.what();
	   logger->Debug(ss.str());
    }

    logger->Debug("End calculate max by simple layout");
}

void VotePrintDocument::calculateMaxByTruncateLayout(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
{
	logger->Debug("Start calculate max by truncate layout");
	maxBallotOptions = 0;

    try
    {
    	std::map < std::string, int >::iterator it;

       for ( it = maxLineBallotOptions.begin();
             it != maxLineBallotOptions.end();
             it++)
       {
    	   Glib::ustring contestCode = (*it).first;

           std::list < Smartmatic::SAES::Voting::Election::Party > & partys = electoralConfiguration->getListPartyByContestCode(contestCode);
           std::list < Smartmatic::SAES::Voting::Election::Party >::iterator itp;

           int value = maxLineBallotOptions[contestCode];
           int mList = 0;
           bool found = false;

           for (itp = partys.begin();
        		itp != partys.end();
        		itp++)
           {
        	   Glib::ustring partyCode = (*itp).getCode();
        	   int countList, countPrincipal, countStandIn;
        	   int total;

        	   electoralConfiguration->getCountBallotOptionByContestParty(contestCode, partyCode, countList, countPrincipal, countStandIn);

        	   total = countList + countPrincipal + countStandIn;

        	   if (countList > mList)
        	   {
        		   mList = countList;
        	   }

         	   if (countList > maxList)
         	   {
         		   maxList = countList;
         	   }

        	   if ( !found && value == total && countPrincipal % 2 != 0 && countStandIn % 2 != 0)
        	   {
        		   // ambos elementos son impares, por lo que para esta configuracion generan una nueva linea
        		   value++;
        		   found = true;
        	   }
           }

           maxLineListOptions[contestCode] = mList;

           value -= mList;
           value = (value % 2 != 0 ? value + 1 : value);

           maxLineBallotOptions[contestCode] = value / 2;
       }

       //Calculo contest group mas grande para obtener la cantidad maxima de ballot options linea a ser impresos

       std::list <Smartmatic::SAES::Voting::Election::Contest_group> & contestGroups ( electoralConfiguration->getContestGroups());
       std::list <Smartmatic::SAES::Voting::Election::Contest_group>::iterator c;

	   for (c = contestGroups.begin ();
			c != contestGroups.end ();
			++c)
	   {
		   Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeSequence & seq( (*c).getContest_code() );
		   Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeIterator itseq;

		   int max = 0;

		   for (itseq = seq.begin();
				itseq != seq.end();
				itseq++)
		   {
			   max += maxLineBallotOptions[(*itseq)];
		   }

		   if (max > maxBallotOptions)
		   {
			   maxBallotOptions = max;
		   }
	   }

    }
    catch(ElectionException & ex)
    {
	   std::stringstream ss;
	   ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << ex.what();
	   logger->Debug(ss.str());
    }

    logger->Debug("End calculate max by truncate layout");
}

void VotePrintDocument::translateText()
{
	bool found = false;
	clearText();

	if (isMultiLanguage)
	{
		separatorLanguage = printConfiguration.getMultiLanguageConfiguration().getSeparator();

		Smartmatic::SAES::Voting::Election::Languages & languages (electoralConfiguration->getLanguages());
		Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

		if(languages.getLanguage().size() > 1)
		{
			std::string previousLanguage;
			std::string previousCountry;

			SetLanguageFunctionality::getCurrentLanguageCountry ( previousLanguage, previousCountry );

			found = true;
			Glib::ustring separator = separatorLanguage;
			separatorLanguage = "";

			for (it = languages.getLanguage().begin();
					it != languages.getLanguage().end();
					it++)
			{
				SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry((*it).getLanguage(), (*it).getCountry());
				concatenateText();
				separatorLanguage = separator;
			}

			SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(previousLanguage, previousCountry);
		}
	}

	if (!found)
	{
		separatorLanguage = "";
		concatenateText();
	}
}

void VotePrintDocument::clearText()
{
	strDemoTitle = "";
	strRecoveryTitle = "";
	strSimulatedTitle = "";

	strDemoEnd = "";
	strRecoveryEnd = "";
	strSimulatedEnd = "";

	strNullReferendum = "";
	strNullVote = "";
	strTitleReferendum = "";

	strParentOptionMessage = "";
	strParentOptionWasSelected = "";

	strPrincipalTitleReferendum = "";
	strPrincipalNoSelectectedMessage = "";
	strPrincipalMessage = "";

	strStandInTitleReferendum = "";
	strStandInNoSelectedMessage = "";
	strStandInMessage = "";
}

void VotePrintDocument::concatenateText()
{
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.DemoTitle"), strDemoTitle);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.RecoveryTitle"), strRecoveryTitle);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.SimulatedTitle"), strSimulatedTitle);

	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.DemoEnd"), strDemoEnd);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.RecoveryEnd"), strRecoveryEnd);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.SimulatedEnd"), strSimulatedEnd);

	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.NullReferendum"), strNullReferendum);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.NullVote"), strNullVote);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.TitleReferendum"), strTitleReferendum);

	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.ParentOptionMessage"), strParentOptionMessage);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.ParentOptionWasSelected"), strParentOptionWasSelected);

	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.PrincipalTitleReferendum"), strPrincipalTitleReferendum);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.PrincipalNoSelectectedMessage"), strPrincipalNoSelectectedMessage);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.PrincipalMessage"), strPrincipalMessage);

	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.StandInTitleReferendum"), strStandInTitleReferendum);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.StandInNoSelectedMessage"), strStandInNoSelectedMessage);
	concatenateText(_("Smartmatic.SAES.Printing.VotePrintDocument.StandInMessage"), strStandInMessage);
}

void VotePrintDocument::concatenateText(Glib::ustring text, Glib::ustring & result)
{
	if (isMultiLanguage)
	{
		result += ((text.empty() || text == " ") ? "" : (separatorLanguage + text));
	}
	else
	{
		result = text;
	}
}

Glib::ustring VotePrintDocument::getResource(Glib::ustring key)
{
	Glib::ustring text;
	bool found = false;

	if (isMultiLanguage)
	{
		Smartmatic::SAES::Voting::Election::Languages & languages (electoralConfiguration->getLanguages());
		Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & langSequence (languages.getLanguage());
		Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

		if(langSequence.size() > 1)
		{
			found = true;

			Glib::ustring separator = separatorLanguage;
			separatorLanguage = "";

			for (it = langSequence.begin();
					it != langSequence.end();
					it++)
			{
				Glib::ustring temp = ElectionStringResourcesManager::Current()->getResource(key, (*it).getCustom_code());
				text += separatorLanguage + temp.substr(0, maxCharByLanguage);
				separatorLanguage = separator;
			}
		}
	}

	if (!found)
	{
		separatorLanguage = "";
		text = ElectionStringResourcesManager::Current()->getResource(key);
	}

	return text;
}
