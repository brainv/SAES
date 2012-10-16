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

#ifndef _VOTE_STATISTICS_H_
#define _VOTE_STATISTICS_H_
#include <Voting/Vote/vote-schema.hxx>
#include <Voting/ElectoralConfiguration.hxx>
#include "Voting/PBReports/vote-statistics-schema.hxx"
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/VoteException.hxx>
#include "VoteStatistic.hxx"
#include <glibmm.h>

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
			  * @brief	Vote counter by CA. 
			  *
			  * @author	Eduardo.campione
			  * @date	28/04/2011
			  */

			 class VoteCounterByCA
			 {
				 private:
					 unsigned int counter;  ///< The counter
					 std::string caCode;	///< The CA code
					 std::string caValue;   ///< The ca value
					 
				 public:

					 /**
					  * @brief	Constructor.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  *
					  * @param	caCode		  	The ca code.
					  * @param	caValue		  	The ca value.
					  * @param	initialCounter	The initial counter.
					  */

					 VoteCounterByCA(std::string caCode, std::string caValue, unsigned int initialCounter = 0);

					 /**
					  * @brief	Finaliser.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  */

					 ~VoteCounterByCA();

					 /**
					  * @brief	Increment counter.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  */

					 void incrementCounter();

					 /**
					  * @brief	Gets the ca code.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  *
					  * @return	The ca code.
					  */

					 std::string getCACode();

					 /**
					  * @brief	Gets the ca value.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  *
					  * @return	The ca value.
					  */

					 std::string getCAValue();

					 /**
					  * @brief	Gets the counter.
					  *
					  * @author	Eduardo.campione
					  * @date	28/04/2011
					  *
					  * @return	The counter.
					  */

					 unsigned int getCounter();

					 void clearCounter();

					
			 };
			  /**
             * @class VoteStatistics
             * @brief Header class VoteStatistics
             * @author Marcel Mancini <marcel.mancini@smartmatic.com>
             * @date 29-03-2011
             */
			class VoteStatisticsWrapper
			{
			private:
					Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* votingDeviceWrapper;   ///< The voting device wrapper
					Smartmatic::SAES::Voting::VotingDevice::Voting_device vd;   ///< The voting device

					VoteStatistic * statistics;
					unsigned int deltaVotes;
					std::vector<VoteCounterByCA> voteCountersByCA;  ///< The vote counters by ca
					std::vector<std::string> voteGUUIDsRegistered;  ///< The vote GUI registered

					Glib::Mutex mutex;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
			public:

					/**
					 * @brief	Class constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					VoteStatisticsWrapper();

					/**
					 * @brief	Class destroyer.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~VoteStatisticsWrapper();	

					/**
					 * @brief	Gets the official votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The official votes.
					 */

					unsigned int getOfficialVotes();

					/**
					 * @brief	Gets the simulated votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The simulated votes.
					 */

					unsigned int getSimulatedVotes();

					/**
					 * @brief	Gets the demo votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The demo votes.
					 */

					unsigned int getDemoVotes();

					/**
					 * @brief	Convertes to generated class
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The vote statistic generated class.
					 */

					VoteStatistics convertToGeneratedClass();					 

					/**
					 * @brief	Gets the security copy votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The security copy votes.
					 */

					unsigned int getSecurityCopyVotes();

					/**
					 * @brief	Gets the vote counters by ca.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The vote counters by ca.
					 */

					std::vector<VoteCounterByCA> getVoteCountersByCA();

					/**
					 * @brief	Gets a vote counter by ca code and value.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	caCode 	The ca code.
					 * @param	caValue	The ca value.
					 *
					 * @return	The vote counter by ca code and value.
					 */

					unsigned int getVoteCounterByCACodeAndValue(std::string caCode, std::string caValue);

					/**
					 * @brief	Gets the total votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The total votes.
					 */

					unsigned int getTotalVotes();

					/**
					 * @brief	Gets the super null votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The super null votes.
					 */

					unsigned int getSuperNullVotes();					 

					/**
					 * @brief	Gets the duplicated votes.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The duplicated votes.
					 */

					unsigned int getDuplicatedVotes();					 
					void clearCounter(bool cleanDuplicated = false);
					bool ProcessVote(Smartmatic::SAES::Voting::Vote::Vote & vote);

					/**
					 * @brief	if vote is  processed.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	vote	The vote.
					 *
					 * @return	true if vote processed, false if not.
					 */

					bool IsVoteProcessed(Smartmatic::SAES::Voting::Vote::Vote & vote);

					/**
					 * @brief	if voteGUUID is processed.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	voteGUUID	The vote guuid.
					 *
					 * @return	true if vote processed, false if not.
					 */

					bool IsVoteProcessed(std::string voteGUUID);

					/**
					 * @brief	Initialises this object.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	elecConf	The elec conf.
					 */

					bool init (Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
		              throw (Smartmatic::System::Exception::CryptoException,
		                     Smartmatic::System::Exception::SignedException,
		                     Smartmatic::System::Exception::XmlException,
		                     Smartmatic::System::Exception::VoteException);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void Dispose ();

					/**
                     * @brief Load vote statistic file.
                     *
                     * @author    Yadickson Soto yadickson.soto@smartmatic.com
                     * @date  21/05/2011
                     *
                     * @param xmlFile file full path vote statistic
                     */
					VoteStatistic * Load(std::string xmlFile)
                        throw (Smartmatic::System::Exception::CryptoException,
                               Smartmatic::System::Exception::SignedException,
                               Smartmatic::System::Exception::XmlException);

 					  /**
			           * @brief Persist the vote statistic file.
			           *
			           * @author    Yadickson Soto yadickson.soto@smartmatic.com
			           * @date  20/05/2011
			           *
			           */
			          void persistence()
			              throw (Smartmatic::System::Exception::CryptoException,
			                     Smartmatic::System::Exception::SignedException,
			                     Smartmatic::System::Exception::XmlException);

			          unsigned int getDeltaVotes();

			protected:

	                    /**
	                     * @brief   Increment official votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */

	                    void incrementOfficialVotes();

	                    /**
	                     * @brief   Increment demo votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */

	                    void incrementDemoVotes();

	                    /**
	                     * @brief   Increment super null votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */

	                    void incrementSuperNullVotes();

	                    /**
	                     * @brief   Increment security votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */

	                    void incrementSecurityVotes();

	                    /**
						 * @brief   Increment simulate votes.
						 *
						 * @author  Eduardo.campione
						 * @date    28/04/2011
						 */
	                    void incrementSimulateVotes();

	                    /**
	                     * @brief   Increment total votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */

	                    void incrementTotalVotes();

	                    /**
	                     * @brief   Increment total duplicated votes.
	                     *
	                     * @author  Eduardo.campione
	                     * @date    28/04/2011
	                     */
	                    void incrementTotalDuplicatedVotes();


			};
           
		 }
	  }
   }
}

#endif // _VOTE_STATISTICS_H_
