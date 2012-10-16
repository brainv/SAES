/**
 * @file WindowsManager.hxx
 * @brief Header class windows manager
 * @date 26/03/2012
 * @author Yadickson Soto
 */

#ifndef WINDOWSMANAGER_HXX_
#define WINDOWSMANAGER_HXX_

#include <vector>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace GUI
	{
		namespace Windows
		{
			class BasicWindow;
		}

		namespace Operation
		{
			/**
			 * @class WindowsManager
			 * @brief Class windows manager
			 * @date 26/03/2012
			 * @author Yadickson Soto
			 */
			class WindowsManager
			{
			protected:
				/**
				 * @brief Class constructor
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				WindowsManager();

				static WindowsManager * instance; ///< instance class

			public:
				/**
				 * @brief Class destroy
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				virtual ~WindowsManager();
				/**
				 * @brief Method push new window
				 * @param window new window
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				void push(Smartmatic::GUI::Windows::BasicWindow * window);
				/**
				 * @brief Method pop last window
				 * @return last window
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				Smartmatic::GUI::Windows::BasicWindow * pop();
				/**
				 * @brief Method getter current window
				 * @return current window
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				Smartmatic::GUI::Windows::BasicWindow * current();
				/**
				 * @brief Method getter instance class
				 * @return instance class
				 * @date 26/03/2012
				 * @author Yadickson Soto
				 */
				static WindowsManager * getInstance();

			private:

				std::vector < Smartmatic::GUI::Windows::BasicWindow * > staticWindows; ///< statics list base windows
				static Smartmatic::Log::ISMTTLog* logger;///< The logger
			};
		}
	}
}

#endif /* WINDOWSMANAGER_HXX_ */
