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
/**
 * @file complex-ballot-option-widget.h
 * @brief ballot option widget with a circle
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _COMPLEX_BALLOT_OPTION_WIDGET_H_
#define _COMPLEX_BALLOT_OPTION_WIDGET_H_

#include "Gui/Widgets/ballot-option-widget.h"
#include "Widgets/circle-widget.h"
#include <Voting/Election/election-schema.hxx>
#include "Runtime/Environment/saes-directories.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	ComplexBallotOptionWidget
				 *
				 * @brief	Complex ballot option widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ComplexBallotOptionWidget: public BallotOptionWidget 
				{
				public:

					/**
					 * @fn	ComplexBallotOptionWidget::ComplexBallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& eligibleOption,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir, bool isPrincipal);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	eligibleOption	ballot option to be displayed.
					 * @param	saesDir				  	The saes dir.
					 * @param	isPrincipal			  	is ballot option is principal.
					 */

					ComplexBallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& eligibleOption,
					                          Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
					                          bool isPrincipal);

					/**
					 * @fn	ComplexBallotOptionWidget::~ComplexBallotOptionWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~ComplexBallotOptionWidget();

					/**
					 * @fn	void ComplexBallotOptionWidget::SetSelection(bool select, bool sendSignal = false);
					 *
					 * @brief	select the ballot and mark the circle option widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	select	  	if ballot is selected.
					 * @param	sendSignal	if send click signal or just change visual color.
					 */

					void SetSelection(bool select, bool sendSignal = false);

					/**
					 * @fn	void ComplexBallotOptionWidget::ForceShowImage(int imageHeight, float imageRelation);
					 *
					 * @brief	Force show image.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	imageHeight  	Height of the image.
					 * @param	imageRelation	The image relation.
					 */

					void ForceShowImage(int imageHeight, float imageRelation);

				protected:

					/**
					 * @fn	bool ComplexBallotOptionWidget::on_ballot_clicked(GdkEventButton* event);
					 *
					 * @brief	Executes the ballot clicked action.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	event	If non-null, the event.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool on_ballot_clicked(GdkEventButton* event);
					


				private:
					Smartmatic::GUI::Widgets::CircleWidget* circle; ///< The circle
					Gtk::Label*	numberLabel;	///< Number of labels
					Gtk::HBox* hbox;	///< The hbox

				};
			}
		}
	}
}

#endif // _COMPLEX_BALLOT_OPTION_WIDGET_H_
