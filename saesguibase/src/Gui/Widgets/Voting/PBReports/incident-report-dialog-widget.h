/**
 * @file	incident-report-dialog-widget.h
 *
 * @brief	Declares the incident report dialog widget class.
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

#ifndef _INCIDENT_REPORT_DIALOG_WIDGET_H_
#define _INCIDENT_REPORT_DIALOG_WIDGET_H_

#include <gtkmm.h>
#include "Widgets/smartmatic-entry.h"
#include "Widgets/smartmatic-entry-date-time.h"
#include <Voting/PBReports/incident-report-schema.hxx>
#include "Gui/Widgets/id-card-widget.h"
#include <Widgets/SmartmaticTextView.h>

namespace Smartmatic
{
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
						/**
						 * @brief	Incident report dialog widget. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class IncidentReportDialogWidget : public Gtk::Table
						{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							IncidentReportDialogWidget();

							/**
							 * @brief	Constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	report	The report.
							 */

							IncidentReportDialogWidget(Smartmatic::SAES::Voting::PBReports::Report report);

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~IncidentReportDialogWidget();

							/**
							 * @brief	Sets the parameters.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	report  	The report to set.
							 */

							void SetParams(Smartmatic::SAES::Voting::PBReports::Report report);

							/**
							 * @brief	Gets the parameters.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param [in,out]	report  	The report to get.
							 */

							void GetParams(Smartmatic::SAES::Voting::PBReports::Report& report);

							/**
							 * @brief	Cleans this object.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void Clean();

							/**
							 * @brief	Complete report.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	complete	true to complete.
							 */

							void CompleteReport(bool complete);

							/**
							 * @brief	Queries if we can be saved.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	true if it succeeds, false if it fails.
							 */

							bool CanBeSaved();

							/**
							 * @brief	Queries if we can be completed.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	true if it succeeds, false if it fails.
							 */

							bool CanBeCompleted();

							/**
							 * @brief	Sets a visualize mode.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	visualizeMode	true to enable visualize mode, false to disable it.
							 */

							void SetVisualizeMode(bool visualizeMode = true);

							/**
							 * @brief	Dispose of the widget.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */								 
							void dispose();

							/**
							 * @brief	Initializes the beid of the widget.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */
							void InitializeBEID();

							/**
							 * @brief	Compare times
							 *
							 * @author	Juan.Delgado
							 * @date	11/008/2011
							 *
							 * @param 	minor minor time
							 * @param 	mayor mayor time
							 * @return True if minor is minus than mayor
							 */

							static bool CompareTimes(struct tm minor, struct tm mayor);

							/**
							 * @brief	Getter methods for errorInHours
							 *
							 * @author	Juan.Delgado
							 * @date	11/008/2011
							 *
							 * @return 	errorInHours
							 */
							bool getErrorInHours();

						protected:

						private:
							bool errorInHours;	///< True if error in hours

							/**
							 * @brief	Initializes this object.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void Initialize();

							Smartmatic::SAES::GUI::Widgets::IDCardWidget* idWidget; ///< The identifier widget
					
							Smartmatic::GUI::Widgets::SmartmaticEntry* descEntry;   ///< The description entry
							Smartmatic::GUI::Widgets::SmartmaticEntry* nameTechEntry;   ///< The name technology entry
							Smartmatic::GUI::Widgets::SmartmaticEntry* lastnameTechEntry;   ///< The lastname technology entry
							Smartmatic::GUI::Widgets::SmartmaticEntry* activityTechEntry;   ///< The activity technology entry
							Smartmatic::GUI::Widgets::SmartmaticEntryDateTime* notificationDateEntry;   ///< The notification date entry
							Smartmatic::GUI::Widgets::SmartmaticEntryDateTime* personalDateEntry;   ///< The personal date entry
							Smartmatic::GUI::Widgets::SmartmaticEntryDateTime* incidentDateEntry;   ///< The incident date entry
							Smartmatic::GUI::Widgets::SmartmaticTextView* additionalText;  ///< The additional text
							
							Gtk::Label* descLabel;  ///< The description label
							Gtk::Label* nameTechLabel;  ///< The name technology label
							Gtk::Label* lastnameTechLabel;  ///< The lastname technology label
							Gtk::Label* activityTechLabel;  ///< The activity technology label
							Gtk::Label* additionalLabel;	///< The additional label
							Gtk::Label* notificationDateLabel;  ///< The notification date label
							Gtk::Label* personalDateLabel;  ///< The personal date label
							Gtk::Label* incidentDateLabel;  ///< The incident date label
							Gtk::Alignment* alignID;

							std::string customCode; ///< The custom code
							bool complete;  ///< true to complete

						

						};
					}

				}
			}
		}
	}
}

#endif // _INCIDENT_REPORT_DIALOG_WIDGET_H_
