/*
 * ProcessMonitor.cpp
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#include "System/Runtime/ProcessMonitor.h"
#include "System/Runtime/ProcessLauncher.h"
#include "System/Threading/ThreadSleep.h"

using namespace Smartmatic::System::Runtime;
using namespace Smartmatic::System::Threading;

ProcessMonitor::ProcessMonitor() {
	// TODO Auto-generated constructor stub

}

ProcessMonitor::~ProcessMonitor() {
	// TODO Auto-generated destructor stub
}


int ProcessMonitor::CountProcessRunning(std::string processSearchPattern)
{
	Glib::ustring command = "ps -A";

	if(processSearchPattern.size() > 0 && processSearchPattern != "*" )
	{
		command.append(" | grep ");
		command.append(processSearchPattern);
	}

	std::vector<Glib::ustring> out = ProcessLauncher::RunProcessThroughPipe(command);

	return out.size();
}

void ProcessMonitor::KillProcess(int pid, bool asSudo )
{
	Glib::ustring command;

	if(asSudo)
	{
		command = Glib::ustring::compose("sudo kill -9 %1", pid);
	}
	else
	{
		command = Glib::ustring::compose("kill -9 %1", pid);
	}

	ProcessLauncher::RunProcessThroughSystem(command);
}

void ProcessMonitor::KillProcess(std::string processName, bool asSudo )
{
	Glib::ustring command;

	if(asSudo)
	{
		command = Glib::ustring::compose("sudo pkill -9 %1", processName);
	}
	else
	{
		command = Glib::ustring::compose("pkill -9 %1", processName);
	}

	ProcessLauncher::RunProcessThroughSystem(command);
}

void ProcessMonitor::KillProcessAndWait(std::string processName, int count, bool asSudo)
{
	do
	{
		KillProcess(processName, asSudo);
		ThreadSleep::Sleep(500);
		count--;
	}
	while (count > 0 && CountProcessRunning(processName) > 0);
}

bool ProcessMonitor::WaitForExit(std::string processSearchPattern, int timeout)
{
	bool retVal = true;
	Glib::Timer stopWatch;
	bool running = CountProcessRunning(processSearchPattern) > 0;
	while(running)
	{
		if(timeout != -1)
		{
			ThreadSleep::Sleep(600);
			int elapsed = (int)stopWatch.elapsed();
			if(elapsed > timeout)
			{
				retVal = false;
				break;
			}
		}

		running = CountProcessRunning(processSearchPattern) > 0;

	}
	return retVal;
}
