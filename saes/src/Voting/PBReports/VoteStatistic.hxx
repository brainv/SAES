/*
 * VoteStatistic.hxx
 *
 *  Created on: 13/09/2011
 *      Author: soto
 */

#ifndef VOTESTATISTIC_HXX_
#define VOTESTATISTIC_HXX_

namespace Smartmatic
{
	namespace SAES
	{
		namespace Voting
		{
			namespace PBReports
			{
				class VoteStatistic
				{
				public:
					VoteStatistic();
					virtual ~VoteStatistic();

					void clearAll();
					void clearAllNotDuplicate();

					unsigned int getTotalVotes();
					unsigned int getOfficialVotes();
					unsigned int getDemoVotes();
					unsigned int getSecurityCopyVotes();
					unsigned int getSuperNullVotes();
					unsigned int getDuplicatedVotes();
					unsigned int getSimulateVotes();

					void setTotalVotes(unsigned int totalVotes);
					void setOfficialVotes(unsigned int officialVotes);
					void setDemoVotes(unsigned int demoVotes);
					void setSecurityCopyVotes(unsigned int securityCopyVotes);
					void setSuperNullVotes(unsigned int superNullVotes);
					void setDuplicatedVotes(unsigned int duplicatedVotes);
					void setSimulateVotes(unsigned int simulateVotes);

				private:
					unsigned int totalVotes;	///< The total votes
					unsigned int officialVotes; ///< The official votes
					unsigned int demoVotes; ///< The demo votes
					unsigned int securityCopyVotes; ///< The security copy votes
					unsigned int superNullVotes; ///< The super null votes
					unsigned int duplicatedVotes;///< The duplicated votes
					unsigned int simulateVotes;///< The simulated votes
				};
			}
		}
	}
}

#endif /* VOTESTATISITC_HXX_ */
