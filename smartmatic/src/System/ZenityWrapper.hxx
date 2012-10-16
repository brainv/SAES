/**
 * @file ZenityWrapper.hxx
 * @brief Header class zenity wrapper
 * @date 23/02/2012
 * @author Yadickson Soto
 */

#ifndef ZENITYWRAPPER_HXX_
#define ZENITYWRAPPER_HXX_

#include <iostream>

namespace Smartmatic
{
    namespace System
    {
		/**
		 * @class ZenityWrapper
		 * @brief Class zenity wrapper
		 * @date 23/02/2012
		 * @author Yadickson Soto
		 */
    	class ZenityWrapper
    	{
		protected:
    		/**
    		 * @brief Class constructor
    		 * @date 23/02/2012
    		 * @author Yadickson Soto
    		 */
			ZenityWrapper();

		public:
    		/**
    		 * @brief Class destroy
    		 * @date 23/02/2012
    		 * @author Yadickson Soto
    		 */
			virtual ~ZenityWrapper();

    		/**
    		 * @brief Method show error
    		 * @param message message info
    		 * @param title title window (optional)
    		 *
    		 * @date 23/02/2012
    		 * @author Yadickson Soto
    		 */
			static void showError(std::string message, std::string title);

    		/**
    		 * @brief Method show warning
    		 * @param message message info
    		 * @param title title window (optional)
    		 * @param timeout timeout in seconds (default infinite)
    		 *
    		 * @date 23/02/2012
    		 * @author Yadickson Soto
    		 */
			static void showWarning(std::string message, std::string title, int timeout = 0);

    		/**
    		 * @brief Method show info
    		 * @param message message info
    		 * @param title title window (optional)
    		 * @param timeout timeout in seconds (default infinite)
    		 *
    		 * @date 23/02/2012
    		 * @author Yadickson Soto
    		 */
			static void showInfo(std::string message, std::string title, int timeout = 0);
		};
    }
}

#endif /* ZENITYWRAPPER_HXX_ */
