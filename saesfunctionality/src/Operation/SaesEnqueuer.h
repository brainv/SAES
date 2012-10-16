/**
 * @file	functionality.h
 *
 * @brief	Header file to the functionality class.
 */

#ifndef _SAESENQUEUER_H_
#define _SAESENQUEUER_H_

#include <glibmm.h>
#include <iostream>
#include <Log/ISMTTLog.h>
#include <System/Enqueuer.h>
#include <System/SafeBuffer.h>
#include <Voting/Vote/VoteWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			class VoteResult
			{
			public:
				VoteResult();
					
				VoteResult(MachineOperationManager::VoteFromSafeBufferResult result, Smartmatic::SAES::Voting::Vote::Vote * vote);
					
				~VoteResult();

				MachineOperationManager::VoteFromSafeBufferResult getResult();
					
				Smartmatic::SAES::Voting::Vote::Vote * getVote();

				void setResult(MachineOperationManager::VoteFromSafeBufferResult result);
					
				void setVote(Smartmatic::SAES::Voting::Vote::Vote * vote);
					
				private:
				MachineOperationManager::VoteFromSafeBufferResult result;
				Smartmatic::SAES::Voting::Vote::Vote * vote;
			};

			/**
			 * @brief	SaesEnqueuer class. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */
			class SaesEnqueuer: public Smartmatic::System::Enqueuer<Smartmatic::System::SafeBuffer * >
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *		
				 */
				SaesEnqueuer();
				
				/**
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 */

				virtual ~SaesEnqueuer();

				void getVoteResultList(std::list <VoteResult *> & list);

			protected:

				virtual Smartmatic::Log::ISMTTLog * getLogger();
				void Process(Smartmatic::System::SafeBuffer * safeBuf);
				void DiscardItem(Smartmatic::System::SafeBuffer * safeBuf);
				Glib::Mutex mutex;

			private:
				bool cleanVoteRepeated; ///< flag clean vote
				std::string currentVoteCode; ///< current vote code
				long countRecievedData;
				std::list <VoteResult * > voteResultList;
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		};
	};
};
#endif // _SAESENQUEUER_H_
