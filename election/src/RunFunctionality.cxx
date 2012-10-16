/*
 * RunFunctionality.cxx
 *
 *  Created on: 23/08/2011
 *      Author: soto
 */

#include "RunFunctionality.hxx"
#include <Operation/functionality-initiator.h>
#include <Functionalities/saes-functionality-manager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

using namespace Smartmatic::SAES::Election;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Configuration;

void RunFunctionality::start()
{
	FunctionalityInitiator::Register();
	SaesMenuOptionDescriptor descriptor = SAESGUIConfigurationManager::Current()->getRunFunctionalityDescriptor();
	SaesFunctionalityManager::Current()->ExecuteOptionSelected(descriptor);
	Gtk::Main::run();
}
