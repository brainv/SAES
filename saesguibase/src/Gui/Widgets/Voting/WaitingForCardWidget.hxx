/**
 * @file WaitingForCardWidget.hxx
 * @brief Header class waiting card widget
 * @date 11/04/2012
 * @author Yadickson Soto
 */

#ifndef WAITINGFORCARDWIDGET_HXX_
#define WAITINGFORCARDWIDGET_HXX_

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
					 * @class WaitingForCardWidget
					 * @brief Class card removed widget
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					class WaitingForCardWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						WaitingForCardWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~WaitingForCardWidget();
						/**
						 * @brief view only card
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewOnlyCard();
						/**
						 * @brief view card and barcode
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewCardAndBarcode();
						/**
						 * @brief view error card and barcode
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewErrorCardAndBarcode();
						/**
						 * @brief view reconfigure barcode
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewReconfigureBarcode();
						/**
						 * @brief view card validate
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewCardValidate();
						/**
						 * @brief view error card validate
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void viewErrorCardValidate();
						/**
						 * @brief refresh text
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void update();
						/**
						 * @brief method hide buttons
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void hideButtons();
						/**
						 * @brief method hide buttons
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void showButtons();
						/**
						 * @brief method refresh widget
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();
						/**
						 * @brief method getter signal simulation
						 * @return signal simulation
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getSignalSim();
						/**
						 * @brief method getter signal back
						 * @return signal back
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0< void > getSignalBack();

					protected:

						/**
						 * @brief initialize class
						 * @date 11/04/2012
						 * @author Yadickson Soto
						 */
						void initialize();

					private:

						/**
						 * @enum WaitingState
						 * @brief state widget
						 */
						enum WaitingState
						{
							 ONLY_CARD ///< state only card
							,CARD_AND_BARCODE ///< state card and barcode
							,ERRRO_CARD_AND_BARCODE ///< state error card and barcode
							,RECONFIGURE_BARCODE ///< reconfigure barcode
							,CARD_VALIDATE ///< card validate
							,ERROR_CARD_VALIDATE ///< error card validate
						};

						WaitingState state; ///< state widget
						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< image frame
						Gtk::Frame * mainFrame; ///< main frame
						Gtk::VBox * mainVBox; ///< main vbox
						Gtk::Frame * infoFrame; ///< info frame
						Gtk::HButtonBox * buttonBox; ///< button box
						Gtk::Label * alarmLabel; ///< alarm label
						Smartmatic::GUI::Widgets::SmartmaticButton * buttonSim; ///< button simulation
						Smartmatic::GUI::Widgets::SmartmaticButton * buttonBack; ///< button back
						static Smartmatic::Log::ISMTTLog* logger;   ///< logger
					};
				}
			}
		}
	}
}

#endif /* WAITINGFORCARDWIDGET_HXX_ */
