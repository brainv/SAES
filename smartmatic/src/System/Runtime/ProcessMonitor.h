/*
 * ProcessMonitor.h
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#ifndef PROCESSMONITOR_H_
#define PROCESSMONITOR_H_
#include <string>

namespace Smartmatic {

namespace System {

namespace Runtime
{
/**
	 * @class	ProcessMonitor
	 *
	 * @brief	Class definition file.
	 *
	 * @author	Freddy Gomez &lt;fgomez@smartmatic.com&gt;
	 * @date	04-05-2011
	 */
class ProcessMonitor {
public:
	/**
		 * @brief	Default Constructor
		 *
		 * @author	Freddy Gomez
		 * @date	04-05-2011
		 *
		 *
		 */
	ProcessMonitor();
	/**
		 * @brief	Class destructor.
		 *
		 * @author	Freddy Gomez
		 * @date	04/05/2011
		 *
		 *
		 */
	virtual ~ProcessMonitor();


	/**
	 * @brief	This method counts the number of process which match the specified pattern.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	processSearchPattern	process search pattern.
	 * @return	The nuber of process which match the pattern.
	 *
	 */
	static int CountProcessRunning(std::string processSearchPattern);

	/**
	 * @brief	This method kill the process specified
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	pid		process identifier.
	 * @param [in]	asSudo	execute as sudo.
	 *
	 */
	static void KillProcess(int pid, bool asSudo = true);

	static void KillProcessAndWait(std::string processName, int count = 5, bool asSudo = false);

	/**
	 * @brief	Kill the process
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	processName	process full name.
	 * @param [in]	asSudo	execute as sudo.
	 *
	 */
	static void KillProcess(std::string processName, bool asSudo = true);

	/**
	 * @brief	This method Wait until the process finishes.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	processSearchPattern	process search pattern.
	 * @param [in]	timeout					wait timeout, -1 means infinite.
	 * @return	true whether the process exited, false whether timeout.
	 *
	 */
	static bool WaitForExit(std::string processSearchPattern, int timeout= -1);
};

}
}
}
#endif /* PROCESSMONITOR_H_ */
