/**
 * @file SmartCardController.cxx
 * @brief Body class smartcard controller
 * @date 16/08/2011
 * @author Yadickson Soto
 */

#include "SmartCardController.hxx"
#include <Operation/Security/CryptoSmartCard.hxx>
#include <Operation/Security/CryptoToken.hxx>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>

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
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System::Exception;

ISMTTLog* SmartCardController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.SmartCardController",GETTEXT_PACKAGE);

SmartCardController::SmartCardController()
{

}

SmartCardController::~SmartCardController()
{

}

bool SmartCardController::initialize()
{
	return smartCard.initialize();
}

bool SmartCardController::isCardPresent() 
throw( CardReaderUnresponsiveException )
{
	return smartCard.isCardPresent();
}

bool SmartCardController::read(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
	    InvalidCardContentException)
{
	bool validate = smartCard.read(buffer, cryptoData);

	if (validate && buffer.GetSize() > 0)
	{
		SafeBuffer dataOut;

		if (cryptoData.decrypto(buffer, dataOut))
		{
			buffer.Clear();
			buffer.AddData(dataOut);
		}
		else
		{
			logger->Debug("ERROR - decrypto smart card data");
			buffer.Clear();
			validate = false;
		}
	}
	else
	{
		validate = false;
		buffer.Clear();
	}

	return validate;
}

bool SmartCardController::write(SafeBuffer & buffer, CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
		InvalidCardContentException)
{
	bool validate = false;
	SafeBuffer bufferWrite;

	if (buffer.GetSize() > 0)
	{
		if (cryptoData.crypto(buffer, bufferWrite))
		{
			validate = smartCard.write(bufferWrite, cryptoData);
		}
		else
		{
			logger->Debug("ERROR - decrypto memory card data");
		}
	}

	return validate;
}

bool SmartCardController::test()
{
	bool validate = false;

	if (isCardPresent())
	{
		SmartCardConfiguration::NivelTestSequence & seq ( SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getNivelTest() );
		SmartCardConfiguration::NivelTestIterator it;

		for (it = seq.begin();
			 it != seq.end();
			 it++)
		{
			switch(*it)
			{
				case NivelTestConfig::CONFIGURATION_SIMPLE_SELECT_APPLET:
					validate = testSelect();
					break;

				case NivelTestConfig::CONFIGURATION_SIMPLE_WRITE_READ:
					validate = testWriteRead();
					break;
			}

			if (!validate)
			{
				break;
			}
		}
	}

	return validate;
}

void SmartCardController::dispose()
{
	smartCard.dispose();
}


bool SmartCardController::testSelect()
{
	bool validate = smartCard.test();
	std::stringstream ss;
	ss << "Simple select test " << (validate ? "success": "fail");
	logger->Debug(ss.str());
	return validate;
}

bool SmartCardController::testWriteRead()
{
	bool validate = false;

	SafeBuffer bufferWrite;
	SafeBuffer bufferRead;

	bufferWrite.push_back(0x31);
	bufferWrite.push_back(0x32);
	bufferWrite.push_back(0x33);
	bufferWrite.push_back(0x34);
	bufferWrite.push_back(0x35);
	bufferWrite.push_back(0x36);
	bufferWrite.push_back(0x37);
	bufferWrite.push_back(0x38);

	CryptoToken crypto;

	if (write(bufferWrite, crypto) && read(bufferRead, crypto))
	{
		validate = bufferWrite == bufferRead;
	}

	std::stringstream ss;
	ss << "Simple write read test " << (validate ? "success": "fail");
	logger->Debug(ss.str());

	return validate;
}
