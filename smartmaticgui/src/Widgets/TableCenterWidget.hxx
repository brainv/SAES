/**
 * @file TableCenterWidget.hxx
 * @brief Header class table center widget
 * @date 13/03/2012
 * @author Yadickson Soto
 */

#ifndef TABLECENTERWIDGET_HXX_
#define TABLECENTERWIDGET_HXX_

#include "TableWidget.hxx"

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
			/**
			 * @class TableCenterWidget
			 * @brief Class TableCenterWidget
			 * @author Yadickson Soto
			 * @date 13/03/2012
			 */
			class TableCenterWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief Class constructor
				 * @param homogeneous column homogeneous
				 * @param verticalCenter vertical center
				 * @author Yadickson Soto
				 * @date 16/05/2012
				 */
				TableCenterWidget(bool homogeneous = true, bool verticalCenter = false);
				/**
				 * @brief Class destroy
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				virtual ~TableCenterWidget();
				/**
				 * @brief method initialize class
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				virtual void initialize();
				/**
				 * @brief method dispose class
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				virtual void dispose();
				/**
				 * @brief method set spacings table
				 * @param row row spacings
				 * @param column column spacings
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				void setSpacings(int row, int column);
				/**
				 * @brief method resize table
				 * @param row row number
				 * @param column column number
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				virtual void resize(unsigned int row, unsigned int column);
				/**
				 * @brief method put new element in table
				 * @param widget new widget
				 * @param row row position
				 * @param column column position
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				void put(Gtk::Widget * widget, int row, int column);
				/**
				 * @brief method put new element in table
				 * @param widget new widget
				 * @param row row position
				 * @param column column position
				 * @param xAlign x align
				 * @param yAlign y align
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				void put(Gtk::Widget * widget, int row, int column, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign);
				/**
				 * @brief method getter count elements
				 * @return count elements
				 * @author Yadickson Soto
				 * @date 18/05/2012
				 */
				unsigned int getCountElements();
				/**
				 * @brief method clear elements
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				void clear();

			private:

				Gtk::EventBox * mainEventBox; ///< The main event box frame
				Gtk::HBox * mainHbox; ///< The main hbox
				Gtk::VBox * mainVbox; ///< The main vbox
				Gtk::EventBox * tableBox; ///< table box

				Smartmatic::GUI::Widgets::TableWidget * table; ///< table elements
				static Smartmatic::Log::ISMTTLog* logger;   ///< logger
			};
		}
	}
}

#endif /* TABLECENTERWIDGET_HXX_ */
