/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#ifndef _PRINT_PREVIEW_FUNCTIONALITY_H_
#define _PRINT_PREVIEW_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include "Voting/Vote/vote-schema.hxx"
#include <Functionalities/graphic-display-functionality.h>
#include "Printing/PrintPreviewWidget.h"
#include "Printing/VotePrintDocument.h"
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>
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
				class PrintPreviewFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{

				public:

					/**
					 * @brief	Gets the dont allow help.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowHelp();

					/**
					 * @brief	Gets the help sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The help sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getHelpSeqKey();

					/**
					 * @brief	Gets the dont allow exit.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowExit();

					/**
					 * @brief	Gets the sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getSeqKey();

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static PrintPreviewFunctionality* Current();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

				protected:

					Glib::Mutex mutex;

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

					void BarcodeDisconnected();
					sigc::connection connBarcodeDisconnected;  ///< The connection back

					/**
					 * @brief	Handles barcode connected signal
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					void on_barcode_connected(bool isConnected);

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
					 * @brief virtual method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

				private:

					sigc::connection connReceived;  ///< The connection received
					sigc::connection signalPopDispatcher; /// < the saes enquer ready to pop dispatcher
					sigc::connection connBarcode;
					sigc::connection disconnBarcode;

					sigc::connection signalStartSendCommand; ///< signal start send command
					sigc::connection signalEndSendCommand; ///< signal end send command

					Smartmatic::SAES::Voting::Vote::Vote vote;
					bool validVote; ///< flag valid vote
					Smartmatic::SAES::GUI::Widgets::BarcodeDetectionWidget* barcodeDetectionWidget;
					Gtk::HBox* outsideBox;
					Gtk::Widget* normalFrameWidget;

					void signalingPopDispatcher();//the method that handles the signal pop of the enqueuer
					void RecievedData(Smartmatic::System::SafeBuffer * recieved);
					bool wasPresent;	///< true to was present
					std::vector<unsigned char> dataBinarizedToWrite;	///< The data binarized to write
					sigc::connection conn;  ///< The connection


					Smartmatic::SAES::Printing::PrintPreviewWidget* printWidgetMagnify; ///< The print widget magnify
					Smartmatic::SAES::GUI::Widgets::PartyContestViewerWidget* partyViewerWidget;	///< The party viewer widget
					Smartmatic::SAES::Printing::VotePrintDocument* docMagnify;  ///< The document magnify
					Gtk::Label* labelMessage;   ///< Message describing the label
					Gtk::Frame* frameMagnify;   ///< The frame magnify
					Gtk::VBox* vboxMagnify; ///< The vbox magnify
					Gtk::ScrolledWindow*  scrolledMagnify;  ///< The scrolled magnify
					Gtk::Viewport*   viewMagnify;   ///< The view magnify
				
					/**
					 * @brief	Create the normal frame.
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					void  CreateNormalFrame();

					static PrintPreviewFunctionality *current_instance; ///< The current instance

					/**
					 * @brief	Default constructor initialize all variables in NULL.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					PrintPreviewFunctionality();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					~PrintPreviewFunctionality();			


					Smartmatic::SAES::Voting::Vote::VoteMode voteMode;	///< mode of vote

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();	

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
					 * @brief	Refreshs.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int time_num);

					/**
					 * @brief	Barcode refresh demo.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool BarcodeRefreshVoteMode(int time_num);

					/**
					 * @brief	Barcode error.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 */

					void BarcodeError();

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}


#endif // _PRINT_PREVIEW_FUNCTIONALITY_H_
