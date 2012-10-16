/**
 * @file	VotingMemento.hxx
 *
 * @brief	voting memento class.
 */

#ifndef __VOTING_MEMENTO_H__
#define __VOTING_MEMENTO_H__

#include "VotingState.hxx"

namespace Smartmatic
{
   namespace SAES
   {
      namespace Operation
      {
         namespace Voting
         {
            /**
             * @brief	Voting memento. 
             * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date	07-03-2011
             */
            class VotingMemento
            {
            private:
                VotingState * state;	///< The voting state
                int position; ///< position in creation

            public:

               /**
                * @brief	class constructor.
                * @param [in,out]	state	If non-null, the state.
                */

               VotingMemento ( VotingState * state , int position );

               /**
                * @brief	Finaliser.
                */

               ~VotingMemento ();

               /**
                * @brief	gets the state of memento.
                * @return	state of memento.
                */

               VotingState * getState();

               /**
                * @brief    gets the position of memento.
                * @return   position of memento.
                */

               int getPosition();
            };
         }
      }
   }
}

#endif /*__VOTING_MEMENTO_H__*/
