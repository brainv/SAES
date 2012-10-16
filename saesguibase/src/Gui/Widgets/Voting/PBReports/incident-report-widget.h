/**
 * @file	incident-report-widget.h
 *
 * @brief	Declares the incident report widget class.
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

#ifndef _INCIDENT_REPORT_WIDGET_H_
#define _INCIDENT_REPORT_WIDGET_H_

#include <gtkmm.h>
#include <Voting/PBReports/incident-report-wrapper.h>
#include "Gui/Widgets/Voting/PBReports/incident-report-dialog-widget.h"
#include "Gui/Widgets/Voting/PBReports/incident-report-tree-view.h"
#include "Widgets/smartmatic-button.h"
#include "Gui/Widgets/confirmation-delete-widget.h"

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
						/**
						 * @brief	Incident report widget. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class IncidentReportWidget : public Gtk::Frame
						{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							IncidentReportWidget();

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~IncidentReportWidget();

							/**
							 * @brief	Shows the dialog.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void ShowDialog();

							/**
							 * @brief	Shows the tree.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void ShowTree();

							/**
							 * @brief	Reports the selected.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	true if it succeeds, false if it fails.
							 */

							bool ReportSelected();

							/**
							 * @brief	Persist reports.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void PersistReports();

							/**
							 * @brief	Loads the reports.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void LoadReports();

							/**
							 * @brief	Dispose of the widget.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */								 
							void dispose();
						protected:
							void on_deleteAnswer_send(bool deleteReport);

							/**
							 * @brief	Handles add report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_addReportButton_clicked();

							/**
							 * @brief	Handles save report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_saveReportButton_clicked();

							/**
							 * @brief	Handles modify report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_modifyReportButton_clicked();

							/**
							 * @brief	Handles delete report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_deleteReportButton_clicked();

							/**
							 * @brief	Handles visualize report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_visualizeReportButton_clicked();

							/**
							 * @brief	Handles complete report button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_completeReportButton_clicked();

							/**
							 * @brief	Handles back button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_backButton_clicked();
							
							Smartmatic::GUI::Widgets::SmartmaticButton* addReportButton;	///< The add report button
							Smartmatic::GUI::Widgets::SmartmaticButton* saveReportButton;   ///< The save report button
							Smartmatic::GUI::Widgets::SmartmaticButton* modifyReportButton; ///< The modify report button
							Smartmatic::GUI::Widgets::SmartmaticButton* backButton; ///< The back button
							Smartmatic::GUI::Widgets::SmartmaticButton* completeReportButton;   ///< The complete report button
							Smartmatic::GUI::Widgets::SmartmaticButton* deleteReportButton; ///< The delete report button
							Smartmatic::GUI::Widgets::SmartmaticButton* visualizeReportButton;  ///< The visualize report button

							/**
							 * @brief	Sets the buttons visual.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	visual	true to visual.
							 */

							void SetButtonsVisual(bool visual);

							/**
							 * @brief	Shows back.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void ShowBack();

							/**
							 * @brief	Shows the message.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	message	The message.
							 */

							void ShowMessage(Glib::ustring message);

							Gtk::Alignment* treeAlign;  ///< The tree align
							Gtk::Alignment* dialogAlign;	///< The dialog align
							Gtk::Label* messageLabel;   ///< The message label
							
							IncidentReportDialogWidget* dialog; ///< The dialog
							IncidentReportTreeView* treeview;   ///< The treeview
							Gtk::ScrolledWindow* treeScroll; /// scroll widget
							Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper* incidentReportWrapper;  ///< The incident report wrapper

							bool isModified;	///< true if is modified

							/**
							 * @brief	Values that represent BackButtonEnum. 
							 */

							enum BackButtonEnum
							{
								BACKTOTREE,
								BACKTODIALOG
							};

							BackButtonEnum backTo;  ///< Enum that gets back to a specific position.

							Smartmatic::SAES::GUI::Widgets::ConfirmationDeleteWidget* deleteWidget;

							bool showDeleteConfirmation;

							void DeleteReport();
							Gtk::HBox* externalBox;
							Gtk::VButtonBox* buttonBox;
							Gtk::Alignment* buttonAlignment;

							static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

						};
					}
				}
			}
		}
	}
}

#endif // _INCIDENT_REPORT_WIDGET_H_
