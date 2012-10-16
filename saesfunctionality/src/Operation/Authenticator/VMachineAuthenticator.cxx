/**
 * @file VMachineAuthenticator.cxx
 * @brief body class for voting machine authenticator
 */

#include "VMachineAuthenticator.hxx"
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
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

using namespace std;
using namespace Smartmatic::SAES::Operation::Authenticator;
using namespace Smartmatic::Log;

ISMTTLog* VMachineAuthenticator::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator",GETTEXT_PACKAGE);

VMachineAuthenticator::VMachineAuthenticator()
 : IAuthenticator ( IAuthenticator::VOTING_MACHINE )
{
}

VMachineAuthenticator::~VMachineAuthenticator()
{

}

bool VMachineAuthenticator::ValidateRole(std::string password)
{
	if(validate(password) == MENU)
    	return true;

	return false;
}

IAuthenticator::AuthenticationResultType VMachineAuthenticator::validate( std::string password )
{
    string votingUnblockingKey = "";
    string menuRoleUnblockingKey = "";
    string systemRoleMenuKey = "";
    string systemRoleVotingKey = "";
    string systemRoleVotingAudioKey = "";
    string systemRoleClearAlarm = "";

    try
    {
        menuRoleUnblockingKey = electoralConfiguration->getVotingDevice()->getFirstVotingDevice(). getOperation_modes().getOperation_mode()[0].getRoles().getRole()[0].getKey();
        votingUnblockingKey = electoralConfiguration->getVotingDevice()->getFirstVotingDevice(). getOperation_modes().getOperation_mode()[0].getUnblocking_key();
    }
    catch (std::exception & ex)
    {
		stringstream line;
		line<<"FATAL "<< __func__ <<" "<< ex.what();
		logger->Debug(line.str());
    }

    Smartmatic::SAES::Functionality::Configuration::SystemRoleConfiguration systemRole = Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getSystemRoleConfiguration();    
    Smartmatic::SAES::Functionality::Configuration::SystemRoleConfiguration::RoleSequence & sequence ( systemRole.getRole() );    
    Smartmatic::SAES::Functionality::Configuration::SystemRoleConfiguration::RoleIterator it;

    for ( it = sequence.begin(); it != sequence.end(); ++it)
    {
        switch ((*it).getType())
        {
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_MENU:
                systemRoleMenuKey = (*it).getKey();
                break;
                
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_VOTING:
                systemRoleVotingKey = (*it).getKey();
                break;
                
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_VOTING_AUDIO:
                systemRoleVotingAudioKey = (*it).getKey();
                break;
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_CLEAR_ALARM:
              systemRoleClearAlarm = (*it).getKey();
                break;
            default:
                break;
        }
    }

    if ( password == systemRoleVotingKey || password == votingUnblockingKey )
    {
    	logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator.ValidateVotingProcess"));
    	return VOTING_PROCESS;
    }
    else if ( password == systemRoleMenuKey || password == menuRoleUnblockingKey )
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator.ValidateMenu"));
        return MENU;
    }

    else if( password == systemRoleVotingAudioKey )
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator.ValidateAudioVotingProcess"));
        return AUDIO_VOTING_PROCESS;
    }
    else if ( password == systemRoleClearAlarm)
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator.ValidateClearAlarm"));
        return CLEAR_ALARM;
    }
	logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.VMachineAuthenticator.ValidateNoMatch"));
    return NO_MATCH;
}

void VMachineAuthenticator::dispose()
{
}


