/**
 * @file MemoryStateWidget.hxx
 * @brief Header class memory state widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#ifndef MEMORYSTATEWIDGET_HXX_
#define MEMORYSTATEWIDGET_HXX_

#include <gtkmm.h>
#include <iostream>
#include <Widgets/smartmatic-button.h>
#include <Widgets/StepWidget.hxx>
#include "ProgressWidget.hxx"
#include <Operation/MachineOperationManager.hxx>

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
				 * @class MemoryStateWidget
				 * @brief Class memory state widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				class MemoryStateWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param progress progress widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					MemoryStateWidget(ProgressWidget * progress);
					/**
					 * @brief Class destroy
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~MemoryStateWidget();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
					/**
					 * @brief method getter signal start widget
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalStartWidget();
					/**
					 * @brief method getter signal allow
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalAllow();
					/**
					 * @brief method getter signal block
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalBlock();
					/**
					 * @brief method getter signal one memory
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalOneMemory();
					/**
					 * @brief method getter signal one memory
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalTwoMemory();
					/**
					 * @brief method getter signal verify
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalVerify();

				protected:

					sigc::signal<void> signalStartWidget; ///< signal start run widget
					sigc::signal<void> signalAllow; ///< signal allow one memory
					sigc::signal<void> signalBlock; ///< receive signal block current widget
					sigc::signal<void> signalOneMemory; ///< signal connect one memory
					sigc::signal<void> signalTwoMemory; ///< signal connect two memory
					sigc::signal<void> signalVerify; ///< signal verify data

				protected:

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

					void processMemoryState(Smartmatic::SAES::Operation::MachineOperationManager::MemoryEvent memoryEvent,
							Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior memoryBehavior);

					void getMemoryState();
					void configureWidget(bool showHideButton, bool buttonClose);
					void enabledButton();
					void hideWidget();
					void shutDown();

					bool checkPrinter();

				private:

					std::string labelKey;
					std::string image;

					Gtk::EventBox * mainEventBox;
					Gtk::EventBox * progressEventBox;
					Gtk::VBox * memoryVBox;
					Gtk::HBox * shutdownHBox;
					Smartmatic::GUI::Widgets::SmartmaticButton * shutdownButton;

					sigc::connection conn;
					sigc::connection connectButton;

					Smartmatic::SAES::Operation::MachineOperationManager::MemoryEvent memoryEvent;
					Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior memoryBehavior;

					Glib::Mutex mutex; ///< mutex sync processing

					ProgressWidget * progress;
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* MEMORYSTATEWIDGET_HXX_ */
