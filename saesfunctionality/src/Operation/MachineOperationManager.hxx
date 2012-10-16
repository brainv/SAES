/**
 * @file	MachineOperationManager.hxx
 *
 * @brief	machine operation manager class.
 */

#ifndef _MACHINE_OPERATION_MANAGER_H_
#define _MACHINE_OPERATION_MANAGER_H_

#include <Log/LogBasePath.hxx>
#include "Initiator/IMachineInitiator.hxx"
#include "Authenticator/IAuthenticator.hxx"
#include "Voting/VotingExperienceController.hxx"
#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/operation-status.h>
#include "Voting/PBReports/pollworkers-wrapper.h"
#include "Voting/PBReports/activated-card-statistics-wrapper.h"
#include "Voting/PBReports/assisted-activation-wrapper.h"
#include "Voting/PBReports/closing-notes-wrapper.h"
#include "Voting/PBReports/incident-report-wrapper.h"
#include <Runtime/Environment/saes-directories.h>
#include <Runtime/Environment/SaesInstallDirectories.hxx>
#include <Operation/Alarm/AlarmController.hxx>
#include <System/SafeBuffer.h>
#include <Voting/Vote/vote-schema.hxx>
#include <Voting/PBReports/vote-statistics.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/VoteException.hxx>
#include <System/Exception/SignByCardIDException.h>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/GuIdException.h>
#include <System/Exception/CodiException.hxx>
#include <System/Exception/FileSystemException.hxx>
#include <Log/ISMTTLog.h>
#include <Voting/PBReports/id-card-info-schema.hxx>
#include <eid/CitizenInfo.h>
#include <Voting/PBReports/StatisticManager.hxx>
#include <System/XSLFO/XSLFOTransformer.h>
#include <glibmm.h>
#include <pthread.h>
#include <Voting/PBReports/id-card-info-wrapper.h>
#include <Voting/Vote/StationTallyWrapper.hxx>
#include <Voting/PBReports/VotingDisabledWrapper.hxx>
#include <Voting/PBReports/PoliceNoteWrapper.hxx>

namespace Smartmatic
{
  namespace SAES
  {
    namespace Operation
    {
	  class PersistSortFile;
	  class InstallMachine;
	  class SaesEnqueuer;
      /**
       * @brief	Header class MachineOperationManager.
       * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
       * @date	02-03-2011
       */

      class MachineOperationManager
      {
      private:

        /**
         * @brief	Class constructor.
         */

        MachineOperationManager();

        static MachineOperationManager * instance;  ///< instance of class MachineOperationManager
        Smartmatic::SAES::Operation::Initiator::IMachineInitiator * machineInitiator;   ///< instance of object machine initiator
        Smartmatic::SAES::Operation::Authenticator::IAuthenticator * authenticator; ///< instance of object authnticator
        Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;  ///< instance of object electoral configuration
		Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * pollworkers;  ///< instance of object pollworkers list
		Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * activatedCardStatistics;	///< instance of object activated card statistics list
		Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * incidentReport;	///< instance of object incident report list
		Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * assistedActivation;	///< instance of object assisted activation list
		Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * closingNotes;	///< instance of object closing notes list
        Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDirectories;  ///< instance of object SAES directories
        Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * saesInstallDirectories;
        Smartmatic::SAES::Voting::OperationStatus * operationStatus;	///< instance of object operation status
        Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController;   ///< instance of object voting experience controller
        Smartmatic::SAES::Operation::Alarm::AlarmController * alarmController; ///< instance of object alarm controller
        Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * voteStatistics;   ///< instance of vote statistics
        Smartmatic::SAES::Voting::PBReports::StatisticManager * statisticManager;    ///< instance of object statistic manager
        Smartmatic::SAES::Voting::PBReports::VotingDisabledWrapper * votingDisabledWrapper;    ///< instance of object voting disabled wrapper
        Smartmatic::SAES::Voting::PBReports::PoliceNoteWrapper * policeNoteWrapper;    ///< instance of object police note wrapper
        Smartmatic::SAES::Log::LogBasePath * basePathDom;
        Smartmatic::SAES::Log::LogBasePath * basePathFlash;
        Smartmatic::System::XSLFO::XSLFOTransformer * pvtransformer;
        Smartmatic::SAES::Voting::PBReports::IDCardInfoWrapper * idCardInfoWrapper;

		sigc::connection conn;  ///< connection
		sigc::connection connDetected;  ///< detected connection 
			  
      public:

		enum MemoryEvent
		{
			  ONE_MEMORY
			 ,TWO_MEMORY
			 ,CHECK_MEMORY_OK
			 ,CHECK_MEMORY_ERROR
			 ,ERROR_MEMORY
		};

        enum MemoryBehavior
        {
        	MemoryBehavior_Block,
        	MemoryBehavior_Suspend,
        	MemoryBehavior_Allow
        };

		sigc::signal<void, MemoryEvent, MemoryBehavior> signalMemoryEvent;   ///< The signal extracted detected

        void emitSignal();

		/**
		 * @brief	Starts a detection.
		 */

		void StartDetection();

		/**
		 * @brief	Stop detection.
		 */

		void StopDetection();
		void signalDetectChangeDevice();
		/**
         * @brief   Detect extract.
         */

        void DetectExtract();

        void startInitialization();

        void checkDataDevice();

        /**
         * @brief	Finaliser.
         */

        ~MachineOperationManager();

        /**
         * @brief	method to set machine initiator instance.
         * @param [in,out]	machineInitiator	object machine initiator.
         */

        void setMachineInitiator( Smartmatic::SAES::Operation::Initiator::IMachineInitiator * machineInitiator );

        /**
         * @brief	method to get machine initiator instance.
         * @return	machine initiator instance.
         */

        Smartmatic::SAES::Operation::Initiator::IMachineInitiator * getMachineInitiator();

        /**
         * @brief	method to get SaesEnqueuer instance.
         * @return	SaesEnqueuer instance.
         */

        SaesEnqueuer * getSaesEnqueuer();

        /**
         * @brief	method to set authenticator instance.
         * @param [in,out]	authenticator	object authenticator.
         */

        void setAuthenticator( Smartmatic::SAES::Operation::Authenticator::IAuthenticator * authenticator );

        /**
         * @brief	method to get authenticator instance.
         * @return	authenticator instance.
         */

        Smartmatic::SAES::Operation::Authenticator::IAuthenticator * getAuthenticator();

        /**
         * @brief	method to set the electoral configuration instance.
         * @param [in,out]	electoralConfiguration	object electoral configuration.
         */

        void setElectoralConfiguration( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration );

        /**
         * @brief	method to set pollworkers list instance.
         * @param [in,out]	pollworkers	object pollworkers.
         */

        void setPollworkers( Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * pollworkers );			   

        /**
         * @brief	method to get pollworkers.
         * @return	pollworkers instance.
         */

        Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * getPollworkers();	
		 /**
         * @brief	method to set activated card statistics list instance.
         * @param [in,out]	activated card statistics	object activated card statistics.
         */

        void setActivatedCardStatistics( Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * activatedCardStatistics );	
		 /**
         * @brief	method to get activated card statistics.
         * @return	activated card statistics instance.
         */

        Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * getActivatedCardStatistics();	

        /**
         * @brief	method to set assisted activation list instance.
         * @param [in,out]	assistedActivation	activation object assisted activation.
         */

        void setAssistedActivation( Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * assistedActivation );			   

        /**
         * @brief	method to get assisted activation.
         * @return	assisted activation instance.
         */

        Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * getAssistedActivation();	

        /**
         * @brief	method to set closing notes list instance.
         * @param [in,out]	closingNotes	notes object closing notes.
         */

        void setClosingNotes( Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * closingNotes );			   

        /**
         * @brief	method to get the closing notes.
         * @return	closing notes instance.
         */

        Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * getClosingNotes();	

        /**
         * @brief	method to set incident report list instance.
         * @param [in,out]	incidentReport	report object incident report.
         */

        void setIncidentReport( Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * incidentReport );			   

        /**
         * @brief	method to get incident report.
         * @return	incident report instance.
         */

        Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * getIncidentReport();			  

        /**
         * @brief	method to get electoral configuration.
         * @return	electoral configuration instance.
         */

        Smartmatic::SAES::Voting::ElectoralConfiguration * getElectoralConfiguration();

        /**
         * @brief	method to get saes directories.
         * @return	saes directories instance.
         */

        Smartmatic::SAES::Runtime::Environment::SaesDirectories * getSaesDirectories();

        Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * getSaesInstallDirectories();

        /**
         * @brief	method to set operation status.
         * @param [in,out]	operationStatus	object operation status.
         */

        void setOperationStatus( Smartmatic::SAES::Voting::OperationStatus * operationStatus );

        /**
         * @brief	method to get operation status.
         * @return	operation status instance.
         */

        Smartmatic::SAES::Voting::OperationStatus * getOperationStatus();

        /**
         * @brief	method to set voting experience controller.
         * @param [in,out]	votingExperienceController	object voting experience controller.
         */

        void setVotingExperienceController( Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController );

        /**
         * @brief	method to get voting experience controller.
         * @return	voting experience controller instance.
         */

        Smartmatic::SAES::Operation::Voting::VotingExperienceController * getVotingExperienceController();

        /**
         * @brief	Gets the alarm controller.
         * @return	null if it fails, else the alarm controller.
         */

        Smartmatic::SAES::Operation::Alarm::AlarmController * getAlarmController();

		/**
		 * @brief	method to get machine operation code.
		 * @return	string machine operation code.
		 */

		std::string getMachineOperationCode();


		enum VoteFromSafeBufferResult
		{
			VOTE_FROM_BUFFER_SUCCESS,
			VOTE_FROM_BUFFER_DECOMPRESSION_ERROR,
			VOTE_FROM_BUFFER_DECRYPTO_ERROR,
			VOTE_FROM_BUFFER_SIGNATURE_ERROR,
			VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR,
			VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE,
			VOTE_FROM_BUFFER_INVALID_LVG,
			VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE,
			VOTE_FROM_BUFFER_UNEXPECTED_ERROR
		};

        /**
         * @brief	creates a vote from a SafeBuffer.
         * @param [in,out]	safeBuffer	from which to  extract vote, vote by reference to store data.
         * @param [in,out]	vote	  	The vote.
         * @return	The vote from safe buffer.
         */

        VoteFromSafeBufferResult getVoteFromSafeBuffer(
        		Smartmatic::System::SafeBuffer& safeBuffer,
        		Smartmatic::SAES::Voting::Vote::Vote *& vote,
        		bool inflate = true);

        /**
         * @brief	method for persistence vote.
         * @param [in,out]	vote	vote to persistence.
         */

        bool persistenceVote(Smartmatic::SAES::Voting::Vote::Vote & vote)
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        /**
         * @brief	method for persistence vote.
         * @param [in,out]	Safebuffer	vote to persistence.
         */

        bool persistenceVote(Smartmatic::System::SafeBuffer & buffer)
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        void deleteVote(Smartmatic::SAES::Voting::Vote::Vote & vote);

        /**
         * @brief	method for persistence vote in file system.
         */

        void persistenceFileSystemVote();

		/**
         * @brief	method for persistence PMInstallerData
         * @param [in,out]	citizenInfo	Information describing the citizen.
         */

		void PersistencePMInstallerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
				throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);
        /**
         * @brief	method for persistence InstallerData
         * @param [in,out]	citizenInfo	Information describing the citizen.
         */

        void PersistenceInstallerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
			throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

		/**
		 * @brief	Persistence opener data.
		 * @param [in,out]	citizenInfo	Information describing the citizen.
		 */

		void PersistenceOpenerData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
			throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

		/**
		 * @brief	Persistence voting closer data.
		 * @param [in,out]	citizenInfo	Information describing the citizen.
		 */

		void PersistenceVotingCloserData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
			throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

		  /**
		   * @brief	Persistence election closer data.
		   * @param [in,out]	citizenInfo	Information describing the citizen.
		   */

		  void PersistenceElectionCloserData(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
			throw (Smartmatic::System::Exception::CryptoException,
		        Smartmatic::System::Exception::SignedException,
		        Smartmatic::System::Exception::XmlException);

		  /**
		   * @brief	Generates a transmission package signal file.
		   */

		  void generateTransmissionPackageSigFile()
			throw (Smartmatic::System::Exception::CryptoException,
		        Smartmatic::System::Exception::SignedException,
		        Smartmatic::System::Exception::XmlException,
			       Smartmatic::System::Exception::SignByCardIDException);

          /**
           * @brief Generates a signal file.
           */
		  void generateSigFile(Smartmatic::System::SafeBuffer & buffer, std::string fileDestination)
          throw (Smartmatic::System::Exception::CryptoException,
              Smartmatic::System::Exception::SignedException,
              Smartmatic::System::Exception::XmlException,
              Smartmatic::System::Exception::SignByCardIDException);

          /**
         * @brief	method to set vote statistics.
         * @param [in,out]	voteStatistics	vote statistics.
         */

        void setVoteStatistics(Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * voteStatistics);

        /**
         * @brief	method to get vote statistics.
         * @return	vote statistics.
         */

        Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * getVoteStatistics();

        /**
         * @brief   method getter statistic manager.
         * @return  statistic manager.
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    04-05-2011
         */
        Smartmatic::SAES::Voting::PBReports::StatisticManager * getStatisticManager();
        /**
         * @brief   method getter voting disabled wrapper
         * @return  voting disabled wrapper
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    21-05-2012
         */
        Smartmatic::SAES::Voting::PBReports::VotingDisabledWrapper * getVotingDisabledWrapper();
        /**
         * @brief   method getter police note wrapper
         * @return  police note wrapper
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    25-05-2012
         */
        Smartmatic::SAES::Voting::PBReports::PoliceNoteWrapper * getPoliceNoteWrapper();
       /**
         * @brief   method setter statistic manager.
         * @param   statisticManager  statistic manager.
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    04-05-2011
         */
        void setStatisticManager (Smartmatic::SAES::Voting::PBReports::StatisticManager * statisticManager);
        /**
         * @brief	method to load, validate and count votes.
         */

        bool checkVotes(int deltaP = 1);

        /**
         * @brief	configuration reset.
         */

        void configurationReset();

        /**
         * @brief Method authentication machine
         * @author Yadickson Soto yadickson.soto@smartmatic.com
         * @date 18/10/2011
         * @param center
         * @param password
         * @param centerCaseSensitive
         * @return true is success
         */
        bool authentication(std::string & center, std::string & password, bool centerCaseSensitive);

        bool install();

        std::list<Smartmatic::SAES::Voting::Election::Language> getLanguagesElection();
        std::list<Smartmatic::SAES::Voting::Election::Language> getLanguagesInstall();

        /**
         * @brief method start up machine
         */
        void startUp()
            throw (Smartmatic::System::Exception::ElectionException,
    				Smartmatic::System::Exception::VotingDeviceException,
    				Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException,
                    Smartmatic::System::Exception::GuIdException,
                    Smartmatic::System::Exception::VoteException,
                    Smartmatic::System::Exception::FileSystemException);


        void createMachineId(bool force = false);
        bool validateMachineId();
        bool checkMachineId();
        bool checkIdCardMembers();
        bool checkPVReport();

        /**
         * @brief Method for check transmission package files
         * @return true is valid files
         * @date 17/02/2012
         * @author Yadickson Soto
         */
        bool checkTransmissionPackages();

        /**
         * @brief   Gets vote flash is valid.
         *
         * @author  Yadickson Soto yadickson.soto@smartmatic.com
         * @date    23/05/2011
         *
         * @return  true if it succeeds, false if it fails.
         */
        bool validateVotes();

        /**
         * @brief method for validate election status
         * @return true if success
         */
        bool checkElectionStatus();

        bool checkSAESFiles();
        bool checkSAESLocal();
        bool checkVoteStatistics();
        bool checkElection();
        bool checkVotingDevices();
    	bool checkActivatedCardStatistics();
    	bool checkAssistedActivations();
    	/**
    	 * @brief method check voting disabled file
    	 * @return true is success
    	 * @date 21/05/2012
    	 * @author Yadickson Soto
    	 */
    	bool checkVotingDisabled();
    	/**
    	 * @brief method check police notes file
    	 * @return true is success
    	 * @date 25/05/2012
    	 * @author Yadickson Soto
    	 */
    	bool checkPoliceNotes();
    	bool checkPollworkers();
    	bool checkSignature();
    	bool checkClosingNotes();
    	bool checkStatistics();
    	bool checkTechnicalTroubles();
    	bool checkVotingDeviceStatus();

        void installMachine()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        void registerPollworker()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        void demostrationVote()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        /**
         * @brief	Opens the election.
         */

        void openElection()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        /**
         * @brief	Closes the election.
         */

        void closeElection()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        /**
         * @brief	Closes the voting experience.
         */

        void closeVotingExperience()
            throw (Smartmatic::System::Exception::CryptoException,
                    Smartmatic::System::Exception::SignedException,
                    Smartmatic::System::Exception::XmlException);

        /**
         * @brief   Query if this object is not installed
         * @return  true if not installed
         */

        bool isNotInstalled();

        /**
         * @brief   Query if this object is not pollworker registered
         * @return  true if not pollworker registered
         */

        bool isNotPollworkerRegistered();

        /**
         * @brief   Query if this object is not demostration vote
         * @return  true if not demostration vote
         */

        bool isNotDemostrationVote();

        /**
         * @brief	Query if this object is open election.
         * @return	true if open election, false if not.
         */

        bool isOpenElection();

        bool votingIsPossible();

        /**
         * @brief	Query if this is not an initiated election.
         * @return	true if not initiated election, false if not.
         */

        bool isNotInitiatedElection();

        /**
         * @brief	Query if this is a close election.
         * @return	true if close election, false if not.
         */

        bool isCloseElection();

        /**
         * @brief	Query if this is a close voting experience.
         * @return	true if close voting experience, false if not.
         */

        bool isCloseVotingExperience();

        bool isPrintingInstallReport();

        void setOpeningCode(std::string & openingCode);

		/**
		 * @brief	Method persist all result files.
		 * @date 17/02/2012
		 * @author Yadickson Soto
		 */
		void persistAllResult()
		    throw (Smartmatic::System::Exception::CryptoException,
		            Smartmatic::System::Exception::SignedException,
		            Smartmatic::System::Exception::XmlException,
		            Smartmatic::System::Exception::CodiException);

        /**
         * @brief   Persist pv form.
         */

        void persistPVForm()
            throw (Smartmatic::System::Exception::CryptoException,
                   Smartmatic::System::Exception::SignedException,
                   Smartmatic::System::Exception::XmlException,
                   Smartmatic::System::Exception::SignByCardIDException);

        void generatePVFormSigFile( bool copyToFile = true )
            throw (Smartmatic::System::Exception::CryptoException,
                   Smartmatic::System::Exception::SignedException,
                   Smartmatic::System::Exception::XmlException,
                   Smartmatic::System::Exception::SignByCardIDException);


        void signElectionResults(bool sign = true, bool copyToFile = true )
                    throw (Smartmatic::System::Exception::CryptoException,
                           Smartmatic::System::Exception::SignedException,
                           Smartmatic::System::Exception::XmlException,
                           Smartmatic::System::Exception::SignByCardIDException);


        /**
          * @brief	Saves the electoral configuration report printed.
          */

         void saveElectoralConfigurationReportPrinted();

         void saveElectoralConfigurationContingencyCardCreated();

         void deleteCloseFiles();

         void saveVoteInOneMemory()
			throw (Smartmatic::System::Exception::CryptoException,
					Smartmatic::System::Exception::SignedException,
					Smartmatic::System::Exception::XmlException);

         void restoreVoteInAllMemory()
			throw (Smartmatic::System::Exception::CryptoException,
					Smartmatic::System::Exception::SignedException,
					Smartmatic::System::Exception::XmlException);

        /**
         * @brief	Gets an instance of the clas.
         * @return	null if it fails, else the instance.
         */

        static MachineOperationManager * getInstance();

        void SetBlockMemoryBehavior(MemoryBehavior behavior);

        Smartmatic::SAES::Log::LogBasePath * getLogBasePathDom();

        Smartmatic::SAES::Log::LogBasePath * getLogBasePathFlash();

        Smartmatic::SAES::Voting::PBReports::IDCardInfoWrapper * getIDCardInfoWrapper();


        /**
         * @brief Method for load station tally
         * @date 17/02/2012
         * @author Yadickson Soto
         */
        void loadStationTally()
			throw (Smartmatic::System::Exception::CryptoException,
					Smartmatic::System::Exception::SignedException,
					Smartmatic::System::Exception::XmlException);

        /**
         * @brief Method exit machine
         * @date 23/02/2012
         * @author Yadickson Soto
         */
        void exitMachine();

      private:
        /**
         * @brief   Gets signal console.
         * @param sig number signal
         */

        static void signalHandler(int sig);

        void setMemoryEvent(MemoryEvent memoryEvent);

        bool handleDetection;
        bool isCheckData;

        MemoryBehavior behavior;

        bool startFirstTime; ///< flag star first time
        bool beforeInitialization;

        PersistSortFile * sortDomFile;
        PersistSortFile * sortFlashFile;
        InstallMachine * objInstallMachine;
        SaesEnqueuer * saesEnqueuer; ///< saes enqueuer

        Glib::Mutex mutex;
        Glib::Mutex mutexVote;

		static pthread_mutex_t mutexSignal;
		bool loadOpeninCode;
		bool checkDataResult; ///< result check data
        static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
      };
    }
  }
}

#endif // _MACHINE_OPERATION_MANAGER_H_
