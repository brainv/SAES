/**
 * @file ZenityWrapper.cxx
 * @brief Body class zenity wrapper
 * @date 23/02/2012
 * @author Yadickson Soto
 */

#include "ZenityWrapper.hxx"
#include <System/Runtime/ProcessLauncher.h>
#include <sstream>

using namespace Smartmatic::System;
using namespace Smartmatic::System::Runtime;

ZenityWrapper::ZenityWrapper()
{

}

ZenityWrapper::~ZenityWrapper()
{

}

void ZenityWrapper::showError(std::string message, std::string title)
{
	std::stringstream ss;
	ss << "zenity --error ";
	ss << "--text=\"";
	ss << message;
	ss << "\" ";
	ss << "--title=\"";
	ss << title;
	ss << "\" &";

	(void)ProcessLauncher::RunProcessThroughSystem(ss.str());
}

void ZenityWrapper::showWarning(std::string message, std::string title, int timeout)
{
	std::stringstream ss;
	ss << "zenity --warning ";
	ss << "--text=\"";
	ss << message;
	ss << "\" ";
	ss << "--title=\"";
	ss << title;
	ss << "\" ";
	ss << "--timeout ";
	ss << timeout;
	ss << " & ";

	(void)ProcessLauncher::RunProcessThroughSystem(ss.str());
}

void ZenityWrapper::showInfo(std::string message, std::string title, int timeout)
{
	std::stringstream ss;
	ss << "zenity --info ";
	ss << "--text=\"";
	ss << message;
	ss << "\" ";
	ss << "--title=\"";
	ss << title;
	ss << "\" ";
	ss << "--timeout ";
	ss << timeout;
	ss << " & ";

	(void)ProcessLauncher::RunProcessThroughSystem(ss.str());
}
