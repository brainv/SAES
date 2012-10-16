/**
 * @file PMachineInitiator.cxx
 * @brief body class for president machine initiator
 */

#include "PMachineInitiator.hxx"
#include <Security/Encryption.hxx>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <Operation/Initiator/CheckFlashPresence.hxx>

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

#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include <Voting/operation-status.h>
#include <Runtime/Environment/saes-directories.h>
#include <Operation/MachineOperationManager.hxx>
#include "Printing/PrinterStatusNotifier.h"
#include <Printing/PrintDocumentResult.h>
#include <Log/SMTTLogManager.h>
#include <System/Exception/GuIdException.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Operation/Initiator/CheckForUsedMemory.h>
#include <Operation/Initiator/CheckForMemoryComplete.h>
#include <Runtime/Environment/MemoryPathController.h>
#include <Operation/Initiator/CheckFlashStructure.hxx>

using namespace std;
using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;

ISMTTLog* PMachineInitiator::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.PMachineInitiator",GETTEXT_PACKAGE);

PMachineInitiator::PMachineInitiator ()
{
    runNormal = false;
	m_InstallationPrintDocument = NULL;
	stepTime = Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getPMStepTime();
	runMode = NORMAL_MODE;
}

PMachineInitiator::~PMachineInitiator ()
{
	if ( m_InstallationPrintDocument )
		delete m_InstallationPrintDocument;
}

void PMachineInitiator::start()
{
	logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.StartPMAchine"));

	if (m_InstallationPrintDocument)
		delete m_InstallationPrintDocument;

	m_InstallationPrintDocument = new InstallationPrintDocument(electoralConfiguration,true,true);

    m_thread = Glib::Thread::create(
     sigc::mem_fun(*this,&PMachineInitiator::run), false);
}
    
void PMachineInitiator::run()
{
    bool success = true;

    SaesDirectories directories;
    std::list < ICheckCondition * >::iterator it;

    for ( it = conditions.begin();
          it != conditions.end();
          it++)
    {
        ICheckCondition * condition = (*it);
        status.setMessage(condition->getMessage());
        status.setImageFileName(condition->getImageFilename());
        status.setImageErrorFileName(condition->getImageErrorFilename());
        signal_detected.emit(status,false);
        TestStatus::Tests test = condition->check();
        status.setStatuses(condition->whois(),test);
        success = success && (test == TestStatus::Passed);
        status.setSuccess(success);
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();

    if (success && !Directory::DirectoryExists( flashMedia ))
    {
        CheckFlashPresence flashCondition;
        status.setMessage(flashCondition.getMessage());
        status.setImageFileName(flashCondition.getImageFilename());
        status.setImageErrorFileName(flashCondition.getImageErrorFilename());
        signal_detected.emit(status,false);
        TestStatus::Tests test = flashCondition.check();
        status.setStatuses(flashCondition.whois(),test);
        success = success && (test == TestStatus::Passed);
        status.setSuccess(success);
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    if (success)
    {
        runNormal = true;
        success = checkData();
        MachineOperationManager::getInstance()->startInitialization();
        runNormal = false;
    }

    status.setSuccess(success);
    status.setImageFileName("ui/check-flash-structure-success.gif");
    status.setImageErrorFileName("ui/check-flash-structure-failed.gif");

    if(success && SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getPrintInstallationReportPM())
	{
		if(MachineOperationManager::getInstance()->getOperationStatus()->getElectionStatusWrapper()->getElectionConfigurationReportPrinted() == false)
		{
		    printReport();
		}
		else
		{
			endLoad();
		}
	}
	else
	{
		endLoad();
	}
}

void PMachineInitiator::endLoad()
{
	bool success = status.getSuccess();

	if (success)
	{
        status.setStatuses(TestStatus::MemoryComplete,TestStatus::Passed);

		switch(runMode)
		{
			case FIRST_TIME:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTimeSuccess"));
				break;

			case NORMAL_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.CheckingConfigurationSuccess"));
				break;

			case RECOVERY_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningMemoryRecoverySuccess"));
				break;

			case REPLACE_MACHINE_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineModeSuccess"));
				break;

			case CONTINGENCY_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.ContingencyModeSuccess"));
				break;
		}
	}
	else
	{
		status.setStatuses(TestStatus::MemoryComplete,TestStatus::Failed);

		switch(runMode)
		{
			case FIRST_TIME:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTimeError"));
				break;

			case NORMAL_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.CheckingConfigurationError"));
				break;

			case RECOVERY_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningMemoryRecoveryError"));
				break;

			case REPLACE_MACHINE_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineModeError"));
				break;

			case CONTINGENCY_MODE:
				status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.ContingencyModeError"));
				break;
		}
	}

	signal_detected.emit(status,true);
}

bool PMachineInitiator::checkData()
{
    bool success = true;

    logger->Debug("Start check data");

    try
    {
        SaesDirectories directories;

        CheckFlashStructure checkDom(directories, Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
        CheckFlashStructure checkFlash(directories, Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH);

        if (runNormal)
        {
        	status.setMessage(checkFlash.getMessage());
            status.setImageFileName(checkFlash.getImageFilename());
            status.setImageErrorFileName(checkFlash.getImageErrorFilename());
            signal_detected.emit(status,false);
        }

        TestStatus::Tests testD = checkDom.check();
        TestStatus::Tests testF = checkFlash.check();

        if (runNormal)
        {
        	status.setStatuses(checkFlash.whois(),testF);
        }

        success = (testD == TestStatus::Passed && testF == TestStatus::Passed);

        if (runNormal)
        {
            status.setSuccess(success);
            signal_detected.emit(status,false);
            usleep(stepTime * 1000);
        }

        if (!success)
        {
            status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.NotOperatingSystemInFlash"));
            return false;
        }
	
	if(!MachineOperationManager::getInstance()->checkSAESFiles())
	{
            logger->Debug("Invalid SAES files.");
            return false;
	}

        CheckForUsedMemoryCondition usedDomCond(directories);
        CheckForMemoryCompleteCondition completeDomCond(directories);

        CheckForUsedMemoryCondition usedFlashCond(directories, BasePathType::CONFIGURATION_FLASH);
        CheckForMemoryCompleteCondition completeFlashCond(directories, BasePathType::CONFIGURATION_FLASH);

        TestStatus::Tests usedDOM = usedDomCond.check();
        TestStatus::Tests completeDOM = completeDomCond.check();
        TestStatus::Tests usedFlash = usedFlashCond.check();
        TestStatus::Tests completeFlash = completeFlashCond.check();

        if (runNormal)
        {
            status.setSuccess(success);
            status.setImageFileName("ui/check-flash-structure.gif");
            status.setImageErrorFileName("ui/check-flash-structure.gif");
            signal_detected.emit(status,false);
        }

        if(runNormal && usedDOM == TestStatus::Failed && usedFlash == TestStatus::Failed)
        {
        	runMode = mode;
            success = runFirstTime();
        }
        else if (completeDOM == TestStatus::Passed && usedFlash == TestStatus::Failed)
        {
        	// run with DOM
        	runMode = RECOVERY_MODE;
            success = runRecoveryMode(true);
        }
        else if (usedDOM == TestStatus::Failed && completeFlash == TestStatus::Passed)
        {
        	// run with Flash
        	runMode = RECOVERY_MODE;
            success = runRecoveryMode(false);
        }
        else if (completeDOM == TestStatus::Passed && completeFlash == TestStatus::Passed)
        {
        	success = checkBasicConfig();

        	if (success)
        	{
        		success = false;

				if (MachineOperationManager::getInstance()->validateMachineId())
				{
		        	runMode = NORMAL_MODE;
					success = runNormalMode();
				}
				else if (runNormal)
				{
		        	runMode = REPLACE_MACHINE_MODE;
					success = runReplaceMachineMode();
				}
        	}
        }
        else
        {
            success = false;

            if (completeDOM == TestStatus::Failed)
            {
                logger->Debug("Error: DOM is not complete");
            }
            if (completeFlash == TestStatus::Failed)
            {
                logger->Debug("Error: Flash is not complete");
            }
            if(usedDOM == TestStatus::Failed && usedFlash == TestStatus::Passed)
            {
                logger->Debug("Error: DOM not used but flash used");
            }

            status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.InvalidDomAndFlashData"));
        }
    }
    catch(...)
    {
        logger->Debug("Error check data");
        success = false;
    }

    if (runNormal)
    {
        status.setSuccess(success);
        status.setStatuses(TestStatus::MemoryComplete,success ? TestStatus::Passed:TestStatus::Failed);
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    logger->Debug("End check data");

    return success;
}

bool PMachineInitiator::runFirstTime()
{
    bool success = false;

    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTime"));

    if (runNormal)
    {
    	status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTime"));
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    success = CheckConfigurationLoad();

    if(success)
    {
        MachineOperationManager::getInstance()->createMachineId();

        SaesDirectories directories;
        Smartmatic::SAES::Runtime::Environment::DirectoryManager directorymanager ( directories );
        success = directorymanager.backup(true);
    }

    if(success)
    {
        logger->Debug("Running first time OK");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTimeSuccess"));
    }
    else
    {
        logger->Debug("Running first time Failed");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningFirstTimeError"));
    }

    if (runNormal)
    {
    	signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    return success;
}

bool PMachineInitiator::runRecoveryMode(bool copyDomToFlash)
{
    bool success = false;

    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningMemoryRecovery"));

    if (runNormal)
    {
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningMemoryRecovery"));
		signal_detected.emit(status,false);
		usleep(stepTime * 1000);

		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.CheckVotes"));
		signal_detected.emit(status,false);
    }

	SaesDirectories directories;
	Smartmatic::SAES::Runtime::Environment::DirectoryManager directorymanager ( directories );

    if (!directorymanager.backup(copyDomToFlash))
    {
    	logger->Debug("Error backup memory.");
    }
    else if (!MachineOperationManager::getInstance()->validateVotes())
    {
    	logger->Debug("Invalid votes file in DOM and Flash.");
    }
    else if (!CheckConfigurationLoad())
    {
    	logger->Debug("Error check configuration load.");
    }
    else if (!MachineOperationManager::getInstance()->checkVotes(0))
    {
        logger->Debug("Invalid votes.");
    }
    else
    {
    	success = true;
    }

    if(success)
    {
        logger->Debug("Running recovery mode OK");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.MemoryRecoverySuccess"));
    }
    else
    {
        logger->Debug("Running recovery mode Failed");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.MemoryRecoveryError"));
    }

    if (runNormal)
    {
    	signal_detected.emit(status,false);
    	usleep(stepTime * 1000);
    }

    return success;
}

bool PMachineInitiator::runNormalMode()
{
    bool success = false;

    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningNormalMode"));

    if (runNormal)
    {
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningNormalMode"));
		signal_detected.emit(status,false);
		usleep(stepTime * 1000);
    }

    // se permite un delta de diferencia de votos

    if (runNormal)
    {
    	status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.CheckVotes"));
		signal_detected.emit(status,false);
    }

    if (!MachineOperationManager::getInstance()->validateVotes())
    {
    	logger->Debug("Invalid votes file in DOM and Flash.");
    }
    else if (!MachineOperationManager::getInstance()->checkVotes(1))
    {
        logger->Debug("Invalid votes.");
    }
	else if (!MachineOperationManager::getInstance()->checkSAESLocal())
	{
		logger->Debug("Invalid SaesLocal.");
	}
    else
    {
        success = true;
    }

    if(success)
    {
        logger->Debug("Running normal mode OK");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningNormalModeSuccess"));
    }
    else
    {
        logger->Debug("Running normal mode Failed");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningNormalModeError"));
    }

    if (runNormal)
    {
    	signal_detected.emit(status,false);
    	usleep(stepTime * 1000);
    }

    return success;
}

bool PMachineInitiator::runReplaceMachineMode()
{
    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineMode"));

    if (runNormal)
    {
    	status.setSuccess(true);
        status.setImageFileName("ui/replace-machine-mode-success.gif");
        status.setImageErrorFileName("ui/replace-machine-mode-error.gif");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineMode"));
        signal_detected.emit(status,false);
        usleep(stepTime * 1000 * 2);
    }

    // no se permiten que exista diferencia de votos

	bool success = false;

	if (runNormal)
    {
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.CheckVotes"));
	    signal_detected.emit(status,false);
    }

	if (!MachineOperationManager::getInstance()->validateVotes())
	{
		logger->Debug("Invalid votes file in DOM and Flash.");
	}
	else if (!MachineOperationManager::getInstance()->checkVotes(1))
	{
		logger->Debug("Invalid votes.");
	}
	else if (!MachineOperationManager::getInstance()->checkSAESLocal())
	{
		logger->Debug("Invalid SaesLocal.");
	}
	else
	{
		success = true;
	}

    if(success)
    {
    	// se crea el nuevo machine id en dom y flash
    	MachineOperationManager::getInstance()->createMachineId(true);

        logger->Debug("Running replace machine mode OK");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineModeSuccess"));
    }
    else
    {
        logger->Debug("Running replace machine mode Failed");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningReplaceMachineModeError"));
    }

    if (runNormal)
    {
    	status.setSuccess(success);
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    return success;
}


bool PMachineInitiator::checkBasicConfig()
{
    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningCheckConfiguration"));

    if (runNormal)
    {
    	status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningCheckConfiguration"));
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }

    bool success = false;

    if(!MachineOperationManager::getInstance()->checkVoteStatistics())
	{
		logger->Debug("Invalid vote statistics file.");
	}
	else if(!MachineOperationManager::getInstance()->checkActivatedCardStatistics())
	{
		logger->Debug("Invalid activated card statistics file.");
	}
	else if(!MachineOperationManager::getInstance()->checkAssistedActivations())
	{
		logger->Debug("Invalid assisted activations file.");
	}
	else if(!MachineOperationManager::getInstance()->checkVotingDisabled())
	{
		logger->Debug("Invalid voting disabled file.");
	}
	else if(!MachineOperationManager::getInstance()->checkPoliceNotes())
	{
		logger->Debug("Invalid police notes file.");
	}
	else if(!MachineOperationManager::getInstance()->checkPollworkers())
	{
		logger->Debug("Invalid pollworkers file.");
	}
	else if(!MachineOperationManager::getInstance()->checkSignature())
	{
		logger->Debug("Invalid signature file.");
	}
	else if(!MachineOperationManager::getInstance()->checkClosingNotes())
	{
		logger->Debug("Invalid close notes file.");
	}
	else if(!MachineOperationManager::getInstance()->checkStatistics())
	{
		logger->Debug("Invalid statistics file.");
	}
	else if(!MachineOperationManager::getInstance()->checkTechnicalTroubles())
	{
		logger->Debug("Invalid technical troubles file.");
	}
	else if(!MachineOperationManager::getInstance()->checkVotingDeviceStatus())
	{
		logger->Debug("Invalid voting device status file.");
	}
	else if(!MachineOperationManager::getInstance()->checkElectionStatus())
	{
		logger->Debug("Invalid election status file.");
	}
	else if(!MachineOperationManager::getInstance()->checkElection())
	{
		logger->Debug("Invalid election file.");
	}
	else if(!MachineOperationManager::getInstance()->checkVotingDevices())
	{
		logger->Debug("Invalid voting devices file.");
	}
	else if (!MachineOperationManager::getInstance()->checkMachineId())
	{
		logger->Debug("Invalid machine id file.");
	}
	else if (!MachineOperationManager::getInstance()->checkIdCardMembers())
	{
		logger->Debug("Invalid machine id file.");
	}
	else if(!CheckConfigurationLoad())
    {
		logger->Debug("Error load config");
    }
	else if(!MachineOperationManager::getInstance()->checkPVReport())
	{
		logger->Debug("Invalid pv report file.");
	}
	else if(!MachineOperationManager::getInstance()->checkTransmissionPackages())
	{
		logger->Debug("Invalid transmission package file.");
	}
	else
	{
		success = true;
	}

    if(success)
    {
        logger->Debug("Running check configuration OK");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningCheckConfigurationSuccess"));
    }
    else
    {
        logger->Debug("Running check configuration Failed");
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.RunningCheckConfigurationError"));
    }

    if (runNormal)
    {
    	signal_detected.emit(status,false);
    	usleep(stepTime * 1000);
    }

    return success;
}

bool PMachineInitiator::CheckConfigurationLoad()
{
    try
    {	
        MachineOperationManager::getInstance()->startUp();
        return true;
    }
    catch(ElectionException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(VotingDeviceException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(CryptoException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(SignedException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(XmlException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(GuIdException & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(VoteException & ex)
    {
        stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
        logger->Debug(ss.str());
    }
    catch(FileSystemException & ex)
    {
        stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
        logger->Debug(ss.str());
    }
    catch(exception & ex)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
    }
    catch(...)
    {
		stringstream ss;
        ss<< "FATAL "<<__func__;
		logger->Debug(ss.str());
    }
    return false;
}

bool PMachineInitiator::printReport()
{
    logger->Debug("Start print installation report");
	Glib::ustring print_result_msg;
	PrintDocumentResult::PrintingResultEnumType print_result;
	bool success = false;

    status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.PrintingInstallReport"));
    status.setImageFileName("ui/installation-report-printing-progress.gif");
    status.setImageErrorFileName("ui/installation-report-printing-progress-error.gif");
	status.setSuccess(true);
    signal_detected.emit(status,false);

    sleep(2);

  	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();
	if(printerState & PrinterStatusNotifier::PSTATE_READY)
    {
		logger->Debug("Status Printer Ok");

		m_InstallationPrintDocument->setClient(this);
		logger->Debug("starting printing of report");
		m_InstallationPrintDocument->Print();
		PrintDocumentResult res = m_InstallationPrintDocument->getDocumentResult ();
		res.getResult(success, print_result_msg, print_result);

		std::stringstream ss;
		ss << "Result print installation report - success : " << success << " - status : " << print_result;
	    logger->Debug(ss.str());
    }
	else
    {
		status.setSuccess(false);
		logger->Debug("Status Printer Fail");
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.PrintingInstallReportFail"));
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.LogPrintingInstallReportFailPrinterNotReady"));
		signal_detected.emit(status,false);
		sleep(2);
		signal_detected.emit(status,true);
    }

    return success;
}

void PMachineInitiator::onDocumentPrinted (PrintDocumentResult res)
{
	bool printResult = false;
	Glib::ustring msg;
	PrintDocumentResult::PrintingResultEnum resultType = PrintDocumentResult::PRINTING_NONE;
	res.getResult(printResult, msg, resultType);
	
	if(printResult)
	{
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.PrintingInstallReportOk"));
		logger->Debug("Printing Install Report Ok");
        MachineOperationManager::getInstance()->saveElectoralConfigurationReportPrinted();
	}
	else
	{
		status.setMessage(_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.PrintingInstallReportFail"));
		status.setSuccess(true);
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineInitiator.LogPrintingInstallReportFail"));
	}
	
	status.setSuccess(printResult);
	signal_detected.emit(status,false);
	sleep(2);
	
	endLoad();
}	

void PMachineInitiator::dispose()
{
}

int PMachineInitiator::getSuccessMessageTime()
{
	return Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getPMSuccesMessageTime();
}
