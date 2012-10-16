/*
 * ActivationStatsWidget.cpp
 *
 *  Created on: Sep 6, 2011
 *      Author: juand
 */

 
 
 
#include "ActivationStatsWidget.h"
#include <Configuration/label-configuration.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Log/SMTTLogManager.h>
#include <Operation/Card/CardController.hxx>
#include <Operation/Card/CardMonitor.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <System/Exception/VotingDeviceException.hxx>
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <System/Utils/StringUtils.hxx>

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Utils;

bool ActivationStatsWidget::oneMemory = false;
ISMTTLog* ActivationStatsWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget",GETTEXT_PACKAGE);

ActivationStatsWidget::ActivationStatsWidget(CountConfiguration & totalCountType, bool showStatistic)
{
	this->totalCountType = totalCountType;

	ActivationConsolidationFunctionalityConfiguration config =
			SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration();
	LabelConfiguration titleLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTitleFontConfiguration());
	LabelConfiguration statLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getStatsActivationFontConfiguration());
	LabelConfiguration instructionLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getInstructionFontConfiguration());

	imageInsert = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif");
	imageExtract = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card.gif");
	imageExtractError = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card_error.gif");

	std::map < string, std::map < string, string > > statisticMap;

	std::map < string, string > insideStats;

	if(showStatistic)
	{
		insideStats[N_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalActivated")] =
				_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalActivated");
	}

	statisticMap[_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.GeneratedCards")] = insideStats;

	statsWidget = manage(new StatisticWidget(statisticMap));
	statsWidget->show();
	statsWidget->set_size_request(-1, config.getStatsActivationHeight());
	statsWidget->SetValuesWidth(60);
	statsWidget->SetTitlesSizeRequest(310, config.getTitleHeight());
	statsWidget->SetTitlesLabelConfiguration(titleLabelConfiguration);
	statsWidget->SetStatsLabelConfiguration(statLabelConfiguration);
	pack_start(*statsWidget, false, false);

	instructionLabel = manage(new Label());
	instructionLabel->show();
	instructionLabel->set_alignment(0, 0);
	//instructionLabel->set_size_request(310, -1);
	LabelConfiguration::SetLabelConfiguration(instructionLabel, instructionLabelConfiguration);
	//instructionLabel->set_line_wrap(true);
	//instructionLabel->set_line_wrap_mode(Pango::WRAP_WORD);

	pack_start(*instructionLabel, false, false, 10);

	cardImage = manage(new Image());
	cardImage->show();
	cardImage->set(imageInsert);
	pack_end(*cardImage,false,false, 20);

	timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getActivationStatsWidget();
	timerSleepWriteCard = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getTimerSleepWriteCard();

	show();

	threadIsAlive = false;
	disposeExecuted = false;
}

ActivationStatsWidget::~ActivationStatsWidget()
{
	while(threadIsAlive)
	{
		usleep(1000);
	}

	conn_checkCard.disconnect();
	conn_updateLabel.disconnect();
	conn_updateStat.disconnect();
	connSleepWriteCard.disconnect();

	if(!disposeExecuted)
	{
		CardMonitor::getInstance()->stop();
		CardController::getInstance()->dispose();
	}
}

void ActivationStatsWidget::Initialize()
{
	disposeExecuted = false;
	wasPresent = false;

	CardController::getInstance()->initialize();
	CardMonitor::getInstance()->start(timerRefresh);

	UpdateStat();

	updateLabel = _("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.InsertCardToActivate");
	instructionLabel->set_text(updateLabel);
	conn_checkCard.disconnect();
	conn_checkCard = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ActivationStatsWidget::CheckCardPresence),timerRefresh);
}

void ActivationStatsWidget::Dispose()
{
	disposeExecuted = true;

	conn_checkCard.disconnect();
	conn_updateLabel.disconnect();
	conn_updateStat.disconnect();

	CardMonitor::getInstance()->stop();
	CardController::getInstance()->dispose();
}


bool ActivationStatsWidget::CheckCardPresence()
{
	bool isPresent = CardMonitor::getInstance()->isCardPresent();

	if(isPresent && !wasPresent)
	{
		wasPresent = true;
		updateLabel = _("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ActivatingCardPleaseWait");
		instructionLabel->set_label(updateLabel);
		connSleepWriteCard.disconnect();

		if (timerSleepWriteCard > 0)
		{
			connSleepWriteCard = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ActivationStatsWidget::showMessageSleepWriteCard), timerSleepWriteCard);
		}

		Glib::Thread::create((sigc::mem_fun(*this, &ActivationStatsWidget::WriteCard)), false);
		return false;
	}
	else if(!isPresent && wasPresent)
	{
		wasPresent = false;
		updateLabel = _("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.InsertCardToActivate");
		instructionLabel->set_label(updateLabel);
		cardImage->set(imageInsert);
	}

	UpdateStat();

	return true;
}

void ActivationStatsWidget::SetAttributes(std::vector<Custom_attribute> attributes)
{
	this->attributes = attributes;
}

void ActivationStatsWidget::WriteCard()
{
	threadIsAlive = true;

	//Convert vector<Custom_attribute> to vector<Custom_attribute*>
	vector<Custom_attribute*> ptrAttributes;

	for(vector<Custom_attribute>::iterator iter = attributes.begin();
			iter != attributes.end(); iter++)
	{
		Custom_attribute* prtCustomAttr = new Custom_attribute(iter->getCode(), iter->getValue());
		ptrAttributes.push_back(prtCustomAttr);
	}

	if(WriteVotingCard(ptrAttributes))
	{
		updateLabel = _("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardWasActivated");
		error = false;
	}
	else
	{
		updateLabel = _("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData");
		error = true;
	}

	for(vector<Custom_attribute*>::iterator iter = ptrAttributes.begin();
			iter != ptrAttributes.end(); iter++)
	{
		delete *iter;
	}

	connSleepWriteCard.disconnect();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &ActivationStatsWidget::UpdateLabel), 0);
	conn_checkCard = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ActivationStatsWidget::CheckCardPresence),timerRefresh);

	sleep(1);	//this delay allow to see the writing card message
	threadIsAlive = false;
}

void ActivationStatsWidget::UpdateLabel()
{
	instructionLabel->set_text(updateLabel);

	if (error)
	{
		cardImage->set(imageExtractError);
	}
	else
	{
		cardImage->set(imageExtract);
	}
}

bool ActivationStatsWidget::UpdateStat()
{
	CountConfiguration::CountTypeSequence seq = totalCountType.getCountType();
	CountConfiguration::CountTypeIterator it;

	int total = 0;

	for (it = seq.begin();
		 it != seq.end();
		 it++)
	{
		switch (*it)
		{
			case CountTypeConfig::CONFIGURATION_TOTAL:
				total += MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalActivated();
				break;
			case CountTypeConfig::CONFIGURATION_OFFICIAL:
				total += MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalOfficialActivated();
				break;
			case CountTypeConfig::CONFIGURATION_DEMO:
				total += MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated();
				break;
			case CountTypeConfig::CONFIGURATION_RECOVERY:
				total += MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalRecoveryActivated();
				break;
			case CountTypeConfig::CONFIGURATION_SIMULATE:
				//TODO:
				break;
		}
	}

	if (statsWidget)
	{
		statsWidget->SetValue(N_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalActivated"), StringUtils::intToString(total));
	}

	return false;
}

bool ActivationStatsWidget::WriteVotingCard(std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute*> attributes)
{
	bool activationOK = false;

	try
	{
		Card_data cardData;
		CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes, cardData, true, Card_type::CARD_DATA_OFFICIAL_VOTE_CARD, false);

		if (!CardController::getInstance()->writeCardData(cardData))
		{
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivationCard"));
		}
		else
		{
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.CardWasActivatedSuccessfully"));

			MachineOperationManager::getInstance()->getActivatedCardStatistics()->RefreshStats(cardData);
			activationOK = true;
		}
	}
	catch (CryptoException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivatingCard"));
	}
	catch(SignedException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivatingCard"));
	}
	catch(XmlException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivatingCard"));
	}
	catch(VotingDeviceException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivatingCard"));
	}
	catch(...)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ActivationStatsWidget.ErrorActivatingCard"));
	}

	return activationOK;
}

void ActivationStatsWidget::SetOneMemoryMode(bool oneMemory)
{
	ActivationStatsWidget::oneMemory = oneMemory;
}

void ActivationStatsWidget::AllowCardActivation(bool allow)
{
	if(allow)
	{
		updateLabel = _("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.InsertCardToActivate");
		instructionLabel->set_label(updateLabel);

		conn_checkCard.disconnect();
		conn_checkCard = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ActivationStatsWidget::CheckCardPresence),timerRefresh);
	}
	else
	{
		updateLabel = _("Smartmatic.SAES.GUI.Widgets.ActivationStatsWidget.ActivationNotAllowed");
		instructionLabel->set_label(updateLabel);
		conn_checkCard.disconnect();
	}
}

void ActivationStatsWidget::ContinueOperation()
{
	Initialize();
}

void ActivationStatsWidget::StopOperation()
{
	Dispose();
}

bool ActivationStatsWidget::showMessageSleepWriteCard()
{
	updateLabel = _("Smartmatic.SAES.GUI.Widgets.ActivationStatsWidget.MessageSleepWriteCard");
	instructionLabel->set_label(updateLabel);
	return false;
}
