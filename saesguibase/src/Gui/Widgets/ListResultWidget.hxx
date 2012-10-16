/**
 * ListResultWidget.hxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#ifndef LISTRESULTWIDGET_HXX_
#define LISTRESULTWIDGET_HXX_

#include <gtkmm.h>
#include <list>
#include <Widgets/StepWidget.hxx>
#include <Widgets/TableCenterWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include "ResultWidget.hxx"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class ListResultWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					ListResultWidget(int columns, int width = 250, int height = 40);
					virtual ~ListResultWidget();
					void addWidget(Smartmatic::SAES::GUI::Widgets::ResultWidget * widget);
					int getCountWidget();

				protected:

					void initialize();
					void dispose();

					void putWidget(Smartmatic::SAES::GUI::Widgets::ResultWidget * widget);
					void viewInfo(Smartmatic::SAES::GUI::Widgets::ResultWidget * result);

					void initInfo();
					void clearList();

				private:

					int columns;
					int width;
					int height;

					int i;
					int j;

					Gtk::ScrolledWindow * scrollFrame;
					Gtk::EventBox * centerFrame;

					Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget;

					Gtk::Label * center;
					Smartmatic::GUI::Widgets::TableCenterWidget * resultWidget;
					Smartmatic::GUI::Widgets::SmartmaticButton * button; ///< button

					std::vector <Smartmatic::SAES::GUI::Widgets::ResultWidget *> resultWidgets;
					std::list <Smartmatic::SAES::GUI::Widgets::ResultWidget *> resultList;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* LISTRESULTWIDGET_HXX_ */
