/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * counterstat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * counterstat is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COUNTER_STAT_WIDGET_H_
#define _COUNTER_STAT_WIDGET_H_

#include <gtkmm.h>
#include <Configuration/label-configuration.h>
#include "IStatWidget.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @brief	Counter stat widget. 
			 *
			 * @author	Luiggi.mendez
			 * @date	27/04/2011
			 */

			class CounterStatWidget : public Gtk::HBox
			{
			public:
				/**
				 * @brief Class constructor
				 * @param statWidget stat widget
				 * @param	horizontal 	true to horizontal.
				 * @date 08/05/2012
				 * @author Yadickson Soto
				 */
				CounterStatWidget(IStatWidget * statWidget, bool horizontal = false);
				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	statName   	Name of the stat.
				 * @param	maxCount max count entry values
				 * @param	horizontal 	true to horizontal.
				 */

				CounterStatWidget(std::string statName, int maxCount, bool horizontal = false);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~CounterStatWidget();

				/**
				 * @brief	Gets the stat name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The stat name.
				 */

				std::string GetStatName();

				/**
				 * @brief	Gets the stat value.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The stat value.
				 */

				std::string GetStatValue();

				/**
				 * @brief	Sets a value.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	value	The value.
				 */

				void SetValue(std::string value);

				/**
				 * @brief	Align entry text.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	align	The align.
				 */

				void AlignEntryText(double align = 0.5);

				/**
				 * @brief	Align label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	align	The align.
				 */

				void AlignLabel(double align = 0.5);

				/**
				 * @brief	Sets an entry width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	width	The width.
				 */

				void SetEntryWidth(int width = 50);

				/**
				 * @brief	Sets an insensitive.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	insensitive	true to insensitive.
				 */

				void SetInsensitive(bool insensitive = true);

				/**
				 * @brief	Sets wight of label.
				 *
				 * @author	Juan.Delgado
				 * @date	22/07/2011
				 *
				 * @param	weight Weight of label
				 */
				void SetWeight(Pango::Weight weight);

				std::string getCode() const;

				void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration &labelConf);
				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 25/05/2012
				 * @author Yadickson Soto
				 */
				bool validate();

			protected:

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 * @param	horizontal 	true to horizontal.
				 */
				void Initialize(bool horizontal);

			private:
				
				Gtk::Alignment* alignEntry;
				Gtk::VBox* vbox;
				Gtk::Label* statNameLabel;  ///< The stat name label
				IStatWidget * statWidget; ///< statistic widget
			};
		}
	}
}

#endif // _COUNTER_STAT_WIDGET_H_
