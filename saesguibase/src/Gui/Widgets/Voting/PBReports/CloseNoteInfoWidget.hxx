/**
 * @file CloseNoteInfoWidget.hxx
 * @brief Header class close note info widget
 * @date 24/05/2012
 * @author Yadickson Soto
 */

#ifndef _CLOSE_NOTE_INFO_WIDGET_H_
#define _CLOSE_NOTE_INFO_WIDGET_H_

#include <gtkmm.h>
#include <Voting/PBReports/close-election-notes-schema.hxx>
#include <Widgets/smartmatic-button.h>
#include <Widgets/SmartmaticTextView.h>
#include "CloseNoteRegisterInfoWidget.hxx"
#include <Gui/Widgets/id-card-widget.h>

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
						 * @class CloseNoteInfoWidget
						 * @brief class close note info widget
						 * @date 24/05/2012
						 * @author Yadickson Soto
						 */
						class CloseNoteInfoWidget : public Smartmatic::SAES::GUI::Widgets::IDCardWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							CloseNoteInfoWidget();
							/**
							 * @brief class destroy
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~CloseNoteInfoWidget();
							/**
							 * @brief Method getter signal save info
							 * @return signal
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalSaveInfoButton();
							/**
							 * @brief Method getter signal cancel info
							 * @return signal
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalCancelInfoButton();
							/**
							 * @brief Method setter current info widget
							 * @param widget current info widget
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void setRegisterInfoWidget(CloseNoteRegisterInfoWidget * widget);
							/**
							 * @brief Method getter current info widget
							 * @return current info widget
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							CloseNoteRegisterInfoWidget * getRegisterInfoWidget();
							/**
							 * @brief method refresh
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();

						protected:

							/**
							 * @brief method back clicked
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void backClicked();
							/**
							 * @brief method check info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void checkInfo();
							/**
							 * @brief method show info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void showInfo();
							/**
							 * @brief	Check data
							 * @author	Yadickson Soto
							 * @date	04/06/2012
							 */
							virtual bool CheckCompleteData();
							/**
							 * @brief	Shows the entry data and emit the back signal.
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

							CloseNoteRegisterInfoWidget * widget; ///< current info widget

							sigc::signal<void> signalSave; ///< signal save
							sigc::signal<void> signalCancel; ///< signal cancel

							Gtk::CheckButton* check; ///< check president note
							Gtk::Label * checkLabel; ///< check label
							Gtk::Label * labelComment; ///< label comment
							Smartmatic::GUI::Widgets::SmartmaticButton * backButton; ///< back button
							Smartmatic::GUI::Widgets::SmartmaticButton * acceptButton; ///< accept button
							Smartmatic::GUI::Widgets::SmartmaticTextView * textView; ///< text view

							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif // _CLOSE_NOTE_INFO_WIDGET_H_
