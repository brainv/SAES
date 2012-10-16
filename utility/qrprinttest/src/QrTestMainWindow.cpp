/*
 * QrTestMainWindow.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: root
 */

#include <config.h>
#include <glibmm.h>
#include <iostream>
#include "QRTestController.h"
#include "QrTestMainWindow.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/MemoryPathController.h>

#define UI_FILE DATADIR"/"PACKAGE_NAME"/ui/qrprinttest.ui"

using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;

//============================== Life Cycle ==================================//

QrTestMainWindow::QrTestMainWindow()
{
	PrinterBackendType & backend (SAESCommonConfigurationManager::Current()->getPrinterBackendType());
	backend = PrinterBackendType::CONFIGURATION_DIRECTPRINTING;

	ConfigurationBasePath & basePath (SAESCommonConfigurationManager::Current()->getConfigBasePath());
	basePath.setRulesBasePath(RulesBasePathType::CONFIGURATION_VM_RULE);

	MemoryPathController::getInstance()->updatePaths();

	m_TestCount = 0;
	m_AppController = QRTestController::GetInstance ();


	InitWidgets ();
}




QrTestMainWindow::~QrTestMainWindow()
{
	// TODO Auto-generated destructor stub
}



//============================== Auxiliar ====================================//

void QrTestMainWindow::InitWidgets ()
{
	try
	{
		m_Builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}

	// Execute button

	m_Builder->get_widget ("executeButton", m_ExecuteButton);
	m_ExecuteButton->signal_clicked ().connect (sigc::mem_fun (*this, &QrTestMainWindow::on_executeButton_clicked));


	// AddTest button

	m_Builder->get_widget ("addTestButton", m_AddTestButton);
	m_AddTestButton->signal_clicked ().connect (sigc::mem_fun (*this, &QrTestMainWindow::on_addTestButton_clicked));


	// Tests box

	m_TestsBox = Gtk::manage (new Gtk::VBox ());

	QRTestWidget* ref_test1 = Gtk::manage (new QRTestWidget (m_TestsBox->children().empty()));
	m_TestParams.push_back(ref_test1);
	m_TestsBox->pack_start (*ref_test1, false, false);

	// testScrolledwindow

	m_Builder->get_widget ("testScrolledwindow", m_TestScrolledwindow);
	m_TestScrolledwindow->set_policy (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_TestScrolledwindow->add (*m_TestsBox);

	// FixedContainer

//	m_FixedContainer.add (*m_TestScrolledwindow);

	// Main Notebook

//	m_MainNotebook.append_page (m_FixedContainer, "Test definition");

	// MainFrame

	m_Builder->get_widget ("mainFrame", m_MainFrame);
	m_MainFrame->add (*m_TestScrolledwindow);

	// Top

	this->add (*m_MainFrame);
	this->set_default_size (650, 600);
	this->set_position (Gtk::WIN_POS_CENTER);
	this->show_all_children ();

}

void QrTestMainWindow::AddTest ()
{
	QRTestWidget* ref_test = Gtk::manage (new QRTestWidget (m_TestsBox->children().empty()));
	m_TestParams.push_back(ref_test);

	m_TestsBox->pack_start (*ref_test, false, false);
	m_TestsBox->show_all_children ();
}


//============================ Signal Handling ===============================//

void QrTestMainWindow::on_addTestButton_clicked ()
{
	AddTest ();
}

void QrTestMainWindow::on_executeButton_clicked ()
{
	std::list<QRTestController::QrTestParamsType> test_cases;

	for (std::list<QRTestWidget*>::const_iterator it = m_TestParams.begin ()
			; it != m_TestParams.end ()
			; it++)
		test_cases.push_back((*it)->GetParams());

	m_AppController->ExecuteTest (test_cases);
}





