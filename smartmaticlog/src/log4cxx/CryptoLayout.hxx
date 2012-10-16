/**
 * @file CryptoLayout.hxx
 * @brief Header class CryptoLayout
 * @date 15/07/2011
 * @author Yadickson Soto yadickson.soto@smartmatic.com
 */

#ifndef CRYPTOLAYOUT_HXX_
#define CRYPTOLAYOUT_HXX_

#include <map>
#include <log4cxx/patternlayout.h>
#include <Log/ICryptoLayoutTransformer.hxx>

namespace log4cxx
{
	/**
	 * @class CryptoLayout
	 * @brief This class allows the extension of the class log4cxx::PatternLayout.
	 * @date 15/07/2011
	 * @author Yadickson Soto yadickson.soto@smartmatic.com
	 */
	class CryptoLayout: public log4cxx::PatternLayout
	{
		public:
			DECLARE_LOG4CXX_OBJECT(CryptoLayout)
				BEGIN_LOG4CXX_CAST_MAP()
				LOG4CXX_CAST_ENTRY(CryptoLayout)
				LOG4CXX_CAST_ENTRY_CHAIN(PatternLayout)
				END_LOG4CXX_CAST_MAP()

			/**
			 * @brief Class constructor
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			CryptoLayout();

			/**
			 * @brief Class destroy
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual ~CryptoLayout ();

			/**
			 * @brief virtual method, The PatternLayout does not handle the throwable contained within spi::LoggingEvent LoggingEvents.
			 * @return Thus, it returns true.
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual bool ignoresThrowable();

			/**
			 * @brief Virtual method set option config
			 * @param option option name of config file logger
			 * @param value value of option
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual void setOption(const log4cxx::LogString& option, const log4cxx::LogString& value);

			/**
			 * @brief virtual method, The format string
			 * @param output output format line logger
			 * @param event object container data line
			 * @param pool object for synchronize
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual void format(log4cxx::LogString& output,
			                     const spi::LoggingEventPtr& event,
			                     log4cxx::helpers::Pool& pool) const;

			/**
			 * @brief Method setter crypto map interface
			 * @param iCryptoMap crypto map interface
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 * @see Smartmatic::Log::ICryptoLayoutTransformer
			 */
			static void setCryptoMap(std::map < std::string, Smartmatic::Log::ICryptoLayoutTransformer * > iCryptoMap );
			/**
			 * @brief Method put new crypto interface
			 * @param iCrypto new crypto interface
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 * @see Smartmatic::Log::ICryptoLayoutTransformer
			 */
			static void putCryptoInterface(Smartmatic::Log::ICryptoLayoutTransformer * iCrypto);

		protected:

			log4cxx::LogString cryptoType; ///< crypto type
			static std::map <std::string, Smartmatic::Log::ICryptoLayoutTransformer * > iCryptoMap; ///< crypto map interface

			/**
			 * @brief Method format output line logger
			 * @param output output format line logger
			 * @param cryptoType crypto type
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			static void format(log4cxx::LogString& output, log4cxx::LogString cryptoType);
	};

	LOG4CXX_PTR_DEF(CryptoLayout); ///< create pointer of class 
}

#endif /* CRYPTOLAYOUT_HXX_ */
