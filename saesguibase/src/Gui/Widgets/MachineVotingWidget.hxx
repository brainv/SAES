/**
 * @file MachineVotingWidget.hxx
 * @brief Header class voting experience widget
 * @date 08/03/2012
 * @author Yadickson Soto
 */

#ifndef MACHINEVOTINGWIDGET_HXX_
#define MACHINEVOTINGWIDGET_HXX_

#include "RunMachineWidget.hxx"
#include <Voting/VotingDevice/card-data-schema.hxx>
#include <Widgets/StepWidget.hxx>
#include <System/SafeBuffer.h>
#include <Operation/Alarm/AlarmController.hxx>

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
				namespace Voting
				{
					class WaitingForCardWidget;
					class PreviewWidget;
					class SimulationWidget;
					class LanguageSelectionWidget;
					class VotingExperienceWidget;
				}

				/**
				 * @class MachineVotingWidget
				 * @brief Class voting experience widget
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				class MachineVotingWidget : public RunMachineWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param menuWidget menu widget
					 * @param helpWidget help widget
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					MachineVotingWidget(Smartmatic::SAES::GUI::Widgets::MenuWidget * menuWidget,
							Smartmatic::SAES::GUI::Widgets::HelpWidget * helpWidget);
					/**
					 * @brief Class destroy
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~MachineVotingWidget();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
					/**
					 * @brief virtual method getter is visible help button
					 * @return true is help button visible
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual bool isTitle();
					/**
					 * @brief virtual method start widget
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void start();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

				protected:

					/**
					 * @enum StepVoting
					 * @brief step voting
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					enum StepVoting
					{
						 NONE ///< none process
						,WAITING ///< waiting for card data
						,VALIDATE ///< validate card data
						,ERROR_VALIDATE ///< error validate card data
						,SHOW_LANGUAGE ///< show selection language
						,VOTING ///< process voting
					};

					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief method view widget
					 * @param widget widget to show
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void viewWidget(Smartmatic::GUI::Widgets::StepWidget * widget);
					/**
					 * @brief method card insert event
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void cardInsertEvent();
					/**
					 * @brief method card remove event
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void cardRemoveEvent();
          /**
					 * @brief method card reader unresponsive event
					 * @date 01/08/2012
					 * @author Daniel Ampuero
					 */
          void cardReaderUnresponsiveEvent();
					/**
					 * @brief method card insert
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void cardInsert();
					/**
					 * @brief method card remove
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void cardRemove();
          /**
					 * @brief method card reader unresponsive
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void cardReaderUnresponsive();
					/**
					 * @brief method start check card data
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void startCheckCardPresent();
					/**
					 * @brief method stop check card data
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void stopCheckCardPresent();
					/**
					 * @brief method start check barcode
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void startCheckBarcode();
					/**
					 * @brief method stop check barcode
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void stopCheckBarcode();
					/**
					 * @brief method start check alarm button
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void startCheckAlarmButton();
					/**
					 * @brief method stop check alarm button
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void stopCheckAlarmButton();
					/**
					 * @brief method start check alarm box event
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void startCheckAlarmBoxEvent();
					/**
					 * @brief method stop check alarm box event
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void stopCheckAlarmBoxEvent();
					/**
					 * @brief method connect barcode
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void connectBarcode();
					/**
					 * @brief method disconnect barcode
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void disconnectBarcode();
					/**
					 * @brief method stop reconfigure barcode
					 * @param status true is ok
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void stopReconfigureBarcode(int status);
					/**
					 * @brief virtual method refresh
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief method simulation insert card data
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void simCardData();
					/**
					 * @brief method start voting experience
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void startValidateCardData();
					/**
					 * @brief method show selection language
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void showSelectionLanguage();
					/**
					 * @brief method start voting experience
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void startVotingExperience();
					/**
					 * @brief method stop voting experience
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void stopVotingExperience();
					/**
					 * @brief method read card data
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void readCardData();
					/**
					 * @brief method validate card data
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void validateCardData();
					/**
					 * @brief method create card data
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void createCardData();
					/**
					 * @brief method on language selected
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					void languageSelected();
					/**
					 * @brief	method setter alarm message
					 * @param	alarmType type of the alarm.
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					void setAlarm(Smartmatic::SAES::Functionality::Configuration::AlarmEnum alarmType);
					/**
					 * @brief	method view message error read card
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					void cardNotProperlyInserted();
					/**
					 * @brief	method received data barcode reader
					 * @param received data
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					void recievedData(Smartmatic::System::SafeBuffer * received);
					/**
					 * @brief method that handles the signal pop of the enqueuer
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					void signalingPopDispatcher();
					/**
					 * @brief method check printer
					 * @return true is printer success
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					bool checkPrinter();
					/**
					 * @brief method check recovery card data
					 * @return true is success
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					bool checkRecoveryCard();
					/**
					 * @brief method mark used card data
					 * @return true is success
					 * @author	Yadickson Soto
					 * @date	12/04/2012
					 */
					bool markUsedCardData();
					/**
					 * @brief method alarm box disconnected
					 * @author	Yadickson Soto
					 * @date	16/05/2012
					 */
					void alarmBoxDisconnect();
					/**
					 * @brief method back
					 * @author	Yadickson Soto
					 * @date	03/05/2012
					 */
					void back();
					/**
					 * @brief method restore widget
					 * @author	Yadickson Soto
					 * @date	25/05/2012
					 */
					void restoreWidget();
					/**
					 * @brief method restore widget
					 * @author	Yadickson Soto
					 * @date	25/05/2012
					 */
					void refreshAll();

				private:

					Smartmatic::SAES::GUI::Widgets::Voting::WaitingForCardWidget * waitingForCardWidget;	///< waiting card widget
					Smartmatic::SAES::GUI::Widgets::Voting::PreviewWidget * previewWidget; ///< print preview widget
					Smartmatic::SAES::GUI::Widgets::Voting::SimulationWidget * simulationWidget; ///< nationality widget
					Smartmatic::SAES::GUI::Widgets::Voting::LanguageSelectionWidget * languageSelectionWidget; ///< language selection widget
					Smartmatic::SAES::GUI::Widgets::Voting::VotingExperienceWidget * votingExperienceWidget; ///< voting experience widget

					std::vector < Gtk::Widget * > listWidget; ///< list voting widget

					StepVoting stepVoting; ///< step voting process
					Smartmatic::SAES::Voting::VotingDevice::Card_data currentCardData; ///< current card data
					std::string currentCardDataCode; ///< current card data code

					sigc::connection connLanguage;  ///< The connection language

					sigc::connection connCardInsertEvent;  ///< The connection card insert event
					sigc::connection connCardRemoveEvent;  ///< The connection card remove event
          sigc::connection connCardReaderUnresponsiveEvent;  ///< The connection card reader unresponsive event

					sigc::connection connBarcodeConnected;  ///< The connection barcode
					sigc::connection connBarcodeDisconnected;  ///< The disconnection barcode
					sigc::connection connReceived; ///< The connection received
					sigc::connection signalCommandsSentResponse; ///< signal sent command response
					sigc::connection signalPopDispatcher; ///< signal pop dispatcher
					sigc::connection signalEndVoting; ///< signal end voting experience

					sigc::connection connAlarm; ///< The connection alarm
					sigc::connection connAlarmMonitor; ///< The connection alarm monitor

					Glib::Mutex syncCard; ///< sync card
					Glib::Mutex syncVoting; ///< sync voting

					bool simulateProcess;	///< true if simulate process
					bool simulateVote;	///< true if simulate votes
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
				};
			}
		}
	}
}

#endif /* MACHINEVOTINGWIDGET_HXX_ */
