/*
 * DataUtilsResultWidget.hxx
 *
 *  Created on: 24/07/2012
 *      Author: yadickson
 */

#ifndef DATAUTILSRESULTWIDGET_HXX_
#define DATAUTILSRESULTWIDGET_HXX_

#include <gtkmm.h>
#include <Gui/Widgets/ResultWidget.hxx>
#include <Gui/Widgets/ListResultWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class DataUtilsResultWidget : public Gtk::EventBox
				{
				public:
					DataUtilsResultWidget();
					virtual ~DataUtilsResultWidget();
					void setResult(int success, int fail);

				private:
					Smartmatic::SAES::GUI::Widgets::ListResultWidget * listResultWidget; ///< result widget
				};
			}
		}
	}
}

#endif /* DATAUTILSRESULTWIDGET_HXX_ */
