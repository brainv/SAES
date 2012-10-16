/**
 * @file SmartCardCommand.cxx
 * @brief Body class smartcard command
 * @date 15/08/2011
 * @author Yadickson Soto
 */

#include <sstream>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Security/Encryption.hxx>
#include "SmartCardCommand.hxx"
#include "pcscd/PCSCDManager.hxx"
#include <System/Utils/StringUtils.hxx>
#include <System/ZenityWrapper.hxx>
#include <pcsclite.h>
#include <string.h>
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

#define BUFLEN 1024
#define RECEIVEAPDULEN 261
#define DDES_KEY_LEN 16

#define CLA 0x80

#ifdef SMARTCARD_APPLET_SEC_CHANNEL

#define INS_VERIFY_GLOBAL_PIN 0xF1
#define INS_VERIFY_PASS_PIN 0xF2
#define INS_SET_PASS_PIN 0xF3
#define INS_GET_PASS_PIN 0xF4
#define INS_SET_PASS_FILE 0xF5
#define INS_GET_PASS_FILE 0xF6
#define INS_WRITE 0xF7
#define INS_READ  0xF8

#else

#define INS_VERIFY_GLOBAL_PIN 0x81
#define INS_VERIFY_PASS_PIN 0x82
#define INS_SET_PASS_PIN 0x83
#define INS_GET_PASS_PIN 0x84
#define INS_SET_PASS_FILE 0x85
#define INS_GET_PASS_FILE 0x86
#define INS_WRITE 0x87
#define INS_READ  0x88

#endif

#define P1_NORMAL 0x00
#define P2_NORMAL 0x00

#define P1_OPEN_WRITE_FILE 0x01
#define P1_NORMAL_WRITE_FILE 0x02
#define P1_ABORT_WRITE_FILE 0x03
#define P2_NORMAL_WRITE_FILE 0x00
#define P2_CLOSE_WRITE_FILE 0x01

#define P1_OPEN_READ_FILE 0x01
#define P1_NORMAL_READ_FILE 0x00
#define P2_NORMAL_READ_FILE 0x00
#define LE_GET_LENGTH 0x02

#define GLOBAL_PIN_LEN 0x08
#define STRING_GLOBAL_PIN "3333726314155697"

using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Exception;

ISMTTLog* SmartCardCommand::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Card.SmartCardCommand",GETTEXT_PACKAGE);

SmartCardCommand::SmartCardCommand()
{
	PlatformMode type = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getPlatformMode();

	switch (type)
	{
		case PlatformMode::CONFIGURATION_OP_201:
			platformMode = OP_201;
			break;

		case PlatformMode::CONFIGURATION_GP_211:
			platformMode = GP_211;
			break;
	}

	GlobalPIN globalPinType = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getGlobalPIN();

	switch(globalPinType)
	{
		case GlobalPIN::CONFIGURATION_FIXED:
			StringUtils::stringToBufferHex(STRING_GLOBAL_PIN, globalPIN);
			break;

		case GlobalPIN::CONFIGURATION_DERIVED:  // derived init key
			setDerivedGlobalPin();
			break;
	}

	std::string strAID = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getAppletAID();
	StringUtils::stringToBufferHex(strAID, aid);

	keyIndex = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityKeyIndex();
	keySetVersion = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityKeySetVersion();

	switch(SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityChannelProtocol())
	{
		case SecurityChannelProtocol::CONFIGURATION_SCP01:
			securityChannelProtocol = GP211_SCP01;
			break;

		case SecurityChannelProtocol::CONFIGURATION_SCP02:
			securityChannelProtocol = GP211_SCP02;
			break;

		default:
			securityChannelProtocol = 0x00;
			break;
	}

	switch(SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityChannelProtocolImpl())
	{
		case SecurityChannelProtocolImpl::CONFIGURATION_SCP01_IMPL_I05:
			securityChannelProtocolImpl = GP211_SCP01_IMPL_i05;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP01_IMPL_I15:
			securityChannelProtocolImpl = GP211_SCP01_IMPL_i15;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I04:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i04;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I05:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i05;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I0A:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i0A;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I0B:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i0B;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I14:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i14;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I15:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i15;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I1A:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i1A;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I1B:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i1B;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I44:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i44;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I45:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i45;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I54:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i54;
			break;

		case SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I55:
			securityChannelProtocolImpl = GP211_SCP02_IMPL_i55;
			break;

		default:
			securityChannelProtocolImpl = 0x00;
			break;
	}

	switch(SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityLevel())
	{
		case SecurityLevel::CONFIGURATION_C_MAC:
			securityLevel = (securityChannelProtocol == GP211_SCP01 ? GP211_SCP01_SECURITY_LEVEL_C_MAC : GP211_SCP02_SECURITY_LEVEL_C_MAC);
			maxDataAPDU = 247;
			break;

		case SecurityLevel::CONFIGURATION_C_DEC_C_MAC:
			securityLevel = (securityChannelProtocol == GP211_SCP01 ? GP211_SCP01_SECURITY_LEVEL_C_DEC_C_MAC : GP211_SCP02_SECURITY_LEVEL_C_DEC_C_MAC);
			maxDataAPDU = 239;
			break;

		case SecurityLevel::CONFIGURATION_R_MAC:
			securityLevel = GP211_SCP02_SECURITY_LEVEL_R_MAC;
			maxDataAPDU = 200;
			break;

		case SecurityLevel::CONFIGURATION_C_MAC_R_MAC:
			securityLevel = GP211_SCP02_SECURITY_LEVEL_C_MAC_R_MAC;
			maxDataAPDU = 200;
			break;

		case SecurityLevel::CONFIGURATION_C_DEC_C_MAC_R_MAC:
			securityLevel = GP211_SCP02_SECURITY_LEVEL_C_DEC_C_MAC_R_MAC;
			maxDataAPDU = 200;
			break;

		default:
			break;
	}

	SecurityKeyDerivation derivation = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecurityKeyDerivation();

	switch(derivation)
	{
		case SecurityKeyDerivation::CONFIGURATION_NONE:
			keyDerivation = OPGP_DERIVATION_METHOD_NONE;
			break;

		case SecurityKeyDerivation::CONFIGURATION_VISA2:
			keyDerivation = OPGP_DERIVATION_METHOD_VISA2;
			break;

		case SecurityKeyDerivation::CONFIGURATION_EMVCPS11:
			keyDerivation = OPGP_DERIVATION_METHOD_EMV_CPS11;
			break;
	}

	secureChannelEnabled = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSecureChannelEnabled();

	if (!secureChannelEnabled)
	{
		securityLevel = 0x00;
		maxDataAPDU = 250;
	}

	protocol = OPGP_CARD_PROTOCOL_T0 | OPGP_CARD_PROTOCOL_T1;
}

SmartCardCommand::~SmartCardCommand()
{

}

void SmartCardCommand::setDerivedGlobalPin()
{
	SafeBuffer bufferPIN;
	const SafeBuffer & iv(Encryption::getInstance()->getInitKey());
	globalPIN.Clear();

	Encryption::getInstance()->getComposeKey(iv, bufferPIN, GLOBAL_PIN_LEN);
	globalPIN.AddData(bufferPIN);
}

bool SmartCardCommand::establishContext()
{
	bool validate = true;
	std::string nameLib = "gppcscconnectionplugin";
	std::string nameVersion = "1.0.1";

	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	memcpy (cardContext.libraryName, nameLib.c_str(), nameLib.length()+1);
	memcpy (cardContext.libraryVersion, nameVersion.c_str(), nameVersion.length()+1);

	cardContext.libraryHandle = NULL;
	cardContext.librarySpecific = NULL;

	status = OPGP_establish_context(&cardContext);

	if ( OPGP_ERROR_CHECK ( status ) )
	{
		std::stringstream ss;
		ss << "ERROR - establish context failed, " << (unsigned long)status.errorCode << " error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
		validate = false;

		if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_NO_MEMORY)
		{
			logger->Debug("Not enough memory available to complete this command.");
		}
		else if ((unsigned long)status.errorCode == (unsigned long)SCARD_F_COMM_ERROR)
		{
			logger->Debug("An internal communications error has been detected.");
		}
		else
		{
			logger->Debug("An internal error has been detected, but the source is unknown.");
		}

		if (SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getForceRestartPCSCD())
		{
			if (SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getShowMessageRestartPCSCD())
			{
				ZenityWrapper::showInfo("Restart PCSCD", "Info", 5);
			}

			logger->Debug("Force restart PCSCD");

			PCSCD::PCSCDManager::stop(true);
			sleep(SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getWaitStopPCSCD());
			PCSCD::PCSCDManager::start(true);
			sleep(SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getWaitStartPCSCD());

			logger->Debug("End restart PCSCD");
		}
	}

	return validate;
}

bool SmartCardCommand::releaseContext()
{
	bool validate = true;
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_release_context(&cardContext);

	if ( OPGP_ERROR_CHECK ( status ) )
	{
		std::stringstream ss;
		ss << "ERROR - release context failed, error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
		validate = false;
	}

	return validate;
}

bool SmartCardCommand::searchReaders()
{
	bool validate = false;
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

    char buf[BUFLEN + 1];
    unsigned long readerStrLen = BUFLEN;

	status = OPGP_list_readers (cardContext, buf, &readerStrLen);

	if ( OPGP_ERROR_CHECK ( status ) )
	{
		std::stringstream ss;
		ss << "List readers failed, error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
		readerStrLen = 0;
	}
	else
	{
		readerName.assign(buf, readerStrLen);
		readerName.resize(readerStrLen);
		validate = true;
	}

	return validate;
}

SmartCardCommand::StatusCard SmartCardCommand::connect()
{
	StatusCard endStatus = NOT_INSERT;

	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_card_connect(cardContext, readerName.c_str(), &cardInfo, protocol);

	if ( !OPGP_ERROR_CHECK (status) )
	{
		cardInfo.specVersion = platformMode;
		endStatus = INSERT;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_W_UNPOWERED_CARD)
	{
		endStatus = INVALID;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_NO_SMARTCARD)
	{
		endStatus = NOT_INSERT;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_W_UNRESPONSIVE_CARD)
	{
		logger->Debug("ERROR - card is unresponsive");
		endStatus = NOT_INSERT;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_PROTO_MISMATCH)
	{
		logger->Debug("ERROR - Card protocol mismatch");
		endStatus = NOT_INSERT;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_NO_SERVICE)
	{
		logger->Debug("ERROR - service not available");
		endStatus = NOT_INSERT;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_UNKNOWN_READER)
	{
		logger->Debug("ERROR - reader not found");
		endStatus = READER_NOT_FOUND;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_READER_UNAVAILABLE)
	{
		logger->Debug("ERROR - reader is unavailable");
		endStatus = READER_ERROR;
	}
	else
	{
		std::stringstream ss;
		ss << "ERROR - card connect failed, " << (unsigned long)status.errorCode << " error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
		endStatus = NOT_INSERT;
	}

	return endStatus;
}

bool SmartCardCommand::disconnect()
{
	bool validate = false;

	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_card_disconnect(cardContext, &cardInfo);

	if ( !OPGP_ERROR_CHECK ( status ) )
	{
		validate = true;
	}
	else if ((unsigned long)status.errorCode == (unsigned long)SCARD_E_INVALID_HANDLE)
	{

	}
	else
	{
		std::stringstream ss;
		ss << "ERROR - disconnect failed, " << (unsigned long)status.errorCode << " error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
	}

	return validate;
}

bool SmartCardCommand::sendAPDU(SafeBuffer & apdu)
{
	SafeBuffer response;
	return sendAPDU(apdu, response, false);
}

bool SmartCardCommand::sendAPDU(SafeBuffer & apdu, SafeBuffer & response, bool fillResponse)
{
	bool validate = false;

	unsigned char recvAPDU[RECEIVEAPDULEN + 1];
	unsigned long recvAPDULen = RECEIVEAPDULEN;

	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	if (platformMode == OP_201)
    {
		logger->Debug("sendAPDU OP_201");
        status = OP201_send_APDU(cardContext, cardInfo,
                             (!secureChannelEnabled ? NULL : &securityInfo201),
                             (unsigned char *)apdu.GetData(), apdu.GetSize(),
                             recvAPDU, &recvAPDULen);
    }
    else if (platformMode == GP_211)
    {
    	logger->Debug("sendAPDU GP_211");
        status = GP211_send_APDU(cardContext, cardInfo,
                             (!secureChannelEnabled ? NULL : &securityInfo211),
                             (unsigned char *)apdu.GetData(), apdu.GetSize(),
                             recvAPDU, &recvAPDULen);
    }
    else
    {
    	return false;
    }

    if (OPGP_ERROR_CHECK(status))
    {
		std::stringstream ss;
		ss << "ERROR - send APDU, error message " << status.errorMessage << ".";
		logger->Debug(ss.str());
    }
    else
    {
    	if (fillResponse)
        {
    		 response.AddData((const unsigned char *)recvAPDU, recvAPDULen);
        }
    	validate = true;
    }

    return validate;
}

bool SmartCardCommand::verifyGlobalPIN ()
throw (InvalidCardContentException)
{
	bool validate = false;
	logger->Debug("verifyGlobalPIN");

	SafeBuffer apdu;
	SafeBuffer response;

	apdu.push_back(CLA);
	apdu.push_back(INS_VERIFY_GLOBAL_PIN);
	apdu.push_back(P1_NORMAL);
	apdu.push_back(P2_NORMAL);
	apdu.push_back(globalPIN.GetSize());
	apdu.AddData(globalPIN);
	apdu.push_back(0x01);

	if (sendAPDU(apdu, response))
	{
		if (response.GetSize() == 3)
		{
			validate = response.GetData()[0] == 0x01;
			validate = validate && response.GetData()[1] == 0x90;
			validate = validate && response.GetData()[2] == 0x00;
		}
	}

	if (!validate)
	{
		logger->Debug("Fail verify global PIN");
		throw InvalidCardContentException (
				_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.FailVerifyGlobalPIN"),
				N_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.FailVerifyGlobalPIN"),
				logger);
	}

	return validate;
}

bool SmartCardCommand::verifyPasswordPIN (Smartmatic::SAES::Security::CryptoData & cryptoData)
throw (InvalidCardContentException)
{
	bool validate = false;
	logger->Debug("verifyPasswordPIN");

	SafeBuffer apdu;
	SafeBuffer response;
	const SafeBuffer & pin (cryptoData.getPin());

	apdu.push_back(CLA);
	apdu.push_back(INS_VERIFY_PASS_PIN);
	apdu.push_back(P1_NORMAL);
	apdu.push_back(P2_NORMAL);
	apdu.push_back(PASSWORD_PIN_LEN);
	apdu.AddData(pin);
	apdu.push_back(0x01);

	if (sendAPDU(apdu, response))
	{
		if (response.GetSize() == 3)
		{
			validate = response.GetData()[0] == 0x01;
			validate = validate && response.GetData()[1] == 0x90;
			validate = validate && response.GetData()[2] == 0x00;
		}
	}

	if (!validate)
	{
		logger->Debug("Fail verify password PIN");
		throw InvalidCardContentException (
				_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.FailVerifyPasswordPIN"),
				N_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.FailVerifyPasswordPIN"),
				logger);
	}

	return validate;
}

bool SmartCardCommand::setPasswordPIN(Smartmatic::SAES::Security::CryptoData & cryptoData)
{
	bool validate = false;

	SafeBuffer apdu;
	const SafeBuffer & pin (cryptoData.getPin());

	apdu.push_back(CLA);
	apdu.push_back(INS_SET_PASS_PIN);
	apdu.push_back(P1_NORMAL);
	apdu.push_back(P2_NORMAL);
	apdu.push_back(PASSWORD_PIN_LEN);
	apdu.AddData(pin);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		logger->Debug("Fail set password PIN");
	}

	return validate;
}

bool SmartCardCommand::setPasswordFile(CryptoData & cryptoData)
{
	bool validate = false;

	const SafeBuffer & key (cryptoData.getKey());
	const SafeBuffer & iv (cryptoData.getIV());

	if (key.GetSize() != PASSWORD_FILE_KEY)
	{
		std::stringstream ss;
		ss << "Fail set password file, key size " << key.GetSize();
		ss << " != " << PASSWORD_FILE_KEY;
		logger->Debug(ss.str());
	}
	else if (iv.GetSize() != PASSWORD_FILE_IV)
	{
		std::stringstream ss;
		ss << "Fail set password file, iv size " << iv.GetSize();
		ss << " != " << PASSWORD_FILE_IV;
		logger->Debug(ss.str());
	}
	else
	{
		SafeBuffer apdu;

		apdu.push_back(CLA);
		apdu.push_back(INS_SET_PASS_FILE);
		apdu.push_back(P1_NORMAL);
		apdu.push_back(P2_NORMAL);
		apdu.push_back(PASSWORD_FILE_LEN);
		apdu.AddData(key);
		apdu.AddData(iv);

		validate = sendAPDU(apdu);

		if (!validate)
		{
			logger->Debug("Fail set password file");
		}
	}

	return validate;
}

bool SmartCardCommand::getPasswordFile(CryptoData & cryptoData)
{
	bool validate = false;
	logger->Debug("getPasswordFile");

	SafeBuffer apdu;
	SafeBuffer response;

	apdu.push_back(CLA);
	apdu.push_back(INS_GET_PASS_FILE);
	apdu.push_back(P1_NORMAL);
	apdu.push_back(P2_NORMAL);
	apdu.push_back(PASSWORD_FILE_LEN);

	validate = sendAPDU(apdu, response);

	if (!validate || response.GetSize() != (PASSWORD_FILE_LEN + 2))
	{
		validate = false;
		logger->Debug("Fail get password file");
	}
	else
	{
		SafeBuffer key ((unsigned char*)(response.GetData()), PASSWORD_FILE_KEY);
		SafeBuffer iv ((unsigned char*)(response.GetData() + PASSWORD_FILE_KEY), PASSWORD_FILE_IV);

		cryptoData.setKey(key);
		cryptoData.setIV(iv);
	}

	return validate;
}

bool SmartCardCommand::setDataFile(SafeBuffer & buffer)
throw (CardCanNotWriteException)
{
	bool validate = open();

	if (validate)
	{
		unsigned int leng = buffer.GetSize();

		if (leng > 0)
		{
			unsigned int offset = 0;

			do
			{
				unsigned int size = leng > maxDataAPDU ? maxDataAPDU : leng;
				SafeBuffer temp;
				temp.AddData(buffer.GetData() + offset, size);

				if (!continueWrite(temp))
				{
					validate = false;
					logger->Debug("ERROR - writing file");
					throw CardCanNotWriteException (
							_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile"),
							N_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile"),
							logger);
				}

				leng -= size;
				offset += size;

			}while (leng != 0);

		}

		closeWrite();
	}
	else
	{
		logger->Debug("ERROR - open file");
	}

	return validate;
}

bool SmartCardCommand::getDataFile(SafeBuffer & buffer)
{
	unsigned int leng = 0;
	bool validate = openRead(leng);

	logger->Debug("getDataFile");

	if (validate)
	{
		do
		{
			unsigned int size = leng > maxDataAPDU ? maxDataAPDU : leng;

			if (!continueRead(buffer, size, leng))
			{
				validate = false;
				logger->Debug("ERROR - read file");
				break;
			}

			std::stringstream ss;
			ss << "size : " << size;
			logger->Debug(ss.str());

		} while (leng != 0);

	}
	else
	{
		logger->Debug("ERROR - open read file");
	}

	return validate;
}

bool SmartCardCommand::openSecureChannel()
{
	bool validate = false;
	logger->Debug("openSecureChannel");

	if (secureChannelEnabled)
	{
		OPGP_ERROR_STATUS status;
		OPGP_ERROR_CREATE_NO_ERROR(status);

		unsigned char key[DDES_KEY_LEN] = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f };
		unsigned char encKey[DDES_KEY_LEN] = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f };
		unsigned char macKey[DDES_KEY_LEN] = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f };
		unsigned char kekKey[DDES_KEY_LEN] = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f };

		if (platformMode == OP_201)
		{
			status = OP201_mutual_authentication(cardContext, cardInfo,
						 key,
						 encKey,
						 macKey,
						 kekKey,
						 keySetVersion,
						 keyIndex,
						 securityLevel,
						 keyDerivation,
						 &securityInfo201);
		}
		else if (platformMode == GP_211)
		{
			status = GP211_mutual_authentication(cardContext, cardInfo,
					 key,
					 encKey,
					 macKey,
					 kekKey,
					 keySetVersion,
					 keyIndex,
					 securityChannelProtocol,
					 securityChannelProtocolImpl,
					 securityLevel,
					 keyDerivation,
					 &securityInfo211);
		}

		if (OPGP_ERROR_CHECK(status))
		{
			std::stringstream ss;
			ss << "ERROR - open secure channel, error message " << status.errorMessage << ".";
			logger->Debug(ss.str());
		}
		else
		{
			validate = true;
		}
	}
	else
	{
		logger->Debug("Secure channel disabled");
		validate = true;
	}

	return validate;
}

void SmartCardCommand::closeSecureChannel()
{

}

bool SmartCardCommand::selectAID()
throw (InvalidCardContentException)
{
	return selectAID(aid);
}

bool SmartCardCommand::selectAID(SafeBuffer & aid)
throw (InvalidCardContentException)
{
	bool validate = false;
	logger->Debug("selectAID");

	int count = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getReadRetry();

	do
	{
		count--;

		OPGP_ERROR_STATUS status;
		OPGP_ERROR_CREATE_NO_ERROR(status);

		status = OPGP_select_application (cardContext, cardInfo,
										  (unsigned char *)aid.GetData(), aid.GetSize());
		if (OPGP_ERROR_CHECK(status))
		{
			std::stringstream ss;
			ss << "ERROR - select AID [" + StringUtils::bufferHexToString(aid) + "], error message " << status.errorMessage << ".";
			logger->Debug(ss.str());
		}
		else
		{
			validate = true;
		}

	} while (count > 0);

	if (!validate)
	{
		throw InvalidCardContentException (
				_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.ErrorSelectAID"),
				N_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.ErrorSelectAID"),
				logger);
	}

	return validate;
}

bool SmartCardCommand::open()
throw (CardCanNotWriteException)
{
	bool validate = false;

	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_OPEN_WRITE_FILE);
	apdu.push_back(P2_NORMAL_WRITE_FILE);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		abortWrite();
	}

	return validate;
}

bool SmartCardCommand::openWrite(SafeBuffer & buffer)
throw (CardCanNotWriteException)
{
	bool validate = false;

	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_OPEN_WRITE_FILE);
	apdu.push_back(P2_NORMAL_WRITE_FILE);
	apdu.push_back(buffer.GetSize());
	apdu.AddData(buffer);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		abortWrite();
	}

	return validate;
}

bool SmartCardCommand::continueWrite(SafeBuffer & buffer)
throw (CardCanNotWriteException)
{
	bool validate = false;

	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_NORMAL_WRITE_FILE);
	apdu.push_back(P2_NORMAL_WRITE_FILE);
	apdu.push_back(buffer.GetSize());
	apdu.AddData(buffer);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		abortWrite();
	}

	return validate;
}

bool SmartCardCommand::openWriteClose(SafeBuffer & buffer)
throw (CardCanNotWriteException)
{
	bool validate = false;

	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_OPEN_WRITE_FILE);
	apdu.push_back(P2_CLOSE_WRITE_FILE);
	apdu.push_back(buffer.GetSize());
	apdu.AddData(buffer);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		abortWrite();
	}

	return validate;
}

bool SmartCardCommand::closeWrite()
throw (CardCanNotWriteException)
{
	bool validate = false;

	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_NORMAL_WRITE_FILE);
	apdu.push_back(P2_CLOSE_WRITE_FILE);
	apdu.push_back(0x00);

	validate = sendAPDU(apdu);

	if (!validate)
	{
		abortWrite();
	}

	return validate;
}

void SmartCardCommand::abortWrite ()
throw (CardCanNotWriteException)
{
	SafeBuffer apdu;

	apdu.push_back(CLA);
	apdu.push_back(INS_WRITE);
	apdu.push_back(P1_ABORT_WRITE_FILE);
	apdu.push_back(P2_NORMAL_WRITE_FILE);

	if ( ! sendAPDU(apdu) )
	{
		throw CardCanNotWriteException (
				_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.UnableWriteData"),
				N_("Smartmatic.SAES.Card.SmartCardCommand.ErrorWritingFile.UnableWriteData"),
				logger);
	}
}

bool SmartCardCommand::openRead(unsigned int & left)
{
	bool validate = false;
	left = 0;

	SafeBuffer apdu;
	SafeBuffer response;

	apdu.push_back(CLA);
	apdu.push_back(INS_READ);
	apdu.push_back(P1_OPEN_READ_FILE);
	apdu.push_back(P2_NORMAL_READ_FILE);
	apdu.push_back(LE_GET_LENGTH);

	validate = sendAPDU(apdu, response);

	if (response.GetSize() == 4)
	{
		left = response.GetData()[0];
		left <<= 8;
		left += response.GetData()[1];

		validate = response.GetData()[2] == 0x90;
		validate = validate && response.GetData()[3] == 0x00;
	}
	else
	{
		validate = false;
	}

	return validate;
}

bool SmartCardCommand::continueRead(SafeBuffer & buffer, unsigned char size, unsigned int & left)
{
	bool validate = false;
	left = 0;

	SafeBuffer apdu;
	SafeBuffer response;

	apdu.push_back(CLA);
	apdu.push_back(INS_READ);
	apdu.push_back(P1_NORMAL_READ_FILE);
	apdu.push_back(P2_NORMAL_READ_FILE);
	apdu.push_back(size + 2);   //TWO HEADER

	validate = sendAPDU(apdu, response);

	if (validate && response.GetSize() == (unsigned int)(4 + size))
	{
		left = response.GetData()[0];
		left <<= 8;
		left += response.GetData()[1];

		if (response.GetSize() > 2)
		{
			buffer.AddData(response.GetData() + 2, size);
		}

		validate = response.GetData()[2 + size] == 0x90;
		validate = validate && response.GetData()[3 + size] == 0x00;
	}
	else
	{
		validate = false;
	}

	return validate;
}
