/**
 * @file FillTableColumnFixedWidget.hxx
 * @brief Header class fill table mode
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#ifndef FILLTABLECOLUMNFIXEDWIDGET_HXX_
#define FILLTABLECOLUMNFIXEDWIDGET_HXX_

#include <gtkmm.h>
#include "FillTableWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class FillTableColumnFixedWidget
				 * @brief Class FillTableColumnFixedWidget
				 * @author Yadickson Soto
				 * @date 15/03/2012
				 */
				class FillTableColumnFixedWidget : public FillTableWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param FillTableColumnFixedWidget fill mode table widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					FillTableColumnFixedWidget(Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					virtual ~FillTableColumnFixedWidget();

				protected:
					/**
					 * @brief method fill principal
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					virtual void putPrincipal();
				};
			}
		}
	}
}

#endif /* FILLTABLECOLUMNFIXEDWIDGET_HXX_ */
