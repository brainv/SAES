/**
 * @file RegisterWidget.hxx
 * @brief Header class register generic widget
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#ifndef REGISTERWIDGET_HXX_
#define REGISTERWIDGET_HXX_

#include "StepWidget.hxx"
#include "smartmatic-button.h"
#include "notebook-container.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class RegisterWidget
			 * @brief class register generic widget
			 * @data 18/05/2012
			 * @author Yadickson Soto
			 */
			class RegisterWidget : public StepWidget
			{
			public:
				/**
				 * @brief class constructor
				 * @param showTabs show tabs
				 * @param bottomWidget bottom widget
				 * @data 18/05/2012
				 * @author Yadickson Soto
				 */
				RegisterWidget(bool showTabs, Gtk::Widget * bottomWidget = NULL);
				/**
				 * @brief class destroy
				 * @data 18/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~RegisterWidget();
				/**
				 * @brief method configuration
				 * @param maxRow max row
				 * @param maxCol max column
				 * @param rowSpacing row spacing
				 * @param colSpacing column spacing
				 * @param width width
				 * @param height height
				 * @param vertical vertical fill
				 * @param border border
				 * @data 24/05/2012
				 * @author Yadickson Soto
				 */
				void setConfig(int maxRow = 2, int maxCol = 3, int rowSpacing = 5, int colSpacing = 5, int width = 315, int height = 175, bool vertical = true, int border = 0);
				/**
				 * @brief virtual method stop
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				virtual void dispose();
				/**
				 * @brief method add widget
				 * @param widget new widget
				 * @param title title tab
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				void addWidget(Gtk::Widget * widget, std::string title = " ");
				/**
				 * @brief method setter current page
				 * @param currentPage current page
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				void setCurrentPage(int currentPage);
				/**
				 * @brief method getter signal all pages view
				 * @return signal
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				sigc::signal<void> getSignalAllPagesViewed();

			private:

				Smartmatic::GUI::Widgets::NotebookContainer * notebookContainer; ///< notebook container
				Gtk::HButtonBox * hboxBtn; ///< hbutton info
				Gtk::Alignment * align; ///< align
				std::vector<Gtk::Widget*> vectorWidget; ///< vector widget
				int maxRow; ///< max row
				int maxCol; ///< max column
				int rowSpacing; ///< row spacing
				int colSpacing; ///< column spacing
				int border; ///< border
				int width; ///< width
				int height; ///< height
				bool vertical; ///< vertical
			};
		}
	}
}

#endif /* REGISTERWIDGET_HXX_ */
