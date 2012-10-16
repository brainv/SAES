/**
 * @file	empty-window.cc
 * @brief	Body the empty Windows Form.
 * @date	03/04/2012
 * @author	Yadickson Soto
 */

/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "empty-window.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Functionalities/saes-functionality.h"
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/HelpWidget.hxx>
#include <Gui/Widgets/MemoryStateWidget.hxx>
#include <Gui/Widgets/AbstractFactoryWidget.hxx>
#include <Runtime/Environment/MemoryPathController.h>
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* EmptyWindow::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.EmptyWindow",GETTEXT_PACKAGE);

EmptyWindow::EmptyWindow(StepWidget * stepWidget)
: BasicWindow(false, false)
{
	initConfig();
	pushStepWidget(stepWidget);
}

EmptyWindow::EmptyWindow(Gtk::Widget * widget, std::string title, bool showTitleText, bool showHelpButton, bool showExitButton)
: BasicWindow(false, showTitleText)
{
	initConfig();

	stepWidget.setTitleText(title);
	stepWidget.setTitle(showTitleText);
	stepWidget.setHelp(showHelpButton);
	stepWidget.setExit(showExitButton);
	stepWidget.setWidget(widget);

	pushStepWidget(&stepWidget);
}

EmptyWindow::~EmptyWindow()
{
	this->remove();

	if (memoryStateWidget)
	{
		delete memoryStateWidget;
		memoryStateWidget = NULL;
	}

	BasicWindow::dispose();
}

void EmptyWindow::initConfig()
{
	this->block = false;
	this->viewInitMessage = false;
	this->viewExitMessage = false;
	this->oneMemory = false;
	this->viewHelpWidget = false;
	this->viewMemoryStateWidget = false;

	LaunchConfiguration& launchConfig(SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());
	AppType apptoLaunch = launchConfig.getAppType();

	RulesBasePathType & rule = MemoryPathController::getInstance()->getRule();
    forceHide = rule != RulesBasePathType::CONFIGURATION_PM_RULE || apptoLaunch != AppType::CONFIGURATION_POLLBOOKONLY;

	this->memoryStateWidget = AbstractFactoryWidget::createMemoryStateWidget();

	Gdk::Color color("black");
	setTitleColor(color);

	std::string fileImage = Smartmatic::Environment::ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/one-memory-small.gif");
	setTitleImage(fileImage);
    setTitleLabelConfiguration(SAESGUIConfigurationManager::Current()->GetEmptyWindowTitleFormConfiguration());

	memoryStateWidget->getSignalOneMemory().connect(sigc::mem_fun(*this, &EmptyWindow::OneMemoryOperation));
	memoryStateWidget->getSignalTwoMemory().connect(sigc::mem_fun(*this, &EmptyWindow::TwoMemoryOperation));
	memoryStateWidget->getSignalBlock().connect(sigc::mem_fun(*this, &EmptyWindow::memoryBlock));
	memoryStateWidget->getSignalVerify().connect(sigc::mem_fun(*this, &EmptyWindow::memoryVerify));

	memoryStateWidget->getSignalStartWidget().connect(sigc::mem_fun(*this, &EmptyWindow::showMemoryState));
	memoryStateWidget->getSignalAllow().connect(sigc::mem_fun(*this, &EmptyWindow::restoreOneMemory));
	memoryStateWidget->getSignalEnd().connect(sigc::mem_fun(*this, &EmptyWindow::restoreTwoMemory));
}

void EmptyWindow::memoryBlock()
{
	setBlockPopPush(true);

	logger->Debug("memory block");
	block = true;

	StateListener * state = getCurrentWidget()->getStateListener();

	if (state)
	{
		state->block();
	}
}

void EmptyWindow::memoryVerify()
{
	logger->Debug("memory verify");

	refreshStepWidget();
}

void EmptyWindow::OneMemoryOperation()
{
	this->oneMemory = true;

	Gdk::Color color("red");
	setTitleColor(color);
	disableExitButton();
	showTitleImage();
}

void EmptyWindow::TwoMemoryOperation()
{
	if (forceHide)
	{
		return;
	}

	Gdk::Color color("black");
	setTitleColor(color);
	enableExitButton();
	hideTitleImage();

	this->oneMemory = false;
}

void EmptyWindow::showInitMessageWidget(InfoStepWidget & widget)
{
	if (!viewInitMessage)
	{
		logger->Debug("init message widget");
		viewInitMessage = true;
		showMessageWidget(widget);
	}
}

void EmptyWindow::showExitMessageWidget(InfoStepWidget & widget)
{
	if (!viewExitMessage)
	{
		logger->Debug("exit message widget");
		popStepWidget();
		viewExitMessage = true;
		showMessageWidget(widget);
	}
}

void EmptyWindow::showMessageWidget(InfoStepWidget & widget)
{
	pushStepWidget(&widget);
	disableHelpButton();
	disableExitButton();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &EmptyWindow::exitMessage),widget.getTimeout());
}

void EmptyWindow::ShowHelp()
{
	Glib::Mutex::Lock lock(mutex);
	viewHelpWidget = true;
	BasicWindow::ShowHelp();
}

void EmptyWindow::exitMessage()
{
	if (!block)
	{
		viewInitMessage = false;
		viewExitMessage = false;
		Exit();
	}
}

void EmptyWindow::ShowExit()
{
	Glib::Mutex::Lock lock(mutex);

	signalShowExitMessage.emit();

	StepWidget * widget = getCurrentWidget();

	if (!viewExitMessage && widget && widget->getExitWidget())
	{
		InfoStepWidget * widgetExit = (InfoStepWidget * )widget->getExitWidget();
		showExitMessageWidget (*widgetExit);
	}
	else
	{
		exitMessage();
	}
}

void EmptyWindow::Exit()
{
	if (viewHelpWidget)
	{
		viewHelpWidget = false;
		BasicWindow::Exit();
	}
	else if(!oneMemory || forceHide)
	{
		BasicWindow::Exit();
		signalExitButton.emit();
	}

	enableExitButton();
}

void EmptyWindow::showMemoryState()
{
	Glib::Mutex::Lock lock(mutex);

	if (!viewMemoryStateWidget)
	{
		block = true;
		viewMemoryStateWidget = true;
		pushStepWidget(memoryStateWidget, true);
	}

	hideTitleImage();
}

void EmptyWindow::restoreOneMemory()
{
	restore(true);

	StateListener * state = getCurrentWidget()->getStateListener();

	if (state)
	{
		state->partial();
	}
}

void EmptyWindow::restoreTwoMemory()
{
	restore(false);

	StateListener * state = getCurrentWidget()->getStateListener();

	if (state)
	{
		state->resume();
	}
}

void EmptyWindow::restore(bool oneMemory)
{
	this->oneMemory = oneMemory;
	block = false;

	if (viewMemoryStateWidget)
	{
		popStepWidget(true);
		setBlockPopPush(false);
		viewMemoryStateWidget = false;
		enableExitButton();

		if (!viewInitMessage && !viewExitMessage)
		{
			return;
		}
	}

	if (oneMemory)
	{
		showTitleImage();
	}
	else
	{
		Gdk::Color color("black");
		setTitleColor(color);
		hideTitleImage();

		exitMessage();
	}

	enableExitButton();
}

void EmptyWindow::enableExitButton()
{
	StepWidget * widget = getCurrentWidget();

	if (widget)
	{
		setExitButtonSensitive((!oneMemory || viewHelpWidget) && widget->isExitSensitive());
	}
	else
	{
		setExitButtonSensitive(true);
	}
}

void EmptyWindow::refreshTitleText()
{
	StepWidget * widget = getCurrentWidget();

	if (widget)
	{
		setTitleText(_(widget->getTitleText().c_str()));
	}
}

sigc::signal<void> EmptyWindow::getSignalShowExitMessage()
{
	return signalShowExitMessage;
}

sigc::signal<void> EmptyWindow::getSignalExitButton()
{
	return signalExitButton;
}
