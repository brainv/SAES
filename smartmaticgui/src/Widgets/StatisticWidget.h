/*
 * StatisticWidget.h
 *
 *  Created on: Sep 6, 2011
 *      Author: Juan Delgado
 */

#ifndef STATISTICWIDGET_H_
#define STATISTICWIDGET_H_

#include <gtkmm.h>
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class StatisticWidget : public Gtk::VBox
			{
			public:
				/**
				 * @brief	Constructor
				 *
				 * @author	Juan Delgado
				 *
				 * @param 	selectionMap, first-> title of options, second-> (map, first-> value of option, second-> name of option
				 */
				StatisticWidget(std::map<std::string, std::map< std::string, std::string > > statisticMap);

				/**
				 * @brief	Destructor
				 *
				 * @author	Juan Delgado
				 */
				virtual ~StatisticWidget();

				/**
				 * @brief	Set value of a particular stat
				 *
				 * @author	Juan Delgado
				 *
				 * @param	code of stat
				 * @param	value of stat
				 */
				void SetValue(std::string codeStat, std::string value);

				/**
				 * @brief	Get value of a particular stat
				 *
				 * @author	Juan Delgado
				 *
				 * @param	code of stat
				 * @return	value of stat
				 */
				std::string GetValue(std::string codeStat);

				/**
				 * @brief	Set stats label configuration
				 *
				 * @author	Juan Delgado
				 *
				 * @param	stats label configuration
				 */
				void SetStatsLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfiguration);

				/**
				 * @brief	Set titles label configuration
				 *
				 * @author	Juan Delgado
				 *
				 * @param	titles label configuration
				 */
				void SetTitlesLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfiguration);

				/**
				 * @brief	Set titles size request
				 *
				 * @author	Juan Delgado
				 *
				 * @param	titles height
				 * @param	titles width
				 */
				void SetTitlesSizeRequest(int width, int height);

				/**
				 * @brief	Set value width
				 *
				 * @author	Juan Delgado
				 *
				 * @param	values height
				 */
				void SetValuesWidth(int width);

			protected:
				std::map < std::string, Gtk::Label* > valuesMap;	///< the values map
				std::map < std::string, std::map < std::string, std::string > > statisticMap;	///< the statistic map

				std::list <Gtk::Label* > titleLabelList;	///< the title label list
				std::list <Gtk::Label* > statsLabelList;	///< the stats label list


			};
		}
	}
}

#endif /* STATISTICWIDGET_H_ */
