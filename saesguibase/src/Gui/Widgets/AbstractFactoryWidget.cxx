/**
 * @file AbstractFactoryWidget.cxx
 * @brief Body class for create widget
 * @date 03/11/2011
 * @author Yadickson Soto
 */

#include "AbstractFactoryWidget.hxx"
#include "FactoryMethodWidget.hxx"

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;

AbstractFactoryWidget::AbstractFactoryWidget()
{

}

AbstractFactoryWidget::~AbstractFactoryWidget()
{

}

InstallMachineWidget * AbstractFactoryWidget::createInstallMachineWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PollingPlaceInfoWidget * pollingPlaceInfo = FactoryMethodWidget::createPollingPlaceInfoWidget();
	InstallMachineWidget * widget = FactoryMethodWidget::createInstallMachineWidget(progress, pollingPlaceInfo);
	return widget;
}

AutomaticDiagnosticWidget * AbstractFactoryWidget::createAutomaticDiagnosticWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	AutomaticDiagnosticWidget * widget = new AutomaticDiagnosticWidget(progress);
	return widget;
}

InitiatorWidget * AbstractFactoryWidget::createInitiatorWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	InitiatorWidget * widget = new InitiatorWidget(progress);
	return widget;
}

ReportInstallWidget * AbstractFactoryWidget::createReportInstallWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	ReportInstallWidget * widget = new ReportInstallWidget(progress);
	return widget;
}

PersistTransmissionPackageWidget * AbstractFactoryWidget::createPersistTransmissionPackageWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PersistTransmissionPackageWidget * widget = new PersistTransmissionPackageWidget(progress);
	return widget;
}

PersistCodiFilesWidget * AbstractFactoryWidget::createPersistCodiFilesWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PersistCodiFilesWidget * widget = new PersistCodiFilesWidget(progress);
	return widget;
}

GeneratePVReportWidget * AbstractFactoryWidget::createGeneratePVReportWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	GeneratePVReportWidget * widget = new GeneratePVReportWidget(progress);
	return widget;
}

SignTransmissionPackageWidget * AbstractFactoryWidget::createSignTransmissionPackageWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	SignTransmissionPackageWidget * widget = new SignTransmissionPackageWidget(progress);
	return widget;
}

CloseElectionStatusWidget * AbstractFactoryWidget::createCloseElectionStatusWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	CloseElectionStatusWidget * widget = new CloseElectionStatusWidget(progress);
	return widget;
}

OpenElectionStatusWidget * AbstractFactoryWidget::createOpenElectionStatusWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	OpenElectionStatusWidget * widget = new OpenElectionStatusWidget(progress);
	return widget;
}

PersistAllResultWidget * AbstractFactoryWidget::createPersistAllResultWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PersistAllResultWidget * widget = new PersistAllResultWidget(progress);
	return widget;
}

BarcodeDetectionWidget * AbstractFactoryWidget::createBarcodeDetectionWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	BarcodeDetectionWidget * widget = new BarcodeDetectionWidget(progress);
	return widget;
}

BallotOptionTableWidget * AbstractFactoryWidget::createBallotOptionTableWidget()
{
	TableCenterWidget * table = FactoryMethodWidget::createTableWidget();
	FillTableWidget * fillTable = FactoryMethodWidget::createFillTableWidget(table);
	BallotOptionTableWidget * widget = new BallotOptionTableWidget(fillTable);
	return widget;
}

ContingencyCardGenWidget * AbstractFactoryWidget::createContingencyCardGenWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	ContingencyCardGenWidget * widget = new ContingencyCardGenWidget(progress);
	return widget;
}

MemoryStateWidget * AbstractFactoryWidget::createMemoryStateWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	MemoryStateWidget * widget = new MemoryStateWidget(progress);
	return widget;
}

AuthenticationWidget * AbstractFactoryWidget::createAuthenticationWidget()
{
	PollingPlaceInfoWidget * info = FactoryMethodWidget::createAuthenticationPollingPlaceInfoWidget();
	AuthenticationWidget * widget = FactoryMethodWidget::createAuthenticationWidget(info);
	return widget;
}

BeidErrorWidget * AbstractFactoryWidget::createBeidErrorWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	BeidErrorWidget * widget = new BeidErrorWidget(progress);
	return widget;
}

ReportPrintingWidget * AbstractFactoryWidget::createReportPrintingWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	ReportPrintingWidget * widget = new ReportPrintingWidget(progress);
	return widget;
}

DiagnosisBlockedWidget * AbstractFactoryWidget::createDiagnosisBlockedWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	DiagnosisBlockedWidget * widget = new DiagnosisBlockedWidget(progress);
	return widget;
}

DataUtilsValidatorWidget * AbstractFactoryWidget::createDataUtilsValidatorWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	DataUtilsValidatorWidget * widget = new DataUtilsValidatorWidget(progress);
	return widget;
}
