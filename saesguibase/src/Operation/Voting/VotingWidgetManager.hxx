/**
 * @file VotingWidgetManager.hxx
 * 		 
 * @brief Core class object widget for voting experience
 */

#ifndef __VOTING_WIDGET_MANAGER_H__
#define __VOTING_WIDGET_MANAGER_H__

#include <iostream>
#include <map>
#include <Voting/ElectoralConfiguration.hxx>
#include "Gui/Widgets/party-selection-widget.h"
#include "Gui/Widgets/ballot-option-selection-widget.h"
#include "Runtime/Environment/saes-directories.h"
#include <Operation/Initiator/ICheckCondition.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
   namespace SAES
   {
       namespace GUI
       {
          namespace Operation
          {
             namespace Voting
             {
                /**
                 * @brief	Header class VotingWidgetManager.
                 *
                 * @author	Yadickson Soto &lt;yadickson.soto@smartmatic.com&gt;
                 * @date	23-03-2011
                 */

                class VotingWidgetManager : public Smartmatic::SAES::Operation::Initiator::ICheckCondition
                {
                private:

                   /**
                    * @brief	Class constructor.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    */

                   VotingWidgetManager();

                public:
                   Smartmatic::SAES::Operation::Initiator::TestStatus::Tests check ();

                   /**
                    * @brief	method initialization.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @throw ElectionException.
                    */

                   void init()
                       throw (Smartmatic::System::Exception::ElectionException,
                    		   Smartmatic::System::Exception::VotingDeviceException);

                   /**
                    * @brief	Set electoral cofnfiguration
                    *
                    * @author	Juan.Delgado
                    * @date	09/08/2011
                    *
                    * @param electoralConfiguration	electoral configuration.
                    *
                    */

                   void SetElectoralConfiguration(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

                   /**
                    * @brief	Set Saes directories
                    *
                    * @author	Juan.Delgado
                    * @date	09/08/2011
                    *
                    * @param saesDir Saes directories
                    */

                   void SetSaesDirectories(Smartmatic::SAES::Runtime::Environment::SaesDirectories* saesDir);

                   /**
                    * @brief	Class destroyer.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    */

                   virtual ~VotingWidgetManager();

                   /**
                    * @brief	method dispose.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    */

                   void dispose();

                   /**
                    * @brief	method getter party selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @param	contestCode	contest code.
                    *
                    * @return	party selection widget.
                    */

                   Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * getPartySelectionWidgetByContest( std::string contestCode );

                   /**
                    * @brief	method getter ballot option selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @param	contestCode	contest code.
                    * @param	partyCode  	The party code.
                    *
                    * @return	ballot option selection widget.
                    */

                   Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * getBallotOptionSelectionWidgetByContestParty( std::string contestCode, std::string partyCode );

                   /**
                    * @brief	method getter number of ballot option displayed in selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @param	contestCode	contest code.
                    * @param	partyCode  	The party code.
                    *
                    * @return	number of ballots.
                    */

                   unsigned int getBallotOptionSelectionTotalBallotsWidgetByContestParty( std::string contestCode, std::string partyCode );

                   /**
                    * @brief	method clear ballot option selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    */

                   void clearBallotOptionSelectionWidget();

                   /**
                    * @brief	Gets the map party selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @return	The map party selection widget.
                    */

                   std::map < std::string , Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * > getMapPartySelectionWidget();

                   /**
                    * @brief	Gets the map ballot option selection widget.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @return	The map ballot option selection widget.
                    */

                   std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > > getMapBallotOptionSelectionWidget();

					/**
					 * @brief	Sets a theme.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 *
					 */

					void update();

                   /**
                    * @brief	method getter instance of class
                    * 			@retunr instance of class.
                    *
                    * @author	Fsilva
                    * @date	28/04/2011
                    *
                    * @return	null if it fails, else the instance.
                    */

                   static VotingWidgetManager * getInstance();

                private:
                   int width; ///< The width
                   int partyHeight;  ///< The party height
                   int ballotHeight;  ///< The ballot height

                   Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///<The electoral configuration
                   Smartmatic::SAES::Runtime::Environment::SaesDirectories* saesDir;	///< The saes directories
                   static VotingWidgetManager * instance; ///< The instance of voting widget manager
                   std::map < std::string , Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * > mapPartySelectionWidget; ///< The map party selection widget
                   std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > > mapBallotOptionSelectionWidget; ///< The map ballot option selection widget

                   static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
                };
             }
          }
      }
   }
}

#endif /*__VOTING_WIDGET_MANAGER_H__*/
