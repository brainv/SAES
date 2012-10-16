/*
 * ActivationStatsWidget.h
 *
 *  Created on: Sep 6, 2011
 *      Author: juand
 */

#ifndef ACTIVATIONSTATSWIDGET_H_
#define ACTIVATIONSTATSWIDGET_H_

#include <gtkmm.h>
#include <Log/ISMTTLog.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Widgets/StatisticWidget.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class ActivationStatsWidget : public Gtk::VBox
				{
				public:
					/**
					 * @brief	Constructor
					 *
					 * @author	Juan Delgado
					 */
					ActivationStatsWidget(Smartmatic::SAES::Configuration::CountConfiguration & totalCountType, bool showStatistic);

					/**
					 * @brief	finalizer
					 *
					 * @author	Juan Delgado
					 */
					virtual ~ActivationStatsWidget();

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
					 * @brief	Set attributes for card
					 *
					 * @author	Juan Delgado
					 *
					 * @param	vector with custom attributes
					 */
					void SetAttributes(std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute> attributes);

					/**
					 * @brief	Allow Card Activation
					 *
					 * @author	Juan Delgado
					 *
					 * @param	allo true if allow activation
					 */
					void AllowCardActivation(bool allow);

					/**
					 * @brief	Writes voting info in card
					 *
					 * @author	Juan Delgado
					 *
					 * @param	vector with custom attributes
					 * @return	true if succesfully
					 */
					static bool WriteVotingCard(std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute*> attributes);

					/**
					 * @brief	Set one memory mode operation
					 *
					 * @author	Juan Delgado
					 *
					 * @param	true if only one memory
					 */
					static void SetOneMemoryMode(bool oneMemory);

					/**
					 * @brief	Continue operation
					 */
					void ContinueOperation();

					/**
					 * @brief	Stop operation
					 */
					void StopOperation();

				private:
					/**
					 * @brief	Run thread for write voting card
					 *
					 * @author	Juan Delgado
					 */
					void WriteCard();

					/**
					 * @brief	Handles check if card is presence
					 *
					 * @author	Juan Delgado
					 *
					 * return	true if continue polling
					 */
					bool CheckCardPresence();

					/**
					 * @brief	Update label instruction text
					 *
					 * @author	Juan Delgado
					 *
					 * @return	true if continue signal
					 */
					void UpdateLabel();

					/**
					 * @brief	Update stat instruction text
					 *
					 * @author	Juan Delgado
					 *
 					 * @return	true if continue signal
					 */
					bool UpdateStat();

					bool showMessageSleepWriteCard();

					std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute> attributes;  ///< The attributes
					Smartmatic::GUI::Widgets::StatisticWidget* statsWidget;	///< The statistic widget
					Gtk::Label* instructionLabel;///< The instruction label
					Gtk::Image* cardImage;///< The card image
					sigc::connection conn_checkCard;	///< The check card connection
					sigc::connection conn_updateLabel;	///< The update label connection
					sigc::connection conn_updateStat;	///< The update stat connection
					sigc::connection connSleepWriteCard;	///< The sleep write card connection
					static bool oneMemory;	///< True if operating with one memory
					bool disposeExecuted;///< True if dispose was executed
					bool wasPresent;	///< True if card was present
					bool threadIsAlive;	///< True if thread is alive
					std::string updateLabel;	///< Text for update label
					std::string imageInsert;	///< Path of insert image
					std::string imageExtract;	///< Path of extract image
					std::string imageExtractError;	///< Path of extract image error
					bool error; ///< flag error
					Smartmatic::SAES::Configuration::CountConfiguration totalCountType;
					int timerRefresh; ///< time refresh
					int timerSleepWriteCard; ///< timer sleep write card
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}

#endif /* ACTIVATIONSTATSWIDGET_H_ */
