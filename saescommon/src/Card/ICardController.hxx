/*
 * ICardController.hxx
 *
 *  Created on: 15/08/2011
 *      Author: soto
 */

#ifndef ICARDCONTROLLER_HXX_
#define ICARDCONTROLLER_HXX_

#include <Security/CryptoData.hxx>
#include <System/SafeBuffer.h>
#include <System/Exception/IOCardException.h>
#include <System/Exception/InvalidCardContentException.hxx>
#include <System/Exception/CardCanNotWriteException.h>
#include <System/Exception/CardReaderUnresponsiveException.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Card
		{
			class ICardController
			{
			public:

				ICardController();
				virtual ~ICardController();

				virtual bool initialize() = 0;
				virtual bool isCardPresent() 
        throw( Smartmatic::System::Exception::CardReaderUnresponsiveException )= 0;
				virtual bool read(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
					    Smartmatic::System::Exception::InvalidCardContentException) = 0;
				virtual bool write(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
				throw ( Smartmatic::System::Exception::IOCardException,
						Smartmatic::System::Exception::CardCanNotWriteException,
					    Smartmatic::System::Exception::InvalidCardContentException) = 0;
				virtual bool test() = 0;
				virtual void dispose() = 0;
				virtual void doReaderPowerCycle();

			private:
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* ICARDCONTROLLER_HXX_ */
