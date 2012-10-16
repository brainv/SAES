/**
 * @file CustomStatWidget.hxx
 * @brief Header class custom state widget
 * @date 01/06/2012
 * @author Yadickson Soto
 */

#ifndef CUSTOMSTATWIDGET_HXX_
#define CUSTOMSTATWIDGET_HXX_

#include "IStatWidget.hxx"
#include "smartmatic-entry.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class CustomStatWidget
			 * @brief class custom state widget
			 * @date 01/06/2012
			 * @author Yadickson Soto
			 */
			class CustomStatWidget : public IStatWidget
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
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				CustomStatWidget(std::string name, std::string code, std::string regex, bool mandatory = false, int maxCount = 4, std::string mask = "");
				/**
				 * @brief class destroy
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual ~CustomStatWidget();
				/**
				 * @brief method getter value
				 * @return value
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getValue();
				/**
				 * @brief method setter value
				 * @param value value
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setValue(std::string value);
				/**
				 * @brief method setter enable
				 * @param enable enable
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setEnable(bool enable);
				/**
				 * @brief method setter align
				 * @param align align
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setAlign(double align = 0.5);
				/**
				 * @brief method setter size
				 * @param width width
				 * @param height height
				 * @date 31/05/2012
				 * @author Yadickson Soto
				 */
				virtual void setSize(int width, int height);

			protected:

				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual bool validate();

				SmartmaticEntry* statEntry; ///< The stat entry
			};
		}
	}
}
#endif /* NUMERICSTATWIDGET_HXX_ */
