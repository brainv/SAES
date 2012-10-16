/**
 * @file PMachineAuthenticator.cxx
 * @brief body class for president machine authenticator
 */

#include "PMachineAuthenticator.hxx"
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

ISMTTLog* PMachineAuthenticator::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.PMachineAuthenticator",GETTEXT_PACKAGE);

PMachineAuthenticator::PMachineAuthenticator()
 : IAuthenticator ( IAuthenticator::PRESIDENT_MACHINE )
{
}

PMachineAuthenticator::~PMachineAuthenticator()
{

}

bool PMachineAuthenticator::ValidateRole(std::string password)
{
	if(validate(password) == MENU)
    	return true;

	return false;
}

IAuthenticator::AuthenticationResultType PMachineAuthenticator::validate( std::string password )
{
    string votingUnblockingKey = "";
    string menuRoleUnblockingKey = "";
    string systemRoleMenuKey = "";
    string systemRoleVotingKey = "";
    string systemRoleElectoralKey = "";
    string systemRoleVotingAudioKey = "";

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

    for ( it = sequence.begin();
          it != sequence.end();
         ++it)
    {
        switch ((*it).getType())
        {
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_MENU:
                systemRoleMenuKey = (*it).getKey();
                break;
                
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_VOTING:
                systemRoleVotingKey = (*it).getKey();
                break;
                
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_ELECTORAL:
                systemRoleElectoralKey = (*it).getKey();
                break;
                
            case Smartmatic::SAES::Functionality::Configuration::SystemRoleType::CONFIGURATION_VOTING_AUDIO:
                systemRoleVotingAudioKey = (*it).getKey();
                break;
            default:
              break;
        }
    }

    if ( password == systemRoleElectoralKey )
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineAuthenticator.ValidateElectoralProcess"));
        return ELECTORAL_PROCESS;
    }
    else if ( password == votingUnblockingKey || password == systemRoleVotingKey)
    {
    		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineAuthenticator.ValidateWizardMenu"));
    		return WIZARD_MENU;
    }
    else if ( password == systemRoleMenuKey || password == menuRoleUnblockingKey )
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineAuthenticator.ValidateMenu"));
        return MENU;
    }
	logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.PMachineAuthenticator.ValidateNoMatch"));
    return NO_MATCH;
}

void PMachineAuthenticator::dispose()
{
}

