/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
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

#include "choose-dialog-widget.h"
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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;

ChooseDialogWidget::ChooseDialogWidget(MessageWidget* messageWidget)
{
	currentIndex = -1;
	//SET SOUNDS
	SoundChooseDialog=SMTTGUIConfigurationManager::Current()->getChooseDialogSound();
	buttonCancel.SetSound(SoundChooseDialog);
	backButton.SetSound(SoundChooseDialog);
	this->messageWidget = messageWidget;
	this->chooseDialogInfo = NULL;
	this->confirmationWidget = NULL;

	messageWidget->close_clicked().connect(sigc::mem_fun(this,&ChooseDialogWidget::send_on_close_signal));

    frameClientArea.remove();
	frameClientArea.add(*messageWidget);
	show_all_children();
	SetLabelsProperties();
}

ChooseDialogWidget::ChooseDialogWidget(ConfirmationDialogWidget* confirmationWidget)
{
	currentIndex = -1;
  buttonCancel.SetSound(SoundChooseDialog);
  backButton.SetSound(SoundChooseDialog);
  this->messageWidget = NULL;
  this->chooseDialogInfo = NULL;
  this->confirmationWidget = confirmationWidget;

  this->confirmationWidget->confirm_clicked().connect( sigc::mem_fun(*this,&ChooseDialogWidget::send_on_accept_signal));
  this->confirmationWidget->cancel_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::send_on_cancel_signal));
  this->confirmationWidget->first_confirm_clicked().connect( sigc::mem_fun(*this,&ChooseDialogWidget::send_on_first_confirm_signal));

  labelTitle.set_label(confirmationWidget->GetHeaderTitle());
  frameHeader.add(labelTitle);

  labelFooter.set_label(confirmationWidget->GetFooterTitle());
  frameFooter.add(labelFooter);

  SetLabelsProperties();

  frameClientArea.remove();
  frameClientArea.add(*confirmationWidget);
  show_all_children();
  SetLabelsProperties();
}

ChooseDialogWidget::ChooseDialogWidget(ChooseDialogInfo* dialogInfo, ConfirmationDialogWidget* confirmationWidget)
:buttonOptionsBox(Gtk::BUTTONBOX_CENTER,10)
{
	currentIndex = -1;

  	buttonCancel.SetSound(SoundChooseDialog);
	backButton.SetSound(SoundChooseDialog);
  this->messageWidget = NULL;
  this->chooseDialogInfo = dialogInfo;
  this->confirmationWidget = confirmationWidget;

  labelTitle.set_label(chooseDialogInfo->getTitle());
  frameHeader.add(labelTitle);

  labelFooter.set_label(chooseDialogInfo->getFooter());
  frameFooter.add(labelFooter);

  for(unsigned int i=0;i < (chooseDialogInfo->getListOfChoices()).size(); i++)
    {
      SmartmaticButton* buttonList;
	  buttonList = manage(new SmartmaticButton ());
	  buttonList->SetImage((chooseDialogInfo->getListOfChoices())[i]->getImagePath());
      buttonList->SetLabel((chooseDialogInfo->getListOfChoices())[i]->getName());
      if((chooseDialogInfo->getListOfChoices())[i]->getImagePath().compare("")==0)
        {
          buttonList->WidgetsPosition(5,0,0);
        }
      else
        {
          buttonList->WidgetsPosition(6,5,0);
        }
      buttonList->set_size_request(350, 100);//TODO configuration

      buttonList->signal_clicked().connect(sigc::bind<int>( sigc::mem_fun(*this,&ChooseDialogWidget::onOptionSelected), i));
      buttonOptionsBox.add(*buttonList);
    }

  this->confirmationWidget->confirm_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::send_on_choose_signal));
  this->confirmationWidget->cancel_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::send_on_cancel_intermediate_signal));
  this->confirmationWidget->first_confirm_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::send_on_first_confirm_signal));

  frameClientArea.remove();
  frameClientArea.add(buttonOptionsBox);
  show_all_children();
  SetLabelsProperties();
}

ChooseDialogWidget::~ChooseDialogWidget()
{
  if(messageWidget) delete(messageWidget);
}

ChooseDialogWidget::type_void_signal ChooseDialogWidget::on_accept_signal()
{
  return m_type_accept;
}

ChooseDialogWidget::type_void_signal ChooseDialogWidget::on_cancel_signal()
{
  return m_type_cancel;
}

ChooseDialogWidget::type_void_signal ChooseDialogWidget::on_cancel_intermediate_signal()
{
  return m_type_cancel_intermediate;
}

ChooseDialogWidget::type_void_signal ChooseDialogWidget::on_close_signal()
{
  	return m_type_close;
}

ChooseDialogWidget::type_chooseDialog_signal ChooseDialogWidget::on_accept_intermediate_signal()
{
  return m_type_accept_intermediate;
}

ChooseDialogWidget::type_chooseDialog_signal ChooseDialogWidget::on_choose_signal()
{
  return m_type_choose;
}

void ChooseDialogWidget::send_on_accept_signal()
{
	m_type_accept.emit();
}

void ChooseDialogWidget::send_on_cancel_signal()
{
	m_type_cancel.emit();
}

void ChooseDialogWidget::send_on_cancel_intermediate_signal()
{
  m_type_cancel_intermediate.emit();

  labelTitle.set_label(chooseDialogInfo->getTitle());
  labelFooter.set_label(chooseDialogInfo->getFooter());

  SetLabelsProperties();
  frameClientArea.remove();
  frameClientArea.add(buttonOptionsBox);
  frameClientArea.show_all_children ();
}

void ChooseDialogWidget::send_on_first_confirm_signal()
{
  labelTitle.set_label(confirmationWidget->GetHeaderConfirmationTitle());
  labelFooter.set_label(confirmationWidget->GetFooterConfirmationTitle());
}

void ChooseDialogWidget::send_on_choose_signal()
{
	if (currentIndex >= 0)
	{
		m_type_choose.emit(chooseDialogInfo->getListOfChoices()[currentIndex]);
	}
}

void ChooseDialogWidget::send_on_close_signal()
{
  m_type_close.emit();
}

void ChooseDialogWidget::onOptionSelected(int index)
{
  currentIndex = index;

  if(chooseDialogInfo)
    m_type_accept_intermediate.emit(chooseDialogInfo->getListOfChoices()[index]);
  else
    m_type_accept_intermediate.emit(NULL);

  currentIndex = index;


  Glib::ustring format;

  if(_format.size() > 0 )
    format = _format;
  else
    format = _("Smartmatic.GUI.Widgets.ChooseDialogWidget.ConfirmationTextFormat");


  Glib::ustring text = Glib::ustring::compose(format,(chooseDialogInfo->getListOfChoices()[index])->getName() );


  confirmationWidget->SetConfirmationText(text);

  labelTitle.set_label(confirmationWidget->GetHeaderTitle());
  labelFooter.set_label(confirmationWidget->GetFooterTitle());
  SetConfirmationLabelProperties();
  frameClientArea.remove();
  frameClientArea.add(*confirmationWidget);
  frameClientArea.show_all_children ();
}

string ChooseDialogWidget::onOptionSelectedSim(int index)
{
	onOptionSelected(index);

	string returnValue = chooseDialogInfo->getListOfChoices()[index]->getCode();
	return returnValue;
}

void ChooseDialogWidget::SetBaseButtonsName(const Glib::ustring& baseName)
{
  buttonCancel.SetCustomName(baseName);
  backButton.SetCustomName(baseName);
  //Set the name of the options
  std::vector<Widget*> buttons = buttonOptionsBox.get_children();
  if(buttons.size() > 0)
  {
      for(unsigned int i = 0; i< buttons.size(); i++)
      {
          Widget* child = buttons[i];
          SmartmaticButton* childBtn = static_cast<SmartmaticButton*>(child);
		  childBtn->SetCustomName(baseName);
      }
  }
}
void ChooseDialogWidget::SetConfirmationStringFormat(Glib::ustring& format)
{
  _format = format;
}

void ChooseDialogWidget::SetLabelsProperties()
{
	SetLabelConfiguration(labelTitle, labelTitleConfiguration);
	SetLabelConfiguration(labelFooter, labelFooterConfiguration);
}

void ChooseDialogWidget::SetConfirmationLabelProperties()
{
	SetLabelConfiguration(labelTitle, labelTitleConfigurationConfirmation);
	SetLabelConfiguration(labelFooter, labelFooterConfigurationConfirmation);
}

void ChooseDialogWidget::Refresh(string headerLabel, string footerLabel)
{
	labelTitle.set_label(headerLabel);
	labelFooter.set_label(footerLabel);

	if (chooseDialogInfo && chooseDialogInfo->getListOfChoices().size() > 0)
	{
		std::vector<ChooseDialogButtonInfo *> & list (chooseDialogInfo->getListOfChoices());

		Glib::ustring format;

		if(_format.size() > 0 )
		{
			format = _format;
		}
		else
		{
			format = _("Smartmatic.GUI.Widgets.ChooseDialogWidget.ConfirmationTextFormat");
		}

		if (currentIndex >= 0)
		{
			Glib::ustring text = Glib::ustring::compose(format,list[currentIndex]->getName() );
			confirmationWidget->SetConfirmationText(text);
		}
	}
}	

ChooseDialogWidget::ChooseDialogWidget(ChooseDialogInfo * dialogInfo, bool showBack):
				    buttonOptionsBox(Gtk::BUTTONBOX_CENTER,10)
{
	currentIndex = -1;

  this->messageWidget = NULL;
  this->chooseDialogInfo = dialogInfo;
  this->confirmationWidget = NULL;

  this->showBack = showBack;

  //frameHeader = new Frame();
  //hboxHeader = new HBox();
  //labelTitle = new Label(dialogInformation->getTitle());
  labelTitle.set_label(chooseDialogInfo->getTitle());

	//set label configuration
	SetLabelConfiguration(labelTitle, labelTitleConfiguration);

	//imageTitle = new Image(dialogInformation->getTitleImagePath());
  imageTitle.set(chooseDialogInfo->getTitleImagePath());
  imageTitle.set_size_request(80, 50);
  if(chooseDialogInfo->getTitleImagePath().compare("")!=0)
    {
      hboxHeader.add(imageTitle);
    }
  hboxHeader.add(labelTitle);

  if(chooseDialogInfo->activateCancelButton())
    {
      //buttonCancel = new SmartmaticButton();
      buttonCancel.set_label (_("Smartmatic.GUI.Widgets.ChooseDialogWidget.Cancel"));
      buttonCancel.signal_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::onCancelButton));
      buttonCancel.set_size_request(80 , 50);
      hboxHeader.add(buttonCancel);
    }


  frameHeader.add(hboxHeader);
  //frameHeader.set_border_width(10);

  labelFooter.set_label(chooseDialogInfo->getFooter());

	//set label configuration
  SetLabelConfiguration(labelFooter, labelFooterConfiguration);
  hboxFooter.pack_start(labelFooter);

  backButton.set_label (_("Smartmatic.GUI.Widgets.ChooseDialogWidget.Cancel"));
  backButton.signal_clicked().connect(sigc::mem_fun(*this,&ChooseDialogWidget::on_backButton_clicked));
  backButton.set_size_request(300, 100);//TODO configuration
  hboxFooter.pack_start(backButton, true, false);

  frameFooter.add(hboxFooter);

  if(!showBack)
    {
      backButton.set_no_show_all();
      backButton.hide();
    }
  else
    {
      labelFooter.set_no_show_all();
      labelFooter.hide();
    }

  //frameOptions = new Frame();
  //buttonOptionsBox = new VButtonBox(BUTTONBOX_CENTER,10);

  for(unsigned int i=0;i < (chooseDialogInfo->getListOfChoices()).size(); i++)
    {
      SmartmaticButton* buttonList;
      buttonList = manage(new SmartmaticButton ());
      buttonList->SetImage((chooseDialogInfo->getListOfChoices())[i]->getImagePath());
      buttonList->SetLabel((chooseDialogInfo->getListOfChoices())[i]->getName());
      if((chooseDialogInfo->getListOfChoices())[i]->getImagePath().compare("")==0)
        {
          buttonList->WidgetsPosition(5,0,0);
        }
      else
        {
          buttonList->WidgetsPosition(6,5,0);
        }
      buttonList->set_size_request(350, 100);//TODO configuration

      buttonList->signal_clicked().connect(sigc::bind<int>( sigc::mem_fun(*this,&ChooseDialogWidget::onOptionButton), i));
      //		buttonOptionsBox.add(*buttonList);
      buttonOptionsBox.pack_start(*buttonList, false, false);
      //delete(buttonList);
    }

  frameClientArea.remove();
  frameClientArea.add(buttonOptionsBox);
}

void ChooseDialogWidget::on_backButton_clicked()
{
	signal_back_clicked.emit();
}

void ChooseDialogWidget::onOptionButton(int index)
{

  if(!m_type_choose.empty())
  {
      currentIndex = index;
      //m_type_choose.
      m_type_choose.emit(chooseDialogInfo->getListOfChoices()[index]);
  }
  signal_detected.emit(chooseDialogInfo->getListOfChoices()[index]);
}

void ChooseDialogWidget::onCancelButton()
{
  signal_detected.emit(NULL);
}

void ChooseDialogWidget::SetLabelConfiguration(LabelConfiguration labelTitleConfiguration, 
                                               LabelConfiguration labelFooterConfiguration)
{
	this->labelTitleConfiguration = labelTitleConfiguration;
	this->labelFooterConfiguration = labelFooterConfiguration;	
	SetLabelsProperties();
};

void ChooseDialogWidget::SetLabelConfirmationConfiguration(LabelConfiguration labelTitleConfiguration, LabelConfiguration labelFooterConfiguration)
{
	this->labelTitleConfigurationConfirmation = labelTitleConfiguration;
	this->labelFooterConfigurationConfirmation = labelFooterConfiguration;	
}

void ChooseDialogWidget::SetLabelConfiguration(Gtk::Label & label, Smartmatic::GUI::Configuration::LabelConfiguration configuration)
{	
	label.set_padding(configuration.GetVerticalPadding(), configuration.GetHorizontalPadding());
	Pango::FontDescription fontTitle = label.get_style()->get_font();
	fontTitle.set_size(configuration.GetSize()*Pango::SCALE);

	switch(configuration.GetStyle())
	{
		case Smartmatic::GUI::Configuration::NormalStyle:
		{
			fontTitle.set_style(Pango::STYLE_NORMAL);			
		}
		break;
		case Smartmatic::GUI::Configuration::ObliqueStyle:
		{
			fontTitle.set_style(Pango::STYLE_OBLIQUE);		
		}
		break;
		case Smartmatic::GUI::Configuration::ItalicStyle:
		{
			fontTitle.set_style(Pango::STYLE_ITALIC);		
		}
		break;
	}

	switch(configuration.GetWeight())
	{
		case Smartmatic::GUI::Configuration::LightWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_LIGHT);			
		}
		break;
		case Smartmatic::GUI::Configuration::NormalWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_NORMAL);		
		}
		break;
		case Smartmatic::GUI::Configuration::BoldWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_BOLD);		
		}
		break;
	}

	fontTitle.set_family(configuration.GetFontFamily());

	switch(configuration.GetLabelAlignment())
	{
		case Smartmatic::GUI::Configuration::LeftAlignment:
		{
			label.set_alignment(0, 0.5);			
		}
		break;
		case Smartmatic::GUI::Configuration::CenterAlignment:
		{
			label.set_alignment(0.5, 0.5);		
		}
		break;
		case Smartmatic::GUI::Configuration::RigthAlignment:
		{
			label.set_alignment(1, 0.5);		
		}
		break;
	}
	
	label.modify_font(fontTitle);
};

void ChooseDialogWidget::refresh()
{
	if (chooseDialogInfo)
	{
		labelTitle.set_text(chooseDialogInfo->getTitle());
		labelFooter.set_text(chooseDialogInfo->getFooter());
	}
}
