/*
 * ThreadSleep.cpp
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#include "System/Threading/ThreadSleep.h"
#include <glibmm.h>


using namespace Smartmatic::System::Threading;


ThreadSleep::ThreadSleep() {
	// TODO Auto-generated constructor stub

}

ThreadSleep::~ThreadSleep() {
	// TODO Auto-generated destructor stub
}

void ThreadSleep::Sleep(unsigned int milliseconds)
{
	Glib::Mutex condMutex;
	Glib::Cond condition;
	condMutex.lock();
	Glib::TimeVal wait_period(milliseconds/1000,milliseconds%1000);
	Glib::TimeVal abs_time;
	abs_time.assign_current_time();
	abs_time.add(wait_period);
	condition.timed_wait(condMutex, abs_time);
	condMutex.unlock();
}
