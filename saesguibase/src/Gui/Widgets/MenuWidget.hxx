/**
 * @file MenuWidget.hxx
 * @brief Header menu widget
 * @date29/03/2012
 * @author Yadickson Soto
 */

#ifndef MENUWIDGET_HXX_
#define MENUWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/StepWidget.hxx>
#include <Widgets/menu-widgetmm.h>

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
				class MenuWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:

					MenuWidget();
					virtual ~MenuWidget();

					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
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
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

					static bool reloadMenu; ///< reload menu

				protected:

					/**
					 * @brief	Sets a key.
					 * @author	Yadickson Soto
					 * @date	08/06/2012
					 * @param	value The value.
					 */
					virtual void SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value);

				private:

					Smartmatic::GUI::Widgets::MenuWidgetmm *menu;   ///< The menu
				};
			}
		}
	}
}

#endif /* MENUWIDGET_HXX_ */
