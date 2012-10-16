/**
 * @file TimeOutPreviewWidget.hxx
 * @brief Body class timeout preview
 * @date 13/04/2012
 * @author Yadickson Soto
 */

#ifndef TIMEOUTPREVIEWWIDGET_HXX_
#define TIMEOUTPREVIEWWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include <Widgets/smartmatic-button.h>

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
					/**
					 * @class TimeOutPreviewWidget
					 * @brief Class timeout preview widget
					 * @date 13/04/2012
					 * @author Yadickson Soto
					 */
					class TimeOutPreviewWidget: public Smartmatic::GUI::Widgets::StepWidget
					{
					public:
						/**
						 * @brief Class constructor
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						TimeOutPreviewWidget();
						/**
						 * @brief Class destroy
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~TimeOutPreviewWidget();
						/**
						 * @brief Method getter signal close clicked
						 * @return signal
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getCloseClicked();
						/**
						 * @brief Method getter signal keep clicked
						 * @return signal
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getKeepClicked();

					private:

						Gtk::VBox * mainFrame; ///< main frame
						Gtk::Label * message; ///< message
						Gtk::HButtonBox * hbuttonBox; ///< button box
						Smartmatic::GUI::Widgets::SmartmaticButton * closeButton; ///< close button
						Smartmatic::GUI::Widgets::SmartmaticButton * keepButton; ///< keep button
					};
				}
			}
		}
	}
}

#endif /* TIMEOUTPREVIEWWIDGET_HXX_ */
