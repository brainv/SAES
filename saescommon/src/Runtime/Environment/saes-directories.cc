/**
 * @file saes-directories.cc
 * @brief Body class saes directories
 *
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * saescommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saescommon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Runtime/Environment/saes-directories.h"
#include "Runtime/Environment/MemoryPathController.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>

#include <System/IO/Path.h>
#include <System/IO/Directory.h>
#include <giomm/file.h>
#include <stdio.h>

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;

std::string SaesDirectories::getDevicePath ( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    std::string devicePath;

    switch( type )
    {
        case BasePathType::CONFIGURATION_DOM:
        	devicePath = getDOMMemoryBasePath();
            break;

        case BasePathType::CONFIGURATION_FLASH:
        	devicePath = getFlashMemoryBasePath();
            break;

        case BasePathType::CONFIGURATION_BACKUP:
        	devicePath = MemoryPathController::getInstance()->getBackupMemoryBasePath();
            break;
    }

    return devicePath;
}

std::string SaesDirectories::getBasePath ( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine(getDevicePath(type), getWorkingDirectoryFolderName());
}

std::string SaesDirectories::getLocalBasePath ( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine(getDevicePath(type), workingDirectory);
}

std::string SaesDirectories::getWorkingDirectoryFolderName()
{
    return workingDirectory;
}

std::string SaesDirectories::getDOMMemoryBasePath()
{
    return MemoryPathController::getInstance()->getDomMemoryBasePath();
}

std::string SaesDirectories::getFlashMemoryBasePath()
{
    return MemoryPathController::getInstance()->getFlashMemoryBasePath();
}

std::string SaesDirectories::getElectionFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),ElectionFileName) ;
}

std::string SaesDirectories::getElectionStatusFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),ElectionStatusFileName) ;
}

std::string SaesDirectories::getIDCardMembersFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),IDCardMembersFileName) ;
}

std::string SaesDirectories::getCardListStatusFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),CardListStatusFileName) ;
}

std::string SaesDirectories::getVotingMachineStatusFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),VotingMachineStatusFileName) ;
}

std::string SaesDirectories::getVotingCentersLocalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine ( getBasePath( type ), votingCentersFileName );
}

std::string SaesDirectories::getVotingCentersInstalationFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine ( getBaseInstallationPath(type), votingCentersFileName );
}

std::string SaesDirectories::getPollworkersFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),PollworkersFileName) ;
}

std::string SaesDirectories::getStatisticsFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),StatisticsFileName) ;
}

std::string SaesDirectories::getActivatedCardStatisticsFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),ActivatedCardStatisticsFileName) ;
}

std::string SaesDirectories::getAssistedActivationFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),AssistedActivationFileName) ;
}

std::string SaesDirectories::getVotingDisabledFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),VotingDisabledFileName) ;
}

std::string SaesDirectories::getPoliceNotesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),PoliceNotesFileName) ;
}

std::string SaesDirectories::getClosingNotesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),ClosingNotesFileName) ;
}

std::string SaesDirectories::getXMLImageFileName()
{
	return XMLImageFileName;
}

std::string SaesDirectories::getIncidentReportFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),IncidentReportFileName) ;
}

std::string SaesDirectories::getElectionResourcesFileName()
{
	return ElectionResourcesFileName ;
}

std::string SaesDirectories::getVotingDeviceFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),VotingDeviceFileName) ;
}

std::string SaesDirectories::getElectoralResourceFullFolderPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine(getSaesDataFolderFullPath ( type ),ElectoralResourcesFolderName) ;
}

std::string SaesDirectories::getElectoralResourcesFolderName()
{
    return ElectoralResourcesFolderName;
}

std::string SaesDirectories::getElectoralImagesFullFolderPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine(getSaesDataFolderFullPath ( type ),ElectoralImageFolderName) ;
}

std::string SaesDirectories::getLocalElectoralImagesFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getLocalSaesDataFolderFullPath(type), ElectoralImageFolderName);
}

std::string SaesDirectories::getImageElectoralResource(std::string imageName)
{
//get images resources
    return Path::Combine(getElectoralImagesFullFolderPath() , imageName) ;
}

std::string SaesDirectories::getElectoralSAESFullFolderPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine( getBasePath ( type ) ,SaesDataFolderName) ;
}

std::string SaesDirectories::getTemporalFilesFolderFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine( getBasePath ( type ) ,TemporalFilesFolderName) ;
}

std::string SaesDirectories::getBaseInstallationPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getDevicePath(type), projectName);
}

std::string SaesDirectories::getTemporalFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	//TODO: make sure filename is unique
	std::string filename = tmpnam(NULL);
        return Path::Combine(getTemporalFilesFolderFullPath( type ), Path::GetFileName(filename) ) ;
}

std::string SaesDirectories::getLanguageInstalationFileFullPath ()
{
	return Path::Combine( getBaseInstallationPath(), languageFileName ) ;
}

std::string SaesDirectories::getLanguageLocalFileFullPath ( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getBasePath ( type ), languageFileName ) ;
}

std::string SaesDirectories::getSaesDataFolderName()
{
	return SaesDataFolderName;
}

std::string SaesDirectories::getSaesDataFolderFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine( getBasePath ( type ), SaesDataFolderName );
}

std::string SaesDirectories::getLocalSaesDataFolderFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
        return Path::Combine( getLocalBasePath ( type ), SaesDataFolderName );
}

std::string SaesDirectories::getLanguageImageInstalationDirectoryFullPath ()
{
    return Path::Combine( getBaseInstallationPath(), languageImageDirectory ) ;
}

std::string SaesDirectories::getLanguageImageDirectoryFullPath ( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getBasePath ( type ), languageImageDirectory );
}

std::string SaesDirectories::getBackupFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getBasePath ( type ), backupFileName );
}

std::string SaesDirectories::getSecretKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getBasePath ( type ), secretKeyFileName );
}

std::string SaesDirectories::getUPKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getBasePath ( type ), upKeyFileName );
}

std::string SaesDirectories::getX7SSignedKeyCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), X7SSignedKeyCertifiedFileName );
}

std::string SaesDirectories::getX7SSignedCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), X7SSignedCertifiedFileName );
}

std::string SaesDirectories::getX7SCryptoCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), X7SCryptoCertifiedFileName );
}

std::string SaesDirectories::getMachineKeysFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), machineKeysFileName );
}

std::string SaesDirectories::getProjectName()
{
	return projectName;
}

std::string SaesDirectories::getIdHardwareFileFullPath()
{
	return IdHardwareFileFullPath;
}

std::string SaesDirectories::getVotingExperienceValidationFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getDevicePath(type),votingExperienceValidationFolderName);
}

std::string SaesDirectories::getVotesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), VotesFolder);
}

std::string SaesDirectories::getDocsFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), DocsFolder);
}

std::string SaesDirectories::getCodiFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), CodiFolder);
}

std::string SaesDirectories::getPVFormFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), PVFormFileName);
}

std::string SaesDirectories::getPVFormTestFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), "PVTest.xml");
}

std::string SaesDirectories::getTransmissionPackagesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), TransmissionPackageFileName);
}

std::string SaesDirectories::getTransmissionPackagesKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), TransmissionPackageKeyFileName);
}

std::string SaesDirectories::getTransmissionPackagesCrtFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath( type ), TransmissionPackageCrtFileName);
}

std::string SaesDirectories::getTransmissionPackagesHashFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), TransmissionPackageHashFileName);
}

std::string SaesDirectories::getTransmissionPackageSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getDocsFolderFullPath ( type ), TransmissionPackageSignatureFileName);
}

std::string SaesDirectories::getPVFormSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getDocsFolderFullPath ( type ), PVFormSignatureFileName);
}

std::string SaesDirectories::getCACertificateFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), CACertificateFileName);
}
std::string SaesDirectories::getItermediateCACertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), ItermediateCACertificatesFileName);
}
std::string SaesDirectories::getTrustedCertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine( getSaesDataFolderFullPath ( type ), TrustedCertificatesFileName);
}

std::string SaesDirectories::getCACertificateInstalationFileFullPath()
{
    return Path::Combine ( getBaseInstallationPath(), CACertificateFileName );
}
std::string SaesDirectories::getItermediateCACertificatesInstalationFileFullPath()
{
    return Path::Combine ( getBaseInstallationPath(), ItermediateCACertificatesFileName );
}
std::string SaesDirectories::getTrustedCertificatesInstalationFileFullPath()
{
    return Path::Combine ( getBaseInstallationPath(), TrustedCertificatesFileName );
}

std::string SaesDirectories::getPVTemplateFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine( getSaesDataFolderFullPath ( type ), PVTemplateFolder);
}

std::string SaesDirectories::getGlobalPVTemplateFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine( getPVTemplateFolderFullPath ( type ), PVTemplateFileName);
}

std::string SaesDirectories::getTestPVTemplateFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine( getPVTemplateFolderFullPath ( type ), "PVTest.xslt");
}

std::string SaesDirectories::getGeneratedPVReportFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getDocsFolderFullPath ( type ), GeneratedPVReportFileName);
}

std::string SaesDirectories::getGeneratedPVReportTestFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine( getDocsFolderFullPath ( type ), "PVTest.pdf");
}

std::string SaesDirectories::getMasterDeviceFileFullPath()
{
    return MasterDeviceFileFullPath;
}

std::string SaesDirectories::getEventDeviceFileFullPath()
{
    return EventDeviceFileFullPath;
}
std::string SaesDirectories::getElectionResultSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
	return Path::Combine(getDocsFolderFullPath ( type ),ElectionResultSignatureFile);
}

std::string SaesDirectories::getLogFolderName()
{
    return logFolderName;
}

std::string SaesDirectories::getLogFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getSaesDataFolderFullPath(type), getLogFolderName());
}

std::string SaesDirectories::getLogErrorFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getLogFolderFullPath(type), logErrorFileName);
}

std::string SaesDirectories::getLogAuditFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getLogFolderFullPath(type), logAuditFileName);
}

std::string SaesDirectories::getVoteStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getSaesDataFolderFullPath(type),VoteStatisticsFileName);
}

std::string SaesDirectories::getSignatureResourceFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getSaesDataFolderFullPath ( type ),SignatureResourceFileName) ;
}

std::string SaesDirectories::getCodiFilesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    return Path::Combine(getDevicePath( type ), CodiFilesFolder) ;
}

SaesDirectories::SaesDirectories()
{
	ConfigurationElectionFilesPath & configElectionFiles ((*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationElectionFilesPath());

	ConfigurationBasePath configBasePath = configElectionFiles.getConfigBasePath();

	workingDirectory = configBasePath.getWorkingDirectory();
	languageImageDirectory = configBasePath.getLanguageImageDirectory();
	backupFileName = configBasePath.getBackupFileName();
	projectName = configBasePath.getProjectName();
	votingExperienceValidationFolderName = configBasePath.getVotingExperienceValidationScreensDirectory();
	languageFileName = configElectionFiles.getLanguageFileName();
	votingCentersFileName = configElectionFiles.getVotingCentersFileName();
	SaesDataFolderName=configElectionFiles.getSAESFolder();
	ElectoralResourcesFolderName = configElectionFiles.getResourcesFolder();
	ElectoralImageFolderName = configElectionFiles.getImagesFolder();
	LiveFileSystem = configElectionFiles.getConfigBasePath().getLiveFileSystemBasePath();
	CodiFilesFolder = configElectionFiles.getCodiFilesFolder();

	VotesFolder = configElectionFiles.getVotesFolder();
	DocsFolder = configElectionFiles.getDocsFolder();
	CodiFolder = configElectionFiles.getCodiFolder();
	TransmissionPackageFileName = configElectionFiles.getTransmissionPackageFileName();
	TransmissionPackageHashFileName = configElectionFiles.getTransmissionPackageHashFileName();
	TransmissionPackageKeyFileName = configElectionFiles.getTransmissionPackageKeyFileName();
	TransmissionPackageCrtFileName = configElectionFiles.getTransmissionPackageCrtFileName();

	PVFormFileName = configElectionFiles.getPVFormFileName();
	TransmissionPackageSignatureFileName = configElectionFiles.getTransmissionPackageSignatureFileName();
	ElectionFileName=configElectionFiles.getElectionFileName();
	PollworkersFileName = configElectionFiles.getPollworkersFileName();
	StatisticsFileName = configElectionFiles.getStatisticsFileName();
	ActivatedCardStatisticsFileName = configElectionFiles.getActivatedCardStatisticsFileName();
	AssistedActivationFileName = configElectionFiles.getAssistedActivationFileName();
	VotingDisabledFileName = configElectionFiles.getVotingDisabledFileName();
	PoliceNotesFileName = configElectionFiles.getPoliceNotesFileName();
	IncidentReportFileName = configElectionFiles.getIncidentReportFileName();
	ClosingNotesFileName = configElectionFiles.getClosingNotesFileName();
	XMLImageFileName = configElectionFiles.getXMLImageFileName();
    ElectionStatusFileName=configElectionFiles.getElectionStatusFileName();
	CardListStatusFileName=configElectionFiles.getCardListStatusFileName();
	ElectionResourcesFileName = configElectionFiles.getElectionResourcesFileName();
	IDCardMembersFileName = configElectionFiles.getIDCardMembersFileName();
	CACertificateFileName=configElectionFiles.getCACertificateFileName();
	ItermediateCACertificatesFileName=configElectionFiles.getItermediateCACertificatesFileName();
	TrustedCertificatesFileName=configElectionFiles.getTrustedCertificatesFileName();
	PVFormSignatureFileName=configElectionFiles.getPVFormSignatureFileName();
	VoteStatisticsFileName = configElectionFiles.getVoteStatisticsFileName();
	SignatureResourceFileName = configElectionFiles.getSignatureResourceFileName();
	
	VotingMachineStatusFileName=configElectionFiles.getVotingMachineStatusFileName();
	VotingDeviceFileName=configElectionFiles.getVotingDeviceFileName();

	secretKeyFileName = configElectionFiles.getSecretKeyFile();
	upKeyFileName = configElectionFiles.getUPKeyFile();
	machineKeysFileName = configElectionFiles.getMachineKeysFile();

	OSConfigurationFiles & osConf (SAESCommonConfigurationManager::Current()->getOSConfigurationFiles());
	IdHardwareFileFullPath = osConf.getIdHardwareFileFullPath();
	MasterDeviceFileFullPath = osConf.getMasterDeviceFileFullPath();
	EventDeviceFileFullPath = osConf.getEventDeviceFileFullPath();

    logFolderName = configElectionFiles.getLogsFolderName();
    logErrorFileName = configElectionFiles.getLogErrorFileName();
    logAuditFileName = configElectionFiles.getLogAuditFileName();

    PVTemplateFileName = configElectionFiles.getPVTemplateFileName();	///< Filename of the nonlocalized PV template
	PVTemplateFolder = configElectionFiles.getPVTemplateFolderName(); ///< Pathname of the PVTemplate folder
	GeneratedPVReportFileName = configElectionFiles.getGeneratedPVReportFileName(); ///< Pathname of the PV report file
	ElectionResultSignatureFile = configElectionFiles.getElectionResultSignatureFileName();
	TemporalFilesFolderName = "Temp";

    X7SSignedKeyCertifiedFileName = (configElectionFiles.getX7SSignedKeyCertifiedFileName() != NULL ? configElectionFiles.getX7SSignedKeyCertifiedFileName().get(): "");
    X7SSignedCertifiedFileName = (configElectionFiles.getX7SSignedCertifiedFileName() != NULL ? configElectionFiles.getX7SSignedCertifiedFileName().get(): "");
    X7SCryptoCertifiedFileName = (configElectionFiles.getX7SCryptoCertifiedFileName() != NULL ? configElectionFiles.getX7SCryptoCertifiedFileName().get(): "");

    Smartmatic::System::IO::Directory::Mkdir(getTemporalFilesFolderFullPath());
	
}

SaesDirectories::~SaesDirectories()
{

}
