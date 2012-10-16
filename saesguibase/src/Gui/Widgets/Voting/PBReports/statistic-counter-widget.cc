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

#include "statistic-counter-widget.h"
#include <Voting/PBReports/statistics-schema.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Widgets/NumericStatWidget.hxx>
#include <Widgets/BoolStatWidget.hxx>
#include <Widgets/StringStatWidget.hxx>
#include <Widgets/CustomStatWidget.hxx>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

StatisticCounterWidget::StatisticCounterWidget(std::list<StatisticWrapper*> statisticWrapper, bool vertical, int pivot, int rowSpacing, int colSpacings,
		Smartmatic::GUI::Configuration::LabelConfiguration labelConf)
: TableCenterWidget(false, true)
{
	this->statisticWrapper = statisticWrapper;
	setSpacings(rowSpacing, colSpacings);

	std::list<StatisticWrapper*>::iterator iter;

	int i = 0;
	int j = 0;

	for(iter = this->statisticWrapper.begin(); iter != this->statisticWrapper.end(); iter++)
	{
		IStatWidget * iwidget = NULL;

		switch ((*iter)->getType())
		{
			case StatisticElementType::CONFIGURATION_NUMERIC:
				iwidget = new NumericStatWidget((*iter)->getName(), (*iter)->getCode(), (*iter)->getRegex(), (*iter)->isMandatory(), (*iter)->getMax());
				break;
			case StatisticElementType::CONFIGURATION_BOOLEAN:
				iwidget = new BoolStatWidget((*iter)->getName(), (*iter)->getCode(), (*iter)->isMandatory());
				break;
			case StatisticElementType::CONFIGURATION_STRING:
				iwidget = new StringStatWidget((*iter)->getName(), (*iter)->getCode(), (*iter)->isMandatory(), (*iter)->getMax());
				break;
			case StatisticElementType::CONFIGURATION_CUSTOM:
				iwidget = new CustomStatWidget((*iter)->getName(), (*iter)->getCode(), (*iter)->getRegex(), (*iter)->isMandatory(), (*iter)->getMax(), (*iter)->getMask());
				break;
		}

		iwidget->setSize((*iter)->getWidth(), (*iter)->getHeight());

		CounterStatWidget* countWidget = manage(new CounterStatWidget(iwidget));
		countWidget->SetInsensitive(!(*iter)->isEdit());
		countWidget->AlignEntryText();
		countWidget->SetValue((*iter)->getValue());
		countWidget->SetLabelConfiguration(labelConf);

		mapWidgets[(*iter)->getCode()] = countWidget;

		put(countWidget, i, j, Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);

		if (vertical)
		{
			i++;

			if(i == pivot)
			{
				i = 0;
				j++;
			}
		}
		else
		{
			j++;

			if(j == pivot)
			{
				j = 0;
				i++;
			}
		}
	}

	show_all_children();
}

StatisticCounterWidget::~StatisticCounterWidget()
{
	mapWidgets.clear();
	clear();
}

void StatisticCounterWidget::ResetStats()
{

}

void StatisticCounterWidget::refreshValues()
{
	list<StatisticWrapper*>::iterator iter;

	for(iter = statisticWrapper.begin(); iter != statisticWrapper.end(); iter++)
	{
		if((*iter)->isCalculated())
		{
			std::string newValue = (*iter)->getValue();
			mapWidgets[(*iter)->getCode()]->SetValue(newValue);
		}
	}
}

bool StatisticCounterWidget::validateValues()
{
	list<StatisticWrapper*>::iterator iter;
	bool validate = true;

	for(iter = statisticWrapper.begin(); iter != statisticWrapper.end(); iter++)
	{
		if (!mapWidgets[(*iter)->getCode()]->validate())
		{
			validate = false;
			break;
		}
	}

	return validate;
}


void StatisticCounterWidget::PersistValues()
{
	list<StatisticWrapper*>::iterator iter;

	for(iter = statisticWrapper.begin(); iter != statisticWrapper.end(); iter++)
	{
		std::string newValue = mapWidgets[(*iter)->getCode()]->GetStatValue();
		(*iter)->setValue(newValue);
	}
}

void StatisticCounterWidget::SetStrings()
{
	strInstallationPackageNumberOfCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.InstallationPackageNumberOfCards");
	strInstallationPackageSparePrintingRolls = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.InstallationPackageSparePrintingRolls");
	strVoteMachines = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.VoteMachines");
	strTotalActivatedCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalActivatedCards");
	strTotalActivatedOfficialCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalActivatedOfficialCards");
	strTotalActivatedDemoCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalActivatedDemoCards");
	strTotalSecurityCopyCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalSecurityCopyCards");
	strTotalBelgianActivatedCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalBelgianActivatedCards");
	strTotalEuropeanActivatedCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalEuropeanActivatedCards");
	strTotalBelgianActivatedOfficialCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalBelgianActivatedOfficialCards");
	strTotalEuropeanActivatedOfficialCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalEuropeanActivatedOfficialCards");
	strTotalBelgianActivatedDemoCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalBelgianActivatedDemoCards");
	strTotalEuropeanActivateDemoCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalEuropeanActivateDemoCards");
	strTotalIssueCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalIssueCards");
	strTotalOfficialVotesReceived = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalOfficialVotesReceived");
	strTotalDemoVotesReceived = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalDemoVotesReceived");
	strTotalReadingIssuesVotesReceived = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalReadingIssuesVotesReceived");
	strTotalAnnulledVotesByRevelation = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalAnnulledVotesByRevelation");
	strTotalProxyVotes = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalProxyVotes");
	strTotalAnnulledVotes = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.TotalAnnulledVotes");
	strAdditionalHoursToVote = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.AdditionalHoursToVote");
	strVotersWhichDamagedCards = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.VotersWhichDamagedCards");
	strVotersWhichCouldNotSeeVotes = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterWidget.VotersWhichCouldNotSeeVotes");
}
