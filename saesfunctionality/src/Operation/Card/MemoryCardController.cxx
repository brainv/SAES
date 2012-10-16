/*
 * MemoryCardController.cxx
 *
 *  Created on: 15/08/2011
 *      Author: soto
 */

#include "MemoryCardController.hxx"
#include <Devices/smart-card-reader.h>
#include <Log/SMTTLogManager.h>
#include <Operation/Security/CryptoToken.hxx>

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
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System::Exception;

ISMTTLog* MemoryCardController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.MemoryCardController",GETTEXT_PACKAGE);

MemoryCardController::MemoryCardController()
{

}

MemoryCardController::~MemoryCardController()
{

}

bool MemoryCardController::initialize()
{
	return SmartCardReader::Current()->Initialize();
}

bool MemoryCardController::isCardPresent()
throw( Smartmatic::System::Exception::CardReaderUnresponsiveException )
{
	return SmartCardReader::Current()->getCardPresent();
}

bool MemoryCardController::read(SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
throw ( IOCardException,
	    InvalidCardContentException)
{
	bool validate = true;

	validate = validate && SmartCardReader::Current()->init();
	validate = validate && SmartCardReader::Current()->getConnected();

	std::vector<unsigned char> data;
	buffer.Clear();

	if (validate)
	{
		std::vector<unsigned char> resultSize;
		validate = SmartCardReader::Current()->Read(0,16, resultSize);

		int sizeOfResult = 0;

		if(validate && resultSize.size()>=2)
		{
			sizeOfResult = (resultSize[0] << 8) + (resultSize[1]);
		}

		std::vector<unsigned char> resultCheck;

		if(sizeOfResult < 2048)
		{
			validate = SmartCardReader::Current()->Read(2,sizeOfResult, data);
			validate = validate && data.size() > 0;
		}
	}

	if (!validate)
	{
		logger->Debug("ERROR - read memory card");
	}
	else
	{
		SafeBuffer dataIn(&data[0], data.size());

		if (!cryptoData.decrypto(dataIn, buffer))
		{
			logger->Debug("ERROR - decrypto memory card data");
			validate = false;
		}
	}

	return validate;
}

bool MemoryCardController::write(SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
throw ( IOCardException,
		CardCanNotWriteException,
		InvalidCardContentException)
{
	bool validate = true;

	validate = validate && SmartCardReader::Current()->init();
	validate = validate && SmartCardReader::Current()->getConnected();
	std::vector<unsigned char> bufferWrite;

	if (validate)
	{
		SafeBuffer dataOut;

		if (cryptoData.crypto(buffer, dataOut))
		{
			bufferWrite.assign(&dataOut.GetData()[0], &dataOut.GetData()[0] + dataOut.GetSize());
		}
		else
		{
			logger->Debug("ERROR - decrypto memory card data");
			validate = false;
		}
	}

	if (validate)
	{
		int sizeOfBinarize = bufferWrite.size();
		unsigned char sizeByte1 = sizeOfBinarize & 0x000000ff;
		unsigned char sizeByte2 = (sizeOfBinarize & 0x0000ff00) >> 8;
		std::vector<unsigned char> sizeOfData;
		sizeOfData.push_back (sizeByte2);
		sizeOfData.push_back (sizeByte1);
		validate = validate && SmartCardReader::Current()->Write(0,sizeOfData,0,0);
		validate = validate && SmartCardReader::Current()->Write(2,bufferWrite,0,0);
	}

	if (!validate)
	{
		logger->Debug("ERROR - write memory card");
	}

	return validate;
}

bool MemoryCardController::test()
{
	bool validate = false;

	if (isCardPresent())
	{
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

		if (write(bufferWrite, crypto) &&
			read(bufferRead, crypto))
		{
			validate = bufferWrite == bufferRead;
		}
	}

	return validate;
}

void MemoryCardController::dispose()
{
	SmartCardReader::Current()->Dispose();
}
