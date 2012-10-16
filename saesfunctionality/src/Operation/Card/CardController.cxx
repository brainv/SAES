/**
 * @file CardController.cxx
 * @brief Body class card controller
 * @date 15/08/2011
 * @author Yadickson Soto
 */

#include "CardController.hxx"
#include "MemoryCardController.hxx"
#include "SmartCardController.hxx"
#include <System/SafeBuffer.h>
#include <Security/Encryption.hxx>
#include <Voting/VotingDevice/card-data-wrapper.h>
#include <Voting/VotingDevice/ContingencyCardDataWrapper.hxx>
#include <Operation/Security/CryptoMemoryCard.hxx>
#include <Operation/Security/CryptoSmartCard.hxx>
#include <Operation/Security/CryptoContingencyMemoryCard.hxx>
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include <Log/ISMTTLog.h>
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

using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Exception;

ISMTTLog* CardController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.CardController",GETTEXT_PACKAGE);
CardController * CardController::instance = NULL;

CardController::CardController()
{
	interface = NULL;
	cryptoCardData = NULL;

	switch(SAESFunctionalityConfigurationManager::Current()->getCardTypeController())
	{
		case CardTypeController::CONFIGURATION_SMART_CARD:
			interface = new SmartCardController();
			cryptoCardData = new CryptoSmartCard();
			cryptoContingencyCard = new CryptoSmartCard();
			break;

		case CardTypeController::CONFIGURATION_MEMORY_CARD:
			interface = new MemoryCardController();
			cryptoCardData = new CryptoMemoryCard();
			cryptoContingencyCard = new CryptoContingencyMemoryCard();
			break;
	}
}

CardController::~CardController()
{
	if (interface)
	{
		delete interface;
		interface = NULL;
	}

	if (cryptoCardData)
	{
		delete cryptoCardData;
		cryptoCardData = NULL;
	}
}

bool CardController::initialize()
{
	return interface->initialize();
}

bool CardController::isCardPresent()
throw( Smartmatic::System::Exception::CardReaderUnresponsiveException )
{
	Glib::Mutex::Lock lock(mutex);
	return interface->isCardPresent();
}

bool CardController::read(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
	    InvalidCardContentException)
{
	return interface->read(buffer, cryptoData);
}

bool CardController::write(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	return interface->write(buffer, cryptoData);
}

bool CardController::test()
{
	bool validate = false;

	try
	{
		validate = interface->test();
	}
	catch(...)
	{
		logger->Debug("ERROR - test");
	}

	return validate;
}

void CardController::dispose()
{
	interface->dispose();
}

bool CardController::readCardData (Card_data & cardData)
throw ( IOCardException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;
	SafeBuffer buffer;

	cryptoCardData->getKeyPin();

	if (read(buffer, *cryptoCardData))
	{
		CardDataWrapper::DecompressCardData(buffer, cardData);
		validate = ! cardData.getCard_type().empty();
	}
	else
	{
		logger->Debug("ERROR - read card data");
	}

	return validate;
}

bool CardController::writeCardData(Card_data & cardData)
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;

	SafeBuffer buffer;
	SafeBuffer bufferRead;

	CardDataWrapper::CompressCardData(cardData, buffer);

	cryptoCardData->getKeys();
	cryptoCardData->getKeyPin();

	if (write(buffer, *cryptoCardData))
	{
		if (read(bufferRead, *cryptoCardData))
		{
			validate = buffer == bufferRead;
		}
		else
		{
			logger->Debug("ERROR - read card data");
		}
	}
	else
	{
		logger->Debug("ERROR - write card data");
	}

	return validate;
}

bool CardController::readContingencyCardData(ContingencyCardData & cardData, std::string & strPin)
throw ( IOCardException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;

	SafeBuffer buffer;

	cryptoContingencyCard->setKeyPin(strPin);

	if (read(buffer, *cryptoContingencyCard))
	{
		validate = ContingencyCardDataWrapper::bufferToCardData(buffer, cardData);
	}
	else
	{
		logger->Debug("ERROR - read contingency card data");
	}

	return validate;
}

bool CardController::writeContingencyCardData(ContingencyCardData & cardData, std::string & strPin)
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;

	SafeBuffer buffer;
	SafeBuffer bufferRead;
	ContingencyCardDataWrapper::cardDataToBuffer(cardData, buffer);

	cryptoContingencyCard->setKeyPin(strPin);
	cryptoContingencyCard->getKeys();

	if (write(buffer, *cryptoContingencyCard))
	{
		if (read(bufferRead, *cryptoContingencyCard))
		{
			validate = buffer == bufferRead;
		}
		else
		{
			logger->Debug("ERROR - read contingency card data");
		}
	}
	else
	{
		logger->Debug("ERROR - write contingency card data");
	}

	return validate;
}

bool CardController::readToken(std::string & password)
throw ( IOCardException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;
	SafeBuffer buffer;

	if (read(buffer, cryptoToken) && buffer.GetSize() > 0)
	{
		password.assign((const char *)buffer.GetData(), buffer.GetSize());
		password.resize(buffer.GetSize());
		validate = true;
	}

	return validate;
}

bool CardController::writeToken()
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	Glib::Mutex::Lock lock(mutex);

	bool validate = false;

	std::string passphrase = Encryption::getInstance()->getSecretKey().getPlainPassphrase();

	SafeBuffer buffer;
	SafeBuffer bufferRead;
	buffer.AddData((const unsigned char*)passphrase.c_str(), passphrase.length());

	if (write(buffer, cryptoToken) && read(bufferRead, cryptoToken))
	{
		validate = buffer == bufferRead;
	}

	return validate;
}

CardController * CardController::getInstance()
{
	if (instance == NULL)
	{
		instance = new CardController();
	}

	return instance;
}
