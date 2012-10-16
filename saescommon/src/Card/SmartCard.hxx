/*
 * SmartCard.hxx
 *
 *  Created on: 16/08/2011
 *      Author: soto
 */

#ifndef _SMARTCARD_HXX_
#define _SMARTCARD_HXX_

#include "ICardController.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Card
		{
			class SaesSmartCard;

			class SmartCard : public ICardController
			{
			public:

				SmartCard();
				virtual ~SmartCard();

				virtual bool initialize();
				virtual bool isCardPresent() throw( Smartmatic::System::Exception::CardReaderUnresponsiveException );
				virtual bool read(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
					    Smartmatic::System::Exception::InvalidCardContentException);

				virtual bool write(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
						Smartmatic::System::Exception::CardCanNotWriteException,
					    Smartmatic::System::Exception::InvalidCardContentException);

				virtual bool test();
				virtual void dispose();

			private:

				ICardController * smartCard;
			};
		}
	}
}

#endif /* _SMARTCARD_HXX_ */
