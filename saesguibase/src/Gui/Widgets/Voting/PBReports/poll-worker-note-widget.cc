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

#include "poll-worker-note-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <Voting/PBReports/pollworkers-schema.hxx>
#include <System/Utils/StringUtils.hxx>
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
using namespace Gtk;
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Utils;

ISMTTLog* PollWorkerNoteWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerNoteWidget",GETTEXT_PACKAGE);

PollWorkerNoteWidget::PollWorkerNoteWidget(ustring noteTitle, ustring titleText,
                                           ustring acceptButtonText, 
                                           ustring backButtonText,
                                           int buttonWidth,
                                           int buttonHeight,
                                           bool showTitle)
:TextViewComplex(titleText, acceptButtonText, backButtonText, 20, 0, 150, buttonHeight, buttonWidth,showTitle)
{
	this->showTitle = showTitle;
	Initialize(noteTitle);
}

PollWorkerNoteWidget::~PollWorkerNoteWidget()
{

}

void PollWorkerNoteWidget::Initialize(ustring labelText)
{
	Label* labelNote = manage(new Label(labelText));

	Pango::FontDescription fontTitle = labelNote->get_style()->get_font();
	fontTitle.set_size(16*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelNote->modify_font(fontTitle);

	pack_start(*labelNote, false, false);
	reorder_child(*labelNote, 0);

	Notes::NoteSequence seq = MachineOperationManager::getInstance()->getPollworkers()->getNotes().getNote();
	Notes::NoteIterator it;

	for(it = seq.begin();
			it != seq.end();
			it++)
	{
		if ((*it).getType() == NoteWorkerMemberType::POLLWORKERS_OPEN_ELECTION)
		{
			customCode = (*it).getCustom_code();
			textview->setText((*it).getContent());
			break;
		}
	}
}	

void PollWorkerNoteWidget::SetNote(Note note, string customCode)
{

}

void PollWorkerNoteWidget::GetNote(Note& note, string& customCode)
{

}

void PollWorkerNoteWidget::Clean()
{

}

void PollWorkerNoteWidget::Persist()
{
	logger->Debug("Persist PollWorkerNoteWidget");
	SaveNote();
}

void PollWorkerNoteWidget::on_acceptButton_clicked()
{
	if((GetTitle() == "") && showTitle)
		m_signal_titleEmpty.emit();
	else if(StringUtils::trim(textview->getText()).empty())
		m_signal_contentEmpty();
	else
		m_noteSaved_clicked.emit();
}

PollWorkerNoteWidget::type_void_signal PollWorkerNoteWidget::signal_noteSaved_clicked()
{
	return m_noteSaved_clicked;
}

PollWorkerNoteWidget::type_void_signal PollWorkerNoteWidget::signal_titleEmpty()
{
	return m_signal_titleEmpty;
}

PollWorkerNoteWidget::type_void_signal PollWorkerNoteWidget::signal_contentEmpty()
{
	return m_signal_contentEmpty;
}

void PollWorkerNoteWidget::SaveNote()
{
	Note note;
	
	string title = GetTitle();
	note.setTitle(title);

	string content = textview->getText();
	note.setContent(content);

	if (customCode.empty())
	{
		note.setType(NoteWorkerMemberType::POLLWORKERS_OPEN_ELECTION);
		MachineOperationManager::getInstance()->getPollworkers()->AddNote(note);
	}
	else
	{
		note.setCustom_code(customCode);
		MachineOperationManager::getInstance()->getPollworkers()->ModifyNote(note);
	}

	MachineOperationManager::getInstance()->getPollworkers()->Persist();
}
