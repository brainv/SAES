/*
 * SmartCardController.hxx
 *
 *  Created on: 16/08/2011
 *      Author: soto
 */

#ifndef _SMARTCARDCONTROLLER_HXX_
#define _SMARTCARDCONTROLLER_HXX_

#include <Card/ICardController.hxx>
#include <Log/ISMTTLog.h>
#include <Card/SmartCard.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Card
			{
				class SmartCardController : public Smartmatic::SAES::Card::ICardController
				{
				public:

					SmartCardController();
					virtual  ~SmartCardController();

					virtual bool initialize();
					virtual bool isCardPresent() throw ( Smartmatic::System::Exception::CardReaderUnresponsiveException );
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

					bool testSelect();
					bool testWriteRead();

					Smartmatic::SAES::Card::SmartCard smartCard;
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
				};
			}
		}
	}
}

#endif /* _SMARTCARDCONTROLLER_HXX_ */
