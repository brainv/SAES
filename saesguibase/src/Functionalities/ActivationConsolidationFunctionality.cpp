/**
 * @file ActivationConsolidationFunctionality.cpp
 * @brief Body class activation consolidation functionality
 * @date 02/09/2011
 * @author Juan Delgado
 */

#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Functionalities/ActivationConsolidationFunctionality.h>
#include <Log/SMTTLogManager.h>
#include <Devices/barcode-device.h>
#include <Gui/Widgets/AbstractFactoryWidget.hxx>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::HW::Devices;

ISMTTLog* ActivationConsolidationFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ActivationConsolidationFunctionality",GETTEXT_PACKAGE);

ActivationConsolidationFunctionality* ActivationConsolidationFunctionality::current_instance = NULL;

ActivationConsolidationFunctionality* ActivationConsolidationFunctionality::Current()
{
	if (!current_instance)
		current_instance = new ActivationConsolidationFunctionality();

	return current_instance;
}

ActivationConsolidationFunctionality::ActivationConsolidationFunctionality()
:GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	outsideBox = NULL;
	activationWidget = NULL;
	consolidationWidget = NULL;
	cardActivatorBox = NULL;
	barcodeWidget = NULL;
}

ActivationConsolidationFunctionality::~ActivationConsolidationFunctionality()
{
	deleteElement();
}

Smartmatic::Functionality::MenuOptionDescriptor ActivationConsolidationFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MActivationConsolidation,false);
}

Gtk::Widget* ActivationConsolidationFunctionality::GetFrame()
{
	CountConfiguration totalActivationCountType = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getCardActivationTotalCountConfiguration();
	bool showStatistic = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowActivateCards();
	activationWidget = new ActivationStatsWidget(totalActivationCountType, showStatistic);

	CountConfiguration totalConsolidationCountType = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getConsolidationTotalCountConfiguration();
	CountConfiguration officialConsolidationCountType = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getConsolidationOfficialCountConfiguration();
	consolidationWidget = new ConsolidationStatsWidget(totalConsolidationCountType, officialConsolidationCountType);
	consolidationWidget->barcode_SendCommands().connect(sigc::mem_fun(*this, &ActivationConsolidationFunctionality::statusSendCommands));

	cardActivatorBox = new CardActivatorEventBox(330);
	cardActivatorBox->signal_vectorCustomAttribute_changed().connect(sigc::mem_fun(*this, &ActivationConsolidationFunctionality::SetCustomAttributeVector));

	/**
	 * activation stats
	 */
	activationWidget->set_size_request(325, -1);

	barcodeWidget = AbstractFactoryWidget::createBarcodeDetectionWidget();
	barcodeWidget->ShowConfigure();

	outsideBox = new Gtk::HBox();
	outsideBox->set_spacing(15);
	outsideBox->show();

	outsideBox->pack_start(*consolidationWidget);
	outsideBox->pack_start(*cardActivatorBox,false,false);
	outsideBox->pack_end(*activationWidget,false, false);
	outsideBox->pack_end(*barcodeWidget);

	consolidationWidget->set_no_show_all();
	consolidationWidget->show();

	cardActivatorBox->set_no_show_all();
	cardActivatorBox->show();

	activationWidget->set_no_show_all();
	activationWidget->show();

	barcodeWidget->set_no_show_all();
	barcodeWidget->hide();

	return outsideBox;
}

void ActivationConsolidationFunctionality::statusSendCommands(bool status)
{
	if (!status)
	{
		barcodeWidget->ShowFail();
	}
	else
	{
		hideBarcodeConnected();
	}
}

void ActivationConsolidationFunctionality::BarcodeConnected(bool isConnected)
{
	static bool activateCardsWithoutBarcode =
			Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current(
					)->GetActivationConsolidationFunctionalityConfiguration().getActivateCardsWithoutBarcode();

	if(!activateCardsWithoutBarcode)
	{
		activationWidget->AllowCardActivation(isConnected);
	}
}

void ActivationConsolidationFunctionality::SetCustomAttributeVector(vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > vecCA)
{
	activationWidget->SetAttributes(vecCA);
}

void ActivationConsolidationFunctionality::Dispose()
{
	disableExitButton();

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();
	connBarcodeDisconnected.disconnect();
	connBarcodeConnected.disconnect();

	activationWidget->Dispose();
	consolidationWidget->Dispose();
}

void ActivationConsolidationFunctionality::Initialize()
{
	enableExitButton();

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();
	connBarcodeDisconnected.disconnect();
	connBarcodeConnected.disconnect();

	signalStartSendCommand = BarcodeDevice::Current()->getSignalStartSendCommand().connect(sigc::mem_fun(*this , &ActivationConsolidationFunctionality::disableExitButton));
	signalEndSendCommand = BarcodeDevice::Current()->getSignalEndSendCommand().connect(sigc::mem_fun(*this , &ActivationConsolidationFunctionality::enableExitButton));
	connBarcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &ActivationConsolidationFunctionality::hideBarcodeConnected));
	connBarcodeConnected = BarcodeDevice::Current()->signalConnected().connect(sigc::mem_fun(*this, &ActivationConsolidationFunctionality::showBarcodeConnected));

	activationWidget->Initialize();
	activationWidget->SetAttributes(cardActivatorBox->GetCustomAttributes());

	consolidationWidget->Initialize();

	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.ActivationConsolidationFunctionality.FinalMessage"));
}

string ActivationConsolidationFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ActivationConsolidationFunctionality.ActivationConsolidation");
};

Smartmatic::Log::ISMTTLog* ActivationConsolidationFunctionality::getLogger()
{
	return logger;
}

Glib::ustring ActivationConsolidationFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ActivationConsolidationFunctionality.LogStartFunctionality");
}

Glib::ustring ActivationConsolidationFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ActivationConsolidationFunctionality.LogCloseFunctionality");
}

void ActivationConsolidationFunctionality::block()
{
	logger->Debug("Block functionality");

	activationWidget->SetOneMemoryMode(true);
	consolidationWidget->SetOneMemoryMode(true);

	activationWidget->StopOperation();
	consolidationWidget->pauseOperation();
}

void ActivationConsolidationFunctionality::partial()
{
	logger->Debug("Partial functionality");

	activationWidget->ContinueOperation();
	consolidationWidget->resumeOperation();

	consolidationWidget->UpdateMemoryPresence();
	consolidationWidget->UpdateBarcodePresence();
}

void ActivationConsolidationFunctionality::resume()
{
	logger->Debug("Resume functionality");

	activationWidget->SetOneMemoryMode(false);
	consolidationWidget->SetOneMemoryMode(false);

	activationWidget->ContinueOperation();
	consolidationWidget->resumeOperation();

	consolidationWidget->UpdateMemoryPresence();
	consolidationWidget->UpdateBarcodePresence();
}

void ActivationConsolidationFunctionality::deleteElement()
{
	if (outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
	if (activationWidget)
	{
		delete activationWidget;
		activationWidget = NULL;
	}
	if (consolidationWidget)
	{
		delete consolidationWidget;
		consolidationWidget = NULL;
	}
	if (cardActivatorBox)
	{
		delete cardActivatorBox;
		cardActivatorBox = NULL;
	}
	if (barcodeWidget)
	{
		delete barcodeWidget;
		barcodeWidget = NULL;
	}
}

void ActivationConsolidationFunctionality::hideBarcodeConnected()
{
	logger->Debug("hideBarcodeConnected");

	BarcodeConnected(false);
	activationWidget->ContinueOperation();

	activationWidget->show();
	consolidationWidget->show();
	cardActivatorBox->show();
	barcodeWidget->hide();
	barcodeWidget->ShowConfigure();
	enableExitButton();
}

void ActivationConsolidationFunctionality::showBarcodeConnected()
{
	logger->Debug("showBarcodeConnected");

	BarcodeConnected(true);
	activationWidget->StopOperation();

	activationWidget->hide();
	consolidationWidget->hide();
	cardActivatorBox->hide();
	barcodeWidget->show();
	barcodeWidget->ShowConfigure();
	disableExitButton();
}

void ActivationConsolidationFunctionality::refresh()
{
	consolidationWidget->UpdateMemoryPresence();
	consolidationWidget->UpdateBarcodePresence();
}
