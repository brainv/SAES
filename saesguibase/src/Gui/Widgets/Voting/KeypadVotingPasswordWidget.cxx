/**
 * @file	KeypadVotingPasswordWidget.cxx
 * @brief	Key pad password widget.
 * @author	Yadickson Soto
 * @date	17/04/2012
 */

#include "KeypadVotingPasswordWidget.hxx"
#include "Environment/Configurations/resource-path-provider.h"
#include "Configuration/label-configuration.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/GeneratedClasses/Configuration/SaesGUIConfiguration-schema.hxx"
#include <Operation/MachineOperationManager.hxx>

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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Configuration;

KeypadVotingPasswordWidget::KeypadVotingPasswordWidget ()
: VMAuthenticationWidget(NULL)
{
	infoLabel = new Gtk::Label();

	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->getAuthenticationVotingInfoLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(infoLabel, labelConf);

	infoLabel->set_justify(Gtk::JUSTIFY_CENTER);
	infoLabel->set_text(_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.CancelVoteKeyPadStr"));
	infoFrame->add(*infoLabel);

	setTitle(false);
	setShowBorder(true);
}

KeypadVotingPasswordWidget::~KeypadVotingPasswordWidget()
{
	remove();

	if (infoLabel)
	{
		delete infoLabel;
		infoLabel = NULL;
	}

	VMAuthenticationWidget::dispose();
}

void KeypadVotingPasswordWidget::checkPassword()
{
	std::string password = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice(). getOperation_modes().getOperation_mode()[0].getUnblocking_key();

	if(textFeedBack == password)
	{
		clearPassword();
		signalOk.emit();
	}
	else if (bottomLabel)
	{
		clearPassword();
		bottomLabel->set_label(_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.WrongPassword"));
	}
}

sigc::signal<void> KeypadVotingPasswordWidget::getSignalOk()
{
	return signalOk;
}
