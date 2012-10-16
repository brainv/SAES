/*
 * MemoryCardController.hxx
 *
 *  Created on: 15/08/2011
 *      Author: soto
 */

#ifndef MEMORYCARDCONTROLLER_HXX_
#define MEMORYCARDCONTROLLER_HXX_

#include <Card/ICardController.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Card
			{
				class MemoryCardController: public Smartmatic::SAES::Card::ICardController
				{
				public:
					MemoryCardController();
					virtual ~MemoryCardController();

					virtual bool initialize();
					virtual bool isCardPresent()
          throw( Smartmatic::System::Exception::CardReaderUnresponsiveException );
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

					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
				};
			}
		}
	}
}

#endif /* MEMORYCARDCONTROLLER_HXX_ */
