/**
 * @file	TransmissionPackageWrapper.hxx
 *
 * @brief	transmission package wrapper class.
 */

#ifndef _TRANSMISSION_PACKAGES_WRAPPER_H_
#define _TRANSMISSION_PACKAGES_WRAPPER_H_

#include <Voting/Vote/transmission-package-schema.hxx>
#include <Voting/ElectoralConfiguration.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/CodiException.hxx>
#include <Voting/Codi/CodiFileWrapper.hxx>
#include "StationTallyWrapper.hxx"
#include <iostream>
#include <list>

namespace Smartmatic
{
    namespace Log
    {
        /**
         * @brief	SMTT Log Interface 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class ISMTTLog;
    }
  namespace SAES
  {
    namespace Voting
    {
      namespace Vote
      {
        /**
         * @brief	Transmission package wrapper. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class TransmissionPackageWrapper
        {
        private:

            /**
             * @brief	Default constructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            TransmissionPackageWrapper();
            static TransmissionPackageWrapper * instance;   ///< The instance
            std::list<Vote> votes;  ///< The votes
            std::list<Vote> demoVotes;  ///< The demo votes
			static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

        public:

          /**
           * @brief	Init class
           * @param electoralConfiguration electoral configuration
           * @param directories saes directories
           * @author Yadickson Soto
           * @date	17/02/2012
           */

          void init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
					Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories);

          /**
           * @brief	Dispose of this object, cleaning up any resources it uses.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           */

          void dispose();

          /**
           * @brief	Adds a vote. 
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @param [in,out]	vote	The vote.
           */

          void addVote(Vote & vote);

          /**
           * @brief	Method delete vote in list
           * @author	Yadickson Soto
           * @date	17/02/2012
           */
          void deleteVotes();

          /**
           * @brief getter all votes.
           *
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  05/05/2011
           *
           * @return list all vote
           */

          const std::list<Vote> & getAllVote();

          /**
           * @brief getter all vote demo.
           *
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  05/05/2011
           *
           * @return list all vote demo
           */

          const std::list<Vote> & getAllVoteDemo();

          /**
           * @brief	Finaliser.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           */

          virtual ~TransmissionPackageWrapper();

          /**
           * @brief	Persist the transmission package.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           */

          void persistTransmissionPackage()
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException,
                     Smartmatic::System::Exception::CodiException);

          /**
           * @brief	Method validate files
           * @return true is validate files
           * @author	Yadickson Soto
           * @date	17/02/2012
           */
          bool validate();

          /**
           * @brief	Method delete files
           * @author	Yadickson Soto
           * @date	17/02/2012
           */
          void deleteFiles();

          /**
           * @brief Gets the instance.
           *
           * @author    Eduardo.campione
           * @date  28/04/2011
           *
           * @return    null if it fails, else the instance.
           */

          static TransmissionPackageWrapper * getInstance();

        private:

          Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///< electoral configuration
          Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories; ///< saes directories
          Smartmatic::SAES::Voting::Codi::CodiFileWrapper * codiFiles; ///< codi files wrapper
          StationTallyWrapper * stationTally; ///< station tally info
          bool enableCodi; ///< flag enable result codi

          void persistTransmissionPackageSecretKey(std::string & data)
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          void persistTransmissionPackageAsimetricKey(std::string & data)
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          void persistTransmissionPackageHash()
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);
        };
      }
    }
  }
}

#endif /* _TRANSMISSION_PACKAGES_WRAPPER_H_ */
