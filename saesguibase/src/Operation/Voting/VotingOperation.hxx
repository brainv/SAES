/**
 * @file VotingOperation.hxx
 * @brief Header class voting operation
 * @date 23/04/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGOPERATION_HXX_
#define VOTINGOPERATION_HXX_

#include <string>
#include <Voting/Vote/vote-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				namespace Voting
				{
					/**
					 * @class VotingOperation
					 * @brief class voting operation
					 * @date 23/04/2012
					 * @author Yadickson Soto
					 */
					class VotingOperation
					{
					protected:
						/**
						 * @brief class constructor
						 * @date 23/04/2012
						 * @author Yadickson Soto
						 */
						VotingOperation();
					public:
						/**
						 * @brief class destroy
						 * @date 23/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~VotingOperation();
						/**
						 * @brief method refresh
						 * @date 23/04/2012
						 * @author Yadickson Soto
						 */
						static void refresh();
						/**
						 * @brief method getter window name
						 * @return window name
						 * @date 23/04/2012
						 * @author Yadickson Soto
						 */
						static std::string getWindowName();
						/**
						 * @brief method getter wvote mode
						 * @return vote mode
						 * @date 23/04/2012
						 * @author Yadickson Soto
						 */
						static Smartmatic::SAES::Voting::Vote::VoteMode getVoteMode();
					};
				}
			}
		}
	}
}

#endif /* VOTINGOPERATION_HXX_ */
