/*
 * ContingencyCardDataWrapper.cxx
 *
 *  Created on: 16/10/2011
 *      Author: soto
 */

#include "ContingencyCardDataWrapper.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/Compression/compression-class.h>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::VotingDevice;

ISMTTLog* ContingencyCardDataWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.VotingDevice.ContingencyCardDataWrapper",GETTEXT_PACKAGE);

ContingencyCardDataWrapper::ContingencyCardDataWrapper()
{

}

ContingencyCardDataWrapper::~ContingencyCardDataWrapper()
{

}

bool ContingencyCardDataWrapper::cardDataToString(
		ContingencyCardData & cardData,
		std::string & dataOut)
{
	bool validate = false;
    std::ostringstream str;
    dataOut.clear();

    ContingencyCardDataTypes::NamespaceInfomap mapv;
    mapv[""].name = NAMESPACE_VOTING_VOTINGDEVICE;
    mapv[""].schema = "";

    try
    {
        serializeContingencyCardData(str, cardData, mapv, "UTF-8", ContingencyCardDataTypes::Flags::dont_validate);
        dataOut = str.str();
        validate = true;
    }
    catch (...)
    {
    	logger->Debug("ERROR - cardDataToString");
    }

	return validate;
}

bool ContingencyCardDataWrapper::stringToCardData(
		std::string & data,
		ContingencyCardData & cardDataOut)
{
	bool validate = false;

	cardDataOut.setPollingPlace("");
	cardDataOut.setPassphrase("");
	cardDataOut.setOpeningCode("");

	try
	{
		std::istringstream istr (data);
		cardDataOut = (*(parseContingencyCardData(istr, ContingencyCardDataTypes::Flags::dont_validate)));
		validate = true;
	}
	catch(...)
	{
		logger->Debug("ERROR - stringToCardData");
	}

	return validate;

}

bool ContingencyCardDataWrapper::cardDataToBuffer(
		ContingencyCardData & cardData,
		SafeBuffer & bufferOut)
{
	bool validate;

	std::string strData;

	validate = cardDataToString(cardData, strData);

	if (validate)
	{
		SafeBuffer buffer(strData);
		CompressionClass::Deflate(buffer, bufferOut);
		validate = bufferOut.GetSize() > 0;
	}

	return validate;
}

bool ContingencyCardDataWrapper::bufferToCardData(
		SafeBuffer & buffer,
		ContingencyCardData & cardDataOut)
{
	bool validate = false;

	SafeBuffer bufferInflate;
	CompressionClass::Inflate(buffer, bufferInflate);

	if (bufferInflate.GetSize() > 0)
	{
		std::string strData;
		strData.assign((const char *)bufferInflate.GetData(), bufferInflate.GetSize());
		strData.resize(bufferInflate.GetSize());

		validate = stringToCardData(strData, cardDataOut);
	}

	return validate;
}
