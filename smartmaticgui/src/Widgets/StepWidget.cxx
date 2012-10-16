/**
 * @file StepWidget.cxx
 * @brief Body class step widget
 * @date 08/03/2012
 * @author Yadickson Soto
 */

#include "StepWidget.hxx"

using namespace Smartmatic::GUI::Widgets;

StepWidget::StepWidget()
: Gtk::EventBox()
{
	titleKey = " ";
	name = "election";

	showTitle = true;
	showBottom = false;
	showHelp = false;
	showExit = false;
	showBorder = true;

	helpSensitive = true;
	exitSensitive = true;

	helpWidget = NULL;
	exitWidget = NULL;
	refreshListener = NULL;
	stateListener = NULL;
}

StepWidget::~StepWidget()
{
	this->remove();
}

std::string StepWidget::getTitleText()
{
	return titleKey;
}

void StepWidget::setTitleText(std::string titleKey)
{
	this->titleKey = titleKey;
}

std::string StepWidget::getBottomText()
{
	return bottomKey;
}

void StepWidget::setBottomText(std::string bottomKey)
{
	this->bottomKey = bottomKey;
}

bool StepWidget::isTitle()
{
	return showTitle;
}

void StepWidget::setTitle(bool showTitle)
{
	this->showTitle = showTitle;
}

bool StepWidget::isBottom()
{
	return showBottom;
}

void StepWidget::setBottom(bool showBottom)
{
	this->showBottom = showBottom;
}

bool StepWidget::isHelp()
{
	return showHelp;
}

void StepWidget::setHelp(bool showHelp)
{
	this->showHelp = showHelp;
}

bool StepWidget::isExit()
{
	return showExit;
}

void StepWidget::setExit(bool showExit)
{
	this->showExit = showExit;
}

bool StepWidget::isHelpSensitive()
{
	return helpSensitive;
}

void StepWidget::setHelpSensitive(bool helpSensitive)
{
	this->helpSensitive = helpSensitive;
}

bool StepWidget::isExitSensitive()
{
	return exitSensitive;
}

void StepWidget::setExitSensitive(bool exitSensitive)
{
	this->exitSensitive = exitSensitive;
}

void StepWidget::setWidget(Gtk::Widget * mainWidget)
{
	if (mainWidget)
	{
		this->remove();
		this->add(*mainWidget);
		this->show_all_children();
	}
}

void StepWidget::setHelpWidget(StepWidget * helpWidget)
{
	this->helpWidget = helpWidget;
}

StepWidget * StepWidget::getHelpWidget()
{
	return helpWidget;
}

void StepWidget::setExitWidget(StepWidget * exitWidget)
{
	this->exitWidget = exitWidget;
}

StepWidget * StepWidget::getExitWidget()
{
	return exitWidget;
}

void StepWidget::initialize()
{

}

void StepWidget::dispose()
{

}

void StepWidget::refresh()
{

}

bool StepWidget::isShowBorder()
{
	return showBorder;
}

void StepWidget::setShowBorder(bool showBorder)
{
	this->showBorder = showBorder;
}

std::string StepWidget::getName()
{
	return name;
}

void StepWidget::setName(std::string name)
{
	this->name = name;
}

void StepWidget::setRefreshListener(RefreshListener * refreshListener)
{
	this->refreshListener = refreshListener;
}

RefreshListener * StepWidget::getRefreshListener()
{
	return refreshListener;
}

void StepWidget::setStateListener(StateListener * stateListener)
{
	this->stateListener = stateListener;
}

StateListener * StepWidget::getStateListener()
{
	return stateListener;
}

sigc::signal<void> StepWidget::getSignalEnd()
{
	return signalEnd;
}

void StepWidget::SetKey(KeysActionsCode value)
{

}
