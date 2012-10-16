/**
 * @file OptParser.hxx
 * @brief Header class OptParser
 * @author Yadickson Soto
 * @date 23/08/2011
 */

#ifndef OPTPARSER_HXX_
#define OPTPARSER_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace System
	{
		/**
		 * @class OptParser
		 * @brief Class for parser parameters
		 * @author Yadickson Soto
		 * @date 23/08/2011
		 */
		class OptParser
		{
		public:

			/**
			 * @enum Options
			 * @brief Options available
			 * @author Yadickson Soto
			 * @date 23/08/2011
			 */
			enum Options
			{
				 CONFIG ///< Config parameters
				,LOGGER ///< Logger parameters
				,XSLFO ///< xslfo file
				,MODE ///< mode start machine
				,HELP = 'h' ///< Help option
				,VERS = 'v' ///< Version option
			};

			/**
			 * @brief Class constructor
			 * @param argc Count arg
			 * @param argv Vector of data
			 * @param package package name
			 * @param version package version
			 * @param basepath base path config dir
			 * @author Yadickson Soto
			 * @date 01/08/2012
			 */
			OptParser(int argc, char **argv, const std::string & package, const std::string & version, std::string basepath = "");
			/**
			 * @brief Method getter is option enabled
			 * @param opt option to evaluate
			 * @return true option is enable
			 * @author Yadickson Soto
			 * @date 23/08/2011
			 */
			bool isSet(Options opt);
			/**
			 * @brief Method getter option value
			 * @param opt option to evaluate
			 * @param str in, out option value string
			 * @author Yadickson Soto
			 * @date 23/08/2011
			 */
			void getArg(Options opt, std::string & str);
			/**
			 * @brief Method getter option config value
			 * @param config in,out string
			 * @return true is config option enable
			 * @author Yadickson Soto
			 * @date 09/02/2012
			 */
			bool getConfigOption(std::string & config);
			/**
			 * @brief Method getter option logger value
			 * @param logger in,out string
			 * @return true is logger option enable
			 * @author Yadickson Soto
			 * @date 09/02/2012
			 */
			bool getLoggerOption(std::string & logger);
			/**
			 * @brief Method getter option help value
			 * @param help in,out string
			 * @return true is help option enable
			 * @author Yadickson Soto
			 * @date 09/02/2012
			 */
			bool getHelpOption(std::string & help);
			/**
			 * @brief Method getter option version value
			 * @param version in,out string
			 * @return true is version option enable
			 * @author Yadickson Soto
			 * @date 09/02/2012
			 */
			bool getVersionOption(std::string & version);

		private:
			int argc; ///< Count arg
			char **argv; ///< Vector of data
			static Smartmatic::Log::ISMTTLog* logger;///< The logger

			/**
			 * @brief Method process args
			 * @param package package name
			 * @param version package version
			 * @param basepath base path config dir
			 * @author Yadickson Soto
			 * @date 01/08/2012
			 */
			void processArgs(const std::string & package, const std::string & version, std::string basepath);

			/**
			 * @brief Method getter option value
			 * @param opt option to evaluate
			 * @param str in,out string
			 * @return true is option enable
			 * @author Yadickson Soto
			 * @date 09/02/2012
			 */
			bool getStringOption(Options opt, std::string & str);
		};
	}
}

#endif /* OPTPARSER_HXX_ */
