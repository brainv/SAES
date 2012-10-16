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

#ifndef _INSTALLATIONPRINTDOCUMENT_H_
#define _INSTALLATIONPRINTDOCUMENT_H_

#include "Printing/BasePrintDocument.h"
#include <Voting/ElectoralConfiguration.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include "Graphics/Encoding2D/QREncoding.h"
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include "Printing/DocumentOptions.h"
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @brief	Installation print document. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class InstallationPrintDocument : public BasePrintDocument
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	electoralConfiguration	the electoral configuration.
				 * @param	InstallationReport			  	true for install the report.
				 */

				InstallationPrintDocument (Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,bool InstallationReport, bool createBarcodeOnConstructor);

				/**
				 * @brief	Print document.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void PrintDoc();

				/**
				 * @brief	Begins a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void BeginPrint();

				/**
				 * @brief	Ends a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void EndPrint();

				/**
				 * @brief	Set is password retry.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */
				void setIsPasswordRetry(bool isPasswordRetryA);

				void setPixbufBarCode(Glib::RefPtr<Gdk::Pixbuf> pixbufBarCode);

				static Glib::RefPtr<Gdk::Pixbuf> GetQRCodeVotingMachineStatus();

			protected:

			private:

				/**
				 * @brief	Converts a deviceName to a readable.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	deviceName	Name of the device.
				 *
				 * @return	.
				 */

				Glib::ustring ConvertToReadable(const Glib::ustring & deviceName);
				Smartmatic::SAES::Voting::ElectoralConfiguration *_electoralConfiguration;  ///< The electoral configuration
				Smartmatic::SAES::Configuration::ConfigurationInstallation configurationInstallation;   ///< The configuration intallation

				/**
				 * @brief	Add the header to the report
				 *
				 * @author	Freddy.Gomez
				 * @date	23/03/2011
				 *
				 *
				 */
				void AddHeader(Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

				/**
				 * @brief	Add the region info to the report
				 *
				 * @author	Freddy.Gomez
				 * @date	23/03/2011
				 *
				 *
				 */
				void AddRegions(Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

				/**
				 * @brief	Add the device status to the report
				 *
				 * @author	Freddy.Gomez
				 * @date	23/03/2011
				 *
				 *
				 */
				void AddDeviceStatus(Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

				/**
				 * @brief	Add the activation key to the report
				 *
				 * @author	Freddy.Gomez
				 * @date	23/03/2011
				 *
				 *
				 */
				void AddKeys(Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
						Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo);

				/**
				 * @brief	Gets the regions strings.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	votingBooth	The voting booth.
				 *
				 * @return	The regions strings.
				 */

				std::vector<Glib::ustring> GetRegionsStrings(const Smartmatic::SAES::Voting::VotingDevice::Voting_booth & votingBooth);
				bool installationReport;	///< true to installation report
				Glib::RefPtr<Gdk::Pixbuf> pixbufBarCode;
				bool isPasswordRetry;

				static Smartmatic::Log::ISMTTLog* logger; ///< logger
			};
		}
	}
}

#endif // _INSTALLATIONPRINTDOCUMENT_H_
