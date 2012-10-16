/**
 * @file basic-window.cc
 * @brief Body class basic window
 * @date 26/03/2012
 * @author Yadickson Soto
 */

#include "basic-window.h"
#include <iostream>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Widgets/HelpExitButtons.h>
#include <Widgets/StepWidget.hxx>
#include <Operation/WindowsManager.hxx>

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

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <Operation/WindowsManager.hxx>

using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Operation;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;

#define LOGGER_PROJECT "Smartmatic.GUI.Windows.BasicWindow" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* BasicWindow::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE); ///< The logger
#else
ISMTTLog* BasicWindow::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,""); ///< The logger
#endif

BasicWindow::BasicWindow(bool useHeaderFrame, bool useTitleFrame, bool isModal, Gtk::WindowType type)
: Gtk::Window(type)
{
	this->isModal = isModal;
	blockState = false;
	mainVbox = NULL;
	headerFrame = NULL;
	titleeventbox = NULL;
	titleFrame = NULL;
	clientAreaEventBox = NULL;
	clientArea = NULL;
	bottomFrame = NULL;
	keywordInterface = NULL;
	titleImage = NULL;
	titleLabel = NULL;
	bottomLabel = NULL;
	titleHbox = NULL;
	titleHelpEventbox = NULL;
	bottomEventBox = NULL;
	helpExitButtons = NULL;

	this->useHeaderFrame = useHeaderFrame;
	this->useTitleFrame = useTitleFrame;
	this->useBottomFrame = false;

    helpExitButtons = new HelpExitButtons(this, false, this, false);
	helpExitButtons->show();

	formheight = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getHeight());
	formwidth = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getWidth());
	panelHeaderHeight = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getHeaderHeight());
	panelTitleHeight = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getTitleHeight());
	panelBottomHeight = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getBottomHeight());
	panelsPaddingX = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getHorizontalPadding());
	panelsPaddingY = ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getVerticalPadding());

	set_modal(isModal);
	set_skip_taskbar_hint(true);	//Hides the window from the lower task bar
	set_skip_pager_hint(true);
	set_default_size(formwidth,formheight);
	set_size_request(formwidth,formheight);
	set_border_width(0);
	set_position(Gtk::WIN_POS_CENTER);
	set_decorated(false);
	set_can_focus(true);
	set_resizable(false);
	set_keep_above(false);

	signal_key_press_event().connect(sigc::mem_fun(*this, &BasicWindow::key_pressed));

	//TODO: End of configuration values to be readed from the GUIUtilsClass
	navigationMode = ShortcutNavigation;

	currentWidget = NULL;

	initialize();
	resizeComponents();
	setTitleHelp(helpExitButtons);
	showTitleHelp();

	if (!useTitleFrame)
	{
		hideTitle();
	}

	remove();
	add(*mainVbox);

	setBorderVisible(true);
}

BasicWindow::~BasicWindow ()
{
	dispose();
}

void BasicWindow::ShowDialog()
{
	WindowsManager::getInstance()->push(this);
	show();
	Gtk::Main::run();
}

void BasicWindow::QuitDialog()
{
	WindowsManager::getInstance()->pop();
	Gtk::Main::quit();
}

void BasicWindow::getWindowSize (int& width, int& height)
{
	width = formwidth;
	height = formheight;
}

void BasicWindow::getContentSize (int& width, int& height)
{
	clientArea->get_size_request(width,height);
}

void BasicWindow::getTitleSize (int& width, int& height)
{
	titleFrame->get_size_request(width,height);
}

void BasicWindow::getHeaderSize (int& width, int& height)
{
	headerFrame->get_size_request(width,height);
}

void BasicWindow::getBottomSize (int& width, int& height)
{
	bottomFrame->get_size_request(width,height);
}

void BasicWindow::initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/BasicWindow.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - BasicWindow Initialize");
	}

	builder->get_widget("main-vbox", mainVbox);
	builder->get_widget("header-frame", headerFrame);
	builder->get_widget("title-eventbox", titleeventbox);
	builder->get_widget("title-frame", titleFrame);
	builder->get_widget("center-eventbox", clientAreaEventBox);
	builder->get_widget("center-frame", clientArea);
	builder->get_widget("bottom-frame", bottomFrame);
	builder->get_widget("bottom-label", bottomLabel);
	builder->get_widget("title-image", titleImage);
	builder->get_widget("title-label", titleLabel);
	builder->get_widget("title-hbox", titleHbox);
	builder->get_widget("title-help-eventbox", titleHelpEventbox);
	builder->get_widget("bottom-eventbox", bottomEventBox);

	mainVbox->set_spacing(panelsPaddingY);
	mainVbox->set_border_width(panelsPaddingX);

	bottomLabel->set_no_show_all();
	titleLabel->set_no_show_all();
	titleImage->set_no_show_all();
	headerFrame->set_no_show_all();
	titleeventbox->set_no_show_all();
	titleFrame->set_no_show_all();
	bottomFrame->set_no_show_all();
	titleHelpEventbox->set_no_show_all();
	titleHbox->set_no_show_all();
	bottomEventBox->set_no_show_all();

	titleImage->set_visible(false);
	headerFrame->set_visible(false);
	titleeventbox->set_visible(false);
	bottomEventBox->set_visible(false);
	titleHelpEventbox->set_visible(false);

	titleeventbox->set_name("base_window_title_event_box");
	titleLabel->set_text("");

	bottomEventBox->set_name("base_window_title_event_box");
	bottomLabel->set_text("");

	mainVbox->show_all_children();
}

void BasicWindow::dispose()
{
	this->remove();

	if(mainVbox)
	{
		delete mainVbox;
		mainVbox = NULL;
	}
	if(headerFrame)
	{
		delete headerFrame;
		headerFrame = NULL;
	}
	if(titleFrame)
	{
		delete titleFrame;
		titleFrame = NULL;
	}
	if(titleeventbox)
	{
		delete titleeventbox;
		titleeventbox = NULL;
	}
	if (clientAreaEventBox)
	{
		delete clientAreaEventBox;
		clientAreaEventBox = NULL;
	}
	if (clientArea)
	{
		delete clientArea;
		clientArea = NULL;
	}
	if (bottomFrame)
	{
		delete bottomFrame;
		bottomFrame = NULL;
	}
	if (titleLabel)
	{
		delete titleLabel;
		titleLabel = NULL;
	}
	if (titleImage)
	{
		delete titleImage;
		titleImage = NULL;
	}
	if (titleHbox)
	{
		delete titleHbox;
		titleHbox = NULL;
	}
	if (titleHelpEventbox)
	{
		delete titleHelpEventbox;
		titleHelpEventbox = NULL;
	}
	if (bottomEventBox)
	{
		delete bottomEventBox;
		bottomEventBox = NULL;
	}
	if (helpExitButtons)
	{
		delete helpExitButtons;
		helpExitButtons = NULL;
	}
	if (bottomLabel)
	{
		delete bottomLabel;
		bottomLabel = NULL;
	}

	stepWidgetList.clear();
}

bool BasicWindow::key_pressed(GdkEventKey *event)
{				
	//KeysActionsCode keyAction = OperationKey::Current()->GetKeyActionCode(CustomKeys::KeysCode(event->keyval));
	
	if(BasicWindow::navigationMode == SimpleNavigation)
	{
		/*
		switch (keyAction)
		{
			case PK_4:
				MoveLeft();
				break;
			case PK_6:
				MoveRight();
				break;		
			case PK_5:
				Enter();
				break;	
			case PK_8:
				MoveDown();
				break;
			case PK_2:
				MoveUp();
				break;
			case PK_Asterisk:
				//TODO:Implementar AYUDA
				break;
            default: break;
		}
		*/
	}
	else
	{	
		//verificamos si la tecla presionada es para cerrar la entana
		/*
		if(keyAction == GetKeyvalCloseConfiguration() && keywordInterface != 0 && exitButton)
		{
			if(timeExitElapsed)
			{
				on_exit_button_clicked();
			}
		}
	
		else
		*/
		{
			/*
			if(keyAction == GetKeyvalHelpConfiguration() && keywordInterface != 0)
			{
				//Levantamos la ventana de ayuda
			}

			else
			{
			*/
				try
				{
					if(keywordInterface)
					{
						keyCode = KeysActionsCode(event->keyval);
						keywordInterface->SetKey(keyCode);
					}
				}
				catch(std::bad_exception&)
				{

				}
			//}
		}
	}
	return false;
}

void BasicWindow::FillValidKeys()
{
	/*
	validKeys.push_back(PK_1);
	validKeys.push_back(PK_2);
	validKeys.push_back(PK_3);
	validKeys.push_back(PK_4);
	validKeys.push_back(PK_5);
	validKeys.push_back(PK_6);
	validKeys.push_back(PK_7);
	validKeys.push_back(PK_8);
	validKeys.push_back(PK_9);
	validKeys.push_back(PK_Plus);
	validKeys.push_back(PK_Minus);
	*/
}

bool BasicWindow::IsValidKey(int keyval)
{
	//if(keyval == PK_Invalid)
	//	return FALSE;
	return TRUE;
}

int BasicWindow::GetKeyvalCloseConfiguration()
{
	//return 	PK_Minus;
	return 0;
}

int BasicWindow::GetKeyvalHelpConfiguration()
{
	//return PK_Asterisk;
	return 0;
}

void BasicWindow::MoveLeft()
{
	Display *display;
//	unsigned int keycode = 113;
	display = XOpenDisplay(NULL);
	//XTestFakeKeyEvent(display, keycode, True, 0);
	//XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	XCloseDisplay(display);

}

void BasicWindow::MoveDown()
{
	Display *display;
//	unsigned int keycode = 116;
	display = XOpenDisplay(NULL);
	//XTestFakeKeyEvent(display, keycode, True, 0);
	//XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	XCloseDisplay(display);
}

void BasicWindow::MoveRight()
{
	Display *display;
//	unsigned int keycode = 114;
	display = XOpenDisplay(NULL);
	//XTestFakeKeyEvent(display, keycode, True, 0);
	//XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	XCloseDisplay(display);
}

void BasicWindow::Enter()
{
	Display *display;
	//unsigned int keycode = 36;
	display = XOpenDisplay(NULL);
	//XTestFakeKeyEvent(display, keycode, True, 0);
	//XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	XCloseDisplay(display);
}

void BasicWindow::MoveUp()
{
	Display *display;
//	unsigned int keycode = 111;
	display = XOpenDisplay(NULL);
	//XTestFakeKeyEvent(display, keycode, True, 0);
	//XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	XCloseDisplay(display);
}

bool BasicWindow::on_delete_event( GdkEventAny* G_GNUC_UNUSED )
{
	return true;
}

Gtk::Frame& BasicWindow::getHeaderFrame()
{
	return *(this->headerFrame);
}

Gtk::Frame& BasicWindow::getTitleFrame()
{
	return *(this->titleFrame);
}

Gtk::Frame& BasicWindow::getClientAreaFrame()
{
	return *(this->clientArea);
}

Gtk::Frame& BasicWindow::getBottomFrame()
{
	return *(this->bottomFrame);
}

void BasicWindow::showHeader()
{
	useHeaderFrame = true;
	resizeComponents();
}

void BasicWindow::showTitle()
{
	useTitleFrame = true;
	resizeComponents();
}

void BasicWindow::showBottom()
{
	useBottomFrame = true;
	resizeComponents();
}

void BasicWindow::hideHeader()
{
	useHeaderFrame = false;
	resizeComponents();
}

void BasicWindow::hideTitle()
{
	useTitleFrame = false;
	resizeComponents();
}

void BasicWindow::hideBottom()
{
	useBottomFrame = false;
	resizeComponents();
}

void BasicWindow::resizeComponents()
{
	panelHeaderWidth = formwidth - 2 * panelsPaddingX;
	panelTitleWidth = panelHeaderWidth;
	panelBottomWidth = panelHeaderWidth;
	panelClientWidth = panelHeaderWidth;

	panelClientHeight = formheight - 2 * panelsPaddingY;

	//subtract the panels padding
	if(useHeaderFrame)
	{
		panelClientHeight -= panelsPaddingY + panelHeaderHeight;
	}
	if (useTitleFrame)
	{
		panelClientHeight -= panelsPaddingY + panelTitleHeight;
	}
	if (useBottomFrame)
	{
		panelClientHeight -= panelsPaddingY + panelBottomHeight;
	}

	this->headerFrame->set_size_request(panelHeaderWidth, panelHeaderHeight);
	this->headerFrame->set_border_width(0);

	this->titleFrame->set_size_request(panelTitleWidth, panelTitleHeight);
	this->titleFrame->set_border_width(0);
	this->titleeventbox->show_all();

	this->bottomFrame->set_size_request(panelBottomWidth, panelBottomHeight);
	this->bottomFrame->set_border_width(0);
	this->bottomEventBox->show_all();

	this->clientArea->set_size_request(panelClientWidth, panelClientHeight);

	headerFrame->set_visible(useHeaderFrame);
	titleeventbox->set_visible(useTitleFrame);
	bottomEventBox->set_visible(useBottomFrame);
}

void BasicWindow::setPosition(int x, int y)
{
	set_position(Gtk::WIN_POS_NONE);
	move(x, y);
}

void BasicWindow::setPosition(PositionWindow position)
{
	set_position(Gtk::WIN_POS_NONE);
	get_size_request(formwidth,formheight);

	switch(position)
	{
		case TOP_RIGHT:
			move(Gdk::Screen::get_default()->get_width() - formwidth, 0);
			break;
		case TOP_LEFT:
			move(0, 0);
			break;
		case TOP_CENTER:
			move((Gdk::Screen::get_default()->get_width() - formwidth) / 2, 0);
			break;
		case CENTER_RIGHT:
			move(Gdk::Screen::get_default()->get_width() - formwidth, (Gdk::Screen::get_default()->get_height() - formheight) / 2);
			break;
		case CENTER_LEFT:
			move(0, (Gdk::Screen::get_default()->get_height() - formheight) / 2);
			break;
		case CENTER_CENTER:
			move((Gdk::Screen::get_default()->get_width() - formwidth) / 2, (Gdk::Screen::get_default()->get_height() - formheight) / 2);
			break;
		case BOTTOM_RIGHT:
			move(Gdk::Screen::get_default()->get_width() - formwidth, Gdk::Screen::get_default()->get_height() - formheight);
			break;
		case BOTTOM_LEFT:
			move(0, Gdk::Screen::get_default()->get_height() - formheight);
			break;
		case BOTTOM_CENTER:
			move((Gdk::Screen::get_default()->get_width() - formwidth) / 2, Gdk::Screen::get_default()->get_height() - formheight);
			break;
		default:
			break;
	}
}

void BasicWindow::setTitleLabelConfiguration(LabelConfiguration lblConfig)
{
	LabelConfiguration::SetLabelConfiguration(titleLabel, lblConfig);
}

void BasicWindow::setBottomLabelConfiguration(LabelConfiguration lblConfig)
{
	LabelConfiguration::SetLabelConfiguration(bottomLabel, lblConfig);
}

void BasicWindow::setTitleText(std::string title)
{
	titleLabel->set_text(title);
}

void BasicWindow::setTitleColor(Gdk::Color & color)
{
	titleLabel->modify_fg(Gtk::STATE_NORMAL, color);
}

void BasicWindow::setBottomText(std::string bottom)
{
	bottomLabel->set_text(bottom);
}

void BasicWindow::showTitleImage()
{
	titleImage->show();
	showTitle();
}

void BasicWindow::hideTitleImage()
{
	titleImage->hide();
}

void BasicWindow::setTitleImage(std::string image)
{
	titleImage->set(Gdk::PixbufAnimation::create_from_file(image));
}
void BasicWindow::showTitleHelp()
{
	titleHelpEventbox->show();
	titleHelpEventbox->show_all_children();
	showTitle();
}

void BasicWindow::hideTitleHelp()
{
	titleHelpEventbox->hide();
}

void BasicWindow::setTitleHelp(Gtk::Widget * widget)
{
	titleHelpEventbox->remove();
	titleHelpEventbox->add(*widget);
}

void BasicWindow::setTitle(Gtk::Widget * widget)
{
	titleFrame->remove();

	if (widget)
	{
		titleFrame->add(*widget);
		widget->show();
	}

	titleFrame->show_all_children();
}

void BasicWindow::setWidget(Gtk::Widget * widget)
{
	clientArea->remove();

	if (widget)
	{
		clientArea->add(*widget);
		widget->show();
	}

	clientArea->show_all_children();
}

void BasicWindow::setBottom(Gtk::Widget * widget)
{
	bottomFrame->remove();

	if (widget)
	{
		bottomFrame->add(*widget);
		widget->show();
	}

	bottomFrame->show_all_children();
}

void BasicWindow::setExitButtonSensitive (bool sensitive)
{
	helpExitButtons->ExitButton_SetSensitive(sensitive);
}

void BasicWindow::setExitButtonVisible (bool visible)
{
	helpExitButtons->ExitButton_SetVisible(visible);
}

void BasicWindow::setHelpButtonSensitive (bool sensitive)
{
	helpExitButtons->HelpButton_SetSensitive(sensitive);
}

void BasicWindow::setHelpButtonVisible (bool visible)
{
	helpExitButtons->HelpButton_SetVisible(visible);
}

void BasicWindow::setBorderVisible(bool visible)
{
	if (visible)
	{
		titleFrame->set_shadow_type(Gtk::SHADOW_IN);
		clientArea->set_shadow_type(Gtk::SHADOW_IN);
		bottomFrame->set_shadow_type(Gtk::SHADOW_IN);
	}
	else
	{
		titleFrame->set_shadow_type(Gtk::SHADOW_NONE);
		clientArea->set_shadow_type(Gtk::SHADOW_NONE);
		bottomFrame->set_shadow_type(Gtk::SHADOW_NONE);
	}
}

void BasicWindow::enableHelpButton()
{
	setHelpButtonSensitive(true);
}

void BasicWindow::disableHelpButton()
{
	setHelpButtonSensitive(false);
}

void BasicWindow::enableExitButton()
{
	setExitButtonSensitive(true);
}

void BasicWindow::disableExitButton()
{
	setExitButtonSensitive(false);
}

void BasicWindow::pushStepWidget(StepWidget * widget, bool force)
{
	Glib::Mutex::Lock lock(mutex);

	if (!blockState || force)
	{
		logger->Debug("Push widget");
		stepWidgetList.push_back(widget);
		setStepWidget(widget);
	}
}

StepWidget * BasicWindow::popPushStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget, bool force)
{
	Glib::Mutex::Lock lock(mutex);
	StepWidget * lastWidget = NULL;

	if (!blockState || force)
	{
		if (stepWidgetList.size() > 1)
		{
			logger->Debug("Remove widget");
			lastWidget = stepWidgetList.back();
			stepWidgetList.pop_back();
		}

		logger->Debug("Push widget");
		stepWidgetList.push_back(widget);
		setStepWidget(widget);

	}

	return lastWidget;
}

StepWidget * BasicWindow::BasicWindow::popStepWidget(bool force)
{
	Glib::Mutex::Lock lock(mutex);
	StepWidget * widget = NULL;

	if (!blockState || force)
	{
		if (stepWidgetList.size() > 1)
		{
			logger->Debug("Remove widget");
			widget = stepWidgetList.back();
			stepWidgetList.pop_back();
			setStepWidget(stepWidgetList.back());
		}
		else
		{
			currentWidget = NULL;
			logger->Debug("Window clean");
		}
	}

	return widget;
}

void BasicWindow::setStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget)
{
	currentWidget = widget;

	if (widget)
	{
		refreshStepWidget();
		setWidget(widget);

		if (widget->isTitle())
		{
			showTitle();
		}
		else
		{
			hideTitle();
		}

		if (widget->isBottom())
		{
			showBottom();
		}
		else
		{
			hideBottom();
		}

		setKeywordNavigation(widget);
	}
	else
	{
		setKeywordNavigation(NULL);
		logger->Debug("ERROR set widget");
	}
}

void BasicWindow::ShowHelp()
{
	if (currentWidget && currentWidget->getHelpWidget())
	{
		logger->Debug("Show help");
		pushStepWidget(currentWidget->getHelpWidget());
	}
	else
	{
		logger->Debug("Not show help");
	}
}

void BasicWindow::ShowExit()
{
	if (currentWidget && currentWidget->getExitWidget())
	{
		logger->Debug("Show exit");
		pushStepWidget(currentWidget->getExitWidget());
	}
	else
	{
		logger->Debug("Not show exit");
	}
}

void BasicWindow::Exit()
{
	if (currentWidget && currentWidget->getExitWidget())
	{
		ShowExit();
	}
	else
	{
		logger->Debug("Exit");
		popStepWidget();
	}
}

void BasicWindow::refreshTitleText()
{
	if (currentWidget)
	{
		setTitleText(currentWidget->getTitleText());
	}
	else
	{
		logger->Debug("Not refresh title");
	}
}

void BasicWindow::refreshBottomText()
{
	if (currentWidget)
	{
		setBottomText(currentWidget->getBottomText());
	}
	else
	{
		logger->Debug("Not refresh help button");
	}
}

void BasicWindow::refreshHelpButton()
{
	if (currentWidget)
	{
		setHelpButtonSensitive(currentWidget->isHelpSensitive());
	}
	else
	{
		logger->Debug("Not refresh help button");
	}
}

void BasicWindow::refreshExitButton()
{
	if (currentWidget)
	{
		setExitButtonSensitive(currentWidget->isExitSensitive());
	}
	else
	{
		logger->Debug("Not refresh exit button");
	}
}

void BasicWindow::refreshStepWidget()
{
	if (currentWidget)
	{
		currentWidget->refresh();
	}

	refreshTitleText();
	refreshHelpButton();
	refreshExitButton();
	refreshBottomText();

	if (currentWidget)
	{
		setHelpButtonVisible(currentWidget->isHelp());
		setExitButtonVisible(currentWidget->isExit());
		setBorderVisible(currentWidget->isShowBorder());
		set_name(currentWidget->getName());

		RefreshListener * object = currentWidget->getRefreshListener();

		if (object)
		{
			object->refresh();
		}
	}
}

int BasicWindow::getCountStepWidget()
{
	return stepWidgetList.size();
}

StepWidget * BasicWindow::getCurrentWidget()
{
	return currentWidget;
}

void BasicWindow::setKeywordNavigation(Smartmatic::GUI::Widgets::keywordNavigationInterface * keywordInterface)
{
	this->keywordInterface = keywordInterface;
}

void BasicWindow::setBlockPopPush(bool blockState)
{
	Glib::Mutex::Lock lock(mutex);
	this->blockState = blockState;
}
