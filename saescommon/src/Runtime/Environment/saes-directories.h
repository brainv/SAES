/**
 * @file saes-directories.h
 * @brief Header class saes directories
 *
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 *
 * @file	saes-directories.h
 *
 * @brief	Declares the saes directories class.
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

#ifndef _SAES_DIRECTORIES_H_
#define _SAES_DIRECTORIES_H_

#include <string>
#include <Configuration/SaesCommonConfiguration-schema.hxx>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
                /**
                 * @class	SaesDirectories
                 *
                 * @brief	Saes directories. 
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 */

                class SaesDirectories
                {
                public:

                    /**
                     * @fn	std::string SaesDirectories::getBasePath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a base path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The base path.
                     */

                	std::string getDevicePath ( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM );

                    /**
                     * @brief	Method getter base path
                     * @param	type	base path type.
                     * @return	base path
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string
                        getBasePath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief	Method getter local base path
                     * @param	type	base path type.
                     * @return	local base path
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string
                        getLocalBasePath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectionFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an election file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The election file full path.
                     */

                    virtual std::string
                        getElectionFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectionStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an election status file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The election status file full path.
                     */

                    std::string
                        getElectionStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getCardListStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a card list status file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The card list status file full path.
                     */

                    std::string
                        getCardListStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getVotingMachineStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a voting machine status file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The voting machine status file full path.
                     */

                    std::string
                        getVotingMachineStatusFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getVotingDeviceFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a voting device file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The voting device file full path.
                     */

                    std::string
                        getVotingDeviceFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectoralResourceFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an electoral resource full folder path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The electoral resource full folder path.
                     */

                    std::string
                        getElectoralResourceFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectoralImagesFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an electoral images full folder path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The electoral images full folder path.
                     */

                    std::string
                        getElectoralImagesFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    std::string getLocalElectoralImagesFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectoralSAESFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an electoral saes full folder path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The electoral saes full folder path.
                     */

                    std::string
                        getElectoralSAESFullFolderPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getTemporalFilesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a temporal files folder full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The temporal files folder full path.
                     */

                    std::string
                        getTemporalFilesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getTemporalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a temporal file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The temporal file full path.
                     */

                    std::string
                        getTemporalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getLanguageFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a language file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The language file full path.
                     */

                    std::string
                        getLanguageFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getPollworkersFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets the pollworkers file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The pollworkers file full path.
                     */

                    std::string
                        getPollworkersFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
					 * @fn	std::string SaesDirectories::getStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
					 *
					 * @brief	Gets the statistics file full path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	type	The type.
					 *
					 * @return	The statistics file full path.
					 */

					std::string
                        getStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
					 * @fn	std::string SaesDirectories::getActivatedCardStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
					 *
					 * @brief	Gets an activated card statistics file full path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	type	The type.
					 *
					 * @return	The activated card statistics file full path.
					 */

					std::string
                        getActivatedCardStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getAssistedActivationFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an assisted activation file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The assisted activation file full path.
                     */

                    std::string
                        getAssistedActivationFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief Method getter voting disabled file full path
                     * @param	type	The type.
                     * @date 21/05/2012
                     * @author Yadickson Soto
                     */
                    std::string
                    	getVotingDisabledFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                    /**
                     * @brief Method getter police notes file full path
                     * @param	type	The type.
                     * @date 25/05/2012
                     * @author Yadickson Soto
                     */
                    std::string
                    	getPoliceNotesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getIncidentReportFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an incident report file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The incident report file full path.
                     */

                    std::string
                        getIncidentReportFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getClosingNotesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a closing notes file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The closing notes file full path.
                     */

                    std::string
                        getClosingNotesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getXMLImageFileFullPath();
                     *
                     * @brief	Gets a xml image file full path.
                     *
                     * @author	Juan.Delgado
                     * @date	18/07/2011
                     *
                     * @return	The xml image file name.
                     */

                    std::string getXMLImageFileName();

                    /**
                     * @fn	std::string SaesDirectories::getBaseInstallationPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a base installation path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The base installation path.
                     */

                    std::string getBaseInstallationPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getSaesDataFolderName();
                     *
                     * @brief	Gets the saes data folder name.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The saes data folder name.
                     */

                    std::string getSaesDataFolderName();

                    /**
                     * @fn	std::string SaesDirectories::getSaesDataFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets the saes data folder full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The saes data folder full path.
                     */

                    std::string
                        getSaesDataFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief	Method getter saes local data folder full path.
                     * @param	type	base path type.
                     * @return	saes local data folder full path.
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string getLocalSaesDataFolderFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getElectionResourcesFileName();
                     *
                     * @brief	Gets the election resources file name.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The election resources file name.
                     */

                    std::string getElectionResourcesFileName();

                    /**
                     * @fn	std::string SaesDirectories::getVotingCentersLocalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a voting centers local file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The voting centers local file full path.
                     */

                    virtual std::string getVotingCentersLocalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getVotingCentersInstalationFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a voting centers instalation file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The voting centers instalation file full path.
                     */

                    virtual std::string getVotingCentersInstalationFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getLanguageInstalationFileFullPath();
                     *
                     * @brief	Gets the language instalation file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The language instalation file full path.
                     */

                    std::string getLanguageInstalationFileFullPath();

                    /**
                     * @fn	std::string SaesDirectories::getLanguageLocalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a language local file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The language local file full path.
                     */

                    std::string
                        getLanguageLocalFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getLanguageImageInstalationDirectoryFullPath();
                     *
                     * @brief	Gets the language image instalation directory full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The language image instalation directory full path.
                     */

                    std::string getLanguageImageInstalationDirectoryFullPath();

                    /**
                     * @fn	std::string SaesDirectories::getLanguageImageDirectoryFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a language image directory full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The language image directory full path.
                     */

                    std::string
                        getLanguageImageDirectoryFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getImageElectoralResource(std::string imageName);
                     *
                     * @brief	Gets an image electoral resource.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	imageName	Name of the image.
                     *
                     * @return	The image electoral resource.
                     */

                    std::string
                    getImageElectoralResource(std::string imageName);

                    /**
                     * @fn	std::string SaesDirectories::getWorkingDirectoryFolderName();
                     *
                     * @brief	Gets the working directory folder name, usually SAESLocal.
                     *
                     * @author	Freddy.Gomez
                     * @date	4/28/2011
                     *
                     * @return	The master configuration base path.
                     */
                    virtual std::string getWorkingDirectoryFolderName();

                    /**
                     * @fn	std::string SaesDirectories::getDOMMemoryBasePath();
                     *
                     * @brief	Gets the DOM memory base path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The master configuration base path.
                     */

                    virtual std::string getDOMMemoryBasePath();

                    /**
                     * @fn	std::string SaesDirectories::getFlashMemoryBasePath();
                     *
                     * @brief	Gets the flash memory base path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The backup configuration base path.
                     */

                    virtual std::string getFlashMemoryBasePath();

                    /**
                     * @fn	std::string SaesDirectories::getBackupFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a backup file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The backup file full path.
                     */

                    std::string getBackupFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);  ///< . 

                    /**
                     * @fn	std::string SaesDirectories::getSecretKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a secret key file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The secret key file full path.
                     */

                    std::string getSecretKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     *
                     * @brief	Gets a up key file full path.
                     *
                     * @author	Yadickson Soto
                     * @date	13/02/2012
                     *
                     * @param	type	The type.
                     *
                     * @return	The up key file full path.
                     */

                    virtual std::string getUPKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn  std::string SaesDirectories::getMachineKeysFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief   Gets a machine keys file full path.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    5/24/2011
                     *
                     * @param   type    The type.
                     *
                     * @return  The machine keys file full path.
                     */

                    std::string getMachineKeysFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief method getter x7s signed certified primary key file full path
                     * @param type type
                     * @return signed certified primary key file full path
                     * @date 21/03/2012
                     * @author Yadickson Soto
                     */
                    std::string getX7SSignedKeyCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief method getter x7s signed certified file full path
                     * @param type type
                     * @return signed certified file full path
                     * @date 21/03/2012
                     * @author Yadickson Soto
                     */
                    std::string getX7SSignedCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief method getter x7s crypto certified file full path
                     * @param type type
                     * @return crypto certified file full path
                     * @date 21/03/2012
                     * @author Yadickson Soto
                     */
                    std::string getX7SCryptoCertifiedFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
					 * @fn	std::string SaesDirectories::getIdHardwareFileFullPath();
					 *
					 * @brief	Gets the file path identifier hardware.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The file path identifier hardware.
					 */

					std::string getIdHardwareFileFullPath();

					/**
					 * @fn	std::string SaesDirectories::getVotingExperienceValidationFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
					 *
					 * @brief	Gets a voting experience validation folder full path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	type	The type.
					 *
					 * @return	The voting experience validation folder full path.
					 */

					std::string getVotingExperienceValidationFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
							Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getVotesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets the votes folder full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The votes folder full path.
                     */

                    std::string getVotesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getDocsFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets the documents folder full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The documents folder full path.
                     */

                    std::string getDocsFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief method getter codi folder
                     * @param	type	The type.
                     * @date 10/05/2012
                     * @return codi folder full path
                     */
                    std::string getCodiFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getTransmissionPackagesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a transmission packages file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The transmission packages file full path.
                     */
                    std::string getTransmissionPackagesFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief	Method getter a transmission packages key file full path.
                     * @param	type	base path type.
                     * @return	transmission packages key file full path.
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string getTransmissionPackagesKeyFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief	Method getter a transmission packages crt file full path.
                     * @param	type	base path type.
                     * @return	transmission packages crt file full path.
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string getTransmissionPackagesCrtFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief	Method getter a transmission packages hash file full path.
                     * @param	type	base path type.
                     * @return	transmission packages hash file full path.
                     *
                     * @author	Yadickson Soto
                     * @date	14/02/2012
                     */
                    std::string getTransmissionPackagesHashFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn  std::string SaesDirectories::getPVFormFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief   Gets a pv form file full path.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    05/05/2011
                     *
                     * @param   type    The type.
                     *
                     * @return  The pv form file full path.
                     */
                    std::string getPVFormFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn  std::string SaesDirectories::getPVFormFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief   Gets a pv form test file full path.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    05/05/2011
                     *
                     * @param   type    The type.
                     *
                     * @return  The pv form test file full path.
                     */
                    std::string getPVFormTestFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
					 * @fn	std::string SaesDirectories::getTransmissionPackageSignatureFileName(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
					 *
					 * @brief	Gets a transmission package signature file name.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	type	The type.
					 *
					 * @return	The transmission package signature file name.
					 */

					std::string getTransmissionPackageSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
                     * @fn  std::string SaesDirectories::getTransmissionPackageSignatureFileName(Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief   Gets a pv report signature file name.
                     *
                     * @author  Yadickson.soto
                     * @date    07/05/2011
                     *
                     * @param   type    The type.
                     *
                     * @return  The pv report signature file name.
                     */

                    std::string getPVFormSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

					/**
					 * @fn	std::string SaesDirectories::getIDCardMembersFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
					 *
					 * @brief	Gets an election closer data file full path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	type	The type.
					 *
					 * @return	The election closer data file full path.
					 */

					std::string getIDCardMembersFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                                                               Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getCACertificateFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a ca certificate file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The ca certificate file full path.
                     */

                    std::string getCACertificateFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getItermediateCACertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets an itermediate ca certificates file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The itermediate ca certificates file full path.
                     */

                    std::string getItermediateCACertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getTrustedCertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                     *
                     * @brief	Gets a trusted certificates file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @param	type	The type.
                     *
                     * @return	The trusted certificates file full path.
                     */

                    std::string getTrustedCertificatesFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getCACertificateInstalationFileFullPath();
                     *
                     * @brief	Gets the ca certificate instalation file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The ca certificate instalation file full path.
                     */

                    std::string getCACertificateInstalationFileFullPath();

					/**
					 * @fn	std::string SaesDirectories::getItermediateCACertificatesInstalationFileFullPath();
					 *
					 * @brief	Gets the itermediate ca certificates instalation file full path.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The itermediate ca certificates instalation file full path.
					 */

					std::string getItermediateCACertificatesInstalationFileFullPath();

                    /**
                     * @fn	std::string SaesDirectories::getTrustedCertificatesInstalationFileFullPath();
                     *
                     * @brief	Gets the trusted certificates instalation file full path.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     *
                     * @return	The trusted certificates instalation file full path.
                     */

                    std::string getTrustedCertificatesInstalationFileFullPath();

                    /**
                     * @fn	std::string SaesDirectories::getPVTemplateFolderFullPath();
                     *
                     * @brief	Gets the full path of the PV template folder.
                     *
                     * @author	Freddy.Gomez
                     * @date	06/05/2011
                     *
                     * @return	The full path of the PV template folder.
                     */
                    std::string getPVTemplateFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);


                    /**
					 * @fn	std::string SaesDirectories::getTestPVTemplateFileFullPath();
					 *
					 * @brief	Gets the full path of the test PV template folder.
					 *
					 * @author	Freddy.Gomez
					 * @date	06/05/2011
					 *
					 * @return	The full path of the test PV template folder.
					 */
                    std::string getTestPVTemplateFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);


                    /**
                     * @fn	std::string SaesDirectories::getGlobalPVTemplateFileFullPath();
                     *
                     * @brief	Gets the full path of the global (non localized) PV template file.
                     *
                     * @author	Freddy.Gomez
                     * @date	06/05/2011
                     *
                     * @return	The full path of the global (non localized) PV template file
                     */

                    std::string getGlobalPVTemplateFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	std::string SaesDirectories::getPVReportFileFullPath();
                     *
                     * @brief	Gets the full path of the pv report file.
                     *
                     * @author	Freddy.Gomez
                     * @date	06/05/2011
                     *
                     * @return	The full path of the global pv report file.
                     */

                    std::string getGeneratedPVReportFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);


                    /**
                     * @fn	std::string SaesDirectories::getGeneratedPVReportTestFullPath();
                     *
                     * @brief	Gets the full path of the test pv report file.
                     *
                     * @author	Freddy.Gomez
                     * @date	06/05/2011
                     *
                     * @return	The full path of the global test pv report file.
                     */
                    std::string getGeneratedPVReportTestFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn  std::string SaesDirectories::getMasterDeviceFileFullPath();
                     *
                     * @brief   Gets the master device file full path.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    19/05/2011
                     *
                     * @return  The master device file full path.
                     */

                    std::string getMasterDeviceFileFullPath();

                    /**
                     * @fn  std::string SaesDirectories::getEventDeviceFileFullPath();
                     *
                     * @brief   Gets the event device file full path.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    19/05/2011
                     *
                     * @return  The event device file full path.
                     */

                    std::string getEventDeviceFileFullPath();

                    /**
                     * @fn  std::string SaesDirectories::getLogFolderName();
                     *
                     * @brief   Gets the log folder name.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    20/05/2011
                     *
                     * @return  The log folder name.
                     */

                    std::string getLogFolderName();

                    /**
                     * @fn  std::string SaesDirectories::getLogFolderFullPath();
                     *
                     * @brief   Gets the log folder full path.
                     * @param type the type
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    20/05/2011
                     *
                     * @return  The log folder full path.
                     */
                    std::string getLogFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                    /**
                     * @fn  std::string SaesDirectories::getLogErrorFileFullPath();
                     *
                     * @brief   Gets the log error file full path.
                     * @param type the type
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    20/05/2011
                     *
                     * @return  The log error file full path.
                     */
                    std::string getLogErrorFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
                    /**
                     * @fn  std::string SaesDirectories::getLogAuditFileFullPath();
                     *
                     * @brief   Gets the log audit file full path.
                     * @param type the type
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    20/05/2011
                     *
                     * @return  The log audit file full path.
                     */
                    std::string getLogAuditFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn  std::string SaesDirectories::getElectoralResourcesFolderName();
                     *
                     * @brief   Gets the electoral resources folder name
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    19/05/2011
                     *
                     * @return  The electoral resources folder name.
                     */

                    std::string getElectoralResourcesFolderName();

                    /**
                     * @fn  std::string SaesDirectories::getVoteStatisticsFileFullPath();
                     *
                     * @brief   Gets the vote statistics file full path.
                     * @param type the type
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    20/05/2011
                     *
                     * @return  The vote statistics file full path.
                     */
                    std::string getVoteStatisticsFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @fn	SaesDirectories::SaesDirectories();
                     *
                     * @brief	Default constructor.
                     *
                     * @author	Cesar.bonilla
                     * @date	4/28/2011
                     */
                    SaesDirectories();

                    /**
                     * @brief Class destroy
                     *
                     * @author  Yadickson Soto
                     * @date    14/02/2012
                     */
                    virtual ~SaesDirectories();

                    /**
                     * @fn  std::string SaesDirectories::getElectionResultSignatureFileFullPath();
                     *
                     * @brief   Gets the election result signature file full path.
                     *
                     * @author  Freddy Gomez
                     * @date    19/05/2011
                     *
                     * @return  The election result signature file full path.
                     */

                    std::string getElectionResultSignatureFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                    		Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief Method getter signature resource file full path
                     * @param type base path type
                     * @return signature resource file full path
                     *
                     * @author  Yadickson Soto
                     * @date    14/02/2012
                     */
                    std::string getSignatureResourceFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    /**
                     * @brief Method getter codi files foder full path
                     * @param type base path type
                     * @return codi files foder full path
                     *
                     * @author  Yadickson Soto
                     * @date    14/02/2012
                     */
                    std::string getCodiFilesFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                protected:

                    std::string languageImageDirectory; ///< Pathname of the language image directory
                    std::string backupFileName; ///< Filename of the backup file

                    /**
                     * @brief Method getter project name
                     * @return project name
                     *
                     * @author  Yadickson Soto
                     * @date    14/02/2012
                     */
                    std::string getProjectName();

                private:

                    //Folders name
                    std::string CodiFilesFolder; ///< codi file folder name
                    std::string LiveFileSystem; ///< Live file system
                    std::string workingDirectory; ///< Pathname of the working directory
                    std::string SaesDataFolderName; ///< Pathname of the saes data folder
                    std::string PollworkersFileName;	///< Filename of the pollworkers file
					std::string StatisticsFileName; ///< Filename of the statistics file
					std::string ActivatedCardStatisticsFileName;	///< Filename of the activated card statistics file
                    std::string AssistedActivationFileName; ///< Filename of the assisted activation file
                    std::string VotingDisabledFileName; ///< Filename of the voting disabled file
                    std::string PoliceNotesFileName; ///< Filename of the police notes file
                    std::string ClosingNotesFileName;   ///< Filename of the closing notes file
                    std::string XMLImageFileName;   ///< Filename of the closing notes file
                    std::string IncidentReportFileName; ///< Filename of the incident report file

                    std::string votingCentersFileName;  ///< Filename of the voting centers file
                    std::string secretKeyFileName;  ///< Filename of the secret key file
                    std::string machineKeysFileName; /// File name of the machine keys

                    std::string CACertificateFileName;  ///< Filename of the ca certificate file
                    std::string ItermediateCACertificatesFileName;  ///< Filename of the itermediate ca certificates file
                    std::string TrustedCertificatesFileName;	///< Filename of the trusted certificates file

                    std::string ElectoralResourcesFolderName;	///< Name of the electoral resources folder
                    std::string ElectoralImageFolderName;   ///< Pathname of the electoral image folder
                    std::string ElectionResourcesFileName;  ///< Filename of the election resources file
                    std::string TemporalFilesFolderName;	///< Pathname of the temporal files folder

                    std::string projectName;	///< Name of the project
                    std::string languageFileName;   ///< Filename of the language file

                    //Files Name

                    std::string ElectionStatusFileName; ///< Filename of the election status file
                    std::string CardListStatusFileName; ///< Filename of the card list status file
                    std::string VotingMachineStatusFileName;	///< Filename of the voting machine status file
                    std::string VotingDeviceFileName;   ///< Filename of the voting device file
					std::string IDCardMembersFileName; ///< Filename of the id card members
					std::string TransmissionPackageSignatureFileName;   ///< Filename of the transmission package signature file
                    std::string PVFormFileName;   ///< Filename of the pv form
                    std::string PVFormSignatureFileName; ///< sidneg filename of the pv form
                    std::string VoteStatisticsFileName; ///< Vote statistic file name
                    std::string SignatureResourceFileName; ///< Signature resource file name

					//File IdHardware
					std::string IdHardwareFileFullPath; ///< The file path identifier hardware
					std::string MasterDeviceFileFullPath; ///< The master device file full path
					std::string EventDeviceFileFullPath; ///< The event device file full path

					//Voting Experience Simulation
					std::string votingExperienceValidationFolderName;   ///< Pathname of the voting experience validation folder
					std::string VotesFolder;	///< Pathname of the votes folder
					std::string DocsFolder; ///< Pathname of the documents folder
					std::string CodiFolder; ///< Pathname of the codi folder
					std::string PVTemplateFolder; ///< Pathname of the PVTemplate folder
					std::string TransmissionPackageFileName;	///< Filename of the transmission package file
                    std::string TransmissionPackageHashFileName;    ///< Filename of the transmission package hash file
                    std::string TransmissionPackageKeyFileName; ///< Filename of the transmission package key file
                    std::string TransmissionPackageCrtFileName; ///< Filename of the transmission package crt file
					std::string PVTemplateFileName;	///< Filename of the nonlocalized PV template
					std::string GeneratedPVReportFileName;	///< Filename of the nonlocalized PV template
					std::string ElectionResultSignatureFile; ///< Filename of signature of the election returns

					//Log configuration
					std::string logFolderName; ///< log folder name
                    std::string logErrorFileName; ///< log error file name
                    std::string logAuditFileName; ///< log audit file name

                    //X7S certified files
                    std::string X7SSignedKeyCertifiedFileName;
                    std::string X7SSignedCertifiedFileName;
                    std::string X7SCryptoCertifiedFileName;

                protected:
                    std::string ElectionFileName;   ///< Filename of the election file
                    std::string upKeyFileName; ///< Filename of the up key
                };
            }
        }
    }
}

#endif // _SAES_DIRECTORIES_H_
