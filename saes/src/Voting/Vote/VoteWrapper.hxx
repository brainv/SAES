/**
 * @file	VoteWrapper.hxx
 *
 * @brief	vote wrapper class.
 */

#ifndef _VOTE_WRAPPER_H_
#define _VOTE_WRAPPER_H_

#include <Voting/Vote/vote-schema.hxx>
#include <System/Exception/XmlException.hxx>
#include <iostream>
#include <Voting/PBReports/pvform-schema.hxx>
#include <Voting/ElectoralConfiguration.hxx>


#include "Exceptions/Voting/Vote/QRVoteInvalidFormatException.h"
#include "Exceptions/Voting/Vote/QRVoteSignatureException.h"

namespace Smartmatic
{
    namespace Log
    {
        /**
         * @brief	SMTT Log Interface 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class ISMTTLog;
    }
  namespace SAES
  {
    namespace Voting
    {
      namespace Vote
      {
        /**
         * @brief	Vote wrapper. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class VoteWrapper
        {
        protected:

            /**
             * @brief	Default constructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            VoteWrapper();

           static void CheckFindResult(int markPosition) throw (Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteInvalidFormatException);

        public:

            /**
             * @brief	Finaliser.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            virtual ~VoteWrapper();

            /**
             * @brief   Method generate code.
             * @param   vote object vote
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    07/05/2011
             *
             * @return  vote code
             */

            static std::string generateCode(Vote & vote);

            /**
             * @brief	Vote file to string.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param [in,out]	vote	The vote.
             *
             * @return	The vote into a string
             */

            static bool voteFileToVote(std::string & file, Vote & vote);

            /**
             * @brief	Vote to string.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param [in,out]	vote	The vote.
             *
             * @return	The vote into a string
             */

            static void voteToString(const Vote & vote, std::string& outStringVote)
                throw (Smartmatic::System::Exception::XmlException);

            /**
             * @brief   transform Vote to PVVote.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    06/05/2011
             *
             * @param electoralConfiguration electoral configuration
             * @param [in,out]  vote    The vote.
             * @return  The vote into a PVVote
             */

            static Smartmatic::SAES::Voting::PBReports::PVVote voteToPVVote(
                    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
                    Vote & vote);

            static Smartmatic::SAES::Voting::PBReports::PVCandidate getCandidateInfo(
                    Smartmatic::SAES::Voting::Election::Eligible_option & eligibleOption,
                    Smartmatic::SAES::Voting::Election::Ballot_option & ballotOption);

            static void getPartyInfo(
                    Smartmatic::SAES::Voting::Election::Ballot_option & ballotOption,
                    std::string & pvPartyAbreviation,
                    std::string & pvPartyName);

            /**
             * @brief   validate vote.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    07/05/2011
             *
             * @param electoralConfiguration electoral configuration
             * @param [in,out]  vote    The vote.
             * @return  true is validate vote
             */
            static bool validateVote(
                    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
                    Vote & vote);

            /**
             * @brief   validate vote code.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    07/05/2011
             *
             * @param [in,out]  vote    The vote.
             * @return  true is validate vote
             */
            static bool validateVoteCode(Vote & vote);

            /**
             * @brief   validate logical voter group vote.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    07/05/2011
             *
             * @param electoralConfiguration electoral configuration
             * @param [in,out]  vote    The vote.
             * @return  true is validate vote
             */
            static bool validateLogicalVoterGroupVote(
                    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
                    Vote & vote);

            /**
             * @brief   validate voting device code vote.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    07/05/2011
             *
             * @param electoralConfiguration electoral configuration
             * @param [in,out]  vote    The vote.
             * @return  true is validate vote
             */
            static bool validateVotingDeviceCodeVote(
                    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
                    Vote & vote);

            static void packVoteForQR(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,  const Vote & vote, Smartmatic::System::SafeBuffer& outBuffer, bool deflate = true);

            static bool unpackVoteFromQR(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Smartmatic::System::SafeBuffer& intBuffer, Vote & outVote, bool inflate = true);


            static void getReducedXmlVoteString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Vote vote, std::string& outStringVote);

            static void getExpandedXmlVote(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Vote& inOutVote)
            throw (Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteInvalidFormatException);



            static void getSizeOptimizedVoteString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, const Vote& vote, std::string& outStringVote);

            static void getVoteFromSizeOptimizedString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::string& stringVote, Vote& outVote )
            throw (Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteInvalidFormatException, Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteSignatureException);

            static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
        };
      }
    }
  }
}

#endif /* _VOTE_WRAPPER_H_ */
