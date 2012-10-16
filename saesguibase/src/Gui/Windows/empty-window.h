/**
 * @file	empty-window.h
 * @brief	Declares the empty Windows Form.
 * @date 03/04/2012
 * @author Yadickson Soto
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
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

#ifndef _EMPTY_WINDOW_H_
#define _EMPTY_WINDOW_H_

#include <gtkmm.h>
#include <Windows/basic-window.h>
#include <Widgets/StepWidget.hxx>
#include <Gui/Widgets/InfoStepWidget.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class MemoryStateWidget;
			}

			namespace Windows
			{
				/**
				 * @class EmptyWindow
				 * @brief Form for empty window.
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				class EmptyWindow : public Smartmatic::GUI::Windows::BasicWindow
				{
	
				public:

					/**
					 * @brief	Class constructor.
					 * @param	widget	the widget container
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					EmptyWindow(Smartmatic::GUI::Widgets::StepWidget * stepWidget);

					/**
					 * @brief	Class constructor.
					 * @param 	widget	the widget container
					 * @param	title		The title.
					 * @param 	showTitleText	show title
					 * @param	showHelpButton	true to show help button.
					 * @param	showExitButton	true to show exit button.
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					EmptyWindow(Gtk::Widget * widget, std::string title, bool showTitleText, bool showHelpButton, bool showExitButton);
					/**
					 * @brief	Finaliser.
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					virtual ~EmptyWindow();
					/**
					 * @brief	Show message widget
					 * @param   widget widget base
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					void showInitMessageWidget(Smartmatic::SAES::GUI::Widgets::InfoStepWidget & widget);
					/**
					 * @brief	Show message widget
					 * @param   widget widget base
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					void showExitMessageWidget(Smartmatic::SAES::GUI::Widgets::InfoStepWidget & widget);
					/**
					 * @brief	Show message widget
					 * @param   widget widget base
					 * @date 	30/03/2012
					 * @author 	Yadickson Soto
					 */
					void showMessageWidget(Smartmatic::SAES::GUI::Widgets::InfoStepWidget & widget);

					void showMemoryState();

					void restoreOneMemory();

					void restoreTwoMemory();

					void restore(bool oneMemory);
					/**
					 * @brief Method refresh title
					 * @date 28/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refreshTitleText();
					/**
					 * @brief Method show exit
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void ShowExit();
					/**
					 * @brief Method enable exit button
					 * @date 28/03/2012
					 * @author Yadickson Soto
					 */
					virtual void enableExitButton();
					/**
					 * @brief method getter signal show message exit
					 * @return signal show message exit
					 * @date 14/05/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalShowExitMessage();
					/**
					 * @brief method getter signal exit button
					 * @return signal exit button
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalExitButton();

				protected:

					sigc::signal<void> signalShowExitMessage; ///< signal show message
					sigc::signal<void> signalExitButton; ///< signal exit button

				protected:

					/**
					 * @brief Method show menu clicked
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void ShowHelp();
					/**
					 * @brief Method exit window clicked
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void Exit();
					/**
					 * @brief method one memory operation
					 * @date 20/04/2012
					 * @author Yadickson Soto
					 */
					void OneMemoryOperation();
					/**
					 * @brief method two memory operation
					 * @date 20/04/2012
					 * @author Yadickson Soto
					 */
					void TwoMemoryOperation();
					/**
					 * @brief method receive event memory
					 * @date 20/04/2012
					 * @author Yadickson Soto
					 */
					void memoryBlock();
					/**
					 * @brief method refresh widget by verify data
					 * @date 10/04/2012
					 * @author Yadickson Soto
					 */
					void memoryVerify();
					/**
					 * @brief Method exit message
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					void exitMessage();

				protected:

					Smartmatic::GUI::Widgets::StepWidget stepWidget; ///< step widget
					Smartmatic::SAES::GUI::Widgets::MemoryStateWidget * memoryStateWidget; ///< help widget

				private:

					Glib::Mutex mutex; ///< lock show widget
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					bool block; ///< flag block widget
					bool forceHide; ///< force hide widget
					bool viewInitMessage; ///< flag show current message
					bool viewExitMessage; ///< flag show current message
					bool viewHelpWidget; ///< flag show current help widget
					bool viewMemoryStateWidget; ///< flag show current memory state
					bool oneMemory; ///< flag operation one memory

					/**
					 * @brief Method initialize config
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					void initConfig();
				};
			}
		}
	}

}



#endif // _EMPTY_WINDOW_H_
