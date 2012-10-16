/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	print-pv-report-widget.h
 *
 * @brief	Declares the print PV report widget class.
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PRINT_PV_REPORT_WIDGET_H_
#define _PRINT_PV_REPORT_WIDGET_H_
#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>

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
				class PrintPVReportWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:
					PrintPVReportWidget();

					~PrintPVReportWidget();

					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

					Glib::ustring GetWidgetName() { return "PrintPVReportWidget"; };

				private:

					void ThreadStart();

					void on_done();

					void UpdateLabel(Glib::ustring text);
					Gtk::Label* label;  ///< The label
					Gtk::Image* loadImage;

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _PRINT_PV_REPORT_WIDGET_H_
