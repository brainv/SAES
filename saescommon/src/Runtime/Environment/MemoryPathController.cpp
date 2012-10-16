/*
 * MemoryPathController.cpp
 *
 *  Created on: May 18, 2011
 *      Author: freddy
 */

#include "MemoryPathController.h"
#include "MasterMemoryParser.h"
#include "MemoryEventParser.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <fstream>
#include <sys/mount.h>

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;

MemoryPathController* MemoryPathController::instance = NULL;

MemoryPathController::MemoryPathController()
{
    ConfigurationElectionFilesPath & configElectionFiles ((*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationElectionFilesPath());
    OSConfigurationFiles & osConf (SAESCommonConfigurationManager::Current()->getOSConfigurationFiles());
    ConfigurationBasePath configBasePath = configElectionFiles.getConfigBasePath();

    masterDeviceFileFullPath = osConf.getMasterDeviceFileFullPath();
    eventDeviceFileFullPath = osConf.getEventDeviceFileFullPath();

    rule = configBasePath.getRulesBasePath();
    liveFileSystemBasePath = configBasePath.getLiveFileSystemBasePath();
}

MemoryPathController::~MemoryPathController()
{

}

std::string& MemoryPathController::getStartupMemoryBasePath()
{
	Glib::Mutex::Lock lock(mutex);
	return startupMemoryBasePath; ///< path of the startup memory
}

std::string& MemoryPathController::getLiveFileSystemBasePath()
{
	Glib::Mutex::Lock lock(mutex);
	return liveFileSystemBasePath; ///< path of the live folder
}

std::string& MemoryPathController::getDomMemoryBasePath()
{
	Glib::Mutex::Lock lock(mutex);
	return domMemoryBasePath; ///< path of the DOM memory
}

std::string& MemoryPathController::getFlashMemoryBasePath()
{
	Glib::Mutex::Lock lock(mutex);
	return flashMemoryBasePath;///< path of the Flash Memory
}

std::string& MemoryPathController::getBackupMemoryBasePath()
{
	Glib::Mutex::Lock lock(mutex);
	return backupMemoryBasePath;
}

void MemoryPathController::updatePaths()
{
	Glib::Mutex::Lock lock(mutex);
    domMemoryBasePath.clear();
    flashMemoryBasePath.clear();
    backupMemoryBasePath.clear();

    readMasterDevice(masterDeviceFileFullPath);
    readEventDevice(eventDeviceFileFullPath);

    switch(rule)
    {
        case RulesBasePathType::CONFIGURATION_PM_RULE:
            break;

        case RulesBasePathType::CONFIGURATION_VM_RULE:
            backupMemoryBasePath = domMemoryBasePath;
            domMemoryBasePath = liveFileSystemBasePath;
            break;
    }
}

bool MemoryPathController::umountDevice( std::string device )
{
	bool validate = false;

	if (!device.empty())
	{
		int result = umount2( device.c_str(), MNT_FORCE);
		validate = result == 0;
	}

	return validate;
}

void MemoryPathController::readMasterDevice(std::string file)
{
    if (File::canOpenFile(file))
    {
        MasterMemoryParser parser;

        if (parser.Load(file))
        {
        	startupMemoryBasePath = parser.getMemoryInfo().getPath();
        }
    }
}

void MemoryPathController::readEventDevice(std::string file)
{
    if (File::canOpenFile(file))
    {
        OSConfigurationFiles & osConf (SAESCommonConfigurationManager::Current()->getOSConfigurationFiles());
        bool removeEventFile = osConf.getRemoveEventDeviceFile();

        MemoryEventParser parser;
        parser.Load(file);

        std::vector <MemoryInfo> & listUmount (parser.getUmountedMemories());
        std::vector <MemoryInfo> & listMount (parser.getMountedMemories());
        std::vector <MemoryInfo>::iterator it;

        for (it = listUmount.begin();
             it != listUmount.end();
             it++)
        {
            MemoryInfo info = (*it);
            umountDevice(info.getDevice());
        }

        int count = 0;

        for (it = listMount.begin();
             it != listMount.end();
             it++)
        {
            MemoryInfo info = (*it);

			if (Directory::DirectoryExists(info.getPath()))
			{
				switch(count)
				{
				case 0:
					domMemoryBasePath = info.getPath();
					break;

				case 1:
					flashMemoryBasePath = info.getPath();
					break;

				case 2:
					backupMemoryBasePath = info.getPath();
					break;
				}

				count++;
			}
        }

        if (removeEventFile)
        {
            File::DeleteFile(file);
        }
    }
}

RulesBasePathType & MemoryPathController::getRule()
{
	return rule;
}

bool MemoryPathController::isAllDevices()
{
	bool result = true;

	switch(rule)
	{
		case RulesBasePathType::CONFIGURATION_PM_RULE:

			result = Directory::DirectoryExists(domMemoryBasePath) && Directory::DirectoryExists(flashMemoryBasePath);
			break;

		case RulesBasePathType::CONFIGURATION_VM_RULE:

			result = Directory::DirectoryExists(liveFileSystemBasePath);
			break;
	}

    return result;
}

MemoryPathController * MemoryPathController::getInstance()
{
	if(MemoryPathController::instance == NULL)
		MemoryPathController::instance = new MemoryPathController();

	return MemoryPathController::instance;
}
