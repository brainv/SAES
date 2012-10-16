/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
* saesfunctionality
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _VOTE_CONSOLIDATION_FUNCTIONALITY_H_
#define _VOTE_CONSOLIDATION_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Widgets/smartmatic-button.h>
#include "Voting/Vote/vote-schema.hxx"
#include <Voting/PBReports/vote-statistics.h>
#include "Gui/Widgets/Voting/vote-statistics-widget.h"
#include "Printing/VotePrintDocument.h"
#include "Printing/PrintPreviewWidget.h"
#include <Log/ISMTTLog.h>
#include <System/SafeBuffer.h>
#include "Gui/Widgets/party-contest-viewer-widget.h"
#include "Gui/Widgets/BarcodeDetectionWidget.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class VoteConsolidationFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{

				public:

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static VoteConsolidationFunctionality* Current();

				protected:

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The start log message.
					 */

					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finish log message.
					 */

					Glib::ustring getFinishLogMessage();

					/**
					 * @brief	Handles barcode connected signal
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					void on_barcode_connected(bool isConnected);

					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

				private:
					void signalingPopDispatcher();

					sigc::connection signalStartSendCommand; ///< signal start send command
					sigc::connection signalEndSendCommand; ///< signal end send command

					sigc::connection signalPopDispatcher;
					sigc::connection signalRefreshLabel;
					Smartmatic::SAES::GUI::Widgets::BarcodeDetectionWidget* barcodeDetectionWidget;
					Gtk::Label* labelTemp;
					Gtk::HBox* outsideBox;
					Gtk::Widget* normalFrameWidget;
					Gtk::Fixed* buttonFixedMessage;
					Gtk::Fixed* postButtonFixedMessage;
					Gtk::EventBox* previewButtonEventBox;

					sigc::connection connBarcodeConnected;  ///< The connection back
					sigc::connection connBarcodeDisconnected;  ///< The connection back

					Gtk::Frame* widgetPreviewFrame; ///< The widget preview frame

					Smartmatic::SAES::Printing::PrintPreviewWidget* printPreviewWidget; ///< The print preview widget
					Smartmatic::SAES::Printing::VotePrintDocument* votePrint;   ///< The vote print
					Gtk::Alignment* printPreviewAlign;  ///< The print preview align

					Gtk::Alignment* previewAligment;
					Gtk::VBox* previewBox;
					Gtk::HBox* previewButtonHBox;
					Smartmatic::GUI::Widgets::SmartmaticButton* activatePreviewBoxButton;
					Gtk::Label* previewBoxMessage;

					Gtk::ScrolledWindow* scrolledMagnify;   ///< The scrolled magnify
					Gtk::Viewport* viewMagnify; ///< The view magnify

					Smartmatic::SAES::GUI::Widgets::Voting::VoteStatisticsWidget* voteStatsWidget;  ///< The vote stats widget

					Smartmatic::SAES::GUI::Widgets::PartyContestViewerWidget* partyViewerWidget;	///< The party viewer widget

					Smartmatic::SAES::Voting::Vote::Vote vote;
					sigc::connection connReceived;  ///< The connection received

					Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteStats; ///< The vote stats

					bool previewIsActivated;
					bool thereIsAVote; ///< flag valid vote
					bool isAudit;

					void BarcodeDisconnected();


					/**
					 * @brief	Loads the gtk builder.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void LoadGTKBuilder();

					/**
					 * @brief	Received data.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	received	The received.
					 */

					void ReceivedData(Smartmatic::System::SafeBuffer * received);

					/**
					 * @brief	Procces vote.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ProccesVote();

					/**
					 * @brief	Updates the stats.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void UpdateStats();

					/**
					 * @brief	Refresh label text.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	text	The text.
					 */

					bool RefreshLabelText(std::string text);

					/**
					 * @brief	Creates the vote print document.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void CreateVotePrintDocument();

					/**
					 * @brief	Creates the party viewer widget.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void CreatePartyViewerWidget();

					/**
					 * @brief	Shows the print preview.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ShowPrintPreview();

					/**
					 * @brief	Creates the print preview.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void CreatePrintPreview();

					/**
					 * @brief	Saves the vote.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void SaveVote();

					void on_buttonActivatePreview_clicked();

					static VoteConsolidationFunctionality *current_instance;	///< The current instance

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					VoteConsolidationFunctionality();

					~VoteConsolidationFunctionality();

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					Gtk::Widget* GetFrame();

					/**
					 * @brief	Create the normal frame.
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					void  CreateNormalFrame();

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();
					/**
					 * @brief method block functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void block();
					/**
					 * @brief method partial functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void partial();
					/**
					 * @brief method resume functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void resume();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
					Glib::Mutex mutex;
					bool processingData;	///< true to processing data

					std::string scanNormal;
					std::string scanDuplicated;
					std::string scanBad;
					std::string scanReceivedData;
				};
			}
		}
	}
}


#endif // _VOTE_CONSOLIDATION_FUNCTIONALITY_H_
