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

#include "persist-transmission-package-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* PersistTransmissionPackageWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PersistTransmissionPackageWidget",GETTEXT_PACKAGE);

PersistTransmissionPackageWidget::PersistTransmissionPackageWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
	this->progress->setImage("ui/persist-package.gif");
	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.PersistTransmissionPackageWidget.PersistTransmissionPackage"));
	setWidget(progress);
}

PersistTransmissionPackageWidget::~PersistTransmissionPackageWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void PersistTransmissionPackageWidget::initialize()
{
	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &PersistTransmissionPackageWidget::start), false);
}

void PersistTransmissionPackageWidget::dispose()
{

}

void PersistTransmissionPackageWidget::start()
{
	bool errorHappen = false;
	try
	{
		//MachineOperationManager::getInstance()->persistTransmissionPackage();
	}
	catch(CryptoException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget CryptoException");
		errorHappen = true;
	}
	catch(SignedException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget SignedException");
		errorHappen = true;
	}
	catch(XmlException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget XmlException");
		errorHappen = true;
	}

	sleep(3);

	if(!errorHappen)
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PersistTransmissionPackageWidget::end), 500);
	else
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &PersistTransmissionPackageWidget::updateLabel),
				N_("Smartmatic.SAES.GUI.Widgets.PersistTransmissionPackageWidget.ErrorMessage")), 500);
}

void PersistTransmissionPackageWidget::end()
{
	m_done_signal.emit();
}

void PersistTransmissionPackageWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

Glib::ustring PersistTransmissionPackageWidget::GetWidgetName()
{
	return "";
}

bool PersistTransmissionPackageWidget::isEnabledButtonExitWizard()
{
	return false;
}
