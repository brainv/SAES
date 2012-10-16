/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogPagingTreeViewWidget.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <Log/LogLine.h>
#include <glibmm.h>

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
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;

LogPagingTreeViewWidget::LogPagingTreeViewWidget(LogReader * logReader)
{
	set_shadow_type(Gtk::SHADOW_NONE);

	this->logReader = logReader;
	m_VTable = NULL;
	vBoxRight = NULL;
	m_ButtonBoxNav = NULL;
	m_LabelPage = NULL;
	vboxPrinting = NULL;
	imagePrinting = NULL;
	labelPrinting = NULL;
	buttonBack = NULL;
	buttonNext = NULL;
	buttonPrint = NULL;
	eventboxLog = NULL;

	LoadGUI();
}

LogPagingTreeViewWidget::~LogPagingTreeViewWidget()
{
	if (m_VTable)
	{
		delete m_VTable;
		m_VTable = NULL;
	}
	if (eventboxLog)
	{
		delete eventboxLog;
		eventboxLog = NULL;
	}
	if (vBoxRight)
	{
		delete vBoxRight;
		vBoxRight = NULL;
	}
	if (m_ButtonBoxNav)
	{
		delete m_ButtonBoxNav;
		m_ButtonBoxNav = NULL;
	}
	if (m_LabelPage)
	{
		delete m_LabelPage;
		m_LabelPage = NULL;
	}
	if (vboxPrinting)
	{
		delete vboxPrinting;
		vboxPrinting = NULL;
	}
	if (imagePrinting)
	{
		delete imagePrinting;
		imagePrinting = NULL;
	}
	if (labelPrinting)
	{
		delete labelPrinting;
		labelPrinting = NULL;
	}
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if (buttonNext)
	{
		delete buttonNext;
		buttonNext = NULL;
	}
	if (buttonPrint)
	{
		delete buttonPrint;
		buttonPrint = NULL;
	}
}

void LogPagingTreeViewWidget::on_buttonPrint_clicked()
{
	signalPrint_detected.emit();
}

void LogPagingTreeViewWidget::HidePrintingIndicator()
{
	imagePrinting->set_visible(false);
	labelPrinting->set_visible(false);
}

void LogPagingTreeViewWidget::HidePrintLabel ()
{
	labelPrinting->set_visible(false);
}

void LogPagingTreeViewWidget::ShowPrintLabel ()
{
	labelPrinting->set_visible(true);
}

void LogPagingTreeViewWidget::SetPrinterMessage (const Glib::ustring& msg)
{
	labelPrinting->set_label (msg);
	labelPrinting->set_visible(true);
}

void LogPagingTreeViewWidget::LoadGUI ()
{
	Glib::RefPtr<Gtk::Builder> widget_builder =
		Gtk::Builder::create_from_file (ResourcePathProvider::Current()->
			GetResourcePath(PACKAGE_NAME,"ui/PagingTreeViewWidget.glade"));

	widget_builder->get_widget ("m_VTable", m_VTable);
	widget_builder->get_widget ("eventbox1", eventboxLog);
	widget_builder->get_widget ("vbox-right", vBoxRight);
	widget_builder->get_widget ("m_ButtonBoxNav", m_ButtonBoxNav);
	widget_builder->get_widget ("m_LabelPage",m_LabelPage);
	widget_builder->get_widget ("vboxPrinting",vboxPrinting);
	widget_builder->get_widget ("image-print",imagePrinting);
	widget_builder->get_widget ("label-print",labelPrinting);
	widget_builder->get_widget_derived("button-back",buttonBack);
	widget_builder->get_widget_derived("button-next",buttonNext);
	widget_builder->get_widget_derived("button-print",buttonPrint);

	buttonPrint->set_sensitive(true);
	buttonPrint->WidgetsPosition (5,0,0);
	buttonPrint->SetLabel(_("Smartmatic.SAES.GUI.Widgets.PagingTreeViewWidget.Print"));
	buttonPrint->signal_clicked().connect( sigc::mem_fun(this, &LogPagingTreeViewWidget::on_buttonPrint_clicked));
	//buttonPrint->set_size_request (100,50);

	imagePrinting->set_visible(false);

	labelPrinting->set_label(_("Smartmatic.SAES.GUI.Widgets.PagingTreeViewWidget.IsPrinting"));
	labelPrinting->set_visible(false);
	
	this->logTreeViewWidget = new LogTreeViewWidget();
	eventboxLog->add(*logTreeViewWidget);

	LoadPage(1);
	std::stringstream ss;
	ss<<1<<" / "<<this->logReader->getPageCount();
	m_LabelPage->set_text(ss.str());

	buttonBack->set_sensitive(false);
	
	buttonBack->SetNavigationKey(Smartmatic::GUI::Widgets::Key_Pad1);
	buttonBack->signal_clicked().connect( sigc::mem_fun(this, &LogPagingTreeViewWidget::on_buttonBack_clicked));
	//buttonBack->set_size_request (100,50);
	buttonBack->SetButtonType(SmartmaticButton::ArrowLeft);
	buttonBack->WidgetsPosition (0,5,0);
	

	if(this->logReader->getPageCount()>1)
		buttonNext->set_sensitive(true);
	else
		buttonNext->set_sensitive(false);
	
	buttonNext->SetNavigationKey(Smartmatic::GUI::Widgets::Key_Pad2);
	buttonNext->signal_clicked().connect( sigc::mem_fun(this, &LogPagingTreeViewWidget::on_buttonNext_clicked));
	//buttonNext->set_size_request (100,50);
	buttonNext->SetButtonType(SmartmaticButton::ArrowRight);
	buttonNext->WidgetsPosition (0,5,0);

	imagePrinting->set_no_show_all(true);
	labelPrinting->set_no_show_all(true);

	this->add (*m_VTable);
	this->show_all_children (true);
}

void LogPagingTreeViewWidget::LoadPage (unsigned int page)
{
	this->logTreeViewWidget->CleanAllRows();
	this->logPage = this->logReader->getPage(page);

	std::vector<LogLine> lines = this->logPage.getPage();

	for(unsigned int i = 0; i<lines.size(); i++)
	{
		this->logTreeViewWidget->AddRow(lines[i]);
	}
	
	std::stringstream ss;
	ss<<page<<" / "<<this->logReader->getPageCount();
	m_LabelPage->set_text(ss.str());
}

void LogPagingTreeViewWidget::on_buttonBack_clicked()
{
	unsigned int page = this->logPage.getPageNumber();
	unsigned int pageTotal = this->logReader->getPageCount();

	if( page > 1)
	{
		LoadPage(page-1);
	}
	if(page-1 == 1)
		buttonBack->set_sensitive(false);
	else 
		buttonBack->set_sensitive(true);

	if(page-1 == pageTotal)
		buttonNext->set_sensitive(false);
	else 
		buttonNext->set_sensitive(true);
		
		
}

void LogPagingTreeViewWidget::SetPrintButtonSensitive(bool sensitive)
{
	buttonPrint->set_sensitive(sensitive);
}

void LogPagingTreeViewWidget::on_buttonNext_clicked()
{
	unsigned int page = this->logPage.getPageNumber();
	unsigned int pageTotal = this->logReader->getPageCount();
	
	if( page < pageTotal)
	{
		LoadPage(page+1);
	}

	if(page+1 == pageTotal)
		buttonNext->set_sensitive(false);
	else
		buttonNext->set_sensitive(true);
	if(page+1 == 1)
		buttonBack->set_sensitive(false);
	else 
		buttonBack->set_sensitive(true);
}

void LogPagingTreeViewWidget::showInitialImage()
{
	labelPrinting->set_label(_("Smartmatic.SAES.GUI.Widgets.PagingTreeViewWidget.InitialMessage"));
	labelPrinting->set_visible(true);
	imagePrinting->set(Gdk::PixbufAnimation::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/log-initial-image.png")));
	imagePrinting->set_visible(true);
}

void LogPagingTreeViewWidget::showLoadImage()
{
	labelPrinting->set_label(_("Smartmatic.SAES.GUI.Widgets.PagingTreeViewWidget.IsPrinting"));
	labelPrinting->set_visible(true);
	imagePrinting->set(Gdk::PixbufAnimation::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/log-printing.gif")));
	imagePrinting->set_visible(true);
}

void LogPagingTreeViewWidget::showPrintErrorImage()
{
	imagePrinting->set(Gdk::PixbufAnimation::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/log-print-error.png")));
	imagePrinting->set_visible(true);
}

void LogPagingTreeViewWidget::showPrintOkImage()
{
	imagePrinting->set(Gdk::PixbufAnimation::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/log-print-ok.png")));
	imagePrinting->set_visible(true);
}
