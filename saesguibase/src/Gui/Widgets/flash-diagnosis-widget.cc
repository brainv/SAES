/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "flash-diagnosis-widget.h"
#include "Configuration/label-configuration.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Gui/Widgets/FactoryMethodWidget.hxx>
#include <Runtime/Environment/MemoryPathController.h>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <queue>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace std;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;

FlashDiagnosisWidget::FlashDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
:BasicDiagnosticWidget(Title, OperationStatus::Flash, hasOk,hasCancel,hasMessage,showButtons)
{
	LaunchConfiguration & launchConfig(SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());
	AppType apptoLaunch = launchConfig.getAppType();

	bool checkBoth = MemoryPathController::getInstance()->getRule() == RulesBasePathType::CONFIGURATION_PM_RULE;

	progressWidget = FactoryMethodWidget::createProgressWidget();
	diagnosis = new FlashDiagnosis(checkBoth);

	LabelConfiguration diagConf = SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	progressWidget->setTextConfig(diagConf);

	progressWidget->setImage("ui/Flash.png");

	setDiagnosticFrame(*progressWidget);
	this->show_all_children();
}

FlashDiagnosisWidget::~FlashDiagnosisWidget()
{
	if(progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
	if (diagnosis)
	{
		delete diagnosis;
		diagnosis = NULL;
	}
}

void FlashDiagnosisWidget::Initialize()
{
	diagnosis->setStatus(OperationStatus::NotDiagnosed);
	progressWidget->setText(diagnosis->getMessage());

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &FlashDiagnosisWidget::SendTest), 1000);
}

void FlashDiagnosisWidget::SendTest()
{
	diagnosis->setStatus(OperationStatus::Run);
	progressWidget->setText(diagnosis->getMessage());
    if(!Glib::thread_supported()) Glib::thread_init();
    Glib::Thread::create(sigc::mem_fun(*this, &FlashDiagnosisWidget::test), false);
}

void FlashDiagnosisWidget::test()
{
	diagnosis->test();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &FlashDiagnosisWidget::showResult), 1000);
}

void FlashDiagnosisWidget::showResult()
{
	progressWidget->setText(diagnosis->getMessage());
	signalContinue_detected.emit();
}

void FlashDiagnosisWidget::Dispose()
{

}
