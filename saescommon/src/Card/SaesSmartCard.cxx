/**
 * @file SaesSmartCard.cxx
 * @brief Body class smartcard
 * @date 15/08/2011
 * @author Yadickson Soto
 */

#include <sstream>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include "SaesSmartCard.hxx"
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

using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Exception;

ISMTTLog* SaesSmartCard::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Card.SaesSmartCard",GETTEXT_PACKAGE);

SaesSmartCard::SaesSmartCard()
: SmartCardCommand()
{
	initStatus = false;
	countReload = 0;
	doPowerCycle = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSuspendResumeOnErrorCondition();
}

SaesSmartCard::~SaesSmartCard()
{

}

bool SaesSmartCard::initialize()
{
	logger->Debug("Initialize SmartCard");

	if (!initStatus)
	{
		if (establishContext())
		{
			if (searchReaders())
			{
				initStatus = true;
			}
		}

		releaseContext();
	}

	return initStatus;
}

bool SaesSmartCard::isCardPresent()
throw( Smartmatic::System::Exception::CardReaderUnresponsiveException )
{
	bool cardPresent = false;

	if (initStatus)
	{
		if (establishContext())
		{
			switch(connect())
			{
				case INSERT:
					cardPresent = true;
					viewReloadSuccess();
					break;

				case INVALID:
					cardPresent = true;
					viewReloadSuccess();
					break;

				case NOT_INSERT:
					viewReloadSuccess();
					break;

				case READER_NOT_FOUND:
					countReload = 0;
					break;

				case READER_ERROR:
					reloadReader();
					break;
			}

			disconnect();
		}

		releaseContext();
	}

	return cardPresent;
}

bool SaesSmartCard::read(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException
	  , InvalidCardContentException )
{
	logger->Debug("Read SmartCard");

	bool validate = false;
	buffer.Clear();

	if ( ! test() )
		throw IOCardException (
				_("Smartmatic.SAES.Card.SaesSmartCard.UnableReadSmartCard"),
				N_("Smartmatic.SAES.Card.SaesSmartCard.UnableReadSmartCard"),
				logger);

	if (initStatus)
	{
		if (establishContext())
		{
			if (connect() == INSERT &&
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

		releaseContext();
	}

	logger->Debug("End Read");

	return validate;
}

bool SaesSmartCard::write(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
	    InvalidCardContentException)
{
	logger->Debug("Write SmartCard");

	bool validate = false;

	if (initStatus)
	{
		if (buffer.GetSize() == 0)
		{
			validate = true;
		}
		else
		{
			if (establishContext())
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

			releaseContext();
		}
	}

	logger->Debug("End Write");

	return validate;
}

bool SaesSmartCard::test()
{
	bool validate = false;

	if (establishContext())
	{
		validate = connect() == INSERT && selectAID();
		disconnect();
	}

	releaseContext();
	return validate;
}

void SaesSmartCard::dispose()
{
	if (initStatus)
	{
		logger->Debug("Dispose SmartCard");
		initStatus = false;
	}
}

void SaesSmartCard::reloadReader()
{
	countReload++;

	if(doPowerCycle && (countReload > 1 && countReload <= 5))
	{
		std::stringstream ss;
		ss << "SmartCard Reload (" << countReload << ")";
		logger->Debug(ss.str());

		logger->Debug("SmartCard Reload - Before reader power cycle");
		doReaderPowerCycle();
		logger->Debug("SmartCard Reload - After reader power cycle");
	}
}

void SaesSmartCard::viewReloadSuccess()
{
	if (doPowerCycle && countReload != 0)
	{
		std::stringstream ss;
		ss << "SmartCard Reload Success (" << countReload << ")";
		logger->Debug(ss.str());
	}

	countReload = 0;
}
