/**
 * @file	DirectoryManager.hxx
 *
 * @brief	directory manager class.
 */

#ifndef __DIRECTORY_MANAGER_H__
#define __DIRECTORY_MANAGER_H__

#include "saes-directories.h"
#include <iostream>
#include <Log/ISMTTLog.h>
#include <Security/Encryption.hxx>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
                /**
                 * @class DirectoryManager
                 * @brief Class manager directory and files to backup
                 * @since 15-03-2011
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 */
                class DirectoryManager
                {
                public:
                    /**
                     * @brief Class constructor
                     * @param directories class directories
                     */
                    DirectoryManager( Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories );
                    /**
                     * @brief Class destroy
                     */
                    ~DirectoryManager();
                    /**
                     * @brief method for backup directory
                     * @return true if success
                     */
                    bool backup (bool copyDomToFlash);
                    /**
                     * @brief method for create backup file
                     */
                    void createMachineIdFile(std::string machineId, bool force = false);
					/**
                     * @brief method for validate backup file
                     * @return true if success
                     */						 
					bool validateMachineIdFile(std::string machineId);
                    /**
                     * @brief method for copy directory
                     * @param origDir orig directory name
                     * @param destDir dest directory name
                     * @return true if success
                     */
                    bool copyDir ( std::string origDir, std::string destDir );
                    /**
                     * @brief method for validate machineId in DOM and Flash 
                     * @return true if success
                     */
                    bool validateMachineIdFileDOMFlash();

                private:
					static Smartmatic::Log::ISMTTLog* logger; /**< logger*/
                    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories; /**< saes directories*/
					
                };
            }
        }
    }
}

#endif /*__DIRECTORY_MANAGER_H__*/
