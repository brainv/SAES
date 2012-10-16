/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/** 
 * smartmatic
 * Copyright (C)  2011 <>
 * 
 * @file s-a-e-s-common-conf-manager.h
 * 
 * @brief defines a common configuration manager
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _S_A_E_S_COMMON_CONFIGURATION_MANAGER_H_
#define _S_A_E_S_COMMON_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <Configuration/ConfigurationBase-schema.hxx>
#include <Configuration/configuration-persistence-manager.h>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

    namespace SAES
	{
		namespace Common
		{
			namespace Configuration
			{
				/**
				 * @class	SAESCommonConfigurationManager
				 *
				 * @brief	Manager for saes common configurations. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class SAESCommonConfigurationManager
				{
				public:

						/**
						 * @fn	static SAESCommonConfigurationManager SAESCommonConfigurationManager::*Current();
						 *
						 * @brief	Gets the current.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @return	null if it fails, else.
						 */

						static SAESCommonConfigurationManager *Current();
                                                std::auto_ptr<SaesCommonConfiguration>* getConfiguration();

						/**
						 * @fn	void SAESCommonConfigurationManager::LoadDefault();
						 *
						 * @brief	Loads the default.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void LoadDefault();

						/**
						 * @fn	SecurityConfiguration & SAESCommonConfigurationManager::getSecurityConfiguration();
						 *
						 * @brief	Gets the security configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @return	The security configuration.
						 */

						SecurityConfiguration & getSecurityConfiguration();

						/**
						 * @fn	FileSystemVoteConfiguration & SAESCommonConfigurationManager::getFileSystemVoteConfiguration();
						 *
						 * @brief	Gets the file system vote configuration.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @return	The file system vote configuration.
						 */

						FileSystemVoteConfiguration & getFileSystemVoteConfiguration();

                        /**
                         * @brief   Method getter printer backend type.
                         *
                         * @author  Yadickson Soto yadickson.soto@smartmatic.com
                         * @date    03/06/2011
                         *
                         * @return  printer backend type.
                         */

						PrinterBackendType & getPrinterBackendType();


						ConfigurationBasePath & getConfigBasePath();

						/**
                         * @brief   Method getter is verify extern elements.
                         *
                         * @author  Yadickson Soto yadickson.soto@smartmatic.com
                         * @date    03/06/2011
                         *
                         * @return  true is verify extern elements.
						 */

						bool isVerifyExternElements();

                        /**
                         * @brief   Method getter is compress election.
                         *
                         * @author  Yadickson Soto yadickson.soto@smartmatic.com
                         * @date    03/06/2011
                         *
                         * @return  true is compress election.
                         */

                        bool isCompressElection();

                        /**
                         * @brief   Method getter is compress voting devices.
                         *
                         * @author  Yadickson Soto yadickson.soto@smartmatic.com
                         * @date    03/06/2011
                         *
                         * @return  true is compress voting devices.
                         */

                        bool isCompressVotingDevices();

                        /**
                         * @brief   Method getter is use asimetric key transmission package.
                         *
                         * @author  Yadickson Soto yadickson.soto@smartmatic.com
                         * @date    08/06/2011
                         *
                         * @return  true is use asimetric key transmission package.
                         */

                        bool isUseAsimetricKeyForTransmissionPackages ();

                        BEIDConfiguration & getBEIDConfiguration ();

                        SmartCardConfiguration & getSmartCardConfiguration ();

                        PCSCDConfiguration & getPCSCDConfiguration ();

                        bool getStatusMonitorCancel ();

                        int getStatusMonitorTimeOut ();

                        bool getDirectQrUseOptimization ();

                        std::string getDirectQrCommandHeader ();

                        std::string getDirectQrCommandFooter ();

                        bool isPVInAllLanguages();

                        bool isForceReduceElection();

                        OSConfigurationFiles & getOSConfigurationFiles();

				protected:

						/**
						 * @fn	SAESCommonConfigurationManager::SAESCommonConfigurationManager();
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	26/04/2011
						 */

						SAESCommonConfigurationManager();

						/**
						 * @fn	SAESCommonConfigurationManager::~SAESCommonConfigurationManager();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						~SAESCommonConfigurationManager();

						std::auto_ptr<SaesCommonConfiguration> *configuration;  ///< The configuration

						/**
						 * @fn	void SAESCommonConfigurationManager::Initialize();
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void Initialize();

						static SAESCommonConfigurationManager * singleton_instance; ///< The singleton instance
				private:
						static Smartmatic::Log::ISMTTLog* logger;/**logger*/	///< The logger
				};
			}
		}
	}
}

#endif // _S_A_E_S_COMMON_CONFIGURATION_MANAGER_H_
