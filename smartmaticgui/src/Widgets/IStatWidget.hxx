/**
 * @file IStatWidget.hxx
 * @brief Header class state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#ifndef ISTATWIDGET_HXX_
#define ISTATWIDGET_HXX_

#include <iostream>
#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class IStatWidget
			 * @brief class state widget
			 * @date 08/05/2012
			 * @author Yadickson Soto
			 */
			class IStatWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief class constructor
				 * @param name name
				 * @param code code
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				IStatWidget(std::string name, std::string code);
				/**
				 * @brief class destroy
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~IStatWidget();
				/**
				 * @brief method getter name
				 * @return name
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getName();
				/**
				 * @brief method getter code
				 * @return code
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getCode();
				/**
				 * @brief method getter value
				 * @return value
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getValue() = 0;
				/**
				 * @brief method setter value
				 * @param value value
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setValue(std::string value) = 0;
				/**
				 * @brief method setter enable
				 * @param enable enable
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setEnable(bool enable) = 0;
				/**
				 * @brief method setter align
				 * @param align align
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setAlign(double align = 0.5);
				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 25/05/2012
				 * @author Yadickson Soto
				 */
				virtual bool validate() = 0;
				/**
				 * @brief method setter size
				 * @param width width
				 * @param height height
				 * @date 31/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setSize(int width, int height) = 0;

			protected:

				std::string name; ///< name
				std::string code; ///< code

				/**
				 * @brief method setter size
				 * @param widget widget
				 * @param width width
				 * @param height height
				 * @date 31/05/2012
				 * @author Yadickson Soto
				 */
				void setSize(Gtk::Widget * widget, int width, int height);
			};
		}
	}
}
#endif /* ISTATWIDGET_HXX_ */
