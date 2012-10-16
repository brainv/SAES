/**
 * @file AuthenticationWidget.hxx
 * @brief Header class authentication widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#ifndef AUTHENTICATIONWIDGET_HXX_
#define AUTHENTICATIONWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include "PollingPlaceInfoWidget.hxx"
#include "Widgets/keypad-widget.h"
#include "Widgets/key-pad-widget-interface.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class AuthenticationWidget
				 * @brief Class authentication widget
				 * @date 31/03/2012
				 * @author Yadickson Soto
				 */
				class AuthenticationWidget : public Smartmatic::GUI::Widgets::StepWidget,
					public Smartmatic::GUI::Widgets::KeypadInterface
				{
				public:
					/**
					 * @brief Class constructor
					 * @param composedTitleKey composed title key
					 * @param info info
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					AuthenticationWidget(std::string composedTitleKey, PollingPlaceInfoWidget * info);
					/**
					 * @brief Class destroy
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~AuthenticationWidget();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();
					/**
					 * @brief method refresh widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
					/**
					 * @brief method clear password
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void clearPassword();
					/**
					 * @brief method check password
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void checkPassword();
					/**
					 * @brief method getter signal run menu
					 * @return signal run menu
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalRunMenu();
					/**
					 * @brief method getter signal run machine
					 * @return signal run machine
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalRunMachine();

				protected:

					sigc::signal<void> signalRunMenu; ///< signal menu
					sigc::signal<void> signalRunMachine; ///< signal run machine process

					/**
					 * @brief method config label
					 * @date 24/04/2012
					 * @author Yadickson Soto
					 */
					void config();
					/**
					 * @brief virtual method setter key
					 * @param value value key
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value);
					/**
					 * @brief virtual method key press
					 * @param data key value
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void OnKeyPress(int data);
					/**
					 * @brief virtual method key press
					 * @param data key value
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void OnKeyPressT9(char data);

				protected:

					Gtk::Frame * mainFrame; ///< main frame
					Gtk::HBox * mainHBox; ///< main hbox
					Gtk::Frame* infoFrame;  ///< information frame
					Gtk::HBox * keyHBox; ///< key vbox
					Gtk::Label * topLabel; ///< top label
					Gtk::Label * leftLabel; ///< left label
					Gtk::Frame * keyFrame; ///< key frame
					Gtk::Label * bottomLabel; ///< bottom label
					Gtk::Label * alarmLabel; ///< alarm label
					Gtk::VBox * mainVBox; ///< error label
					std::string composedTitleKey; ///< compose title key
					std::string composedTitle; ///< composed title
					std::string textFeedBack;   ///< feed back text
					Smartmatic::GUI::Widgets::KeypadWidget * keypadTest; ///< keypad test
					PollingPlaceInfoWidget * info; ///< info authentication
				};
			}
		}
	}
}

#endif /* AUTHENTICATIONWIDGET_HXX_ */
