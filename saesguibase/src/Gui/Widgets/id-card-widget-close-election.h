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

#ifndef _ID_CARD_WIDGET_CLOSE_ELECTION_H_
#define _ID_CARD_WIDGET_CLOSE_ELECTION_H_
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
				 * @class	IDCardWidgetCloseElection
				 *
				 * @brief	Identifier card widget close election. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class IDCardWidgetCloseElection: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
				{
				public:

					/**
					 * @fn	IDCardWidgetCloseElection::IDCardWidgetCloseElection();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					IDCardWidgetCloseElection();

					/**
					 * @fn	IDCardWidgetCloseElection::~IDCardWidgetCloseElection();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~IDCardWidgetCloseElection();
					
				protected:

					/**
					 * @fn	void IDCardWidgetCloseElection::on_buttonAccept_clicked();
					 *
					 * @brief	Handles button accept clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonAccept_clicked();

				private:
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					void on_done();
					void UpdateLabel();

				};
			}
		}
	}
}



#endif // _ID_CARD_WIDGET_CLOSE_ELECTION_H_
