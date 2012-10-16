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
#include <sstream>
#include <glib.h>
#include "System/guid-class.h"
#include <Security/Encryption.hxx>
#include "System/Compression/compression-class.h"
#include "System/Encoding/Base64Encoder.h"
#include "Voting/VotingDevice/card-data-wrapper.h"
#include "Voting/ElectoralConfiguration.hxx"
#include "Configuration/s-a-e-s-conf-manager.h"
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

using namespace Smartmatic::System;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* CardDataWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.VotingDevice.CardDataWrapper",GETTEXT_PACKAGE);

CardDataWrapper::CardDataWrapper()
{
}

CardDataWrapper::~CardDataWrapper()
{
}

void CardDataWrapper::BinarizeCardData(Card_data* cardData, std::vector<unsigned char> & dataOut)
{
	dataOut.clear();

	string cardCode;
	string cardType;
	string cardStatus;
	string lvgCode;
	string lvgCustomCode;
	string lvgNameKey;
	string lvgRegionCode;
	string lvgVBCode; 
	string lvgOMCode;
	string lvgCGC;
	string caCode;
	string caValue;
	
	if(cardData!=NULL)
	{
		//base card data
		cardCode = cardData->getCode ();
		cardType = cardData->getCard_type ();
		cardStatus = cardData->getCard_status();
		//get the lvg data

		lvgCode = cardData->getLogical_voter_group().getCode();
		lvgCustomCode = cardData->getLogical_voter_group().getCustom_code ();
		lvgNameKey = cardData->getLogical_voter_group().getName_key ();
		lvgRegionCode = cardData->getLogical_voter_group().getRegion_code ();
		lvgVBCode= cardData->getLogical_voter_group().getVoting_booth_code (); 
		lvgOMCode = cardData->getLogical_voter_group().getOperation_mode_code ();
		lvgCGC = cardData->getLogical_voter_group().getContest_group_code();

		if(cardData->getLogical_voter_group().getCustom_attributes ().present() && cardData->getLogical_voter_group().getCustom_attributes().get().getCustom_attribute ().size()>0)
		{
			//get the Custom Att data
			caCode = cardData->getLogical_voter_group().getCustom_attributes ().get().getCustom_attribute ()[0].getCode();
			caValue = cardData->getLogical_voter_group().getCustom_attributes ().get().getCustom_attribute ()[0].getValue();
		}
	}

	//binarizing card base data
	std::vector<unsigned char> cardCodeBinarized;
	std::vector<unsigned char> cardTypeBinarized;
	std::vector<unsigned char> cardStatusBinarized;

	BinarizeFieldToNumber(cardCode,40,cardCodeBinarized);
	BinarizeFieldToNumber(cardType,20,cardTypeBinarized);
	BinarizeFieldToNumber(cardStatus,20,cardStatusBinarized);

	//binarizing lvg data
	std::vector<unsigned char> lvgCodeBinarized;
	std::vector<unsigned char> lvgCustomCodeBinarized;
	std::vector<unsigned char> lvgNameKeyBinarized;
	std::vector<unsigned char> lvgRegionCodeBinarized;
	std::vector<unsigned char> lvgVBCodeBinarized;
	std::vector<unsigned char> lvgOMCodeBinarized;
	std::vector<unsigned char> lvgCGCBinarized;

	BinarizeFieldToNumber(lvgCode,5,lvgCodeBinarized);
	BinarizeFieldToNumber(lvgCustomCode,5,lvgCustomCodeBinarized);
	BinarizeFieldToNumber(lvgNameKey,5,lvgNameKeyBinarized);
	BinarizeFieldToNumber(lvgRegionCode,5,lvgRegionCodeBinarized);
	BinarizeFieldToNumber(lvgVBCode,5,lvgVBCodeBinarized);
	BinarizeFieldToNumber(lvgOMCode,5,lvgOMCodeBinarized);
	BinarizeFieldToNumber(lvgCGC,40,lvgCGCBinarized);

	//binarizing Custom Att data
	std::vector<unsigned char> caCodeBinarized;
	std::vector<unsigned char> caValueBinarized;

	BinarizeFieldToNumber(caCode,15,caCodeBinarized);
	BinarizeFieldToNumber(caValue,75,caValueBinarized);

	//constructing complete result(should always be 220 in size)
	//order is
	//1 cardCode
	dataOut.insert(dataOut.end(),cardCodeBinarized.begin(),cardCodeBinarized.end());
	//2 cardType
	dataOut.insert(dataOut.end(),cardTypeBinarized.begin(),cardTypeBinarized.end());
	// *NEW* CardStatus
	dataOut.insert(dataOut.end(),cardStatusBinarized.begin(),cardStatusBinarized.end());
	//3 lvgCode
	dataOut.insert(dataOut.end(),lvgCodeBinarized.begin(),lvgCodeBinarized.end());
	//4 lvgCustomCode
	dataOut.insert(dataOut.end(),lvgCustomCodeBinarized.begin(),lvgCustomCodeBinarized.end());
	//5 lvgNameKey
	dataOut.insert(dataOut.end(),lvgNameKeyBinarized.begin(),lvgNameKeyBinarized.end());
	//6 lvgregionCode
	dataOut.insert(dataOut.end(),lvgRegionCodeBinarized.begin(),lvgRegionCodeBinarized.end());
	//7 lvgVotingBoothCode
	dataOut.insert(dataOut.end(),lvgVBCodeBinarized.begin(),lvgVBCodeBinarized.end());
	//8 lvgOMCode
	dataOut.insert(dataOut.end(),lvgOMCodeBinarized.begin(),lvgOMCodeBinarized.end());
	//9 lvgContestGroupCode
	dataOut.insert(dataOut.end(),lvgCGCBinarized.begin(),lvgCGCBinarized.end());
	//10 lvgCustomAttCode
	dataOut.insert(dataOut.end(),caCodeBinarized.begin(),caCodeBinarized.end());
	//11 lvgCustomAttValue
	dataOut.insert(dataOut.end(),caValueBinarized.begin(),caValueBinarized.end());
}

string CardDataWrapper::FormattedString(std::vector<unsigned char> & binarizeData,int begin, int end)
{
	string tempFormatted;
	for(int i=begin;i<end;i++)
	{
		if(binarizeData[i] == '\x0')
		{
			break;
		}
		tempFormatted.push_back(binarizeData[i]);
	}
	return tempFormatted;
}

Card_data CardDataWrapper::DebinarizeCardData(std::vector<unsigned char> & binarizeData)
{
	Card_data cardData;

	if(binarizeData.size()>=240)
	{
		string cardCode(FormattedString(binarizeData,0,40));
		string cardType(FormattedString(binarizeData,40,60));
		string cardStatus(FormattedString(binarizeData,60,80));
		string lvgCode(FormattedString(binarizeData,80,85));
		string lvgCustomCode(FormattedString(binarizeData,85,90));
		string lvgNameKey(FormattedString(binarizeData,90,95));
		string lvgRegionCode(FormattedString(binarizeData,95,100));
		string lvgVBCode(FormattedString(binarizeData,100,105)); 
		string lvgOMCode(FormattedString(binarizeData,105,110));
		string lvgCGC(FormattedString(binarizeData,110,150));
		string caCode(FormattedString(binarizeData,150,165));
		string caValue(FormattedString(binarizeData,165,240));

		Logical_voter_group clvg;
		Custom_attributes customAtts;
		Custom_attributes::Custom_attributeSequence customAttseq;
		Custom_attribute customAtt;
		
		cardData.setCode (cardCode);
		cardData.setCard_type (cardType);
		cardData.setCard_status(cardStatus);
		clvg.setContest_group_code (lvgCGC);
		clvg.setOperation_mode_code (lvgOMCode);
		clvg.setVoting_booth_code (lvgVBCode);
		clvg.setRegion_code (lvgRegionCode);
		clvg.setName_key(lvgNameKey);
		clvg.setCode (lvgCode);
		clvg.setCustom_code (lvgCustomCode);

		customAtt.setCode(caCode);
		customAtt.setValue(caValue);
		
		customAttseq.push_back(customAtt);
		customAtts.setCustom_attribute (customAttseq);
		clvg.setCustom_attributes (customAtts);
		cardData.setLogical_voter_group (clvg);
		
	}
	else
	{
		Logical_voter_group clvg;
		Custom_attributes customAtts;
		Custom_attributes::Custom_attributeSequence customAttseq;
		Custom_attribute customAtt;
		
		cardData.setCode ("");
		cardData.setCard_type ("");
		cardData.setCard_status ("");
		clvg.setContest_group_code ("");
		clvg.setOperation_mode_code ("");
		clvg.setVoting_booth_code ("");
		clvg.setRegion_code ("");
		clvg.setName_key("");
		clvg.setCode ("");
		clvg.setCustom_code ("");

		customAtt.setCode("");
		customAtt.setValue("");
		
		customAttseq.push_back(customAtt);
		customAtts.setCustom_attribute (customAttseq);
		clvg.setCustom_attributes (customAtts);
		cardData.setLogical_voter_group (clvg);
	}

	return cardData;
}

void CardDataWrapper::BinarizeFieldToNumber(string field,unsigned int sizeOfField, std::vector<unsigned char> & dataOut)
{
	if(field.size()<sizeOfField)
	{
		for(unsigned int i=0;i<(sizeOfField-field.size());i++)
		{
			field.push_back ('\x0');
		}
	}
	
	dataOut.assign(field.begin(), field.begin()+sizeOfField);
}

bool CardDataWrapper::checkIfCardTimeIsValid(std::string toCheck)
{
	if(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getCardValidity()==0)
	{
		return true;
	}
	else
	{
		Glib::TimeVal timeValCreation;
		timeValCreation.assign_from_iso8601 (toCheck);		
		Glib::TimeVal timeValNow;
		timeValNow.assign_current_time ();
		timeValCreation.add_seconds(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getCardValidity());

		if(timeValCreation < timeValNow)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

time_t CardDataWrapper::ChangeToSeconds(char *src_date)
{
	string format = "%Y%m%d%H%M%S";
	char *fmt= (char*)format.c_str(); /* change as needed */
	struct tm tmp_time;
	if(! *src_date) return 0; /* this means an error */
	strptime(src_date, fmt, &tmp_time);
	return mktime(&tmp_time);
}


int CardDataWrapper::CompareDates(time_t a, time_t b)
{
	if(a>b) return 1;
	if(a<b) return (-1);
	return 0;
}

void CardDataWrapper::DeflateCardData(string & dataToDeflate, SafeBuffer & dataOut)
{
	SafeBuffer buffer(dataToDeflate);
	CompressionClass::Deflate(buffer, dataOut);
}

void CardDataWrapper::InflateCardData(SafeBuffer & data, std::string & stringInflate)
{
	stringInflate.clear();

	SafeBuffer bufferInflate;
	CompressionClass::Inflate(data, bufferInflate);

	if (bufferInflate.GetSize() > 0)
	{
		stringInflate.assign((const char*)bufferInflate.GetData(), bufferInflate.GetSize());
		stringInflate.resize(bufferInflate.GetSize());
	}
}

void CardDataWrapper::GenerateCardDataBin(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, vector<Custom_attribute*> attributes, std::vector<unsigned char> & dataOut, Smartmatic::SAES::Voting::VotingDevice::Card_type type )
{
	Card_data* cardData = new Card_data();
	Logical_voter_group* clvg = new Logical_voter_group();
	Card_type* cardType = new Card_type();
	Custom_attributes* customAtts = new Custom_attributes();
    Custom_attributes::Custom_attributeSequence* customAttseq = new  Custom_attributes::Custom_attributeSequence();

	GuidClass guidC = GuidClass::NewGuid();
	cardData->setCode ((std::string)guidC.ToString());
    cardData->setCard_type (type);
	cardData->setCard_status (Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_NOT_USED);
	clvg->setContest_group_code ("");

	Voting_device vd = electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
    std::list <Region_category> & listCategoryRegion (electoralConfiguration->getRegionCategoryList());

	if (listCategoryRegion.size() > 0)
	{
		Region_category category = (*(listCategoryRegion.rbegin()));
		clvg->setRegion_code (category.getRegion().getCode ());
	}
	else
	{
		clvg->setRegion_code ("");
	}

	clvg->setOperation_mode_code (vd.getOperation_modes ().getOperation_mode ()[0].getCode());
	clvg->setVoting_booth_code (vd.getVoting_booths ().getVoting_booth ()[0].getCode());
	for(unsigned int i = 0;i < attributes.size();i++)
	{
		customAttseq->push_back(*(attributes[i]));
	}
	customAtts->setCustom_attribute (*customAttseq);
	clvg->setCustom_attributes (*customAtts);

	clvg->setName_key("");
	clvg->setCode ("");
	clvg->setCustom_code ("");
	cardData->setLogical_voter_group (*clvg);
	stringstream ss;
	serializeCard_data (ss,*cardData);

	BinarizeCardData(cardData, dataOut);

	delete(customAtts);
	delete(customAttseq);
	delete(cardType);
	delete(clvg);
	delete(cardData);
}

void CardDataWrapper::CompressCardData(Card_data & cardData, SafeBuffer & dataOut)
{
	dataOut.Clear();

	try
	{
	    CardDataTypes::NamespaceInfomap mapcd;
	    mapcd[""].name = NAMESPACE_VOTING_VOTINGDEVICE;
	    mapcd[""].schema = "";

		stringstream ss;
		serializeCard_data (ss,cardData, mapcd, "UTF-8", CardDataTypes::Flags::dont_validate);
		string stringData = ss.str();

		DeflateCardData(stringData, dataOut);
	}
	catch (...)
	{
		logger->Debug("FATAL - Error CompressCardData");
	}
}

void CardDataWrapper::DecompressCardData(SafeBuffer & data, Card_data & cardDataOut)
{
	cardDataOut.setCard_type("");

	try
	{
		std::string stringData;
		InflateCardData(data, stringData);

		std::stringstream ss;
		ss << stringData;
		Card_data cardDataCheckTemp(*(parseCard_data(ss,Smartmatic::SAES::Voting::CardDataTypes::Flags::dont_validate )));
		cardDataOut = cardDataCheckTemp;
	}
	catch (...)
	{
		logger->Debug("FATAL - Error DecompressCardData");
	}
}

std::string CardDataWrapper::GetTimeNow()
{
	Glib::TimeVal timeValNow;
	timeValNow.assign_current_time ();
	return timeValNow.as_iso8601();
}

void CardDataWrapper::GenerateCompressedCardData(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, vector<Custom_attribute*> attributes, SafeBuffer & dataOut, Smartmatic::SAES::Voting::VotingDevice::Card_type type, bool isAudio)
throw (Smartmatic::System::Exception::CryptoException, Smartmatic::System::Exception::SignedException)
{
	Card_data* cardData = new Card_data();
	Logical_voter_group* clvg = new Logical_voter_group();
	Card_type* cardType = new Card_type();
	Custom_attributes* customAtts = new Custom_attributes();
    Custom_attributes::Custom_attributeSequence* customAttseq = new  Custom_attributes::Custom_attributeSequence();

	cardData->setCode ("");
	std::string activationCode;
	/////LLAMAR A CLASE DE YADICKSON Y GENERAR CIFRADO A PARTIR DE FECHA
	cardData->setActivation_code(GenerateCypheredActivationCode());
	///////////////////////////////////////////////////////////////////////////////////////	
    cardData->setCard_type (type);
	cardData->setCard_status (Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_NOT_USED);
	cardData->setIsAudio(isAudio);

	Voting_device vd = electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
    std::list <Region_category> & listCategoryRegion (electoralConfiguration->getRegionCategoryList());

	if (listCategoryRegion.size() > 0)
	{
		Region_category category = (*(listCategoryRegion.rbegin()));
		clvg->setRegion_code (category.getRegion().getCode ());
	}
	else
	{
		clvg->setRegion_code ("");
	}

	clvg->setContest_group_code ("");
	clvg->setOperation_mode_code (vd.getOperation_modes ().getOperation_mode ()[0].getCode());
	clvg->setVoting_booth_code (vd.getVoting_booths ().getVoting_booth ()[0].getCode());

	for(unsigned int i = 0;i < attributes.size();i++)
	{
		customAttseq->push_back(*(attributes[i]));
	}

	customAtts->setCustom_attribute (*customAttseq);
	clvg->setCustom_attributes (*customAtts);
	clvg->setName_key("");
	clvg->setCode ("");
	clvg->setCustom_code ("");
	cardData->setLogical_voter_group (*clvg);
	stringstream ss;
	serializeCard_data (ss,*cardData);

	string signedXml = ss.str();
	DeflateCardData(signedXml, dataOut);

	delete(customAtts);
	delete(customAttseq);
	delete(cardType);
	delete(clvg);
	delete(cardData);
}

string CardDataWrapper::GenerateCypheredActivationCode()
throw (Smartmatic::System::Exception::CryptoException)
{
	std::string uncypheredDate = GetTimeNow();

	std::string cypheredDate =
	        Smartmatic::SAES::Security::Encryption::getInstance()->cryptoStringToB64(
	                uncypheredDate,
	                Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);

	return cypheredDate;
}

string CardDataWrapper::GetUncypheredActivationCode(std::string cypheredDate)
throw (Smartmatic::System::Exception::CryptoException)
{
	std::string uncypheredDate =
	        Smartmatic::SAES::Security::Encryption::getInstance()->decryptoB64ToString(
	                cypheredDate,
	                Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY);

	return uncypheredDate;
}

void CardDataWrapper::GenerateCardData(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::vector<Custom_attribute*> attributes, Card_data & cardData, bool cryptoCode, Smartmatic::SAES::Voting::VotingDevice::Card_type type, bool isAudio )
throw (Smartmatic::System::Exception::CryptoException)
{
	Logical_voter_group clvg;
	Card_type cardType;
	Custom_attributes customAtts;
    Custom_attributes::Custom_attributeSequence customAttseq;

    if (cryptoCode)
    {
    	cardData.setActivation_code(GenerateCypheredActivationCode());
    }
    else
    {
    	cardData.setActivation_code("");
    }

	///////////////////////////////////////////////////////////////////////////////////////	
	cardData.setCode ("");
	cardData.setCard_type (type);
	cardData.setCard_status (Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_NOT_USED);
	cardData.setIsAudio(isAudio);
	clvg.setContest_group_code ("");

	Voting_device vd = electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
    std::list <Region_category> & listCategoryRegion (electoralConfiguration->getRegionCategoryList());

	if (listCategoryRegion.size() > 0)
	{
		Region_category category = (*(listCategoryRegion.rbegin()));
		clvg.setRegion_code (category.getRegion().getCode ());
	}
	else
	{
		clvg.setRegion_code ("");
	}

	clvg.setOperation_mode_code (vd.getOperation_modes ().getOperation_mode ()[0].getCode());
	clvg.setVoting_booth_code (vd.getVoting_booths ().getVoting_booth ()[0].getCode());

	for(unsigned int i = 0;i < attributes.size();i++)
	{
		customAttseq.push_back(*(attributes[i]));
	}

	customAtts.setCustom_attribute (customAttseq);
	clvg.setCustom_attributes (customAtts);
	clvg.setName_key("");
	clvg.setCode ("");
	clvg.setCustom_code ("");
	cardData.setLogical_voter_group (clvg);
}
