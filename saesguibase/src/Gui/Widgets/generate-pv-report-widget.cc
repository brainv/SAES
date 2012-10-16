/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#include <eid/EIDManager.hxx>
#include <Operation/Card/CardController.hxx>
#include "generate-pv-report-widget.h"
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>

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
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;

Smartmatic::Log::ISMTTLog* GeneratePVReportWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.GeneratePVReportWidget",GETTEXT_PACKAGE);

GeneratePVReportWidget::GeneratePVReportWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
	this->progress->setImage("ui/generate-pv-report.gif");
	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.GeneratePVReportWidget.GeneratingPVReportFile"));
	setWidget(progress);
}

GeneratePVReportWidget::~GeneratePVReportWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void GeneratePVReportWidget::initialize()
{
	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &GeneratePVReportWidget::start), false);
}

void GeneratePVReportWidget::dispose()
{

}

Glib::ustring GeneratePVReportWidget::GetWidgetName()
{
	return "GeneratePVReportWidget";
}

void GeneratePVReportWidget::start()
{
	CardController::getInstance()->dispose();

	bool errorHappen = false;
	try
	{
		MachineOperationManager::getInstance()->persistPVForm();
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.PersistPVFormSuccessfully"));
	}
	catch(Smartmatic::System::Exception::CryptoException & ex)
	{
		logger->Debug("GeneratePVReportWidget XmlException");
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorPersistPVForm"));
		errorHappen = true;
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		logger->Debug("GeneratePVReportWidget XmlException");
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorPersistPVForm"));
		errorHappen = true;
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		logger->Debug("GeneratePVReportWidget XmlException");
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorPersistPVForm"));
		errorHappen = true;
	}
	catch(...)
	{
		logger->Debug("GeneratePVReportWidget UnknowException");
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorPersistPVForm"));
		errorHappen = true;
	}

	if(!errorHappen)
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &GeneratePVReportWidget::end), 500);
	else
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &GeneratePVReportWidget::updateLabel),
								N_("Smartmatic.SAES.GUI.Widgets.GeneratePVReportWidget.ErrorMessage")), 500);
}

void GeneratePVReportWidget::end()
{
	m_done_signal.emit();
}

void GeneratePVReportWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

bool GeneratePVReportWidget::isEnabledButtonExitWizard()
{
	return false;
}
