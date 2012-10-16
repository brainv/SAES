/**
 * @file RegisterWidget.cxx
 * @brief Body class register generic widget
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#include "RegisterWidget.hxx"
#include "TableCenterWidget.hxx"

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

RegisterWidget::RegisterWidget(bool showTabs, Gtk::Widget * bottomWidget)
: StepWidget()
{
	notebookContainer = NULL;
	hboxBtn = NULL;
	align = NULL;

	setConfig();

	notebookContainer = new NotebookContainer();
	notebookContainer->ShowTabs(showTabs);

	if (bottomWidget)
	{
		hboxBtn = new Gtk::HButtonBox();
		hboxBtn->pack_start(*bottomWidget,false,false);
		hboxBtn->set_layout(Gtk::BUTTONBOX_CENTER);
		notebookContainer->AddBottomWidget(hboxBtn);
	}

	setWidget(notebookContainer);
}

RegisterWidget::~RegisterWidget()
{
	dispose();
}

void RegisterWidget::setConfig(int maxRow, int maxCol, int rowSpacing, int colSpacing, int width, int height, bool vertical, int border)
{
	this->maxRow = maxRow;
	this->maxCol = maxCol;
	this->rowSpacing = rowSpacing;
	this->colSpacing = colSpacing;
	this->border = border;
	this->width = width;
	this->height = height;
	this->vertical = vertical;
}

void RegisterWidget::dispose()
{
	remove();

	if (notebookContainer)
	{
		delete notebookContainer;
		notebookContainer = NULL;
	}
	if (hboxBtn)
	{
		delete hboxBtn;
		hboxBtn = NULL;
	}
	if (align)
	{
		delete align;
		align = NULL;
	}

	std::vector <Gtk::Widget *>::iterator itv;

	for (itv = vectorWidget.begin();
			itv != vectorWidget.end();
			itv++)
	{
		Gtk::Widget * widget = (*itv);
		delete widget;
		widget = NULL;
	}
}

void RegisterWidget::addWidget(Gtk::Widget * widget, std::string title)
{
	widget->set_size_request(width, height);
	setCurrentPage(vectorWidget.size()-1);

	Gtk::Widget * container = notebookContainer->getCurrentPageWidget();
	TableCenterWidget * table = NULL;

	if (!container)
	{
		table = new TableCenterWidget(false, true);
		vectorWidget.push_back(table);
		notebookContainer->AppendPage(table, title);
	}
	else
	{
		table = (TableCenterWidget *)container;
	}

	int count = table->getCountElements();
	int row;
	int col;

	if (maxRow * maxCol == count)
	{
		table = new TableCenterWidget(false, true);
		vectorWidget.push_back(table);
		notebookContainer->AppendPage(table, title);
		count = table->getCountElements();
	}

	if (vertical)
	{
		row = count % maxRow;
		col = count / maxRow;
	}
	else
	{
		col = count % maxCol;
		row = count / maxCol;
	}

	table->setSpacings(rowSpacing, colSpacing);
	notebookContainer->SetCurrentPage(notebookContainer->getTotalPages() - 1);
	table->put(widget, row, col);
}

void RegisterWidget::setCurrentPage(int currentPage)
{
	notebookContainer->SetCurrentPage(currentPage);
}

sigc::signal<void> RegisterWidget::getSignalAllPagesViewed()
{
	return notebookContainer->signal_all_pages_viewed();
}
