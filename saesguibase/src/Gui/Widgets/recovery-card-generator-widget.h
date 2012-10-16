/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	recovery-card-generator-widget.h
 *
 * @brief	Declares the recovery card generator widget class.
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

#ifndef _RECOVERY_CARD_GENERATOR_WIDGET_H_
#define _RECOVERY_CARD_GENERATOR_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>
#include <Widgets/smartmatic-combo-box.h>
#include <Operation/MachineOperationManager.hxx>
#include <Voting/Vote/VoteRecovery.h>
#include <Widgets/smartmatic-entry.h>
namespace Smartmatic
{
    namespace Log
    {
        /**
         * @brief   SMTT Log Interface
         *
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    02/06/2011
         */

        class ISMTTLog;
    }

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
			    /**
			     * @class	RecoveryCardInfo
			     *
			     * @brief	Information about the recovery card. 
			     *
			     * @author	Cesar.bonilla
			     * @date	4/29/2011
			     */

			    class  RecoveryCardInfo
			    {
					public:

					/**
					 * @fn	RecoveryCardInfo::RecoveryCardInfo(Glib::ustring voteCode, Glib::ustring lvgCode)
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	voteCode	The vote code.
					 * @param	lvgCode 	The lvg code.
					 */

					RecoveryCardInfo(Glib::ustring voteCode, Glib::ustring lvgCode)
					{
						this->voteCode=voteCode;
						this->lvgCode=lvgCode;
					}

					/**
					 * @fn	Glib::ustring RecoveryCardInfo::getVoteCode()
					 *
					 * @brief	Gets the vote code.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The vote code.
					 */

					Glib::ustring getVoteCode()
					{
						return voteCode;
					}

					/**
					 * @fn	Glib::ustring RecoveryCardInfo::getLVGCode()
					 *
					 * @brief	Gets the lvg code.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The lvg code.
					 */

					Glib::ustring getLVGCode()
					{
						return lvgCode;
					}
					
					private:
					
					Glib::ustring voteCode; ///< The vote code
					Glib::ustring lvgCode;  ///< The lvg code
			    };

				/**
				 * @class	RecoveryCardGeneratorWidget
				 *
				 * @brief	Recovery card generator widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class RecoveryCardGeneratorWidget: public Gtk::VBox
				{
				public:

					/**
					 * @fn	RecoveryCardGeneratorWidget::RecoveryCardGeneratorWidget(bool waitForCardToRegister);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	waitForCardToRegister	true to wait for card to register.
					 */

					RecoveryCardGeneratorWidget(bool waitForCardToRegister, bool showButtons, bool useNewVoteRecovery);
					sigc::signal<void,RecoveryCardInfo> signalOk_detected;  ///< The signal ok detected
					sigc::signal<void> signalCancel_detected;   ///< The signal cancel detected

					~RecoveryCardGeneratorWidget();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::CleanFields();
					 *
					 * @brief	Clean all entry text.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void CleanFields();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::GetFields();
					 *
					 * @brief	get the fields of this widget.
					 *
					 * @return	The RecoveryCardInfo with the fields.
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */						 
					RecoveryCardInfo GetFields();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::CheckFields();
					 *
					 * @brief	Check the emptyness of the fields of this widget and return a message.
					 *
					* @return	A string with a message.
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */						 
					std::string CheckFields();

					std::string checkNewRecovery();

					Smartmatic::SAES::Voting::Vote::Vote GetVote();

					void CheckAllFields();

					bool isValidate();

				protected:
					bool on_entryLVGCode_key_pressed(GdkEventKey* event);
					bool on_entryVoteCode_key_pressed(GdkEventKey* event);
					bool on_contestEntry_key_pressed(GdkEventKey* event);
					void on_contestEntry_focus_grabbed(int index);
					void on_buttonCheck_clicked();
					bool on_entryLVGCode_lost_focus(GdkEventFocus *focus);
					bool on_contestEntry_lost_focus(GdkEventFocus *focus);

				private:
					void CreateEntries();
					void DeleteHBox();

					bool waitForCardToRegister; ///< true to wait for card to register

					/**
					 * @fn	bool RecoveryCardGeneratorWidget::Refresh(int time_num);
					 *
					 * @brief	Refreshs.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int time_num);

					/**
					 * @fn	void RecoveryCardGeneratorWidget::on_buttonOk_clicked();
					 *
					 * @brief	Handles button ok clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonOk_clicked();

					/**
					 * @fn	void RecoveryCardGeneratorWidget::on_buttonCancel_clicked();
					 *
					 * @brief	Handles button cancel clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonCancel_clicked();					
					
					sigc::connection connOk;	///< The connection ok
					sigc::connection connCancel;	///< The connection cancel
					sigc::connection connRefresh;   ///< The connection refresh
					Gtk::VBox vboxPrincipal;	///< The vbox principal
					Smartmatic::GUI::Widgets::SmartmaticEntry entryVoteCode;   ///< The entry vote code
					Smartmatic::GUI::Widgets::SmartmaticEntry entryLVGCode;	///< The entry lvg code
					Gtk::Label labelVoteCode;   ///< The label vote code
					Gtk::Label labelLVGCode;	///< The label lvg code
					Gtk::Label labelTitle;  ///< The label title
					Gtk::Label labelMessage;	///< Message describing the label
					Gtk::HBox hboxTitle;	///< The hbox title
					Gtk::HBox hboxVoteCode; ///< The hbox vote code
					Gtk::HBox hboxLVGCode;  ///< The hbox lvg code
					Gtk::HButtonBox hbuttonbox; ///< The hbuttonbox
					Smartmatic::GUI::Widgets::SmartmaticButton okButton;	///< The ok button
					Smartmatic::GUI::Widgets::SmartmaticButton cancelButton;	///< The cancel button
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonCheck; ///< The button activate

					std::vector<Smartmatic::GUI::Widgets::SmartmaticEntry*>::iterator entryVectorIter;   ///< The entry vector iterator

					int fieldIndex;
					std::map<int, Smartmatic::GUI::Widgets::SmartmaticEntry*> entryMap;   ///< The entry map
					std::map<int, Gtk::Label*> labelMap;   ///< The label map
					std::map<int, Gtk::Image*> imageMap;   ///< The image map
					std::map<int ,Gtk::HBox*> hboxMap;   ///< The hbox map
					std::map<int ,std::string> contestCodeMap;   ///< The contest code map

					std::map<int ,Gtk::HBox*>::iterator hboxMapIter;   ///< The entry vector iterator

					Pango::FontDescription fontLabels;   ///< The font labels

					Gtk::Image lvgCodeImage;
					Gtk::Image voteCodeImage;

					std::string goodImage;
					std::string badImage;
					std::string noneImage;

					Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* votingDeviceWrapper;

					Smartmatic::SAES::Voting::Election::ElectionWrapper* electionWrapper;

					Smartmatic::SAES::Voting::Vote::VoteRecovery* voteRecovery;

					Smartmatic::SAES::Voting::Vote::Vote voteRecovered;

					void ChangeImageState(Gtk::Image& image, std::string state);

					void CleanImages();

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					bool useNewVoteRecovery;
					bool checkIsOk;
					std::string dummyLVG;
					std::string langCode;
					bool ValidateRecoveredVote();

					bool CheckIfVoteAlreadyRecovered(std::string voteCode);

					void CreateSuperNullVote(std::string voteCode);

					std::string statusRecovery;
					int enterKey;

					std::string getVoteCode();
				};
			}
		}
	}
}


#endif // _RECOVERY_CARD_GENERATOR_WIDGET_H_
