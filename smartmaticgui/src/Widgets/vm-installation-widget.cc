/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include "vm-installation-widget.h"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;
using namespace std;

void VMInstallationWidget::Initialize()
{
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/vm_installation.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	builder->get_widget("frameKeyboard", frameKeyboard);
	builder->get_widget("vbox",bottomBox);
	builder->get_widget("labelMensaje", labelMensaje);
	builder->get_widget_derived("password", password);
	builder->get_widget_derived("buttonOk", buttonOk);
	builder->get_widget("hbuttonbox1", labelhbuttonbox1);
	builder->get_widget("hbuttonbox2", textEntryhbuttonbox2);

	Pango::FontDescription font = password->get_style()->get_font();
	font.set_size(30*Pango::SCALE);
	//font.set_weight (Pango::WEIGHT_BOLD);
	password->modify_font(font);
	buttonOk->set_no_show_all();
	buttonOk->hide();

	labelMensaje->set_label(_("Smartmatic.GUI.Widgets.VMInstallationWidget.InsertYourPasswordUsingTheKeyboard"));
	if(!Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getAZERTYShowPass())
	{
		password->set_visibility (false);
		password->set_invisible_char('*');
	}

	switch (type) {
		case OnlyKeyWord:
		{
			Keyboard *keyboard = new Keyboard();
			keyboard->signal_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_key_press));
			keyboard->signalDelete_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_keyDelete_press));
			keyboard->signalEnter_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_keyEnter_press));
			keyboard->set_size_request(100,100);
			frameKeyboard->add(*keyboard);
			buttonOk->show();
		}
		break;
		case OnlyToken:
		{
			Glib::RefPtr<Gdk::PixbufAnimation> pic = Gdk::PixbufAnimation::create_from_file(
					ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/waiting_token_card.gif"));

			waitingTokenImage = new Gtk::Image(pic);

			waitingTokenLabel = manage(new Gtk::Label());
			waitingTokenVBox = manage(new Gtk::VBox());

			waitingTokenLabel->set_label(_("Smartmatic.GUI.Widgets.VMInstallationWidget.WaitingCardTokenLabel"));

			waitingTokenVBox->pack_start(*waitingTokenImage, true, true, 3 );
			waitingTokenVBox->pack_end(*waitingTokenLabel, true, true, 5);

			labelhbuttonbox1->remove(*labelMensaje);
			textEntryhbuttonbox2->remove(*password);

			frameKeyboard->add(*waitingTokenVBox);
		}
		break;
		case keywordAndToken:
		{

			Glib::RefPtr<Gdk::PixbufAnimation> pic = Gdk::PixbufAnimation::create_from_file(
					ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/waiting_token_card.gif"));

			waitingTokenImage = new Gtk::Image(pic);

			waitingTokenLabel = manage(new Gtk::Label());
			waitingTokenVBox = manage(new Gtk::VBox());

			waitingTokenLabel->set_label(_("Smartmatic.GUI.Widgets.VMInstallationWidget.WaitingCardTokenLabel"));

			Keyboard *keyboard = new Keyboard();
			keyboard->signal_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_key_press));
			keyboard->signalDelete_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_keyDelete_press));
			keyboard->signalEnter_detected.connect(sigc::mem_fun(*this,&VMInstallationWidget::on_keyEnter_press));
			//keyboard->set_size_request(100,100);

			waitingTokenVBox->pack_start(*keyboard, false, false, 3);
			waitingTokenVBox->pack_start(*waitingTokenImage, false, false, 3 );
			waitingTokenVBox->pack_end(*waitingTokenLabel, false, false, 5);

			frameKeyboard->add(*waitingTokenVBox);
			buttonOk->show();
		}
		break;
	}

	progressLabel = manage(new Gtk::Label());
	progressLabel->set_label(_("Smartmatic.GUI.Widgets.VMInstallationWidget.DefaultProgressMessage"));

	buttonOk->set_label(_("Smartmatic.GUI.Widgets.VMInstallationWidget.ButtonOk"));
	buttonOk->signal_clicked().connect(sigc::mem_fun(this, &VMInstallationWidget::on_keyEnter_press));
	//frameKeyboard->set_size_request(100,100);
	frameKeyboard->show_all_children();
	frameKeyboard->set_visible(true);
	bottomBox->show_all_children();
	bottomBox->set_visible (true);
	add(*bottomBox);
	show_all_children();
	set_visible(true);
};

void VMInstallationWidget::SetButtonSize(int buttonWidth, int buttonHeight)
{
	buttonOk->set_size_request(buttonWidth, buttonHeight);
	buttonOk->ModifyFontSize(18);
}

void VMInstallationWidget::ClearPassword()
{
	password->set_text("");
}

void VMInstallationWidget::on_key_press(string data)
{
	Glib::ustring key_data (data);

	string pass = password->get_text();

	EntryPassPhraseConfiguration::Value case_conf =
			Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getEntryConfiguration ();

	switch (case_conf)
	{
	case EntryPassPhraseConfiguration::CONFIGURATION_CASESENSITIVE:
		break;
	case EntryPassPhraseConfiguration::CONFIGURATION_UPPERCASE:
		key_data = key_data.uppercase ();
		break;
	case EntryPassPhraseConfiguration::CONFIGURATION_LOWERCASE:
		key_data = key_data.lowercase ();
		break;
	default:
		break;
	}

	pass.append(key_data.raw ());
	password->set_text(pass);
}

void VMInstallationWidget::on_keyDelete_press()
{
	string pass = password->get_text();
	password->set_text(pass.substr(0,pass.size()-1));
}

void VMInstallationWidget::on_keyEnter_press()
{
	std::string data = password->get_text();
	signalEnter_detected.emit(data);
}

void VMInstallationWidget::Dispose()
{

};

void VMInstallationWidget::SetMessageFont(Smartmatic::GUI::Configuration::LabelConfiguration labelMessageConfiguration)
{
	if(labelMensaje)
	{
		Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelMensaje, labelMessageConfiguration);
		Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(progressLabel, labelMessageConfiguration);
		Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(waitingTokenLabel, labelMessageConfiguration);
	}
}

void VMInstallationWidget::setVMInstallationWidgetType(VMInstallationWidgetType typeA)
{
	type = typeA;
}

void VMInstallationWidget::showProgress()
{
	if(this->get_child())
	{
		this->remove();
	}

	this->add(*GetProgressFrame());

	show_all_children();
	set_visible(true);
}

void VMInstallationWidget::ResetWidgets()
{
	if(this->get_child())
	{
		this->remove();
	}

	add(*bottomBox);
	show_all_children();
	set_visible(true);
}

void VMInstallationWidget::setProgressMessage(std::string message)
{
	if(progressLabel)
		progressLabel->set_label(message);

	show_all_children();
}

Gtk::Frame* VMInstallationWidget::GetProgressFrame()
{
	Gtk::Frame* progressFrame = manage(new Gtk::Frame());
	progressFrame->set_shadow_type(Gtk::SHADOW_NONE);
	Gtk::VBox*	progressVBox = manage(new Gtk::VBox());
	Gtk::Image*	progressImage = manage(new Gtk::Image());
	progressVBox->pack_start(*progressImage);

	if(progressLabel->get_parent() != 0)
	{
		progressLabel->reparent(*progressVBox);
	}
	else
	{
		progressVBox->pack_start(*progressLabel);
	}
	progressLabel->show();

	progressFrame->add(*progressVBox);

	try
	{
		string s = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/cargando.gif");
		progressImage->set(Gdk::PixbufAnimation::create_from_file(s));
	}
	catch(...)
	{
		string s = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");
		progressImage->set(Gdk::Pixbuf::create_from_file(s));
	}

	return progressFrame;
}
