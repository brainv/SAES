/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SmartcardRemovedPrintDocument.h"
#include "Voting/VotingDevice/voting-devices-schema.hxx"
#include "Printing/TranslatorTextConfiguration.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/voting-devices-schema.hxx"

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

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Resources;
using namespace std;

SmartcardRemovedPrintDocument::SmartcardRemovedPrintDocument (Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, 
                                                              Glib::ustring voteCode, int timesRemoved)
{
	this->electoralConfiguration =  electoralConfiguration;
	this->voteCode = voteCode;
	this->timesRemoved = timesRemoved;
	configurationSmartcardRemovedPrinting = (*SAESConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getConfigurationSmartcardRemoved();
}

void SmartcardRemovedPrintDocument::PrintDoc()
{

	// Title
	if(configurationSmartcardRemovedPrinting.getTextTitle().getVisible())
	{
		DocumentTextOptions textOptionTextTitle = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationSmartcardRemovedPrinting.getTextTitle()); 
		this->NewTextBlock(textOptionTextTitle);
		Glib::ustring toCompose = _("Smartmatic.SAES.Printing.SmartcardRemovedPrintDocument.PrintDoc_Title");
		stringstream ss;
		ss<<this->timesRemoved;
		Glib::ustring composed = Glib::ustring::compose(toCompose,ss.str());
		this->DrawString(composed,true);

	}
	this->DrawString("",true);
	// ELECTION NAME 
	if(configurationSmartcardRemovedPrinting.getTextElectionName().getVisible())
	{	
		Smartmatic::SAES::Voting::Election::Election election = electoralConfiguration->getElection()->getElection();
		Glib::ustring strElectionName = ElectionStringResourcesManager::Current()->getResource(election.getName_key());
		DocumentTextOptions textOptionElectionName = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationSmartcardRemovedPrinting.getTextElectionName()); 
		this->NewTextBlock(textOptionElectionName);
		this->DrawString(strElectionName,true);
	}

	this->DrawString(_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineSeparator"),true);
	
	// Voting booths
	if(configurationSmartcardRemovedPrinting.getTextVotingBooth().getVisible())
	{	
		Voting_device device = electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
		Voting_booths votingBooths =  electoralConfiguration->getVotingDevice()->getVotingBooths(device);
		Voting_booths::Voting_boothIterator iteratorVotingBooths (votingBooths.getVoting_booth ().begin());
		const Voting_booth & votingBooth (*iteratorVotingBooths);
		Glib::ustring strVotingBooth = votingBooth.getCustom_code ();
		DocumentTextOptions textOptionVotingBooths = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationSmartcardRemovedPrinting.getTextVotingBooth()); 
		this->NewTextBlock(textOptionVotingBooths);
		this->DrawString(strVotingBooth,true);
	}
	this->DrawString("",true);
	// Vote Code
	if(configurationSmartcardRemovedPrinting.getTextVoteID().getVisible())
	{
		DocumentTextOptions textOptionVoteId = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationSmartcardRemovedPrinting.getTextVoteID()); 
		this->NewTextBlock(textOptionVoteId);
		this->DrawString(voteCode,true);
	}
	this->DrawString(_("Smartmatic.SAES.Printing.VotePrintDocument.HorizontalLineSeparator"),true);
	this->DrawString("",true);
	
	// Description
	if(configurationSmartcardRemovedPrinting.getTextDescription().getVisible())
	{
		DocumentTextOptions textOptionTextDescription = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationSmartcardRemovedPrinting.getTextDescription()); 
		this->NewTextBlock(textOptionTextDescription);
		Glib::ustring toCompose = _("Smartmatic.SAES.Printing.SmartcardRemovedPrintDocument.PrintDoc_Description");
		stringstream ss;
		ss<<this->timesRemoved;
		Glib::ustring composed = Glib::ustring::compose(toCompose,ss.str());
		this->DrawString(composed,true);
	}
}

void SmartcardRemovedPrintDocument::BeginPrint()
{
	
}

void SmartcardRemovedPrintDocument::EndPrint()
{
	
}
