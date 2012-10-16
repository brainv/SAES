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

#include "banner-widget.h"

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


using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;

BannerWidget::BannerWidget(ExitButtonListener *exitListener, bool exitButton,
						   HelpButtonListener* helpListener, bool helpButton)
{

	formwidth =  ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getWidth());

	helpExitButtons = NULL;

	image_banner = new Gtk::Image();
	Glib::RefPtr<Gdk::Pixbuf> picToTFT;

	if(formwidth <= 770)
	{
		if(exitButton && helpButton)
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_614_85.png"), 580, 85, false);
		else if(exitButton || helpButton)
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_687_85.png"), 670, 85, false);
		else
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_760_85.png"), 760, 85, false);
	}
	else
	{
		if(exitButton && helpButton)
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_878_85.png"), 862, 85, false);
		else if(exitButton || helpButton)
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_951_85.png"), /*935*/924, 85, false);
		else
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_1024_85.png"), 1024, 85, false);
	}


	image_banner->set(picToTFT);

	add(*image_banner);

	helpExitButtons = new HelpExitButtons(exitListener, exitButton, helpListener, helpButton);
	add(*helpExitButtons);
}

BannerWidget::~BannerWidget()
{
	delete image_banner;

	delete helpExitButtons;
};

void BannerWidget::exitButtonSetSensitive(bool sensitive)
{
	helpExitButtons->ExitButton_SetSensitive(sensitive);
}

void BannerWidget::exitButtonSetVisible(bool visible)
{
	helpExitButtons->ExitButton_SetVisible(visible);
}

void BannerWidget::exitButtonSetName(std::string name)
{
	helpExitButtons->ExitButton_SetName(name);
}

void BannerWidget::helpButtonSetSensitive(bool sensitive)
{
	helpExitButtons->HelpButton_SetSensitive(sensitive);
}

void BannerWidget::helpButtonSetVisible(bool visible)
{
	if(!visible)
	{
		Glib::RefPtr<Gdk::Pixbuf> picToTFT;

		if(formwidth <= 770)
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_687_85.png"), 670, 85, false);
		else
			picToTFT = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/banner_951_85.png"), 935, 85, false);

		image_banner->set(picToTFT);
		image_banner->show();
	}
	helpExitButtons->HelpButton_SetVisible(visible);
}

void BannerWidget::helpButtonSetName(std::string name)
{
	helpExitButtons->HelpButton_SetName(name);
}
