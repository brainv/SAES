/*
 * ConsolidationStatsWidget.h
 *
 *  Created on: Sep 6, 2011
 *      Author: Juan Delgado
 */

#ifndef CONSOLIDATIONSTATSWIDGET_H_
#define CONSOLIDATIONSTATSWIDGET_H_

#include <gtkmm.h>
#include <Log/ISMTTLog.h>

#include <System/SafeBuffer.h>
#include <Voting/Vote/vote-schema.hxx>
#include <Voting/PBReports/vote-statistics.h>
#include <Widgets/StatisticWidget.h>
#include <Windows/pop-up-message-window.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Operation/SaesEnqueuer.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class ConsolidationStatsWidget : public Gtk::VBox
				{
				public:
					/**
					 * @brief	Constructor
					 *
					 * @author	Juan Delgado
					 */
					ConsolidationStatsWidget(Smartmatic::SAES::Configuration::CountConfiguration & totalCountType,
							Smartmatic::SAES::Configuration::CountConfiguration & officialCountType);

					/**
					 * @brief	Finializer
					 *
					 * @author	Juan Delgado
					 */
					virtual ~ConsolidationStatsWidget();

					/**
					 * @brief	Initialize widget
					 *
					 * @author	Juan Delgado
					 */
					void Initialize();

					/**
					 * @brief	Dispose widget
					 *
					 * @author	Juan Delgado
					 */
					void Dispose();

					/**
					 * @brief	Set one memory mode operation
					 *
					 * @author	Juan Delgado
					 *
					 * @param	true if only one memory
					 */
					void SetOneMemoryMode(bool oneMemory);

					/**
					 * @brief	Defines an alias representing the type signal_barcodeConnected
					 */
					typedef sigc::signal<void, bool> signal_void_bool;

					/**
					 * @brief	Signal that handles the barcode commands send
					 *
					 * @return	signal connection
					 */
					signal_void_bool barcode_SendCommands();

					/**
					 * @brief	Continue operation
					 */
					void ContinueOperation();

					/**
					 * @brief	Stop operation
					 */
					void StopOperation();

					void pauseOperation();

					void resumeOperation();

					void UpdateMemoryPresence();

					void UpdateBarcodePresence();

				private:

					signal_void_bool m_signal_sendCommands;

					Smartmatic::SAES::Operation::VoteResult * voteResult;

					void BarcodeCommandsSent(bool commandsOk);

					void BarcodeConnected();

					void BarcodeDisconnected();

					bool UpdateInstructionLabel();

					void UpdateStats();

					void showPopUp();

					void ShowMessageWindow();

					void ReceivedData(Smartmatic::System::SafeBuffer * received);

					void SignalSaesEnqueuerDispatch();

					void ProccesVote(Smartmatic::SAES::Voting::Vote::Vote& vote);

					void ShowNormalState();

					void ConnectSignals();

					void DisconnectSignals();

					std::string getValue(Smartmatic::SAES::Configuration::CountConfiguration::CountTypeSequence & seq);

					Smartmatic::GUI::Widgets::StatisticWidget* statsWidget;///< The card image
					Gtk::Label* infoScanVoteLabel;///< The info scan vote label
					Gtk::Label* instructionLabel;///< The instruction label
					Gtk::Label* barcodeLabel;///< The barcode label
					Gtk::Label* memoryLabel;///< The memory label
					Gtk::Image* barcodeImage;///< The barcode image
					Gtk::Image* memoryImage;///< The memory image
					Gtk::VBox* vbox;///< The veBarcodeInParamsrtical box

					Gdk::Color scanFontVoteColor; ///< valid vote color
					Gdk::Color scanFontDuplicateVoteColor; ///< duplicate vote color
					Gdk::Color scanFontBadVoteColor; ///< bad vote color

					Gdk::Color scanBoxVoteColor; ///< valid vote color
					Gdk::Color scanBoxDuplicateVoteColor; ///< duplicate vote color
					Gdk::Color scanBoxBadVoteColor; ///< bad vote color

					enum StateVote
					{
						GOOD
						,BAD
						,DUPLICATE
					};

					StateVote flagStateVote; ///< flag state vote
					bool consolidateVoteWithOneMemory;///< True if consolidate with one memory
					bool oneMemory;///< True if only one memory
					bool barcodeConnected;///< True if barcode is connected
					bool disposeExecuted;///< True if dispose was executed
					bool sendingCommands;///< True if sending commands
					bool stopOperationAfterSend;///< True if stop operation after send

					std::string barcodeConnectedImage;///< The barcode connected image path
					std::string barcodeNotConnectedImage;///< The barcode not connected image path
					std::string oneMemoryConnectedImage;///< The one memory connected image path
					std::string twoMemoryConnectedImage;///< The two memory connected image path
					std::string commandsInBarcode;///< The commands in barcode
					std::string commandsOutBarcode;///< The commands out barcode

					sigc::connection conn_barcodeReceivedData;///< The connection for received data from barcode
					sigc::connection conn_barcodeConnected;///< The connection for barcode connected
					sigc::connection conn_barcodeDisconnected;///< The connection for barcode disconnected
					sigc::connection conn_barcodeCommandsSend;///< The connection for barcode commands send
					sigc::connection conn_saesEnqueuerDispatcher;///< The connection for received data from barcode
					sigc::connection conn_updateLabelInstruction;///< The connection for update label instruction

					long countRecievedData;
					Smartmatic::GUI::Windows::PopUpMessageWindow* popUpWindow;
					Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteWrapper; ///< The vote stats
					Glib::Mutex mutex;///< The mutex
					Glib::Mutex windowMutex;///< The window mutex
					Glib::Mutex popupMutex;///< The window mutex
					bool showPopUpMessage; ///< flag show popup message
					bool enabledPopupChangeColor; ///< flag enabled popup change color
					Smartmatic::SAES::Configuration::CountConfiguration totalCountType;
					Smartmatic::SAES::Configuration::CountConfiguration officialCountType;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}

#endif /* CONSOLIDATIONSTATSWIDGET_H_ */
