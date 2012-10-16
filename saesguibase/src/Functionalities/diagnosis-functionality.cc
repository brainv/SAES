/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "diagnosis-functionality.h"
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* DiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.DiagnosisFunctionality",GETTEXT_PACKAGE);

DiagnosisFunctionality* DiagnosisFunctionality::current_instance = NULL;

DiagnosisFunctionality* DiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new DiagnosisFunctionality();

	return current_instance;
};

DiagnosisFunctionality::DiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	frame = NULL;
}

void DiagnosisFunctionality::Initialize()
{
	enableExitButton();
};

void DiagnosisFunctionality::deleteElement()
{
	if (frame)
	{
		delete frame;
		frame = NULL;
	}
};

Gtk::Widget* DiagnosisFunctionality::GetFrame()
{
	frame = new Gtk::Frame();
	return frame;
};

string DiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DiagnosisFunctionality.Diagnosis");
};

MenuOptionDescriptor DiagnosisFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MDiagnosisFunctionality,false);
};

void DiagnosisFunctionality::Dispose()
{
};

Smartmatic::Log::ISMTTLog* DiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring DiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring DiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.DiagnosisFunctionality.LogCloseFunctionality");
}
