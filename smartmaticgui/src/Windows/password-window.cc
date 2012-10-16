/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * BasicWindow
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * BasicWindow is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BasicWindow is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Windows/password-window.h"
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"

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
using namespace std;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Functionality;

int PasswordWindow::div = 4;
int PasswordWindow::maxChar = 4;
int PasswordWindow::width = 55;

PasswordWindow::PasswordWindow(bool isRole, const FunctionalityChallengeConfiguration& config, std::string okButtonLabel,
				               PasswordTypeEnum type)
:BasicWindow(false, true)
{
	this->isRole = isRole;
	label = NULL;
	align = NULL;
	passIsOk = false;
	//this->passToCheck = config.getPassword();
	this->config = config;
	this->messagetitle = messagetitle;
	this->messageOk = this->config.getMessageOK();
	this->messageWrong = this->config.getMessageError();


	titleConf = GetLabelTitleConfiguration();
	okAndWrongConf = GetLabelOkAndWrongConfiguration();
	titleFrameConf = GetLabelTitleFrameConfiguration();
	
	entryPass = manage(new Gtk::Entry());
	entryPass->set_size_request(250, -1);

	Alignment* alignEntry = manage(new Alignment());
	alignEntry->set(0.5,0.5,0,0);
	alignEntry->add(*entryPass);

	string fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/password-window.gif");
	
	if(!File::canOpenFile(fileImage))
		fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");

	Gtk::Image* loadImage = manage(new Gtk::Image());
	loadImage->set(Gdk::PixbufAnimation::create_from_file(fileImage));

	if(okButtonLabel == "")
	{
		okButtonLabel = _("Smartmatic.GUI.Windows.PasswordWindow.OkButton");
	}
	
	okButton = manage(new SmartmaticButton(okButtonLabel));
	okButton->signal_clicked().connect(sigc::mem_fun(*this, &PasswordWindow::on_okButton_clicked));
	okButton->set_size_request(200, 60);

	HButtonBox* buttonBox = manage(new HButtonBox());
	buttonBox->set_layout(BUTTONBOX_CENTER);
	buttonBox->pack_start(*okButton, false, false);

	passlabel = manage(new Label(this->config.getDescriptionMessage()));
	LabelConfiguration::SetLabelConfiguration(passlabel, titleConf);

	password = manage(new Smartmatic::GUI::Widgets::SmartmaticEntryDivided(div, maxChar, width));

	Gtk::Alignment* alignPass = manage(new Alignment());
	alignPass->add(*password);
	alignPass->set(0.5,0.5,0,0);


	VBox* vbox = manage(new VBox(false, 20));
	vbox->pack_start(*passlabel);
	vbox->pack_start(*loadImage);
	vbox->pack_start(*alignEntry, false, false);
	vbox->pack_start(*alignPass, false, false);
	vbox->pack_start(*buttonBox, false, false);
	
	if(isRole)
	{
		alignPass->set_no_show_all();
		alignPass->hide();
	}
	else
	{
		alignEntry->set_no_show_all();
		alignEntry->hide();
	}

	align = new Alignment();
	align->set(0.5,0.5,0,0);
	align->add(*vbox);

	setWidget(align);

	titleLabel = manage(new Label(this->config.getTitle()));
	LabelConfiguration::SetLabelConfiguration(titleLabel, titleFrameConf);
	setTitle(titleLabel);
}

void PasswordWindow::SetDividedEntryParams(int _div, int _maxChar, int _width)
{
	PasswordWindow::div = _div;
	PasswordWindow::maxChar = _maxChar;
	PasswordWindow::width = _width;
}

PasswordWindow::~PasswordWindow()
{
	if(align) delete align;
	if(label) delete label;
}

void PasswordWindow::on_okButton_clicked()
{
	passIsOk = false;
	
	if(config.getAuthenticationProvider())
	{
		string pass = "";

		if(isRole)
			pass = entryPass->get_text();
		else
			pass = password->GetText();

		if(config.getAuthenticationProvider()->Authenticate(pass))
			passIsOk = true;
		else
			passIsOk = false;
	}
	else
		passIsOk = false;

	CheckPass();
}

bool PasswordWindow::GetPasswordCorrect()
{
	return passIsOk;
}

void PasswordWindow::CheckPass()
{
	label = new Label();
	LabelConfiguration::SetLabelConfiguration(label, okAndWrongConf);
	
	if(passIsOk)
	{
		label->set_text(messageOk);
	}
	else
	{
		label->set_text(messageWrong);
	}

	setWidget(label);

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PasswordWindow::QuitDialog), 3000);
}

void PasswordWindow::SetLabelsConfiguration(LabelConfiguration titleConf,
                                            LabelConfiguration okAndWrongConf,
                                            LabelConfiguration titleFrameConf)
{
	LabelConfiguration::SetLabelConfiguration(passlabel, titleConf);
	LabelConfiguration::SetLabelConfiguration(label, okAndWrongConf);
	LabelConfiguration::SetLabelConfiguration(titleLabel, titleFrameConf);
}

LabelConfiguration PasswordWindow::GetLabelTitleConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(CenterAlignment);
	configuration.SetVerticalPadding(2);
	configuration.SetHorizontalPadding(2);
	configuration.SetSize(16);
	configuration.SetWeight(BoldWeight);
	return configuration;
};

LabelConfiguration PasswordWindow::GetLabelTitleFrameConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(CenterAlignment);
	configuration.SetVerticalPadding(2);
	configuration.SetHorizontalPadding(2);
	configuration.SetSize(18);
	configuration.SetWeight(BoldWeight);
	return configuration;
};

LabelConfiguration PasswordWindow::GetLabelOkAndWrongConfiguration()
{
	LabelConfiguration configuration;
	configuration.SetLabelAlignment(CenterAlignment);
	configuration.SetVerticalPadding(2);
	configuration.SetHorizontalPadding(2);
	configuration.SetSize(22);
	configuration.SetWeight(BoldWeight);
	return configuration;
};
