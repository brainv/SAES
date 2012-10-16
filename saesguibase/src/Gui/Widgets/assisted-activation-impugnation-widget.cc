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

#include "assisted-activation-impugnation-widget.h"
#include <Widgets/smartmatic-button.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include "Configuration/label-configuration.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <System/Utils/StringUtils.hxx>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::Utils;

Smartmatic::Log::ISMTTLog* AssistedActivationImpugnationWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationImpugnationWidget",GETTEXT_PACKAGE);

AssistedActivationImpugnationWidget::AssistedActivationImpugnationWidget(string textTitle, string acceptButtonText, std::string instruction)
{
	Label* label = manage(new Label(textTitle));
	//label->set_size_request(700, 200);
		Pango::FontDescription fontTitle = label->get_style()->get_font();
		fontTitle.set_size(17*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);
	label->set_alignment(0.5, 0.5);

	acceptButton = manage(new SmartmaticButton(acceptButtonText));
	acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &AssistedActivationImpugnationWidget::on_acceptButton_clicked));
	acceptButton->set_size_request(150, 60);
	acceptButton->set_sensitive(false);

	VButtonBox* btnBox = manage(new VButtonBox());
	btnBox->set_layout(BUTTONBOX_CENTER);
	btnBox->pack_start(*acceptButton, false, false);

	textView = manage(new Smartmatic::GUI::Widgets::SmartmaticTextView());
	textView->set_size_request(600, 240);

	Alignment* align = manage(new Alignment());
	align->set(0.5, 0.5, 0, 0);
	align->add(*textView);

	Label* label1 = manage(new Label());
	label1->set_text(instruction);
	label1->set_size_request(-1, 60);

	LabelConfiguration instructionConfiguration = SAESGUIConfigurationManager::Current()->GetFillAssistedInforConfiguration();
	LabelConfiguration::SetLabelConfiguration(label1, instructionConfiguration);

	VBox* vbox = manage(new VBox(false, 30));
	vbox->pack_start(*label1, false, false);
	vbox->pack_start(*label, false, false);
	vbox->pack_start(*align, false, false);
	vbox->pack_start(*btnBox, false, false);

	acceptButton->set_sensitive(true);

	setWidget(vbox);
}

AssistedActivationImpugnationWidget::~AssistedActivationImpugnationWidget()
{

}

void AssistedActivationImpugnationWidget::on_acceptButton_clicked()
{
	std::string text = textView->getText();
	std::string data = StringUtils::trim(text);

	if(!data.empty())
	{
		m_done_signal.emit();
	}
}

void AssistedActivationImpugnationWidget::initialize()
{
	textView->setText("");
}

void AssistedActivationImpugnationWidget::dispose()
{

}

std::string AssistedActivationImpugnationWidget::GetReason()
{
	return textView->getText();
}
