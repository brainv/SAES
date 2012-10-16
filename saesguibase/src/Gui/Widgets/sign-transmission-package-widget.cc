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
#include "sign-transmission-package-widget.h"
#include <Operation/Card/CardController.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation::Card;

Smartmatic::Log::ISMTTLog* SignTransmissionPackageWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.SignTransmissionPackageWidget",GETTEXT_PACKAGE);

SignTransmissionPackageWidget::SignTransmissionPackageWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
	this->progress->setImage("ui/sign-package.gif");
	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.SignTransmissionPackageWidget.SignTransmissionPackage"));
	setWidget(progress);
}

SignTransmissionPackageWidget::~SignTransmissionPackageWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void SignTransmissionPackageWidget::initialize()
{
	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &SignTransmissionPackageWidget::start), false);
}

void SignTransmissionPackageWidget::dispose()
{

}

Glib::ustring SignTransmissionPackageWidget::GetWidgetName()
{
	return "";
}

void SignTransmissionPackageWidget::start()
{
	CardController::getInstance()->dispose();

	bool errorHappen = false;
	try
	{
		MachineOperationManager::getInstance()->generateTransmissionPackageSigFile();
	}
	catch(CryptoException & ex)
	{
		logger->Debug("SignTransmissionPackageWidget CryptoException");
		errorHappen = true;
	}
	catch(SignedException & ex)
	{
		logger->Debug("SignTransmissionPackageWidget SignedException");
		errorHappen = true;
	}
	catch(XmlException & ex)
	{
		logger->Debug("SignTransmissionPackageWidget XmlException");
		errorHappen = true;
	}
	catch(SignByCardIDException & ex)
	{
		logger->Debug("SignTransmissionPackageWidget SignByCardIDException");
		errorHappen = true;
	}

	if(!errorHappen)
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignTransmissionPackageWidget::end), 500);
	else
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &SignTransmissionPackageWidget::updateLabel),
						N_("Smartmatic.SAES.GUI.Widgets.SignTransmissionPackageWidget.ErrorMessage")), 500);
}

void SignTransmissionPackageWidget::end()
{
	m_done_signal.emit();
}

void SignTransmissionPackageWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

bool SignTransmissionPackageWidget::isEnabledButtonExitWizard()
{
	return false;
}
