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

#ifndef _POLLWORKERS_WRAPPER_H_
#define _POLLWORKERS_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/pollworkers-schema.hxx>
#include <list>

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
			 * @brief	Header class PollworkersWrapper.
			 *
			 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
			 * @date	29-03-2011
			 */

			class PollworkersWrapper
			{
			private:
					Pollworkers* pollworkers;   ///< The pollworkers

					/**
					 * @brief	Loads.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	xmlFile	The file to load.
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

					PollworkersWrapper();

					/**
					 * @brief	Class destroyer.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~PollworkersWrapper();					

					/**
					 * @brief	Adds a worker. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	worker	The worker.
					 */

					void AddWorker(Worker & worker);

					/**
					 * @brief	Removes the worker.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	worker	The worker.
					 */

					void RemoveWorker(Worker & worker);

					/**
					 * @brief	Modify worker.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	worker	The worker.
					 */

					void ModifyWorker(Worker & worker);

					/**
					 * @brief	Gets a worker.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	customCode	  	The custom code.
					 * @param [in,out]	worker	The worker.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool getWorker(std::string customCode,Worker & worker);

					/**
					 * @brief	Gets the workers.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The workers.
					 */

					Workers & getWorkers();

					/**
					 * @brief	Adds a note. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	note	The note.
					 */

					void AddNote(Note &note);

					/**
					 * @brief	Removes the note described by customCode.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	customCode	The custom code.
					 */

					void RemoveNote(std::string customCode);

					/**
					 * @brief	Modify note.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	note	The note.
					 */

					void ModifyNote(Note & note);

					/**
					 * @brief	Gets a note.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	customCode	The custom code.
					 *
					 * @return	The note.
					 */

					Note getNote(std::string customCode);

					/**
					 * @brief	Gets the notes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The notes.
					 */

					Notes & getNotes();

					/**
					 * @brief	Gets counts by type.
					 * @return count element
					 * @author	Yadickson Soto
					 * @date	02/05/2012
					 */
					unsigned int getCount(WorkerMemberType type);

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
                     * @brief   getter pollworkers
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    05/05/2011
                     */
                    Pollworkers* getPollworkers();

                    /**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void Dispose ();

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

			};
           
		 }
	  }
   }
}

#endif // _POLLWORKERS_WRAPPER_H_
