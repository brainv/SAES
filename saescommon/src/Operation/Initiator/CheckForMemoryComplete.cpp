/**
 * @file CheckForMemoryComplete.cpp
 * @brief Body class check for memory complete
 * @date 23/05/2011
 * @author Yadickson Soto
 */

#include "CheckForMemoryComplete.h"
#include <System/IO/File.h>
#include <Runtime/Environment/saes-directories.h>
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

using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::Log;

ISMTTLog* CheckForMemoryCompleteCondition::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.CheckForMemoryCompleteCondition",GETTEXT_PACKAGE);

CheckForMemoryCompleteCondition::CheckForMemoryCompleteCondition(
        Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories,
        Smartmatic::SAES::Common::Configuration::BasePathType type) :
            ICheckCondition(
                    TestStatus::MemoryComplete,
                    N_("Smartmatic.SAES.Operation.Initiator.CheckForMemoryCompleteCondition.CheckingMemoryCompleteCondition"),
                    "ui/check-memory-full.gif",
                    "ui/check-memory-full-failed.gif")
{
    this->directories = directories;
    this->type = type;
}

CheckForMemoryCompleteCondition::~CheckForMemoryCompleteCondition()
{

}

TestStatus::Tests CheckForMemoryCompleteCondition::check()
{
    SaesDirectories directories;

    bool checkElectionStatusFile = File::canOpenFile(directories.getElectionStatusFileFullPath(type));
    bool checkVMStatusFile = File::canOpenFile(directories.getVotingMachineStatusFileFullPath(type));
    bool checkAssistedActivationFile = File::canOpenFile(directories.getAssistedActivationFileFullPath(type));
    bool checkVotingDisabledFile = File::canOpenFile(directories.getVotingDisabledFileFullPath(type));
    bool checkActivatedCardStatisticFile = File::canOpenFile(directories.getActivatedCardStatisticsFileFullPath(type));
    bool checkIncidentReportFile = File::canOpenFile(directories.getIncidentReportFileFullPath(type));
    bool checkPollworkerFile = File::canOpenFile(directories.getPollworkersFileFullPath(type));
    bool checkStatisticFile = File::canOpenFile(directories.getStatisticsFileFullPath(type));
    bool checkClosingNoteFile = File::canOpenFile(directories.getClosingNotesFileFullPath(type));
    bool checkMachineId = File::canOpenFile(directories.getBackupFileFullPath(type));
    bool checkIdCardMembers = File::canOpenFile(directories.getIDCardMembersFileFullPath(type));
    bool checkPoliceNotesFile = File::canOpenFile(directories.getPoliceNotesFileFullPath(type));

    logger->Debug("checkElectionStatusFile " + std::string(checkElectionStatusFile ? "success":"fail") + " in " + type);
    logger->Debug("checkVMStatusFile " + std::string(checkVMStatusFile ? "success":"fail") + " in " + type);
    logger->Debug("checkAssistedActivationFile " + std::string(checkAssistedActivationFile ? "success":"fail") + " in " + type);
    logger->Debug("checkVotingDisabledFile " + std::string(checkVotingDisabledFile ? "success":"fail") + " in " + type);
    logger->Debug("checkActivatedCardStatisticFile " + std::string(checkActivatedCardStatisticFile ? "success":"fail") + " in " + type);
    logger->Debug("checkIncidentReportFile " + std::string(checkIncidentReportFile ? "success":"fail") + " in " + type);
    logger->Debug("checkPollworkerFile " + std::string(checkPollworkerFile ? "success":"fail") + " in " + type);
    logger->Debug("checkStatisticFile " + std::string(checkStatisticFile ? "success":"fail") + " in " + type);
    logger->Debug("checkClosingNoteFile " + std::string(checkClosingNoteFile ? "success":"fail") + " in " + type);
    logger->Debug("checkMachineId " + std::string(checkMachineId ? "success":"fail") + " in " + type);
    logger->Debug("checkIdCardMembers " + std::string(checkIdCardMembers ? "success":"fail") + " in " + type);
    logger->Debug("checkPoliceNotesFile " + std::string(checkPoliceNotesFile ? "success":"fail") + " in " + type);

    bool validate = checkElectionStatusFile &&
       checkVMStatusFile &&
       checkAssistedActivationFile &&
       checkVotingDisabledFile &&
       checkActivatedCardStatisticFile &&
       checkIncidentReportFile &&
       checkPollworkerFile &&
       checkStatisticFile &&
       checkClosingNoteFile &&
       checkMachineId &&
       checkIdCardMembers &&
       checkPoliceNotesFile;

    return validate ? TestStatus::Passed : TestStatus::Failed;
}
