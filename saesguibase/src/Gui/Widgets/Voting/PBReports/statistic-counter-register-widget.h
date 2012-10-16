/**
 * @file	statistic-counter-widget.h
 *
 * @brief	Declares the statistic counter widget class.
 */

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

#ifndef _STATISTIC_COUNTER_REGISTER_WIDGET_H_
#define _STATISTIC_COUNTER_REGISTER_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>
#include <Widgets/smartmatic-button.h>
#include <Voting/PBReports/StatisticManager.hxx>
#include <Gui/Widgets/Voting/PBReports/statistic-counter-widget.h>
#include <Widgets/RegisterWidget.hxx>
#include <Widgets/notebook-container.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					namespace PBReports
					{
						class StatisticCounterRegisterWidget : public Smartmatic::GUI::Widgets::WizardWidgetBase
						{
						public:

							StatisticCounterRegisterWidget();

							virtual ~StatisticCounterRegisterWidget();

							void ShowNextButton();

							bool Persist();
							/**
							 * @brief virtual method init
							 * @date 08/03/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 08/03/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();

							Glib::ustring GetWidgetName() { return "StatisticCounterRegisterWidget"; };

							//virtual bool StopWizard();

						protected:
							void on_nextButton_clicked();
							void on_nextButton_setSensitive();
						  
						private:
							sigc::connection connector;
							bool RefreshStats();

							void StartCounter();

							void on_done();
							void UpdateLabel();

							Gtk::Alignment* align;
							Smartmatic::GUI::Widgets::SmartmaticButton* nextButton;
							Smartmatic::SAES::Voting::PBReports::StatisticManager* statManager;
							Smartmatic::GUI::Widgets::NotebookContainer* notebook;
							//Smartmatic::GUI::Widgets::RegisterWidget * registerWidget; ///< register widget
							Gtk::Label* titleStats;
							Gtk::Label* titleCheckTabs;

							Smartmatic::SAES::GUI::Widgets::Voting::PBReports::StatisticCounterWidget* statWidget;  ///< The stat widget
							std::vector<Smartmatic::SAES::GUI::Widgets::Voting::PBReports::StatisticCounterWidget*> vectorStat;
							std::vector<Gtk::Widget*> pagesWidget;

							static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

						};
					}
				}
			}
		}
	}
}

#endif // _STATISTIC_COUNTER_REGISTER_WIDGET_H_
