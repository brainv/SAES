/*
 * VMInstallMachineWidget.cxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#include "VMInstallMachineWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Gui/Widgets/VMProgressWidget.hxx>
#include <Gui/Widgets/VMPollingPlaceInfoWidget.hxx>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/Card/CardController.hxx>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::Log;

ISMTTLog* VMInstallMachineWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.VMInstallMachineWidget",GETTEXT_PACKAGE);

VMInstallMachineWidget::VMInstallMachineWidget(ProgressWidget * progressWidget, PollingPlaceInfoWidget * pollingPlaceInfoWidget)
: InstallMachineWidget(), progressWidget(progressWidget), pollingPlaceInfoWidget(pollingPlaceInfoWidget)
{
	this->installWidget = NULL;
	this->infoMessage = NULL;
	this->messageError = NULL;

	initialize();
	login();
}

VMInstallMachineWidget::~VMInstallMachineWidget()
{
	dispose();
}

void VMInstallMachineWidget::dispose()
{
	this->remove();

	if (installWidget)
	{
		delete installWidget;
		installWidget = NULL;
	}
	if (progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
	if (infoMessage)
	{
		delete infoMessage;
		infoMessage = NULL;
	}
	if (pollingPlaceInfoWidget)
	{
		delete pollingPlaceInfoWidget;
		pollingPlaceInfoWidget = NULL;
	}
	if (messageError)
	{
		delete messageError;
		messageError = NULL;
	}
}

void VMInstallMachineWidget::initialize()
{
	installWidget = new VMInstallationWidget();

	switch (SAESGUIConfigurationManager::Current()->GetVMInstallationConfiguration().getType())
	{
		case VMInstallationWidgetTypeConfiguration::CONFIGURATION_ONLYKEYWORDXML:
			installWidget->setVMInstallationWidgetType(Smartmatic::GUI::Widgets::OnlyKeyWord);
			break;
		case VMInstallationWidgetTypeConfiguration::CONFIGURATION_ONLYTOKENXML:
			installWidget->setVMInstallationWidgetType(Smartmatic::GUI::Widgets::OnlyToken);
			break;
		case VMInstallationWidgetTypeConfiguration::CONFIGURATION_KEYWORDANDTOKENXML:
			installWidget->setVMInstallationWidgetType(Smartmatic::GUI::Widgets::keywordAndToken);
			break;
	}

	int buttonWidth = SAESGUIConfigurationManager::Current()->GetVMInstallationConfiguration().getButtonsWidth();
	int buttonHeight = SAESGUIConfigurationManager::Current()->GetVMInstallationConfiguration().getButtonsHeight();

	installWidget->set_shadow_type(Gtk::SHADOW_NONE);
	installWidget->Initialize();
	installWidget->SetButtonSize(buttonWidth - 20, buttonHeight - 10);
	installWidget->SetMessageFont(SAESGUIConfigurationManager::Current()->GetWelcomeContestCenterLabelConfiguration());

	progressWidget->setImage(ProgressWidget::PROGRESS);
	progressWidget->setTitle(" ");
	progressWidget->setText(_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.ProgressMessage"));
	progressWidget->setTextConfig(SAESGUIConfigurationManager::Current()->GetWelcomeContestCenterLabelConfiguration());

	messageError = new Gtk::Label();
	messageError->set_label(_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.AuthenticationFailed"));

	Pango::FontDescription font = messageError->get_style()->get_font();
	font.set_size(15*Pango::SCALE);
	messageError->modify_font(font);

	infoMessage = new VMInstallationConfirmation();

	infoMessage->getSignalButtonBackClicked().connect(sigc::mem_fun(*this,&VMInstallMachineWidget::login));
	infoMessage->getSignalButtonOkClicked().connect(sigc::mem_fun(*this,&VMInstallMachineWidget::end));

	installWidget->signalEnter_detected.connect(sigc::mem_fun(*this,&VMInstallMachineWidget::authentication));

	if (VotingCentersWrapper::getInstance()->getVotingCenters().size() == 1)
	{
		VotingCenter votingCenter;
		VotingCentersWrapper::getInstance()->getInstallationVotingCenter(votingCenter);
		center = votingCenter.getCode();
	}


}

void VMInstallMachineWidget::login()
{
	this->loginOk = false;
	this->wasPresent = false;
	CardController::getInstance()->initialize();
	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getVMInstallationWindow();
	conn.disconnect();
	installWidget->ResetWidgets();
	installWidget->ClearPassword();
	setWidget(installWidget);
	conn = Glib::signal_timeout().connect (sigc::mem_fun (*this, &VMInstallMachineWidget::checkCard), timerRefresh);
}

void VMInstallMachineWidget::authentication(std::string password)
{
	this->password = password;
	showProgressLogin();
}

void VMInstallMachineWidget::showProgressLogin()
{
	setWidget(progressWidget);
    if(!Glib::thread_supported()) Glib::thread_init();
    Glib::Thread::create(sigc::mem_fun(*this, &VMInstallMachineWidget::checkData), false);
}

void VMInstallMachineWidget::checkData()
{
	loginOk = MachineOperationManager::getInstance()->authentication(center, password, true);
    Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VMInstallMachineWidget::showInfo), 250);
}

bool VMInstallMachineWidget::checkCard()
{
	bool cardPresent = CardController::getInstance()->isCardPresent();

	if ( !cardPresent  && wasPresent )
	{
		wasPresent = false;
	}
	else if(cardPresent && !wasPresent)
	{
		wasPresent = true;
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VMInstallMachineWidget::readCard), 50);
		return false;
	}

	return true;
}

void VMInstallMachineWidget::readCard()
{
	try
	{
		CardController::getInstance()->readToken(this->password);
	}
	catch (...)
	{
		logger->Debug("ERROR read card data");
		password = "";
	}

	showProgressLogin();
}

void VMInstallMachineWidget::showInfo()
{
	if (!loginOk)
	{
		logger->Debug("Error authentication");
		infoMessage->setInfoWidget(messageError);
		infoMessage->showButtonBack();
		infoMessage->hideButtonOk();
	}
	else
	{
		logger->Debug("authentication ok");
		pollingPlaceInfoWidget->fillInfoWidget();
		infoMessage->setInfoWidget(pollingPlaceInfoWidget);
		infoMessage->hideButtonBack();
		infoMessage->showButtonOk();
	}

	setWidget(infoMessage);
}

void VMInstallMachineWidget::end()
{
	stop();
	MachineOperationManager::getInstance()->getElectoralConfiguration()->notReload();
	signalEnd.emit();
}

void VMInstallMachineWidget::stop()
{
	CardController::getInstance()->dispose();
	conn.disconnect();
}

std::string VMInstallMachineWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.Title");
}
