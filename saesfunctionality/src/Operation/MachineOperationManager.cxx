/**
 * @file MachineOperationManager.cxx
 * @brief body class for machine operation manager
 */

#include <log4cxx/DynamicPathRollingFileAppender.hxx>
#include "MachineOperationManager.hxx"
#include "System/IO/Directory.h"
#include "System/IO/Path.h"
#include <Security/Encryption.hxx>
#include <Voting/Vote/VoteWrapper.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/Compression/compression-class.h>
#include <Log/SMTTLogManager.h>
#include <Runtime/Environment/filename-hasher.h>
#include <Voting/Vote/TransmissionPackageWrapper.hxx>
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <System/guid-class.h>
#include <System/Threading/ThreadSleep.h>
#include <System/XML/DomXml.hxx>
#include <Voting/PBReports/PVFormWrapper.hxx>
#include <System/IO/File.h>
#include <eid/EIDManager.hxx>
#include <iomanip>
#include <glibmm/timeval.h>
#include <System/Encoding/Base64Encoder.h>
#include <Configuration/saes-language-controller.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <System/Utils/StringUtils.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/MemoryPathController.h>
#include <Voting/set-language-functionality.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Printing/InstallationPrintDocument.h>
#include <System/XSLFO/FOPTransformer.hxx>
#include <System/XSLFO/XMLRoffTransformer.h>
#include "PersistSortFile.hxx"
#include "InstallMachine.hxx"
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <System/Runtime/ProcessLauncher.h>
#include <Exceptions/Voting/Vote/QRVoteInvalidFormatException.h>
#include <Exceptions/Voting/Vote/QRVoteSignatureException.h>
#include <Runtime/Environment/saes-temporal-directories.h>
#include <Runtime/Environment/SaesProgramUnitDirectories.hxx>
#include <System/ZenityWrapper.hxx>
#include "SaesEnqueuer.h"

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

using namespace std;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Threading;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System::XSLFO;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::System::Runtime;
using namespace Smartmatic::SAES::Operation::Alarm;

MachineOperationManager * MachineOperationManager::instance = NULL;

ISMTTLog* MachineOperationManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.MachineOperationManager",GETTEXT_PACKAGE);
pthread_mutex_t MachineOperationManager::mutexSignal = PTHREAD_MUTEX_INITIALIZER;

MachineOperationManager::MachineOperationManager()
{
  this->isCheckData = false;
  this->behavior = MemoryBehavior_Block;
  this->alarmController = AlarmController::getInstance();
  this->voteStatistics = NULL;
  this->statisticManager = NULL;
  this->electoralConfiguration = new ElectoralConfiguration();
  this->beforeInitialization = true;
  this->operationStatus = NULL;
  this->startFirstTime = false;
  this->handleDetection = false;
  this->pvtransformer = NULL;
  this->loadOpeninCode = true;
  this->saesDirectories = NULL;
  this->idCardInfoWrapper = NULL;
  this->votingExperienceController = NULL;
  this->votingDisabledWrapper = new VotingDisabledWrapper();
  this->policeNoteWrapper = new PoliceNoteWrapper();

  (void) signal(SIGABRT, MachineOperationManager::signalHandler);
  (void) signal(SIGSEGV, MachineOperationManager::signalHandler);

  this->saesDirectories = new Smartmatic::SAES::Runtime::Environment::SaesDirectories();

  std::string markFile = SAESCommonConfigurationManager::Current()->getFileSystemVoteConfiguration().getBackupMarkFile();
  bool pesistence = SAESCommonConfigurationManager::Current()->getFileSystemVoteConfiguration().getImplementRandom();

  this->sortDomFile = new PersistSortFile(BasePathType::CONFIGURATION_DOM, markFile, pesistence);
  this->sortFlashFile = new PersistSortFile(BasePathType::CONFIGURATION_FLASH, markFile, pesistence);

  basePathDom = new LogBasePath(BasePathType::CONFIGURATION_DOM);
  basePathFlash = new LogBasePath(BasePathType::CONFIGURATION_FLASH);

  PVFormTransformationType type = SAESFunctionalityConfigurationManager::Current()->getPVFormTransformation().getType();

  switch(type)
  {
	case PVFormTransformationType::CONFIGURATION_FOP:
		pvtransformer = new FOPTransformer();
		break;
	case PVFormTransformationType::CONFIGURATION_XMLROFF:
		pvtransformer = new XMLRoffTransformer();
		break;
  }

  saesInstallDirectories = NULL;

  StructureInstallationType structType = SAESFunctionalityConfigurationManager::Current()->getStructureInstallationType();

  switch (structType)
  {
	  case StructureInstallationType::CONFIGURATION_SEPARATE:
		  saesInstallDirectories = new SaesTemporalDirectories();
		  break;
	  case StructureInstallationType::CONFIGURATION_GROUPED:
		  saesInstallDirectories = new SaesProgramUnitDirectories();
		  break;
  }

  this->idCardInfoWrapper = new Smartmatic::SAES::Voting::PBReports::IDCardInfoWrapper();
  this->objInstallMachine = new InstallMachine(saesDirectories, saesInstallDirectories);
  this->saesEnqueuer = new SaesEnqueuer();

  Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->init(electoralConfiguration, saesDirectories);

  (void) signal(SIGUSR2, MachineOperationManager::signalHandler);  // señal probada # 12

  MemoryPathController::getInstance()->updatePaths();

  std::string data = "SIGUSR2";
  SafeBuffer buffer(data);
  std::string sigFile = SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getSyncFileSignalUSER2();
  File::saveBufferToFile(buffer,sigFile);
}

void MachineOperationManager::signalHandler(int sig)
{
	std::cout << "SignalHandler : " << sig << std::endl;

	pthread_mutex_lock( &MachineOperationManager::mutexSignal );

    switch(sig)
    {
        case SIGUSR2:

        	MachineOperationManager::getInstance()->signalDetectChangeDevice();

            break;

        case SIGSEGV:

        	ZenityWrapper::showError(_("Smartmatic.SAES.Operation.MachineOperationManager.MessageErrorSIGSEGV"),
        				_("Smartmatic.SAES.Operation.MachineOperationManager.TitleErrorSIGSEGV"));

        	MachineOperationManager::getInstance()->exitMachine();

            break;

        case SIGABRT:

        	ZenityWrapper::showError(_("Smartmatic.SAES.Operation.MachineOperationManager.MessageErrorSIGABRT"),
        			_("Smartmatic.SAES.Operation.MachineOperationManager.TitleErrorSIGABRT"));

        	MachineOperationManager::getInstance()->exitMachine();

        	break;

        default:
            break;
    }

    // (void) signal(SIGUSR1, SIG_DFL); // quitar registro de señal
    // (void) signal(SIGUSR2, SIG_DFL); // quitar registro de señal

    pthread_mutex_unlock( &MachineOperationManager::mutexSignal );
}

MachineOperationManager::~MachineOperationManager()
{
  if(alarmController)
  {
	  delete(alarmController);
	  alarmController = NULL;
  }
  if (sortDomFile)
  {
	  delete sortDomFile;
	  sortDomFile = NULL;
  }
  if (sortFlashFile)
  {
	  delete sortFlashFile;
	  sortFlashFile = NULL;
  }
  if (basePathDom)
  {
	  delete basePathDom;
	  basePathDom = NULL;
  }
  if (basePathFlash)
  {
	  delete basePathFlash;
	  basePathFlash = NULL;
  }
  if (pvtransformer)
  {
	  delete pvtransformer;
	  pvtransformer = NULL;
  }
  if (saesDirectories)
  {
	  delete saesDirectories;
	  saesDirectories = NULL;
  }
  if (saesInstallDirectories)
  {
	  delete saesInstallDirectories;
	  saesInstallDirectories = NULL;
  }
  if (idCardInfoWrapper)
  {
	  delete idCardInfoWrapper;
	  idCardInfoWrapper = NULL;
  }
}

void MachineOperationManager::StartDetection()
{
    ConfigurationElectionFilesPath & configElectionFiles ((*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationElectionFilesPath());
    ConfigurationBasePath configBasePath = configElectionFiles.getConfigBasePath();
    RulesBasePathType rule = configBasePath.getRulesBasePath();

	if(rule == RulesBasePathType::CONFIGURATION_PM_RULE)
	{
		handleDetection = true;
	}
}

void MachineOperationManager::StopDetection()
{
	connDetected.disconnect();
	conn.disconnect();
	handleDetection = false;
}

void MachineOperationManager::signalDetectChangeDevice()
{
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &MachineOperationManager::DetectExtract), false);
}

void MachineOperationManager::DetectExtract()
{
	Glib::Mutex::Lock lock(mutex);

    MemoryPathController::getInstance()->updatePaths();

    std::string domMedia = MemoryPathController::getInstance()->getDomMemoryBasePath();
    std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();

    std::cout << "DomMemoryBasePath : " << domMedia << std::endl;
    std::cout << "FlashMemoryBasePath : " << flashMedia << std::endl;

    if(!handleDetection)
    {
    	return;
    }

    SMTTLogManager::shutdown();
    SMTTLogManager::Reconfigure();

	bool domNotPresent = domMedia.empty();
	bool flashNotPresent = flashMedia.empty();

	if (beforeInitialization)
	{
		if (domNotPresent && flashNotPresent)
		{
			setMemoryEvent(ERROR_MEMORY);
		}
	}
	else
	{
		if (isCheckData || (domNotPresent && flashNotPresent))
		{
			setMemoryEvent(ERROR_MEMORY);
		}
		else if (!isCheckData && (!domNotPresent && flashNotPresent))
		{
			setMemoryEvent(ONE_MEMORY);
		}
		else if (!isCheckData && (domNotPresent && !flashNotPresent))
		{
			setMemoryEvent(ONE_MEMORY);
		}
		else if (!domNotPresent && !flashNotPresent)
		{
			setMemoryEvent(TWO_MEMORY);

			if (!isCheckData)
			{
				isCheckData = true;
				if(!Glib::thread_supported()) Glib::thread_init();
				Glib::Thread::create(sigc::mem_fun(*this, &MachineOperationManager::checkDataDevice), false);
			}
		}
	}
}

void MachineOperationManager::startInitialization()
{
    beforeInitialization = false;
}

void MachineOperationManager::emitSignal()
{
	logger->Debug("Emit signal end ckeck data");

    std::string domMedia = MemoryPathController::getInstance()->getDomMemoryBasePath();
    std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();

    if (Directory::DirectoryExists(domMedia) && Directory::DirectoryExists(flashMedia))
    {
		if (checkDataResult)
		{
			setMemoryEvent(CHECK_MEMORY_OK);
		}
		else
		{
			setMemoryEvent(CHECK_MEMORY_ERROR);
		}
    }

	isCheckData = false;
}

void MachineOperationManager::checkDataDevice()
{
	checkDataResult = machineInitiator->checkData();
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MachineOperationManager::emitSignal), 3500);
}

void MachineOperationManager::setMachineInitiator( Smartmatic::SAES::Operation::Initiator::IMachineInitiator * machineInitiator )
{
    this->machineInitiator = machineInitiator;
}

Smartmatic::SAES::Operation::Initiator::IMachineInitiator * MachineOperationManager::getMachineInitiator()
{
    return this->machineInitiator;
}

SaesEnqueuer * MachineOperationManager::getSaesEnqueuer()
{
	return saesEnqueuer;
}

void MachineOperationManager::setAuthenticator( Smartmatic::SAES::Operation::Authenticator::IAuthenticator * authenticator )
{
    this->authenticator = authenticator;
}

Smartmatic::SAES::Operation::Authenticator::IAuthenticator * MachineOperationManager::getAuthenticator()
{
    return this->authenticator;
}

void MachineOperationManager::setElectoralConfiguration( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration )
{
    this->electoralConfiguration = electoralConfiguration;
}

void MachineOperationManager::setPollworkers( Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * pollworkers )
{
	 this->pollworkers = pollworkers;
}

Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * MachineOperationManager::getPollworkers()
{
	return this->pollworkers;
}

void MachineOperationManager::setActivatedCardStatistics( Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * activatedCardStatistics )
{
	this->activatedCardStatistics = activatedCardStatistics;
}

Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * MachineOperationManager::getActivatedCardStatistics()
{
	return this->activatedCardStatistics;
}

void MachineOperationManager::setAssistedActivation( Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * assistedActivation )
{
	 this->assistedActivation = assistedActivation;
}

Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * MachineOperationManager::getAssistedActivation()
{
	return this->assistedActivation;
}

void MachineOperationManager::setClosingNotes( Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * closingNotes )
{
	 this->closingNotes = closingNotes;
}

Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * MachineOperationManager::getClosingNotes()
{
	return this->closingNotes;
}

void MachineOperationManager::setIncidentReport( Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * incidentReport )
{
	 this->incidentReport = incidentReport;
}

Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * MachineOperationManager::getIncidentReport()
{
	return this->incidentReport;
}

Smartmatic::SAES::Voting::ElectoralConfiguration * MachineOperationManager::getElectoralConfiguration()
{
    return this->electoralConfiguration;
}

Smartmatic::SAES::Runtime::Environment::SaesDirectories * MachineOperationManager::getSaesDirectories()
{
    return saesDirectories;
}

void MachineOperationManager::setOperationStatus( Smartmatic::SAES::Voting::OperationStatus * operationStatus )
{
    this->operationStatus = operationStatus;
}

Smartmatic::SAES::Voting::OperationStatus * MachineOperationManager::getOperationStatus()
{
    return operationStatus;
}

void MachineOperationManager::setVotingExperienceController( Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController )
{
    this->votingExperienceController = votingExperienceController;
}

Smartmatic::SAES::Operation::Voting::VotingExperienceController * MachineOperationManager::getVotingExperienceController()
{
    return votingExperienceController;
}

AlarmController * MachineOperationManager::getAlarmController()
{
  return alarmController;
}

std::string MachineOperationManager::getMachineOperationCode()
{
    std::string code;

	std::string votingDeviceCode = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getCode();
	code += votingDeviceCode;

	std::string openingCode = getOperationStatus()->getElectionStatusWrapper()->getOpeningCode();
	code +="_"+openingCode;
 
	std::string pathIdHardware = saesDirectories->getIdHardwareFileFullPath();

    std::string hardwareId = "";

    std::ifstream fileM ( pathIdHardware.c_str() );

    if ( fileM.is_open() )
    {
        if ( fileM.good() ) getline ( fileM, hardwareId );
        fileM.close();
        code +="_"+hardwareId;
    }
    else
    {
        logger->Debug("Hardware id file " + pathIdHardware + " not found.");
    }
	
    return code;
}

void MachineOperationManager::PersistencePMInstallerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start persistence pm installer data");
    idCardInfoWrapper->addPMInstallIdCardInfo(citizenInfo);
    logger->Debug("Success persistence pm installer data");
}

void MachineOperationManager::PersistenceInstallerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start persistence installer data");
    idCardInfoWrapper->addVMInstallIdCardInfo(citizenInfo);
    logger->Debug("Success persistence installer data");
}
void MachineOperationManager::PersistenceOpenerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start persistence opener data");
    idCardInfoWrapper->addOpenElectionIdCardInfo(citizenInfo);
    logger->Debug("Success persistence opener data");
}

void MachineOperationManager::PersistenceVotingCloserData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start persistence voting closer data");
    idCardInfoWrapper->addCloseVotingIdCardInfo(citizenInfo);
    logger->Debug("Success persistence closer data");
}

void MachineOperationManager::PersistenceElectionCloserData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start persistence election closer data");
    idCardInfoWrapper->addCloseElectionIdCardInfo(citizenInfo);
    logger->Debug("Success persistence election closer data");
}

bool MachineOperationManager::persistenceVote(Smartmatic::SAES::Voting::Vote::Vote & vote)
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	//Glib::Mutex::Lock lock(mutexVote);

	if (isCheckData)
	{
		logger->Debug("Check data in progress");
		return false;
	}

	logger->Debug("Start persistence vote");

    std::string folderDOM = sortDomFile->getFolder();
    std::string folderFlash = sortFlashFile->getFolder();

    bool saveVoteOneMemory = operationStatus->getElectionStatusWrapper()->getSynchronizeVotes();

	if (!saveVoteOneMemory && (!Directory::DirectoryExists(folderDOM) || !Directory::DirectoryExists(folderFlash)))
	{
		logger->Debug("ERROR - Device Dom or Flash not found, not persistence vote");
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"));
		return false;
	}

    if (!Vote::VoteWrapper::validateVote(electoralConfiguration, vote))
    {
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatingVote"));
        throw Smartmatic::System::Exception::XmlException(
                _("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatedVote"),
                N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatedVote"), logger);
    }

    if (!getVoteStatistics()->IsVoteProcessed(vote))
    {
        logger->Debug("Start persistence vote file");

        Runtime::Environment::FileNameHasher hasher;
        std::string file = hasher.GetFileNameHasher(vote.getCode()) + ".vt";

        std::string fullPathDOM = Path::Combine(folderDOM, file);
        std::string fullPathFlash = Path::Combine(folderFlash, file);

        if (File::canOpenFile(fullPathDOM) || File::canOpenFile(fullPathFlash))
        {
        	Vote::Vote existVote;
        	Vote::VoteWrapper::voteFileToVote(fullPathDOM, existVote);

        	logger->Debug("ERROR - vote file " + file + " with code=" + existVote.getCode() + " exist.");
        	logger->Debug("ERROR - vote file " + file + " with code=" + vote.getCode() + " not persistence.");

        	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatingVote"));
            throw Smartmatic::System::Exception::XmlException(
                    _("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatedVote"),
                    N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorValidatedVote"), logger);
        }

        std::string strVote;
        Smartmatic::SAES::Voting::Vote::VoteWrapper::voteToString(vote, strVote);

        try
        {
			Encryption::getInstance()->saveXmlFile(strVote, fullPathDOM, Encryption::EXCHANGE_FILE);

			if (!saveVoteOneMemory)
			{
				File::copyFile(fullPathDOM, fullPathFlash);
			}
        }
        catch (...)
        {
			logger->Debug("FATAL - persistence vote, read vote file " + file);
			File::DeleteFile(fullPathDOM);
			File::DeleteFile(fullPathFlash);
			logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"));
	        throw Smartmatic::System::Exception::XmlException(
	                _("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"),
	                N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"), logger);
		}

        Vote::Vote vote;

        if (!Vote::VoteWrapper::voteFileToVote(fullPathDOM, vote) ||
            (!saveVoteOneMemory && !Vote::VoteWrapper::voteFileToVote(fullPathFlash, vote)))
        {
			logger->Debug("FATAL - persistence vote, read vote file " + file);
			File::DeleteFile(fullPathDOM);
			File::DeleteFile(fullPathFlash);

			logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"));
	        throw Smartmatic::System::Exception::XmlException(
	                _("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"),
	                N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVote"), logger);
		}

        sortDomFile->addFile(file);
       	sortFlashFile->addFile(file);

        persistenceFileSystemVote();

        logger->Debug("Success persistence vote file");

        getVoteStatistics()->ProcessVote(vote);
        getVoteStatistics()->persistence();

        switch(vote.getMode())
        {
        case Vote::VoteMode::VOTE_O:
        	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SucessfullPersistenceOfficialVote"));
        	break;
        case Vote::VoteMode::VOTE_D:
        	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SucessfullPersistenceDemoVote"));
        	break;
        case Vote::VoteMode::VOTE_R:
        	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SucessfullPersistenceRecoveryVote"));
        	break;
        case Vote::VoteMode::VOTE_S:
        	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SucessfullPersistenceSimulateVote"));
        	break;
        }
    }
    else
    {
    	getVoteStatistics()->ProcessVote(vote);
    	getVoteStatistics()->persistence();

    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SucessfullPersistenceDuplicatedVote"));
    }



    return true;
}

void MachineOperationManager::deleteVote(Smartmatic::SAES::Voting::Vote::Vote & vote)
{
    if (!getVoteStatistics()->IsVoteProcessed(vote))
    {
        Runtime::Environment::FileNameHasher hasher;
        std::string file = hasher.GetFileNameHasher(vote.getCode()) + ".vt";

        std::string folderDOM = sortDomFile->getFolder();
        std::string folderFlash = sortFlashFile->getFolder();

        std::string fullPathDOM = Path::Combine(folderDOM, file);
        std::string fullPathFlash = Path::Combine(folderFlash, file);

        File::DeleteFile(fullPathDOM);
        File::DeleteFile(fullPathFlash);
    }
}

void MachineOperationManager::persistenceFileSystemVote()
{
	sortDomFile->persistFiles();
	sortFlashFile->persistFiles();
}

bool MachineOperationManager::persistenceVote(Smartmatic::System::SafeBuffer & buffer)
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	bool resp = false;

    Smartmatic::SAES::Voting::Vote::Vote * vote = NULL;
    VoteFromSafeBufferResult result = getVoteFromSafeBuffer(buffer, vote);

    if (result == VOTE_FROM_BUFFER_SUCCESS)
    {
    	resp = persistenceVote(*vote);
    	delete  vote;
    }
    else if (result == VOTE_FROM_BUFFER_DECRYPTO_ERROR)
    {
    	if (vote) delete  vote;
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistingVoteDecyptoException"));
        throw System::Exception::CryptoException(_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorDecryptoData"),N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorDecryptoData"), logger);
    }
    else if (result == VOTE_FROM_BUFFER_DECOMPRESSION_ERROR)
    {
    	if (vote) delete  vote;
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistingVoteDecompressionException"));
        throw System::Exception::CryptoException(_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorDecompressData"),N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorDecompressData"), logger);
    }
    else if (result == VOTE_FROM_BUFFER_SIGNATURE_ERROR || result == VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR)
    {
    	if (vote) delete  vote;
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistingVoteSignatureException"));
        throw System::Exception::CryptoException(_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorSignedData"),N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorSignedData"), logger);
    }
    else
    {
    	if (vote) delete  vote;
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistingVoteErrorData"));
        throw System::Exception::CryptoException(_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorData"),N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorData"), logger);
    }
	
    if (resp)
	{
    	logger->Debug("Success persistence vote");
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SuccessPersistenceVote"));
	}

    return resp;
}

void MachineOperationManager::setVoteStatistics(Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * voteStatistics)
{
    this->voteStatistics = voteStatistics;
}

Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * MachineOperationManager::getVoteStatistics()
{
    return this->voteStatistics;
}

Smartmatic::SAES::Voting::PBReports::StatisticManager * MachineOperationManager::getStatisticManager()
{
    return this->statisticManager;
}

Smartmatic::SAES::Voting::PBReports::VotingDisabledWrapper * MachineOperationManager::getVotingDisabledWrapper()
{
	return this->votingDisabledWrapper;
}

Smartmatic::SAES::Voting::PBReports::PoliceNoteWrapper * MachineOperationManager::getPoliceNoteWrapper()
{
	return this->policeNoteWrapper;
}

void MachineOperationManager::setStatisticManager (Smartmatic::SAES::Voting::PBReports::StatisticManager * statisticManager)
{
    this->statisticManager = statisticManager;
}

MachineOperationManager * MachineOperationManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new MachineOperationManager();
    }

    return instance;
}

bool MachineOperationManager::checkVotes(int deltaP)
{
    logger->Debug("Start check file system votes");

    std::string votesFolderDom = sortDomFile->getFolder();
    std::string votesFolderFlash = sortFlashFile->getFolder();

    std::vector<std::string> listDom;
    std::vector<std::string> listFlash;

    std::vector<std::string>::iterator itDom;
    System::IO::Directory::GetFiles(votesFolderDom, listDom, false, true);
    System::IO::Directory::GetFiles(votesFolderFlash, listFlash, false, true);

    if (!votingIsPossible() && listDom.size() > 0)
    {
    	logger->Debug("ERROR - Check file system votes, exist votes in dom folder");
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorFoundFolderDomVotes"));
        return false;
    }

    if (!votingIsPossible() && listFlash.size() > 0)
    {
    	logger->Debug("ERROR - Check file system votes, exist votes in flash folder");
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorFoundFolderFlashVotes"));
        return false;
    }

    int officialVotes = getVoteStatistics()->getOfficialVotes();
    int demoVotes = getVoteStatistics()->getDemoVotes();
    int securityCopyVotes = getVoteStatistics()->getSecurityCopyVotes();
    int superNullVotes = getVoteStatistics()->getSuperNullVotes();
    int totalVotes = getVoteStatistics()->getTotalVotes();

    int delta = listDom.size() - totalVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
    	{
    		std::stringstream ss;
    		ss << "ERROR - Check file system votes, file delta votes > ";
    		ss << deltaP << " - Dom files = " << listDom.size() << ", Total votes = " << totalVotes;
    		logger->Debug(ss.str());
    	}

        logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorCountVotes"));
        return false;
    }

    delta = listDom.size() - listFlash.size();

    if(!(delta >=0 && delta <= deltaP))
    {
    	{
    		std::stringstream ss;
    		ss << "ERROR - Check file system votes, file delta votes > ";
    		ss << deltaP << " - Dom files = " << listDom.size() << ", Flash files = " << listFlash.size();
    		logger->Debug(ss.str());
    	}

        logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorCountVotes"));
        return false;
    }
    else
    {
        getVoteStatistics()->clearCounter();
    }

    for (itDom = listDom.begin();
         itDom != listDom.end();
         itDom++)
    {
        std::string fileDom = Path::Combine(votesFolderDom, (*itDom));

        Smartmatic::SAES::Voting::Vote::Vote vote;

        if (!Vote::VoteWrapper::voteFileToVote(fileDom, vote))
        {
			logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorVote"));
			return false;
        }

        if (Vote::VoteWrapper::validateVote(electoralConfiguration, vote))
        {
            Runtime::Environment::FileNameHasher hasher;
            std::string fileCode = hasher.GetFileNameHasher(vote.getCode()) + ".vt";

            if ((*itDom) == fileCode)
            {
                getVoteStatistics()->ProcessVote(vote);
            }
            else
            {
            	logger->Debug("VoteCode: " + vote.getCode() + " -> " + fileCode + " (" + *itDom + ")");
                logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorFileNameVote"));
                return false;
            }
        }
        else
        {
            logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorValidateVote"));
            return false;
        }
    }

    delta = getVoteStatistics()->getOfficialVotes() - officialVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
    	std::stringstream ss;
    	ss << "OfficialVotesStatistics: " << getVoteStatistics()->getOfficialVotes() << " OfficialVotes: " << officialVotes;
    	logger->Debug(ss.str());
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLostOfficialVotes"));
        return false;
    }

    delta = getVoteStatistics()->getDemoVotes() - demoVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLostDemoVotes"));
        return false;
    }

    delta = getVoteStatistics()->getSecurityCopyVotes() - securityCopyVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLostSecurityCopyVotes"));
        return false;
    }

    delta = getVoteStatistics()->getSuperNullVotes() - superNullVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLostSuperNullVotes"));
        return false;
    }

    delta = getVoteStatistics()->getTotalVotes() - totalVotes;

    if (!(delta >=0 && delta <= deltaP))
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLostTotalVotes"));
        return false;
    }

    try
    {
        getVoteStatistics()->persistence();
    }
    catch(...)
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistenceVoteStatistics"));
        return false;
    }

	logger->Debug("Success check file system votes");

	return true;
}

void MachineOperationManager::configurationReset()
{

}

bool MachineOperationManager::authentication(std::string & center, std::string & password, bool centerCaseSensitive)
{
	return objInstallMachine->authentication(center, password, centerCaseSensitive, electoralConfiguration);
}

SaesInstallDirectories * MachineOperationManager::getSaesInstallDirectories()
{
	return saesInstallDirectories;
}

bool MachineOperationManager::install()
{
	return objInstallMachine->install();
}

std::list<Smartmatic::SAES::Voting::Election::Language> MachineOperationManager::getLanguagesElection()
{
	std::list<Smartmatic::SAES::Voting::Election::Language> languages;
	std::list<Smartmatic::SAES::Voting::Election::Language> langs;

	if(electoralConfiguration == NULL)
		return languages;

	//Initialize the language handling class with the items in the list.
	Election::ElectionInstalationLanguages::getInstance()->clearLanguage();
	Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & sequence (electoralConfiguration->getLanguages().getLanguage());
	Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

	for (it = sequence.begin();
		 it != sequence.end();
		 ++it)
	{
		languages.push_back(*it);
	}

	std::list<Smartmatic::SAES::Voting::Election::Language>::iterator itl;

	for (itl = languages.begin();
		 itl != languages.end();
		 ++itl)
	{
		if((*itl).getIs_default())
		{
			langs.push_back((*itl));
		}

		(*itl).setIs_default(false);
		Election::ElectionInstalationLanguages::getInstance()->addInstallationLanguages((*itl));
	}

	return langs;
}

std::list<Election::Language> MachineOperationManager::getLanguagesInstall()
{
	std::list<Election::Language> languages;
	Election::ElectionInstalationLanguages::getInstance()->ReloadLanguages();
	languages = Election::ElectionInstalationLanguages::getInstance()->getLanguages();

	//Initialize the language handling class with the items in the list.
	Election::ElectionInstalationLanguages::getInstance()->clearLanguage();

	std::list<Election::Language> langs;
	std::list<Election::Language>::iterator itl;

	for (itl = languages.begin();
		 itl != languages.end();
		 ++itl)
	{
		if((*itl).getIs_default())
		{
			langs.push_back((*itl));
		}

		(*itl).setIs_default(false);
		Election::ElectionInstalationLanguages::getInstance()->addInstallationLanguages((*itl));
	}

	return langs;
}

void MachineOperationManager::startUp()
    throw (Smartmatic::System::Exception::ElectionException,
			Smartmatic::System::Exception::VotingDeviceException,
			Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException,
            Smartmatic::System::Exception::GuIdException,
            Smartmatic::System::Exception::VoteException,
            Smartmatic::System::Exception::FileSystemException)
{
	logger->Debug("Start load configuration machine");

    if (SAESFunctionalityConfigurationManager::Current()->getOperationConfiguration().getConfigurationReset())
    {
        configurationReset();
    }

    electoralConfiguration->init(saesDirectories);
    electoralConfiguration->loadAllData();

    std::string openingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getOpening_date_time();
    std::string closingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getClosing_date_time();

    Glib::TimeVal openingTime;
    Glib::TimeVal closingTime;

    openingTime.assign_from_iso8601(openingDateTime);
    double openingD = openingTime.as_double();

    closingTime.assign_from_iso8601(closingDateTime);
    double closingD = closingTime.as_double();

    Smartmatic::SAES::Security::Encryption::getInstance()->setMachineTime(openingD + (openingD + closingD)/2);

    if (loadOpeninCode)
    {
    	getOperationStatus()->InitializeElectionStatus();
    }

    getOperationStatus()->InitializeVMStatus();
    getOperationStatus()->InitializeCardDataListStatus();

    if (!getVotingDisabledWrapper()->init())
    {
    	getVotingDisabledWrapper()->persistence();
    }

    if (!getPoliceNoteWrapper()->init())
    {
    	getPoliceNoteWrapper()->persistence();
    }

    if (!getAssistedActivation()->init())
    {
        getAssistedActivation()->Persist();
    }

    if (!getActivatedCardStatistics()->init(electoralConfiguration))
    {
        getActivatedCardStatistics()->Persist();
    }

    getActivatedCardStatistics()->RestoreFile(electoralConfiguration);

    if (!getIncidentReport()->init())
    {
        getIncidentReport()->Persist();
    }

    if (!getPollworkers()->init())
    {
        getPollworkers()->Persist();
    }

    if (!getClosingNotes()->init())
    {
        getClosingNotes()->Persist();
    }

    if (!getIDCardInfoWrapper()->init(saesDirectories))
    {
    	getIDCardInfoWrapper()->persistence();
    }

    if (!startFirstTime)
    {
        startFirstTime = true;

        if (!getStatisticManager()->init(operationStatus, assistedActivation, activatedCardStatistics, voteStatistics))
        {
            getStatisticManager()->persistence();
        }

        if (!getVoteStatistics()->init(electoralConfiguration))
        {
        	getVoteStatistics()->persistence();
        }

        Smartmatic::System::IO::Directory::Mkdir(saesDirectories->getDocsFolderFullPath());
        Smartmatic::System::IO::Directory::Mkdir(saesDirectories->getVotesFolderFullPath());

        Glib::ustring openingCode = getOperationStatus()->getElectionStatusWrapper()->getOpeningCode();
        logger->Debug("startup opening code " + openingCode);

        Smartmatic::System::GuidClass openCodeGUID = Smartmatic::System::GuidClass::Parse(openingCode);
        Smartmatic::SAES::Security::Encryption::getInstance()->setOpeningCode(openCodeGUID);

        getOperationStatus()->persistElectionStatus(loadOpeninCode);
        getOperationStatus()->persistVotingMachineStatus();
        getOperationStatus()->PersistOnStatusChange(true);

        loadOpeninCode = true;
    }

    if (SAESFunctionalityConfigurationManager::Current()->getOperationConfiguration().getStartOpenElection())
    {
        openElection();
    }

    Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->init(
            electoralConfiguration,
            operationStatus,
            pollworkers,
            statisticManager,
            assistedActivation,
            activatedCardStatistics,
            voteStatistics,
            incidentReport,
            closingNotes,
            idCardInfoWrapper,
            votingDisabledWrapper,
            policeNoteWrapper);

	TimeConfiguration type =
			SAESCommonConfigurationManager::Current()->getFileSystemVoteConfiguration().getImplementTime();

    std::string date;

	switch(type)
	{
		case TimeConfiguration::CONFIGURATION_CONFIG_TIME:
			date = SAESCommonConfigurationManager::Current()->getFileSystemVoteConfiguration().getFileSystemVoteTime();
			break;
		case TimeConfiguration::CONFIGURATION_MACHINE_TIME:
			date = openingTime.as_iso8601();
			break;
		case TimeConfiguration::CONFIGURATION_NONE:
			date = "";
			break;
	}

	sortDomFile->updateDate(date);
	sortFlashFile->updateDate(date);

    logger->Debug("Success load configuration machine");
}

void MachineOperationManager::createMachineId(bool force)
{
    std::string code = getMachineOperationCode();
    Smartmatic::SAES::Runtime::Environment::DirectoryManager directorymanager ( *saesDirectories );
    directorymanager.createMachineIdFile(code, force);
}

bool MachineOperationManager::validateMachineId()
{
    std::string code = getMachineOperationCode();
    Smartmatic::SAES::Runtime::Environment::DirectoryManager directorymanager ( *saesDirectories );
    return directorymanager.validateMachineIdFile(code);
}

bool MachineOperationManager::validateVotes()
{
    logger->Debug("validating votes");

    if (!sortDomFile->recoverVotes() || !sortFlashFile->recoverVotes())
    {
    	return false;
    }

    std::string votesFolderDom = sortDomFile->getFolder();
    std::string votesFolderFlash = sortFlashFile->getFolder();

    std::vector<std::string> listDom;
    std::vector<std::string> listFlash;
    std::vector<std::string> listTempFlash;

    std::vector<std::string>::iterator itDom;
    std::vector<std::string>::iterator itFlash;

    System::IO::Directory::GetFiles(votesFolderDom, listDom, false, true);
    System::IO::Directory::GetFiles(votesFolderFlash, listFlash, false, true);

    std::stringstream ss1;
    ss1 << "votes dom = " << listDom.size();
    logger->Debug(ss1.str());

    std::stringstream ss2;
    ss2 << "votes flash = " << listFlash.size();
    logger->Debug(ss2.str());

    listTempFlash = listFlash;

    unsigned int delta;
    unsigned int check;

    bool saveVoteOneMemory = operationStatus->getElectionStatusWrapper()->getSynchronizeVotes();

    if (saveVoteOneMemory)
    {
    	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.RestoreVoteInAllMemory"));
    	delta = getVoteStatistics()->getDeltaVotes();
    	check = delta;
    }
    else
    {
    	check = 1;
    	delta = abs((int)listDom.size() - (int)listFlash.size());
    }

    if (!(delta >= 0 && delta <= check))
    {
        logger->Error("Error vote list size in dom and flash - delta " + delta);
        return false;
    }

    /// validate votes
    for (itDom = listDom.begin();
            itDom != listDom.end();
            itDom++)
    {
        for (itFlash = listFlash.begin();
                itFlash != listFlash.end();
                itFlash++)
        {
            if ((*itFlash) == (*itDom))
            {
            	std::string file = *itDom;
                std::string fileDomFullPath = Path::Combine(votesFolderDom, (file));
                std::string fileFlashFullPath = Path::Combine(votesFolderFlash, (file));

                listFlash.erase(itFlash);

                if (!File::compareFiles(fileDomFullPath, fileFlashFullPath))
                {
                	Vote::Vote voteDom;
                	Vote::Vote voteFlash;

                	bool successDom = Vote::VoteWrapper::voteFileToVote(fileDomFullPath, voteDom);
                	bool successFlash = Vote::VoteWrapper::voteFileToVote(fileFlashFullPath, voteFlash);

                	if (successDom && !successFlash)
                	{
                		logger->Debug("Restore file vote dom to flash " + file);
                		File::copyFile(fileDomFullPath, fileFlashFullPath);
                	}
                	else if (!successDom && successFlash)
                	{
                		logger->Debug("Restore file vote flash to dom " + file);
                		File::copyFile(fileFlashFullPath, fileDomFullPath);
                	}
                	else if (successDom && successFlash)
                	{
                		logger->Error("Error file dom and flash " + file);
                		logger->Debug("Vote code in dom " + voteDom.getCode());
                		logger->Debug("Vote code in flash " + voteFlash.getCode());
                		return false;
                	}
                	else
                	{
                		logger->Error("Error structure file dom and flash " + file);
                		return false;
                	}
                }

                break;
            }
        }
    }

    // clear all file
    for (itFlash = listTempFlash.begin();
            itFlash != listTempFlash.end();
            itFlash++)
    {
        for (itDom = listDom.begin();
                itDom != listDom.end();
                itDom++)
        {
            if ((*itFlash) == (*itDom))
            {
                listDom.erase(itDom);
                break;
            }
        }
    }

    /// copy file vote to flash
    for (itDom = listDom.begin();
            itDom != listDom.end();
            itDom++)
    {
        std::string fileName = *itDom;
        std::string fileDomFullPath = Path::Combine(votesFolderDom, fileName);
        std::string fileFlashFullPath = Path::Combine(votesFolderFlash, fileName);
        File::copyFile(fileDomFullPath, fileFlashFullPath);
        logger->Debug("Restore file vote to flash " + fileName);
    }

    /// copy file vote to dom
    for (itFlash = listFlash.begin();
    		itFlash != listFlash.end();
    		itFlash++)
    {
        std::string fileName = *itFlash;
        std::string fileDomFullPath = Path::Combine(votesFolderDom, fileName);
        std::string fileFlashFullPath = Path::Combine(votesFolderFlash, fileName);
        File::copyFile(fileFlashFullPath, fileDomFullPath);
        logger->Debug("Restore file vote to dom " + fileName);
    }

    try
    {
    	if (saveVoteOneMemory)
    	{
    		restoreVoteInAllMemory();
    	}
    }
    catch(...)
    {
    	return false;
    }

    return true;
}

bool MachineOperationManager::checkPVReport()
{
    bool validate = false;

    if (isCloseElection())
    {
        validate = Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->validate();
    }
    else
    {
        validate = true;
    }

    return validate;
}

bool MachineOperationManager::checkTransmissionPackages()
{
    bool validate = false;

    if (isCloseElection())
    {
        validate = Vote::TransmissionPackageWrapper::getInstance()->validate();
    }
    else
    {
        validate = true;
    }

    return validate;
}

bool MachineOperationManager::checkMachineId()
{
    std::string dom = saesDirectories->getBackupFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getBackupFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::compareFiles(dom, flash);
}

bool MachineOperationManager::checkIdCardMembers()
{
    std::string dom = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkSAESFiles()
{
	bool validate = true;

	if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getVerifySAESFolder())
	{
		std::string dom = saesDirectories->getBaseInstallationPath(BasePathType::CONFIGURATION_DOM);
		std::string flash = saesDirectories->getBaseInstallationPath(BasePathType::CONFIGURATION_FLASH);

		validate = Directory::compareDirectoryStructure(dom, flash) && Directory::compareDirectories(dom, flash, false);
	}

	std::string vdom = saesDirectories->getVotingCentersInstalationFileFullPath(BasePathType::CONFIGURATION_DOM);
	std::string vflash = saesDirectories->getVotingCentersInstalationFileFullPath(BasePathType::CONFIGURATION_FLASH);

	validate = validate && File::compareFiles(vdom, vflash);

	return validate;
}

bool MachineOperationManager::checkSAESLocal()
{
	std::string dom = saesDirectories->getBasePath(BasePathType::CONFIGURATION_DOM);
	std::string flash = saesDirectories->getBasePath(BasePathType::CONFIGURATION_FLASH);

	return Directory::compareDirectoryStructure(dom, flash);
}

bool MachineOperationManager::checkVoteStatistics()
{
    std::string dom = saesDirectories->getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkElectionStatus()
{
    std::string dom = saesDirectories->getElectionStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getElectionStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkElection()
{
    std::string dom = saesDirectories->getElectionFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getElectionFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::compareFiles(dom, flash);
}

bool MachineOperationManager::checkVotingDevices()
{
    std::string dom = saesDirectories->getVotingDeviceFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getVotingDeviceFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::compareFiles(dom, flash);
}

bool MachineOperationManager::checkActivatedCardStatistics()
{
    std::string dom = saesDirectories->getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkAssistedActivations()
{
    std::string dom = saesDirectories->getAssistedActivationFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getAssistedActivationFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkVotingDisabled()
{
    std::string dom = saesDirectories->getVotingDisabledFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getVotingDisabledFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkPoliceNotes()
{
    std::string dom = saesDirectories->getPoliceNotesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getPoliceNotesFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkPollworkers()
{
    std::string dom = saesDirectories->getPollworkersFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getPollworkersFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkSignature()
{
    std::string dom = saesDirectories->getSignatureResourceFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getSignatureResourceFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkClosingNotes()
{
    std::string dom = saesDirectories->getClosingNotesFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getClosingNotesFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkStatistics()
{
    std::string dom = saesDirectories->getStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkTechnicalTroubles()
{
    std::string dom = saesDirectories->getIncidentReportFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getIncidentReportFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

bool MachineOperationManager::checkVotingDeviceStatus()
{
    std::string dom = saesDirectories->getVotingMachineStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string flash = saesDirectories->getVotingMachineStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    return File::canOpenFile(dom) && File::canOpenFile(flash);
}

void MachineOperationManager::installMachine()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	if(operationStatus->getElectionStatusWrapper()->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINSTALLED)
	{

		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StatingInstallMachine"));
		logger->Debug("Start install machine");


		operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTPOLLWORKERREGISTERED);
		getOperationStatus()->persistElectionStatus();

		logger->Debug("Success install machine");
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.MachineInstalled"));
	}
}

void MachineOperationManager::registerPollworker()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StatingRegisterPollworker"));
    logger->Debug("Start register pollworker");

    operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE);
    getOperationStatus()->persistElectionStatus();

    logger->Debug("Success register pollworker");
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.PollworkerRegistered"));
}

void MachineOperationManager::demostrationVote()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StatingDemostrationVote"));
    logger->Debug("Start demostration vote");

    operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED);
    getOperationStatus()->persistElectionStatus();

    logger->Debug("Success demostration vote");
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.DemostrationVote"));
}

void MachineOperationManager::openElection()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StatingOpenElection"));
    logger->Debug("Start open election");

    Glib::TimeVal now;
	now.assign_current_time();

	operationStatus->getElectionStatusWrapper()->setOpenElectionDate(now.as_iso8601());
	operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED);
    getOperationStatus()->persistElectionStatus();

    logger->Debug("Success open election");
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ElectionOpened"));
}

void MachineOperationManager::closeElection()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StartingCloseElection"));
    logger->Debug("Start close election");

    persistenceFileSystemVote();

    Glib::TimeVal now;
	now.assign_current_time();

	operationStatus->getElectionStatusWrapper()->setCloseElectionDate(now.as_iso8601());
	operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED);

    getOperationStatus()->persistElectionStatus();

    std::string folderDom = saesDirectories->getBasePath(BasePathType::CONFIGURATION_DOM);
    std::string folderFlash = saesDirectories->getBasePath(BasePathType::CONFIGURATION_FLASH);
    std::string command = "chmod 777 -R ";

    (void)ProcessLauncher::RunProcessThroughSystem ((command + folderDom).c_str());
    (void)ProcessLauncher::RunProcessThroughSystem ((command + folderFlash).c_str());

    logger->Debug("Success close election");
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ElectionClosed"));
}

void MachineOperationManager::loadStationTally()
	throw (Smartmatic::System::Exception::CryptoException,
			Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::XmlException)
{
    logger->Debug("Start load station tally info");


    logger->Debug("Success load station tally info");
}

void MachineOperationManager::persistAllResult()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException,
            Smartmatic::System::Exception::CodiException)
{
    logger->Debug("Start persistence transmission package");

	Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->deleteVotes();

	std::string votesFolderDom = sortDomFile->getFolder();
    std::string votesFolderFlash = sortFlashFile->getFolder();

    std::vector<std::string> listDom;
    std::vector<std::string>::iterator itDom;

    System::IO::Directory::GetFiles(votesFolderDom, listDom, false, true);

    for (itDom = listDom.begin();
         itDom != listDom.end();
         itDom++)
    {
        std::string fileDom = Path::Combine(votesFolderDom, (*itDom));
        std::string fileFlash = Path::Combine(votesFolderFlash, (*itDom));
        Smartmatic::SAES::Voting::Vote::Vote vote;

        if (!Vote::VoteWrapper::voteFileToVote(fileDom, vote) &&
        	!Vote::VoteWrapper::voteFileToVote(fileFlash, vote))
        {
            logger->Audit(N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorVote"));
            Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->deleteVotes();
            throw Smartmatic::System::Exception::XmlException(
    				_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorVote"),
    				N_("Smartmatic.SAES.Functionality.Operation.MachineOperationManager.ErrorVote"),
    				logger);
        }
        else
        {
            Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->addVote(vote);
        }
    }

    Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->persistTransmissionPackage();
	Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->deleteVotes();

    logger->Debug("Success persistence transmission package");
}

void MachineOperationManager::persistPVForm()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException,
            Smartmatic::System::Exception::SignByCardIDException)
{
    logger->Debug("Start persistence pv report data");
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StartingPersistPVForm"));

	if (!Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->persistencePVForm(pvtransformer))
	{
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistPVForm"));

		throw Smartmatic::System::Exception::XmlException (
				_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistPVForm"),
				N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorPersistPVForm"),
				logger);
	}

    generatePVFormSigFile();

	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.PersistPVFormSuccess"));
    logger->Debug("Success persistence pv report data");
}

void MachineOperationManager::generatePVFormSigFile( bool copyToFlash )
    throw (Smartmatic::System::Exception::CryptoException,
        Smartmatic::System::Exception::SignedException,
        Smartmatic::System::Exception::XmlException,
        Smartmatic::System::Exception::SignByCardIDException)
{
    std::list <std::string> languages = Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->getLanguages();

    bool signedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSignedPVForm();

    if (signedFile)
    {
        logger->Debug("Start persistence signed pv report data");

        std::string pvformFileDom = saesDirectories->getPVFormFileFullPath();
        std::string signedFileDom = saesDirectories->getPVFormSignatureFileFullPath();
        std::string signedFileFlash = saesDirectories->getPVFormSignatureFileFullPath(BasePathType::CONFIGURATION_FLASH);

        std::list <std::string>::iterator itl;

        for (itl = languages.begin();
             itl != languages.begin();
             itl++)
        {
            std::string lang = (*itl);

            std::string pvformFileDomTemp = Path::GetFullFileNameWithOutExtension(pvformFileDom) + lang + Path::GetFileExtension(pvformFileDom);
            std::string signedFileDomTemp = Path::GetFullFileNameWithOutExtension(signedFileDom) + lang + Path::GetFileExtension(signedFileDom);

            logger->Debug("input pv report file " + pvformFileDomTemp);
            logger->Debug("signed pv report file " + signedFileDomTemp);

            std::string data =  Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile( pvformFileDomTemp,
                    Smartmatic::SAES::Security::Encryption::UTIL_FILE);

            SafeBuffer buffer ((unsigned char *)data.c_str(), data.length());
            generateSigFile(buffer, signedFileDomTemp);

            if (copyToFlash)
            {
                std::string signedFileFlashTemp = Path::GetFullFileNameWithOutExtension(signedFileFlash) + lang + Path::GetFileExtension(signedFileFlash);
                File::copyFile(signedFileDomTemp, signedFileFlashTemp);
            }
        }

        logger->Debug("Success persistence signed pv report data");
    }
}

void MachineOperationManager::signElectionResults(bool sign, bool copyToFile)
throw (Smartmatic::System::Exception::CryptoException,
		Smartmatic::System::Exception::SignedException,
		Smartmatic::System::Exception::XmlException,
		Smartmatic::System::Exception::SignByCardIDException)
{

	SafeBuffer toSign;

	std::list<std::string> fileList;

	//Add the transmission package
	std::string fileDom = saesDirectories->getTransmissionPackagesFileFullPath();
	File::openFileToBuffer(fileDom, toSign);

	//Add the pv data files
	std::list <std::string> languages = Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->getLanguages();
	std::list <std::string>::iterator itl;

	std::string pvformFileDom = saesDirectories->getPVFormFileFullPath();

	for (itl = languages.begin();
			itl != languages.end();
			itl++)
	{
		std::string lang = (*itl);
		std::string pvformFileDomTemp = Path::GetFullFileNameWithOutExtension(pvformFileDom) + lang + Path::GetFileExtension(pvformFileDom);
		fileList.push_back(pvformFileDomTemp);
	}

	// Sort the file to sign
	fileList.sort();
	//Add the files to the buffer
	std::list<std::string>::iterator it = fileList.begin();
	while(it != fileList.end())
	{
		std::string pvFileName = *it++;
		std::string pvData =  Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile( pvFileName,
		                    Smartmatic::SAES::Security::Encryption::UTIL_FILE);
		toSign.AddData((const unsigned char*)	pvData.c_str(),pvData.size());
	}
	//Sign the file - this save the file to dom
	std::string resultSignFile = saesDirectories->getElectionResultSignatureFileFullPath();

	if(sign)
	{
		//TODO: fix the name
		generateSigFile(toSign, resultSignFile);

		if(copyToFile)
		{
			std::string flashresultSignFile = saesDirectories->getElectionResultSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH);
			File::copyFile(resultSignFile, flashresultSignFile);
		}
	}
}

void MachineOperationManager::generateTransmissionPackageSigFile()
    throw (Smartmatic::System::Exception::CryptoException,
        Smartmatic::System::Exception::SignedException,
        Smartmatic::System::Exception::XmlException,
        Smartmatic::System::Exception::SignByCardIDException)
{
    logger->Debug("Start persistence signed transmission package");

    std::string devicePathDom = saesDirectories->getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = saesDirectories->getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = saesDirectories->getTransmissionPackageSignatureFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = saesDirectories->getTransmissionPackageSignatureFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::string signedFileDom = saesDirectories->getTransmissionPackageSignatureFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string signedFileFlash = saesDirectories->getTransmissionPackageSignatureFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	std::string data =  Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile( fileDom,
    	            Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

    	SafeBuffer buffer ((unsigned char *)data.c_str(), data.length());
    	generateSigFile(buffer, signedFileDom);

        File::copyFile(signedFileDom, signedFileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	std::string data =  Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile( fileFlash,
    	            Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

    	SafeBuffer buffer ((unsigned char *)data.c_str(), data.length());
    	generateSigFile(buffer, signedFileFlash);

        File::copyFile(signedFileFlash, signedFileDom);
    }

    logger->Debug("Success persistence signed transmission package");
}

void MachineOperationManager::generateSigFile(SafeBuffer & buffer, std::string fileDestination)
    throw (Smartmatic::System::Exception::CryptoException,
        Smartmatic::System::Exception::SignedException,
        Smartmatic::System::Exception::XmlException,
        Smartmatic::System::Exception::SignByCardIDException)
{
    logger->Debug("Start generate signed file " + fileDestination);

    EIDManager::stop();

    if(!EIDManager::isReaderPresent() || !EIDManager::isCardPresent())
    {
    	EIDManager::stop();
        throw Smartmatic::System::Exception::SignByCardIDException(_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardDetectionException"), N_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardDetectionException"), logger, EIDManager::EIDMANAGER_FAILD);
    }

    Smartmatic::System::SafeBuffer safeBuf;
    bool sign = EIDManager::signPKCS11( buffer, safeBuf );
	EIDManager::stop();

    if(!sign)
    {
        throw Smartmatic::System::Exception::SignByCardIDException(_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardSignatureOperationException"), N_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardSignatureOperationException"), logger, EIDManager::EIDMANAGER_SIGNATURE_FAILED);
    }
    else
    {
        Smartmatic::System::SafeBuffer cryptoBuf;
        Smartmatic::SAES::Security::Encryption::getInstance()->cryptoBufferToBuffer(safeBuf, cryptoBuf, Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE);

        if (!Smartmatic::System::IO::File::saveBufferToFile(cryptoBuf, fileDestination))
        {
        	throw Smartmatic::System::Exception::SignByCardIDException(_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardSignatureCannotOpenFileException"), N_("Smartmatic.SAES.Operation.MachineOperationManager.IDCardSignatureCannotOpenFileException"), logger);
        }
    }

    logger->Debug("Success generate signed file " + fileDestination);
}

void MachineOperationManager::closeVotingExperience()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.StartingCloseVotingExperience"));
    logger->Debug("Start close voting experience");

    Glib::TimeVal now;
	now.assign_current_time();

	operationStatus->getElectionStatusWrapper()->setCloseVotingDate(now.as_iso8601());
	operationStatus->getElectionStatusWrapper()->setEletionState(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED);
    
    getOperationStatus()->persistElectionStatus();

    logger->Debug("Success close voting experience");
    logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.VotingExperienceClosed"));
}

bool MachineOperationManager::isNotInstalled()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINSTALLED;
}

bool MachineOperationManager::isNotPollworkerRegistered()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTPOLLWORKERREGISTERED;
}

bool MachineOperationManager::isNotDemostrationVote()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE;
}

bool MachineOperationManager::isOpenElection()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED;
}

bool MachineOperationManager::votingIsPossible()
{
	ElectionStatusWrapper * status = operationStatus->getElectionStatusWrapper();

	bool validate = true;

	std::stringstream ss;
	ss << "Current election state is " << status->getEletionState();

	logger->Debug(ss.str());

	validate = 	status->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE ||
				status->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED ||
				status->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED ||
				status->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED ||
				status->getEletionState() == Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED;

    return validate;
}

bool MachineOperationManager::isNotInitiatedElection()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED;
}

bool MachineOperationManager::isCloseElection()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED;
}

bool MachineOperationManager::isCloseVotingExperience()
{
    return operationStatus->getElectionStatusWrapper()->getEletionState() ==
    		Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED;
}

bool MachineOperationManager::isPrintingInstallReport()
{
	bool isPrinting = false;

	if (SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getPrintInstallationReportPM())
	{
		try
		{
			getOperationStatus()->InitializeElectionStatus();
			isPrinting = getOperationStatus()->getElectionStatusWrapper()->getElectionConfigurationReportPrinted();
		}
		catch (...)
		{
			logger->Debug("ERRRO - read electoral configuration");
		}
	}

	return isPrinting;
}

void MachineOperationManager::setOpeningCode(std::string & openingCode)
{
	if (!openingCode.empty())
	{
		logger->Debug("Start contingency mode - opening code " + openingCode);

		getOperationStatus()->InitializeElectionStatus();
		getOperationStatus()->getElectionStatusWrapper()->setOpeningCode(openingCode);
		getOperationStatus()->getElectionStatusWrapper()->setContingencyCardCreated(true);
		loadOpeninCode = false;
		machineInitiator->setMode(Initiator::IMachineInitiator::CONTINGENCY_MODE);
	}
}

MachineOperationManager::VoteFromSafeBufferResult MachineOperationManager::getVoteFromSafeBuffer(Smartmatic::System::SafeBuffer& safeBuffer, Smartmatic::SAES::Voting::Vote::Vote *& vote, bool inflate)
{
	Glib::Mutex::Lock lock(mutexVote);

	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.GettingVoteFromSafeBuffer"));
	logger->Debug("Start vote from safe buffer");

	vote = NULL;

	MachineOperationManager::VoteFromSafeBufferResult result = MachineOperationManager::VOTE_FROM_BUFFER_SUCCESS;
	try
	{
		Smartmatic::SAES::Voting::Vote::Vote voteTmp;
		if(Vote::VoteWrapper::unpackVoteFromQR(electoralConfiguration, safeBuffer, voteTmp, inflate))
		{
			vote = new Smartmatic::SAES::Voting::Vote::Vote( voteTmp);
			Smartmatic::SAES::Voting::VotingDevice::Voting_device  vd = MachineOperationManager::getInstance()->getElectoralConfiguration ()->getVotingDevice ()->getFirstVotingDevice ();

			if(!Vote::VoteWrapper::validateLogicalVoterGroupVote(electoralConfiguration, *vote))
			{
				logger->Debug("Error logical voter group of vote");
				logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorLogicalVoterGroupInVote"));
				result = MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG;
			}
			else if(!Vote::VoteWrapper::validateVotingDeviceCodeVote(electoralConfiguration, *vote))
			{
				logger->Debug("Error voting device code of vote");
				logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVotingDeviceInVote"));
				result = MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE;
			}
			else if(!Vote::VoteWrapper::validateVoteCode(*vote))
			{
				logger->Debug("Error code of vote");
				logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteCode"));
				result = MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE;
			}
		}
		else
		{
			result = MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR;
			logger->Debug("Error Buffer decompression");
			logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorUnpackVote"));
		}

	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR;
		std::stringstream ss;
		ss << __func__ << " " << e;
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}
	catch(Smartmatic::System::Exception::SignedException& ex)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR;
		std::stringstream ss;
		ss << __func__ << " " << ex.what();
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}
	catch(Smartmatic::System::Exception::CryptoException& cex)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR;
		std::stringstream ss;
		ss << __func__ << " " << cex.what();
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}
	catch(Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteInvalidFormatException& cex)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR;
		std::stringstream ss;
		ss << __func__ << " " << cex.what();
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}
	catch(Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteSignatureException& cex)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR;
		std::stringstream ss;
		ss << __func__ << " " << cex.what();
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}
	catch(...)
	{
		result = MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR;
		std::stringstream ss;
		ss << __func__;
		logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ErrorVoteData"));
	}

	logger->Debug("End vote from safe buffer");
	return result;
}

void MachineOperationManager::saveElectoralConfigurationReportPrinted()
{
    try
    {
    	operationStatus->getElectionStatusWrapper()->setElectionConfigurationReportPrinted(true);
        logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ElectoralConfigurationReportPrinted"));
        getOperationStatus()->persistElectionStatus();
    }
    catch(...)
    {
        logger->Debug("Error save electoral configuration report printed");
    }
}

void MachineOperationManager::saveElectoralConfigurationContingencyCardCreated()
{
	try
	{
		getOperationStatus()->getElectionStatusWrapper()->setContingencyCardCreated(true);
		getOperationStatus()->persistElectionStatus();

		logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.ContingencyCardCreated"));
	}
	catch(...)
	{
		logger->Debug("FATAL - Error persistence election status");
	}
}

void MachineOperationManager::deleteCloseFiles()
{
    Smartmatic::SAES::Voting::Vote::TransmissionPackageWrapper::getInstance()->deleteFiles();
    Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->deleteFiles();

    std::string sigDom = saesDirectories->getElectionResultSignatureFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string sigFlash = saesDirectories->getElectionResultSignatureFileFullPath(BasePathType::CONFIGURATION_FLASH);

    Smartmatic::System::IO::File::DeleteFile(sigDom);
    Smartmatic::System::IO::File::DeleteFile(sigFlash);
}

void MachineOperationManager::SetBlockMemoryBehavior(MemoryBehavior behavior)
{
	this->behavior = behavior;
}

LogBasePath * MachineOperationManager::getLogBasePathDom()
{
	return basePathDom;
}

LogBasePath * MachineOperationManager::getLogBasePathFlash()
{
	return basePathFlash;
}

void MachineOperationManager::saveVoteInOneMemory()
	throw (Smartmatic::System::Exception::CryptoException,
			Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::XmlException)
{
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SaveVoteInOneMemory"));
	operationStatus->getElectionStatusWrapper()->setSynchronizeVotes(true);
	getOperationStatus()->persistElectionStatus(true, false);
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.SaveVoteInOneMemorySuccess"));
}

void MachineOperationManager::restoreVoteInAllMemory()
	throw (Smartmatic::System::Exception::CryptoException,
			Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::XmlException)
{
	operationStatus->getElectionStatusWrapper()->setSynchronizeVotes(false);
	getOperationStatus()->persistElectionStatus();
	logger->Audit(N_("Smartmatic.SAES.Operation.MachineOperationManager.RestoreVoteInAllMemorySuccess"));
}

void MachineOperationManager::setMemoryEvent(MachineOperationManager::MemoryEvent memoryEvent)
{
	if (!handleDetection)
	{
		return;
	}

	std::stringstream ss;
	ss << "Emit signal ";

	switch(memoryEvent)
	{
		case MachineOperationManager::ONE_MEMORY:
			ss << "ONE_MEMORY";
			break;
		case MachineOperationManager::TWO_MEMORY:
			ss << "TWO_MEMORY";
			break;
		case MachineOperationManager::CHECK_MEMORY_OK:
			ss << "CHECK_MEMORY_OK";
			break;
		case MachineOperationManager::CHECK_MEMORY_ERROR:
			StopDetection();
			ss << "CHECK_MEMORY_ERROR";
			break;
		case MachineOperationManager::ERROR_MEMORY:
			StopDetection();
			ss << "ERROR_MEMORY";
			break;
	}

	logger->Debug(ss.str());

	signalMemoryEvent.emit(memoryEvent, behavior);
}

IDCardInfoWrapper * MachineOperationManager::getIDCardInfoWrapper()
{
	return this->idCardInfoWrapper;
}

void MachineOperationManager::exitMachine()
{
	(void) signal(SIGUSR2, SIG_DFL);
	(void) signal(SIGSEGV, SIG_DFL);
	(void) signal(SIGABRT, SIG_DFL);

	Smartmatic::SAES::EID::EIDManager::release();
	exit(EXIT_FAILURE);
}
