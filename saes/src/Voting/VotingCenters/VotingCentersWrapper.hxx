/**
 * @file VotingCentersWrapper.hxx
 * @brief Header class voting centers
 */

#ifndef _VOTING_CENTERS_WRAPPER_H_
#define _VOTING_CENTERS_WRAPPER_H_

#include "Voting/VotingCenters/voting-centers-schema.hxx"
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <iostream>
#include <list>

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
      namespace VotingCenters
      {
        /**
         * @brief	Voting centers wrapper. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class VotingCentersWrapper
        {
        private:

            /**
             * @brief	Default constructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            VotingCentersWrapper();
            static VotingCentersWrapper * instance; ///< The instance

        public:

            bool isInstall();

            Smartmatic::SAES::Common::Configuration::BasePathType getMasterDevice();

          /**
           * @brief	Gets the voting centers.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @return	The voting centers.
           */

          std::list <VotingCenter> & getVotingCenters();

          /**
           * @brief	Sets an installation voting device.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @param [in,out]	votingCenter	The voting center.
           */

          void setInstallationVotingCenter(VotingCenter &votingCenter);

          void getInstallationVotingCenter(VotingCenter &votingCenter);

          /**
           * @brief	Finaliser.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           */

          virtual ~VotingCentersWrapper();

          /**
           * @brief	Persist voting devices.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           */

          void persistVotingCenters()
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          /**
           * @brief	Gets the instance.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @return	null if it fails, else the instance.
           */

          static VotingCentersWrapper * getInstance();

          /**
           * @brief	Loads a file.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @param	filePath	Full pathname of the file.
           *
           * @return	true if it succeeds, false if it fails.
           */

          bool LoadFile(std::string filePath);

        private:
          bool install;
          Smartmatic::SAES::Common::Configuration::BasePathType type;
          VotingCenter votingCenter;	///< The voting center
          std::list <VotingCenter> votingCenters;   ///< The voting centers
		  static Smartmatic::Log::ISMTTLog* logger; ///< The logger
        };
      }
    }
  }
}

#endif /* _VOTING_CENTERS_WRAPPER_H_ */
