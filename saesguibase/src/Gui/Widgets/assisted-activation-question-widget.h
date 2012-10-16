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

#ifndef _ASSISTED_ACTIVATION_QUESTION_WIDGET_
#define _ASSISTED_ACTIVATION_QUESTION_WIDGET_
#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>

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
				class AssistedActivationQuestionWidget : public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					AssistedActivationQuestionWidget(std::string questionTitle,
							std::string okButtonText, std::string cancelButtonText, std::string instruction,
							bool buttonsVertical = false);

					~AssistedActivationQuestionWidget();

					void SendStopWizardOnCancel();
					void SendStopWizardOnOK();
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

					bool StopWizard();

					bool GetAnswer();

					void reset();

					Glib::ustring GetWidgetName() { return "AssistedActivationQuestionWidget"; };

				protected:
					void on_okButton_clicked();
					void on_cancelButton_clicked();

				private:
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
					bool stopOnCancel;
					bool stopOnOk;
					bool answer;
				};
			}
		}
	}
}

#endif // _ASSISTED_ACTIVATION_QUESTION_WIDGET_
