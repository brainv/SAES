/**
 * ListResultWidget.cxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#include "ListResultWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <System/Runtime/ProcessLauncher.h>

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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::System::Runtime;

ISMTTLog* ListResultWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ListResultWidget",GETTEXT_PACKAGE);

ListResultWidget::ListResultWidget(int columns, int width, int height)
: StepWidget()
{
	this->columns = columns;
	this->width = width;
	this->height = height;
	this->scrollFrame = NULL;
	this->centerFrame = NULL;
	this->tableWidget = NULL;
	this->resultWidget = NULL;
	this->center = NULL;
	this->i = 0;
	this->j = 0;

	this->initialize();
	initInfo();
	setTitle(false);
	setWidget(scrollFrame);
}

ListResultWidget::~ListResultWidget()
{
	dispose();
}

void ListResultWidget::initialize()
{
	scrollFrame = new Gtk::ScrolledWindow();
	scrollFrame->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	scrollFrame->set_shadow_type(Gtk::SHADOW_NONE);

	centerFrame = new Gtk::EventBox();
	scrollFrame->add(*centerFrame);

	tableWidget = new TableCenterWidget(false, true);
	tableWidget->setSpacings(0, 10);

	center = new Gtk::Label();
	Pango::FontDescription fontLabel = center->get_style()->get_font();
	fontLabel.set_size(16 * Pango::SCALE);
	center->modify_font(fontLabel);
	center->set_padding(0, 10);

	resultWidget = new TableCenterWidget(false, true);
	resultWidget->setSpacings(0, 0);

	button = new SmartmaticButton();
	button->SetLabel("<--");
	button->set_size_request(140, 60);
	button->signal_clicked().connect(sigc::mem_fun(*this, &ListResultWidget::initInfo));
	button->set_border_width(10);
}

void ListResultWidget::addWidget(Smartmatic::SAES::GUI::Widgets::ResultWidget * widget)
{
	widget->getSignalClick().connect(sigc::mem_fun(*this, &ListResultWidget::viewInfo));
	resultWidgets.push_back(widget);
	putWidget(widget);
}

void ListResultWidget::putWidget(Smartmatic::SAES::GUI::Widgets::ResultWidget * widget)
{
	if (j == columns)
	{
		j = 0;
		i++;
	}

	j++;

	tableWidget->put(widget, i, j);
}

void ListResultWidget::dispose()
{
	this->remove();

	if (scrollFrame)
	{
		delete scrollFrame;
		scrollFrame = NULL;
	}
	if (centerFrame)
	{
		delete centerFrame;
		centerFrame = NULL;
	}
	if (tableWidget)
	{
		delete tableWidget;
		tableWidget = NULL;
	}
	if (resultWidget)
	{
		delete resultWidget;
		resultWidget = NULL;
	}
	if (button)
	{
		delete button;
		button = NULL;
	}

	std::vector < ResultWidget * >::iterator it;

	for (it = resultWidgets.begin();
		 it != resultWidgets.end();
		 it++)
	{
		ResultWidget * widget = (*it);
		delete widget;
		widget = NULL;
	}

	clearList();
}

int ListResultWidget::getCountWidget()
{
	return resultWidgets.size();
}

void ListResultWidget::viewInfo( ResultWidget * result )
{
	clearList();

	std::list <ResultWidget::Result> & list (result->getResult());
	std::list <ResultWidget::Result>::iterator it;

	if (list.size() > 0)
	{
		int row = 0;

		center->set_text(result->getText());
		resultWidget->put(center, row++, 0);

		for (it = list.begin();
				it != list.end();
				it++)
		{
			ResultWidget * widget = new ResultWidget();
			widget->setText((*it).message, false);
			widget->setStatus((*it).status);
			widget->set_size_request(width, height);
			resultWidget->put(widget, row++, 0);
		}

		resultWidget->put(button, row++, 0, Gtk::SHRINK, Gtk::SHRINK);

		centerFrame->remove();
		centerFrame->add(*resultWidget);

		show_all_children();
	}
}

void ListResultWidget::initInfo()
{
	centerFrame->remove();
	centerFrame->add(*tableWidget);
	clearList();
}

void ListResultWidget::clearList()
{
	resultWidget->clear();

	std::list < ResultWidget * >::iterator itl;

	for (itl = resultList.begin();
		 itl != resultList.end();
		 itl++)
	{
		ResultWidget * widget = (*itl);
		delete widget;
		widget = NULL;
	}
}
