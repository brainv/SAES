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

#ifndef _CARD_GENERATED_LIST_WRAPPER_H_
#define _CARD_GENERATED_LIST_WRAPPER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <Voting/Status/card-generated-list-schema.hxx>
#include <Voting/VotingDevice/card-data-schema.hxx>

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
          namespace Status
          {
				/**
				 * @brief	Card generated list wrapper. 
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				class CardGeneratedListWrapper
				{
				public:
						
					//void Initialize(std::string filePath);

					/**
					 * @brief	Gets the list in string.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The list in string.
					 */

					std::vector<std::string> GetListInString();

					/**
					 * @brief	Gets the list of card datas.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the list of card datas.
					 */

					std::vector<Smartmatic::SAES::Voting::VotingDevice::Card_data*> GetListOfCardDatas();

					/**
					 * @brief	Appends a card.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	cardData	Information describing the card.
					 */

					void AppendCard(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData);

					/**
					 * @brief	Appends a card in string.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	cardData	Information describing the card.
					 */

					void AppendCardInString(std::string cardData);
					//void SaveFile();

					/**
					 * @brief	Gets the card data list status.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The card data list status.
					 */

					CardDataList & getCardDataListStatus ();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	cardDataList	List of card data.
					 */

					CardGeneratedListWrapper(CardDataList & cardDataList);
				protected:

				private:	
					Smartmatic::SAES::Voting::Status::CardDataList cardDataList;	///< List of card data
				    std::string filePath;   ///< Full pathname of the file
				    static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
		  }
	  }
	}
}

#endif // _CARD_GENERATED_LIST_WRAPPER_H_
