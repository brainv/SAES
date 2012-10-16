/*
 * ReportPrintingFunctionality.h
 *
 *  Created on: Apr 20, 2011
 *      Author: root
 */

#ifndef REPORTPRINTINGFUNCTIONALITY_H_

/**
 * @brief	Gets the reportprintingfunctionality h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define REPORTPRINTINGFUNCTIONALITY_H_


#include <gtkmm.h>
#include <Widgets/menu-option.h>
#include <Functionalities/graphic-display-functionality.h>
//#include <Functionalities/saes-menu-option-descriptor.h>
#include <vector>
#include <iostream>

#include <Log/ISMTTLog.h>
#include <Printing/ReportPrintingController.h>
#include "Gui/Widgets/ReportPrintingWidget.h"


namespace Smartmatic
{
namespace SAES
{
namespace GUI
{
namespace Functionality
{

class ReportPrintingFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
{
public:

	// Life Cycle

	/**
	 * @brief	Finaliser.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 */

	virtual ~ReportPrintingFunctionality();

	/**
	 * @brief	returns singleton instance.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 *
	 * @return	null if it fails, else.
	 */

	static ReportPrintingFunctionality* Current ();

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
	 * @brief	Gets the window title.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 *
	 * @return	The window title.
	 */

	std::string GetWindowTitle();


	// GraphicDisplayFunctionality abstract method implementation

	/**
	 * @brief	Gets the frame.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 *
	 * @return	null if it fails, else the frame.
	 */

	Gtk::Widget* GetFrame();

	/**
	 * @brief	Dispose of this object, cleaning up any resources it uses.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 */

	void Dispose();

	/**
	 * @brief	Initializes this object.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 */

	void Initialize();

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
	 * @brief virtual method delete all element
	 * @date 03/04/2012
	 * @author Yadickson Soto
	 */
	virtual void deleteElement();

protected:

	/**
	 * @brief	Default constructor.
	 *
	 * @author	Luiggi.mendez
	 * @date	28/04/2011
	 */

	ReportPrintingFunctionality();

private:

	void BeginPrint();
	void EndPrint(bool succes);

	Smartmatic::SAES::GUI::Widgets::ReportPrintingWidget* m_ReportPrintingWidget;   ///< The report printing widget

	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
	static ReportPrintingFunctionality* current_instance;   ///< The current instance

};

}
}
}
}

#endif /* REPORTPRINTINGFUNCTIONALITY_H_ */
