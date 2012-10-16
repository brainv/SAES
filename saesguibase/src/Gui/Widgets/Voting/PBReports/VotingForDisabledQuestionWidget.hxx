/**
 * @file VotingForDisabledQuestionWidget.hxx
 * @brief Header class voting for disabled question
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDQUESTIONWIDGET_HXX_
#define VOTINGFORDISABLEDQUESTIONWIDGET_HXX_

#include <Widgets/smartmatic-button.h>

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
						 * @class VotingForDisabledQuestionWidget
						 * @brief class voting for disabled question
						 * @data 18/05/2012
						 * @author Yadickson Soto
						 */
						class VotingForDisabledQuestionWidget : public Gtk::EventBox
						{
						public:
							/**
							 * @brief class constructor
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledQuestionWidget();
							/**
							 * @brief class destroy
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~VotingForDisabledQuestionWidget();
							/**
							 * @brief virtual method init
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();
							/**
							 * @brief method getter signal assisted button
							 * @return signal assisted button
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalAssistedButton();
							/**
							 * @brief method getter signal accompaniedButton
							 * @return signal accompaniedButton
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalAccompaniedButton();

						private:

							Gtk::EventBox * mainFrame; ///< main frame
							Gtk::VBox * mainVBox; ///< main vbox
							Gtk::Label * labelTitle; ///< label title
							Gtk::HBox * hbox1; ///< hbox
							Gtk::HBox * hbox2; ///< hbox
							Smartmatic::GUI::Widgets::SmartmaticButton * assistedButton; ///< assisted button
							Smartmatic::GUI::Widgets::SmartmaticButton * accompaniedButton; ///< accompanied button
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDQUESTIONWIDGET_HXX_ */
