/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * counterstat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * counterstat is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "counter-stat-widget.h"
#include <sstream>
#include <gdk/gdkkeysyms.h>
#include <System/Utils/StringUtils.hxx>
#include "NumericStatWidget.hxx"

using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

CounterStatWidget::CounterStatWidget(IStatWidget * statWidget, bool horizontal)
{
	this->statWidget = statWidget;
	statNameLabel = NULL;
	alignEntry = NULL;
	vbox = NULL;

	Initialize(horizontal);
}

CounterStatWidget::CounterStatWidget(std::string statName, int maxCount, bool horizontal)
{
	statWidget = new NumericStatWidget(statName, "", "", maxCount);
	statNameLabel = NULL;
	alignEntry = NULL;
	vbox = NULL;

	Initialize(horizontal);
}

CounterStatWidget::~CounterStatWidget()
{
	if (statWidget) delete statWidget;
	if (statNameLabel) delete statNameLabel;
	if (alignEntry) delete alignEntry;
	if (vbox) delete vbox;
}

void CounterStatWidget::Initialize(bool horizontal)
{
	if (statNameLabel) delete statNameLabel;
	statNameLabel = new Label(statWidget->getName());
	//statNameLabel->set_line_wrap();

	if (alignEntry) delete alignEntry;
	alignEntry = new Alignment();
	alignEntry->set(0.5, 0.5, 0, 0);
	alignEntry->add(*statWidget);

	if(!horizontal)
	{
		if (vbox) delete vbox;
		vbox = new VBox();
		vbox->pack_start(*statNameLabel, true, true);
		vbox->pack_start(*alignEntry);
		pack_start(*vbox, true, true);
		vbox->set_spacing(10);
	}
	else
	{
		pack_start(*statNameLabel, true, true);
		pack_end(*alignEntry);
	}

	set_spacing(5);
	set_homogeneous(false);
	show_all_children();	
}

void CounterStatWidget::SetValue(std::string value)
{
	statWidget->setValue(value);
}

std::string CounterStatWidget::GetStatName()
{
	return statWidget->getName();
}

void CounterStatWidget::SetInsensitive(bool insensitive)
{
	statWidget->setEnable(!insensitive);
}

void CounterStatWidget::AlignEntryText(double align)
{
	statWidget->setAlign(align);
}

void CounterStatWidget::AlignLabel(double align)
{
	statNameLabel->set_alignment(align);
}

void CounterStatWidget::SetEntryWidth(int width)
{
	statWidget->setSize(width, -1);

	//int labelWidth, dummy;
	//get_size_request(labelWidth, dummy);
	//labelWidth -= (width + 10);
	//statNameLabel->set_size_request(labelWidth, -1);
}

std::string CounterStatWidget::GetStatValue()
{
	return statWidget->getValue();
}

std::string CounterStatWidget::getCode() const
{
	return statWidget->getCode();
}

void CounterStatWidget::SetWeight(Pango::Weight weight)
{
	Pango::FontDescription fontTitle = statNameLabel->get_style()->get_font();
	fontTitle.set_weight(weight);
	statNameLabel->modify_font(fontTitle);
}

void CounterStatWidget::SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration &labelConf)
{
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(statNameLabel, labelConf);
}

bool CounterStatWidget::validate()
{
	return statWidget->validate();
}
