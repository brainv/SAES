/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	id-card-widget.h
 *
 * @brief	Declares the identifier card widget class.
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

#ifndef _ID_CARD_WIDGET_H_
#define _ID_CARD_WIDGET_H_
#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>
#include "Gui/Widgets/BeidWidget.h"
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include <Widgets/smartmatic-entry.h>
#include <Widgets/smartmatic-button.h>
#include <eid/EIDEventInterface.hxx>
#include "BeidErrorWidget.hxx"
#include <Widgets/TableWidget.hxx>
#include <Widgets/GenderComboBox.hxx>

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
				 * @class	IDCardWidget
				 *
				 * @brief	Identifier card widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class IDCardWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase, Smartmatic::SAES::EID::EIDEventInterface
				{
				public:

					/**
					 * @fn	IDCardWidget::IDCardWidget(std::string title1 = "", std::string title2 = "",
					 * 		bool showAccept = true);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	title1	  	The first title.
					 * @param	title2	  	The second title.
					 * @param	showAccept	true to show, false to hide the accept.
					 * @param	blockButton True to block button
					 */

					IDCardWidget(std::string title1 = "", std::string title2 = "",bool showAccept = true,
							bool blockButton = false);

					/**
					 * @fn	IDCardWidget::~IDCardWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~IDCardWidget();

					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

					/**
    				 * @fn	Glib::ustring IDCardWidget::GetWidgetName();
    				 *
    				 * @brief	Gets the widget name.
    				 *
    				 * @author	Cesar.bonilla
    				 * @date	4/29/2011
    				 *
    				 * @return	The widget name.
    				 */

    				Glib::ustring GetWidgetName();

					/**
					 * @fn	void IDCardWidget::ShowElements();
					 *
					 * @brief	Shows the only names.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					virtual void ShowElements();
					/**
					 * @brief method setter id config elements
					 * @param idConfig id config
					 * @date 04/05/2012
					 * @author Yadickson Soto
					 */
					void setIDConfig(Smartmatic::SAES::Configuration::IDConfig idConfig);

					/**
					 * @fn	void IDCardWidget::HideAcceptTitle();
					 *
					 * @brief	Hides the accept title.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void HideAcceptTitle();

					/**
					 * @fn	void IDCardWidget::HideConfirmationBeid();
					 *
					 * @brief	Hides the confirmation beid.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void HideConfirmationBeid();

					/**
					 * @fn	void IDCardWidget::SetNames(std::string firstName, std::string lastName);
					 *
					 * @brief	Sets the names.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	firstName	Name of the first.
					 * @param	lastName 	Name of the last.
					 */

					void SetNames(std::string firstName, std::string lastName);

					/**
					 * @fn	void IDCardWidget::GetNames(std::string& firstName, std::string& lastName);
					 *
					 * @brief	Gets the names.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	firstName	Name of the first.
					 * @param [in,out]	lastName 	Name of the last.
					 */

					void GetNames(std::string& firstName, std::string& lastName);

					/**
					 * @fn	void IDCardWidget::ClearNames();
					 *
					 * @brief	Clears the names.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ClearNames();


					/**
					 * @fn	Smartmatic::SAES::EID::CitizenInfo IDCardWidget::getCitizenInfo();
					 *
					 * @brief	Gets the citizen information.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The citizen information.
					 */

					Smartmatic::SAES::EID::CitizenInfo getCitizenInfo();

					void setCitizenInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo);

					void MaintainInfo();

					void SetVisualizeMode(bool visualizeMode);

					/**
					 * @typedef	sigc::signal<void> signal_void
					 *
					 * @brief	Defines an alias representing the signal void. .
					 */

					typedef sigc::signal<void> signal_void;						

					/**
					 * @fn	signal_void IDCardWidget::signal_accept_clicked();
					 *
					 * @brief	Raises the accept clicked event.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					signal_void signal_accept_clicked();

					/**
					 * @fn	signal_void IDCardWidget::signal_cardRemoved_detected();
					 *
					 * @brief	Raises the card removed detected event.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					signal_void signal_cardRemoved_detected();
					
					/**
					 * @fn	signal_void IDCardWidget::signal_backIncomplete_emitted();
					 *
					 * @brief	Raises the back incomplete emitted event.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					signal_void signal_backIncomplete_emitted();

					/**
					 * @fn	void IDCardWidget::ShowInCompleteData();
					 *
					 * @brief	Shows the in complete data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowInCompleteData();

					/**
					 * @fn	bool IDCardWidget::CheckCompleteData();
					 *
					 * @brief	Gets the check complete data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool CheckCompleteData();

					/**
					 * @brief virtual method refresh titles
					 * @date 19/05/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief method setter titles
					 * @param title1 title
					 * @param title2 title
					 * @date 22/05/2012
					 * @author Yadickson Soto
					 */
					void setTitles(std::string title1, std::string title2);

					/**
					 * @fn	void IDCardWidget::ShowEntryData();
					 *
					 * @brief	Shows the entry data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowEntryData();

					/**
					 * @brief method setter title configuration
					 * @param labelConf label configuration
					 * @date 22/05/2012
					 * @author Yadickson Soto
					 */
					void setTitleConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf);
					/**
					 * @brief method setter label configuration
					 * @param labelConf label configuration
					 * @date 22/05/2012
					 * @author Yadickson Soto
					 */
					void setLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf);

				protected:
					signal_void m_accept_clicked;   ///< The accept clicked
					signal_void signalCardRemoved_detected; ///< The signal card removed detected
					signal_void m_signal_backIncomplete_emitted; ///< The signal back incomplete emitted

					sigc::connection incompleteConnection;	///< The incomplete connection

					virtual void TextInserted();

					/**
					 * @fn	void IDCardWidget::SetShowAcept(bool showAccept);
					 *
					 * @brief	Sets show accept.
					 *
					 * @author	Juan.Delgado
					 * @date	19/08/2011
					 *
					 * @param showAccept	true if showAccept
					 */

					void SetShowAcept(bool showAccept);

					/**
					 * @fn	void IDCardWidget::on_beidButtonAccept_clicked();
					 *
					 * @brief	Handles beid button accept clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_beidButtonAccept_clicked();

					/**
					 * @fn	void IDCardWidget::on_beidButtonCancel_clicked();
					 *
					 * @brief	Handles beid button cancel clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_beidButtonCancel_clicked();

					/**
					 * @fn	virtual void IDCardWidget::on_buttonAccept_clicked();
					 *
					 * @brief	Handles button accept clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					virtual void on_buttonAccept_clicked();

					/**
					 * @fn	void IDCardWidget::GetData();
					 *
					 * @brief	Gets the data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void GetData();

					/**
					 * @fn	void IDCardWidget::ShowEntryDataAndEmitSignal();
					 *
					 * @brief	Shows the entry data and emit the back signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					virtual bool ShowEntryDataAndEmitSignal(int timer);

					Smartmatic::SAES::EID::CitizenInfo citizenInfo;	///< Information describing the citizen

					Smartmatic::GUI::Widgets::TableWidget * dataTable;  ///< The data table
					int entryWidth;
					int entryHeight;
					int labelWidth;
					Gtk::Label* labelMessage;
					Gtk::Alignment* alignDataGlobal;	///< The align data global
					Gtk::HBox* dataHbox;	///< The data hbox
					Gtk::Label *loadingLabel;  ///< The loading label
					Gtk::Label* removeCardLabel;	///< The remove card label
					Gtk::HButtonBox* buttonBox;	///< The button box
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonAccept;
					Gtk::VBox* entryVBox;	///< The entry v box

					int countElement;

					virtual void cardInserted();
					virtual void cardExtracted();

				private:

					Gtk::Alignment*  alignDataTable; ///< align table

					sigc::connection connCardChange;  ///< The connection card inserted
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					bool showAccept;
					bool maintainInfo;  ///< true to maintain info
					bool flagCardPresent;
					bool blockButton; 	///<true if block button
					Smartmatic::SAES::Configuration::ShowBeidEntryTypeConfiguration showBeidEntry;

					bool CardChange(int time_num);

					/**
					 * @fn	void IDCardWidget::CardDetected();
					 *
					 * @brief	Card detected.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void CardDetected();

					/**
					 * @fn	void IDCardWidget::CardExtracted();
					 *
					 * @brief	Card extracted.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void CardExtracted();

					/**
					 * @fn	void IDCardWidget::LogCardInfo(Smartmatic::SAES::EID::CitizenInfo citizenInfo);
					 *
					 * @brief	Logs a card information.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	citizenInfo	Information describing the citizen.
					 */

					void LogCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo);

					/**
					 * @fn	void IDCardWidget::ShowBeidWidget();
					 *
					 * @brief	Shows the beid widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowBeidWidget();

					/**
					 * @brief	method show error beid widget.
					 * @author	Yadickson Soto
					 * @date	23/04/2012
					 */
					void showBeidError();
					/**
					 * @fn	void IDCardWidget::ShowLoadingLabel();
					 *
					 * @brief	Shows the loading label.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowLoadingLabel();

					/**
					 * @fn	void IDCardWidget::SetData();
					 *
					 * @brief	Sets the data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void SetData();

					/**
					 * @fn	void IDCardWidget::ClearData();
					 *
					 * @brief	Clears the data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ClearData();

					/**
					 * @fn	void IDCardWidget::CreateBeidWidget();
					 *
					 * @brief	Creates the beid widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void CreateBeidWidget();

					/**
					 * @fn	void IDCardWidget::ShowSecondLoadingLabel();
					 *
					 * @brief	Shows the second loading label.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowSecondLoadingLabel();

					/**
					 * @fn	void IDCardWidget::GetCitizenAndData();
					 *
					 * @brief	Gets the citizen and data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void GetCitizenAndData();

					Gtk::Image* loadImage;  ///< The load image
					Gtk::Alignment* incompleteAlign;///< The incomplete align
					Gtk::Frame* beidFrame;  ///< The beid frame
					Gtk::Alignment* alignBeidExternal;  ///< The align beid external
					Gtk::Alignment* alignLoad;  ///< The align load
					Gtk::Label* beidLabel;  ///< The beid label
					Gtk::VBox* beidVBox;	///< The beid v box

					Smartmatic::GUI::Widgets::SmartmaticButton* beidButtonAccept;
					Smartmatic::GUI::Widgets::SmartmaticButton* beidButtonCancel;
					Gtk::Label* incompleteDataLabel;

					BeidWidget * beidWidget; ///< The beid widget
					BeidErrorWidget * beidErrorWidget; ///< The beid error

					Gtk::HBox * outsideBox;

					bool viewButtonTable;   ///< true to view button table
					bool showBeid;
					bool visualizeMode;
					bool showError; ///< show error
					std::string title1;
					std::string title2;
					void init_Thread();

				protected:

					Smartmatic::GUI::Widgets::SmartmaticEntry* firstNameEntry; ///< The first name entry
					Smartmatic::GUI::Widgets::SmartmaticEntry* surNameEntry;   ///< The sur name entry
					Smartmatic::GUI::Widgets::GenderComboBox* genderEntry;	///< The gender entry
					Smartmatic::GUI::Widgets::SmartmaticEntry* nationalityEntry;   ///< The nationality entry
					Smartmatic::GUI::Widgets::SmartmaticEntry* natNumberEntry; ///< The nat number entry

					Gtk::Label* firstNameLabel; ///< The first name label
					Gtk::Label* surNameLabel;   ///< The sur name label
					Gtk::Label* genderLabel;	///< The gender label
					Gtk::Label* nationalityLabel;   ///< The nationality label
					Gtk::Label* natNumberLabel; ///< The nat number label

					Smartmatic::SAES::Configuration::IDConfig idConfig; ///< id configuration

				};
			}
		}
	}
}



#endif // _ID_CARD_WIDGET_H_
