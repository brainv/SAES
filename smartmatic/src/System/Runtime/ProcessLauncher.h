/*
 * ProcessLauncher.h
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#ifndef PROCESSLAUNCHER_H_
#define PROCESSLAUNCHER_H_

#include <glibmm.h>
#include <vector>

namespace Smartmatic {

namespace System {

namespace Runtime
{
/**
	 * @class	ProcessLauncher
	 *
	 * @brief	Class definition file.
	 *
	 * @author	Freddy Gomez &lt;fgomez@smartmatic.com&gt;
	 * @date	04-05-2011
	 */

class ProcessLauncher {
public:
	/**
	 * @brief	Default Constructor
	 *
	 * @author	Freddy Gomez
	 * @date	04-05-2011
	 *
	 *
	 */
	ProcessLauncher();
	/**
		 * @brief	Class destructor.
		 *
		 * @author	Freddy Gomez
		 * @date	04/05/2011
		 *
		 *
		 */
	virtual ~ProcessLauncher();

	/**
	 * @brief	This method run the process specified in the command line using the popen/pclose function.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	commandLineWithArguments	process command line with arguments.
	 * @return	The data taken from the stdout of the process.
	 *
	 */
	static std::vector<Glib::ustring> RunProcessThroughPipe(Glib::ustring commandLineWithArguments);

	/**
	 * @brief	This method run the process specified in the command line using the system function.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	commandLineWithArguments	process command line with arguments.
	 * @return	The same return value of the "system" function.
	 *
	 */
	static int RunProcessThroughSystem(Glib::ustring commandLineWithArguments);
};

}
}
}

#endif /* PROCESSLAUNCHER_H_ */
