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

#include <Gui/Widgets/id-card-widget-close-election.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/MachineOperationManager.hxx>

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

#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>

using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

Smartmatic::Log::ISMTTLog* IDCardWidgetCloseElection::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseElection",GETTEXT_PACKAGE);

IDCardWidgetCloseElection::IDCardWidgetCloseElection()
:IDCardWidget(_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseElection.IdCardMessage"),
              _("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseElection.IdCardMessageConfirm"),
              true)
{
	idConfig = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getCloseElection();
	ShowElements();
}

IDCardWidgetCloseElection::~IDCardWidgetCloseElection()
{
	dispose();
}

void IDCardWidgetCloseElection::on_buttonAccept_clicked()
{
	GetData();

	if(!CheckCompleteData())
		ShowInCompleteData();
	else
	{
		bool errorHappen = false;
		try
		{
			MachineOperationManager::getInstance()->PersistenceElectionCloserData(citizenInfo);
		}
		catch(CryptoException & ex)
		{
			logger->Debug("IDCardWidgetCloseElection CryptoException");
			errorHappen = true;
		}
		catch(SignedException & ex)
		{
			logger->Debug("IDCardWidgetCloseElection SignedException");
			errorHappen = true;
		}
		catch(XmlException & ex)
		{
			logger->Debug("IDCardWidgetCloseElection XmlException");
			errorHappen = true;
		}
		catch(...)
		{
			logger->Debug("IDCardWidgetCloseElection Unknow Error");
			errorHappen = true;
		}

		if(!errorHappen)
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidgetCloseElection::on_done), 10);
		else
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidgetCloseElection::UpdateLabel), 10);
	}
}


void IDCardWidgetCloseElection::on_done()
{
	m_done_signal.emit();
}

void IDCardWidgetCloseElection::UpdateLabel()
{
	remove();
	Label* label = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseElection.ErrorMessage")));
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);
}
