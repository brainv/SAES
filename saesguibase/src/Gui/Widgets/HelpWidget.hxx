/**
 * @file HelpWidget.hxx
 * @brief Header help widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#ifndef HELPWIDGET_HXX_
#define HELPWIDGET_HXX_

#include <gtkmm.h>
#include <iostream>
#include <Widgets/StepWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include <Printing/HelpPrinting.hxx>

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
				 * @class HelpWidget
				 * @brief Class help widget
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				class HelpWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					HelpWidget();
					/**
					 * @brief Class constructor
					 * @param titleKey title key
					 * @param image image
					 * @param file file
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					HelpWidget(std::string titleKey, std::string image, std::string file);
					/**
					 * @brief Class destroy
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~HelpWidget();
					/**
					 * @brief Method set info
					 * @param titleKey title key
					 * @param image image
					 * @param file file
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void setInfo(std::string titleKey, std::string image, std::string file);
					/**
					 * @brief virtual method getter is visible help button
					 * @return true is help button visible
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual bool isExit();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief method getter signal run print
					 * @return signal run print
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalStartPrint();
					/**
					 * @brief method getter signal end print
					 * @return signal end print
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalEndPrint();

				protected:

					sigc::signal<void> signalStartPrint; ///< signal start print
					sigc::signal<void> signalEndPrint; ///< signal end print

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
					/**
					 * @brief method printing
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void startPrintProcess();
					/**
					 * @brief method check print
					 * @retur true is ok
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					bool checkPrinter();
					/**
					 * @brief method end printing, show result
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void endPrinting();
					/**
					 * @brief method printing
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void printHelp();
					/**
					 * @brief method end printing
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void printFinished();
					/**
					 * @brief method error printing
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					void errorDetected();
					/**
					 * @brief method getter file name by current language
					 * @param file file
					 * @result file name by current language
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					std::string getCurrentLanguageFile(std::string file);

				private:

					std::string imageFile; ///< image file
					std::string file; ///< file to print
					bool endStatus; ///< end status printer

					Gtk::EventBox * helpEventBox; ///< help main frame
					Gtk::VBox * mainVBox; ///< object
					Gtk::Label * labelInfo; /// label info printing
					Gtk::Label * label1; /// label info printing
					Gtk::Image * image; ///< image
					Gtk::VBox * helpVBox; ///< help container
					Gtk::HSeparator * separator; ///< horizontal separator
					Gtk::HBox * printHBox; ///< print hbox
					Smartmatic::GUI::Widgets::SmartmaticButton * printButton; ///< print button
					Smartmatic::SAES::Printing::HelpPrinting * printing; ///< help printing file
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* HELPWIDGET_HXX_ */
