/**
 * @file PoliceNoteWrapper.hxx
 * @brief Header class police note wrapper
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#ifndef POLICE_NOTE_WRAPPER_H_
#define POLICE_NOTE_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/police-notes-schema.hxx>

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
			 * @class PoliceNoteWrapper
			 * @brief class police note wrapper.
			 * @date 25/05/2012
			 * @author Yadickson Soto
			 */
			class PoliceNoteWrapper
			{
			private:

					/**
					 * @brief	Load the police note information
					 * @param	xmlFile	The std::string to load.
					 * @return true is load file
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					bool load(std::string xmlFile)
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

					PoliceNotes * policeNotes;   ///< police notes
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

			public:

					/**
					 * @brief	Class constructor.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					PoliceNoteWrapper();
					/**
					 * @brief	Class destroyer.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~PoliceNoteWrapper();
					/**
					 * @brief	Adds police note
					 * @param	policeNote	The police note.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					void addPoliceNote(PoliceNote & policeNote);
					/**
					 * @brief	Removes the police note by customCode.
					 * @param	customCode	The custom code.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					void removePoliceNote(std::string customCode);
					/**
					 * @brief	Modify police note.
					 * @param	policeNote	The police note.
					 * @return  true is modify success
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					bool modifyPoliceNote(PoliceNote & policeNote);
					/**
					 * @brief	Method getter police note by custom code.
					 * @param	customCode	The custom code.
					 * @return police note by custom code
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					PoliceNote getPoliceNote(std::string customCode);
					/**
					 * @brief	Method getter police notes
					 * @return police notes
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					PoliceNotes getPoliceNotes();
					/**
					 * @brief	Persists.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					void persistence()
		               throw (Smartmatic::System::Exception::CryptoException,
		                        Smartmatic::System::Exception::SignedException,
		                        Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Init this object.
					 * @return true is load file
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					bool init ()
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 * @date 25/05/2012
					 * @author Yadickson Soto
					 */
					void dispose ();
			};
		 }
	  }
   }
}

#endif // POLICE_NOTE_WRAPPER_H_
