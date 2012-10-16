/**
 * @file  ICryptoLayoutTransformer.hxx
 * @brief	Header class ICryptoLayoutTransformer.
 *
 * @author	Yadickson Soto
 * @date	15-07-2011
 *
 */

#ifndef CRYPTOINTERFACE_HXX_
#define CRYPTOINTERFACE_HXX_

#include <log4cxx/helpers/pool.h>
#include <log4cxx/helpers/mutex.h>
#include <Log/LogInterface.hxx>

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @class ICryptoLayoutTransformer
		 * @brief	Constructor class.
		 *
		 * @author	Yadickson Soto
		 * @date	15-07-2011
		 *
		 * @see LogInterface
		 *
		 */
		class ICryptoLayoutTransformer : public LogInterface
		{
			public:

				/**
				 * @brief	Constructor class.
				 * @param code code of crypto layout
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				ICryptoLayoutTransformer (std::string code);
				/**
				 * @brief	Destroy.
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				virtual ~ICryptoLayoutTransformer();
				/**
				 * @brief	Virtual method for encode line.
				 * @param line line to encode
				 * @return encode line
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				virtual std::string encode(std::string & line) = 0;
				/**
				 * @brief	Virtual method for decode line.
				 * @param line line to decode
				 * @return decode line
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				virtual std::string decode(std::string & line) = 0;
				/**
				 * @brief	Method for get mutex class.
				 * @return mutex class
				 *
				 * @author	Yadickson Soto
				 * @date	15-07-2011
				 *
				 */
				log4cxx::helpers::Mutex & getMutex();

			private:

				log4cxx::helpers::Pool pool; ///< Pool for mutex
				log4cxx::helpers::Mutex mutex; ///< Object Mutex
		};
	}
}

#endif /* CRYPTOINTERFACE_HXX_ */
