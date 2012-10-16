/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C)  2011 <>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CardGeneratedListWrapper.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::Log;

ISMTTLog* CardGeneratedListWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Status.CardGeneratedListWrapper", GETTEXT_PACKAGE);

CardGeneratedListWrapper::CardGeneratedListWrapper(CardDataList & cardDataList)
{
	this->cardDataList = cardDataList;
}

CardDataList & CardGeneratedListWrapper::getCardDataListStatus ()
{
    return cardDataList;
}

std::vector<Smartmatic::SAES::Voting::VotingDevice::Card_data*> CardGeneratedListWrapper::GetListOfCardDatas()
{
	std::vector<std::string> cardDatasInString =  GetListInString();
	std::vector<Smartmatic::SAES::Voting::VotingDevice::Card_data*> cardDatas;
	try
	{
		for(unsigned int i= 0;i < cardDatasInString.size();i++)
		{
			string semiFile (cardDatasInString[i]);
			if(!semiFile.empty())
			{
				Card_data* data;
				istringstream ss( semiFile );
				data = new Card_data(*(Smartmatic::SAES::Voting::VotingDevice::parseCard_data(ss,Smartmatic::SAES::Voting::CardDataTypes::Flags::dont_validate )));
				cardDatas.push_back (data);
			}
		}
		
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << e;
        logger->Debug(ss.str());
	}
	catch (...)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__;
        logger->Debug(ss.str());
	}

	return cardDatas;
}

std::vector<std::string> CardGeneratedListWrapper::GetListInString()
{
	std::vector<std::string> listOfCardsGenerated;
	 for(unsigned int i= 0;i < cardDataList.getCardDataGenerated().size();i++)
	{
		std::string out;	
		out.append(cardDataList.getCardDataGenerated()[i].getCardData());
		listOfCardsGenerated.push_back(out);
	}
	return listOfCardsGenerated;
}

void CardGeneratedListWrapper::AppendCard(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData)
{
	stringstream ss;
	serializeCard_data(ss,cardData);
	AppendCardInString(ss.str());
	return;
}

void CardGeneratedListWrapper::AppendCardInString(std::string cardData)
{
	CardDataGenerated *type = new CardDataGenerated();
	type->setCardData (cardData);
	cardDataList.getCardDataGenerated().push_back(*type);
	delete(type);
}
