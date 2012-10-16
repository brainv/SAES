/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
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

#include "Printing/TimeoutPrintDocument.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/voting-devices-schema.hxx"
#include "Printing/TranslatorTextConfiguration.h"

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

using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Resources;
using namespace std;

TimeoutPrintDocument::TimeoutPrintDocument (Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Glib::ustring voteCode)
{
	_electoralConfiguration =  electoralConfiguration;
	_voteCode = voteCode;
	_configurationTimeoutPrinting = (*SAESConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getConfigurationTimeout();
}

void TimeoutPrintDocument::PrintDoc()
{

	// Title
	if(_configurationTimeoutPrinting.getTextTitle().getVisible())
	{
		DocumentTextOptions textOptionTextTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(_configurationTimeoutPrinting.getTextTitle()); 
		this->NewTextBlock(textOptionTextTitle);
		this->DrawString(_("Smartmatic.SAES.Printing.TimeoutPrintDocument.PrintDoc_Title"),true);
	}
	this->DrawString("",true);
	// ELECTION NAME 
	if(_configurationTimeoutPrinting.getTextElectionName().getVisible())
	{	
		Smartmatic::SAES::Voting::Election::Election election = _electoralConfiguration->getElection()->getElection();
		Glib::ustring strElectionName = ElectionStringResourcesManager::Current()->getResource(election.getName_key());
		DocumentTextOptions textOptionElectionName = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(_configurationTimeoutPrinting.getTextElectionName()); 
		this->NewTextBlock(textOptionElectionName);
		this->DrawString(strElectionName,true);
	}

	this->DrawString(_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineSeparator"),true);
	
	// Voting booths
	if(_configurationTimeoutPrinting.getTextVotingBooth().getVisible())
	{	
		Voting_device device = _electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
		Voting_booths votingBooths =  _electoralConfiguration->getVotingDevice()->getVotingBooths(device);
		Voting_booths::Voting_boothIterator iteratorVotingBooths (votingBooths.getVoting_booth ().begin());
		const Voting_booth & votingBooth (*iteratorVotingBooths);
		Glib::ustring strVotingBooth = votingBooth.getCustom_code ();
		DocumentTextOptions textOptionVotingBooths = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(_configurationTimeoutPrinting.getTextVotingBooth()); 
		this->NewTextBlock(textOptionVotingBooths);
		this->DrawString(strVotingBooth,true);
	}
	this->DrawString("",true);
	// Vote Code
	if(_configurationTimeoutPrinting.getTextVoteID().getVisible())
	{
		DocumentTextOptions textOptionVoteId = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(_configurationTimeoutPrinting.getTextVoteID()); 
		this->NewTextBlock(textOptionVoteId);
		this->DrawString(_voteCode,true);
	}
	this->DrawString(_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineSeparator"),true);
	this->DrawString("",true);
	
	// Description
	if(_configurationTimeoutPrinting.getTextDescription().getVisible())
	{
		DocumentTextOptions textOptionTextDescription = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(_configurationTimeoutPrinting.getTextDescription()); 
		this->NewTextBlock(textOptionTextDescription);
		this->DrawString(_("Smartmatic.SAES.Printing.TimeoutPrintDocument.PrintDoc_Description"),true);
	}
}


void TimeoutPrintDocument::BeginPrint()
{
	
}

void TimeoutPrintDocument::EndPrint()
{
	
}
