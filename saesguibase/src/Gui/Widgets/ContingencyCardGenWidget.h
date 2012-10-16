/*
 * ContingencyCardGenWidget.h
 *
 *  Created on: Oct 17, 2011
 *      Author: marcel
 */

#ifndef CONTINGENCYCARDGENWIDGET_H_
#define CONTINGENCYCARDGENWIDGET_H_

#include <list>
#include <gtkmm.h>
#include <pangomm.h>
#include <Printing/ContingencyCardReport.h>
#include <Voting/VotingDevice/contingency-card-data-schema.hxx>
#include <Widgets/smartmatic-button.h>
#include "Printing/BasePrintDocument.h"
#include "Printing/PrintDocumentClient.h"
#include "Printing/PrintDocumentResult.h"
#include <Log/ISMTTLog.h>
#include "ProgressWidget.hxx"
#include <Widgets/StepWidget.hxx>

namespace Smartmatic {
namespace SAES {
namespace GUI {
namespace Widgets {

class ContingencyCardGenWidget : public Smartmatic::GUI::Widgets::StepWidget
, Smartmatic::SAES::Printing::PrintDocumentClient
{

public:

	typedef enum
	{
		CONTCARD_WAITING_INSERTION,
		CONTCARD_WRITING,
		CONTCARD_PRINTING_REPORT,
		CONTCARD_WAITING_REMOVAL,
		CONTCARD_SHOWING_RESULTS,
		CONTCARD_ERROR_HANDLING

	} OpStateEnumType;

	typedef enum
	{
		CONTCARD_SUCCESS,
		CONTCARD_ERROR_READER,
		CONTCARD_ERROR_WRITING,
		CONTCARD_ERROR_PRINTING,
		CONTCARD_FATAL_ERROR

	} ContingencyErrorEnumType;

	/**
	 * @brief Class constructor
	 * @param progress
	 * @date 20/03/2012
	 * @author Yadickson Soto
	 */
	ContingencyCardGenWidget (ProgressWidget * progress);
	/**
	 * @brief Class destroy
	 * @date 20/03/2012
	 * @author Yadickson Soto
	 */
	virtual ~ContingencyCardGenWidget ();
	/**
	 * @brief virtual method getter title
	 * @return title
	 * @date 30/03/2012
	 * @author Yadickson Soto
	 */
	virtual std::string getTitleText();
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

	void onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res);

	typedef sigc::signal<void, ContingencyErrorEnumType> signal_card_generated_type;
	signal_card_generated_type card_generated_signal () { return this->on_card_generated; }

private:

	ProgressWidget * progress; ///< progress widget
	Gtk::Frame * mainFrame; ///< main frame
	Gtk::VBox * mainVBox; ///< main vbox
	Gtk::Frame * centerFrame; ///< center frame
	Gtk::HBox * hboxButton; ///< hbox button
	Smartmatic::GUI::Widgets::SmartmaticButton * retryButton; ///< retry button
	Smartmatic::GUI::Widgets::SmartmaticButton * quitButton; ///< quit button

	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

	Smartmatic::SAES::Voting::VotingDevice::ContingencyCardData m_CardData;
	std::string m_Pin;
	Glib::ustring m_ErrorMsg;

	sigc::connection mconn_wait_card_insertion;
	sigc::connection mconn_wait_card_writing;
	sigc::connection mconn_wait_printing;
	sigc::connection mconn_wait_card_removal;

	std::list<OpStateEnumType> steps;
	std::list<OpStateEnumType>::iterator current_step;
	std::list<OpStateEnumType>::iterator result_step;

	ContingencyErrorEnumType current_error;

	signal_card_generated_type on_card_generated;

	Smartmatic::SAES::Printing::ContingencyCardReport* report;

	void ManageState ();
	void WriteContingencyData ();
	void PrintContingencyReport ();

	void SetScreen ();
	void SetResultScreen ();
	void SetErrorScreen ();

	void OnRetryButtonClicked ();
	void OnQuitButtonClicked ();

	bool DetectCard ();
	bool DetectRemoval ();
	void Wait ();
	void WaitAndExit ();

};

} /* namespace Widgets */
} /* namespace GUI */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CONTINGENCYCARDGENWIDGET_H_ */
