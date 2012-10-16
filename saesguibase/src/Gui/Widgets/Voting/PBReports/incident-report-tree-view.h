/**
 * @file	incident-report-tree-view.h
 *
 * @brief	Declares the incident report tree view class.
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

#ifndef _INCIDENT_REPORT_TREE_VIEW_H_
#define _INCIDENT_REPORT_TREE_VIEW_H_

#include <gtkmm.h>
#include "Widgets/smartmatic-tree-view.h"
#include <Voting/PBReports/incident-report-schema.hxx>

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
						 * @brief	Incident report tree view. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class IncidentReportTreeView : public Smartmatic::GUI::Widgets::SmartmaticTreeView  
						{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							IncidentReportTreeView();

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~IncidentReportTreeView();

							/**
							 * @brief	Adds a row.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	report  	The report to add.
							 * @param	complete	true if it's complete.
							 */

							void AddRow(Smartmatic::SAES::Voting::PBReports::Report report);

							/**
							 * @brief	Gets a row.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	customCode			The custom code.
							 * @param [in,out]	report  	The report to get
							 * @param [in,out]	complete	Indicates if the report is complete.
							 *
							 * @return	true if it succeeds, false if it fails.
							 */

							bool GetRow(std::string customCode, Smartmatic::SAES::Voting::PBReports::Report& report);

							/**
							 * @brief	Modify row.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	report  	The report to modify.
							 * @param	complete	Indicates if the report is complete.
							 */

							void ModifyRow(Smartmatic::SAES::Voting::PBReports::Report report);

							/**
							 * @brief	Sets the reports.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	reports	The reports.
							 */

							void SetReports(Smartmatic::SAES::Voting::PBReports::Reports reports);
							
							//static Smartmatic::SAES::Voting::PBReports::DateTime ParseDateTime(std::string time);
							//static std::string ParseDateTime(Smartmatic::SAES::Voting::PBReports::DateTime time);

							/**
							 * @brief	Gets a ustring from struc time.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	structtm	The structtm.
							 *
							 * @return	The ustring from struc time.
							 */

							static Glib::ustring GetUstringFromStrucTm(struct tm structtm);

							/**
							 * @brief	Gets a string from date time.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	time	The time.
							 *
							 * @return	The string from date time.
							 */

							static std::string GetStringFromDateTime(Smartmatic::SAES::Voting::PBReports::DateTime time);

							/**
							 * @brief	Get a time structure from UString.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 * 
							 * @param	time	The time to convert
							 * 					
							 * @return	The time struct converted.
							 */

							static struct tm GetStructTmFromUstring(Glib::ustring time);

							/**
							 * @brief	Get time structure from DateTime. 
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 * 			
							 * @param	time	The time to convert.
							 * 					
							 * @return	The time struct converted.
							 */

							static struct tm GetStructTmFromDateTime(Smartmatic::SAES::Voting::PBReports::DateTime time);

							/**
							 * @brief	Gets a date time fom structure time.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	structtm	The time struct to convert.
							 *
							 * @return	The date time fom structure time.
							 */

							static Smartmatic::SAES::Voting::PBReports::DateTime GetDateTimeFomStructTm(struct tm structtm);

							/**
							 * @brief	Gets a date time from ustring.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	time	The time to convert
							 *
							 * @return	The date time from ustring.
							 */

							static Smartmatic::SAES::Voting::PBReports::DateTime GetDateTimeFromUstring(Glib::ustring time);

							/**
							 * @brief	Gets the custom code selected.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	The custom code selected.
							 */

							std::string GetCustomCodeSelected();
					
						protected:
							class IncidentReportTreeModel : 
								public Smartmatic::GUI::Widgets::SmartmaticTreeView::SmartmaticTreeModel
							{
							public:

								/**
								 * @brief	Default constructor.
								 *
								 * @author	Fsilva
								 * @date	28/04/2011
								 */

								IncidentReportTreeModel()
								{
									add(description); add(namesOfTechnicians); 
									add(activityOfTechnicians); add(complete);
									add(additionalObservations);
									add(notificationDate); add(personalArrivalDate);
									add(incidentSolutionDate);
									add(firstName); add(surName);
								}


								Gtk::TreeModelColumn<Glib::ustring> description;	///< The description
								Gtk::TreeModelColumn<Glib::ustring> namesOfTechnicians; ///< The names of technicians
								Gtk::TreeModelColumn<Glib::ustring> activityOfTechnicians;  ///< The activity of technicians
								Gtk::TreeModelColumn<Glib::ustring> additionalObservations; ///< The additional observations
								Gtk::TreeModelColumn<Glib::ustring> notificationDate;   ///< Date of the notification
								Gtk::TreeModelColumn<Glib::ustring> personalArrivalDate;	///< Date of the personal arrival
								Gtk::TreeModelColumn<Glib::ustring> incidentSolutionDate;   ///< Date of the incident solution
								Gtk::TreeModelColumn<bool> complete;	///< Indicates if it's completed
								Gtk::TreeModelColumn<Glib::ustring> firstName; ///< The first name of technician
								Gtk::TreeModelColumn<Glib::ustring> surName; ///< The surname of technician
							};

						private:

							IncidentReportTreeModel incidentReportTreeModel;	///< The incident report tree model

							/**
							 * @brief	Selection changed.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void SelectionChanged();

							std::string currentCustomCode;  ///< The current custom code
							std::vector <Gtk::TreeViewColumn *> treeViewColumns; ///< Tree view columns
						};
					}
				}
			}
		}
	}
}

#endif // _INCIDENT_REPORT_TREE_VIEW_H_
