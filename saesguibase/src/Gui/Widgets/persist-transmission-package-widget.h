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

#ifndef _PERSIST_TRANSMISSION_PACKAGE_WIDGET_H_
#define _PERSIST_TRANSMISSION_PACKAGE_WIDGET_H_

#include <Widgets/wizard-widget-base.h>
#include "ProgressWidget.hxx"

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

				class PersistTransmissionPackageWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					/**
					 * @fn	PersistTransmissionPackageWidget::PersistTransmissionPackageWidget();
					 *
					 * @brief	Default constructor.
					 * @param progress widget with label and image
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					PersistTransmissionPackageWidget(ProgressWidget * progress);

					/**
					 * @fn	PersistTransmissionPackageWidget::~PersistTransmissionPackageWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PersistTransmissionPackageWidget();

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

					virtual Glib::ustring GetWidgetName();

					/**
					 * @brief Method getter is enabled button exit wizard
					 * @return true is enabled button exit wizard
					 * @date 22/02/2012
					 * @author Yadickson Soto
					 */
					virtual bool isEnabledButtonExitWizard();

				private:
					ProgressWidget * progress; ///< widget with label and image
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					/**
					 * @brief	Method start persist codi files
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void start();

					/**
					 * @brief	Method end persist codi files
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void end();

					/**
					 * @brief	Method start persist codi files
					 * @param text new text for widget
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void updateLabel(std::string text);
				};
			}
		}
	}
}

#endif // _PERSIST_TRANSMISSION_PACKAGE_WIDGET_H_
