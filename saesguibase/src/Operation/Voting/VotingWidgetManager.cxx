/**
 * @file VotingWidgetManager.cxx
 * @brief Body class object widget for voting experience
 */

#include "VotingWidgetManager.hxx"
#include <Windows/basic-window.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <list>
#include "Operation/Voting/VotingExperienceController.hxx"
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;

ISMTTLog* VotingWidgetManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Operation.VotingWidgetManager",GETTEXT_PACKAGE);


VotingWidgetManager * VotingWidgetManager::instance = NULL;

VotingWidgetManager::VotingWidgetManager()
: ICheckCondition ( Smartmatic::SAES::Operation::Initiator::TestStatus::ConfigurationLoad,
		_("Smartmatic.SAES.GUI.Operation.VotingWidgetManager.CreatingVotingMaps"),
		"ui/check-memory-map.gif", "ui/check-memory-map-failed.gif")
{
	int height;

	Smartmatic::GUI::Windows::BasicWindow window(false,true);
	window.getContentSize(width, height);

	int bottomHeight = SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getBottomFrameHeight();

	partyHeight = height - bottomHeight;

	ballotHeight = height;

	if(SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBallotOptionFooter())
		ballotHeight -= bottomHeight;
}

VotingWidgetManager::~VotingWidgetManager()
{
    dispose();
}

Smartmatic::SAES::Operation::Initiator::TestStatus::Tests VotingWidgetManager::check ()
{
	Smartmatic::SAES::Operation::Initiator::TestStatus::Tests result;

	try
	{
		init();
		result = Smartmatic::SAES::Operation::Initiator::TestStatus::Passed;
	}
	catch(...)
	{
		result = Smartmatic::SAES::Operation::Initiator::TestStatus::Failed;
	}

	return result;
}

void VotingWidgetManager::SetElectoralConfiguration(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
{
	this->electoralConfiguration = electoralConfiguration;
}

void VotingWidgetManager::SetSaesDirectories(Smartmatic::SAES::Runtime::Environment::SaesDirectories* saesDir)
{
	this->saesDir = saesDir;
}

void VotingWidgetManager::init ()
        throw (ElectionException, VotingDeviceException)
{
    dispose();

    electoralConfiguration->loadAllData();
    std::list < Smartmatic::SAES::Voting::Election::Contest > allContest = electoralConfiguration->getContestList();
    std::list < Smartmatic::SAES::Voting::Election::Contest >::iterator itc;

//    std::list < Smartmatic::SAES::Voting::Election::Ballot_option > partyListByContest;
//    std::list < Smartmatic::SAES::Voting::Election::Ballot_option >::iterator itp;

    Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * partySelectionWidget = NULL;
    Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * ballotOptionSelectionWidget = NULL;

    for ( itc = allContest.begin();
          itc != allContest.end();
          itc++)
    {
        std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & partyListByContest (electoralConfiguration->getBallotOptionPartyByContest((*itc).getCode()));
        std::list < Smartmatic::SAES::Voting::Election::Ballot_option >::iterator itp;

//        electoralConfiguration->getElection()->getBallotOptionPartyByContest ( *itc, partyListByContest, Smartmatic::SAES::Voting::Election::Category::ELECTION_PRINCIPAL );

        partySelectionWidget = new Smartmatic::SAES::GUI::Widgets::PartySelectionWidget( *itc, false);
        partySelectionWidget->set_size_request (width, partyHeight);
        partySelectionWidget->Initialize( partyListByContest, *saesDir );
		partySelectionWidget->show_all_children();
		partySelectionWidget->show();

        mapPartySelectionWidget [ (*itc).getCode() ] = partySelectionWidget;

        for ( itp = partyListByContest.begin();
              itp != partyListByContest.end();
              itp++)
        {
            Smartmatic::SAES::Voting::Election::Party & party ( (*itp).getParty() );
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & ballotList (electoralConfiguration->getEligibleOptionsListByContestParty( (*itc).getCode() , party.getCode()));
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & principalBallotList (electoralConfiguration->getEligibleOptionsPrincipalByContestParty( (*itc).getCode() , party.getCode()));
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & standInBallotList (electoralConfiguration->getEligibleOptionsStandInByContestParty( (*itc).getCode() , party.getCode()));

            ballotOptionSelectionWidget = new Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget( *itc );
            ballotOptionSelectionWidget->set_size_request (width, ballotHeight);
            ballotOptionSelectionWidget->Initialize(ballotList, principalBallotList, standInBallotList, *saesDir);
            ballotOptionSelectionWidget->show_all_children();
    		ballotOptionSelectionWidget->show();
			ballotOptionSelectionWidget->hide();
			
            (mapBallotOptionSelectionWidget [ (*itc).getCode() ])[ party.getCode() ] = ballotOptionSelectionWidget;
        }
    }
}

void VotingWidgetManager::dispose ()
{
    std::map < std::string , Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * >::iterator itp;
    Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * party;

    for ( itp = mapPartySelectionWidget.begin();
          itp != mapPartySelectionWidget.end();
          itp++ )
    {
        party = (*itp).second;
        if (party) delete party;
    }

    mapPartySelectionWidget.clear();

    std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > >::iterator itb;
    std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * >::iterator itbo;
    Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * ballotOption;

    for ( itb = mapBallotOptionSelectionWidget.begin();
          itb != mapBallotOptionSelectionWidget.end();
          itb++ )
    {
        for ( itbo = ((*itb).second).begin();
              itbo != ((*itb).second).end();
              itbo++)
        {
            ballotOption = (*itbo).second;
            if (ballotOption) delete ballotOption;
        }
    }

    mapBallotOptionSelectionWidget.clear();
}

Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * VotingWidgetManager::getPartySelectionWidgetByContest( std::string contestCode )
{
    return mapPartySelectionWidget[ contestCode ];
}

Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * VotingWidgetManager::getBallotOptionSelectionWidgetByContestParty( std::string contestCode, std::string partyCode )
{
    return (mapBallotOptionSelectionWidget [ contestCode ])[ partyCode ];
}

unsigned int VotingWidgetManager::getBallotOptionSelectionTotalBallotsWidgetByContestParty( std::string contestCode, std::string partyCode )
{
    return ((mapBallotOptionSelectionWidget [ contestCode ])[ partyCode ])->GetTotalBallotsDisplayed();
}

void VotingWidgetManager::clearBallotOptionSelectionWidget()
{
    std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > >::iterator itb;
    std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * >::iterator itbo;
    Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * ballotOption;

    for ( itb = mapBallotOptionSelectionWidget.begin();
          itb != mapBallotOptionSelectionWidget.end();
          itb++ )
    {
        for ( itbo = ((*itb).second).begin();
              itbo != ((*itb).second).end();
              itbo++)
        {
            ballotOption = (*itbo).second;
            ballotOption->ClearVisualSelection();
        }
    }
}

VotingWidgetManager * VotingWidgetManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new VotingWidgetManager();
    }

    return instance;
}

std::map < std::string , Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * > VotingWidgetManager::getMapPartySelectionWidget()
{
	return mapPartySelectionWidget;
};

std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > > VotingWidgetManager::getMapBallotOptionSelectionWidget()
{
	return mapBallotOptionSelectionWidget;
};

void VotingWidgetManager::update()
{
    std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > >::iterator itb;
    std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * >::iterator itbo;
    Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * ballotOption;

    for ( itb = mapBallotOptionSelectionWidget.begin();
          itb != mapBallotOptionSelectionWidget.end();
          itb++ )
    {
        for ( itbo = ((*itb).second).begin();
              itbo != ((*itb).second).end();
              itbo++)
        {
            ballotOption = (*itbo).second;
            ballotOption->refresh();
        }
    }

    std::map < std::string , Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * >::iterator itp;
    Smartmatic::SAES::GUI::Widgets::PartySelectionWidget * party;

    for ( itp = mapPartySelectionWidget.begin();
          itp != mapPartySelectionWidget.end();
          itp++ )
    {
        party = (*itp).second;
        party->refresh();
    }
}
