/*
 * SmartcardConnected.cpp
 *
 *  Created on: Sep 1, 2011
 *      Author: fgomez
 */

#include <sstream>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include "SmartcardConnected.h"
#include <Log/SMTTLogManager.h>
#include <PCSC/pcsclite.h>
#include <PCSC/winscard.h>

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

using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Exception;

ISMTTLog* SmartcardConnected::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Card.SmartcardConnected",GETTEXT_PACKAGE);

#define GET_SCARDCONTEXT(context) ((PCSC_CARD_CONTEXT_SPECIFIC *)(context.librarySpecific))->cardContext

/**
 * PC/SC specific context information. Used in OPGP_CARD_CONTEXT.librarySpecific.
 */
typedef struct
{
	SCARDCONTEXT cardContext; //!<  Reference to the reader resource manager.
} PCSC_CARD_CONTEXT_SPECIFIC;


SmartcardConnected::SmartcardConnected()
: SmartCardCommand()
{
	countLogger = 0;
	counterError = 0;
  powerCycleTryCount = 0;
	initStatus = false;

	renewContext = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getConnectedReaderRenewContext();
	checkCardUsingPCSC = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getConnectedSmartcardPCSCCheckCard();
	connectToCheckPresence = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getConnectedSmartcardConnectToCheckPresence();

	startPCSCConnection();
}

SmartcardConnected::~SmartcardConnected()
{
	finalizePCSCConnection();
}

void SmartcardConnected::finalizePCSCConnection()
{
	if (initStatus)
	{
		logger->Debug("SmartcardConnected: Finalize PCSC Context");
		releaseContext();
		readerName = "";
		initStatus = false;
	}
}

void SmartcardConnected::startPCSCConnection()
{
	if(initStatus == false)
	{
		logger->Debug("SmartcardConnected: Initialize PCSC Context");
		if (establishContext())
		{
			if (searchReaders())
			{
				initStatus = true;
			}
		}
		else
		{
			releaseContext();
		}
	}
	else
	{
		logger->Debug("SmartcardConnected: Context already initialized");
	}
}

bool SmartcardConnected::initialize()
{
	startPCSCConnection();
	return initStatus;
}

bool SmartcardConnected::checkCardPCSC()
throw( CardReaderUnresponsiveException )
{

	SCARDCONTEXT hContext = GET_SCARDCONTEXT(cardContext);
	SCARD_READERSTATE rgReaderStates;
	rgReaderStates.szReader = readerName.c_str();
	rgReaderStates.dwCurrentState = SCARD_STATE_UNAWARE;
	rgReaderStates.dwEventState = 0;

	//get the context from the connection plugin
	unsigned int retVal = SCardGetStatusChange(hContext, 500, &rgReaderStates, 1);

  xsd::cxx::tree::sequence<Smartmatic::SAES::Common::Configuration::SmartCardErrorCode, false> errorCodes = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getFatalErrorCodes();

  for(unsigned int i=0; i<errorCodes.size(); ++i)
  {
    if(retVal == errorCodes[i])
      throw CardReaderUnresponsiveException(
				_("Smartmatic.SAES.Card.SmartcardConnected.CardReaderUnresponsive"),
				N_("Smartmatic.SAES.Card.SmartcardConnected.CardReaderUnresponsive"),
				logger);
  }

	if(retVal == (unsigned int)SCARD_E_INVALID_VALUE)
	{
		logger->Debug("CheckCardUsingPCSC: SCARD_E_INVALID_VALUE");
	}
	else if(retVal == (unsigned int)SCARD_E_INVALID_HANDLE)
	{
		logger->Debug("CheckCardUsingPCSC: SCARD_E_INVALID_HANDLE");
		//a test has pointed that if the pcscd is reinitialize the handle become invalid
		//so the class should close the context and open other again

		//setting initStatus to false will allow a operative recovery by going to the diagnostic of the smartcard.
		//if it is encounter as a feasible solution can later be done by code.
		initStatus = false;

	}
	else if (retVal == (unsigned int)SCARD_E_READER_UNAVAILABLE)
	{
		logger->Debug("CheckCardUsingPCSC: SCARD_E_READER_UNAVAILABLE");
	}
	else if (!(rgReaderStates.dwEventState & 0x10) && !(rgReaderStates.dwEventState & 0x20))
	{
		{
			std::stringstream msg;
			msg << "CheckCardUsingPCSC: retVal = " << retVal;
			logger->Debug(msg.str());
		}

		{
			std::stringstream msg;
			msg << "CheckCardUsingPCSC: eventstate = " << rgReaderStates.dwEventState;
			logger->Debug(msg.str());
		}
	}

	// SCARD_STATE_CHANGED = 0x02
	// SCARD_STATE_UNKNOWN = 0x04
	// SCARD_STATE_UNAVAILABLE = 0x08
	// sum is 14 or 0x0E (this happens when the card is turned off by software and does not turn on again)
	// sum is 10 or 0x0A (this was verified after the replicate the issue)
	if(rgReaderStates.dwEventState == ( 14)  || //SCARD_STATE_CHANGED | SCARD_STATE_UNKNOWN | SCARD_STATE_UNAVAILABLE
	rgReaderStates.dwEventState == (10) ) //  SCARD_STATE_CHANGED | SCARD_STATE_UNAVAILABLE
	{
		logger->Debug("Smartcard Reader Error condition");
		bool doPowerCycle = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSuspendResumeOnErrorCondition();
    unsigned int powerCycleMaxTries = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getPowerCycleTries();
    if( powerCycleTryCount >= powerCycleMaxTries )
    {
      throw CardReaderUnresponsiveException(
				_("Smartmatic.SAES.Card.SmartcardConnected.CardReaderUnresponsive"),
				N_("Smartmatic.SAES.Card.SmartcardConnected.CardReaderUnresponsive"),
				logger);
    }
		if(doPowerCycle)
		{
			if (counterError > 10)
			{
				logger->Debug("Before smartcard reader power cycle");
				doReaderPowerCycle();
        powerCycleTryCount++;
				logger->Debug("After smartcard reader power cycle");
				counterError = 0;
			}			
			counterError++;
		}
	}
	else
	{
    powerCycleTryCount=0;
		counterError = 0;
	}
	
	if(rgReaderStates.dwEventState & 0x10)
	{
		return false;
	}
	else if(rgReaderStates.dwEventState & 0x20)
	{
		return true;
	}

	
	
	return false;
}

bool SmartcardConnected::isCardPresent() 
throw( CardReaderUnresponsiveException )
{
	if (countLogger % 80 == 0)
	{
		logger->Debug("is Card Present");
	}

	bool cardPresent = false;

	if (initStatus)
	{
		bool tryConnect = true;
		if(checkCardUsingPCSC)
		{
			//ask as done in 
      tryConnect =checkCardPCSC();
			cardPresent = tryConnect;

			if (countLogger % 80 == 0)
			{
				logger->Debug("CheckCardUsingPCSC: " + std::string(cardPresent ? "Card inserted" : "Card not inserted"));
			}
		}

		if(tryConnect && connectToCheckPresence)
		{
			switch(connect())
			{
				case INSERT:
					cardPresent = true;
					logger->Debug("SmartcardConnected: Card inserted id valid");
					break;

				case INVALID:
					cardPresent = false;
					logger->Debug("SmartcardConnected: Card inserted is not valid");
					break;

				case NOT_INSERT:
					if (countLogger % 80 == 0)
					{
						logger->Debug("SmartcardConnected: Card not inserted after connect");
					}
					break;
				case READER_NOT_FOUND:
					break;

				case READER_ERROR:
					break;
			}
			disconnect();
		}
	}

	countLogger++;
	return cardPresent;
}

bool SmartcardConnected::read(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
	    InvalidCardContentException)
{
	logger->Debug("Reading Card");

	bool validate = false;
	buffer.Clear();

	if ( ! test() )
		throw IOCardException (
				_("Smartmatic.SAES.Card.SmartcardConnected.UnableReadSmartCard"),
				N_("Smartmatic.SAES.Card.SmartcardConnected.UnableReadSmartCard"),
				logger);

	if (initStatus)
	{

		if ( ( connect() == INSERT ) &&
			selectAID() &&
			openSecureChannel() &&
			verifyGlobalPIN())
		{
			validate = verifyPasswordPIN(cryptoData) &&
			   getPasswordFile(cryptoData) &&
			   getDataFile(buffer);
		}

		closeSecureChannel();
		disconnect();
	}

	return validate;
}

bool SmartcardConnected::write(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
		InvalidCardContentException)
{
	logger->Debug("Writing Card");

	bool validate = false;

	if (initStatus)
	{
		if (buffer.GetSize() == 0)
		{
			validate = true;
		}
		else
		{
			if (connect() == INSERT &&
				selectAID() &&
				openSecureChannel() &&
				verifyGlobalPIN())
			{
				validate = setPasswordPIN(cryptoData) &&
				   verifyPasswordPIN(cryptoData) &&
				   setPasswordFile(cryptoData) &&
				   setDataFile(buffer);
			}

			closeSecureChannel();
			disconnect();
		}
	}

	return validate;
}

bool SmartcardConnected::test()
{
	logger->Debug("Testing Card");

	connect();

	bool validate = selectAID();

	disconnect();

	return validate;
}

void SmartcardConnected::dispose()
{
	if(renewContext)
	{
		finalizePCSCConnection();
	}
}
