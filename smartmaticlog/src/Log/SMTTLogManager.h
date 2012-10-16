/**
 * @file	SMTTLogManager.h
 *
 * @brief	Declares the smtt log manager class.
 */

#ifndef _SMTTLOGMANAGER_H_
#define _SMTTLOGMANAGER_H_

#include <iostream>
#include <vector>
#include <typeinfo>
#include <map>

namespace Smartmatic
{
    namespace Log
    {
    	/**
    	 * @class ISMTTLog
    	 * @brief forward declaration of the class.
    	 */
    	class ISMTTLog;
    }
}

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @class SMTTLogManager
		 * @brief	Manage the state and functions about Loggers and logs. 
		 *
		 * @author	Fsilva
		 * @date	28/04/2011
		 */

		class SMTTLogManager
		{
		public:

			/**
			 * @brief	Checks if the file exits.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	name	The name.
			 *
			 * @return	null if it fails, else.
			 */
			static ISMTTLog* Exist(std::string name);

			/**
			 * @brief	Checks if the file exits.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	name  	The name.
			 * @param	domain	The domain.
			 *
			 * @return	null if it fails, else.
			 */
			static ISMTTLog* Exist(std::string name, std::string domain);

			/**
			 * @brief	Gets the current loggers.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @return	null if it fails, else the current loggers.
			 */
			static std::vector<ISMTTLog*> GetCurrentLoggers();

			/**
			 * @brief	Gets a current loggers.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	domain	The domain.
			 *
			 * @return	null if it fails, else the current loggers.
			 */
			static std::vector<ISMTTLog*> GetCurrentLoggers(std::string domain);

			/**
			 * @brief	Gets a logger.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	name  	The name.
			 * @param	domain	The domain.
			 *
			 * @return	null if it fails, else the logger.
			 */
			static ISMTTLog* GetLogger(std::string name, std::string domain);

			/**
			 * @brief	Configures the logger by the given file.
			 *
			 * @author	Fsilva
			 * @date	27/04/2011
			 *
			 * @param	fileName	Filename of the file.
			 */
			static void Configure(std::string fileName);

			/**
			 * @brief	Configures the logger by default.
			 *
			 * @author	gerardo.hernandez
			 * @date	13/05/2011
			 *
			 */
			static void Configure();

            /**
             * @brief   Reconfigure the logger.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    27/05/2011
             *
             */
			static void Reconfigure();

            /**
             * @brief   Shutdown the logger.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    27/05/2011
             *
             */
			static void shutdown();

			static const std::string & getConfigFile();

		protected:

		private:

			static std::string fullFilePath; ///< full file path configure
		};
	}
}

#endif // _SMTTLOGMANAGER_H_
