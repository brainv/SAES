/**
 * @file RegisterActionWidget.hxx
 * @brief Header class register action widget
 * @data 24/05/2012
 * @author Yadickson Soto
 */

#ifndef REGISTERACTIONWIDGET_HXX_
#define REGISTERACTIONWIDGET_HXX_

#include <Widgets/RegisterWidget.hxx>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class RegisterActionWidget
			 * @brief class register action widget
			 * @data 24/05/2012
			 * @author Yadickson Soto
			 */
			template <class TRegister>
			class RegisterActionWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief class constructor
				 * @data 24/05/2012
				 * @author Yadickson Soto
				 */
				RegisterActionWidget();
				/**
				 * @brief class destroy
				 * @data 24/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~RegisterActionWidget();
				/**
				 * @brief method add widget
				 * @param widget new widget
				 * @param title title tab
				 * @date 24/05/2012
				 * @author Yadickson Soto
				 */
				void addWidget(TRegister widget, std::string title = " ");
				/**
				 * @brief method setter current page
				 * @param currentPage current page
				 * @date 24/05/2012
				 * @author Yadickson Soto
				 */
				void setCurrentPage(int currentPage);
				/**
				 * @brief method getter signal clicked
				 * @return signal clicked
				 * @data 24/05/2012
				 * @author Yadickson Soto
				 */
				sigc::signal<void, TRegister> getSignalClicked();

			protected:

				Smartmatic::GUI::Widgets::RegisterWidget * registerWidget; ///< register container widget

			private:

				/**
				 * @brief method process signal clicked
				 * @param widget widget
				 * @data 24/05/2012
				 * @author Yadickson Soto
				 */
				void editInfo(TRegister widget);

				sigc::signal<void, TRegister> signalClicked; ///< signal clicked info
			};
		}
	}
}

#include "RegisterActionWidget.hpp"

#endif /* REGISTERACTIONWIDGET_HXX_ */
