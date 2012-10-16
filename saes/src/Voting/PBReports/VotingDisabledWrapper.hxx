/**
 * @file VotingDisabledWrapper.hxx
 * @brief Header class voting disabled wrapper
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTING_DISABLED_WRAPPER_H_
#define VOTING_DISABLED_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/voting-disabled-information-schema.hxx>

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
			 * @class VotingDisabledWrapper
			 * @brief class voting disabled wrapper.
			 * @date 21/05/2012
			 * @author Yadickson Soto
			 */
			class VotingDisabledWrapper
			{
			private:

					/**
					 * @brief	Load the voting disabled information
					 * @param	xmlFile	The std::string to load.
					 * @return true is load file
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					bool load(std::string xmlFile)
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

					VotingDisabledInformation * votingDisabledInformation;   ///< voting disabled information
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

			public:

					/**
					 * @brief	Class constructor.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					VotingDisabledWrapper();
					/**
					 * @brief	Class destroyer.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~VotingDisabledWrapper();
					/**
					 * @brief	Adds voting disabled
					 * @param	votingDisabled	The voting disabled.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					void addVotingDisabled(VotingDisabled & votingDisabled);
					/**
					 * @brief	Removes the voting disabled by customCode.
					 * @param	customCode	The custom code.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					void removeVotingDisabled(std::string customCode);
					/**
					 * @brief	Modify voting disabled.
					 * @param	votingDisabled	The voting disabled.
					 * @return  true is modify success
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					bool modifyVotingDisabled(VotingDisabled & votingDisabled);
					/**
					 * @brief	Method getter voting disabled by custom code.
					 * @param	customCode	The custom code.
					 * @return voting disabled by custom code
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					VotingDisabled getVotingDisabled(std::string customCode);
					/**
					 * @brief	Method getter voting disabled information
					 * @return voting disabled information
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					VotingDisabledInformation getVotingDisabledInformation();
					/**
					 * @brief	Persists.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					void persistence()
		               throw (Smartmatic::System::Exception::CryptoException,
		                        Smartmatic::System::Exception::SignedException,
		                        Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Init this object.
					 * @return true is load file
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					bool init ()
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 * @date 21/05/2012
					 * @author Yadickson Soto
					 */
					void dispose ();
			};
		 }
	  }
   }
}

#endif // VOTING_DISABLED_WRAPPER_H_
