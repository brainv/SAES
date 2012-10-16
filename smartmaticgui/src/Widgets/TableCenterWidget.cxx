/**
 * @file TableCenterWidget.cxx
 * @brief Body class table center widget
 * @date 13/03/2012
 * @author Yadickson Soto
 */

#include "TableCenterWidget.hxx"
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;

ISMTTLog* TableCenterWidget::logger = SMTTLogManager::GetLogger("Smartmatic.GUI.Widgets.TableCenterWidget",GETTEXT_PACKAGE);

TableCenterWidget::TableCenterWidget(bool homogeneous, bool verticalCenter)
: Gtk::EventBox()
{
	this->mainEventBox = NULL;
	this->mainHbox = NULL;
	this->mainVbox = NULL;
	this->tableBox = NULL;
	this->table = NULL;

	mainEventBox = new Gtk::EventBox();
	mainHbox = new Gtk::HBox();
	mainHbox->set_homogeneous(true);

	mainVbox = new Gtk::VBox();
	mainVbox->set_homogeneous(false);

	tableBox = new Gtk::EventBox();
	mainVbox->pack_start(*tableBox, verticalCenter, false);

	mainHbox->pack_start(*mainVbox, false, false);

	mainEventBox->add(*mainHbox);

	table = new TableWidget();
	tableBox->add(*table);

	table->getTable()->set_homogeneous(homogeneous);
	add(*mainEventBox);
	show_all_children();
}

TableCenterWidget::~TableCenterWidget()
{
	dispose();
}

void TableCenterWidget::initialize()
{

}

void TableCenterWidget::dispose()
{
	remove();

	if (mainEventBox)
	{
		delete mainEventBox;
		mainEventBox = NULL;
	}
	if (mainHbox)
	{
		delete mainHbox;
		mainHbox = NULL;
	}
	if (mainVbox)
	{
		delete mainVbox;
		mainVbox = NULL;
	}
}

void TableCenterWidget::resize(unsigned int row, unsigned int column)
{
	table->resize(row, column);
}

void TableCenterWidget::put(Gtk::Widget * widget, int row, int column)
{
	table->put(widget, row, column);
}

void TableCenterWidget::put(Gtk::Widget * widget, int row, int column, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign)
{
	table->put(widget, row, column, xAlign, yAlign);
}

void TableCenterWidget::setSpacings(int row, int column)
{
	table->setSpacings(row, column);
}

unsigned int TableCenterWidget::getCountElements()
{
	return table->getCountElements();
}

void TableCenterWidget::clear()
{
	table->clear();
}
