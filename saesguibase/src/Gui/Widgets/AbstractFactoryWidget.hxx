/**
 * @file AbstractFactoryWidget.hxx
 * @brief Header class for create widget
 * @date 03/11/2011
 * @author Yadickson Soto
 */

#ifndef ABSTRACTFACTORYWIDGET_HXX_
#define ABSTRACTFACTORYWIDGET_HXX_

#include "InstallMachineWidget.hxx"
#include "AutomaticDiagnosticWidget.hxx"
#include "InitiatorWidget.hxx"
#include "ReportInstallWidget.hxx"
#include "PersistCodiFilesWidget.hxx"
#include "persist-transmission-package-widget.h"
#include "generate-pv-report-widget.h"
#include "sign-transmission-package-widget.h"
#include "close-election-status-widget.h"
#include "OpenElectionStatusWidget.hxx"
#include "PersistAllResultWidget.hxx"
#include "BarcodeDetectionWidget.h"
#include "BallotOptionTableWidget.hxx"
#include "ContingencyCardGenWidget.h"
#include "MemoryStateWidget.hxx"
#include "AuthenticationWidget.hxx"
#include "BeidErrorWidget.hxx"
#include "ReportPrintingWidget.h"
#include "DiagnosisBlockedWidget.hxx"
#include "DataUtilsValidatorWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class AbstractFactoryWidget
				 * @brief Class for create widget
				 * @date 03/11/2011
				 * @author Yadickson Soto
				 */
				class AbstractFactoryWidget
				{
				protected:

					/**
					 * @brief Class constructor
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					AbstractFactoryWidget();

				public:

					/**
					 * @brief Class destroy
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~AbstractFactoryWidget();
					/**
					 * @brief Method for create install machine widget
					 * @return new widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static InstallMachineWidget * createInstallMachineWidget();
					/**
					 * @brief Method for create automatic diagnostic widget
					 * @return new widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static AutomaticDiagnosticWidget * createAutomaticDiagnosticWidget();
					/**
					 * @brief Method for create initiator widget
					 * @return new widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static InitiatorWidget * createInitiatorWidget();
					/**
					 * @brief Method for create report install widget
					 * @return new widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static ReportInstallWidget * createReportInstallWidget();
					/**
					 * @brief Method for create persist transmission package widget
					 * @return new widget
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					static PersistTransmissionPackageWidget * createPersistTransmissionPackageWidget();
					/**
					 * @brief Method for create persist codi files widget
					 * @return new widget
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					static PersistCodiFilesWidget * createPersistCodiFilesWidget();
					/**
					 * @brief Method for create generate pv report widget
					 * @return new widget
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					static GeneratePVReportWidget * createGeneratePVReportWidget();
					/**
					 * @brief Method for create sign transmission package widget
					 * @return new widget
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					static SignTransmissionPackageWidget * createSignTransmissionPackageWidget();
					/**
					 * @brief Method for create close election status widget
					 * @return new widget
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					static CloseElectionStatusWidget * createCloseElectionStatusWidget();
					/**
					 * @brief Method for create persist all result widget
					 * @return new widget
					 * @date 17/02/2012
					 * @author Yadickson Soto
					 */
					static PersistAllResultWidget * createPersistAllResultWidget();
					/**
					 * @brief Method for create barcode detection widget
					 * @return new widget
					 * @date 07/03/2012
					 * @author Yadickson Soto
					 */
					static BarcodeDetectionWidget * createBarcodeDetectionWidget();
					/**
					 * @brief Method for create ballot option table widget
					 * @return ballot option table widget
					 * @date 13/03/2012
					 * @author Yadickson Soto
					 */
					static BallotOptionTableWidget * createBallotOptionTableWidget();
					/**
					 * @brief Method for create contingency card widget
					 * @return contingency card widget
					 * @date 20/03/2012
					 * @author Yadickson Soto
					 */
					static ContingencyCardGenWidget * createContingencyCardGenWidget();
					/**
					 * @brief Method for create memory state widget
					 * @return memory state widget
					 * @date 29/03/2012
					 * @author Yadickson Soto
					 */
					static MemoryStateWidget * createMemoryStateWidget();
					/**
					 * @brief Method for create authentication widget
					 * @return authentication widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					static AuthenticationWidget * createAuthenticationWidget();
					/**
					 * @brief Method for create beid error widget
					 * @return beid error widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					static BeidErrorWidget * createBeidErrorWidget();
					/**
					 * @brief Method for create open election status widget
					 * @return new widget
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					static OpenElectionStatusWidget * createOpenElectionStatusWidget();
					/**
					 * @brief Method for create report printing widget
					 * @return new widget
					 * @date 29/05/2012
					 * @author Yadickson Soto
					 */
					static ReportPrintingWidget * createReportPrintingWidget();
					/**
					 * @brief Method for create diagnosis blocked widget
					 * @return new widget
					 * @date 12/06/2012
					 * @author Yadickson Soto
					 */
					static DiagnosisBlockedWidget * createDiagnosisBlockedWidget();
					/**
					 * @brief Method for create data utils validator widget
					 * @return new widget
					 * @date 24/07/2012
					 * @author Yadickson Soto
					 */
					static DataUtilsValidatorWidget * createDataUtilsValidatorWidget();
				};
			}
		}
	}
}

#endif /* ABSTRACTFACTORYWIDGET_HXX_ */
