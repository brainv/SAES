/**
 * @file	LogImpl.h
 * @brief	Declares the log implementation class.
 * @date 08-03-2011
 * @author gerardohernandez
 */

#ifndef LOGIMPL_H_
#define LOGIMPL_H_

#include "ISMTTLog.h"
#include "log4cxx/logger.h"
#include "log4cxx/helpers/pool.h"
#include "log4cxx/spi/loggingevent.h"

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @class LogImpl
		 * @brief	Implementation of the ISMTTLog.
		 *
		 * @author	Fsilva
		 * @date	28/04/2011
		 * @see ISMTTLog
		 */

		class LogImpl : public ISMTTLog, public log4cxx::Logger
		{

		private:

			log4cxx::LoggerPtr loggerPtr;   ///< The logger pointer
			log4cxx::LoggerPtr loggerError; ///< The logger with the error level
			log4cxx::LoggerPtr loggerInfo;  ///< The logger with the info level
			log4cxx::LoggerPtr loggerWarn;  ///< The logger with the warning level
			bool useResourceManager;	///< true to use resource manager
			log4cxx::LogString currentName; ///< The current name of the log string
			std::string domain; ///< The domain
			bool activatePathValidation; ///< flag for activate path validation

			/**
			 * @brief	Executes the log operation.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	level	   	The level.
			 * @param	messageCode	The message code.
			 */

			void doLog(log4cxx::LevelPtr level, std::string messageCode);

			/**
			 * @brief	Executes the log operation.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	level		   	The level.
			 * @param	messageCode	   	The message code.
			 * @param	properties	   	The properties.
			 * @param	t			   	Details of the exception.
			 * @param	messageArgument	The message argument.
			 */

			void doLog(log4cxx::LevelPtr level, std::string messageCode, std::map<std::string, std::string> properties, std::exception t, std::vector<std::string> messageArgument);

			/**
			 * @brief	Method for validate logger path
			 *
			 * @author	Yadickson Soto
			 * @date	27/04/2011
			 *
			 * @param	logger	logger to validate
			 * @return	true is path is validated
			 */
			bool validatePath(log4cxx::LoggerPtr logger);

			/**
			 * @brief	Method for validate directory path
			 *
			 * @author	Yadickson Soto
			 * @date	27/04/2011
			 *
			 * @param	path	logger path to validate
			 * @return	true is path is validated
			 */
			bool DirectoryExists(const std::string & path);

		public:

			/**
			 * @brief	Constructor.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	loggerInfoArg 	The logger information argument.
			 * @param	loggerErrorArg	The logger error argument.
			 * @param	loggerWarnArg 	The logger warning argument.
			 * @param [in,out]	pool  	The pool.
			 * @param	name		  	The name.
			 * @param	domain		  	The domain.
			 */

			LogImpl(log4cxx::LoggerPtr loggerInfoArg,log4cxx::LoggerPtr loggerErrorArg, log4cxx::LoggerPtr loggerWarnArg,
					log4cxx::helpers::Pool& pool, const log4cxx::LogString& name, std::string domain = "");
			/**
			 * @brief	Log the Debug message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Debug(std::string messageCode);

			/**
			 * @brief	Log the Debug message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Debug(std::string messageCode, std::exception errorEntry);

			/**
			 * @brief	Log the Info message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Info(std::string messageCode);

			/**
			 * @brief	Log the Info message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Info(std::string messageCode, std::exception errorEntry);

			/**
			 * @brief	Log the Audit message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Audit(std::string messageCode);

			/**
			 * @brief	Log the Audit message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Audit(std::string messageCode, std::exception errorEntry);

			/**
			 * @brief	Log the Warn message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Warn(std::string messageCode);

			/**
			 * @brief	Log the Warn message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Warn(std::string messageCode, std::exception errorEntry);

			/**
			 * @brief	Log the error message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Error(std::string messageCode);

			/**
			 * @brief	Log the error message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Error(std::string messageCode, std::exception errorEntry);

			/**
			 * @brief	Log the Fatal message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 */

			void Fatal(std::string messageCode);

			/**
			 * @brief	Log the fatal message.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	messageCode	The message code.
			 * @param	errorEntry 	Details of the exception.
			 */

			void Fatal(std::string messageCode, std::exception errorEntry);
		};
	}
}

#endif /* LOGIMPL_H_ */
