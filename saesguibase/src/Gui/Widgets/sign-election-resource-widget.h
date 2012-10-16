/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	persist-transmission-package-widget.h
 *
 * @brief	Declares the persist transmission package widget class.
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

#ifndef _SIGN_ELECTION_RESOURCE_WIDGET_H_
#define _SIGN_ELECTION_RESOURCE_WIDGET_H_
#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>
#include "Gui/Widgets/id-card-widget.h"

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
				/**
				 * @class	PersistTransmissionPackageWidget
				 *
				 * @brief	Persist transmission package widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class SignElectionResourceWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					/**
					 * @fn	PersistTransmissionPackageWidget::PersistTransmissionPackageWidget();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					SignElectionResourceWidget();

					/**
					 * @fn	PersistTransmissionPackageWidget::~PersistTransmissionPackageWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~SignElectionResourceWidget();

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

					/**
					 * @fn	Glib::ustring PersistTransmissionPackageWidget::GetWidgetName()
					 *
					 * @brief	Gets the widget name.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The widget name.
					 */

					Glib::ustring GetWidgetName() { return "SignElectionResourceWidget"; };

				private:
					void on_signButton_clicked();
					void on_nosignButton_clicked();
					void on_confirmButton_clicked();
					void on_cancelButton_clicked();
					void CheckIDCard();
					void on_IDWidgetAccept_clicked();
					void ShowIDCard();
					void ShowSignElectionFrame();
					void ShowConfirmFrame();
					Gtk::VBox* vbox;
					Gtk::VBox* confirmBox;
					Gtk::VBox* confirmBoxSign;
					Smartmatic::SAES::GUI::Widgets::IDCardWidget* idCard;
					bool signFile;
					bool continueOnFail;

					/**
					 * @fn	void PersistTransmissionPackageWidget::ThreadStart();
					 *
					 * @brief	Thread start.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ThreadStart();

					/**
					 * @fn	void PersistTransmissionPackageWidget::on_done();
					 *
					 * @brief	Handles done signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_done();

					/**
					 * @fn	void PersistTransmissionPackageWidget::UpdateLabel(Glib::ustring text);
					 *
					 * @brief	Updates the label described by text.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	text	The text.
					 */

					void UpdateLabel(Glib::ustring text);
					Gtk::Label* label;  ///< The label
					Gtk::Image* loadImage;

					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
					bool showQuestion;
					bool showConfirm;
				};
			}
		}
	}
}

#endif // _SIGN_ELECTION_RESOURCE_WIDGET_H_
