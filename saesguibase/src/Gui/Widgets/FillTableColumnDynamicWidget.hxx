/**
 * @file FillTableColumnDynamicWidget.hxx
 * @brief Header class fill table mode
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#ifndef FILLTABLECOLUMNDYNAMICWIDGET_HXX_
#define FILLTABLECOLUMNDYNAMICWIDGET_HXX_

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
				 * @class FillTableColumnDynamicWidget
				 * @brief Class FillTableColumnDynamicWidget
				 * @author Yadickson Soto
				 * @date 15/03/2012
				 */
				class FillTableColumnDynamicWidget : public FillTableWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param FillTableColumnDynamicWidget fill mode table widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					FillTableColumnDynamicWidget(Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					virtual ~FillTableColumnDynamicWidget();

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

#endif /* FILLTABLECOLUMNDYNAMICWIDGET_HXX_ */
