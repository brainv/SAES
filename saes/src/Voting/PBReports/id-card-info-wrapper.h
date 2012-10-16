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

#ifndef _ID_CARD_INFO_WRAPPER_H_
#define _ID_CARD_INFO_WRAPPER_H_

#include <Voting/PBReports/id-card-info-schema.hxx>
#include <Voting/PBReports/id-card-members-schema.hxx>
#include <eid/CitizenInfo.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Runtime/Environment/saes-directories.h>

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
			 * @brief	Header class IDCardInfoWrapper.
			 *
			 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
			 * @date	29-03-2011
			 */

			class IDCardInfoWrapper
			{
			private:
					//IDCardInfo* idCardInfo;
                static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

			public:

                /**
                 * @brief   Class constructor.
                 *
                 * @author  Eduardo.campione
                 * @date    28/04/2011
                 */

                IDCardInfoWrapper();

				/**
				 * @brief	Class destroyer.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				~IDCardInfoWrapper();

				/**
				 * @brief	Generates an identifier card information wrapper.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	citizenInfo	Information describing the citizen.
				 *
				 * @return	The identifier card information wrapper.
				 */

				static void generateIdCardInfoWrapper(Smartmatic::SAES::EID::CitizenInfo &citizenInfo, IDCardInfo & info);
				static void generateCitizenInfo(IDCardInfo & idCardInfo, Smartmatic::SAES::EID::CitizenInfo & citizenInfo);

				bool init(Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDirectories)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);


				void addPMInstallIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);

				void addVMInstallIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);

				void addOpenElectionIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);

				void addCloseVotingIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);

				void addCloseElectionIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
					throw (Smartmatic::System::Exception::CryptoException,
										Smartmatic::System::Exception::SignedException,
										Smartmatic::System::Exception::XmlException);

				void persistence()
					throw (Smartmatic::System::Exception::CryptoException,
							Smartmatic::System::Exception::SignedException,
							Smartmatic::System::Exception::XmlException);

				IDCardMembers * getIdCardMembers();

				bool isInstallPM();

			private:

				Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDirectories;
				IDCardMembers * idCardMembers;

				/**
				 * @brief	Serialize identifier card information wrapper.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	citizenInfo	Information describing the citizen.
				 *
				 * @return	.
				 */

				std::string serializeIdCardInfoWrapper(Smartmatic::SAES::EID::CitizenInfo &citizenInfo);

				bool loadMembersFile()
					throw (Smartmatic::System::Exception::CryptoException,
							Smartmatic::System::Exception::SignedException,
							Smartmatic::System::Exception::XmlException);

				void persistenceInfo(IDCardInfo & info)
					throw (Smartmatic::System::Exception::CryptoException,
							Smartmatic::System::Exception::SignedException,
							Smartmatic::System::Exception::XmlException);
			};
		 }
	  }
   }
}

#endif // _ID_CARD_INFO_WRAPPER_H_
