/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	close-election-status-widget.h
 *
 * @brief	Declares the close election status widget class.
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

#ifndef _ASSISTED_ACTIVATION_MANAGER_WIDGET_
#define _ASSISTED_ACTIVATION_MANAGER_WIDGET_
#include <gtkmm.h>
#include <Widgets/wizard-widget-manager.h>
#include <Widgets/smartmatic-button.h>
#include "assisted-activation-id-card-widget.h"
#include "assisted-activation-question-widget.h"
#include "assisted-activation-impugnation-widget.h"
#include <Voting/PBReports/assisted-activation-schema.hxx>

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
				class AssistedActivationManagerWidget : public Gtk::Frame
				{
				public:

					AssistedActivationManagerWidget();

					~AssistedActivationManagerWidget();

					void Start();

					void Dispose();

					typedef sigc::signal<void, Smartmatic::SAES::Voting::PBReports::Activation> type_activation_signal;

					type_activation_signal on_activation_signal_emit();

				protected:
					type_activation_signal m_activation_signal;

				private:
					Gtk::VBox* vbox;
					Gtk::Label* labelWait;
					void on_nextButton_clicked();

					void on_backButton_clicked();

					void on_finishSignal_emitted();
					void EmitFinish(Smartmatic::SAES::Voting::PBReports::Activation activation);

					Smartmatic::GUI::Widgets::SmartmaticButton* nextButton;
					Smartmatic::GUI::Widgets::SmartmaticButton* backButton;
					Smartmatic::GUI::Widgets::WizardWidgetManager* wizardWidget;

					AssistedActivationIDCardWidget* voterID;
					AssistedActivationIDCardWidget* helperID;
					AssistedActivationIDCardWidget* presidentID;
					AssistedActivationIDCardWidget* challengerID;
					AssistedActivationIDCardWidget* finalHelperID;

					AssistedActivationQuestionWidget* proxyQuestion;
					AssistedActivationQuestionWidget* challengeQuestion;

					AssistedActivationImpugnationWidget* impugnWidget;

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _ASSISTED_ACTIVATION_MANAGER_WIDGET_
