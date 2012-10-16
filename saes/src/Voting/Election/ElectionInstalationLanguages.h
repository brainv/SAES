/*
 * ElectionInstalationLanguages.h
 *
 *  Created on: Mar 10, 2011
 *      Author: freddyg
 */

#ifndef ELECTIONINSTALATIONLANGUAGES_H_
#define ELECTIONINSTALATIONLANGUAGES_H_

#include "Voting/Election/election-language-schema.hxx"
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
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
      namespace Election
      {
        /**
         * @brief	Election instalation languages. 
         *
         * @author	Eduardo.campione
         * @date	28/04/2011
         */

        class ElectionInstalationLanguages
        {
        private:

            /**
             * @brief	Default constructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            ElectionInstalationLanguages();
            static ElectionInstalationLanguages * instance; ///< The instance of the Election Instalation Languages

        public:

          /**
           * @brief	Gets the languages.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @return	The languages.
           */

          std::list<Smartmatic::SAES::Voting::Election::Language> getLanguages();

          /**
           * @brief	Sets an installation languages.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @param [in,out]	lang	The language.
           */

          void setInstallationLanguages(Smartmatic::SAES::Voting::Election::Language& lang);

          /**
           * @brief	Adds an installation languages. 
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @param [in,out]	lang	The language.
           */

          void addInstallationLanguages(Smartmatic::SAES::Voting::Election::Language& lang);

          /**
           * @brief	Finaliser.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           */

          virtual ~ElectionInstalationLanguages();

          /**
           * @brief	Persist language.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           */

          void persistLanguage()
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          /**
           * @brief Method getter all string languages.
           *
           * @author Yadickson Soto yadickson.soto@smartmatic.com
           * @date  11/05/2011
           *
           * @return list string languages in format ll_CC
           */

          std::list <std::string> getStringLanguages();

          void clearLanguage();

          void ReloadLanguages();

          /**
           * @brief	Gets the instance.
           *
           * @author	Eduardo.campione
           * @date	28/04/2011
           *
           * @return	null if it fails, else the instance.
           */

          static ElectionInstalationLanguages * getInstance();

          static std::list<Smartmatic::SAES::Voting::Election::Language> GetOperatingLanguages(std::list<Smartmatic::SAES::Voting::Election::Language> allLang);
        private:
            std::list<Smartmatic::SAES::Voting::Election::Language> languages;  ///< The languages

            /**
             * @brief	Loads a file.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param	file	The file.
             *
             * @return	true if it succeeds, false if it fails.
             */

            bool LoadFile(std::string file);
			static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
        };
      }
    }
  }
}

#endif /* ELECTIONINSTALATIONLANGUAGES_H_ */
