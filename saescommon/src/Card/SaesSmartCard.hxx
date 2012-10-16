/*
 * SmartCardController.hxx
 *
 *  Created on: 15/08/2011
 *      Author: soto
 */

#ifndef _SAESSMARTCARD_HXX_
#define _SAESSMARTCARD_HXX_

#include "ICardController.hxx"
#include "SmartCardCommand.hxx"
#include <System/Exception/IOCardException.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Card
		{
			class SaesSmartCard : public ICardController, private SmartCardCommand
			{
			public:

				SaesSmartCard();
				virtual ~SaesSmartCard();

				virtual bool initialize();
				virtual bool isCardPresent() throw( Smartmatic::System::Exception::CardReaderUnresponsiveException );

				virtual bool read(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
				        Smartmatic::System::Exception::InvalidCardContentException );

				virtual bool write(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
						Smartmatic::System::Exception::CardCanNotWriteException,
					    Smartmatic::System::Exception::InvalidCardContentException);

				virtual bool test();
				virtual void dispose();

			private:

				bool initStatus;
				unsigned int countReload;
				bool doPowerCycle;
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				void reloadReader();
				void viewReloadSuccess();
			};
		}
	}
}

#endif /* _SAESSMARTCARD_HXX_ */
