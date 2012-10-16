/**
 * @file PMInstallMachineWidget.cxx
 * @brief Body class pm installation widget
 * @date 19/10/2011
 * @author Yadickson Soto
 */

#include "PMInstallMachineWidget.hxx"
#include <Gui/Widgets/AbstractFactoryWidget.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <System/IO/File.h>
#include <System/Sounds/smartmatic-sounds-manager.h>
#include <Operation/Card/CardController.hxx>
#include <Operation/Initiator/CheckForMemoryComplete.h>
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
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* PMInstallMachineWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.PMInstallMachineWidget",GETTEXT_PACKAGE);

PMInstallMachineWidget::PMInstallMachineWidget(ProgressWidget * progressWidget, ProgressWidget * removeCardWidget, PollingPlaceInfoWidget * pollingPlaceInfoWidget)
: InstallMachineWidget(), progressWidget(progressWidget), removeCardWidget(removeCardWidget)
{
	showImages = !SAESGUIConfigurationManager::Current()->getStartConfiguration().getLoadSelectionLanguage();
	centerCaseSensitive = SAESGUIConfigurationManager::Current()->getPMInstallationWidgetConfig().getLoginCaseSensitiveConfiguration();
	forceText = false;
	loginOk = false;

	this->loginWidget = NULL;
	this->contingencyWidget = NULL;
	this->infoMessage = NULL;
	this->message = NULL;
	this->image = NULL;
	this->languageWidget = NULL;
	this->reportInstall = NULL;
	this->pollingPlaceInfoWidget = pollingPlaceInfoWidget;

	this->progressWidget->setImage(ProgressWidget::PROGRESS);

	EntryDividedWidgetConfiguration & passwordConfig (SAESGUIConfigurationManager::Current()->getPMInstallationWidgetConfig().getPasswordWidgetConfiguration());
	loginWidget = new LoginWidget(showImages, passwordConfig);

	EntryDividedWidgetConfiguration & contingencyConfig (SAESGUIConfigurationManager::Current()->getPMInstallationWidgetConfig().getContingencyWidgetConfiguration());
	contingencyWidget = new ContingencyWidget(showImages, contingencyConfig);

	infoMessage = new InfoMessageWidget();
	languageWidget = new LanguageInstallWidget();
	reportInstall = AbstractFactoryWidget::createReportInstallWidget();

	message = new Gtk::Label();
	image = new Gtk::Image();

	loginWidget->getSignalButtonOkClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::authentication));
	contingencyWidget->getSignalButtonOkClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::contingency));
	contingencyWidget->getSignalButtonBackClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::initialize));
	infoMessage->getSignalButtonOkClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::install));
	infoMessage->getSignalButtonBackClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::initialize));
	infoMessage->getSignalButtonPrintClicked().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::print));
	languageWidget->getSignalEnd().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::info));
	reportInstall->getSignalEnd().connect(sigc::mem_fun(*this, &PMInstallMachineWidget::info));

	firstTime = !VotingCentersWrapper::getInstance()->isInstall();

	if (!firstTime)
	{
		VotingCenter votingCenter;
		VotingCentersWrapper::getInstance()->getInstallationVotingCenter(votingCenter);
		center = votingCenter.getCode();
		loginWidget->setLoginText(center);
		loginWidget->enabledLogin(false);
	}

	// force contingency mode
	CheckForMemoryCompleteCondition completeDomCond(*(MachineOperationManager::getInstance()->getSaesDirectories()));
	bool forceContingency = completeDomCond.check() == TestStatus::Failed;

	usedContingencyCardData = (firstTime || forceContingency) && SAESGUIConfigurationManager::Current()->getContingencyCardEnabled();

	logger->Debug(usedContingencyCardData ? "Used contingency CardData" : "Not used contingency CardData");

	if (usedContingencyCardData)
	{
		CardController::getInstance()->initialize();
	}

	Pango::FontDescription font = message->get_style()->get_font();
	font.set_size(15 * Pango::SCALE);
	message->modify_font(font);

	LabelConfiguration labelTitle = SAESGUIConfigurationManager::Current()->getRemoveCardTitle();
	LabelConfiguration labelText = SAESGUIConfigurationManager::Current()->getRemoveCardText();

	removeCardWidget->setTitleConfig(labelTitle);
	removeCardWidget->setTextConfig(labelText);

	initialize();
}

PMInstallMachineWidget::~PMInstallMachineWidget()
{
	dispose();
}

void PMInstallMachineWidget::initialize()
{
	password.clear();
	openingCode.clear();
	contingencyWidget->clear();

	loginOk = false;
	forceText = false;
	infoMessage->hideButtonPrint();

	if (usedContingencyCardData)
	{
		isPresent = CardController::getInstance()->isCardPresent();

		if (!isPresent)
		{
			setWidget(loginWidget);
		}
		else
		{
			setWidget(contingencyWidget);
		}

		int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getPMInstallationWindow();
		cardConn.disconnect();
		cardConn = Glib::signal_timeout().connect (sigc::mem_fun (*this, &PMInstallMachineWidget::checkCard), timerRefresh);
	}
	else
	{
		setWidget(loginWidget);
	}
}

void PMInstallMachineWidget::contingency()
{
	std::string pin;
	contingencyWidget->getText(pin);
	contingencyWidget->clear();

	Smartmatic::SAES::Voting::VotingDevice::ContingencyCardData cardData;

	try
	{
		if (CardController::getInstance()->readContingencyCardData(cardData, pin))
		{
			center = cardData.getPollingPlace();
			password = cardData.getPassphrase();
			openingCode = cardData.getOpeningCode();
		}
	}
	catch(...)
	{
		logger->Debug("ERROR - read card data");

		password = "";
		openingCode = "";
	}

	showProgressLogin();
}

void PMInstallMachineWidget::authentication()
{
	loginWidget->getLoginText(center);
	loginWidget->getPasswordText(password);
	showProgressLogin();
}

void PMInstallMachineWidget::error()
{
	SMTTSoundsManager::Current()->Sound(SAESGUIConfigurationManager::Current()->getAuthenticationInvalidPasswordSound());
	infoMessage->setInfoWidget(getMessageLoginError());
	infoMessage->enableButtonOk(false);
	infoMessage->hideText();
	setWidget(infoMessage);
}

void PMInstallMachineWidget::language()
{
	setWidget(languageWidget);
	languageWidget->start();
}

void PMInstallMachineWidget::info()
{
	forceText = true;

	MachineOperationManager::getInstance()->setOpeningCode(openingCode);
	SMTTSoundsManager::Current()->Sound(SAESGUIConfigurationManager::Current()->getAuthenticationValidPasswordSound());

	infoMessage->setInfoWidget(getMessageLoginOk());
	infoMessage->enableButtonOk(true);
	infoMessage->showText();

	if (!firstTime && SAESGUIConfigurationManager::Current()->GetPMInstallationWidgetShowPrintPasswordButton() &&
			MachineOperationManager::getInstance()->isPrintingInstallReport())
	{
		infoMessage->showButtonPrint();
	}

	if (!CardController::getInstance()->isCardPresent())
	{
		cardConn.disconnect();
		setWidget(infoMessage);
	}
	else
	{
		removeCardWidget->setTitle(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.RemoveContingencyCardTitle"));
		removeCardWidget->setText(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.RemoveContingencyCardText"));
		removeCardWidget->setImage("ui/extract_contingency_card.gif");

		logger->Debug("Remove Card");

		setWidget(removeCardWidget);
	}
}

void PMInstallMachineWidget::print()
{
	setWidget(reportInstall);
	reportInstall->start(false);
}

void PMInstallMachineWidget::install()
{
	 if (MachineOperationManager::getInstance()->install())
	 {
		 end();
	 }
	 else
	 {
		 infoMessage->setInfoWidget(getMessageLoginError());
		 setWidget(infoMessage);
	 }
}

void PMInstallMachineWidget::login()
{
	loginWidget->clearPassword();

	if (!loginOk)
	{
		error();
	}
	else if (SAESGUIConfigurationManager::Current()->getStartConfiguration().getLoadSelectionLanguage())
	{
		info();
	}
	else
	{
		language();
	}
}

void PMInstallMachineWidget::stop()
{
	cardConn.disconnect();
	CardController::getInstance()->dispose();
}

void PMInstallMachineWidget::dispose()
{
	this->remove();

	if (loginWidget)
	{
		delete loginWidget;
		loginWidget = NULL;
	}
	if (contingencyWidget)
	{
		delete contingencyWidget;
		contingencyWidget = NULL;
	}
	if (infoMessage)
	{
		delete infoMessage;
		infoMessage = NULL;
	}
	if (message)
	{
		delete message;
		message = NULL;
	}
	if (image)
	{
		delete image;
		image = NULL;
	}
	if (pollingPlaceInfoWidget)
	{
		delete pollingPlaceInfoWidget;
		pollingPlaceInfoWidget = NULL;
	}
	if (languageWidget)
	{
		delete languageWidget;
		languageWidget = NULL;
	}
	if (progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
	if (reportInstall)
	{
		delete reportInstall;
		reportInstall = NULL;
	}
	if (removeCardWidget)
	{
		delete removeCardWidget;
		removeCardWidget = NULL;
	}
}

Gtk::Widget * PMInstallMachineWidget::getMessageLoginError()
{
	Gtk::Widget * widget;

	if(showImages)
	{
		std::string imageFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/PM_passWrong.gif");
		image->set(Gdk::PixbufAnimation::create_from_file(imageFile));
		widget = image;
	}
	else
	{
		message->set_label(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.LoginAndPasswordIncorrect"));
		widget = message;
	}

	return widget;
}

Gtk::Widget * PMInstallMachineWidget::getMessageLoginOk()
{
	Gtk::Widget * widget;

	if (showImages && !forceText)
	{
		std::string passOkPath = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/PM_passOK.gif");
		image->set(Gdk::PixbufAnimation::create_from_file(passOkPath));
		widget = image;
	}
	else
	{
		pollingPlaceInfoWidget->fillInfoWidget();
		widget = pollingPlaceInfoWidget;
	}

	return widget;
}

void PMInstallMachineWidget::showProgressLogin()
{
	progressWidget->setTitle(" ");
	progressWidget->setText(" ");

	setWidget(progressWidget);
    if(!Glib::thread_supported()) Glib::thread_init();
    Glib::Thread::create(sigc::mem_fun(*this, &PMInstallMachineWidget::checkData), false);
}

void PMInstallMachineWidget::checkData()
{
	loginOk = MachineOperationManager::getInstance()->authentication(center, password, centerCaseSensitive);
    Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PMInstallMachineWidget::login), 250);
}

bool PMInstallMachineWidget::checkCard()
{
	static bool force = true;

	bool cardPresent = CardController::getInstance()->isCardPresent();

	if (!forceText && !loginOk)
	{
		if ((!isPresent || force) && cardPresent)
		{
			force = false;
			isPresent = true;
			loginWidget->clearPassword();
			setWidget(contingencyWidget);
		}
		else if (isPresent && !cardPresent)
		{
			isPresent = false;
			setWidget(loginWidget);
		}
	}
	else if (forceText && !cardPresent)
	{
		setWidget(infoMessage);
		cardConn.disconnect();
	}

	return true;
}

void PMInstallMachineWidget::end()
{
	try
	{
		Election::ElectionInstalationLanguages::getInstance()->persistLanguage();
		MachineOperationManager::getInstance()->getElectoralConfiguration()->notReload();

		logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.LoadCenterSuccess"));

		stop();
		signalEnd.emit();
		hide();
	}
	catch(...)
	{
		error();
	}
}

bool PMInstallMachineWidget::isTitle()
{
	return false;
}

std::string PMInstallMachineWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.PMInstallationWindow.Title");
}
