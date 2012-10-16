/**
 * @file	StationTallyWrapper.hxx
 *
 * @brief	station tally wrapper class.
 */

#ifndef __STATION_TALLY_WRAPPER_H__
#define __STATION_TALLY_WRAPPER_H__

#include <map>
#include <list>
#include <Voting/Vote/station-tally-schema.hxx>
#include <Voting/Vote/vote-schema.hxx>
#include <Voting/Election/election-schema.hxx>
#include <System/Exception/StationTallyException.hxx>
#include <Voting/Codi/CodiFile.h>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
		 class ElectoralConfiguration;

         namespace Vote
         {

            /**
             * @brief	Station tally wrapper. 
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            class StationTallyWrapper
            {
            public:

               /**
                * @brief	Default constructor.
                * @param electoralConfiguration electoral configuration
                * @param enableCodi enable codi result
                * @author	Yadickson Soto
                * @date	28/04/2011
                */

               StationTallyWrapper(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, bool enableCodi);

               /**
                * @brief	Finaliser.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                */

               virtual ~StationTallyWrapper();

               /**
                * @brief Method add vote for update info
                * @param vote vote
                * @date 17/02/2012
                * @author Yadickson Soto
                */
               void update (Vote & vote);

               /**
                * @brief Method init info
                * @date 17/02/2012
                * @author Yadickson Soto
                */
               void init();

               /**
                * @brief Method clear info
                * @date 17/02/2012
                * @author Yadickson Soto
                */
               void clear();

               /**
                * @brief Method get station tally list
                * @param list station tally list
                * @date 17/02/2012
                * @author Yadickson Soto
                */
               void getStationTally(std::list <StationTally *> & list);

               /**
                * @brief method getter map codi files register
                * @return map codi files
                * @author Yadickson Soto
                * @date 24/02/2012
                */
               std::map < std::string, Smartmatic::SAES::Voting::Codi::CodiFile * > & getCodiFiles();

				/**
				 * @brief method setter codi machine
				 * @param codiMachine new codi machine
				 * @date 14/03/2012
				 * @author Yadickson Soto
				 */
				void setCodiMachine(std::string codiMachine);

				/**
				 * @brief method setter codi voting type
				 * @param codiVotingType codi voting type
				 * @date 04/04/2012
				 * @author Yadickson Soto
				 */
				void setCodiVotingType(std::string codiVotingType);

				/**
				 * @brief method setter custom nis code
				 * @param customniscode custom nis code
				 * @date 14/03/2012
				 * @author Yadickson Soto
				 */
				void setCustomniscode(std::string customniscode);

            private:

               typedef std::map <std::string, Smartmatic::SAES::Voting::Vote::Register *> registerMap;
               typedef std::map <std::string, registerMap > fullRegisterMap;

               void initRegisterMap(std::string code, registerMap & map, std::list<Smartmatic::SAES::Voting::Election::Ballot_option> & list);
               void cleanRegisterMap(registerMap & map);

               void m_UpdateCodiFiles (
            		  std::string index
            		, std::string contestClassCode
               		, std::string contestCode
               		, std::string customCode
               		, std::list<Election::Ballot_option> & listOptions);

               void CmputeCodiCheckSums ();

               bool enableCodi;
               std::string customniscode; ///< custom NIS code
               std::string codiMachine; ///< codi machine
               std::string codiVotingType; ///< codi voting tipe
               Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;
               std::map <std::string, StationTally *> stationTallyMap;

               fullRegisterMap allRegisterMap;
               fullRegisterMap listRegisterMap;
               fullRegisterMap principalRegisterMap;
               fullRegisterMap standInRegisterMap;

               std::map<std::string, Smartmatic::SAES::Voting::Codi::CodiFile *> codi_files;

               static Smartmatic::Log::ISMTTLog* logger;
            };
         }
      }
   }
}

#endif /*__STATION_TALLY_WRAPPER_H__*/
