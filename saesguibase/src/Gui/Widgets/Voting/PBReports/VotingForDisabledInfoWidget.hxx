/**
 * @file VotingForDisabledInfoWidget.hxx
 * @brief Header class voting for disabled info widget
 * @date 18/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDINFOWIDGET_HXX_
#define VOTINGFORDISABLEDINFOWIDGET_HXX_

#include <Widgets/smartmatic-button.h>
#include <Widgets/RegisterInfoWidget.hxx>
#include <Gui/Widgets/id-card-widget.h>
#include "VotingForDisabledRegisterInfoWidget.hxx"
#include <Widgets/counter-stat-widget.h>
#include <Widgets/SmartmaticTextView.h>

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
					namespace PBReports
					{
						/**
						 * @class VotingForDisabledInfoWidget
						 * @brief class voting for disabled info
						 * @data 18/05/2012
						 * @author Yadickson Soto
						 */
						class VotingForDisabledInfoWidget : public Gtk::EventBox
						{
						public:
							/**
							 * @brief Class constructor
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledInfoWidget();
							/**
							 * @brief Class destroy
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~VotingForDisabledInfoWidget();
							/**
							 * @brief Method getter signal save info
							 * @return signal
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalSaveInfoButton();
							/**
							 * @brief Method getter signal cancel info
							 * @return signal
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalCancelInfoButton();
							/**
							 * @brief Method setter current info widget
							 * @param widget current info widget
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void setRegisterInfoWidget(VotingForDisabledRegisterInfoWidget * widget);
							/**
							 * @brief Method getter current info widget
							 * @return current info widget
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledRegisterInfoWidget * getRegisterInfoWidget();
							/**
							 * @brief method refresh
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();

						protected:

							/**
							 * @brief method init
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void initialize();
							/**
							 * @brief method dispose
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void dispose();
							/**
							 * @brief method check info
							 * @date 22/05/2012
							 * @author Yadickson Soto
							 */
							void checkInfo();
							/**
							 * @brief method show info
							 * @date 22/05/2012
							 * @author Yadickson Soto
							 */
							void showInfo();
							/**
							 * @brief method show error
							 * @date 22/05/2012
							 * @author Yadickson Soto
							 */
							void showError();
							/**
							 * @brief	Check data
							 * @author	Yadickson Soto
							 * @date	04/06/2012
							 */
							virtual bool CheckCompleteData();

						private:

							sigc::signal<void> signalSave; ///< signal save info

							Gtk::EventBox * mainEventBox; ///< main event box
							Gtk::VBox * vBoxIDOne; ///< info disabled
							Gtk::VBox * vBoxIDTwo; ///< info approved
							Gtk::EventBox * eventBoxText; ///< event box text
							Gtk::EventBox * eventBoxButton; ///< event box button

							Gtk::VBox * mainVBox; ///< main vbox
							Gtk::HBox * hboxID; ///< hbox id
							Gtk::Label * labelCommennts; ///< label comments
							Gtk::Label * labelError; ///< label error
							Smartmatic::GUI::Widgets::SmartmaticTextView * textview; ///< text view

							Smartmatic::SAES::GUI::Widgets::IDCardWidget * idOne; ///< id one
							Smartmatic::SAES::GUI::Widgets::IDCardWidget * idTwo; ///< id two
							Smartmatic::GUI::Widgets::SmartmaticButton * backButton; ///< back button

							Smartmatic::GUI::Widgets::CounterStatWidget * valueOptionInfoDisabled; ///< value option info disabled
							Smartmatic::GUI::Widgets::CounterStatWidget * valueOptionInfoApproved; ///< value option info approved

							VotingForDisabledRegisterInfoWidget * widget; ///< current info widget
							int timeout; ///< time out error
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDINFOWIDGET_HXX_ */
