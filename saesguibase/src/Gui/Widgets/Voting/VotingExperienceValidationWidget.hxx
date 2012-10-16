/**
 * @file VotingExperienceValidationWidget.hxx
 * @brief Header class voting experience validation widget
 * @date 25/04/2012
 * @author Yadickson Soto
 */

#ifndef VotingExperienceValidationWidget_HXX_
#define VotingExperienceValidationWidget_HXX_

#include <Gui/Widgets/ProgressWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include <Widgets/StepWidget.hxx>

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
					/**
					 * @class VotingExperienceValidationWidget
					 * @brief Class card removed widget
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					class VotingExperienceValidationWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						VotingExperienceValidationWidget();
						/**
						 * @brief Class destroy
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~VotingExperienceValidationWidget();
						/**
						 * @brief method refresh widget
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();
						/**
						 * @brief method getter signal ballot
						 * @return signal ballot
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getSignalBallot();
						/**
						 * @brief method getter signal all
						 * @return signal all
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getSignalAll();

					protected:

						/**
						 * @brief initialize class
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						void initialize();
						/**
						 * @brief dispose class
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						void dispose();

					private:

						Gtk::EventBox * mainFrame; ///< The frame principal
						Gtk::VBox * vBox;   ///< The vbox
						Gtk::HBox * hBox1;   ///< The hbox
						Gtk::HBox * hBox2;   ///< The hbox
						Gtk::Alignment * alignment; ///< The alignment
						Smartmatic::GUI::Widgets::SmartmaticButton * ballotButton;	///< The only ballot button
						Smartmatic::GUI::Widgets::SmartmaticButton * allButton;	///< The generate all button
						static Smartmatic::Log::ISMTTLog* logger;   ///< logger
					};
				}
			}
		}
	}
}

#endif /* VotingExperienceValidationWidget_HXX_ */
