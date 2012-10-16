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

#include "statistic-counter-register-widget.h"
#include <Voting/PBReports/StatisticGroup.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Voting/operation-status.h>
#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/label-configuration.h>

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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* StatisticCounterRegisterWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.StatisticCounterRegisterWidget",GETTEXT_PACKAGE);

StatisticCounterRegisterWidget::StatisticCounterRegisterWidget()
{
	static StatisticFunctionalityConfiguration config =
		SAESGUIConfigurationManager::Current()->GetStatisticFunctionalityConfiguration();

	int rowS = config.getRowsSpacing();
	int colS = config.getColumnsSpacing();

	vector<string> titles;

	statManager = MachineOperationManager::getInstance()->getStatisticManager();
	statManager->refreshAll();

	list<StatisticGroup*> statisticGroup = statManager->getStatisticGroup();
	list<StatisticGroup*>::iterator iter;

	LabelConfiguration titleLabelConf = SAESGUIConfigurationManager::Current()->GetTitleStatisticsLabelConfiguration();
	LabelConfiguration statLabelConf = SAESGUIConfigurationManager::Current()->GetStatsStatisticsLabelConfiguration();

	for(iter = statisticGroup.begin(); iter != statisticGroup.end(); iter++)
	{
		statWidget = manage(new StatisticCounterWidget((*iter)->getStatistics(), (*iter)->isVerticalFilling(), (*iter)->getPivot(), rowS, colS, statLabelConf));
		vectorStat.push_back(statWidget);

		titleStats = manage(new Label((*iter)->getInfo()));
		LabelConfiguration::SetLabelConfiguration(titleStats, titleLabelConf);

		VBox* vbox = manage(new VBox());
		vbox->pack_start(*titleStats, false, false, 10);
		vbox->pack_start(*statWidget, true, true);

		Alignment* statAlign = manage(new Alignment());
		statAlign->set(0.5, 0.5, 1.0, 1.0);
		statAlign->set_padding(0, 20, 20 ,20);
		statAlign->add(*vbox);

		string titleTable = (*iter)->getName();
		titles.push_back(titleTable);
		pagesWidget.push_back(statAlign);

	}

	nextButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.StatisticCounterRegisterWidget.ConfirmStatistics")));
	nextButton->signal_clicked().connect(sigc::mem_fun(*this, &StatisticCounterRegisterWidget::on_nextButton_clicked));
	nextButton->set_size_request(170, 50);

	HButtonBox* hbox = manage(new HButtonBox());
	hbox->pack_start(*nextButton);
	hbox->set_layout(BUTTONBOX_CENTER);

	align = manage(new Alignment());
	align->set(0.5, 0.5, 0, 1);
	align->add(*hbox);
	align->set_size_request(250, -1);
	align->show_all_children();
	align->set_no_show_all();

	notebook = new NotebookContainer(pagesWidget, titles);
	notebook->ShowTabs(true);
	notebook->AddBottomWidget(align);

	titleCheckTabs = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.StatisticCounterRegisterWidget.ViewAllTabs")));
	Pango::FontDescription fontSuperNull = titleCheckTabs->get_style()->get_font();
	fontSuperNull.set_size(16*Pango::SCALE);
	fontSuperNull.set_weight(Pango::WEIGHT_ULTRABOLD);
	titleCheckTabs->modify_font(fontSuperNull);
	titleCheckTabs->set_no_show_all();
	titleCheckTabs->set_size_request(-1, 40);

	VBox* vbox = manage(new VBox());
	vbox->pack_start(*titleCheckTabs,false,false);
	vbox->pack_start(*notebook);

	setWidget(vbox);

	if((int)statisticGroup.size() > 1)
		nextButton->set_sensitive(false);

	notebook->signal_all_pages_viewed().connect(sigc::mem_fun(*this, &StatisticCounterRegisterWidget::on_nextButton_setSensitive));

	StartCounter();
}



StatisticCounterRegisterWidget::~StatisticCounterRegisterWidget()
{

}

void StatisticCounterRegisterWidget::ShowNextButton()
{
	align->show();
	titleCheckTabs->show();
}

void StatisticCounterRegisterWidget::on_nextButton_setSensitive()
{
	nextButton->set_sensitive(true);
	titleCheckTabs->set_text(_("Smartmatic.SAES.GUI.Widgets.StatisticCounterRegisterWidget.NextToAdvance"));
}

void StatisticCounterRegisterWidget::on_nextButton_clicked()
{
	vector<StatisticCounterWidget*>::iterator iter;

	int post = 0;

	for(iter = vectorStat.begin(); iter != vectorStat.end(); iter++, post++)
	{
		if (!(*iter)->validateValues())
		{
			(*iter)->grab_focus();
			notebook->SetCurrentPage(post);
			titleCheckTabs->set_text(_("Smartmatic.SAES.GUI.Widgets.StatisticCounterRegisterWidget.FieldError"));
			return;
		}
	}

	if(Persist())
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &StatisticCounterRegisterWidget::on_done), 100);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &StatisticCounterRegisterWidget::UpdateLabel), 100);
	}
}

bool StatisticCounterRegisterWidget::RefreshStats()
{
	vector<StatisticCounterWidget*>::iterator iter;
	for(iter = vectorStat.begin(); iter != vectorStat.end(); iter++)
		(*iter)->PersistValues();

	statManager->refreshAll();

	for(iter = vectorStat.begin(); iter != vectorStat.end(); iter++)
	{
		(*iter)->refreshValues();
	}

	return true;
}

bool StatisticCounterRegisterWidget::Persist()
{
	bool persistOk = true;
	connector.disconnect();

	try
	{
		vector<StatisticCounterWidget*>::iterator iter;

		for(iter = vectorStat.begin(); iter != vectorStat.end(); iter++)
		{
			(*iter)->PersistValues();
		}

		statManager->persistence();
	}
	catch(Smartmatic::System::Exception::CryptoException & ex)
	{
		logger->Debug("StatisticCounterRegisterWidget CryptoException");
		persistOk = false;
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		logger->Debug("StatisticCounterRegisterWidget SignedException");
		persistOk = false;
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		logger->Debug("StatisticCounterRegisterWidget XmlException");
		persistOk = false;
	}
	catch(...)
	{
		logger->Debug("StatisticCounterRegisterWidget Unknow Exception");
		persistOk = false;
	}

	return persistOk;
}

void StatisticCounterRegisterWidget::on_done()
{
	m_done_signal.emit();
}

void StatisticCounterRegisterWidget::UpdateLabel()
{
	if(align->get_visible())
	{
		remove();
		Label* label = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.StatisticCounterRegisterWidget.ErrorMessage")));
		Pango::FontDescription fontTitle = label->get_style()->get_font();
		fontTitle.set_size(14*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		label->modify_font(fontTitle);
		setWidget(label);
		m_stop_signal.emit();
	}
}

void StatisticCounterRegisterWidget::StartCounter()
{
	bool hasCalculedStat = false;

	list<StatisticGroup*> statisticGroup = statManager->getStatisticGroup();
	list<StatisticGroup*>::iterator iterGroup;

	for(iterGroup = statisticGroup.begin(); iterGroup != statisticGroup.end(); iterGroup++)
	{
		list<StatisticWrapper*> statisticWrapper = (*iterGroup)->getStatistics();
		list<StatisticWrapper*>::iterator iterWrapper;

		for(iterWrapper = statisticWrapper.begin(); iterWrapper != statisticWrapper.end(); iterWrapper++)
		{
			if((*iterWrapper)->isCalculated())
				hasCalculedStat = true;

			if(hasCalculedStat)
				break;
		}
		if(hasCalculedStat)
			break;
	}

	if(hasCalculedStat)
	{
		connector = Glib::signal_timeout().connect(sigc::mem_fun(*this, &StatisticCounterRegisterWidget::RefreshStats), 1000);
	}
}

void StatisticCounterRegisterWidget::initialize()
{
	notebook->EnableMapRefresh();
}

void StatisticCounterRegisterWidget::dispose()
{

}
