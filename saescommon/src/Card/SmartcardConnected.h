/*
 * SmartcardConnected.h
 *
 *  Created on: Sep 1, 2011
 *      Author: fgomez
 */

#ifndef SMARTCARDCONNECTED_H_
#define SMARTCARDCONNECTED_H_

#include "ICardController.hxx"
#include "SmartCardCommand.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Card
		{
			class SmartcardConnected : public ICardController, private SmartCardCommand
			{
			public:

				SmartcardConnected();
				virtual ~SmartcardConnected();

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

				bool initStatus;
				long countLogger;
        unsigned int powerCycleTryCount;
				bool renewContext;
				bool checkCardUsingPCSC;
				bool connectToCheckPresence;

				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				void finalizePCSCConnection();
				void startPCSCConnection();
				bool checkCardPCSC() throw( Smartmatic::System::Exception::CardReaderUnresponsiveException );
			
				int counterError;
			};
		}
	}
}


#endif /* SMARTCARDCONNECTED_H_ */
