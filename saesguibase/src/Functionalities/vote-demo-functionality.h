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

#ifndef _VOTE_DEMO_FUNCTIONALITY_H_
#define _VOTE_VOTE_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include "Voting/Vote/vote-schema.hxx"
#include <Functionalities/graphic-display-functionality.h>
#include "Gui/Widgets/custom-attributes-combo-selections-widget.h"
#include "Printing/PrintPreviewWidget.h"
#include "Printing/VotePrintDocument.h"
#include <Voting/PBReports/vote-statistics.h>
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>
#include <Widgets/smartmatic-button.h>
#include "Gui/Widgets/BarcodeDetectionWidget.h"
#include "Gui/Widgets/CardActivatorEventBox.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class VoteProcessDemoFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
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

					static VoteProcessDemoFunctionality* Current();

					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

				protected:

					sigc::connection signalStartSendCommand; ///< signal start send command
					sigc::connection signalEndSendCommand; ///< signal end send command

					Glib::Mutex mutex;
					bool validVote; ///< flag valid vote
					bool magnify; ///< flag magnify vote


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

				private:

					Smartmatic::SAES::Voting::Vote::Vote vote;
					sigc::connection connReceived;  ///< The connection received
					sigc::connection signalPopDispatcher; /// < the saes enquer ready to pop dispatcher

					Smartmatic::SAES::GUI::Widgets::BarcodeDetectionWidget* barcodeDetectionWidget;
					Gtk::HBox* outsideBox;
					Gtk::Widget* normalFrameWidget;

					/**
					 * @brief	Recieved data.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	recieved	The recieved.
					 */
					
					void RecievedData(Smartmatic::System::SafeBuffer * recieved);

					/**
					 * @brief	Create the normal frame.
					 *
					 * @author	Juan.Delgado
					 * @date	23/07/2011
					 */
					void  CreateNormalFrame();

					/**
					 * @brief	Saves the vote. VoteProcessDemoFunctionality::SaveVote()
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 */						 
					void SaveVote();

					/**
					 * @brief	Process the vote. VoteProcessDemoFunctionality::ProcessVote()
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 */	
					void ProcessVote();

					void reconfigureBarcode();

					void endReconfigureBarcode();

					bool reconfigure; ///< flag reconfigure

					Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteStats; ///< The vote stats
					void signalingPopDispatcher();//the method that handles the signal pop of the enqueuer
					bool wasPresent;	///< true to was present
					std::vector<unsigned char> dataBinarizedToWrite;	///< The data binarized to write
					sigc::connection conn;  ///< The connection
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Frame* frameNormal;	///< The frame normal
					Gtk::Frame* frame2; ///< The second frame
					Gtk::EventBox* eventboxVoteDemo;	///< The eventbox vote demo
					Gtk::EventBox* eventboxStepBarcode; ///< The eventbox step barcode
					Gtk::VBox* vbox2;   ///< The second vbox
					std::string lastCardGUUID;  ///< The last card guuid
					Smartmatic::SAES::Printing::PrintPreviewWidget *printWidget;	///< The print widget
					Smartmatic::SAES::Printing::PrintPreviewWidget *printWidgetMagnify; ///< The print widget magnify
					Smartmatic::SAES::Printing::VotePrintDocument* doc; ///< The document
					Smartmatic::SAES::Printing::VotePrintDocument* docMagnify;  ///< The document magnify
					Gtk::Image* imageCard;  ///< The image card
					Gtk::Image* imageVote;  ///< The image vote
					Gtk::Label* labelResult;	///< The label result
					Gtk::Label*	labelStatus;	///< The label status
					Gtk::Label* labelVoteGen;   ///< The label vote generate
					Gtk::ScrolledWindow *scrolledwindowVote;	///< The scrolledwindow vote
					Gtk::Viewport *viewportVote;	///< The viewport vote
					Gtk::EventBox* eventbox1; ///< The eventbox custom attributes

					Gtk::CheckButton* checkbuttonIsAudio;   ///< The button to determine if is Audio
					Gtk::Frame* frameMagnify;   ///< The frame magnify
					Gtk::VBox* vboxMagnify; ///< The vbox magnify
					Gtk::ScrolledWindow*  scrolledMagnify;  ///< The scrolled magnify
					Gtk::Viewport*   viewMagnify;   ///< The view magnify
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonBackMagnify;  ///< The button back magnify
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonMagnify;  ///< The button magnify

					/**
					 * @brief	Method activate card data
					 * @author	Yadickson Soto
					 * @date	10/05/2012
					 */
					void activateCardData();

					void SetCustomAttributeVector(std::vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > vecCA);

					/**
					 * @brief	Handles button back magnify clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonBackMagnify_clicked();

					/**
					 * @brief	Handles button magnify clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonMagnify_clicked();

					Smartmatic::SAES::GUI::Widgets::CardActivatorEventBox * cardActivatorBox;

					std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute * > atts;
					std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > attributes;  ///< The attributes
					//Smartmatic::SAES::GUI::Widgets::CustomAttributesComboSelectionsWidget* comboSelections; ///< The combo selections
					static VoteProcessDemoFunctionality *current_instance;  ///< The current instance

					/**
					 * @brief	Executes the option button action.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param [in,out]	info	If non-null, the information.
					 */

					void onOptionButton(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* info);
					std::string temporalValue;  ///< The temporal value

					/**
					 * @brief	Default constructor initialize all variables in NULL.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					VoteProcessDemoFunctionality();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					~VoteProcessDemoFunctionality();			

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();	
					std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > listCAD;  ///< The list cad

					/**
					 * @brief	Gets a code by name.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	optionName	Name of the option.
					 *
					 * @return	The code by name.
					 */

					std::string getCodeByName(std::string optionName);

					/**
					 * @brief	Gets a name by code.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	optionCode	The option code.
					 *
					 * @return	The name by code.
					 */

					std::string getNameByCode(std::string optionCode);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					void cleanAttributes();

					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

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
					 * @brief	Barcode refresh.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 */

					void BarcodeRefresh();

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

					void BarcodeRefreshDemo(bool enabledMagnify);

					/**
					 * @brief	Barcode refresh not demo.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					void BarcodeRefreshNotDemo();

					/**
					 * @brief	Barcode error.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					void BarcodeError(bool enabledMagnify);

					virtual void BeforeExit();

					void AdjustElectionStatus();

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


#endif // _VOTE_VOTE_FUNCTIONALITY_H_
