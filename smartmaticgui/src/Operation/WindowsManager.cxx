/**
 * @file WindowsManager.cxx
 * @brief Body class windows manager
 * @date 26/03/2012
 * @author Yadickson Soto
 */

#include "WindowsManager.hxx"
#include "Windows/basic-window.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::GUI::Operation;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;

WindowsManager * WindowsManager::instance = NULL;

#define LOGGER_PROJECT "Smartmatic.GUI.Operation.WindowsManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* WindowsManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE); ///< The logger
#else
ISMTTLog* WindowsManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,""); ///< The logger
#endif

WindowsManager::WindowsManager()
{

}

WindowsManager::~WindowsManager()
{

}

void WindowsManager::push(BasicWindow * window)
{
	logger->Debug("Push new window");
	staticWindows.push_back(window);
}

BasicWindow * WindowsManager::pop()
{
	BasicWindow * window = current();

	if (window)
	{
		logger->Debug("Pop window");
		staticWindows.pop_back();
	}

	return window;
}

BasicWindow * WindowsManager::current()
{
	BasicWindow * window = NULL;

	if (staticWindows.size() > 0)
	{
		window = staticWindows.back();
	}

	return window;
}

WindowsManager * WindowsManager::getInstance()
{
	if (!instance)
	{
		instance = new WindowsManager();
	}
	return instance;
}
