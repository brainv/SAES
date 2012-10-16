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

#ifndef _S_A_E_S_CONFIGURATION_MANAGER_H_
#define _S_A_E_S_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SaesConfiguration-schema.hxx>
#include <qrencode.h>

namespace Smartmatic
{
    namespace Log
    {
        /**
         * @class	ISMTTLog
         *
         * @brief	Interface for the log class. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */
        class ISMTTLog;
    }

	namespace SAES
	{
		namespace Configuration
		{
			/**
			 * @class	SAESConfigurationManager
			 *
			 * @brief	Manager for saes configurations. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class SAESConfigurationManager
			{
			public:

					/**
					 * @brief	Gets the current SAES Configuration Manager.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the current SAES Configuration Manager.
					 */

					static SAESConfigurationManager *Current();

					/**
					 * @brief	Gets the Saes configuration.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the Saes configuration.
					 */

					std::auto_ptr<SaesConfiguration> *getConfiguration();

					/**
					 * @brief	Loads the default.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void LoadDefault();

                    /**
                     * @brief	method to obtain the Vote Dummy Configuration.
                     *
                     * @author	Eduardo.campione
                     * @date	28/04/2011
                     *
                     * @return	Vote Dummy Configuration.
                     */

                    VoteDummyConfiguration getVoteDummyConfiguration();

					/**
					 * @brief	Gets the Correction Mode QR Code
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The correction mode qr code.
					 */

					QRecLevel GetCorrectionModeQRCode(CorrectionModeQRCode & correction);

                    /**
                     * @brief   Gets the QR code vote config
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    31/05/2011
                     *
                     * @return  The QR code vote config
                     */

					QRCodeConfig getQRCodeVoteConfig(int size = -1);

                    /**
                     * @brief   Gets the QR code barcode config
                     *
                     * @author  Juan Delgado juand.delgado@smartmatic.com
                     * @date    30/08/2011
                     *
                     * @return  The QR code barcode config
                     */

					QRCodeConfig getQRCodeBarcodeConfig();

                    /**
                     * @brief   Gets the QR code install config
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    31/05/2011
                     *
                     * @return  The QR code install config
                     */

                    QRCodeConfig getQRCodeInstallConfig();

					/**
					 * @brief	Gets the card validity.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The card validity.
					 */

					unsigned int getCardValidity();

					bool getAllowRecoveryCardGenerationOfConsolidatedVotes();

					bool getSaveDemoVotesInTransmissionPackage();

					/**
					 * @brief method getter codi file configuration
					 * @return codi file configuration
					 * @author Yadickson Soto
					 * @date 02/03/2012
					 */
					CodiFileConfiguration & getCodiFileConfiguration();

					/**
					 * @brief	Gets the print vote configuration
					 *
					 * @author	Freddy.Gomez
					 * @date	04/05/2011
					 *
					 * @return	The print vote configuration.
					 */
					ConfigurationVote & getPrintVoteConfiguration();
                    
                    /**
                    * @brief	Gets the screen vote configuration 
                    *
                    * @author	daniel.ampuero
                    * @date	04/05/2011
                    *
                    * @return	The screen vote configuration.
                    */
                    ConfigurationVote& getPrintScreenVoteConfiguration();

                    /**
                     * @brief   Method getter vote checksum type
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     */

                    VoteChecksumType getVoteChecksum();

                    /**
                     * @brief   Method getter vote code config
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    14/07/2011
                     */

                    VoteCodeConfig & getVoteCodeConfig();

                    VoteEncodeModeType getEncodingMode ();

                    bool showBarCodeInstallationReport();

                    bool isUseShortVoteCode();

                    LayoutContestConfiguration & getLayoutContestConfiguration();

                    LayoutBallotOptiontType & getLayoutBallotOptiontType();
                    
                    LayoutContestConfiguration & getLayoutContestConfigurationPreviewScreen();

                    LayoutBallotOptiontType & getLayoutBallotOptiontTypePreviewScreen();

			protected:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					SAESConfigurationManager();		

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~SAESConfigurationManager();	

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void Initialize();

					static SAESConfigurationManager * singleton_instance;   ///< The singleton instance

			private:
					std::auto_ptr<SaesConfiguration>* configuration;	///< The saes configuration
					static Smartmatic::Log::ISMTTLog* logger;/**logger*/
			};
		}
	}
}

#endif // _S_M_T_T_G_U_I_CONFIGURATION_MANAGER_H_
