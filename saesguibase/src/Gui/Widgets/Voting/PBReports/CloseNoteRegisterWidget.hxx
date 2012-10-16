/**
 * @file CloseNoteRegisterWidget.hxx
 * @brief Header class close note
 * @data 24/05/2012
 * @author Yadickson Soto
 */

#ifndef CLOSENOTEREGISTERWIDGET_HXX_
#define CLOSENOTEREGISTERWIDGET_HXX_

#include <Widgets/smartmatic-button.h>
#include <Widgets/RegisterWidget.hxx>
#include <Widgets/RegisterActionWidget.hxx>
#include "CloseNoteRegisterInfoWidget.hxx"

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
						 * @class CloseNoteRegisterWidget
						 * @brief class close note
						 * @data 24/05/2012
						 * @author Yadickson Soto
						 */
						class CloseNoteRegisterWidget : public Smartmatic::GUI::Widgets::RegisterActionWidget<CloseNoteRegisterInfoWidget *>
						{
						public:
							/**
							 * @brief class constructor
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							CloseNoteRegisterWidget();
							/**
							 * @brief class destroy
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~CloseNoteRegisterWidget();
							/**
							 * @brief virtual method init
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();
							/**
							 * @brief method getter signal add info
							 * @return signal add info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalAddInfoButton();
							/**
							 * @brief method getter signal next
							 * @return signal next
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalNextButton();
							/**
							 * @brief method show next button
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void showNextButton();
							/**
							 * @brief method enable next button
							 * @param sensitive sensitive value
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void enableNextButton(bool sensitive = true);

						private:

							Gtk::Label * registerNotesLabel; ///< register notes label
							Smartmatic::GUI::Widgets::SmartmaticButton * addInfoButton; ///< add info
							Smartmatic::GUI::Widgets::SmartmaticButton * nextButton; ///< next
						};
					}
				}
			}
		}
	}
}

#endif /* CLOSENOTEREGISTERWIDGET_HXX_ */
