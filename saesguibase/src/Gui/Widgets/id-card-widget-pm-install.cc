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

#include <Gui/Widgets/id-card-widget-pm-install.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
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

using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

Smartmatic::Log::ISMTTLog* IDCardWidgetPMInstall::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.IDCardWidgetPMInstall",GETTEXT_PACKAGE);

IDCardWidgetPMInstall::IDCardWidgetPMInstall()
:IDCardWidget(N_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetPMInstall.IdCardMessage"),
              N_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetPMInstall.IdCardMessageConfirm"),
              true)
{
	idConfig = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getPMInstall();
	ShowElements();
}

IDCardWidgetPMInstall::~IDCardWidgetPMInstall()
{
	dispose();
}

void IDCardWidgetPMInstall::on_buttonAccept_clicked()
{
	GetData();

	if(!CheckCompleteData())
		ShowInCompleteData();
	else
	{
		try
		{
			MachineOperationManager::getInstance()->PersistencePMInstallerData(citizenInfo);
		}
		catch(CryptoException & ex)
		{
			logger->Debug("IDCardWidgetPMInstall CryptoException");
			//TODO handle exception
		}
		catch(SignedException & ex)
		{
			logger->Debug("IDCardWidgetPMInstall SignedException");
			//TODO handle exception
		}
		catch(XmlException & ex)
		{
			logger->Debug("IDCardWidgetPMInstall XmlException");
			//TODO handle exception
		}
		catch(...)
		{
			//TODO handle exception
		}

		m_done_signal.emit();
	}
}

std::string IDCardWidgetPMInstall::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.InitializationWindow.Title");
}
