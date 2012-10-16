/**
 * @file StepWidget.hxx
 * @brief Header class step widget
 * @date 08/03/2012
 * @author Yadickson Soto
 */

#ifndef STEPWIDGET_HXX_
#define STEPWIDGET_HXX_

#include <gtkmm.h>
#include "RefreshListener.hxx"
#include "StateListener.hxx"
#include "keyword-navigation-interface.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class StepWidget
			 * @brief Class step widget
			 * @date 08/03/2012
			 * @author Yadickson Soto
			 */
			class StepWidget : public Gtk::EventBox, public RefreshListener, public keywordNavigationInterface
			{
			public:
				/**
				 * @brief Class constructor
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				StepWidget();
				/**
				 * @brief Class destroy
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				virtual ~StepWidget();
				/**
				 * @brief virtual method getter title
				 * @return title
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getTitleText();
				/**
				 * @brief method setter title
				 * @param titleKey title window
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setTitleText(std::string titleKey);
				/**
				 * @brief virtual method getter title
				 * @return bottom
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getBottomText();
				/**
				 * @brief method setter bottom
				 * @param bottomKey bottom window
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				void setBottomText(std::string bottomKey);
				/**
				 * @brief virtual method getter is visible title frame
				 * @return true is title frame visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual bool isTitle();
				/**
				 * @brief method setter is visible title frame
				 * @param showTitle true is title frame visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setTitle(bool showTitle);
				/**
				 * @brief virtual method getter is visible title frame
				 * @return true is title frame visible
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				virtual bool isBottom();
				/**
				 * @brief method setter is visible bottom frame
				 * @param showBottom true is bottom frame visible
				 * @date 25/04/2012
				 * @author Yadickson Soto
				 */
				void setBottom(bool showBottom);
				/**
				 * @brief virtual method getter is visible help button
				 * @return true is help button visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual bool isHelp();
				/**
				 * @brief method setter is visible help button
				 * @param showHelp true is help button visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setHelp(bool showHelp);
				/**
				 * @brief virtual method getter is visible help button
				 * @return true is help button visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual bool isExit();
				/**
				 * @brief method setter is visible exit button
				 * @param showExit true is exit button visible
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setExit(bool showExit);
				/**
				 * @brief virtual method getter is sensitive help button
				 * @return true is help button is sensitive
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual bool isHelpSensitive();
				/**
				 * @brief method setter is sensitive help button
				 * @param showTitle true is help button is sensitive
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setHelpSensitive(bool helpSensitive);
				/**
				 * @brief virtual method getter is sensitive help button
				 * @return true is exit button is sensitive
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual bool isExitSensitive();
				/**
				 * @brief method setter is sensitive exit button
				 * @param showExit true is exit button is sensitive
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setExitSensitive(bool exitSensitive);
				/**
				 * @brief virtual method getter is show border
				 * @return true is show border
				 * @date 14/04/2012
				 * @author Yadickson Soto
				 */
				virtual bool isShowBorder();
				/**
				 * @brief method setter is show border
				 * @param showBorder true is show border
				 * @date 14/04/2012
				 * @author Yadickson Soto
				 */
				void setShowBorder(bool showBorder);
				/**
				 * @brief virtual method getter string name
				 * @return name
				 * @date 14/04/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getName();
				/**
				 * @brief method setter string name
				 * @param name name
				 * @date 14/04/2012
				 * @author Yadickson Soto
				 */
				void setName(std::string name);
				/**
				 * @brief virtual method init
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				virtual void initialize();
				/**
				 * @brief virtual method stop
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				virtual void dispose();
				/**
				 * @brief method setter widget
				 * @param widget widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setWidget(Gtk::Widget * widget);
				/**
				 * @brief method setter help widget
				 * @param helpWidget help widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setHelpWidget(StepWidget * helpWidget);
				/**
				 * @brief method getter help widget
				 * @return help widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				StepWidget * getHelpWidget();
				/**
				 * @brief method setter exit widget
				 * @param exitWidget exit widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				void setExitWidget(StepWidget * exitWidget);
				/**
				 * @brief method getter exit widget
				 * @return exit widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				StepWidget * getExitWidget();
				/**
				 * @brief method refresh widget
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				virtual void refresh();
				/**
				 * @brief method setter refresh listener.
				 * @param refreshListener object listener
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				void setRefreshListener(RefreshListener * refreshListener);
				/**
				 * @brief method getter refresh listener.
				 * @return object listener
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				RefreshListener * getRefreshListener();
				/**
				 * @brief method setter stete listener.
				 * @param stateListener object listener
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				void setStateListener(StateListener * stateListener);
				/**
				 * @brief method getter state listener.
				 * @return object listener
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				StateListener * getStateListener();
				/**
				 * @brief method getter signal end
				 * @return signal end
				 * @date 22/04/2012
				 * @author Yadickson Soto
				 */
				sigc::signal<void> getSignalEnd();

			protected:

				sigc::signal<void> signalEnd; ///< signal end

				/**
				 * @brief	Sets a key.
				 * @author	Yadickson Soto
				 * @date	08/06/2012
				 * @param	value The value.
				 */
				virtual void SetKey(KeysActionsCode value);

			private:

				std::string titleKey; ///< title key
				std::string bottomKey; ///< bottom text
				std::string name; ///< name

				bool showTitle; ///< flag show title
				bool showBottom; ///< flag show bottom
				bool showHelp; ///< flag show help
				bool showExit; ///< flag show exit
				bool showBorder; ///< flag show border
				bool helpSensitive; ///< flag help sensitive
				bool exitSensitive; ///< flag exit sensitive
				StepWidget * helpWidget; ///< help widget
				StepWidget * exitWidget; ///< exit widget
				RefreshListener * refreshListener; ///< widget to refresh
				StateListener * stateListener; ///< widget to state
			};
		}
	}
}

#endif /* STEPWIDGET_HXX_ */
