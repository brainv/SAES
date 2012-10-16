/*
 * MemoryPathController.h
 *
 *  Created on: May 18, 2011
 *      Author: feddy
 */

#ifndef MEMORYPATHCONTROLLER_H_
#define MEMORYPATHCONTROLLER_H_

#include <string>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <glibmm.h>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
                /**
                 * @class	MemoryPathController
                 *
                 * @brief	Memory Path Manager.
                 *
                 * @author	Freddy.Gomez
                 * @date	18/05/2011
                 */

                class MemoryPathController
                {
                public:

                    /**
                     * @fn	MemoryPathController::MemoryPathController();
                     *
                     * @brief	Default constructor.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    MemoryPathController();

                    /**
                     * @fn	MemoryPathController::~MemoryPathController();
                     *
                     * @brief	Finalizer.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    virtual ~MemoryPathController();

                    /**
                     * @fn	MemoryPathController::getStartupMemoryBasePath();
                     *
                     * @brief	Get the path of the startup meomry.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     * @return the path of the startup memory.
                     */
                    std::string& getStartupMemoryBasePath();

                    /**
                     * @fn	MemoryPathController::getLiveFileSystemBasePath();
                     *
                     * @brief	Get the path of the memory mapped file system.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     * @return the path of live file system.
                     */
                    std::string& getLiveFileSystemBasePath();

                    /**
                     * @fn	MemoryPathController::getDomMemoryBasePath();
                     *
                     * @brief	Get the path of the dom memory.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     * @return  The path of the Dom memory, if connected.
                     */
                    std::string& getDomMemoryBasePath();

                    /**
                     * @fn	MemoryPathController::getFlashMemoryBasePath();
                     *
                     * @brief	Get the path of the flash memory.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     * @return  The path of the Flash memory, if connected.
                     */
                    std::string& getFlashMemoryBasePath();

                    /**
                     * @brief	Get the path of the backup memory
                     *
                     * @author	Yadickson Soto
                     * @date	14/05/2012
                     * @return  The path of the backup memory
                     */
                    std::string& getBackupMemoryBasePath();

                    /**
                     * @fn	MemoryPathController::getInstance();
                     *
                     * @brief	Get the unique instance of the class.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     * @return  The instance of the class.
                     */
                    static MemoryPathController * getInstance();

                    /**
                     * @fn	MemoryPathController::UpdatePaths();
                     *
                     * @brief	Update the Paths registered.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    void updatePaths();
                    /**
                     * @brief method getter rules config
                     * @date 04/06/2012
                     * @author Yadickson Soto
                     */
                    Smartmatic::SAES::Common::Configuration::RulesBasePathType & getRule();
                    /**
                     * @brief method getter is all devices
                     * @return true is all devices
                     * @date 04/06/2012
                     * @author Yadickson Soto
                     */
                    bool isAllDevices();

                private:

                    static MemoryPathController * instance; ///< instance of class MemoryPathController
                    std::string startupMemoryBasePath; ///< path of the startup memory
                    std::string liveFileSystemBasePath; ///< path of the live folder
                    std::string domMemoryBasePath; ///< path of the DOM memory
                    std::string flashMemoryBasePath;///< path of the Flash Memory
                    std::string backupMemoryBasePath; ///< path of the backup memory
                    Smartmatic::SAES::Common::Configuration::RulesBasePathType rule; ///< current rule
                    std::string masterDeviceFileFullPath; ///< master device file
                    std::string eventDeviceFileFullPath; ///< event device file
                    Glib::Mutex mutex; ///< mutex

                    /**
                     * @brief Method read master device
                     * @param file master device file full path
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 19/05/2011
                     */
                    void readMasterDevice(std::string file);

                    /**
                     * @brief Method read event device
                     * @param file event device file full path
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 19/05/2011
                     */
                    void readEventDevice(std::string file);

                    /**
                     * @brief Method umount device
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 27/05/2011
                     * @param device to umount
                     * @return true if success
                     */
                    bool umountDevice( std::string device );
                };

            }
        }
    }
}
#endif /* MEMORYPATHCONTROLLER_H_ */
