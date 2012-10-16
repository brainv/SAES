/*
 * ReportInstallWidget.hxx
 *
 *  Created on: 19/10/2011
 *      Author: soto
 */

#ifndef REPORTINSTALLWIDGET_HXX_
#define REPORTINSTALLWIDGET_HXX_

#include <gtkmm.h>
#include <Printing/InstallationPrintDocument.h>
#include <Printing/PrintDocumentClient.h>
#include <Printing/PrintDocumentResult.h>
#include <Gui/Widgets/ProgressWidget.hxx>
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
				class ReportInstallWidget: public Smartmatic::GUI::Widgets::StepWidget, Smartmatic::SAES::Printing::PrintDocumentClient
				{
				public:
					ReportInstallWidget(ProgressWidget * progress);
					virtual ~ReportInstallWidget();

					void start(bool createBarcode = true);
					bool getStatus();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				private:
					bool status;
					ProgressWidget * progress;
					std::string message;
					Smartmatic::SAES::Printing::InstallationPrintDocument*  installationPrintDocument; ///< Installation print document
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/

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

					virtual void onDocumentPrinted(Smartmatic::SAES::Printing::PrintDocumentResult res);

                    void startPrinting();
                    void end();
                    void showMessagePrinting();
				};
			}
		}
	}
}

#endif /* REPORTINSTALLWIDGET_HXX_ */
