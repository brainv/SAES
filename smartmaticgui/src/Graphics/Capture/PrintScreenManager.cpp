/*
 * PrintScreenManager.cpp
 *
 *  Created on: Apr 7, 2011
 *      Author: Gerardo Hernandez
 */

#include "PrintScreenManager.h"
#include "System/IO/File.h"
#include <iostream>
#include <string>
#include <System/Runtime/ProcessLauncher.h>

using namespace Smartmatic::Graphics::Capture;
using namespace Smartmatic::System::IO;
using namespace std;
using namespace Smartmatic::System::Runtime;

PrintScreenManager::PrintScreenManager() {
	// TODO Auto-generated constructor stub

};

PrintScreenManager::~PrintScreenManager() {
	// TODO Auto-generated destructor stub
};

void PrintScreenManager::Capture(std::string windowID, std::string imageFullPath)
{
	size_t found;

	do
	{
		found = imageFullPath.find(" ");
		if(found != string::npos)
			imageFullPath.replace(found,1, "");
	}while(found != string::npos);

	std::string systemCallLine (("import -window " + windowID + " " + imageFullPath));
	(void)ProcessLauncher::RunProcessThroughSystem(systemCallLine.c_str());
};

void PrintScreenManager::CaptureRootScreen(std::string imageFolderFullPath)
{
	std::string systemCallLine ("import -window root rootscreen.png");
	(void)ProcessLauncher::RunProcessThroughSystem(systemCallLine.c_str());
};

std::vector<std::string> PrintScreenManager::GetWindows(std::vector<std::string> windowsPrefix)
{
	std::vector<std::string> windowsId;

	for(unsigned int index(0); index<windowsPrefix.size(); index++)
	{
		std::vector<std::string> tempWindows = GetWindows(windowsPrefix[index]);

		for(unsigned int y(0); y<tempWindows.size(); y++)
		{
			windowsId.push_back(tempWindows[y]);
		}
	}

	return windowsId;
};

bool PrintScreenManager::isComplete()
{
	while(ProcessLauncher::RunProcessThroughSystem("sudo ps -A | grep import") != 0)
	{

	}

	return true;
}

std::vector<std::string> PrintScreenManager::GetWindows(std::string windowPrefix)
{
	std::vector<std::string> windowsId;
	std::string fileName = "/tmp/temp-election.windows";
	std::string getWindowsCommand = "wmctrl -l > " + fileName;

	int i = ProcessLauncher::RunProcessThroughSystem(getWindowsCommand.c_str());

	if(i==0)
	{
		if(File::canOpenFile(fileName))
		{
			std::string fileContent;

			if(File::findLine(fileName, fileContent, windowPrefix))
			{
				windowsId.push_back(fileContent.substr(0, 11));
			}
			else
			{
				windowsId.push_back("root");
			}
		}
		else
		{

		}
	}
	else
	{

	}

	return windowsId;
};
