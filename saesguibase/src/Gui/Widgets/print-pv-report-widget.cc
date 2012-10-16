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

#include "print-pv-report-widget.h"
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
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
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* PrintPVReportWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PrintPVReportWidget",GETTEXT_PACKAGE);

PrintPVReportWidget::PrintPVReportWidget()
{
	string fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/print-pv-report.gif");
	
	if(!File::canOpenFile(fileImage))
		fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");

	Gtk::Image* loadImage = manage(new Gtk::Image());
	loadImage->set(Gdk::PixbufAnimation::create_from_file(fileImage));

	label = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.PrintPVReportWidget.PrintingPVReportFile")));
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);
	
	Gtk::VBox* vbox = manage(new Gtk::VBox());
	vbox->pack_start(*loadImage);
	vbox->pack_start(*label);
	
	add(*vbox);
}

PrintPVReportWidget::~PrintPVReportWidget()
{

}

void PrintPVReportWidget::initialize()
{
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &PrintPVReportWidget::ThreadStart), false);
	//Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignTransmissionPackageWidget::on_done),5000);
}

void PrintPVReportWidget::dispose()
{

}

void PrintPVReportWidget::ThreadStart()
{
	bool errorHappen = false;
	try
	{
		//TODO call the method to print report
	}
	catch(...)
	{
		//TODO catch exceptions
		errorHappen = true;
	}

	sleep(3);

	if(!errorHappen)
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PrintPVReportWidget::on_done), 500);
	else
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &PrintPVReportWidget::UpdateLabel),
								_("Smartmatic.SAES.GUI.Widgets.PrintPVReportWidget.ErrorMessage")), 500);
}

void PrintPVReportWidget::on_done()
{
	m_done_signal.emit();
}

void PrintPVReportWidget::UpdateLabel(Glib::ustring text)
{
	loadImage->hide();
	label->set_text(text);
}

