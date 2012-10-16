/**
 * @file LogInterface.hxx
 * @brief Header interface log class
 * @date 18/07/2011
 * @author Yadickson Soto
 */

#ifndef LOGINTERFACE_HXX_
#define LOGINTERFACE_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace Log
	{
		/**
		 * @class LogInterface
		 * @brief Interface for Log
		 * @date 18/07/2011
		 * @author Yadickson Soto
		 */
		class LogInterface
		{
			public:
				/**
				 * @brief Constructor class
				 * @param code code of interface
				 * @date 18/07/2011
				 * @author Yadickson Soto
				 */
				LogInterface(std::string code);
				/**
				 * @brief Method for get code of class
				 * @return code of class
				 * @date 18/07/2011
				 * @author Yadickson Soto
				 */
				std::string getCode();

			protected:
				std::string code; ///< Code of class
		};
	}
}

#endif /* LOGINTERFACE_HXX_ */
