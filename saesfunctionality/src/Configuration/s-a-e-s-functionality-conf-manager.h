/**
 * @file	s-a-e-s-functionality-conf-manager.h
 *
 * @brief	Declares SAES functionality conf manager class.
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

#ifndef _S_A_E_S_FUNCTIONALITY_CONFIGURATION_MANAGER_H_
#define _S_A_E_S_FUNCTIONALITY_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SaesFunctionalityConfiguration-schema.hxx>
#include <Configuration/ConfigurationBase-schema.hxx>
#include "Configuration/configuration-persistence-manager.h"

namespace Smartmatic
{
	namespace Log
    {
        /**
         * @brief	SAES. 
         *
         */

        class ISMTTLog;
    }
	namespace SAES
	{
		namespace Functionality
		{
			namespace Configuration
			{
				/**
				 * @brief	Manager for SAES functionality configurations. 
				 */

				class SAESFunctionalityConfigurationManager
				{
				public:

						/**
						 * @brief	Gets the current configuration manager.
						 * @return	null if it fails, else.
						 */

						static SAESFunctionalityConfigurationManager *Current();

						/**
						 * @brief	Gets the configuration.
						 * @return	null if it fails, else the configuration.
						 */

						std::auto_ptr<SaesFunctionalityConfiguration>* getConfiguration();

						/**
						 * @brief	Loads the default.
						 */

						void LoadDefault();

						/**
						 * @brief	method to obtain the voting experience controller configuration.
						 * @return	voting experience controller configuration.
						 */

						VotingExperienceControllerConfiguration getVotingExperienceControllerConfiguration();

                        /**
                         * @brief	method to obtain the blank vote configuration.
                         * @return	blank vote configuration.
                         */

                        BlankVoteConfiguration getBlankVoteConfiguration();

                        /**
                         * @brief	method to obtain the vote configuration.
                         * @return	vote configuration.
                         */

                        VoteConfiguration getVoteConfiguration();
                        /**
                         * @brief	method to obtain the operation's configuration.
                         * @return	operation's configuration.
                         */
                        OperationConfiguration getOperationConfiguration();

						/**
						 * @brief	method to obtain the system role configuration.
						 * @return	system role configuration.
						 */

						SystemRoleConfiguration getSystemRoleConfiguration();

						/**
						 * @brief	method to obtain the commands of the alarm.
						 * @param	typeOfAlarm	Type of the alarm.
						 * @return	The commands of alarm.
						 */

						std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand> getCommandsOfAlarm(std::string typeOfAlarm);					

						/**
						 * @brief	method to obtain the commands of the alarm.
						 * @param [in,out]	list	The list.
						 * @param	typeOfAlarm 	Type of the alarm.
						 */

						void getCommandsOfAlarm(std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand>& list,  AlarmEnum typeOfAlarm);

						/**
						 * @brief	obtains the category of the alarm.
						 * @param	typeOfAlarm	Type of the alarm.
						 * @return	The category of alarm.
						 */

						AlarmCategoryEnum getCategoryOfAlarm(AlarmEnum typeOfAlarm);

						/**
						 * @brief	obtains the behavior of the alarm.
						 * @param	typeOfAlarm	Type of the alarm.
						 * @return	The behavior of alarm.
						 */

						AlarmBehaviorEnum getBehaviorOfAlarm(AlarmEnum typeOfAlarm);

						/**
						 * @brief	obtains the launch configuration.		
						 * @return	The launch configuration.
						 */

						LaunchConfiguration& getLaunchConfiguration();

						/**
						 * @brief	obtains the message remove flash time.
						 * @return	message remove flash time.
						 */

						int getMessageRemoveFlashTime();

						int getVMSuccesMessageTime();

						int getPMSuccesMessageTime();

						int getVMStepTime();

						int getPMStepTime();

						CardTypeController & getCardTypeController();
						PVFormTransformationConfig & getPVFormTransformation();
						StructureInstallationType & getStructureInstallationType();
						EnqueueVoteConfiguration & getEnqueueVoteConfiguration();
						
				protected:

						/**
						 * @brief	Default constructor.
						 */
						SAESFunctionalityConfigurationManager();

						/**
						 * @brief	Finaliser.
						 */

						~SAESFunctionalityConfigurationManager();
						std::auto_ptr<SaesFunctionalityConfiguration>* configuration;   ///< The configuration

						/**
						 * @brief	Initializes this object.
						 */

						void Initialize();
				private:
                        static SAESFunctionalityConfigurationManager * singleton_instance;  ///< The singleton instance
						static Smartmatic::Log::ISMTTLog* logger;	///< The logger
				};
			}
		}
	}
}

#endif // _S_A_E_S_FUNCTIONALITY_CONFIGURATION_MANAGER_H_
