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

#ifndef _CARD_DATA_WRAPPER_H_
#define _CARD_DATA_WRAPPER_H_
#include <time.h>
#include <Voting/VotingDevice/card-data-schema.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/SafeBuffer.h>
#include <Voting/ElectoralConfiguration.hxx>

namespace Smartmatic
{
    namespace Log
    {
        /**
         * @brief	SMTT Log interface. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class ISMTTLog;
    }

   namespace SAES
   {
      namespace Voting
      {
         namespace VotingDevice
         {
			/**
			 * @brief	Card data wrapper. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class CardDataWrapper
			{
			public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					CardDataWrapper();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~CardDataWrapper();

                    /**
                     * @brief	Generates a card data bin.
                     *
                     * @author	Eduardo.campione
                     * @date	28/04/2011
                     *
                     * @param [in,out]	vd		  	The vd.
                     * @param [in,out]	attributes	If non-null, the attributes.
                     * @param	type			  	The type.
                     *
                     * @return	The card data bin.
                     */

                    static void GenerateCardDataBin(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::vector<Custom_attribute*> attributes, std::vector<unsigned char> & dataOut, Smartmatic::SAES::Voting::VotingDevice::Card_type type = Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD);

                    /**
                     * @brief	Generates a card data.
                     *
                     * @author	Eduardo.campione
                     * @date	28/04/2011
                     *
                     * @param [in,out]	vd		  	The vd.
                     * @param [in,out]	attributes	If non-null, the attributes.
                     * @param cryptoCode crypto code
                     * @param cardDataOut result card data.
                     * @param isAudio is card audio
                     * @return	The card data.
                     */

                    static void GenerateCardData(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::vector<Custom_attribute*> attributes, Card_data & cardDataOut, bool cryptoCode, Smartmatic::SAES::Voting::VotingDevice::Card_type type, bool isAudio = false)throw (Smartmatic::System::Exception::CryptoException);

					/**
					 * @brief	Generates a compressed card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	vd		  	The vd.
					 * @param [in,out]	attributes	If non-null, the attributes.
					 * @param	type			  	The type.
					 *
					 * @return	The compressed card data.
					 */

					static void GenerateCompressedCardData(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::vector<Custom_attribute*> attributes, Smartmatic::System::SafeBuffer & dataOut, Smartmatic::SAES::Voting::VotingDevice::Card_type type = Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD, bool isAudio = false) throw (Smartmatic::System::Exception::CryptoException, Smartmatic::System::Exception::SignedException);

					/**
					 * @brief	Compress card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	cardData	If non-null, information describing the card.
					 *
					 * @return	The compressed card data
					 */

					static void CompressCardData(Card_data & cardData, Smartmatic::System::SafeBuffer & dataout);

					/**
					 * @brief	Decompress card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	cardData	If non-null, information describing the card.
					 *
					 * @return	The compressed card data
					 */

					static void DecompressCardData(Smartmatic::System::SafeBuffer & data, Card_data & cardDataOut);

					/**
					 * @brief	Deflate card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	toDeflate	to deflate.
					 *
					 * @return	.The card data Deflated
					 */

					static void DeflateCardData(std::string & toDeflate, Smartmatic::System::SafeBuffer & dataOut);

					/**
					 * @brief	Inflate card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	data
					 *
					 * @return	.The card data inflated
					 */

					static void InflateCardData(Smartmatic::System::SafeBuffer & data, std::string & stringInflate);

					/**
					 * @brief	Binarize card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	cardData	If non-null, information describing the card.
					 *
					 * @return	The data binarized
					 */

					static void BinarizeCardData(Card_data* cardData, std::vector<unsigned char> & dataOut);

					/**
					 * @brief	Debinarize card data.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	binarizeData	Information describing the binarize.
					 *
					 * @return	The card data
					 */

					static Card_data DebinarizeCardData(std::vector<unsigned char> & binarizeData);


					static bool checkIfCardTimeIsValid(std::string toCheck);

					/**
					 * @brief	Generates a cyphered activation code.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The cyphered activation code.
					 */

					static std::string GenerateCypheredActivationCode() throw (Smartmatic::System::Exception::CryptoException);

					/**
					 * @brief	Gets a uncyphered activation code.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	cypheredDate	Date of the cyphered.
					 *
					 * @return	The uncyphered activation code.
					 */

					static std::string GetUncypheredActivationCode(std::string cypheredDate) throw (Smartmatic::System::Exception::CryptoException);

					/**
					 * @brief	Gets the time now.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The time now.
					 */

					static std::string GetTimeNow();
			protected:

			private:					

					/**
					 * @brief	Change to seconds.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	src_date	If non-null, date of the source.
					 *
					 * @return	The time in seconds
					 */

					static time_t ChangeToSeconds(char *src_date);

					/**
					 * @brief	Compare dates.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	a	a.
					 * @param	b	The.
					 *
					 * @return	1 if the dates are the same , 0 is not
					 */

					static int CompareDates(time_t a, time_t b);

					/**
					 * @brief	Formatted string.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	binarizeData	Information describing the binarize.
					 * @param	begin			The begin.
					 * @param	end				The end.
					 *
					 * @return	The string formatted
					 */

					static std::string FormattedString(std::vector<unsigned char> & binarizeData,int begin, int end);

				    /**
				     * @brief	Binarize field to number.
				     *
				     * @author	Eduardo.campione
				     * @date	28/04/2011
				     *
				     * @param	field	   	The field.
				     * @param	sizeOfField	Size of the field.
				     *
				     * @return	The file binarized into a number
				     */

				    static void BinarizeFieldToNumber(std::string field,unsigned int sizeOfField, std::vector<unsigned char> & dataOut);
				    static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		 }
	  }
   }
}

#endif // _CARD_DATA_WRAPPER_H_
