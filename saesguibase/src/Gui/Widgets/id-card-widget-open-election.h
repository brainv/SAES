/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	id-card-widget-open-election.h
 *
 * @brief	Declares the identifier card widget open election class.
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

#ifndef _ID_CARD_WIDGET_OPEN_ELECTION_H_
#define _ID_CARD_WIDGET_OPEN_ELECTION_H_
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
				 * @class	IDCardWidgetOpenElection
				 *
				 * @brief	Identifier card widget open election. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class IDCardWidgetOpenElection: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
				{
				public:

					/**
					 * @fn	IDCardWidgetOpenElection::IDCardWidgetOpenElection();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					IDCardWidgetOpenElection();

					/**
					 * @fn	IDCardWidgetOpenElection::~IDCardWidgetOpenElection();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~IDCardWidgetOpenElection();
					
				protected:

					/**
					 * @fn	void IDCardWidgetOpenElection::on_buttonAccept_clicked();
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



#endif // _ID_CARD_WIDGET_OPEN_ELECTION_H_
