/*
 * SmartCard.cxx
 *
 *  Created on: 16/08/2011
 *      Author: soto
 */

#include "Configuration/s-a-e-s-common-conf-manager.h"
#include "SmartCard.hxx"
#include "SaesSmartCard.hxx"
#include "Card/SmartcardConnected.h"

using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Exception;

SmartCard::SmartCard()
{
	bool connectedReader =SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getUseConnectedSmartcardReader();
	if(connectedReader)
		smartCard = new SmartcardConnected();
	else
		smartCard = new SaesSmartCard();
}

SmartCard::~SmartCard()
{
	if (smartCard)
	{
		delete smartCard;
	}
}

bool SmartCard::initialize()
{
	return smartCard->initialize();
}

bool SmartCard::isCardPresent()
throw( Smartmatic::System::Exception::CardReaderUnresponsiveException )
{
	return smartCard->isCardPresent();
}

bool SmartCard::read(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException
	  , InvalidCardContentException)
{
	return smartCard->read(buffer, cryptoData);
}

bool SmartCard::write(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	return smartCard->write(buffer, cryptoData);
}

bool SmartCard::test()
{
	return smartCard->test();
}

void SmartCard::dispose()
{
	smartCard->dispose();
}
