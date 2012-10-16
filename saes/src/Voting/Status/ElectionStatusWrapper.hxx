/**
 * @file	ElectionStatusWrapper.hxx
 *
 * @brief	election status wrapper class.
 */

#ifndef __ELECTION_STATUS_WRAPPER_H__
#define __ELECTION_STATUS_WRAPPER_H__

#include <iostream>
#include <list>
#include <Voting/Status/election-status-schema.hxx>


namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
          namespace Status
          {
            /**
             * @brief	Election status wrapper. 
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            class ElectionStatusWrapper
            {
            public:

               /**
                * @brief	Constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	elecStatus	The elec status.
                */

               ElectionStatusWrapper(ElectionStatus & elecStatus);

			   /**
			    * @brief	Gets the election status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The election status.
			    */

			   ElectionStatus & getElectionStatus();

			   /**
			    * @brief	Gets the eletion state.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The eletion state.
			    */

			   ProcessStatus &  getEletionState();

			   bool getSynchronizeVotes();

			   void setSynchronizeVotes(bool value);

			   /**
			    * @brief	Sets an eletion state.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param	newState	State of the new.
			    */

			   void  setEletionState(ProcessStatus newState);

			   /**
			    * @brief	Sets an election configuration report printed.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param	arg	if true print the report
			    */

			   void setElectionConfigurationReportPrinted(bool arg);

			   /**
			    * @brief	Gets the string status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The string status
			    */

			   std::string & getStringStatus();

			   /**
			    * @brief	Gets the opening code.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The opening code.
			    */

			   std::string & getOpeningCode();	

			   /**
			    * @brief	Sets the opening code.
			    *
			    * @author	Yadickson Soto
			    * @date	19/10/2011
			    *
			    * @param openingCode The opening code.
			    */

			   void setOpeningCode(std::string & openingCode);

			   /**
			    * @brief	Gets the voters registered in book.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The voters registered in book.
			    */

			   long long unsigned int & getVotersRegisteredInBook();

				/**
				 * @brief	Gets the operation mode code.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The operation mode code.
				 */

				std::string & getOperationModeCode();

				/**
				 * @brief	Gets the election configuration report printed.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The election configuration report printed.
				 */

				bool & getElectionConfigurationReportPrinted();

				/**
				 * @brief	Gets the open election date.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The open election date.
				 */

				std::string	 getOpenElectionDate();

				/**
				 * @brief	Gets the close election date.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @return	The close election date.
				 */

				std::string	 getCloseElectionDate();

				/**
				 * @brief	Gets the close voting date.
				 *
				 * @author	Freddy.Gomez
				 * @date	02/05/2011
				 *
				 * @return	The close voting date.
				 */

				std::string   getCloseVotingDate();

				/**
				 * @brief	Gets the contingency card's creation flag.
				 *
				 * @author	Marcel Cordoví
				 * @date	17/10/2011
				 *
				 * @return	void
				 */

				bool getContingencyCardCreated ();

               /**
                * @brief	Set the open election time
                *
                * @author	Freddy.Gomez
                * @date	02/05/2011
                *
                * @return void
                */

				void	 setOpenElectionDate(std::string openDate);

				/**
				 * @brief	Sets the close election date.
				 *
				 * @author	Freddy.Gomez
				 * @date	02/05/2011
				 *
				 * @return	void
				 */

				void	 setCloseElectionDate(std::string closeElectionDate);

				/**
				 * @brief	Sets the close voting date.
				 *
				 * @author	Freddy.Gomez
				 * @date	02/05/2011
				 *
				 * @return	void
				 */

				void	 setCloseVotingDate(std::string closeVotingDate);

				/**
				 * @brief	Sets the contingency card's creation flag.
				 *
				 * @author	Marcel Cordoví
				 * @date	17/10/2011
				 *
				 * @return	void
				 */

				void setContingencyCardCreated (bool contCardCreated);

               /**
                * @brief	Finaliser.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                */

               virtual ~ElectionStatusWrapper();

			private:
				ElectionStatus status;  ///< The status
            };
         }
      }
   }
}

#endif /*__ELECTION_STATUS_WRAPPER_H__*/
