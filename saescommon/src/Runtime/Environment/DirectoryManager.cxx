/**
 * @file DirectoryManager.cxx
 * @brief Class for manager directory and files to backup
 */

#include "DirectoryManager.hxx"
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <System/guid-class.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <Security/Encryption.hxx>
#include <Log/SMTTLogManager.h>
#include <System/Runtime/ProcessLauncher.h>
#include "Configuration/s-a-e-s-common-conf-manager.h"

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

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Runtime;

ISMTTLog* DirectoryManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Runtime.Environment.DirectoryManager",GETTEXT_PACKAGE);

DirectoryManager::DirectoryManager( Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories )
{
    this->directories = directories;
}

DirectoryManager::~DirectoryManager()
{

}

bool DirectoryManager::backup (bool copyDomToFlash)
{
    std::string languageImageDirectory = directories.getLanguageImageInstalationDirectoryFullPath();
    std::string languageImageDirectoryLocal = directories.getLanguageImageDirectoryFullPath();

    std::string caCertified = directories.getCACertificateInstalationFileFullPath();
    std::string caCertifiedLocal = directories.getCACertificateFileFullPath();

    std::string itermediateCACertificates = directories.getItermediateCACertificatesInstalationFileFullPath();
    std::string itermediateCACertificatesLocal = directories.getItermediateCACertificatesFileFullPath();

    std::string trustedCertificates = directories.getTrustedCertificatesInstalationFileFullPath();
    std::string trustedCertificatesLocal = directories.getTrustedCertificatesFileFullPath();

    bool success = true;

    if (Smartmatic::System::IO::Directory::DirectoryExists(languageImageDirectory))
    {
    	success = copyDir ( languageImageDirectory, languageImageDirectoryLocal ) && success;
    }

    if (Smartmatic::System::IO::File::canOpenFile(caCertified))
    {
        success = Smartmatic::System::IO::File::copyFile(caCertified, caCertifiedLocal) && success;
    }

    if (Smartmatic::System::IO::File::canOpenFile(itermediateCACertificates))
    {
        success = Smartmatic::System::IO::File::copyFile(itermediateCACertificates, itermediateCACertificatesLocal) && success;
    }

    if (Smartmatic::System::IO::File::canOpenFile(trustedCertificates))
    {
        success = Smartmatic::System::IO::File::copyFile(trustedCertificates, trustedCertificatesLocal) && success;
    }

    std::string masterDir = directories.getBasePath ( BasePathType::CONFIGURATION_DOM );
    std::string backupDir = directories.getBasePath ( BasePathType::CONFIGURATION_FLASH );

    if (copyDomToFlash)
    {
    	success = copyDir ( masterDir, backupDir ) && success;
    }
    else
    {
    	success = copyDir ( backupDir, masterDir ) && success;
    }

    return success;
}

bool DirectoryManager::copyDir ( std::string origDir, std::string destDir )
{
    std::string command = "rm -f -R " + destDir;
    int result = ProcessLauncher::RunProcessThroughSystem(command.c_str());

    if (result != 0)
    {
        return false;
    }

    command = "mkdir -p " + destDir;
    result = ProcessLauncher::RunProcessThroughSystem(command.c_str());

    if (result != 0)
    {
        return false;
    }

    command = "cp -R " + Smartmatic::System::IO::Path::Combine( origDir, "*" ) + " " + destDir;
    result = ProcessLauncher::RunProcessThroughSystem(command.c_str());

    if (result != 0)
    {
    	return false;
    }

    command = "chmod 777 -R " + origDir;
    result = ProcessLauncher::RunProcessThroughSystem(command.c_str());

    if (result != 0)
    {
    	return false;
    }

    command = "chmod 777 -R " + destDir;
    result = ProcessLauncher::RunProcessThroughSystem(command.c_str());

    return result == 0;
}

void DirectoryManager::createMachineIdFile(std::string machineId, bool force)
{
    std::string machineIdPath = directories.getBackupFileFullPath ( BasePathType::CONFIGURATION_DOM );
    std::string machineIdFlashPath = directories.getBackupFileFullPath ( BasePathType::CONFIGURATION_FLASH );

    if (!Smartmatic::System::IO::File::canOpenFile(machineIdPath) || force)
    {
        try
        {
            Encryption::getInstance()->cryptoStringToFile(machineId, machineIdPath, Encryption::INTERNAL_FILE);
        }
        catch(CryptoException & ex)
        {
            std::stringstream ss;
            ss << __func__ << " - ERROR " << machineIdPath <<" "<< ex.what();
            logger->Debug(ss.str());
        }
    }

    if (force)
    {
        try
        {
            Encryption::getInstance()->cryptoStringToFile(machineId, machineIdFlashPath, Encryption::INTERNAL_FILE);
        }
        catch(CryptoException & ex)
        {
            std::stringstream ss;
            ss << __func__ << " - ERROR " << machineIdFlashPath <<" "<< ex.what();
            logger->Debug(ss.str());
        }
    }
}

bool DirectoryManager::validateMachineIdFile(std::string machineId)
{
	std::string machineIdFilePath = directories.getBackupFileFullPath ( BasePathType::CONFIGURATION_DOM );
	std::string machineIdData;
	bool validate = false;

	try
	{
	    Encryption::getInstance()->decryptoFileToString(machineIdFilePath, machineIdData,
                        Encryption::INTERNAL_FILE);
	    validate = machineIdData == machineId;
	}
	catch(CryptoException & ex)
	{
	    std::stringstream ss;
		ss << __func__ << " - ERROR " << machineIdFilePath <<" "<< ex.what();
		logger->Debug(ss.str());
	}

	return validate;
}


bool DirectoryManager::validateMachineIdFileDOMFlash ()
{
    std::string backupFileM = directories.getBackupFileFullPath ( BasePathType::CONFIGURATION_DOM );
    std::string backupFileB = directories.getBackupFileFullPath ( BasePathType::CONFIGURATION_FLASH );

    bool validate = Smartmatic::System::IO::File::compareFiles(backupFileM, backupFileB);

    if (!validate)
    {
        logger->Debug("MachineId file Faild");
    }
    else
    {
        logger->Debug("MachineId file Ok");
    }

    return validate;
}
