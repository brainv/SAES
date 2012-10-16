/**
 * @file VMachineInitiator.cxx
 * @brief body class for voting machine initiator
 */

#include "VMachineInitiator.hxx"
#include <Security/Encryption.hxx>
#include <System/guid-class.h>
#include "Operation/MachineOperationManager.hxx"
#include <glibmm.h>

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
#include <Printing/VotePrintDocument.h>
#include <Printing/InstallationPrintDocument.h>
#include <Log/SMTTLogManager.h>
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include <System/Exception/GuIdException.h>
#include <System/Exception/FileSystemException.hxx>
#include <Voting/Election/ElectionInstalationLanguages.h>

using namespace std;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation;

ISMTTLog* VMachineInitiator::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.VMachineInitiator",GETTEXT_PACKAGE);

VMachineInitiator::VMachineInitiator()
{
	stepTime = Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getVMStepTime();
}

VMachineInitiator::~VMachineInitiator()
{

}

void VMachineInitiator::start()
{
	logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.StartVMAchine")); 
    m_thread = Glib::Thread::create(
	sigc::mem_fun(*this,&VMachineInitiator::run), false);
}
    
void VMachineInitiator::run()
{
    std::list < ICheckCondition * >::iterator it;
    bool success = true;

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
        success = success && (test == TestStatus::Passed);
        status.setStatuses(condition->whois(),test);
        status.setSuccess(success);
        signal_detected.emit(status,false);
        usleep(stepTime * 1000);
    }


	status.setMessage(_("Smartmatic.SAES.Operation.Initiator.CanRemoveTheFlashDriveFromTheMachine"));
	status.setSuccess(success);
	signal_detected.emit(status,false);
	sleep( Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getMessageRemoveFlashTime());

	success = success && CheckConfigurationLoad();

    if (success || SAESFunctionalityConfigurationManager::Current()->getOperationConfiguration().getDiagnosesConsideredApproved())
	{
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.VMachineInitiator.CheckingConfigurationSuccess"));
        status.setStatuses(TestStatus::ConfigurationLoad,TestStatus::Passed);
        status.setSuccess(true);
	}
	else
	{
        status.setMessage(_("Smartmatic.SAES.Operation.Initiator.VMachineInitiator.CheckingConfigurationError"));
	    status.setStatuses(TestStatus::ConfigurationLoad,TestStatus::Failed);
	    status.setSuccess(false);
	}

    signal_detected.emit(status,true);
}

bool VMachineInitiator::checkData()
{
    return true;
}

bool VMachineInitiator::CheckConfigurationLoad()
{
    try
    {    
        electoralConfiguration->init(&directories);
        electoralConfiguration->loadAllData();
        VotePrintDocument::calculateMax(electoralConfiguration);

        std::string openingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getOpening_date_time();
        std::string closingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getClosing_date_time();

        Glib::TimeVal openingTime;
        Glib::TimeVal closingTime;

        openingTime.assign_from_iso8601(openingDateTime);
        double openingD = openingTime.as_double();

        closingTime.assign_from_iso8601(closingDateTime);
        double closingD = closingTime.as_double();

        Smartmatic::SAES::Security::Encryption::getInstance()->setMachineTime(openingD + (openingD + closingD)/2);

        MachineOperationManager::getInstance()->getOperationStatus()->init();
        Glib::ustring openingCode = MachineOperationManager::getInstance()->getOperationStatus()->getElectionStatusWrapper()->getOpeningCode();
        Smartmatic::System::GuidClass openCodeGUID = Smartmatic::System::GuidClass::Parse(openingCode);
        Smartmatic::SAES::Security::Encryption::getInstance()->setOpeningCode(openCodeGUID);

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

void VMachineInitiator::dispose()
{
}

int VMachineInitiator::getSuccessMessageTime()
{
	return Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getVMSuccesMessageTime();
}
