/**
 * @file VotingForDisabledRegisterInfoWidget.cxx
 * @brief Body voting for disabled register info widget
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#include "VotingForDisabledRegisterInfoWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
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
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* VotingForDisabledRegisterInfoWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget",GETTEXT_PACKAGE);

VotingForDisabledRegisterInfoWidget::VotingForDisabledRegisterInfoWidget(VotingDisabled & votingDisabled)
: RegisterInfoWidget()
{
	this->votingDisabled = votingDisabled;
	getSignalClick().connect(sigc::mem_fun(*this, &VotingForDisabledRegisterInfoWidget::clicked));

	RegisterWidgetConfiguration config = SAESGUIConfigurationManager::Current()->getVotingForDisabledFunctionalityConfiguration().getRegisterWidgetConfiguration();
	showHeader(config.getShowHeader());
	showCenter(config.getShowCenter());
	showBottom(config.getShowBottom());

	refresh();
}

VotingForDisabledRegisterInfoWidget::~VotingForDisabledRegisterInfoWidget()
{

}

void VotingForDisabledRegisterInfoWidget::refresh()
{
	clearAll();

	std::string voter;
	std::string helper;
	std::string disabled;
	std::string approved;

	switch(votingDisabled.getType())
	{
		case VotingDisabledType::VOTING_DISABLED_ASSISTED:
			addHeader("", _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.Assisted"));
			helper = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget.Assistant");
			break;
		case VotingDisabledType::VOTING_DISABLED_ACCOMPANIED:
			addHeader("", _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.Accompanied"));
			helper = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget.Accompanist");
			break;
	}

	voter = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget.Voter");
	voter.append(" :");

	helper.append(" :");

	disabled = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget.Disabled");
	disabled.append(" :");

	approved = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledRegisterInfoWidget.Approved");
	approved.append(" :");

	addCenter(voter, votingDisabled.getVoter().getFirstName() + " " + votingDisabled.getVoter().getSurname());
	addCenter(helper, votingDisabled.getHelper().getFirstName() + " " + votingDisabled.getHelper().getSurname());

	std::string disabledResponse;
	std::string approvedResponse;

	if (votingDisabled.getDisabled() == BoolStatWidget::True)
	{
		disabledResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.DisabledYes");
	}
	else if (votingDisabled.getDisabled() == BoolStatWidget::False)
	{
		disabledResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.DisabledNo");
	}
	else
	{
		disabledResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.DisabledNone");
	}

	if (votingDisabled.getApproved() == BoolStatWidget::True)
	{
		approvedResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.ApprovedYes");
	}
	else if (votingDisabled.getApproved() == BoolStatWidget::False)
	{
		approvedResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.ApprovedNo");
	}
	else
	{
		approvedResponse = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.ApprovedNone");
	}

	//addCenter(disabled, disabledResponse);
	addCenter(approved, approvedResponse);
}

VotingDisabled & VotingForDisabledRegisterInfoWidget::getVotingDisabled()
{
	return votingDisabled;
}

void VotingForDisabledRegisterInfoWidget::clicked(bool state)
{
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingForDisabledRegisterInfoWidget::emitClicked), 0);
}

void VotingForDisabledRegisterInfoWidget::emitClicked()
{
	signalClicked.emit(this);
}

sigc::signal<void, VotingForDisabledRegisterInfoWidget *> VotingForDisabledRegisterInfoWidget::getSignalClicked()
{
	return signalClicked;
}
