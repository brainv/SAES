/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include "combo-box-choose-widget.h"

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;

ComboBoxChooseWidget::ComboBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo * dialogInfo)
:	Gtk::HBox(5)
{
	labelTitle.set_label(dialogInfo->getTitle());
	labelTitle.set_alignment(0.0, 0.5);//TODO configuration
	labelTitle.set_padding(0, 0);
	labelTitle.set_size_request(180, 30);
	Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_size(10*Pango::SCALE);
	labelTitle.modify_font(fontTitle);

	imageTitle.set(dialogInfo->getTitleImagePath());

	if(dialogInfo->getTitleImagePath().compare("")!=0)
	{
		pack_start (imageTitle,Gtk::PACK_SHRINK);
	}

	pack_start (labelTitle,Gtk::PACK_SHRINK);

	m_refTreeModel = Gtk::ListStore::create(choicesColumnModel);
	comboChoices.set_model(m_refTreeModel);
	comboChoices.set_size_request (150,100);
	//Connect signal handler:
	connCombo = comboChoices.signal_changed().connect( sigc::mem_fun(*this, &ComboBoxChooseWidget::on_combo_changed) );

	for(unsigned int i=0;i < (dialogInfo->getListOfChoices()).size(); i++)
	{
		//Fill the ComboBox's Tree Model:
		Gtk::TreeModel::Row row = *(m_refTreeModel->append());
		row[choicesColumnModel.m_col_name] = dialogInfo->getListOfChoices()[i]->getName();
	}

	//Add the ComboBox to the window.
	comboChoices.pack_start(choicesColumnModel.m_col_name);
	comboChoices.set_active(0);

	pack_start (comboChoices,Gtk::PACK_SHRINK);
	show_all_children ();
	set_visible (true);
}

void ComboBoxChooseWidget::ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight)
{
	comboChoices.set_size_request (WidgetOptionsWidth,WidgetOptionsHeight);
}

ComboBoxChooseWidget::~ComboBoxChooseWidget()
{

}

std::string ComboBoxChooseWidget::getOptionName()
{
	return labelTitle.get_label();
}

std::string ComboBoxChooseWidget::getOptionValue()
{
	return optionSelected;
}

void ComboBoxChooseWidget::Dispose()
{
	connCombo.disconnect();
}

void ComboBoxChooseWidget::on_combo_changed()
{
  Gtk::TreeModel::iterator iter = comboChoices.get_active();
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    if(row)
    {
      optionSelected = row[choicesColumnModel.m_col_name];
    }
  }
}

