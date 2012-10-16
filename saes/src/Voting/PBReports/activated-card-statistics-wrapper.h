/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ACTIVATED_CARD_STATISTICS_WRAPPER_H_
#define _ACTIVATED_CARD_STATISTICS_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/activated-card-statistics-schema.hxx>
#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/VotingDevice/card-data-schema.hxx>
namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

   namespace SAES
   {
      namespace Voting
      {
         namespace PBReports
         {
			/**
			 * @brief	Header class ActivatedCardStatisticsWrapper.
			 *
			 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
			 * @date	29-03-2011
			 */

			class ActivatedCardStatisticsWrapper
			{
			private:
					ActivatedCardStatistics* cardStatistics;	///< The card statistics

					/**
					 * @brief	Load the Activated Card Statistics
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	xmlFile	The std::string to load.
					 * @return true is load file
					 */

					bool Load(std::string xmlFile,Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);
					
					bool oneMemory;

					Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* votingDeviceWrapper;   ///< The voting device wrapper
					Smartmatic::SAES::Voting::VotingDevice::Voting_device vd;   ///< The voting device
			public:

					/**
					 * @brief	Class constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					ActivatedCardStatisticsWrapper();

					/**
					 * @brief	Class destroyer.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~ActivatedCardStatisticsWrapper();					

					/**
					 * @brief	Persists.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	oneMemory	true if only one memory
					 */

					void Persist()
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

                    /**
                     * @brief	Initialises this object.
                     *
                     * @author	Eduardo.campione
                     * @date	28/04/2011
                     * @return true is load file
                     */

                    bool init (Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */


					ActivatedCardStatistics* getCardStatistics();
					void RefreshStats(Smartmatic::SAES::Voting::VotingDevice::Card_data & card)
						 throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);
					
					bool RestoreFile(Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf);


					void Dispose ();

					void IncrementTotalActivated();
					void IncrementTotalNonAudioActivated();
					void IncrementTotalAudioActivated();
					void IncrementTotalOfficialActivated();
					void IncrementTotalDemoActivated();
					void IncrementTotalRecoveryActivated();
					void IncrementTotalAudioOfficialActivated();
					void IncrementTotalAudioDemoActivated();
					void IncrementTotalAudioRecoveryActivated();
					void IncrementTotalNonAudioOfficialActivated();
					void IncrementTotalNonAudioDemoActivated();
					void IncrementTotalNonAudioRecoveryActivated();

					unsigned int getTotalActivated();
					unsigned int getTotalNonAudioActivated();
					unsigned int getTotalAudioActivated();
					unsigned int getTotalOfficialActivated();
					unsigned int getTotalDemoActivated();
					unsigned int getTotalRecoveryActivated();
					unsigned int getTotalAudioOfficialActivated();
					unsigned int getTotalAudioDemoActivated();
					unsigned int getTotalAudioRecoveryActivated();
					unsigned int getTotalNonAudioOfficialActivated();
					unsigned int getTotalNonAudioDemoActivated();
					unsigned int getTotalNonAudioRecoveryActivated();
					
                    static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
           
		 }
	  }
   }
}

#endif // _ACTIVATED_CARD_STATISTICS_WRAPPER_H_
