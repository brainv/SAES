/*
 * ThreadSleep.h
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#ifndef THREADSLEEP_H_
#define THREADSLEEP_H_


namespace Smartmatic{

namespace System{

namespace Threading
{

/**
	 * @class	ThreadSleep
	 *
	 * @brief	Class definition file.
	 *
	 * @author	Freddy Gomez &lt;fgomez@smartmatic.com&gt;
	 * @date	04-05-2011
	 */

class ThreadSleep {
public:

	/**
	 * @brief	Default Constructor
	 *
	 * @author	Freddy Gomez
	 * @date	04-05-2011
	 *
	 *
	 */
	ThreadSleep();
	/**
	 * @brief	Class destructor.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 *
	 */
	virtual ~ThreadSleep();
	/**
	 * @brief	Sleep the calling thread.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	milliseconds	time to sleep, in milliseconds.
	 *
	 */
	static void Sleep(unsigned int milliseconds);
};

}
}
}
#endif /* THREADSLEEP_H_ */
