#include "graphic-display-functionality.h"
#include <Runtime/Environment/MemoryPathController.h>
#include <Runtime/Environment/MemoryPathController.h>
#include <Operation/WindowsManager.hxx>

namespace Smartmatic
{
namespace SAES
{
namespace GUI
{
namespace Functionality
{

template <class TMenuOptionDescriptor>
GraphicDisplayFunctionality<TMenuOptionDescriptor>::GraphicDisplayFunctionality()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.DefaultExitMessage"));
	frame = NULL;
	baseWindow = NULL;
	enableBackgroundProcess = true;
    forceToLoad = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetForceToLoadFrame();

	startHelpPrintConn = helpWidget.getSignalStartPrint().connect(sigc::mem_fun(*this, &GraphicDisplayFunctionality::disableExitButton));
	stopHelpPrintConn = helpWidget.getSignalEndPrint().connect(sigc::mem_fun(*this, &GraphicDisplayFunctionality::enableExitButton));
}

template <class TMenuOptionDescriptor>
GraphicDisplayFunctionality<TMenuOptionDescriptor>::~GraphicDisplayFunctionality<TMenuOptionDescriptor>()
{

}

template <class TMenuOptionDescriptor>
std::vector<Smartmatic::GUI::Windows::HelpItem> GraphicDisplayFunctionality<TMenuOptionDescriptor>::GetHelpconfiguration()
{
	std::vector<Smartmatic::GUI::Windows::HelpItem> listOfHelp;
	return listOfHelp;
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::Execute()
{
    try
    {
        getLogger()->Audit(getStartLogMessage());
        BeginExecute();

        if(enableBackgroundProcess)
        {
        	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &GraphicDisplayFunctionality<TMenuOptionDescriptor>::ExcuteBackgroundProcess),1500);
        }

    }
    catch(std::exception& e)
    {
        std::cerr << "FATAL - " << e.what() << std::endl;
    }
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::ExcuteBackgroundProcess()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::EnableBackgroundProcess()
{
	enableBackgroundProcess = true;
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::PreLoad()
{
	enableBackgroundProcess = false;
	deleteElement();
    frame = GetFrame();
    this->loaded = true;
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::DisplayUnableMessage()
{
    int delay = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetUnableMessageCloseTime();
	baseWindow = (Smartmatic::SAES::GUI::Windows::EmptyWindow * )Smartmatic::GUI::Operation::WindowsManager::getInstance()->current();

	initWidget.setTitleText(this->GetWindowTitle());
	initWidget.setTitle(false);
	initWidget.setHelp(false);
	initWidget.setExit(false);
	initWidget.setTimeout(delay);

	baseWindow->showInitMessageWidget(initWidget);
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::ForceShowHelp()
{

}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::GetIsRolePassword()
{
    return Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getIfChallengeIsRole(GetMenuOptionType());
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::CanExecute()
{
    bool canExecute = true;

    helpConfiguration = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getHelpConfiguration(GetMenuOptionType());

    Smartmatic::SAES::Voting::OperationStatus * operationStatus =
            Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus();

    if (operationStatus == NULL)
    {
    	getLogger()->Debug("Operation status is null");
        return canExecute;
    }

    if (!checkMemoryPath())
    {
    	canExecute = false;
    }
    else if (checkOperationStatus(operationStatus))
    {
    	canExecute = checkNecessaryDevices();
    }
    else
    {
    	canExecute = false;
    }

    return canExecute;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkMemoryPath()
{
	Smartmatic::SAES::Functionality::Configuration::LaunchConfiguration& launchConfig(Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());
	Smartmatic::SAES::Functionality::Configuration::AppType apptoLaunch = launchConfig.getAppType();

	bool result;

	result = Smartmatic::SAES::Runtime::Environment::MemoryPathController::getInstance()->isAllDevices() ||
			apptoLaunch != Smartmatic::SAES::Functionality::Configuration::AppType::CONFIGURATION_POLLBOOKONLY;

	if (!result)
	{
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ErrorMemoryPath"));
	}

    return result;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkOperationStatus( Smartmatic::SAES::Voting::OperationStatus * operationStatus )
{
	bool canExecute = true;

	getLogger()->Debug("Start check operation status");

    Smartmatic::SAES::Voting::Status::ProcessStatus actualStatus = operationStatus->getElectionStatusWrapper()->getEletionState();

    Smartmatic::SAES::Configuration::ElectionBlockStatusList::ElectionStatusSequence seq =
            Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDisableStateList(GetMenuOptionType());

    Smartmatic::SAES::Configuration::ElectionBlockStatusList::ElectionStatusIterator iter;

    for(iter = seq.begin(); iter != seq.end(); iter++)
    {
        Smartmatic::SAES::Voting::Status::ProcessStatus checkStatus = (*iter);

        if(actualStatus == checkStatus)
        {
            switch(actualStatus)
            {
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED:
                	initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusNotInitiated"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusInitiated"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusClosed"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusResultsTransmitted"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINSTALLED:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusNotInstalled"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTPOLLWORKERREGISTERED:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusNotPollworkerRegistered"));
                    break;
                case Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE:
                    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ElectionStatusNotDemostrationVote"));
                    break;
            }
            canExecute = false;
            break;
        }
        else
        {
        	initWidget.setInfo(" ");
        }
    }

    canExecute = canExecute && Enable();

    getLogger()->Debug("End check operation status " + std::string(canExecute ? "success" : "fail"));
    return canExecute;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkNecessaryDevices()
{
	bool canExecute = true;

	getLogger()->Debug("Start check necessary devices");

	Smartmatic::SAES::Configuration::NecessaryDevicesConfiguration::DeviceConfigurationSequence seq =
            Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDeviceConfiguration(GetMenuOptionType());

	Smartmatic::SAES::Configuration::NecessaryDevicesConfiguration::DeviceConfigurationIterator iter;

    for(iter = seq.begin(); iter != seq.end(); iter++)
    {
        switch(*iter)
        {
            case Smartmatic::SAES::Configuration::DeviceConfiguration::CONFIGURATION_BARCODE:
                canExecute = checkBarcode();
                break;
            case Smartmatic::SAES::Configuration::DeviceConfiguration::CONFIGURATION_SMARTCARD:
                canExecute = checkSmartcard();
                break;
            case Smartmatic::SAES::Configuration::DeviceConfiguration::CONFIGURATION_PRINTER:
                canExecute = checkPrinter();
                break;
        }

        if (!canExecute) break;
    }

    getLogger()->Debug("End check necessary devices " + std::string(canExecute ? "success" : "fail"));

	return canExecute;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkBarcode()
{
	bool canExecute = true;

	if (!Smartmatic::SAES::HW::Devices::BarcodeDevice::Current()->Resync())
	{
	    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.BarcodeNotFound"));
	    getLogger()->Audit(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.LoggerAuditBarcodeNotFound"));
	    canExecute = false;
	}

	Smartmatic::SAES::HW::Devices::BarcodeDevice::Current()->Close();
	return canExecute;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkSmartcard()
{
	bool canExecute = true;

	if (!Smartmatic::SAES::Operation::Card::CardController::getInstance()->initialize())
	{
	    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.SmartCardNotFound"));
	    getLogger()->Audit(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.LoggerAuditSmartCardNotFound"));
	    canExecute = false;
	}

	Smartmatic::SAES::Operation::Card::CardController::getInstance()->dispose();
	return canExecute;
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::checkPrinter()
{
	bool canExecute = true;

	Smartmatic::SAES::Printing::PrinterStatusNotifier printNotifier;
	Smartmatic::SAES::Printing::PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	if (printerState != Smartmatic::SAES::Printing::PrinterStatusNotifier::PSTATE_READY)
	{
	    initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.PrinterError"));
	    getLogger()->Audit(N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.LoggerAuditPrinterError"));
	    canExecute = false;
	}

	return canExecute;
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::ForceExit()
{

}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::LockMachine()
{
	return Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getFunctionalityGoToAuthenticationOnExit(GetMenuOptionType());
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::ChallengeIsEnable()
{
    return  getChallengeIsEnable();
}

template <class TMenuOptionDescriptor>
Smartmatic::Functionality::FunctionalityChallengeConfiguration GraphicDisplayFunctionality<TMenuOptionDescriptor>::getChallengeConfiguration()
{
    Smartmatic::Functionality::FunctionalityChallengeConfiguration arg;
    arg.setMessageError(getIvalidChallengeMessage());
    arg.setMessageOK(getValidChallengeMessage());
    arg.setTitle(getChallengeTitleMessage());
    arg.setDescriptionMessage(getDescriptionMessage());

    switch (getChallengePasswordSource())
    {
        case Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum::CONFIGURATION_PRESIDENTPASSPHRASE:
        {
            Smartmatic::SAES::GUI::Functionality::Providers::PresidentPassPhraseAuthenticationProvider* presidentPass = new Smartmatic::SAES::GUI::Functionality::Providers::PresidentPassPhraseAuthenticationProvider();

            arg.setAuthenticationProvider(presidentPass);
        }
        break;
        case Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum::CONFIGURATION_ROLE:
        {
            Smartmatic::SAES::GUI::Functionality::Providers::RoleAuthenticationProvider* rolePass = new Smartmatic::SAES::GUI::Functionality::Providers::RoleAuthenticationProvider();

            arg.setAuthenticationProvider(rolePass);
        }
        break;
        default:
            throw;
        break;
    }

    return arg;
}

template <class TMenuOptionDescriptor>
std::string GraphicDisplayFunctionality<TMenuOptionDescriptor>::getChallengeTitleMessage()
{
    return N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ChallengeTitleMessage");
}

template <class TMenuOptionDescriptor>
std::string GraphicDisplayFunctionality<TMenuOptionDescriptor>::getIvalidChallengeMessage()
{
    return N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.IvalidChallengeMessage");
}

template <class TMenuOptionDescriptor>
std::string GraphicDisplayFunctionality<TMenuOptionDescriptor>::getValidChallengeMessage()
{
    return N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.ValidChallengeMessage");
}

template <class TMenuOptionDescriptor>
std::string GraphicDisplayFunctionality<TMenuOptionDescriptor>::getDescriptionMessage()
{
    return N_("Smartmatic.SAES.GUI.Functionality.GraphicDisplayFunctionality.DescriptionMessage");
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::Exit()
{
    connExitWindow.disconnect();
    connShowExitMessage.disconnect();
	SetMenuMemoryBlock();
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::ShowFinalMessage()
{
	return Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetShowExitMessage(GetMenuOptionType());
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::setExitButtonSensitive(bool sensitive)
{
    stepWidget.setExitSensitive(sensitive);

    if (sensitive)
    {
    	baseWindow->enableExitButton();
    }
    else
    {
    	baseWindow->disableExitButton();
    }
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::setHelpButtonSensitive(bool sensitive)
{
    stepWidget.setHelpSensitive(sensitive);

    if (sensitive)
    {
    	baseWindow->enableHelpButton();
    }
    else
    {
    	baseWindow->disableHelpButton();
    }
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::enableExitButton()
{
	setExitButtonSensitive(true);
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::disableExitButton()
{
	setExitButtonSensitive(false);
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::enableHelpButton()
{
	setHelpButtonSensitive(true);
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::disableHelpButton()
{
	setHelpButtonSensitive(false);
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::BeforeExit()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::OnExitButtonClicked()
{
	ExecuteDispose();
	Exit();

    getLogger()->Audit(getFinishLogMessage());
    if(LockMachine())
    {
        this->LockMachineSigc().emit();
    }
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::ExitFunctionality()
{
	RefreshInfo();
	baseWindow->ShowExit();
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::OnHelpButtonClicked()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::OnHelpButtonClickedConnect()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::ExecuteDispose()
{
    Dispose();

    if(this->forceToLoad == true)
    {
    	getLogger()->Debug("Execute Delete Element");
    	deleteElement();
    }
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::Enable()
{
	return true;
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::BeginExecute()
{
    try
    {
    	SetMemoryBlock();

        if(this->loaded == false || this->forceToLoad == true)
        {
        	bool showExit = true;

        	baseWindow = (Smartmatic::SAES::GUI::Windows::EmptyWindow *)Smartmatic::GUI::Operation::WindowsManager::getInstance()->current();

        	if (!baseWindow)
        	{
        		baseWindow = new Smartmatic::SAES::GUI::Windows::EmptyWindow(NULL, " ", false, false, false);
        		Smartmatic::GUI::Operation::WindowsManager::getInstance()->push(baseWindow);
        		showExit = false;
        		baseWindow->show();
        	}

            deleteElement();
            frame = GetFrame();

            stepWidget.setWidget(frame);
            stepWidget.setTitleText(this->GetWindowTitle());
            stepWidget.setTitle(this->ShowWindowTitle());
            stepWidget.setExit(showExit);
            stepWidget.setHelp(helpConfiguration.getUseHelp());

            if (helpConfiguration.getUseHelp())
            {
                helpWidget.setInfo(helpConfiguration.getTitleKey(), helpConfiguration.getImageHelp(), helpConfiguration.getPdfHelp());
            	stepWidget.setHelpWidget(&helpWidget);
            }
            else
            {
            	stepWidget.setHelpWidget(NULL);
            }

        	if(ShowFinalMessage() && !LockMachine())
        	{
        		int delay = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetExitFunctionalityMessageCloseTime();
        		exitWidget.setTitleText(this->GetWindowTitle());
        		exitWidget.setTitle(stepWidget.isTitle());
        		exitWidget.setHelp(helpConfiguration.getUseHelp());
        		exitWidget.setExit(stepWidget.isExit());
        		exitWidget.setHelpSensitive(false);
        		exitWidget.setExitSensitive(false);
        		exitWidget.setTimeout(delay);
            	stepWidget.setExitWidget(&exitWidget);
        	}
        	else
        	{
        		stepWidget.setExitWidget(NULL);
        	}

        	stepWidget.setRefreshListener(this);
        	stepWidget.setStateListener(this);
            baseWindow->pushStepWidget(&stepWidget);

            connExitWindow.disconnect();
            connShowExitMessage.disconnect();

            connShowExitMessage = baseWindow->getSignalShowExitMessage().connect(sigc::mem_fun(this,
                    &GraphicDisplayFunctionality<TMenuOptionDescriptor>::BeforeExit));
            connExitWindow = baseWindow->getSignalExitButton().connect(sigc::mem_fun(this,
                    &GraphicDisplayFunctionality<TMenuOptionDescriptor>::OnExitButtonClicked));

            this->loaded = true;
        }
        else
        {
        }

        disableExitButton();
        Initialize();
    }
    catch(std::exception& e)
    {
        throw  e;
    }
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::SetMemoryBlock()
{
	Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->SetBlockMemoryBehavior(
			Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBlockMemoryBehavior(
					GetMenuOptionType()));
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::SetMenuMemoryBlock()
{
	static Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior behavior =
			Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBlockMemoryBehaviorMenu();

	Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->SetBlockMemoryBehavior(behavior);
}

template <class TMenuOptionDescriptor>
bool GraphicDisplayFunctionality<TMenuOptionDescriptor>::getChallengeIsEnable()
{
	return Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getChallengeIsEnable(GetMenuOptionType());
}

template <class TMenuOptionDescriptor>
Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum GraphicDisplayFunctionality<TMenuOptionDescriptor>::getChallengePasswordSource()
{
	return Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getChallengePasswordSource(GetMenuOptionType());
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::RefreshInfo()
{
	if (baseWindow)
	{
		baseWindow->refreshTitleText();
	}
}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::refresh()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::block()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::partial()
{

}

template <class TMenuOptionDescriptor>
void GraphicDisplayFunctionality<TMenuOptionDescriptor>::resume()
{

}

}
}
}
}
