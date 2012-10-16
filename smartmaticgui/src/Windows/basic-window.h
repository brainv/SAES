/**
 * @file basic-window.h
 * @brief Header class basic window
 * @date 26/03/2012
 * @author Yadickson Soto
 */

#ifndef _BASIC_WINDOW_H_
#define _BASIC_WINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include <list>
#include "Widgets/keyword-navigation-interface.h"
#include "Widgets/operation-key.h"
#include "Configuration/label-configuration.h"
#include "Widgets/exit-button-listener.h"
#include "Widgets/help-button-listener.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace GUI  
	{
		namespace Widgets
		{
			class HelpExitButtons;
			class StepWidget;
		}

		namespace Windows
		{
			/**
			 * @class BasicWindow
			 * @brief class basic window
			 * @date 26/03/2012
			 * @author Yadickson Soto
			 */
			class BasicWindow: public Gtk::Window,
				public Smartmatic::GUI::Widgets::ExitButtonListener,
				public Smartmatic::GUI::Widgets::HelpButtonListener
			{
			public:

				/**
				 * @enum	PositionWindow
				 * @brief	enum position window
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				typedef enum
				{
					 TOP_RIGHT		///< top right
					,TOP_LEFT		///< top left
					,TOP_CENTER		///< top center
					,CENTER_RIGHT	///< center right
					,CENTER_LEFT	///< center left
					,CENTER_CENTER	///< center center
					,BOTTOM_RIGHT	///< bottom right
					,BOTTOM_LEFT	///< bottom left
					,BOTTOM_CENTER	///< bottom center
				}PositionWindow;

				/**
				 * @brief	Constructor.
				 * @param	useHeaderFrame	true to use header frame.
				 * @param	useTitleFrame 	true to use title frame.
				 * @param	isModal flag modal
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				BasicWindow(bool useHeaderFrame=true, bool useTitleFrame = false, bool isModal = true, Gtk::WindowType type = Gtk::WINDOW_TOPLEVEL);
				/**
				 * @brief	Class destroy.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				virtual ~BasicWindow ();
				/**
				 * @brief	Method  show the dialog.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				virtual void ShowDialog();
				/**
				 * @brief	Method quit dialog.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				virtual void QuitDialog();
				/**
				 * @brief	Method getter window size
				 * @param	width 	result width.
				 * @param	height	result height.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void getWindowSize (int& width, int& height);
				/**
				 * @brief	Gets a principal size.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	width 	The width.
				 * @param [in,out]	height	The height.
				 */
				void getContentSize (int& width, int& height);
				/**
				 * @brief	Method set position window
				 * @param	x position x
				 * @param	y position y
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void setPosition(int x, int y);
				/**
				 * @brief	Method set position window
				 * @param	position new position
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void setPosition(PositionWindow position);
				/**
				 * @brief	Method show header
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void showHeader();
				/**
				 * @brief	Method show title
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void showTitle();
				/**
				 * @brief	Method show bottom
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void showBottom();
				/**
				 * @brief	Method hide header
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void hideHeader();
				/**
				 * @brief	Method hide title
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void hideTitle();
				/**
				 * @brief	Method hide bottom
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				void hideBottom();
				/**
				 * @brief	Gets a title size.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	width 	The width.
				 * @param [in,out]	height	The height.
				 */
				void getTitleSize (int& width, int& height);
				/**
				 * @brief	Gets a banner size.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	width 	The width.
				 * @param [in,out]	height	The height.
				 */
				void getHeaderSize (int& width, int& height);
				/**
				 * @brief	Method getter bottom size
				 * @param width result width.
				 * @param height result height.
				 * @author	Yadickson Soto
				 * @date	28/03/2012
				 */
				void getBottomSize (int& width, int& height);
				/**
				 * @brief Method set title label configuration
				 * @param lblConfig label configuration
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration lblConfig);
				/**
				 * @brief Method set bottom label configuration
				 * @param lblConfig label configuration
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				void setBottomLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration lblConfig);
				/**
				 * @brief Method set title test
				 * @param title new text
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleText(std::string title);
				/**
				 * @brief Method set bottom test
				 * @param bottom new text
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				void setBottomText(std::string bottom);
				/**
				 * @brief Method set title color
				 * @param color new title color
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleColor(Gdk::Color & color);
				/**
				 * @brief Method show title image
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void showTitleImage();
				/**
				 * @brief Method hide title image
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void hideTitleImage();
				/**
				 * @brief Method setter title image
				 * @param image new title image
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleImage(std::string image);
				/**
				 * @brief Method show title help
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void showTitleHelp();
				/**
				 * @brief Method hide title help
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void hideTitleHelp();
				/**
				 * @brief Method setter title help
				 * @param widget new title help
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleHelp(Gtk::Widget * widget);
				/**
				 * @brief Method view widget in title area
				 * @param widget widget to view
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void setTitle(Gtk::Widget * widget);
				/**
				 * @brief Method view widget in client area
				 * @param widget widget to view
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void setWidget(Gtk::Widget * widget);
				/**
				 * @brief Method view widget in bottom area
				 * @param widget widget to view
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void setBottom(Gtk::Widget * widget);
				/**
				 * @brief	Sets exit button sensitive.
				 * @param	sensitive	true to sensitive.
				 */
				virtual void setExitButtonSensitive (bool sensitive);
				/**
				 * @brief	Sets exit button visible.
				 * @param	visible	true to show, false to hide.
				 */
				virtual void setExitButtonVisible (bool visible);
				/**
				 * @brief	Sets help button sensitive.
				 * @param	sensitive	true to sensitive.
				 */
				virtual void setHelpButtonSensitive (bool sensitive);
				/**
				 * @brief	Sets help button visible.
				 * @param	visible	true to show, false to hide.
				 */
				virtual void setHelpButtonVisible (bool visible);
				/**
				 * @brief Method view all border
				 * @param visible true to show, false to hide.
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void setBorderVisible(bool visible);
				/**
				 * @brief Method enable help button
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void enableHelpButton();
				/**
				 * @brief Method disable help button
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void disableHelpButton();
				/**
				 * @brief Method enable exit button
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void enableExitButton();
				/**
				 * @brief Method disable exit button
				 * @date 28/03/2012
				 * @author Yadickson Soto
				 */
				virtual void disableExitButton();
				/**
				 * @brief Method push new widget
				 * @param widget new widget
				 * @param force force push
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void pushStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget, bool force = false);
				/**
				 * @brief Method pop and push new widget
				 * @param widget new widget
				 * @param force force push
				 * @return last widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				Smartmatic::GUI::Widgets::StepWidget * popPushStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget, bool force = false);
				/**
				 * @brief Method pop last widget
				 * @param force force push
				 * @return last widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				Smartmatic::GUI::Widgets::StepWidget * popStepWidget(bool force = false);
				/**
				 * @brief Method set step windget
				 * @param widget set step widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget);
				/**
				 * @brief Method refresh title text
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void refreshTitleText();
				/**
				 * @brief Method refresh bottom text
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				virtual void refreshBottomText();
				/**
				 * @brief Method refresh help button
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void refreshHelpButton();
				/**
				 * @brief Method refresh exit button
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void refreshExitButton();
				/**
				 * @brief Method refresh step widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void refreshStepWidget();
				/**
				 * @brief Method setter current keyword
				 * @param keywordInterface current keyword
				 * @date 08/06/2012
				 * @author Yadickson Soto
				 */
				void setKeywordNavigation(Smartmatic::GUI::Widgets::keywordNavigationInterface * keywordInterface);
				/**
				 * @brief Method setter block push pop
				 * @param blockState block state
				 * @date 08/06/2012
				 * @author Yadickson Soto
				 */
				void setBlockPopPush(bool blockState = false);

			protected:

				/**
				 * @brief	Move left.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void MoveLeft();
				/**
				 * @brief	Move right.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void MoveRight();
				/**
				 * @brief	Move down.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void MoveDown();
				/**
				 * @brief	Move up.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void MoveUp();
				/**
				 * @brief	Enters this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void Enter();
				/**
				 * @brief	Gets the keyval close configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The keyval close configuration.
				 */
				int GetKeyvalCloseConfiguration();
				/**
				 * @brief	Gets the keyval help configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The keyval help configuration.
				 */
				int GetKeyvalHelpConfiguration();
				/**
				 * @brief	Key pressed.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */
				virtual bool key_pressed(GdkEventKey *event);
				/**
				 * @brief	Fill valid keys.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				void FillValidKeys();
				/**
				 * @brief	Query if 'keyval' is valid key.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	keyval	The keyval.
				 *
				 * @return	true if valid key, false if not.
				 */
				bool IsValidKey(int keyval);
				/**
				 * @brief	Gets the header frame.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The header frame.
				 */
				Gtk::Frame& getHeaderFrame();
				/**
				 * @brief	Gets the title frame.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The title frame.
				 */
				Gtk::Frame& getTitleFrame();
				/**
				 * @brief	Gets the client area frame.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The client area frame.
				 */
				Gtk::Frame& getClientAreaFrame();
				/**
				 * @brief	Method getter bottom frame
				 * @return	The bottom frame.
				 * @author	Yadickson Soto
				 * @date	28/03/2012
				 */
				Gtk::Frame& getBottomFrame();
				/**
				 * @brief	Raises the delete event.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	G_GNUC_UNUSED	If non-null, the gnuc unused.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */
				virtual bool on_delete_event( GdkEventAny* G_GNUC_UNUSED );
				/**
				 * @brief Method initialize class
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				void initialize();
				/**
				 * @brief Method dispose class
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				virtual void dispose();
				/**
				 * @brief Method show menu
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void ShowHelp();
				/**
				 * @brief Method show exit
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void ShowExit();
				/**
				 * @brief Method exit window clicked
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void Exit();
				/**
				 * @brief Method getter count step widget
				 * @return count step widget
				 * @date 11/04/2012
				 * @author Yadickson Soto
				 */
				int getCountStepWidget();
				/**
				 * @brief Method getter current step widget
				 * @return current step widget
				 * @date 11/04/2012
				 * @author Yadickson Soto
				 */
				Smartmatic::GUI::Widgets::StepWidget * getCurrentWidget();

			private:
				/**
				 * @brief Method resize components
				 * @date 27/04/2012
				 * @author Yadickson Soto
				 */
				void resizeComponents();

				Glib::Mutex mutex; ///< lock show widget

				Smartmatic::GUI::Widgets::HelpExitButtons* helpExitButtons; ///< help exit buttons
				Smartmatic::GUI::Widgets::StepWidget * currentWidget; ///< current widget

				bool blockState; ///< block pusp pop state
				int formheight; ///< form height
				int formwidth; ///< form width
				int panelsPaddingX; ///< padding x
				int panelsPaddingY; ///< padding y
				bool isModal; ///< flag modal
				bool useHeaderFrame; ///< flag show header frame
				bool useTitleFrame; ///< flag show title frame
				bool useBottomFrame; ///< flag use bottom frame
				int panelHeaderWidth; ///< panel header width
				int panelHeaderHeight; ///< panel header height
				int panelTitleWidth; ///< panel title width
				int panelTitleHeight; ///< panel title height
				int panelBottomWidth; ///< panel bottom width
				int panelBottomHeight; ///< panel bottom height
				int panelClientWidth; ///< panel client width
				int panelClientHeight; ///< panel client height

				std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> validKeys;   ///< The valid keys
				Smartmatic::GUI::Widgets::NavigationMode navigationMode;	///< The navigation mode

				Gtk::VBox * mainVbox; ///< main frame
				Gtk::HBox * titleHbox; ///< title hbox
				Gtk::EventBox * titleHelpEventbox; ///< title help
				Gtk::EventBox * bottomEventBox; ///< bottom event box
				Gtk::Frame * headerFrame;   ///< The header frame
				Gtk::Frame * titleFrame;	///< The title frame
				Gtk::Frame * clientArea;	///< The client area
				Gtk::Frame * bottomFrame; ///< The bottom frame
				Gtk::Image * titleImage;	///< The title image
				Gtk::Label * titleLabel; ///< title label
				Gtk::Label * bottomLabel; ///< bottom label
				Gtk::EventBox* titleeventbox;   ///< The titleeventbox
				Gtk::EventBox* clientAreaEventBox;  ///< The client area event box
				Smartmatic::GUI::Widgets::keywordNavigationInterface* keywordInterface; ///< The keyword interface

				std::list < Smartmatic::GUI::Widgets::StepWidget * > stepWidgetList; ///< widget list
				Smartmatic::GUI::Widgets::KeysActionsCode keyCode; ///< key press
				static Smartmatic::Log::ISMTTLog* logger;///< The logger
			};
		}
	}
}
#endif // _BASIC_FORM_H_
