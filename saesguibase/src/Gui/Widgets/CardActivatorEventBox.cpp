/**
 * @file CardActivactorEventBox.cpp
 * @brief Body class card activator event box
 * @date 06/09/2011
 * @author Juan Delgado
 */

#include "CardActivatorEventBox.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Resources/election-string-resources-manager.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/SaesGUIConfiguration-schema.hxx>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Gtk;
using namespace std;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting::VotingDevice;

CardActivatorEventBox::CardActivatorEventBox(int width)
{
	static ActivationConsolidationFunctionalityConfiguration config =
			SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration();

	static LabelConfiguration selectedLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getLabelSelectedConfiguration());

	static LabelConfiguration unselectedLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getLabelUnselectedConfiguration());

	static LabelConfiguration titleLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTitleFontConfiguration());

	Gdk::Color selectedBoxColor;
	selectedBoxColor.set_rgb(config.getSelectedBoxColor().getRed(),
			config.getSelectedBoxColor().getGreen(), config.getSelectedBoxColor().getBlue());

	Gdk::Color unselectedBoxColor;
	unselectedBoxColor.set_rgb(config.getUnselectedBoxColor().getRed(),
			config.getUnselectedBoxColor().getGreen(), config.getUnselectedBoxColor().getBlue());

	Gdk::Color selectedFontColor;
	selectedFontColor.set_rgb(config.getSelectedFontColor().getRed(),
			config.getSelectedFontColor().getGreen(), config.getSelectedFontColor().getBlue());

	Gdk::Color unselectedFontColor;
	unselectedFontColor.set_rgb(config.getUnselectedFontColor().getRed(),
			config.getUnselectedFontColor().getGreen(), config.getUnselectedFontColor().getBlue());

	std::map< string, std::map< string, string > > eventboxSelectionMap;

	if(MachineOperationManager::getInstance()->getElectoralConfiguration() != NULL)
	{
		try
		{
			listCAD = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(
				MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice(),
				Machine_type::VOTING_DEVICES_PM);
		}
		catch (...)
		{

		}

		for(list<Custom_attribute_definition>::iterator iter = listCAD.begin(); iter != listCAD.end(); iter++)
		{
			std::map< string, string > customAttrMap;

			for ( Custom_attribute_definition::ValueIterator cad = iter->getValue().begin(); cad != iter->getValue().end(); cad++)
			{
				customAttrMap[*cad] = ElectionStringResourcesManager::Current()->getResource(*cad);
			}

			string s = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CardActivactorEventBox.TitleCustomAttribute"), ElectionStringResourcesManager::Current()->getResource(iter->getName_key()));
			eventboxSelectionMap[s] = customAttrMap;
		}
	}

	eventboxSelectionWidget = manage(new EventboxSelectionWidget(eventboxSelectionMap));
	eventboxSelectionWidget->SetSelectedBoxColor(selectedBoxColor);
	eventboxSelectionWidget->SetUnselectedBoxColor(unselectedBoxColor);
	eventboxSelectionWidget->SetSelectedFontColor(selectedFontColor);
	eventboxSelectionWidget->SetUnselectedFontColor(unselectedFontColor);
	eventboxSelectionWidget->SetTitlesFontDescription(titleLabelConfiguration);
	eventboxSelectionWidget->SetSelectedFontDescription(selectedLabelConfiguration);
	eventboxSelectionWidget->SetUnselectedFontDescription(unselectedLabelConfiguration);
	eventboxSelectionWidget->set_size_request(width, -1);
	eventboxSelectionWidget->SetTitlesHeight(config.getTitleHeight());
	eventboxSelectionWidget->signal_box_clicked().connect(sigc::mem_fun(*this, &CardActivatorEventBox::on_EventboxClicked));
	eventboxSelectionWidget->SetFirstSelected();
	eventboxSelectionWidget->show();

	pack_start(*eventboxSelectionWidget);
}

CardActivatorEventBox::~CardActivatorEventBox()
{

}

void CardActivatorEventBox::on_EventboxClicked(std::list< std::string > valuesSelected)
{
	attributes.clear();

	for(list< string >::iterator iter = valuesSelected.begin();
			iter != valuesSelected.end(); iter++)
	{
		for(list < Custom_attribute_definition >::iterator iter2 = listCAD.begin();
				iter2 != listCAD.end(); iter2++)
		{
			for (Custom_attribute_definition::ValueIterator cad = iter2->getValue().begin();
					cad != iter2->getValue().end(); cad++)
			{
				if(*cad == *iter)
				{
					Custom_attribute ca;
					ca.setCode(iter2->getCode());
					ca.setValue(*iter);
					attributes.push_back(ca);
					break;
				}
			}
		}
	}

	m_type_vector_changed.emit(attributes);
}

std::vector< Custom_attribute > CardActivatorEventBox::GetCustomAttributes()
{
	return attributes;
}

CardActivatorEventBox::type_vectorCA_changed CardActivatorEventBox::signal_vectorCustomAttribute_changed()
{
	return m_type_vector_changed;
}

void CardActivatorEventBox::setFont(LabelConfiguration & titleLabelConfiguration, LabelConfiguration & selectedLabelConfiguration, LabelConfiguration & unselectedLabelConfiguration)
{
	eventboxSelectionWidget->SetTitlesFontDescription(titleLabelConfiguration);
	eventboxSelectionWidget->SetSelectedFontDescription(selectedLabelConfiguration);
	eventboxSelectionWidget->SetUnselectedFontDescription(unselectedLabelConfiguration);
	eventboxSelectionWidget->SetFirstSelected();
	eventboxSelectionWidget->show();
}
