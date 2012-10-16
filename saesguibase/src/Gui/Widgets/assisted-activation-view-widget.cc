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

#include "Gui/Widgets/assisted-activation-view-widget.h"

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

using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;


AssistedActivationTreeView::AssistedActivationTreeView()
{
	refListStore = Gtk::ListStore::create(m_Columns);
	set_model(refListStore);
	
	append_column(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationTreeView.PresidentColumn"), m_Columns.m_col_presidentNames);
	append_column(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationTreeView.WitnessColumn"), m_Columns.m_col_witnessNames);
	append_column(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationTreeView.VoterColumn"), m_Columns.m_col_voterNames);
	/*
	append_column("President", m_Columns.m_col_presidentNames);
	append_column("Witness", m_Columns.m_col_witnessNames);
	append_column("Voter", m_Columns.m_col_voterNames);
	*/
	set_visible(true);
}

void AssistedActivationTreeView::Initialize()
{
	refListStore->clear();
	Activations activations = MachineOperationManager::getInstance()->getAssistedActivation()->getActivations();
	for(unsigned int i=0; i <activations.getActivation().size();i++)
	{
		Gtk::TreeModel::Row row = *(refListStore->append());
		row[m_Columns.m_col_presidentNames] = activations.getActivation()[i].getPollworker().getFirstName() +
				activations.getActivation()[i].getPollworker().getSurname();
		row[m_Columns.m_col_witnessNames] = activations.getActivation()[i].getPropossedPerson().getFirstName() +
				activations.getActivation()[i].getPropossedPerson().getSurname();
		row[m_Columns.m_col_voterNames] = activations.getActivation()[i].getVoter().getFirstName() +
				activations.getActivation()[i].getVoter().getSurname();
	}
	show_all_children ();
}

void AssistedActivationTreeView::SelectionChanged()
{
	
}

AssistedActivationViewWidget::AssistedActivationViewWidget()
{
	m_ScrolledWindow.add(assistedTreeView);
	m_ScrolledWindow.set_size_request (400,300);
	m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	pack_start(m_ScrolledWindow,Gtk::PACK_SHRINK);
	show_all_children ();
	set_visible(true);
}

void AssistedActivationViewWidget::Initialize()
{
	assistedTreeView.Initialize();
	
}

void AssistedActivationViewWidget::Dispose()
{
	
}
