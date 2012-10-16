/**
 * @file	ISMTTLog.h
 * @brief	Declares the ismtt log class.
 * @date 8/07/2011
 * @author gerardohernandez
 */

#ifndef ISMTTLOG_H_
#define ISMTTLOG_H_

#include <string>

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @brief	Interface to define the contract for the SMTT log.  
		 *
		 * @author	Fsilva
		 * @date	28/04/2011
		 */

		class ISMTTLog
		{
			public:

				/**
				 * @brief	Constructor class.
				 *
				 * @author	Yadickson Soto
				 * @date	20/01/2012
				 *
				 */
				ISMTTLog();

				/**
				 * @brief	Destroy.
				 *
				 * @author	Yadickson Soto
				 * @date	20/01/2012
				 *
				 */
				virtual ~ISMTTLog();

				/**
				 * @brief	Log the debug message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Debug(std::string messageCode) = 0;

				/**
				 * @brief	Log the debug message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Debug(std::string messageCode, std::exception errorEntry) = 0;

				/**
				 * @brief	Log the info message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Info(std::string messageCode) = 0;

				/**
				 * @brief	Log the info message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Info(std::string messageCode, std::exception errorEntry) = 0;

				/**
				 * @brief	Log the audit message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Audit(std::string messageCode) = 0;

				/**
				 * @brief	Log the audit message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Audit(std::string messageCode, std::exception errorEntry) = 0;

				/**
				 * @brief	Log the warn message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Warn(std::string messageCode) = 0;

				/**
				 * @brief	Log the warn message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Warn(std::string messageCode, std::exception errorEntry) = 0;

				/**
				 * @brief	Log the error message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Error(std::string messageCode) = 0;

				/**
				 * @brief	Log the error message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Error(std::string messageCode, std::exception errorEntry) = 0;

				/**
				 * @brief	Log the fatal message
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 */

				virtual void Fatal(std::string messageCode) = 0;

				/**
				 * @brief	Log the fatal message.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	messageCode	The message code.
				 * @param	errorEntry 	Details of the exception.
				 */

				virtual void Fatal(std::string messageCode, std::exception errorEntry) = 0;
		};
	}
}

#endif /* ISMTTLOG_H_ */
