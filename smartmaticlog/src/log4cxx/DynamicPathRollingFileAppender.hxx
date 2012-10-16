/**
 * @file DynamicPathRollingFileAppender.hxx
 * @brief Header class DynamicPathRollingFileAppender
 * @date 15/07/2011
 * @author Yadickson Soto yadickson.soto@smartmatic.com
 */

#ifndef DYNAMICPATHROLLINGFILEAPPENDER_HXX_
#define DYNAMICPATHROLLINGFILEAPPENDER_HXX_

#include <log4cxx/rollingfileappender.h>
#include <Log/BasePathInterface.hxx>
#include <list>
#include <map>

namespace log4cxx
{
	/**
	 * @class DynamicPathRollingFileAppender
	 * @brief This class allows the extension of the class log4cxx::RollingFileAppender
	 * @date 15/07/2011
	 * @author Yadickson Soto yadickson.soto@smartmatic.com
	 */
	class DynamicPathRollingFileAppender : public log4cxx::RollingFileAppender
	{
		public:
			DECLARE_LOG4CXX_OBJECT(DynamicPathRollingFileAppender)
			BEGIN_LOG4CXX_CAST_MAP()
				LOG4CXX_CAST_ENTRY(DynamicPathRollingFileAppender)
				LOG4CXX_CAST_ENTRY_CHAIN(RollingFileAppender)
			END_LOG4CXX_CAST_MAP()
			/**
			 * @brief Constructor class
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			DynamicPathRollingFileAppender();

			/**
			 * @brief Destroy
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual ~DynamicPathRollingFileAppender();

			/**
			 * @brief Virtual method set file name
			 * @param file file name of config file logger
			 * @param append flag method
			 * @param bufferedIO flag method
			 * @param bufferSize size of buffer
			 * @param p object for synchronize
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual void setFile(const log4cxx::LogString& file,
						bool append,
						bool bufferedIO,
						size_t bufferSize,
						log4cxx::helpers::Pool& p);

			/**
			 * @brief Virtual method set option config
			 * @param option option name of config file logger
			 * @param value value of option
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual void setOption( const log4cxx::LogString & option, const log4cxx::LogString & value );

			/**
			 * @brief Virtual method set append log
			 * @param event object container data line
			 * @param p object for synchronize
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			virtual void append(const log4cxx::spi::LoggingEventPtr& event, log4cxx::helpers::Pool& p);

			/**
			 * @brief Method set base path interface logger
			 * @param iBasePath base path interface
			 * @see Smartmatic::Log::BasePathInterface
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			static void putBasePathInterface(Smartmatic::Log::BasePathInterface * iBasePath);

			/**
			 * @brief Method getter state change map
			 * @return state change map
			 * @date 15/07/2011
			 * @author Yadickson Soto yadickson.soto@smartmatic.com
			 */
			static std::map <int, bool> & getStateChangeMap();

		private:

			static std::map <std::string, Smartmatic::Log::BasePathInterface * > iBasePathMap; ///< state change map

			log4cxx::LogString file; ///< file name logger
			log4cxx::LogString cryptoType; ///< crypto type config
			log4cxx::LogString basePathType; ///< base path type

			bool appendFlag; ///< append flag logger file
			bool bufferedIO; ///< buffer io flag logger file
			size_t bufferSize; ///< buffer size logger file
			bool createFile;  ///< flag for create logger file
			bool forceClose; ///< flag for force close logger file
	};

	LOG4CXX_PTR_DEF(DynamicPathRollingFileAppender); ///< create pointer of class DynamicPathRollingFileAppender
}

#endif /* DYNAMICPATHROLLINGFILEAPPENDER_HXX_ */
