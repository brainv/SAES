/**
 * @file	s-a-e-s-hardware-conf-manager.h
 *
 * @brief	Declares a e s hardware conf manager class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _S_A_E_S_HARDWARE_CONFIGURATION_MANAGER_H_
#define _S_A_E_S_HARDWARE_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SaesHardwareConfiguration-schema.hxx>
#include <Configuration/ConfigurationBase-schema.hxx>
#include "Configuration/configuration-persistence-manager.h"

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

    namespace SAES
	{
		namespace HW
		{
			namespace Configuration
			{
				/**
				 * @brief	Manager for saes hardware configurations. 
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class SAESHardwareConfigurationManager
				{
				public:

						/**
						 * @brief	Gets the current hardware configuration manager.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @return	null if it fails, else.
						 */

						static SAESHardwareConfigurationManager *Current();

						/**
						 * @brief	Gets the configuration.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @return	null if it fails, else the configuration.
						 */

						std::auto_ptr<Smartmatic::SAES::HW::Configuration::SaesHardwareConfiguration>* getConfiguration();

						/**
						 * @brief	Loads the default configuration.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 */

						void LoadDefault();

						/**
						 * @brief	Gets the list of barcode ports.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @return	The list of barcode ports.
						 */

						std::vector<std::string> getListOfBarcodePorts();		

						/**
						 * @brief	Gets the smart card reader type.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @return	The smart card reader type.
						 */

						CardReaderType getSmartCardReaderType();

						/**
						 * @brief	Gets the barcode configuration commands.
						 *
						 * @author	Juan.Delgado
						 * @date	24/08/2011
						 *
						 * @param	commandBlock, command block name
						 * @param	barcodeModel, model of barcode
						 *
						 * @return	The configuration commands.
						 */
						BarcodeCommands::CommandSequence getBarcodeConfigurationCommands(const std::string& commandBlock, const std::string& barcodeModel);


						BarcodeDeviceConfiguration & getBarcodeDeviceConfiguration();

				protected:

						/**
						 * @brief	Default constructor.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 */

						SAESHardwareConfigurationManager();

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 */

						~SAESHardwareConfigurationManager();

						/**
						 * @brief	Initializes this object.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 */

						void Initialize();

						static SAESHardwareConfigurationManager * singleton_instance;   ///< The singleton instance.
				private:

                        std::auto_ptr<Smartmatic::SAES::HW::Configuration::SaesHardwareConfiguration> *configuration;   ///< The configuration
                        static Smartmatic::Log::ISMTTLog* logger; ///< The logger
				};
			}
		}
	}
}

#endif // _S_A_E_S_HARDWARE_CONFIGURATION_MANAGER_H_
