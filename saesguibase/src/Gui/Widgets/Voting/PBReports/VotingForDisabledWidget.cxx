/**
 * @file VotingForDisabledWidget.cxx
 * @brief Header class voting for disabled
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#include "VotingForDisabledWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Widgets/BoolStatWidget.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::Log;

ISMTTLog* VotingForDisabledWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledWidget",GETTEXT_PACKAGE);

VotingForDisabledWidget::VotingForDisabledWidget()
: StepWidget()
{
	votingForDisabledRegisterWidget = NULL;
	votingForDisabledQuestionWidget = NULL;
	votingForDisabledInfoWidget = NULL;

	initialize();
	load();
}

VotingForDisabledWidget::~VotingForDisabledWidget()
{
	dispose();
}

void VotingForDisabledWidget::initialize()
{
	dispose();

	votingForDisabledRegisterWidget = new VotingForDisabledRegisterWidget();
	votingForDisabledQuestionWidget = new VotingForDisabledQuestionWidget();
	votingForDisabledInfoWidget = new VotingForDisabledInfoWidget();

	votingForDisabledRegisterWidget->getSignalAddInfoButton().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::showQuestion));
	votingForDisabledRegisterWidget->getSignalClicked().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::editInfo));

	votingForDisabledQuestionWidget->getSignalAssistedButton().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::addAssistedInfo));
	votingForDisabledQuestionWidget->getSignalAccompaniedButton().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::addAccompaniedInfo));

	votingForDisabledInfoWidget->getSignalCancelInfoButton().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::cancelInfo));
	votingForDisabledInfoWidget->getSignalSaveInfoButton().connect(sigc::mem_fun(*this, &VotingForDisabledWidget::saveInfo));
}

void VotingForDisabledWidget::dispose()
{
	remove();

	if (votingForDisabledRegisterWidget)
	{
		delete votingForDisabledRegisterWidget;
		votingForDisabledRegisterWidget = NULL;
	}
	if (votingForDisabledQuestionWidget)
	{
		delete votingForDisabledQuestionWidget;
		votingForDisabledQuestionWidget = NULL;
	}
	if (votingForDisabledInfoWidget)
	{
		delete votingForDisabledInfoWidget;
		votingForDisabledInfoWidget = NULL;
	}
}

void VotingForDisabledWidget::showQuestion()
{
	setWidget(votingForDisabledQuestionWidget);
}

void VotingForDisabledWidget::load()
{
	VotingDisabledInformation info = MachineOperationManager::getInstance()->getVotingDisabledWrapper()->getVotingDisabledInformation();
	VotingDisabledInformation::VotingDisabledIterator it;

	for (it = info.getVotingDisabled().begin();
			it != info.getVotingDisabled().end();
			it++)
	{
		VotingDisabled votingDisabled = (*it);
		votingForDisabledRegisterWidget->addWidget(manage(new VotingForDisabledRegisterInfoWidget(votingDisabled)));
	}

	votingForDisabledRegisterWidget->setCurrentPage(0);
	setWidget(votingForDisabledRegisterWidget);
}

void VotingForDisabledWidget::addAssistedInfo()
{
	signalDisabled.emit();
	logger->Debug("addAssistedInfo");

	VotingDisabled votingDisabled;
	createVotingDisabled(votingDisabled);
	votingDisabled.setType(VotingDisabledType::VOTING_DISABLED_ASSISTED);
	votingForDisabledInfoWidget->setRegisterInfoWidget(manage(new VotingForDisabledRegisterInfoWidget(votingDisabled)));

	setWidget(votingForDisabledInfoWidget);
}

void VotingForDisabledWidget::addAccompaniedInfo()
{
	signalDisabled.emit();
	logger->Debug("addAccompaniedInfo");

	VotingDisabled votingDisabled;
	createVotingDisabled(votingDisabled);
	votingDisabled.setType(VotingDisabledType::VOTING_DISABLED_ACCOMPANIED);
	votingForDisabledInfoWidget->setRegisterInfoWidget(manage(new VotingForDisabledRegisterInfoWidget(votingDisabled)));

	setWidget(votingForDisabledInfoWidget);
}

void VotingForDisabledWidget::saveInfo()
{
	try
	{
		bool modify = MachineOperationManager::getInstance()->getVotingDisabledWrapper()->modifyVotingDisabled(votingForDisabledInfoWidget->getRegisterInfoWidget()->getVotingDisabled());
		MachineOperationManager::getInstance()->getVotingDisabledWrapper()->persistence();
		votingForDisabledInfoWidget->getRegisterInfoWidget()->refresh();

		if (!modify)
		{
			votingForDisabledRegisterWidget->addWidget(votingForDisabledInfoWidget->getRegisterInfoWidget());
			votingForDisabledInfoWidget->setRegisterInfoWidget(NULL);
		}
	}
	catch(...)
	{
		logger->Debug("ERROR save info");
	}

	setWidget(votingForDisabledRegisterWidget);
	signalEnabled.emit();
}

void VotingForDisabledWidget::cancelInfo()
{
	logger->Debug("cancelInfo");
	votingForDisabledInfoWidget->setRegisterInfoWidget(NULL);
	setWidget(votingForDisabledRegisterWidget);
	signalEnabled.emit();
}

void VotingForDisabledWidget::editInfo(VotingForDisabledRegisterInfoWidget * widget)
{
	votingForDisabledInfoWidget->setRegisterInfoWidget(widget);
	setWidget(votingForDisabledInfoWidget);
	signalDisabled.emit();
}

void VotingForDisabledWidget::createVotingDisabled(Smartmatic::SAES::Voting::PBReports::VotingDisabled & votingDisabled)
{
	IDCardInfo info("", "");
	votingDisabled.setCustom_code("");
	votingDisabled.setCreate_date("");
	votingDisabled.setDisabled(BoolStatWidget::None);
	votingDisabled.setApproved(BoolStatWidget::None);
	votingDisabled.setVoter(info);
	votingDisabled.setHelper(info);
	votingDisabled.setDescription("");
}

sigc::signal<void> VotingForDisabledWidget::getSignalEnabled()
{
	return signalEnabled;
}

sigc::signal<void> VotingForDisabledWidget::getSignalDisabled()
{
	return signalDisabled;
}
