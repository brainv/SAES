/**
 * @file PoliceNoteInfoWidget.hxx
 * @brief Header class police note info widget
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#ifndef _POLICE_NOTE_INFO_WIDGET_H_
#define _POLICE_NOTE_INFO_WIDGET_H_

#include <gtkmm.h>
#include "PoliceNoteRegisterInfoWidget.hxx"
#include <Gui/Widgets/id-card-widget.h>
#include <Widgets/SmartmaticTextView.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					namespace PBReports
					{
						/**
						 * @class PoliceNoteInfoWidget
						 * @brief class police note info widget
						 * @date 25/05/2012
						 * @author Yadickson Soto
						 */
						class PoliceNoteInfoWidget : public Smartmatic::SAES::GUI::Widgets::IDCardWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							PoliceNoteInfoWidget();
							/**
							 * @brief class destroy
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~PoliceNoteInfoWidget();
							/**
							 * @brief Method getter signal save info
							 * @return signal
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalSaveInfoButton();
							/**
							 * @brief Method getter signal cancel info
							 * @return signal
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalCancelInfoButton();
							/**
							 * @brief Method setter current info widget
							 * @param widget current info widget
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void setRegisterInfoWidget(PoliceNoteRegisterInfoWidget * widget);
							/**
							 * @brief Method getter current info widget
							 * @return current info widget
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							PoliceNoteRegisterInfoWidget * getRegisterInfoWidget();
							/**
							 * @brief method refresh
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();

						protected:

							/**
							 * @brief method back clicked
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void backClicked();
							/**
							 * @brief method check info
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void checkInfo();
							/**
							 * @brief	Check data
							 * @author	Yadickson Soto
							 * @date	04/06/2012
							 */
							virtual bool CheckCompleteData();
							/**
							 * @brief	Shows the entry data and emit the back signal.
							 * @param timer timer
							 * @author	Juan.Delgado
							 * @date	18/07/2011
							 */
							virtual bool ShowEntryDataAndEmitSignal(int timer);
							/**
							 * @brief	Shows elements
							 * @author	Yadickson Soto
							 * @date	04/06/2012
							 */
							virtual void ShowElements();

						private:

							PoliceNoteRegisterInfoWidget * widget; ///< current info widget
							Smartmatic::GUI::Widgets::SmartmaticButton * backButton; ///< back button
							Smartmatic::GUI::Widgets::SmartmaticButton * acceptButton; ///< accept button
							Smartmatic::GUI::Widgets::SmartmaticTextView * textView; ///< text view
							Gtk::CheckButton * checkOne; ///< check one
							Gtk::CheckButton * checkTwo; ///< check two
							Gtk::CheckButton * checkThree; ///< check three

							Gtk::Label * actionOne; ///< action one label
							Gtk::Label * actionTwo; ///< action two label
							Gtk::Label * actionThree; ///< action three label
							Gtk::Label * labelComment; ///< label comment

							sigc::signal<void> signalSave; ///< signal save
							sigc::signal<void> signalCancel; ///< signal cancel

							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif // _CLOSE_NOTE_INFO_WIDGET_H_
