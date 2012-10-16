/**
 * @file TableWidget.hxx
 * @brief Header class table widget
 * @date 13/03/2012
 * @author Yadickson Soto
 */

#ifndef TABLEWIDGET_HXX_
#define TABLEWIDGET_HXX_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class TableWidget
			 * @brief Class TableWidget
			 * @author Yadickson Soto
			 * @date 13/03/2012
			 */
			class TableWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief Class constructor
				 * @param xAlign x align
				 * @param yAlign y align
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				TableWidget(Gtk::AttachOptions xAlign = Gtk::SHRINK, Gtk::AttachOptions yAlign = Gtk::SHRINK);
				/**
				 * @brief Class constructor
				 * @param table table
				 * @param xAlign x align
				 * @param yAlign y align
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				TableWidget(Gtk::Table * table, Gtk::AttachOptions xAlign = Gtk::SHRINK, Gtk::AttachOptions yAlign = Gtk::SHRINK);
				/**
				 * @brief Class destroy
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				virtual ~TableWidget();
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
				 * @brief method resize table
				 * @param row row number
				 * @param column column number
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				virtual void resize(unsigned int row, unsigned int column);
				/**
				 * @brief method getter table
				 * @return table
				 * @author Yadickson Soto
				 * @date 15/03/2012
				 */
				Gtk::Table * getTable();
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
				 * @brief method put new element in table
				 * @param widget new widget
				 * @param rowInit row position
				 * @param rowEnd row position
				 * @param colInit column position
				 * @param colEnd column position
				 * @param xAlign x align
				 * @param yAlign y align
				 * @author Yadickson Soto
				 * @date 25/05/2012
				 */
				void put(Gtk::Widget * widget, int rowInit, int rowEnd, int colInit, int colEnd, Gtk::AttachOptions xAlign, Gtk::AttachOptions yAlign);
				/**
				 * @brief method clear
				 * @author Yadickson Soto
				 * @date 09/05/2012
				 */
				void clear();
				/**
				 * @brief method getter count elements
				 * @return count elements
				 * @author Yadickson Soto
				 * @date 09/05/2012
				 */
				unsigned int getCountElements();
				/**
				 * @brief method set spacings table
				 * @param row row spacings
				 * @param column column spacings
				 * @author Yadickson Soto
				 * @date 16/03/2012
				 */
				void setSpacings(int row, int column);

			protected:

				Gtk::Table * table; ///< The table
				Gtk::AttachOptions xAlign; ///< x align
				Gtk::AttachOptions yAlign; ///< y align
				std::list <Gtk::Widget *> listWidget; ///< list in table
			};
		}
	}
}

#endif /* TABLEWIDGET_HXX_ */
