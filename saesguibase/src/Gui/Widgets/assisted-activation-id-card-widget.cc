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

#include "assisted-activation-id-card-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Log/SMTTLogManager.h>
#include "Configuration/label-configuration.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

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
using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* AssistedActivationIDCardWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidget",GETTEXT_PACKAGE);

AssistedActivationIDCardWidget::AssistedActivationIDCardWidget(std::string title, std::string instruction)
{
	Label* label = manage(new Label());
	label->set_text(instruction);
	label->set_size_request(-1, 60);

	LabelConfiguration instructionConfiguration = SAESGUIConfigurationManager::Current()->GetFillAssistedInforConfiguration();
	LabelConfiguration::SetLabelConfiguration(label, instructionConfiguration);

	idWidget = NULL;
	idWidget = new IDCardWidget(title,"",true,true);
	idWidget->setIDConfig(SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getAssistedActivation());
	idWidget->signal_accept_clicked().connect(sigc::mem_fun(*this, &AssistedActivationIDCardWidget::on_done));
	idWidget->MaintainInfo();

	VBox* vbox = manage(new VBox());
	vbox->pack_start(*label, false, false);
	vbox->pack_start(*idWidget);

	setWidget(vbox);
}

AssistedActivationIDCardWidget::~AssistedActivationIDCardWidget()
{
	if(idWidget) delete idWidget;
}

void AssistedActivationIDCardWidget::initialize()
{
	idWidget->initialize();
}

void AssistedActivationIDCardWidget::dispose()
{
	idWidget->dispose();
	usleep(300000);
}

void AssistedActivationIDCardWidget::on_done()
{
	idWidget->dispose();
	m_done_signal.emit();
}

Smartmatic::SAES::EID::CitizenInfo AssistedActivationIDCardWidget::GetCitizenInfo()
{
	return idWidget->getCitizenInfo();
}
