/*
 * CardActivatorEventBox.h
 *
 *  Created on: Sep 6, 2011
 *      Author: Juan Delgado
 */

#ifndef CARDACTIVATOREVENTBOX_H_
#define CARDACTIVATOREVENTBOX_H_

#include <gtkmm.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Widgets/EventboxSelectionWidget.h>
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class CardActivatorEventBox : public Gtk::VBox
				{
				public:
					/**
					 * @brief	Constructor
					 *
					 * @author	Juan Delgado
					 *
					 * @param	width of widget
					 */
					CardActivatorEventBox(int width);

					/**
					 * @brief	finalizer
					 *
					 * @author	Juan Delgado
					 */
					virtual ~CardActivatorEventBox();

					/**
					 * @brief	Retur vector with custom attributes selected
					 *
					 * @author	Juan Delgado
					 *
					 * @return	vector with custom attributes selecteds
					 */
					std::vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > GetCustomAttributes();

					/**
					 * @brief	Signal returns vector of custom attribute selected
					 *
					 * @author	Juan Delgado
					 */
					typedef sigc::signal< void, std::vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > > type_vectorCA_changed;

					/**
					 * @brief	Signal to receive when a custom attribute change
					 *
					 * @author	Juan Delgado
					 *
					 * @return	connection signal
					 */
					type_vectorCA_changed signal_vectorCustomAttribute_changed();

					void setFont(Smartmatic::GUI::Configuration::LabelConfiguration & titleLabelConfiguration,
							Smartmatic::GUI::Configuration::LabelConfiguration & selectedLabelConfiguration,
							Smartmatic::GUI::Configuration::LabelConfiguration & unselectedLabelConfiguration);

				protected:
					type_vectorCA_changed m_type_vector_changed;

				private:
					/**
					 * @brief	handles eventBox clicked event
					 *
					 * @author	Juan Delgado
					 *
					 * @param	list of values selected
					 */
					void on_EventboxClicked(std::list< std::string > valuesSelected);

					std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > listCAD;	///< The list of custom attributes definition
					std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute> attributes;  ///< The attributes
					Smartmatic::GUI::Widgets::EventboxSelectionWidget* eventboxSelectionWidget;	///< The eventbox selection widget
				};
			}
		}
	}
}

#endif /* CARDACTIVATOREVENTBOX_H_ */
