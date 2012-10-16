/**
 * @file	poll-worker-note-widget.h
 *
 * @brief	Declares the poll worker note widget class.
 */

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

#ifndef _POLL_WORKER_NOTE_WIDGET_H_
#define _POLL_WORKER_NOTE_WIDGET_H_

#include <gtkmm.h>
#include "Widgets/text-view-complex.h"
#include <Voting/PBReports/pollworkers-schema.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					namespace PBReports
					{
						/**
						 * @brief	Poll worker note widget. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class PollWorkerNoteWidget : public Smartmatic::GUI::Widgets::TextViewComplex
						{
						public:

							/**
							 * @brief	Constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	noteTitle			The note title.
							 * @param	titleText			The title text.
							 * @param	acceptButtonText	The accept button text.
							 * @param	backButtonText  	The back button text.
							 * @param	buttonWidth			Width of the button.
							 * @param	buttonHeight		Height of the button.
							 */

							PollWorkerNoteWidget(Glib::ustring noteTitle, Glib::ustring titleText,
							                     Glib::ustring acceptButtonText, 
							                     Glib::ustring backButtonText,
							                     int buttonWidth = -1,
							                     int buttonHeight = -1,
							                     bool showTitle = false);

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~PollWorkerNoteWidget();

							/**
							 * @brief	Persists this object.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void Persist();

							/**
							 * @brief	Sets a note.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	note	  	The note.
							 * @param	customCode	The custom code.
							 */

							void SetNote(Smartmatic::SAES::Voting::PBReports::Note note, std::string customCode);

							/**
							 * @brief	Gets a note.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param [in,out]	note	  	The note.
							 * @param [in,out]	customCode	The custom code.
							 */

							void GetNote(Smartmatic::SAES::Voting::PBReports::Note& note, std::string& customCode);

							/**
							 * @brief	Cleans this object.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void Clean();

						    /**
							 * @brief definition of signals
						     */
							typedef sigc::signal<void> type_void_signal;

						    /**
							 * @brief method to connect signals
						     */
							type_void_signal signal_noteSaved_clicked();

							/**
							 * @brief	Raises the title empty event.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	.
							 */

							type_void_signal signal_titleEmpty();

							/**
							 * @brief	Raises the content empty event.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @return	.
							 */

							type_void_signal signal_contentEmpty();
												
						protected:
						    /**
							 * declaration of signal handler
						     */
							type_void_signal m_noteSaved_clicked;

							type_void_signal m_signal_titleEmpty;   ///< The signal title empty
							type_void_signal m_signal_contentEmpty; ///< The signal content empty

							/**
							 * @brief	Handles accept button clicked signals.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void on_acceptButton_clicked();

						private:

							/**
							 * @brief	Initializes this object.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	labelText	The label text.
							 */

							void Initialize(Glib::ustring labelText);

							/**
							 * @brief	Saves a note.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	textbuffer	The textbuffer.
							 */

							void SaveNote();
							
							std::string customCode; ///< The custom code
							bool showTitle;  ///< TRue if show title
							static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif // _POLL_WORKER_NOTE_WIDGET_H_
