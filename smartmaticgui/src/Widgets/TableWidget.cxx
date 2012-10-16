/**
 * @file TableWidget.cxx
 * @brief Body class table widget
 * @date 13/03/2012
 * @author Yadickson Soto
 */

#include "TableWidget.hxx"

using namespace Smartmatic::GUI::Widgets;

TableWidget::TableWidget(Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign)
: Gtk::EventBox()
{
	this->table = NULL;
	this->xAlign = xAlign;
	this->yAlign = yAlign;

	initialize();
	add(*table);
	show_all_children();
}

TableWidget::TableWidget(Gtk::Table * table, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign)
: Gtk::EventBox()
{
	this->table = NULL;
	this->xAlign = xAlign;
	this->yAlign = yAlign;

	add(*table);
	show_all_children();
}

TableWidget::~TableWidget()
{
	dispose();
}

void TableWidget::initialize()
{
	dispose();
	table = new Gtk::Table();
}

void TableWidget::dispose()
{
	remove();

	if (table)
	{
		delete table;
		table = NULL;
	}

	listWidget.clear();
}

void TableWidget::put(Gtk::Widget * widget, int row, int column)
{
	put(widget, row, column, xAlign, yAlign);
}

void TableWidget::put(Gtk::Widget * widget, int row, int column, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign)
{
	put(widget, row, row + 1, column, column + 1, xAlign, yAlign);
}

void TableWidget::put(Gtk::Widget * widget, int rowInit, int rowEnd, int colInit, int colEnd, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign)
{
	listWidget.push_back(widget);
	table->attach(*widget, colInit, colEnd, rowInit, rowEnd, xAlign, yAlign);
}

Gtk::Table * TableWidget::getTable()
{
	return table;
}

void TableWidget::clear()
{
	std::list <Gtk::Widget *>::iterator it;

	for (it = listWidget.begin();
			it != listWidget.end();
			it++)
	{
		Gtk::Widget * widget = *it;
		table->remove(*widget);
	}

	listWidget.clear();
}

void TableWidget::resize(unsigned int row, unsigned int column)
{
	if (table)
	{
		table->resize(row, column);
	}
}

unsigned int TableWidget::getCountElements()
{
	return listWidget.size();
}

void TableWidget::setSpacings(int row, int column)
{
	table->set_row_spacings(row);
	table->set_col_spacings(column);
}
