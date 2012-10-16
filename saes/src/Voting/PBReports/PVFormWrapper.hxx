/**
 * @file	PVFormWrapper.hxx
 * @brief	Header pvform wrapper class.
 */

#ifndef _PVFORM_WRAPPER_H_
#define _PVFORM_WRAPPER_H_

#include "Voting/PBReports/pvform-schema.hxx"
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/operation-status.h>
#include <Voting/ElectoralConfiguration.hxx>
#include "pollworkers-wrapper.h"
#include "StatisticManager.hxx"
#include "activated-card-statistics-wrapper.h"
#include "assisted-activation-wrapper.h"
#include "vote-statistics.h"
#include "incident-report-wrapper.h"
#include "id-card-info-wrapper.h"
#include "closing-notes-wrapper.h"
#include "VotingDisabledWrapper.hxx"
#include "PoliceNoteWrapper.hxx"
#include <iostream>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/XSLFO/XSLFOTransformer.h>

namespace Smartmatic
{
    namespace Log
    {
        /**
         * @brief	SMTT Log Interface 
         *
         * @author	Yadickson Soto yadickson.soto@smartmatic.com
         * @date	05/05/2011
         */

        class ISMTTLog;
    }
  namespace SAES
  {
    namespace Voting
    {
      namespace PBReports
      {
        /**
         * @brief	Transmission package wrapper. 
         *
         * @author	Yadickson Soto yadickson.soto@smartmatic.com
         * @date	05/05/2011
         */

        class PVFormWrapper
        {
        private:

            /**
             * @brief	Default constructor.
             *
             * @author	Yadickson Soto yadickson.soto@smartmatic.com
             * @date	05/05/2011
             */

            PVFormWrapper();

            std::string durationElection; /**< duration electionduration of the election day*/
            Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; /**< electoral configuration*/
            Smartmatic::SAES::Voting::OperationStatus * operationStatus; /**< operation status*/
            PollworkersWrapper * pollWorkersWrapper; /**< pollworkers*/
            StatisticManager * statisticManager; /**< statistic manager*/
            AssistedActivationWrapper * assistedActivationWrapper; /**< assisted activation wrapper*/
            VotingDisabledWrapper * votingDisabledWrapper; ///< voting disabled wrapper
            ActivatedCardStatisticsWrapper * activatedCardStatisticsWrapper; /**< activated card statistics*/
            VoteStatisticsWrapper * voteStatisticsWrapper; /**< vote statistics wrapper*/
            IncidentReportWrapper * incidentReportWrapper; /**< incident report wrapper*/
            ClosingNotesWrapper * closingNotesWrapper; /**< closing notes wrapper*/
            IDCardInfoWrapper * idCardInfoWrapper; /**< ID Card Info Wrapper*/
            PoliceNoteWrapper * policeNoteWrapper; ///< Police Note Wrapper
            std::string fileFullPath; ///< file full path dom
            static PVFormWrapper * instance;   ///< The instance
            Smartmatic::System::XSLFO::XSLFOTransformer * transformer;
			static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

        public:

          /**
           * @brief	Initialises this object.
           *
           * @author	Yadickson Soto yadickson.soto@smartmatic.com
           * @date	05/05/2011
           */

          void init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
                  Smartmatic::SAES::Voting::OperationStatus * operationStatus,
                  PollworkersWrapper * pollWorkersWrapper,
                  StatisticManager * statisticManager,
                  AssistedActivationWrapper * assistedActivationWrapper,
                  ActivatedCardStatisticsWrapper * activatedCardStatisticsWrapper,
                  VoteStatisticsWrapper * voteStatisticsWrapper,
                  IncidentReportWrapper * incidentReportWrapper,
                  ClosingNotesWrapper * closingNotesWrapper,
                  IDCardInfoWrapper * idCardInfoWrapper,
                  VotingDisabledWrapper * votingDisabledWrapper,
                  PoliceNoteWrapper * policeNoteWrapper)
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          /**
           * @brief	Dispose of this object, cleaning up any resources it uses.
           *
           * @author	Yadickson Soto yadickson.soto@smartmatic.com
           * @date	05/05/2011
           */

          void dispose();

          /**
           * @brief	Finaliser.
           *
           * @author	Yadickson Soto yadickson.soto@smartmatic.com
           * @date	05/05/2011
           */

          virtual ~PVFormWrapper();

          bool persistencePVForm(Smartmatic::System::XSLFO::XSLFOTransformer * transformer)
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          bool persistence(std::string & pvformFileDom,
        			std::string & pvformFileFlash,
        			std::string & pvreportFileDom,
        			std::string & pvreportFileFlash,
        			std::string & pvtemplateFile)
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          /**
           * @brief	Persist the transmission package.
           *
           * @author	Yadickson Soto yadickson.soto@smartmatic.com
           * @date	05/05/2011
           *
           */

          void persistence()
              throw (Smartmatic::System::Exception::CryptoException,
                     Smartmatic::System::Exception::SignedException,
                     Smartmatic::System::Exception::XmlException);

          /**
           * @brief Method setter file
           * @param fileFullPath file full path dom.
           * @param fileFullPathFlash file full path flash.
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  13/05/2011
           */
          void setFileFullPath(std::string fileFullPath);

          /**
           * @brief Method setter duration election.
           * @param durationElection duration election.
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  07/05/2011
           */
          void setDurationElection(std::string durationElection);

          /**
           * @brief Method getter duration election.
           * @return duration election.
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  07/05/2011
           */
          std::string getDurationElection();

          bool validate();

          /**
           * @brief Method getter languages
           * @return languages
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  16/06/2011
           */
          std::list <std::string> getLanguages();

          /**
           * @brief Method getter pv file names
           * @param file file name
           * @fileNames result pv file names
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  02/03/2012
           */
          void getPVFileNames(std::string file, std::list <std::string> & fileNames);

          /**
           * @brief Method delete all files
           * @author    Yadickson Soto yadickson.soto@smartmatic.com
           * @date  02/03/2012
           */
          void deleteFiles();

          /**
           * @brief	Gets the instance.
           * @return    instance of class.
           * @author	Yadickson Soto yadickson.soto@smartmatic.com
           * @date	05/05/2011
           */

          static PVFormWrapper * getInstance();

        };
      }
    }
  }
}

#endif /* _PVFORM_WRAPPER_H_ */
