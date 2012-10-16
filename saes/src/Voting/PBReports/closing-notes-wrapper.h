/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CLOSING_NOTES_WRAPPER_H_
#define _CLOSING_NOTES_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/close-election-notes-schema.hxx>
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

   namespace SAES
   {
      namespace Voting
      {
         namespace PBReports
         {
			/**
			 * @brief	Header class ClosingNotesWrapper.
			 *
			 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
			 * @date	29-03-2011
			 */

			class ClosingNotesWrapper
			{
			private:
					CloseElectionNotes* closingNotes;   ///< The closing notes

					/**
					 * @brief	Load the Closing Notes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	xmlFile	The std::string to load.
					 * @return true is load file
					 */

					bool Load(std::string xmlFile)
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

			public:

					/**
					 * @brief	Class constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					ClosingNotesWrapper();

					/**
					 * @brief	Class destroyer.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~ClosingNotesWrapper();					

					/**
					 * @brief	Adds a note. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	note	The note.
					 * @return	The notes (by ref) with custom code assigned
					 */

					void AddNote(CloseNote& note);

					/**
					 * @brief	Removes the note described by note.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	note	The note.
					 */

					void RemoveNote(CloseNote note);

					/**
					 * @brief	Gets the notes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The notes.
					 */

					CloseNotes getNotes();

					/**
					 * @brief	modify a note.
					 * @param	note	The note.
					 * @return	true is modify success
					 * @author	Yadickson Soto
					 * @date	24/05/2012
					 *
					 */					 
					bool modifyNote(CloseNote & note);

					/**
					 * @brief	Gets one note.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param customCode the custom code of the note to get
					 * @return	The note.
					 */					 
					CloseNote getNote(std::string customCode);
					
					/**
					 * @brief	Persists.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 */

					void Persist()
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Initialises this object.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 * @return true is load file
					 */

					bool init ()
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void Dispose ();

                    /**
                     * @brief   Method getter close election notes
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    07/05/2011
                     */
					CloseElectionNotes * getCloseElectionNotes();

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

			};
           
		 }
	  }
   }
}

#endif // _CLOSING_NOTES_WRAPPER_H_
