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

#include "OpenElectionStatusWidget.hxx"
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

Smartmatic::Log::ISMTTLog* OpenElectionStatusWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.OpenElectionStatusWidget",GETTEXT_PACKAGE);

OpenElectionStatusWidget::OpenElectionStatusWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
//	this->progress->setImage("ui/open-election.gif");
//	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.OpenElectionStatusWidget.OpenElection"));
//	setWidget(progress);
}

OpenElectionStatusWidget::~OpenElectionStatusWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void OpenElectionStatusWidget::initialize()
{
	m_disable_close_signal.emit();

	bool errorHappen = false;

	try
	{
		MachineOperationManager::getInstance()->openElection();
	}
	catch(CryptoException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ErrorOpeningElection"));
		logger->Debug("OpenElectionStatusWidget CryptoException");
		errorHappen = true;
	}
	catch(SignedException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ErrorOpeningElection"));
		logger->Debug("OpenElectionStatusWidget SignedException");
		errorHappen = true;
	}
	catch(XmlException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ErrorOpeningElection"));
		logger->Debug("OpenElectionStatusWidget XmlException");
		errorHappen = true;
	}
	catch(...)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ErrorOpeningElection"));
		logger->Debug("OpenElectionStatusWidget XmlException");
		errorHappen = true;
	}

	if(!errorHappen)
	{
		end();
	}
	else
	{
		updateLabel(N_("Smartmatic.SAES.GUI.Widgets.OpenElectionStatusWidget.ErrorMessage"));
	}
}

void OpenElectionStatusWidget::dispose()
{

}

Glib::ustring OpenElectionStatusWidget::GetWidgetName()
{
	return "";
}

void OpenElectionStatusWidget::end()
{
	m_done_signal.emit();
}

void OpenElectionStatusWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

bool OpenElectionStatusWidget::isEnabledButtonExitWizard()
{
	return false;
}
