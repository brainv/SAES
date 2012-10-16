/**
 * @file SimulationWidget.cxx
 * @brief Body class nationality widget
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#include "SimulationWidget.hxx"
#include <Operation/MachineOperationManager.hxx>
#include <Resources/election-string-resources-manager.h>
#include <Voting/VotingDevice/card-data-wrapper.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::GUI::Configuration;

SimulationWidget::SimulationWidget()
: ChooseSelectionWidget()
{
	std::list < Custom_attribute_definition > listCAD;
	std::list < Custom_attribute_definition >::iterator it;

	Voting_device vd = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
	listCAD = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, Machine_type::VOTING_DEVICES_PM);

	for( it = listCAD.begin();
			it != listCAD.end();
			it++)
	{
		std::vector < ChooseDialogButtonInfo * > choices;

		for ( Custom_attribute_definition::ValueIterator c ((*it).getValue().begin()); c != (*it).getValue().end(); ++c)
		{
			ChooseDialogButtonInfo* info = new ChooseDialogButtonInfo(ElectionStringResourcesManager::Current()->getResource(*c), "",(*it).getCode(), (*c));
			choices.push_back (info);
		}

		ChooseDialogInfo *infoDiag = new ChooseDialogInfo(_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CustomAttributeSelection"),
				it->getName_key(),
				"",
				ElectionStringResourcesManager::Current()->getResource(it->getName_key()),
				choices,
				false);

		infoList.push_back(infoDiag);
	}

	setTitle(false);
	setShowBorder(true);
	setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName());

	initialize();
}

SimulationWidget::~SimulationWidget()
{
	remove();

	std::vector <ChooseDialogInfo *>::iterator it;

	for (it = infoList.begin();
			it != infoList.end();
			it++)
	{
		ChooseDialogInfo * info = (*it);
		delete info;
		info = NULL;
	}

	ChooseSelectionWidget::dispose();
}

void SimulationWidget::initialize()
{
	currentInfo = 0;
	options.clear();
	next();
}

void SimulationWidget::next()
{
	if (currentInfo < infoList.size())
	{
		setShowBack(false);
		setChooseInfo(infoList[currentInfo]);
		/*
		int width = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowWith();
		int height = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowHeight();
		setInternalSizeWidget(width, height);
		 */
		chooseDialogWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
		currentInfo++;
	}
	else
	{
		signalEnd.emit();
	}
}

void SimulationWidget::onSelected(ChooseDialogButtonInfo* choose)
{
	if (choose)
	{
		options.push_back(choose);
	}

	next();
}

std::vector <ChooseDialogButtonInfo*> & SimulationWidget::getOptionsSelected()
{
	return options;
}

void SimulationWidget::getCardData(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData)
{
	std::vector < ChooseDialogButtonInfo * >::iterator choose;

	std::vector < Custom_attribute * > attributes;
	std::vector < Custom_attribute * >::iterator it;

	for (choose = options.begin();
			choose != options.end();
			choose++)
	{
		Custom_attribute  * attribute = new Custom_attribute();

		attribute->setCode((*choose)->getCode());
		attribute->setValue((*choose)->getOption());
		attributes.push_back(attribute);
	}

	CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes, cardData, true, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD, false);

	for (it = attributes.begin();
			it != attributes.end();
			it++)
	{
		Custom_attribute  * attribute = (*it);
		delete attribute;
		attribute = NULL;
	}
}
