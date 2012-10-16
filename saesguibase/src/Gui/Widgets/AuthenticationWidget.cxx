/**
 * @file AuthenticationWidget.cxx
 * @brief Body class authentication widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#include "AuthenticationWidget.hxx"
#include <Resources/election-string-resources-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <System/Sounds/smartmatic-sounds-manager.h>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Authenticator;

AuthenticationWidget::AuthenticationWidget(std::string composedTitleKey, PollingPlaceInfoWidget * info)
: StepWidget()
{
	this->composedTitleKey = composedTitleKey;
	this->info = info;
	this->mainFrame = NULL;
	this->mainHBox = NULL;
	this->infoFrame = NULL;
	this->keyHBox = NULL;
	this->topLabel = NULL;
	this->keyFrame = NULL;
	this->bottomLabel = NULL;
	this->mainVBox = NULL;
	this->leftLabel = NULL;
	this->alarmLabel = NULL;

	keypadTest = new KeypadWidget(CorrigeConfirma, true);
	keypadTest->keypadinterface = this;

	composedTitle = " ";
}

AuthenticationWidget::~AuthenticationWidget()
{
	dispose();
}

void AuthenticationWidget::dispose()
{
	this->remove();

	if (info)
	{
		delete info;
		info = NULL;
	}
	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainHBox)
	{
		delete mainHBox;
		mainHBox = NULL;
	}
	if (infoFrame)
	{
		delete infoFrame;
		infoFrame = NULL;
	}
	if (keyHBox)
	{
		delete keyHBox;
		keyHBox = NULL;
	}
	if (topLabel)
	{
		delete topLabel;
		topLabel = NULL;
	}
	if (keyFrame)
	{
		delete keyFrame;
		keyFrame = NULL;
	}
	if (bottomLabel)
	{
		delete bottomLabel;
		bottomLabel = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (keypadTest)
	{
		delete keypadTest;
		keypadTest = NULL;
	}
	if (leftLabel)
	{
		delete leftLabel;
		leftLabel = NULL;
	}
	if (alarmLabel)
	{
		delete alarmLabel;
		alarmLabel = NULL;
	}
}

void AuthenticationWidget::refresh()
{
	clearPassword();

	try
	{
		Voting::VotingDevice::Voting_booths::Voting_boothSequence & votingBooth (MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice().getVoting_booths().getVoting_booth());

		Glib::ustring versionValue = VERSION;
		Glib::ustring region1Value;
		Glib::ustring region2Value;
		Glib::ustring votingCenterValue;
		Glib::ustring votingCenterAddressValue;
		Glib::ustring electionNameValue = ElectionStringResourcesManager::Current()->getResource(MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection()->getElection().getName_key ());
		Glib::ustring registeredElectorsValue;
		Glib::ustring pollingStationCodeValue;
		Glib::ustring pollingStationNumberValue;

		if (votingBooth.size() > 0)
		{
			std::list < Voting::VotingDevice::Region_category > & regionCategoryList (
			MachineOperationManager::getInstance()->getElectoralConfiguration()->getRegionCategoryList());

			if (regionCategoryList.size() > 0)
			{
				Voting::VotingDevice::Region_category region1 = (*(regionCategoryList.begin()));
				region1Value = ElectionStringResourcesManager::Current()->getResource(region1.getRegion().getName_key());

				if (region1.getCategory() != NULL)
				{
					region2Value = ElectionStringResourcesManager::Current()->getResource(region1.getCategory().get().getRegion().getName_key());
				}
			}

			votingCenterValue = ElectionStringResourcesManager::Current()->getResource(votingBooth[0].getPolling_place_name ());
			votingCenterAddressValue = ElectionStringResourcesManager::Current()->getResource(votingBooth[0].getPolling_place_address());

			std::stringstream ss1;
			ss1 << votingBooth[0].getRegistered_electors();
			registeredElectorsValue = ss1.str();

			std::stringstream ss2;
			ss2 << votingBooth[0].getPolling_station_code();
			pollingStationCodeValue = ss2.str();

			std::stringstream ss3;
			ss3 << votingBooth[0].getPolling_station_number();
			pollingStationNumberValue = ss3.str();
		}

		composedTitle = Glib::ustring::compose(composedTitleKey,
		region1Value,
		region2Value,
		votingCenterValue,
		versionValue,
		votingCenterAddressValue,
		electionNameValue,
		registeredElectorsValue,
		pollingStationCodeValue,
		pollingStationNumberValue);
	}
	catch (...)
	{

	}

	if (info)
	{
		info->fillInfoWidget();
		info->show_all_children();
		info->show();
	}
}

std::string AuthenticationWidget::getTitleText()
{
	return composedTitle;
}

void AuthenticationWidget::clearPassword()
{
	textFeedBack = "";

	if (topLabel)
	{
		topLabel->set_text("");
	}
	if (bottomLabel)
	{
		bottomLabel->set_text("");
	}
	if (alarmLabel)
	{
		alarmLabel->set_text(_(MachineOperationManager::getInstance()->getAlarmController()->getMessage().c_str()));
	}
}

void AuthenticationWidget::checkPassword()
{
	IAuthenticator * authenticator = NULL;
	IAuthenticator::AuthenticationResultType mode;

	authenticator = MachineOperationManager::getInstance()->getAuthenticator();
	mode = authenticator->validate( textFeedBack );

	std::string SoundAuthenticationValid = SAESGUIConfigurationManager::Current()->getAuthenticationValidPasswordSound();
	std::string SoundAuthenticationInValid = SAESGUIConfigurationManager::Current()->getAuthenticationInvalidPasswordSound();

	textFeedBack.clear();

	if (topLabel)
	{
		topLabel->set_text("");
	}

	if(MachineOperationManager::getInstance()->getAlarmController()->isCriticalAlarmPending() &&
			mode != IAuthenticator::CLEAR_ALARM)
	{
		if (bottomLabel)
		{
			bottomLabel->set_label(_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.AlarmPending"));
		}
		return;
	}

	switch(mode)
	{
		case IAuthenticator::AUDIO_VOTING_PROCESS:
		case IAuthenticator::VOTING_PROCESS:
		case IAuthenticator::ELECTORAL_PROCESS:
		case IAuthenticator::WIZARD_MENU:
			if(!MachineOperationManager::getInstance()->getAlarmController()->isCriticalAlarmPending())
			{
				SMTTSoundsManager::Current()->Sound(SoundAuthenticationValid);
				MachineOperationManager::getInstance()->getAlarmController()->setMessage(" ");
				clearPassword();
				signalRunMachine.emit();
			}

			break;

		case IAuthenticator::MENU:
			SMTTSoundsManager::Current()->Sound(SoundAuthenticationValid);
			signalRunMenu.emit();
			break;

		case IAuthenticator::CLEAR_ALARM:
			if(MachineOperationManager::getInstance()->getAlarmController()->isAlarmPending())
			{
				MachineOperationManager::getInstance()->getAlarmController()->clearAlarms();
			}
			MachineOperationManager::getInstance()->getAlarmController()->setMessage(" ");
			clearPassword();
			break;

		case IAuthenticator::NO_MATCH:
			SMTTSoundsManager::Current()->Sound(SoundAuthenticationInValid);
			clearPassword();

			if (bottomLabel)
			{
				bottomLabel->set_label(_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.WrongPassword"));
			}
			break;

		default:
			break;
	}
}

void AuthenticationWidget::SetKey(KeysActionsCode value)
{
	SMTTSoundsManager::Current()->Sound(SMTTGUIConfigurationManager::Current()->getKeypadSound());

	switch(value)
	{
		case Key_0:
		case Key_Aaccent:
		case Key_Arroba:
		case Key_Pad0:
		case Key_Caps0:
			OnKeyPress(0);
			break;
		case Key_1:
		case Key_And:
		case Key_Alt1:
		case Key_F1:
		case Key_Pad1:
			OnKeyPress(1);
			break;
		case Key_2:
		case Key_Eaccent:
		case Key_Alt2:
		case Key_F2:
		case Key_Pad2:
		case Key_Caps2:
			OnKeyPress(2);
			break;
		case Key_3:
		case Key_Quote:
		case Key_F3:
		case Key_Pad3:
			OnKeyPress(3);
			break;
		case Key_4:
		case Key_SingleQuote:
		case Key_OpenKey:
		case Key_F4:
		case Key_Pad4:
			OnKeyPress(4);
			break;
		case Key_5:
		case Key_OpenParentheses:
		case Key_OpenBrace:
		case Key_F5:
		case Key_Pad5:
			OnKeyPress(5);
			break;
		case Key_6:
		case Key_Minus:
		case Key_Or:
		case Key_F6:
		case Key_Pad6:
			OnKeyPress(6);
			break;
		case Key_7:
		case Key_Eaccent2:
		case Key_Accent2:
		case Key_F7:
		case Key_Pad7:
		case Key_Caps7:
			OnKeyPress(7);
			break;
		case Key_8:
		case Key_MinusBig:
		case Key_BackSlash:
		case Key_F8:
		case Key_Pad8:
			OnKeyPress(8);
			break;
		case Key_9:
		case Key_Caccent:
		case Key_InversedV:
		case Key_F9:
		case Key_Pad9:
		case Key_Caps9:
			OnKeyPress(9);
			break;
		case Key_Numeral:
			checkPassword();
			break;
		case Key_BS:
		case Key_Asterisk:
			clearPassword();
			break;
		default:
			break;
	}
}

void AuthenticationWidget::OnKeyPress(int data)
{
	if (bottomLabel)
	{
		bottomLabel->set_label(" ");
	}

	if(data == kConfirma)
    {
		checkPassword();
    }
	else if(data == kCorrige)
    {
		clearPassword();
    }
	else
	{
		if (topLabel)
		{
			topLabel->set_text(topLabel->get_text() + "*");
		}
		textFeedBack.append(Glib::Ascii::dtostr(data));
	}
}

void AuthenticationWidget::OnKeyPressT9(char data)
{

}

sigc::signal<void> AuthenticationWidget::getSignalRunMenu()
{
	return signalRunMenu;
}

sigc::signal<void> AuthenticationWidget::getSignalRunMachine()
{
	return signalRunMachine;
}

void AuthenticationWidget::config()
{
	if (bottomLabel)
	{
		LabelConfiguration infoLabelConf = SAESGUIConfigurationManager::Current()->getAuthenticationInfoLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(bottomLabel, infoLabelConf);
	}
	if (topLabel)
	{
		LabelConfiguration passLabelConf = SAESGUIConfigurationManager::Current()->getAuthenticationPasswordLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(topLabel, passLabelConf);
	}
	if (alarmLabel)
	{
		LabelConfiguration alarmLabelConf = SAESGUIConfigurationManager::Current()->getAuthenticationAlarmLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(alarmLabel, alarmLabelConf);
	}

    alarmLabel->set_justify(Gtk::JUSTIFY_CENTER);
}
