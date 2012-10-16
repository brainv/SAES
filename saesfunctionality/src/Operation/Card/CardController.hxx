/**
 * @file CardController.hxx
 * @brief Header class card controller
 * @date 15/08/2011
 * @author Yadickson Soto
 */

#ifndef CARDCONTROLLER_HXX_
#define CARDCONTROLLER_HXX_

#include <Card/ICardController.hxx>
#include <Voting/VotingDevice/card-data-schema.hxx>
#include <Voting/VotingDevice/contingency-card-data-schema.hxx>
#include <Operation/Security/CryptoCard.hxx>
#include <Operation/Security/CryptoToken.hxx>
#include <System/Exception/InvalidCardContentException.hxx>
#include <System/Exception/CardReaderUnresponsiveException.hxx>
#include <System/Exception/IOCardException.h>
#include <glibmm.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Operation
		{
			namespace Card
			{
				/**
				 * @class CardController
				 * @brief Class card controller
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 15/08/2011
				 * @see ICardController
				 */
				class CardController : public Smartmatic::SAES::Card::ICardController
				{
				private:

	                /**
	                 * @brief Class constructor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					CardController();

					static CardController * instance; ///< instance
					Smartmatic::SAES::Card::ICardController * interface; ///< interface card controller
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
					Smartmatic::SAES::Operation::Security::CryptoCard * cryptoCardData; ///< crypto card data
					Smartmatic::SAES::Operation::Security::CryptoToken cryptoToken; ///< crypto token card
					Smartmatic::SAES::Operation::Security::CryptoCard * cryptoContingencyCard; ///< crypto contingency card

				public:

	                /**
	                 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual ~CardController();
	                /**
	                 * @brief Method get instance
	                 * @return instance class
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					static CardController * getInstance();
	                /**
	                 * @brief Method initialize
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual bool initialize();
	                /**
	                 * @brief Method getter is card present
	                 * @return true is card present
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual bool isCardPresent() throw( Smartmatic::System::Exception::CardReaderUnresponsiveException );
	                /**
	                 * @brief Method card test
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual bool test();
	                /**
	                 * @brief Method dispose
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual void dispose();
	                /**
	                 * @brief Method read card data
	                 * @param cardData result card data
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool readCardData(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData)
					throw ( Smartmatic::System::Exception::IOCardException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method write card data
	                 * @param cardData card data
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool writeCardData(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData)
					throw ( Smartmatic::System::Exception::IOCardException,
							Smartmatic::System::Exception::CardCanNotWriteException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method read contingency card data
	                 * @param cardData result card data
	                 * @param strPin pin
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool readContingencyCardData(Smartmatic::SAES::Voting::VotingDevice::ContingencyCardData & cardData, std::string & strPin)
					throw ( Smartmatic::System::Exception::IOCardException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method write contingency card data
	                 * @param cardData card data
	                 * @param strPin pin
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool writeContingencyCardData(Smartmatic::SAES::Voting::VotingDevice::ContingencyCardData & cardData, std::string & strPin)
					throw ( Smartmatic::System::Exception::IOCardException,
							Smartmatic::System::Exception::CardCanNotWriteException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method read token card
	                 * @param password result password
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool readToken(std::string & password)
					throw ( Smartmatic::System::Exception::IOCardException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method write token card
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					bool writeToken()
					throw ( Smartmatic::System::Exception::IOCardException,
							Smartmatic::System::Exception::CardCanNotWriteException,
						    Smartmatic::System::Exception::InvalidCardContentException);

				private:

					Glib::Mutex mutex; ///< mutex

	                /**
	                 * @brief Method read and decrypto buffer
	                 * @param buffer result data
	                 * @param cryptoData object crypto
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual bool read(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
					throw ( Smartmatic::System::Exception::IOCardException,
						    Smartmatic::System::Exception::InvalidCardContentException);
	                /**
	                 * @brief Method write and crypto buffer
	                 * @param buffer data
	                 * @param cryptoData object crypto
	                 * @return true is valid
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 15/08/2011
	                 */
					virtual bool write(Smartmatic::System::SafeBuffer & buffer, Smartmatic::SAES::Security::CryptoData & cryptoData)
					throw ( Smartmatic::System::Exception::IOCardException,
							Smartmatic::System::Exception::CardCanNotWriteException,
						    Smartmatic::System::Exception::InvalidCardContentException);
				};
			}
		}
	}
}

#endif /* CARDCONTROLLER_HXX_ */
