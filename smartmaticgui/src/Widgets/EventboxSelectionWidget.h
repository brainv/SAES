/*
 * EventboxSelectionWidget.h
 *
 *  Created on: Sep 5, 2011
 *      Author: Juan Delgado
 */

#ifndef EVENTBOXSELECTIONWIDGET_H_
#define EVENTBOXSELECTIONWIDGET_H_

#include <gtkmm.h>
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class EventboxSelectionWidget : public Gtk::VBox
			{
			public:
				/**
				 * @brief 	Constructor
				 *
				 * @author	Juan Delgado
				 *
				 * @param 	selectionMap, first-> title of options, second-> (map, first-> value of option, second-> name of option
				 */
				EventboxSelectionWidget(std::map<std::string, std::map< std::string, std::string > > selectionMap);

				/**
				 * @brief 	Destructor
				 *
				 * @author	Juan Delgado
				 */
				virtual ~EventboxSelectionWidget();

				/**
				 * @brief 	Get names of option selected
				 *
				 * @author	Juan Delgado
				 *
				 * @return	list with name selected
				 */
				std::list< std::string > GetNamesSelected();

				/**
				 * @brief	Get values of option selected
				 *
				 * @author	Juan Delgado
				 *
				 * @return	list with value selected
				 */
				std::list< std::string > GetValuesSelected();

				/**
				 * @brief	Set selected box color
				 *
				 * @author	Juan Delgado
				 *
				 * @param	selected box color
				 */
				void SetSelectedBoxColor(Gdk::Color color);

				/**
				 * @brief	Set unselected box color
				 *
				 * @author	Juan Delgado
				 *
				 * @param	unselected box color
				 */
				void SetUnselectedBoxColor(Gdk::Color color);

				/**
				 * @brief	Set selected font color
				 *
				 * @author	Juan Delgado
				 *
				 * @param	selected font color
				 */
				void SetSelectedFontColor(Gdk::Color color);

				/**
				 * @brief	Set unselected font color
				 *
				 * @author	Juan Delgado
				 *
				 * @pram	unselected font color
				 */
				void SetUnselectedFontColor(Gdk::Color color);

				/**
				 * @brief	Set selected label configuration
				 *
				 * @author	Juan Delgado
				 *
				 * @param	selected label configuration
				 */
				void SetSelectedFontDescription(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfiguration);

				/**
				 * @brief	Set unselected label configuration
				 *
				 * @author	Juan Delgado
				 *
				 * @param	unselected label configuration
				 */
				void SetUnselectedFontDescription(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfiguration);

				/**
				 * @brief	Set titles label configuration
				 *
				 * @author	Juan Delgado
				 *
				 * @param	titles label configuration
				 */
				void SetTitlesFontDescription(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfiguration);

				/**
				 * @brief	Set titles height
				 *
				 * @author	Juan Delgado
				 *
				 * @param	titles height
				 */
				void SetTitlesHeight(int height);


				/**
				 * @brief	Set first element selected
				 *
				 * @author	Juan Delgado
				 */
				void SetFirstSelected();

				/**
				 * @brief	set_size_request
				 *
				 * @author	Juan Delgado
				 *
				 * @param	int width request
				 * @param	int height request
				 */
				virtual void set_size_request(int width, int height);

				/**
				 * @brief	Signal returns list of boxs selected
				 *
				 * @author	Juan Delgado
				 */
				typedef sigc::signal< void, std::list< std::string > > type_box_clicked;

				/**
				 * @brief	Signal to receive when a box is clicked
				 *
				 * @author	Juan Delgado
				 *
				 * @return	connection signal
				 */
				type_box_clicked signal_box_clicked();

			protected:
				type_box_clicked m_type_box_clicked;

				/**
				 * @brief	Handles option selected
				 *
				 * @author	Juan Delgado
				 *
				 * @return	true if handle
				 */
				bool on_event_selected(GdkEventButton* event, std::string value);

				/**
				 * @brief	Set event box selected
				 *
				 * @author	Juan Delgado
				 *
				 * @param	isSelected, true if is selected
				 * @param	label to be changed
				 * @param	eventbox to be change
				 */
				void SetEventboxSelected(bool isSelected, Gtk::Label* label, Gtk::EventBox* eventbox);

				int widthRequested;	///< the width requested
				Gdk::Color selectedBoxColor;	///< the selected box color
				Gdk::Color unselectedBoxColor;	///< the unselected box color
				Gdk::Color selectedFontColor;	///< the selected font color
				Gdk::Color unselectedFontColor;	///< the unselected font color
				Smartmatic::GUI::Configuration::LabelConfiguration selectedLabelConfiguration; ///< the selected label configuration
				Smartmatic::GUI::Configuration::LabelConfiguration unselectedLabelConfiguration; ///< the unselected label configuration
				std::map < std::string, std::map < std::string, std::string > > selectionMap;	///< the selection map
				std::map < std::string, std::string > namesSelected;	///< the map of names selected
				std::map < std::string, std::string > valuesSelected; ///< the map of values selected
				std::map < std::string, Gtk::EventBox* > eventboxMap;	///< the eventbox map
				std::map < std::string, Gtk::Label* > labelMap;		///< the label map
				std::list < Gtk::Label* > titleLabelList;	///< the title label list

			};
		}
	}
}

#endif /* EVENTBOXSELECTIONWIDGET_H_ */
