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

#ifndef _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEWER_
#define _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEWER_
#include <gtkmm.h>
#include "Voting/PBReports/assisted-activation-wrapper.h"
#include "Gui/Widgets/assisted-activation-id-card-widget-view.h"

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
				 * @class	AssistedActivationIDCardWidgetViewer
				 *
				 * @brief	Show the info for the assisted activation. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */
				class AssistedActivationIDCardWidgetViewer: public Gtk::VBox
				{
				public:

						/**
						 * @fn	AssistedActivationIDCardWidgetViewer::AssistedActivationIDCardWidgetViewer (Smartmatic::SAES::Voting::PBReports::Activation activation);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	activation the activation object to preview
						 */
					AssistedActivationIDCardWidgetViewer(Smartmatic::SAES::Voting::PBReports::Activation activation);

						/**
						 * @fn	AssistedActivationIDCardWidgetViewer::AssistedActivationIDCardWidgetViewer ();
						 *
						 * @brief	Finalizer.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 */
					~AssistedActivationIDCardWidgetViewer();

						/**
					 * @fn	void AssistedActivationIDCardWidgetViewer::init();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					void init();

						/**
					 * @fn	void AssistedActivationIDCardWidgetViewer::dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					void dispose();

				//private:

					AssistedActivationIDCardWidgetView* pollworkerViewWidget; /// < the pollworker view widget;
					AssistedActivationIDCardWidgetView* voterViewWidget;/// < the voter view widget;
					AssistedActivationIDCardWidgetView* propossedPersonViewWidget;/// < the propossed person view widget;
					AssistedActivationIDCardWidgetView* impugnatedPersonViewWidget;/// < the impugnator view widget;
					AssistedActivationIDCardWidgetView* dessignatedPersonViewWidget;/// < the dessignated person view widget;
					Gtk::EventBox eventTypeOfActivation; /// < the eventbox that hold the type of activation label
					Gtk::Label labelTypeOfActivation;/// < the label of type of activation	
					Gtk::VButtonBox vboxButtonPerson; ///< the vbuttonbox containing the principal actors
					Gtk::VButtonBox vboxButtonImpugnation;///< the vbuttonbox containing the impugnated actors
					Gtk::EventBox eventImpugnation; ///< the eventbox containing the impugnation label info
					Gtk::Label labelImpugnation;///< the label containing the impugnation info
					Gtk::Frame frameReason;///< the frame containing the reason of impugnation
					Gtk::VBox vboxReason;///< the vbox containing the reason of impugnation
					Gtk::EventBox eventReasonTitle;///< the event box containing the reason of impugnation title
					Gtk::Label labelReasonTitle;///< the label containing the reason of impugnation title
					Gtk::ScrolledWindow scrollReasonContent;///< the scroll containing the reason of impugnation content
					Gtk::Label labelReasonContent;///< the label containing the reason of impugnation content
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEWER_
