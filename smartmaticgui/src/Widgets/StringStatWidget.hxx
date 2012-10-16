/**
 * @file StringStatWidget.hxx
 * @brief Header class string state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#ifndef STRINGSTATWIDGET_HXX_
#define STRINGSTATWIDGET_HXX_

#include "IStatWidget.hxx"
#include "SmartmaticTextView.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class StringStatWidget
			 * @brief class string state widget
			 * @date 08/05/2012
			 * @author Yadickson Soto
			 */
			class StringStatWidget : public IStatWidget
			{
			public:
				/**
				 * @brief class constructor
				 * @param name name
				 * @param code code
				 * @param mandatory mandatory
				 * @param maxCount max count
				 * @param width width
				 * @param height height
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				StringStatWidget(std::string name, std::string code, bool mandatory = false, int maxCount = 4, int width = 300, int height = 100);
				/**
				 * @brief class destroy
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~StringStatWidget();
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

			protected:

				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 01/06/2012
				 * @author Yadickson Soto
				 */
				virtual bool validate();

			private:

				SmartmaticTextView * textView; ///< text view
				Gtk::Alignment * align; ///< align
			};
		}
	}
}
#endif /* STRINGSTATWIDGET_HXX_ */
