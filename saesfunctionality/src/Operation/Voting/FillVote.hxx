/**
 * @file	FillVote.hxx
 *
 * @brief	fill vote class.
 */


#ifndef __FILL_VOTE_H__
#define __FILL_VOTE_H__

#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/Vote/vote-schema.hxx>
#include "VotingMemento.hxx"
#include <vector>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Operation
      {
         namespace Voting
         {
            /**
             * @brief	Header class FillVote.
             * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date	23-03-2011
             */

            class FillVote
            {
            public:

               /**
                * @brief	class constructor.
                * @param [in,out]	electoralConfiguration	electoral configuration.
                */

               FillVote ( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration );

               /**
                * @brief	Finaliser.
                */

               ~FillVote ();

               /**
                * @brief	method to fill normal vote.
                * @param [in,out]	vote			 	vote.
                * @param [in,out]	contestCount	 	contest count.
                * @param [in,out]	ballotOptionCount	count of ballot option of contest.
                * @param [in,out]	caretaker		 	list memento state
                * 										@throw ElectionException.
                */

               void fillNormalVote ( Smartmatic::SAES::Voting::Vote::Vote & vote,
                   int & contestCount,
                   int & ballotOptionCount,
                   std::vector < Smartmatic::SAES::Operation::Voting::VotingMemento * > & caretaker )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to fill blank vote.
                * @param [in,out]	vote			 	vote.
                * @param [in,out]	contestCount	 	contest count.
                * @param [in,out]	ballotOptionCount	count of ballot option of contest.
                * @param [in,out]	memento			 	current memento state
                * 										@throw ElectionException.
                */

               void fillBlankVote ( Smartmatic::SAES::Voting::Vote::Vote & vote,
                   int & contestCount, 
                   int & ballotOptionCount,
                   Smartmatic::SAES::Operation::Voting::VotingMemento * memento )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to fill vote.
                * @param [in,out]	vote	 	vote.
                * @param	contestCount	 	contest count.
                * @param	ballotOptionCount	count of ballot option of contest.
                */

               void fillVote ( Smartmatic::SAES::Voting::Vote::Vote & vote,
                   int contestCount,
                   int ballotOptionCount );

            private:
			   static Smartmatic::Log::ISMTTLog* logger;	///< The logger
               Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;   ///< The electoral configuration
            };
         }
      }
   }
}

#endif /*__FILL_VOTE_H__*/
