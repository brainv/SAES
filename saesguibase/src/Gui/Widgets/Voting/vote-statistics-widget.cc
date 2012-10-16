/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "vote-statistics-widget.h"
#include <Voting/PBReports/statistics-schema.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <Operation/MachineOperationManager.hxx>
#include <Voting/PBReports/vote-statistics.h>
#include "Resources/election-string-resources-manager.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <System/Utils/StringUtils.hxx>

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
using namespace Gtk;
using namespace Gdk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::System::Utils;

VoteStatisticsWidget::VoteStatisticsWidget(
		VoteStatisticsWrapper* voteStats,
		Custom_attribute_definitions& cadefs,
		CountConfiguration & totalCountType,
		CountConfiguration & officialCountType)
{
	this->totalCountType = totalCountType;
	this->officialCountType = officialCountType;

	labelTitle = NULL;
	eventTitle = NULL;
	totalVoteCounter = NULL;
	officialVoteCounter = NULL;
	duplicateVoteCounter = NULL;

	this->voteStats = voteStats;
	vmCA.clear();
	pmCA.clear();
	vmMap.clear();
	pmMap.clear();
	
	int index = 0;
	int width = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getCounterWidth();
	int height = -1;
	int ypadding = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getCounterPadding();
	showVM = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getShowVotingMachineCustomAttribute();

	labelTitle = new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.VotesStatisticsTitle"));
	Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConf = SAESGUIConfigurationManager::Current()->GetVoteConsolidationStatisticsTitleLabelConfiguration();
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelTitle, labelTitleConf);

	eventTitle = new EventBox();
	eventTitle->add(*labelTitle);
	eventTitle->show_all_children ();

	Color selectedColor;
	ColorConfiguration colorTitleConf = SAESGUIConfigurationManager::Current()->getVoteConsolidationStatisticsTitleColor();
	selectedColor.set_rgb(colorTitleConf.getRed(), colorTitleConf.getGreen(), colorTitleConf.getBlue());
	eventTitle->modify_bg(Gtk::STATE_NORMAL, selectedColor);
	attach(*eventTitle, 0, 1, index, index + 1, SHRINK, SHRINK);
	index++;
	
	int maxSizeCount = 100;

	totalVoteCounter = new CounterStatWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalVotes"), maxSizeCount, true);
	totalVoteCounter->set_size_request(width, height);
	totalVoteCounter->AlignEntryText(0.5);
	totalVoteCounter->AlignLabel(0);
	totalVoteCounter->SetEntryWidth(60);
	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowTotalVotes())
	{
		attach(*totalVoteCounter, 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
		index++;
	}

	officialVoteCounter = new CounterStatWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalOfficialVotes"), maxSizeCount, true);
	officialVoteCounter->set_size_request(width, height);
	officialVoteCounter->AlignEntryText(0.5);
	officialVoteCounter->AlignLabel(0);
	officialVoteCounter->SetEntryWidth(60);
	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowOfficialVotes())
	{
		attach(*officialVoteCounter, 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
		index++;
	}

	duplicateVoteCounter = new CounterStatWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalDuplicateVotes"), maxSizeCount, true);
	duplicateVoteCounter->set_size_request(width, height);
	duplicateVoteCounter->AlignEntryText(0.5);
	duplicateVoteCounter->AlignLabel(0);
	duplicateVoteCounter->SetEntryWidth(60);
	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowDuplicatesVotes())
	{
		attach(*duplicateVoteCounter, 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
		index++;
	}
	
	for(unsigned int i = 0;i < cadefs.getCustom_attribute_definition().size();i++)
	{
		Glib::ustring caCode =ElectionStringResourcesManager::Current()->getResource(cadefs.getCustom_attribute_definition()[i].getCode());
		Glib::ustring caName = ElectionStringResourcesManager::Current()->getResource(cadefs.getCustom_attribute_definition()[i].getName_key());
		Glib::ustring caDesc = ElectionStringResourcesManager::Current()->getResource(cadefs.getCustom_attribute_definition()[i].getDescription_key());

		Glib::ustring labelText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

		if(cadefs.getCustom_attribute_definition()[i].getValue().size() > 1)
		{
			Label* label = new Label(labelText);
			label->set_size_request(width - 60, height);
				Pango::FontDescription fontTitle = label->get_style()->get_font();
				fontTitle.set_weight(Pango::WEIGHT_BOLD);
			label->modify_font(fontTitle);
			label->set_alignment(0.0, 0.5);
			vecLabels.push_back(label);
			attach(*label, 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND,0,ypadding);
			index++;

			label->set_line_wrap(true);
			label->set_justify(JUSTIFY_LEFT);

			for(unsigned int j = 0;j < cadefs.getCustom_attribute_definition()[i].getValue().size() ;j++)
			{
				Custom_attribute_definition caDef = cadefs.getCustom_attribute_definition()[i];
				string normalValue = caDef.getValue()[j];
				string resourceValue = ElectionStringResourcesManager::Current()->getResource(normalValue);

				if(caDef.getMachine_type() == Machine_type::VOTING_DEVICES_VM)
				{
					if(showVM)
					{
						vmCA.push_back(normalValue);
						vmMap[normalValue] = new CounterStatWidget(resourceValue, maxSizeCount, true);
						vmMap[normalValue]->set_size_request(width, height);
						vmMap[normalValue]->AlignEntryText(0.5);
						vmMap[normalValue]->AlignLabel(0);
						vmMap[normalValue]->SetEntryWidth(60);
						attach(*vmMap[normalValue], 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
						index++;
					}
				}
				else
				{
					pmCA.push_back(normalValue);
					pmMap[normalValue] = new CounterStatWidget(resourceValue, maxSizeCount, true);
					pmMap[normalValue]->set_size_request(width, height);
					pmMap[normalValue]->AlignEntryText(0.5);
					pmMap[normalValue]->AlignLabel(0);
					pmMap[normalValue]->SetEntryWidth(60);
					attach(*pmMap[normalValue], 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
					index++;
				}
			}
		}
		else
		{
			Custom_attribute_definition caDef = cadefs.getCustom_attribute_definition()[i];
			string normalValue = caDef.getValue()[0];

			if(caDef.getMachine_type() == Machine_type::VOTING_DEVICES_VM)
			{
				if(showVM)
				{
					vmCA.push_back(normalValue);
					vmMap[normalValue] = new CounterStatWidget(labelText, maxSizeCount, true);
					vmMap[normalValue]->set_size_request(width, height);
					vmMap[normalValue]->AlignEntryText(0.5);
					vmMap[normalValue]->AlignLabel(0);
					vmMap[normalValue]->SetEntryWidth(60);
					vmMap[normalValue]->SetWeight(Pango::WEIGHT_BOLD);
					attach(*vmMap[normalValue], 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
					index++;
				}
			}
			else
			{
				pmCA.push_back(normalValue);
				pmMap[normalValue] = new CounterStatWidget(labelText, maxSizeCount, true);
				pmMap[normalValue]->set_size_request(width, height);
				pmMap[normalValue]->AlignEntryText(0.5);
				pmMap[normalValue]->AlignLabel(0);
				pmMap[normalValue]->SetEntryWidth(60);
				pmMap[normalValue]->SetWeight(Pango::WEIGHT_BOLD);
				attach(*pmMap[normalValue], 0, 1, index, index + 1, FILL|~EXPAND, FILL|~EXPAND);
				index++;
			}
		}
	}

	show_all_children();
}

VoteStatisticsWidget::~VoteStatisticsWidget()
{
	if (labelTitle) delete labelTitle;
	if (eventTitle) delete eventTitle;
	if (totalVoteCounter) delete totalVoteCounter;
	if (duplicateVoteCounter) delete duplicateVoteCounter;
	if (officialVoteCounter) delete officialVoteCounter;

	vector<Label*>::iterator iter;

	for(iter = vecLabels.begin(); iter != vecLabels.end(); iter++)
	{
		Label* label = *iter;
		if(label) delete label;
	}
	
	std::map<string, CounterStatWidget*>::iterator iter2;
	for(iter2 = vmMap.begin(); iter2 != vmMap.end(); iter2++)
	{
		CounterStatWidget* count = (*iter2).second;
		if(count) delete count;
	}

	for(iter2 = pmMap.begin(); iter2 != pmMap.end(); iter2++)
	{
		CounterStatWidget* count = (*iter2).second;
		if(count) delete count;
	}
}

void VoteStatisticsWidget::Initialize()
{

}

std::string VoteStatisticsWidget::getValue(CountConfiguration::CountTypeSequence & seq)
{
	CountConfiguration::CountTypeIterator it;
	int total = 0;

	for (it = seq.begin();
		 it != seq.end();
		 it++)
	{
		switch (*it)
		{
			case CountTypeConfig::CONFIGURATION_TOTAL:
				total += voteStats->getTotalVotes();
				break;
			case CountTypeConfig::CONFIGURATION_OFFICIAL:
				total += voteStats->getOfficialVotes();
				break;
			case CountTypeConfig::CONFIGURATION_DEMO:
				total += voteStats->getDemoVotes();
				break;
			case CountTypeConfig::CONFIGURATION_RECOVERY:
				total += voteStats->getSecurityCopyVotes();
				break;
			case CountTypeConfig::CONFIGURATION_SIMULATE:
				total += voteStats->getSimulatedVotes();
				break;
		}
	}

	return StringUtils::intToString(total);
}

void VoteStatisticsWidget::RefreshStats()
{
	CountConfiguration::CountTypeSequence seq;

	std::string total = getValue(totalCountType.getCountType());
	std::string official = getValue(officialCountType.getCountType());

	totalVoteCounter->SetValue(total);
	officialVoteCounter->SetValue(official);

	std::string duplicatedVotes = StringUtils::intToString(voteStats->getDuplicatedVotes());
	duplicateVoteCounter->SetValue(duplicatedVotes);

	vector<VoteCounterByCA> vectorCounterCA;
	vectorCounterCA = voteStats->getVoteCountersByCA();
	vector<VoteCounterByCA>::iterator iter;

	for(iter = vectorCounterCA.begin(); iter != vectorCounterCA.end(); iter++)
	{
		string caValue = iter->getCAValue();

		std::map<std::string, Smartmatic::GUI::Widgets::CounterStatWidget*>::iterator iterMap;
		iterMap = vmMap.find(caValue);

		if(iterMap != vmMap.end())
		{
			std::string value = StringUtils::intToString(iter->getCounter());
			iterMap->second->SetValue(value);
		}
		else
		{
			iterMap = pmMap.find(caValue);
			if(iterMap != pmMap.end())
			{
				std::string value = StringUtils::intToString(iter->getCounter());
				iterMap->second->SetValue(value);
			}
			else
			{
			}
		}
	}
}

void VoteStatisticsWidget::SetSensitive(bool setSensitive)
{
	if(totalVoteCounter)
		totalVoteCounter->SetInsensitive(!setSensitive);

	if(duplicateVoteCounter)
		duplicateVoteCounter->SetInsensitive(!setSensitive);
	
	if(officialVoteCounter)
		officialVoteCounter->SetInsensitive(!setSensitive);

	std::map<string, CounterStatWidget*>::iterator iter2;
	for(iter2 = vmMap.begin(); iter2 != vmMap.end(); iter2++)
	{
		CounterStatWidget* count = (*iter2).second;
		count->SetInsensitive(!setSensitive);
	}

	for(iter2 = pmMap.begin(); iter2 != pmMap.end(); iter2++)
	{
		CounterStatWidget* count = (*iter2).second;
		count->SetInsensitive(!setSensitive);
	}
}
