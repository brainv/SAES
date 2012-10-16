/**
 * @file X7SSecurity.hxx
 * @brief Header class x7s security
 * @date 19/03/2012
 * @author Yadickson Soto
 */

#ifndef X7SSECURITY_HXX_
#define X7SSECURITY_HXX_

#include <Voting/ElectoralConfiguration.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/SafeBuffer.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace Voting
		{
			namespace Codi
			{
				/**
				 * @class X7SSecurity
				 * @brief Class x7s security
				 * @date 19/03/2012
				 * @author Yadickson Soto
				 */
				class X7SSecurity
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					X7SSecurity();
					/**
					 * @brief Class destroy
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~X7SSecurity();
					/**
					 * @brief Method init class
					 * @param electoralConfiguration electoral configuration
					 * @param directories saes directories
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					void init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
							Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories);
					/**
					 * @brief Method signed buffer
					 * @param bufferIn buffer in
					 * @param bufferOut buffer out
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					void signedBuffer(Smartmatic::System::SafeBuffer & bufferIn,
							Smartmatic::System::SafeBuffer & bufferOut)
						throw (Smartmatic::System::Exception::CryptoException,
								Smartmatic::System::Exception::SignedException);
					/**
					 * @brief Method crypto buffer
					 * @param bufferIn buffer in
					 * @param bufferOut buffer out
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					void cryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
							Smartmatic::System::SafeBuffer & bufferOut)
						throw (Smartmatic::System::Exception::CryptoException);
					/**
					 * @brief Method decrypto buffer
					 * @param bufferIn buffer in
					 * @param bufferOut buffer out
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					void decryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
							Smartmatic::System::SafeBuffer & bufferOut)
						throw (Smartmatic::System::Exception::CryptoException);
					/**
					 * @brief Method validate buffer
					 * @param bufferIn buffer in
					 * @date 19/03/2012
					 * @author Yadickson Soto
					 */
					void validateSignedBuffer(Smartmatic::System::SafeBuffer & bufferIn)
						throw (Smartmatic::System::Exception::SignedException);

				private:
					Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///< electoral configuration
					Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories; ///< saes directories
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* X7SSECURITY_HXX_ */
