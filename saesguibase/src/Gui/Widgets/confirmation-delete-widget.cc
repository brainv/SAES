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

#include "confirmation-delete-widget.h"

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
using namespace Smartmatic::SAES::GUI::Widgets;

ConfirmationDeleteWidget::ConfirmationDeleteWidget()
{
	int width = 150;
	int height = 60;
	
	label = new Label(_("Smartmatic.SAES.GUI.Widget.ConfirmationDeleteWidget.DeleteQuestion"));
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);
	label->set_size_request(400, 200);

	deleteButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Widget.ConfirmationDeleteWidget.Delete"));
	deleteButton->set_size_request(width, height);
	deleteButton->signal_clicked().connect(sigc::mem_fun(*this, &ConfirmationDeleteWidget::on_deleteButton_clicked));
	deleteButton->SetButtonType(SmartmaticButton::Ok);
	deleteButton->WidgetsPosition(5,6,0);


	backButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Widget.ConfirmationDeleteWidget.Back"));
	backButton->set_size_request(width, height);
	backButton->signal_clicked().connect(sigc::mem_fun(*this, &ConfirmationDeleteWidget::on_backButton_clicked));
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);

	btnBox = new HButtonBox();
	btnBox->pack_start(*backButton, false, false);
	btnBox->pack_start(*deleteButton, false, false);
	btnBox->set_layout(BUTTONBOX_SPREAD);

	vbox = new VBox();
	vbox->pack_start(*label, false, false);
	vbox->pack_start(*btnBox, false, false);

	align = new Alignment();
	align->set(0.5, 0.5, 0, 1);
	align->add(*vbox);

	add(*align);
	show_all_children();
}

ConfirmationDeleteWidget::~ConfirmationDeleteWidget()
{
	remove();

	if (label)
	{
		delete label;
		label = NULL;
	}
	if (deleteButton)
	{
		delete deleteButton;
		deleteButton = NULL;
	}
	if (backButton)
	{
		delete backButton;
		backButton = NULL;
	}
	if (btnBox)
	{
		delete btnBox;
		btnBox = NULL;
	}
	if (vbox)
	{
		delete vbox;
		vbox = NULL;
	}
	if (align)
	{
		delete align;
		align = NULL;
	}
}

void ConfirmationDeleteWidget::on_deleteButton_clicked()
{
	m_answer_signal.emit(true);
}

void ConfirmationDeleteWidget::on_backButton_clicked()
{
	m_answer_signal.emit(false);
}

ConfirmationDeleteWidget::type_bool_signal ConfirmationDeleteWidget::on_answer_emit()
{
	return m_answer_signal;
}
