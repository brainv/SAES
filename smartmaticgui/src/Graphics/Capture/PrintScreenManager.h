/*
 * PrintScreenManager.h
 *
 *  Created on: Apr 7, 2011
 *      Author: Gerardo Hernandez
 */

#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include "System/Runtime/ProcessLauncher.h"

#ifndef PRINTSCREENMANAGER_H_

/**
 * @brief	Gets the printscreenmanager h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define PRINTSCREENMANAGER_H_


namespace Smartmatic
{
	namespace Graphics
	{
		namespace Capture
		{

			class PrintScreenManager {
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				PrintScreenManager();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual ~PrintScreenManager();

				/**
				 * @brief	Captures.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	windowID	 	Identifier for the window.
				 * @param	imageFullPath	Full pathname of the image full file.
				 */

				void Capture(std::string windowID, std::string imageFullPath);

				/**
				 * @brief	Capture root screen.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	imageFolderFullPath	Full pathname of the image folder full file.
				 */

				void CaptureRootScreen(std::string imageFolderFullPath);

				/**
				 * @brief	Gets the windows.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	windowPrefix	The window prefix.
				 *
				 * @return	The windows.
				 */

				std::vector<std::string> GetWindows(std::string windowPrefix);

				/**
				 * @brief	Gets the windows.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	windowsPrefix	The windows prefix.
				 *
				 * @return	The windows.
				 */

				std::vector<std::string> GetWindows(std::vector<std::string> windowsPrefix);

			protected:

			private:

				bool isComplete();

			};

		}
	}
}

#endif /* PRINTSCREENMANAGER_H_ */
