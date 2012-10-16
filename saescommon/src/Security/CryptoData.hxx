/*
 * CryptoData.hxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#ifndef CRYPTODATA_HXX_
#define CRYPTODATA_HXX_

#include <System/SafeBuffer.h>

#define PASSWORD_PIN_LEN 0x08
#define PASSWORD_FILE_LEN 0x30
#define PASSWORD_FILE_KEY 0x20
#define PASSWORD_FILE_IV 0x10

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Security
		{
			class CryptoData
			{
			public:

				CryptoData();
				CryptoData(
						Smartmatic::System::SafeBuffer & pin,
						Smartmatic::System::SafeBuffer & key,
						Smartmatic::System::SafeBuffer & iv);

				virtual ~CryptoData();

				virtual bool crypto(
						Smartmatic::System::SafeBuffer & dataIn,
						Smartmatic::System::SafeBuffer & dataOut);

				virtual bool decrypto(
						Smartmatic::System::SafeBuffer & dataIn,
						Smartmatic::System::SafeBuffer & dataOut);

				const Smartmatic::System::SafeBuffer & getPin();
				const Smartmatic::System::SafeBuffer & getKey();
				const Smartmatic::System::SafeBuffer & getIV();

				void setPin(Smartmatic::System::SafeBuffer & pin);
				void setKey(Smartmatic::System::SafeBuffer & key);
				void setIV(Smartmatic::System::SafeBuffer & iv);

			private:

				Smartmatic::System::SafeBuffer pin;
				Smartmatic::System::SafeBuffer key;
				Smartmatic::System::SafeBuffer iv;
				static Smartmatic::Log::ISMTTLog* logger; ///< The logger
			};
		}
	}
}

#endif /* CRYPTODATA_HXX_ */
