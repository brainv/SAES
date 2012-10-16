/**
 * @file BoolStatWidget.hxx
 * @brief Header class boolean state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#ifndef BOOLSTATWIDGET_HXX_
#define BOOLSTATWIDGET_HXX_

#include "IStatWidget.hxx"
#include "smartmatic-combo-box.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class BoolStatWidget
			 * @brief class boolean state widget
			 * @date 08/05/2012
			 * @author Yadickson Soto
			 */
			class BoolStatWidget : public IStatWidget
			{
			public:
				/**
				 * @brief class constructor
				 * @param name name
				 * @param code code
				 * @param mandatory mandatory
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				BoolStatWidget(std::string name, std::string code, bool mandatory = true);
				/**
				 * @brief class destroy
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~BoolStatWidget();
				/**
				 * @brief method getter value
				 * @return value
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getValue();
				/**
				 * @brief method setter value
				 * @param value value
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setValue(std::string value);
				/**
				 * @brief method setter enable
				 * @param enable enable
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setEnable(bool enable);
				/**
				 * @brief method setter size
				 * @param width width
				 * @param height height
				 * @date 31/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setSize(int width, int height);
				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 02/08/2012
				 * @author Yadickson Soto
				 */
				virtual bool validate();

				static std::string True; ///< true
				static std::string False; ///< false
				static std::string None; ///< false

			private:

				SmartmaticComboBox * comboBox; ///< combo box
				bool mandatory; ///< mandatory

				/**
				 * @brief method combo changed
				 * @date 02/08/2012
				 * @author Yadickson Soto
				 */
				void comboChanged(Glib::ustring text);
			};
		}
	}
}
#endif /* BOOLSTATWIDGET_HXX_ */
