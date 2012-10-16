/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * trunk
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	LogPagingTreeViewWidget.h
 *
 * @brief	Declares the log paging tree view widget class.
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

#ifndef _LOGPAGINGTREEVIEWWIDGET_H_
#define _LOGPAGINGTREEVIEWWIDGET_H_

#include <gtkmm.h>
#include <Gui/Widgets/LogTreeViewWidget.h>
#include <Log/LogReader.h>
#include "Widgets/smartmatic-button.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	LogPagingTreeViewWidget
				 *
				 * @brief	Log paging tree view widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class LogPagingTreeViewWidget : public Gtk::Frame
				{
				public:

					/**
					 * @fn	LogPagingTreeViewWidget::LogPagingTreeViewWidget(Smartmatic::SAES::Log::LogReader * logReader);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	logReader	If non-null, the log reader.
					 */

					LogPagingTreeViewWidget(Smartmatic::SAES::Log::LogReader * logReader);

					/**
					 * @fn	virtual LogPagingTreeViewWidget::~LogPagingTreeViewWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					virtual ~LogPagingTreeViewWidget();

					void HidePrintingIndicator ();

					void SetPrinterMessage (const Glib::ustring& msg);

					void ShowPrintLabel ();
					void HidePrintLabel ();

					sigc::signal<void> signalPrint_detected;   ///< The signal print detected

					void SetPrintButtonSensitive(bool sensitive);

					void showInitialImage();
					void showLoadImage();
					void showPrintErrorImage();
					void showPrintOkImage();

				protected:
					
				private:

					/**
					 * @fn	void LogPagingTreeViewWidget::LoadPage (unsigned int page);
					 *
					 * @brief	Loads a page.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	page	The page.
					 */

					void LoadPage (unsigned int page);

					/**
					 * @fn	void LogPagingTreeViewWidget::LoadGUI ();
					 *
					 * @brief	Loads the graphical user interface.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void LoadGUI ();

					/**
					 * @fn	void LogPagingTreeViewWidget::on_buttonBack_clicked();
					 *
					 * @brief	Handles button back clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonBack_clicked();

					/**
					 * @fn	void LogPagingTreeViewWidget::on_buttonNext_clicked();
					 *
					 * @brief	Handles button next clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonNext_clicked();						

					void on_buttonPrint_clicked();
					

					Gtk::Table *m_VTable;   ///< The v table
					Gtk::VBox * vBoxRight;
					Gtk::ButtonBox	*m_ButtonBoxNav;	///< The button box nav
					Gtk::Label * labelPrinting;
					Gtk::Image * imagePrinting;
					Gtk::VBox * vboxPrinting;
					Gtk::Label	*m_LabelPage;   ///< The label page
					Gtk::EventBox * eventboxLog; ///< eventbox
					LogTreeViewWidget * logTreeViewWidget;  ///< The log tree view widget
						
					Smartmatic::SAES::Log::LogReader *logReader;	///< The log reader
					Smartmatic::SAES::Log::LogPage logPage; ///< The log page
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonBack;  ///< The back button
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonNext;  ///< The next button
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonPrint;
				};
			}
		}
	}
}

#endif // _LOGPAGINGTREEVIEWWIDGET_H_
