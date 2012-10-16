/**
 * @file	ReportPrintingWidget.h
 *
 * @brief	Declares the report printing widget class.
 */

#ifndef REPORTPRINTINGWIDGET_H_
#define REPORTPRINTINGWIDGET_H_

#include <gtkmm.h>
#include <glibmm.h>
#include <Printing/ReportPrintingController.h>
#include <Widgets/smartmatic-button.h>
#include "Configuration/label-configuration.h"
#include "ProgressWidget.hxx"
#include <Widgets/StepWidget.hxx>

namespace Smartmatic
{
namespace SAES
{
namespace GUI
{
namespace Widgets
{
/**
 * @class	ReportPrintingWidget
 *
 * @brief	Report printing widget.
 *
 * @author	Cesar.bonilla
 * @date	4/29/2011
 */

class ReportPrintingWidget : public Smartmatic::GUI::Widgets::StepWidget
{
public:

	/**
	 * @brief	Class constructor.
	 * @param 	progress progress images
	 * @author	Yadickson Soto
	 * @date	29/05/2012
	 */
	ReportPrintingWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);

	/**
	 * @fn	virtual ReportPrintingWidget::~ReportPrintingWidget();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	virtual ~ReportPrintingWidget();

	// Signaling

	/**
	 * @typedef	sigc::signal<void, bool> signal_finished_t
	 *
	 * @brief	Defines an alias representing the signal finished t. .
	 */

	typedef sigc::signal<void, bool> signal_finished_t;

	/**
	 * @typedef	sigc::signal<void> signal_begin_print_t
	 *
	 * @brief	Defines an alias representing the signal begin print t. .
	 */

	typedef sigc::signal<void> signal_begin_print_t;

	/**
	 * @fn	signal_finished_t ReportPrintingWidget::signal_finished ()
	 *
	 * @brief	Raises the finished event.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 *
	 * @return	.
	 */

	signal_finished_t signal_finished () { return m_SignalFinished; }

	/**
	 * @fn	signal_finished_t ReportPrintingWidget::signal_begin_print ()
	 *
	 * @brief	Raises the begin print event.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 *
	 * @return	.
	 */

	signal_begin_print_t signal_begin_print () { return m_SignalBeginPrint; }

private:

	Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< progress widget

	typedef enum WidgetStateEnum
	{
		RPWDGT_INIT,
		RPWDGT_PRINTING,
		RPWDGT_PRINTERROR,
		RPWDGT_FINISHED

	} WidgetStateEnumType;

	Smartmatic::SAES::Printing::ReportPrintingController m_ReportPrinterController; ///< The report printer controller

	WidgetStateEnumType m_CurrentState; ///< The current state

	Gtk::Label* m_ReportListTitle;  ///< The report list title

	Gtk::Table* m_TopTableLayout;   ///< The top table layout

	Smartmatic::GUI::Widgets::SmartmaticButton* m_PrintButton; ///< The print button

	Gtk::VBox* m_ReportListVBox;	///< The report list v box

	Gtk::EventBox* eventbox_ReportListTitle; ///< The report list title event box
	Gtk::EventBox * mainEventBox; ///< main event box

	Gtk::HBox* outsideHbox;	///< The outside h box

	signal_finished_t m_SignalFinished; ///< The signal finished
	signal_begin_print_t m_SignalBeginPrint; ///< The signal begin print

	sigc::connection m_SignalPrintFileConn; ///< The signal print file connection
	sigc::connection m_SignalPrintFinishedConn; ///< The signal print finished connection
	sigc::connection m_SignalErrorDetectedConn; ///< The signal error detected connection

	/**
	 * @fn	void ReportPrintingWidget::LoadGUI ();
	 *
	 * @brief	Loads the graphical user interface.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void LoadGUI ();

	/**
	 * @fn	void ReportPrintingWidget::DisplayState (WidgetStateEnumType state);
	 *
	 * @brief	Displays a state described by state.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 *
	 * @param	state	The state.
	 */

	void DisplayState (WidgetStateEnumType state);

	/**
	 * @fn	void ReportPrintingWidget::OnPrintButtonClicked ();
	 *
	 * @brief	Executes the print button clicked action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void OnPrintButtonClicked ();

	/**
	 * @fn	void ReportPrintingWidget::OnBeginReportPrinting ();
	 *
	 * @brief	Executes the begin report printing action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void OnBeginReportPrinting ();

	/**
	 * @fn	void ReportPrintingWidget::OnAllReportPrintingFinished ();
	 *
	 * @brief	Executes all report printing finished action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void OnAllReportPrintingFinished ();

	/**
	 * @fn	void ReportPrintingWidget::OnReportPrintErrorDetected ();
	 *
	 * @brief	Executes the report print error detected action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void OnReportPrintErrorDetected ();

	/**
	 * @fn	void ReportPrintingWidget::PrintReportsThreadBody ();
	 *
	 * @brief	Print reports thread body.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/29/2011
	 */

	void PrintReportsThreadBody ();
};

}
}
}
}

#endif /* REPORTPRINTINGWIDGET_H_ */
