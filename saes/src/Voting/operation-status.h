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

#ifndef _OPERATION_STATUS_H_
#define _OPERATION_STATUS_H_
#include <iostream>
#include <fstream>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Voting/Status/CardGeneratedListWrapper.hxx>
#include <Voting/Status/VMStatusWrapper.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Log/ISMTTLog.h>
#include <glibmm.h>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
			/**
			 * @brief	Operation status. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class OperationStatus
			{
			public:

				enum Diagnostic
				{
					Ballot,
					Printer,
					AlarmBox,
					SmartCard,											
					TouchScreenCalibration,
					ScreenContrast,
					Barcode,
					Flash,
					Able,
					DateTime,
				};

				enum DiagStatus
				{
					NotDiagnosed,
					Run,
					Ok,
					Error
				};

				/**
				 * @brief	Gets the current Operation Status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else the Operation Status.
				 */

				static OperationStatus* Current();

				/**
				 * @brief	Loads the default.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void LoadDefault();

				/**
				 * @brief	Initialises this object.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void init()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

				/**
				 * @brief	Persist election status.
				 * @param 	loadOpeningCode force load opening code
				 * @param 	createBackup create backup file
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void persistElectionStatus(bool loadOpeningCode = true, bool createBackup = true)
				throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

				/**
				 * @brief	Persist card list status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 */

				void persistCardListStatus()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

				/**
				 * @brief	Persist voting machine status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 */

				void persistVotingMachineStatus()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

				/**
				 * @brief	Persist on status change.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	persistOnChange	true to persist on change.
				 */

				void PersistOnStatusChange(bool persistOnChange);

                /**
                 * @brief	Change diagnosis status.
                 *
                 * @author	Eduardo.campione
                 * @date	28/04/2011
                 *
                 * @param	diag	The diagram.
                 * @param	stat	The stat.
                 */

                void changeDiagnosisStatus(Diagnostic diag, DiagStatus stat);

				/**
				 * @brief	Gets the diagnosis status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	diag	The diagram.
				 *
				 * @return	The diagnosis status.
				 */

				OperationStatus::DiagStatus getDiagnosisStatus(Diagnostic diag);

				/**
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void dispose();

				/**
				 * @brief	Gets the election status wrapper.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The election status wrapper.
				 */

				Smartmatic::SAES::Voting::Status::ElectionStatusWrapper * getElectionStatusWrapper();

				/**
				 * @brief	Gets the card generated list status wrapper.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The card generated list status wrapper.
				 */

				Smartmatic::SAES::Voting::Status::CardGeneratedListWrapper * getCardGeneratedListStatusWrapper();

				/**
				 * @brief	Gets the voting machine status wrapper.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The voting machine status wrapper.
				 */

				Smartmatic::SAES::Voting::Status::VotingMachineStatusWrapper * getVotingMachineStatusWrapper();

				/**
				 * @brief	Gets the device status list.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The device status list.
				 */

				std::vector<std::string> getDeviceStatusList();

				/**
				 * @brief	Gets the device list.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The device list.
				 */

				std::vector<OperationStatus::Diagnostic> getDeviceList();

				/**
				 * @brief	Loads the default virtual memory status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void LoadDefaultVMStatus();

				/**
				 * @brief	Loads the default election status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void LoadDefaultElectionStatus();


                /**
                 * @brief   Initializes the election status.
                 *
                 * @author  Eduardo.campione
                 * @date    28/04/2011
                 */

                bool InitializeElectionStatus()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

                /**
                 * @brief   Initializes the card data list status.
                 *
                 * @author  Eduardo.campione
                 * @date    28/04/2011
                 */

                bool InitializeCardDataListStatus()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);

                /**
                 * @brief   Initializes the virtual memory status.
                 *
                 * @author  Eduardo.campione
                 * @date    28/04/2011
                 */

                bool InitializeVMStatus()
                throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);


			protected:

			private:
				bool persistanceOnStatusChange; ///< true to persistance on status change
				Smartmatic::SAES::Voting::Status::ElectionStatus *base; ///< The base of the election status
				Smartmatic::SAES::Voting::Status::VotingMachineStatus *baseVM;  ///< The base virtual memory
				Smartmatic::SAES::Voting::Status::CardDataList *baseCardList;   ///< List of base cards
				Smartmatic::SAES::Voting::Status::DevicesStatus* devices;   ///< The devices
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceBallot;   ///< The device ballot
				Smartmatic::SAES::Voting::Status::DeviceStatus* devicePrinter;  ///< The device printer
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceSmartcard;	///< The device smartcard
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceScreenCalibration;	///< The device screen calibration
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceScreenContrast;   ///< The device screen contrast
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceAlarmBox; ///< The device alarm box
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceBarcode;  ///< The device barcode
				Smartmatic::SAES::Voting::Status::DeviceStatus* deviceFlash;	///< The device flash

				/**
				 * @brief	Change status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	device	The device.
				 * @param	stat		  	The stat.
				 */

				void changeStatus(Smartmatic::SAES::Voting::Status::DeviceStatus* device,DiagStatus stat);

				/**
				 * @brief	Gets a device status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	device	The device.
				 * @param	diag		  	The diagram.
				 *
				 * @return	null if it fails, else the device status.
				 */

				Smartmatic::SAES::Voting::Status::DeviceStatus* getDeviceStatus(Smartmatic::SAES::Voting::Status::DeviceStatus* device, Diagnostic diag);

				/**
				 * @brief	Look status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	device	The device.
				 * @param	index 	Zero-based index of the.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool lookStatus(Smartmatic::SAES::Voting::Status::VMType::Value device, unsigned int index);
				static OperationStatus* singleton_instance; ///< The singleton instance

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				OperationStatus();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				~OperationStatus();
				Smartmatic::SAES::Voting::Status::VotingMachineStatusWrapper *vmStatus; ///< The virtual memory status
				Smartmatic::SAES::Voting::Status::ElectionStatusWrapper* electionStatus;	///< The election status
				Smartmatic::SAES::Voting::Status::CardGeneratedListWrapper*	cardListStatus; ///< The card list status

				/**
				 * @brief	Loads the default card list status.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void LoadDefaultCardListStatus();

				Smartmatic::SAES::Voting::Status::ElectionStatusWrapper * loadElectionStatusFile(std::string file);

				Glib::Mutex mutex;
				static Smartmatic::Log::ISMTTLog* logger; ///< logger
			};
	  }
   }
}

#endif // _OPERATION_STATUS_H_
