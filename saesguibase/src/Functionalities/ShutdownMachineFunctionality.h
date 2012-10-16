/*
 * ShutdownMachineFunctionality.h
 *
 *  Created on: Jun 10, 2011
 *      Author: gerardohernandez
 */

#ifndef SHUTDOWNMACHINEFUNCTIONALITY_H_
#define SHUTDOWNMACHINEFUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Widgets/smartmatic-button.h>
#include <Log/ISMTTLog.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class ShutdownMachineFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
					public:
						/**
						 * @brief	Gets the current.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else.
						 */

						static ShutdownMachineFunctionality* Current();

					protected:

						/**
						 * @brief	Gets the logger.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else the logger.
						 */

						Smartmatic::Log::ISMTTLog* getLogger();

						/**
						 * @brief	Gets the start log message.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	The start log message.
						 */

						Glib::ustring getStartLogMessage();

						/**
						 * @brief	Gets the finish log message.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	The finish log message.
						 */

						Glib::ustring getFinishLogMessage();

						/**
						 * @brief method delete all element
						 * @date 03/04/2012
						 * @author Yadickson Soto
						 */
						virtual void deleteElement();

					private:
						static ShutdownMachineFunctionality *current_instance;

						Gtk::Frame* externalFrame;
						Gtk::Label* titleLabel;

						/**
						 * @brief	Default constructor.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 */

						ShutdownMachineFunctionality();

						/**
						 * @brief	Gets the frame.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else the frame.
						 */

						Gtk::Widget* GetFrame();

						void Dispose();

						/**
						 * @brief	Initializes this object.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 */

						void Initialize();

						/**
						 * @brief	Gets the window title.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	The window title.
						 */

						std::string GetWindowTitle();

						/**
						 * @brief	Gets the menu option type.
						 *
						 * @author	Luiggi.mendez
						 * @date	28/04/2011
						 *
						 * @return	The menu option type.
						 */

						Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

						/**
						 * @brief	Execute background process for close votation functionality.
						 *
						 * @author	Gerardo.Hernandez
						 * @date	10/06/2011
						 *
						 */
						virtual void ExcuteBackgroundProcess();

						static Smartmatic::Log::ISMTTLog* logger;
				};
			}
		}
	}
}

#endif /* SHUTDOWNMACHINEFUNCTIONALITY_H_ */
