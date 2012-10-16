/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk_functionalities
 * Copyright (C)  2010 <>
 * 
 * gtk_functionalities is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk_functionalities is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Operation/SaesEnqueuer.h>
#include <System/Compression/compression-class.h>
#include "Operation/MachineOperationManager.hxx"
#include <System/Compression/compression-class.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace std;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Functionality::Configuration;

ISMTTLog* SaesEnqueuer::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.SaesEnqueuer",GETTEXT_PACKAGE);

SaesEnqueuer::SaesEnqueuer()
{
	countRecievedData = 0;
	cleanVoteRepeated = SAESFunctionalityConfigurationManager::Current()->getEnqueueVoteConfiguration().getCleanVoteRepeated();
}

SaesEnqueuer::~SaesEnqueuer()
{

}

void SaesEnqueuer::Process(Smartmatic::System::SafeBuffer * safeBuf)
{
	logger->Debug("Start process vote");
	Glib::Mutex::Lock lock(mutex);

	if (safeBuf != NULL)
	{
		{
			std::stringstream ss;
			ss << "Fase # 5 : Get signal Enqueuer data - size : " << safeBuf->GetSize() << " - count data : " << ++countRecievedData;
			logger->Debug(ss.str());
		}

		std::list <SafeBuffer *> list;
		std::list <SafeBuffer *>::iterator it;

		CompressionClass::Inflate(*safeBuf, list);

		{
			std::stringstream ss;
			ss << "Fase # 5 : Count vote list of buffer : " << list.size();
			logger->Debug(ss.str());
		}

		for (it = list.begin();
			 it != list.end();
			 it++)
		{
			SafeBuffer * buffer = (*it);

			{
				std::stringstream ss;
				ss << "Fase # 5 : Buffer vote size : " << buffer->GetSize();
				logger->Debug(ss.str());
			}

			/*
			std::string data;

			if (buffer->GetSize() > 0)
			{
				data.assign((const char*)buffer->GetData(), buffer->GetSize());
				data.resize(buffer->GetSize());
			}
			*/

			Vote::Vote * vote = NULL;
			MachineOperationManager::VoteFromSafeBufferResult parseResult = MachineOperationManager::getInstance()->getVoteFromSafeBuffer(*buffer, vote, false);
			
			if (cleanVoteRepeated && parseResult == MachineOperationManager::VOTE_FROM_BUFFER_SUCCESS)
			{
				if (currentVoteCode == vote->getCode())
				{
					delete vote;
					vote = NULL;
					currentVoteCode = "";
					logger->Debug("Discard Duplicates Vote");
				}
				else
				{
					currentVoteCode = vote->getCode();
					voteResultList.push_back(new VoteResult(parseResult, vote));
				}
			}
			else
			{
				voteResultList.push_back(new VoteResult(parseResult, vote));
				currentVoteCode = "";
			}
		}

		if (list.size() == 0)
		{
			voteResultList.push_back(new VoteResult(MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR, NULL));
		}

		delete safeBuf;
	}

	logger->Debug("End process vote");
}

void SaesEnqueuer::DiscardItem(Smartmatic::System::SafeBuffer * safeBuf)
{
	{
		std::stringstream ss;
		ss << "Fase # 5 : Discard item - size : " << safeBuf->GetSize();
		logger->Debug(ss.str());
	}

	countRecievedData = 0;
	delete safeBuf;
}

void SaesEnqueuer::getVoteResultList(std::list <VoteResult *> & list)
{
	Glib::Mutex::Lock lock(mutex);
	list.clear();

	std::list <VoteResult *>::iterator it;

	for (it = voteResultList.begin();
		 it != voteResultList.end();
		 it++)
	{
		list.push_back((*it));
	}

	voteResultList.clear();
}

VoteResult::VoteResult()
{
	vote = NULL;
}

VoteResult::VoteResult(MachineOperationManager::VoteFromSafeBufferResult result, Vote::Vote * vote)
{
	this->result = result;
	this->vote = vote;
}

VoteResult::~VoteResult()
{
	if (vote)
	{
		delete vote;
		vote = NULL;
	}
}

MachineOperationManager::VoteFromSafeBufferResult VoteResult::getResult()
{
	return result;
}

Smartmatic::SAES::Voting::Vote::Vote * VoteResult::getVote()
{
	return vote;
}

void VoteResult::setResult(MachineOperationManager::VoteFromSafeBufferResult result)
{
	this->result = result;
}

void VoteResult::setVote(Smartmatic::SAES::Voting::Vote::Vote * vote)
{
	this->vote = vote;
}

Smartmatic::Log::ISMTTLog * SaesEnqueuer::getLogger()
{
	return logger;
}
