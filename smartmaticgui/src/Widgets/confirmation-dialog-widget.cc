/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file party-selection-widget.cc
 * @brief PartySelectionWidget body
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#include "confirmation-dialog-widget.h"
#include <Configuration/SmartmaticGUIConfiguration-schema.hxx>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

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

using namespace Smartmatic::GUI::Configuration;
using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

ConfirmationDialogWidget::ConfirmationDialogWidget(string confirmationText, string headerTitle, string footerTitle,
                                                   string confirmButtonText, string cancelButtonText, 
                                                   bool placeButtonVertical, bool skipFalse)
{

	//SET SOUNDS
	SoundConfirmationDialog = SMTTGUIConfigurationManager::Current()->getConfirmationDialogSound();
	bool switchButtons = false;
	
	switch(SMTTGUIConfigurationManager::Current()->getButtonsQuestionConfiguration())
	{
		case ButtonsQuestionConfiguration::CONFIGURATION_ACCEPT_CANCEL:
			switchButtons = true;
			break;
		case ButtonsQuestionConfiguration::CONFIGURATION_CANCEL_ACCEPT:
			switchButtons = false;
			break;
	}

	this->skipFalse = skipFalse;
	this->headerTitle = _(headerTitle.c_str());
	this->footerTitle = _(footerTitle.c_str());
	this->buttonVerticals = placeButtonVertical;
	this->confirmationText = _(confirmationText.c_str());
	secondConfirm = false;
	selectOk = false;
	
	buttonBoxAlignment = manage(new Alignment());
	buttonBoxAlignment->set_padding(0, 25, 50, 50); //TODO configuration
	hButtonsBox = manage(new HBox(true, 50)); //TODO configuration
	vButtonsBox = manage(new VBox(true, 20)); //TODO configuration
	externalButtonsBox = manage(new HBox());

	confirmationLabel = manage(new Label(confirmationText));
	confirmationLabel->set_alignment(0.5, 0.5);//TODO configuration
	confirmationLabel->set_padding(0, 0);
	confirmationLabel->set_line_wrap(true);
	confirmationLabel->set_line_wrap_mode(Pango::WRAP_WORD);
	Pango::FontDescription fontTitle = confirmationLabel->get_style()->get_font();
	fontTitle.set_size(17*Pango::SCALE);
	confirmationLabel->modify_font(fontTitle);

	int buttonsHeight = 80; //TODO configuration
	int buttonsWidth = 150; //TODO configuration

	
	confirmButton = manage(new SmartmaticButton());
	confirmButton->set_size_request(buttonsWidth, buttonsHeight);
	if(confirmButtonText.empty()) confirmButton->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Accept"));
	else confirmButton->SetLabel(_(confirmButtonText.c_str()));
	confirmButton->WidgetsPosition(5,0,0);
	confirmButton->signal_clicked().connect(sigc::mem_fun(this,&ConfirmationDialogWidget::on_confirmButton_clicked));

	cancelButton = manage(new SmartmaticButton());
	cancelButton->set_size_request(buttonsWidth, buttonsHeight);
	if(cancelButtonText.empty()) cancelButton->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Cancel"));
	else cancelButton->SetLabel(_(cancelButtonText.c_str()));
	cancelButton->WidgetsPosition(5,0,0);
	cancelButton->signal_clicked().connect(sigc::mem_fun(this,&ConfirmationDialogWidget::on_cancelButton_clicked));

	confirmButtonDuplex = manage(new SmartmaticButton());
	confirmButtonDuplex->set_size_request(buttonsWidth, buttonsHeight);
	confirmButtonDuplex->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Accept"));
	confirmButtonDuplex->WidgetsPosition(5,0,0);
	confirmButtonDuplex->set_no_show_all();
	confirmButtonDuplex->signal_clicked().connect(sigc::mem_fun(this,&ConfirmationDialogWidget::on_confirmButtonDuplex_clicked));

	cancelButtonDuplex = manage(new SmartmaticButton());
	cancelButtonDuplex->set_size_request(buttonsWidth, buttonsHeight);
	cancelButtonDuplex->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Cancel"));
	cancelButtonDuplex->WidgetsPosition(5,0,0);
	cancelButtonDuplex->set_no_show_all();
	cancelButtonDuplex->signal_clicked().connect(sigc::mem_fun(this,&ConfirmationDialogWidget::on_cancelButtonDuplex_clicked));


	confirmButton->SetSound(SoundConfirmationDialog);
	cancelButton->SetSound(SoundConfirmationDialog);
	confirmButtonDuplex->SetSound(SoundConfirmationDialog);
	cancelButtonDuplex->SetSound(SoundConfirmationDialog);
	
	if(buttonVerticals)
	{
		buttonBoxAlignment->set_padding(0, 25, 100, 100); //TODO configuration
		if(switchButtons)
		{
			vButtonsBox->pack_start(*confirmButton, false, false);
			vButtonsBox->pack_start(*cancelButton, false, false);
		}
		else
		{
			vButtonsBox->pack_start(*cancelButton, false, false);
			vButtonsBox->pack_start(*confirmButton, false, false);
		}
		hButtonsBox->set_no_show_all();
	}
	else
	{
		if(switchButtons)
		{
			hButtonsBox->pack_start(*confirmButton);
			hButtonsBox->pack_start(*cancelButton);
		}
		else
		{
			hButtonsBox->pack_start(*cancelButton);
			hButtonsBox->pack_start(*confirmButton);
		}
		vButtonsBox->set_no_show_all();
	}

	if (switchButtons)
	{
		hButtonsBox->pack_start(*confirmButtonDuplex);
		hButtonsBox->pack_start(*cancelButtonDuplex);
	}
	else
	{
		hButtonsBox->pack_start(*cancelButtonDuplex);
		hButtonsBox->pack_start(*confirmButtonDuplex);
	}

	externalButtonsBox->add(*hButtonsBox);
	externalButtonsBox->add(*vButtonsBox);
	
	buttonBoxAlignment->add(*externalButtonsBox);
	pack_start(*confirmationLabel);
	pack_start(*buttonBoxAlignment, false, false);
	show_all_children();
}

void ConfirmationDialogWidget::SetBaseButtonsName(const Glib::ustring& baseName)
{
  confirmButton->SetCustomName(baseName);
  cancelButton->SetCustomName(baseName);
  confirmButtonDuplex->SetCustomName(baseName);
  cancelButtonDuplex->SetCustomName(baseName);
}
ConfirmationDialogWidget::~ConfirmationDialogWidget()
{

}

void ConfirmationDialogWidget::SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration& labelCenterConfigurationA)
{
	this->labelConfiguration = labelCenterConfigurationA;
	ConfigureLabel();
}

void ConfirmationDialogWidget::SetLabelConfigurationReconfirmation(LabelConfiguration& labelConfigurationReconfirmation)
{
	this->labelConfigurationReconfirmation = labelConfigurationReconfirmation;
}

void ConfirmationDialogWidget::ConfigureLabel()
{
	LabelConfiguration::SetLabelConfiguration(confirmationLabel,labelConfiguration);
}

void ConfirmationDialogWidget::ConfigureReconfirmationLabel()
{
	LabelConfiguration::SetLabelConfiguration(confirmationLabel,labelConfigurationReconfirmation);
}

void ConfirmationDialogWidget::SetReconfirmation(string acceptSelectionText, string cancelSelectionText,
												 string headerTitleConfirmation, string footerTitleConfirmation,
                                                 string confirmButtonText, string cancelButtonText)
{
	secondConfirm = true;
	this->acceptSelectionText = acceptSelectionText;
	this->cancelSelectionText = cancelSelectionText;
	this->headerTitleConfirmation = headerTitleConfirmation;
	this->footerTitleConfirmation = footerTitleConfirmation;
	
	if(confirmButtonText.empty()) confirmButtonDuplex->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Accept"));
	else confirmButtonDuplex->SetLabel(_(confirmButtonText.c_str()));
	
	if(cancelButtonText.empty()) cancelButtonDuplex->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Cancel"));
	else cancelButtonDuplex->SetLabel(_(cancelButtonText.c_str()));
}

void ConfirmationDialogWidget::SetConfirmationText(Glib::ustring confirmText)
{
	confirmationLabel->set_text(confirmText);
}

ConfirmationDialogWidget::type_void_signal ConfirmationDialogWidget::confirm_clicked()
{
	return m_confirm_clicked;
}

ConfirmationDialogWidget::type_void_signal ConfirmationDialogWidget::cancel_clicked()
{
	return m_cancel_clicked;
}

ConfirmationDialogWidget::type_void_signal ConfirmationDialogWidget::first_confirm_clicked()
{
	return m_first_confirm_clicked;
}

void ConfirmationDialogWidget::on_confirmButton_clicked()
{
	if(secondConfirm)
	{
		ConfigureReconfirmationLabel();

		if(buttonVerticals)
		{
			vButtonsBox->hide();
			hButtonsBox->show();
			buttonBoxAlignment->set_padding(0, 25, 50, 50); //TODO configuration
		}
		
		selectOk = true;	
		headerTitle = headerTitleConfirmation;
		footerTitle = footerTitleConfirmation;
		confirmationLabel->set_text(acceptSelectionText);
		confirmButton->hide();
		cancelButton->hide();
		confirmButtonDuplex->show();
		cancelButtonDuplex->show();
		m_first_confirm_clicked.emit();			
	}
	else
		m_confirm_clicked.emit();
}

void ConfirmationDialogWidget::on_cancelButton_clicked()
{
	if(secondConfirm)
	{
		selectOk = false;

		if(skipFalse)
			m_cancel_clicked.emit();
		else
		{
			if(buttonVerticals)
			{
				vButtonsBox->hide();
				hButtonsBox->show();
				buttonBoxAlignment->set_padding(0, 25, 50, 50); //TODO configuration
			}
			
			ConfigureReconfirmationLabel();
			confirmationLabel->set_text(cancelSelectionText);
			confirmButton->hide();
			cancelButton->hide();
			confirmButtonDuplex->show();
			cancelButtonDuplex->show();
		}
	}
	else
		m_cancel_clicked.emit();
}

void ConfirmationDialogWidget::on_confirmButtonDuplex_clicked()
{
	if(selectOk)
		m_confirm_clicked.emit();
	else
		m_cancel_clicked.emit();
}

void ConfirmationDialogWidget::on_cancelButtonDuplex_clicked()
{
	if(buttonVerticals)
	{
		vButtonsBox->show();
		hButtonsBox->hide();
		buttonBoxAlignment->set_padding(0, 25, 100, 100); //TODO configuration
	}
	
	ConfigureLabel();
	confirmationLabel->set_text(confirmationText);
	confirmButton->show();
	cancelButton->show();
	confirmButtonDuplex->hide();
	cancelButtonDuplex->hide();
}

void ConfirmationDialogWidget::Refresh(std::string confirmButtonText, std::string cancelButtonText)
{
	if(confirmButtonText.empty()) confirmButton->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Accept"));
	else confirmButton->SetLabel(_(confirmButtonText.c_str()));

	if(cancelButtonText.empty()) cancelButton->SetLabel(_("Smartmatic.GUI.Widgets.ConfirmationDialogWidget.Cancel"));
	else cancelButton->SetLabel(_(cancelButtonText.c_str()));
	
}

std::string ConfirmationDialogWidget::GetHeaderConfirmationTitle()
{
	return headerTitleConfirmation;	
}

std::string ConfirmationDialogWidget::GetFooterConfirmationTitle()
{
	return footerTitleConfirmation;	
}
