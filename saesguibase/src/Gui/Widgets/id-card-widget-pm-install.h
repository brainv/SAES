/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	id-card-widget-close-election.h
 *
 * @brief	Declares the identifier card widget close election class.
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

#ifndef _ID_CARD_WIDGET_PM_INSTALL_H_
#define _ID_CARD_WIDGET_PM_INSTALL_H_
#include <gtkmm.h>
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
				 * @class	IDCardWidgetPMInstall
				 *
				 * @brief	Identifier card widget pm install. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class IDCardWidgetPMInstall: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
				{
				public:

					/**
					 * @fn	IDCardWidgetPMInstall::IDCardWidgetPMInstall();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					IDCardWidgetPMInstall();

					/**
					 * @fn	IDCardWidgetPMInstall::~IDCardWidgetPMInstall();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~IDCardWidgetPMInstall();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				protected:

					/**
					 * @fn	void IDCardWidgetPMInstall::on_buttonAccept_clicked();
					 *
					 * @brief	Handles button accept clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonAccept_clicked();

				private:
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

				};
			}
		}
	}
}



#endif // _ID_CARD_WIDGET_PM_INSTALL_H_
