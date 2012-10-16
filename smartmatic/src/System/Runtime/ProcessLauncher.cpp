/*
 * ProcessLauncher.cpp
 *
 *  Created on: May 4, 2011
 *      Author: fgomez
 */

#include "System/Runtime/ProcessLauncher.h"
#include <stdio.h>

using namespace Smartmatic::System::Runtime;


ProcessLauncher::ProcessLauncher() {
	// TODO Auto-generated constructor stub

}

ProcessLauncher::~ProcessLauncher() {
	// TODO Auto-generated destructor stub
}


std::vector<Glib::ustring> ProcessLauncher::RunProcessThroughPipe(Glib::ustring commandLineWithArguments)
{

	std::vector<Glib::ustring> retVal;
	Glib::ustring line;
	FILE *in;

	char buff[512];

	/* popen creates a pipe so we can read the output
	     of the program we are invoking */
	if ((in = popen(commandLineWithArguments.c_str(), "r")) != NULL)
	{
		/* read the output of the process, one line at a time */
		while (fgets(buff, sizeof(buff), in) != NULL )
		{
			line.assign(buff);
			retVal.push_back(line);
		}

		/* close the pipe */
		pclose(in);
	}



	return retVal;
}


int ProcessLauncher::RunProcessThroughSystem(Glib::ustring commandLineWithArguments)
{
	return system(commandLineWithArguments.c_str());
}
