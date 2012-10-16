/**
 * @file	VotingOriginator.hxx
 *
 * @brief	Header class originator design pattern memento.
 */

#ifndef __VOTING_ORIGINATOR_H__
#define __VOTING_ORIGINATOR_H__

#include "VotingState.hxx"
#include "VotingMemento.hxx"

namespace Smartmatic
{
   namespace SAES
   {
      namespace Operation
      {
         namespace Voting
         {
            /**
             * @brief	Voting originator. 
             * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date	07-03-2011
             */

            class VotingOriginator
            {
            private:
                VotingState * state;	///< The voting state
                static int count; ///< count creation

            public:

               /**
                * @brief	create memento.
                * @return	new memento.
                */

               VotingMemento * createMemento();

               /**
                * @brief	restore	state from new memento.
                * @param [in,out]	state	new state memento.
                */

               void setState( VotingState * state );
            };
         }
      }
   }
}

#endif /*__VOTING_ORIGINATOR_H__*/
