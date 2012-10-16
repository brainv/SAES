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

#include "assisted-activation-question-widget.h"
#include <Widgets/smartmatic-button.h>
#include <Log/ISMTTLog.h>
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

Smartmatic::Log::ISMTTLog* AssistedActivationQuestionWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationQuestionWidget",GETTEXT_PACKAGE);

AssistedActivationQuestionWidget::AssistedActivationQuestionWidget(string questionTitle,
		string okButtonText, string cancelButtonText, std::string instruction, bool buttonsVertical)
{
	answer = false;
	stopOnCancel = false;
	stopOnOk = false;

	Label* questionLabel = manage(new Label(questionTitle));
	questionLabel->set_size_request(700, 200);
	//questionLabel->set_line_wrap(true);
	//questionLabel->set_justify(JUSTIFY_CENTER);
		Pango::FontDescription fontTitle = questionLabel->get_style()->get_font();
		fontTitle.set_size(20*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	questionLabel->modify_font(fontTitle);
	questionLabel->set_alignment(0.5, 0.5);

	SmartmaticButton* okButton = manage(new SmartmaticButton(okButtonText));
	okButton->signal_clicked().connect(sigc::mem_fun(*this, &AssistedActivationQuestionWidget::on_okButton_clicked));

	SmartmaticButton* cancelButton = manage(new SmartmaticButton(cancelButtonText));
	cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &AssistedActivationQuestionWidget::on_cancelButton_clicked));

	ButtonBox* btnBox = NULL;
	if(buttonsVertical)
	{
		btnBox = manage(new VButtonBox());

		cancelButton->set_size_request(200, 70);

		okButton->set_size_request(200, 70);
	}
	else
	{
		btnBox = manage(new HButtonBox());

		cancelButton->set_size_request(170, 70);
		cancelButton->SetButtonType(SmartmaticButton::Cancel);
		cancelButton->WidgetsPosition(5,0,0);

		okButton->set_size_request(170, 70);
		okButton->SetButtonType(SmartmaticButton::Ok);
		okButton->WidgetsPosition(5,0,0);
	}

	btnBox->set_size_request(300, 200);
	btnBox->set_layout(BUTTONBOX_SPREAD);
	btnBox->pack_start(*cancelButton, false, false);
	btnBox->pack_start(*okButton, false, false);

	Label* label = manage(new Label());
	label->set_text(instruction);
	label->set_size_request(-1, 60);
	LabelConfiguration instructionConfiguration = SAESGUIConfigurationManager::Current()->GetFillAssistedInforConfiguration();
	LabelConfiguration::SetLabelConfiguration(label, instructionConfiguration);

	VBox* vbox = manage(new VBox());
	vbox->pack_start(*label, false, false);
	vbox->pack_start(*questionLabel, false, false);
	vbox->pack_start(*btnBox, false, false);

	setWidget(vbox);
}

AssistedActivationQuestionWidget::~AssistedActivationQuestionWidget()
{

}

bool AssistedActivationQuestionWidget::StopWizard()
{
	bool varReturn;
	if(stopOnOk || stopOnCancel)
	{
		varReturn = true;
	}
	else
	{
		varReturn = false;
	}

	return varReturn;
}

void AssistedActivationQuestionWidget::on_okButton_clicked()
{
	answer = true;
	stopOnCancel = false;
	m_done_signal.emit();
}

void AssistedActivationQuestionWidget::on_cancelButton_clicked()
{
	answer = false;
	stopOnOk = false;
	m_done_signal.emit();
}

void AssistedActivationQuestionWidget::SendStopWizardOnCancel()
{
	stopOnCancel = true;
}

void AssistedActivationQuestionWidget::SendStopWizardOnOK()
{
	stopOnOk = true;
}

bool AssistedActivationQuestionWidget::GetAnswer()
{
	return answer;
}

void AssistedActivationQuestionWidget::initialize()
{

}

void AssistedActivationQuestionWidget::dispose()
{

}

void AssistedActivationQuestionWidget::reset()
{
	answer = false;
	stopOnCancel = false;
}
