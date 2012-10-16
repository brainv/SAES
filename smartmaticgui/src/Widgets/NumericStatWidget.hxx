/**
 * @file NumericStatWidget.hxx
 * @brief Header class numeric state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#ifndef NUMERICSTATWIDGET_HXX_
#define NUMERICSTATWIDGET_HXX_

#include "CustomStatWidget.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class NumericStatWidget
			 * @brief class numeric state widget
			 * @date 08/05/2012
			 * @author Yadickson Soto
			 */
			class NumericStatWidget : public CustomStatWidget
			{
			public:
				/**
				 * @brief class constructor
				 * @param name name
				 * @param code code
				 * @param regex regex
				 * @param mandatory mandatory
				 * @param maxCount max count
				 * @param mask mask
				 * @param enableEvent enable event
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				NumericStatWidget(std::string name, std::string code, std::string regex, bool mandatory, int maxCount = 4);
				/**
				 * @brief class destroy
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~NumericStatWidget();
				/**
				 * @brief method setter value
				 * @param value value
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setValue(std::string value);

			protected:

				/**
				 * @brief method event key pressed
				 * @param event event
				 * @return result
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				bool on_key_pressed(GdkEventKey* event);
				/**
				 * @brief method increment
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				void increment();
				/**
				 * @brief method decrement
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				void decrement();
			};
		}
	}
}
#endif /* NUMERICSTATWIDGET_HXX_ */
