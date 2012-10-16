/*
 * SmartCardController.hxx
 *
 *  Created on: 15/08/2011
 *      Author: soto
 */

#ifndef _SMARTCARDCOMMAND_HXX_
#define _SMARTCARDCOMMAND_HXX_

#include <vector>
#include <Security/CryptoData.hxx>
#include <Log/ISMTTLog.h>
#include <iostream>
#include <globalplatform.h>
#include <System/Exception/InvalidCardContentException.hxx>
#include <System/Exception/IOCardException.h>
#include <System/Exception/CardCanNotWriteException.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Card
		{
			class SmartCardCommand
			{
			public:

				SmartCardCommand();
				~SmartCardCommand();

			private:

				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				OPGP_CARD_INFO cardInfo;
				OP201_SECURITY_INFO securityInfo201;
				GP211_SECURITY_INFO securityInfo211;

				bool secureChannelEnabled;

				unsigned int platformMode;
				unsigned int protocol;

				unsigned char keySetVersion;
				unsigned char keyIndex;
				unsigned char keyDerivation;

				unsigned int maxDataAPDU;
				unsigned int securityLevel;
				unsigned int securityChannelProtocol;
				unsigned int securityChannelProtocolImpl;

			protected:

				OPGP_CARD_CONTEXT cardContext;
				std::string readerName;
				Smartmatic::System::SafeBuffer aid;
				Smartmatic::System::SafeBuffer globalPIN;

				enum StatusCard
				{
					 INSERT
					,INVALID
					,NOT_INSERT
					,READER_NOT_FOUND
					,READER_ERROR
				};

				bool establishContext();
				bool releaseContext();

				bool searchReaders();

				StatusCard connect();

				bool disconnect();

				bool sendAPDU(Smartmatic::System::SafeBuffer & apdu);
				bool sendAPDU(Smartmatic::System::SafeBuffer & apdu, Smartmatic::System::SafeBuffer & response, bool fillResponse = true);

				bool verifyGlobalPIN()
				throw (Smartmatic::System::Exception::InvalidCardContentException);

				bool setPasswordPIN(Smartmatic::SAES::Security::CryptoData & cryptoData);

				bool verifyPasswordPIN(Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw (Smartmatic::System::Exception::InvalidCardContentException);

				bool setPasswordFile(Smartmatic::SAES::Security::CryptoData & cryptoData);
				bool getPasswordFile(Smartmatic::SAES::Security::CryptoData & cryptoData);

				bool setDataFile(Smartmatic::System::SafeBuffer & buffer)
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool getDataFile(Smartmatic::System::SafeBuffer & buffer);

				bool openSecureChannel();
				void closeSecureChannel();

				bool selectAID()
				throw (Smartmatic::System::Exception::InvalidCardContentException);
				bool selectAID(Smartmatic::System::SafeBuffer & aid)
				throw (Smartmatic::System::Exception::InvalidCardContentException);

				bool open()
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool openWrite(Smartmatic::System::SafeBuffer & buffer)
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool continueWrite(Smartmatic::System::SafeBuffer & buffer)
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool openWriteClose(Smartmatic::System::SafeBuffer & buffer)
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool closeWrite()
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				void abortWrite()
				throw (Smartmatic::System::Exception::CardCanNotWriteException);

				bool openRead(unsigned int & left);
				bool continueRead(Smartmatic::System::SafeBuffer & buffer, unsigned char size, unsigned int & left);

			private:

				void setDerivedGlobalPin();
			};
		}
	}
}

#endif /* _SMARTCARDCOMMAND_HXX_ */
