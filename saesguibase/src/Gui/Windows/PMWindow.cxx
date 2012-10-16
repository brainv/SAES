/**
 * @file PMWindow.cxx
 * @brief Body class pm window
 * @date 19/10/2011
 * @author Yadickson Soto
 */

#include "PMWindow.hxx"

using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Widgets;

PMWindow::PMWindow()
: RunMachineWindow()
{
	initialize();
	nextStep();
	show();
}

PMWindow::~PMWindow()
{

}

void PMWindow::initialize()
{
	wizardStep.push_back(INSTALL_MACHINE);
	wizardStep.push_back(AUTOMATIC_DIAGNOSTIC);
	wizardStep.push_back(INITIATOR);
	//wizardStep.push_back(REPORT_INSTALL);
	wizardStep.push_back(CONTINGENCY_CARD);
	wizardStep.push_back(ID_CARD_INSTALL);
	wizardStep.push_back(PROCESS);
	wizardStep.push_back(END);
}
