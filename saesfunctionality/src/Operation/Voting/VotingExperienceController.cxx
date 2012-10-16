
/**
 * @file VotingExperienceController.cxx
 * @brief Body of core class voting experience
 */

#include "VotingExperienceController.hxx"
#include "VotingOriginator.hxx"
#include "VotingMemento.hxx"
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include "VotingOriginator.hxx"
#include "VotingMemento.hxx"
#include "FillVote.hxx"
#include "Voting/set-language-functionality.h"
#include <Security/Encryption.hxx>
#include <System/guid-class.h>
#include <Voting/operation-status.h>
#include <Voting/Vote/VoteWrapper.hxx>
#include <Voting/Vote/VoteCode.hxx>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Log/SMTTLogManager.h>
#include "Functionalities/time-functionality.h"

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

using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Voting::Vote;

ISMTTLog* VotingExperienceController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Voting.VotingExperienceController",GETTEXT_PACKAGE);

static Election::ElectionWrapper * electionWrapper = NULL; /**<instance of election wrapper*/
static VotingDevice::VotingDeviceWrapper * votingDeviceWrapper = NULL; /**<instance of voting device wrapper*/

VotingExperienceController::VotingExperienceController( ElectoralConfiguration * electoralConfiguration )
{
    this->electoralConfiguration = electoralConfiguration;
    this->originator = new VotingOriginator();
    this->fillVote = new FillVote( electoralConfiguration );
    this->isBlankVote = false;
    this->votingMode = VoteMode::VOTE_O;
    this->vote = NULL;
}

VotingExperienceController::~VotingExperienceController()
{
    dispose();

    if (originator != NULL)
    {
        delete originator;
        originator = NULL;
    }

    if (fillVote != NULL)
    {
        delete fillVote;
        fillVote = NULL;
    }
}

bool VotingExperienceController::init ( VotingDevice::Card_data & cardData )
    throw (Smartmatic::System::Exception::ElectionException,
           Smartmatic::System::Exception::VotingDeviceException)
{
    dispose();

    this->cardData = cardData;
	logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.StartingVotingExperience"));
	
    votingDeviceWrapper = electoralConfiguration->getVotingDevice();
    electionWrapper = electoralConfiguration->getElection();

    if ( !validateCardData( cardData ) )
    {
    	logger->Debug("ERROR - validate card data");
		logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.StartVotingExperienceFailture"));
        return false;
    }

    switch ( cardData.getCard_type() )
    {
        case Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD:
            votingMode = VoteMode::VOTE_O;
            break;

        case Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD:
            votingMode = VoteMode::VOTE_D;
            break;

        case Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_RECOVERY_VOTE_CARD:
            votingMode = VoteMode::VOTE_R;
            break;
    }

    if(votingMode == VoteMode::VOTE_R && cardData.getVote() != NULL)
    {
    	newRecoveryType = true;
        vote = new Smartmatic::SAES::Voting::Vote::Vote (cardData.getVote().get());
        Smartmatic::System::SafeBuffer checksumBuffer;
        Smartmatic::SAES::Voting::Vote::VoteCode::getChecksum(vote->getCode(), checksumBuffer);
        checksumCode = checksumBuffer.GetBase64Data();

        bool validate = Smartmatic::SAES::Voting::Vote::VoteWrapper::validateVote(electoralConfiguration, *vote);

        if(validate)
        {
            logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.VoteRecoveryIntegrityOk"));
            return true;
        }
        else
        {
            logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.VoteRecoveryIntegrityBad"));
            return false;
        }
    }

    VotingDevice::Voting_device votingDevice = votingDeviceWrapper->getFirstVotingDevice();

    std::list <VotingDevice::Logical_voter_group> & logicalVoterGroups (electoralConfiguration->getLogicalVoterGroupList());
    std::list <VotingDevice::Custom_attribute_definition> customAttributeDefinitions;
    std::list <std::string> contestByContestClass;

    customAttributeDefinitions = votingDeviceWrapper->getCustomAttributeDefinitionList( votingDevice );
    electionWrapper->getContestCodeOrderByContestClass(contestByContestClass);

    /*first configuration*/
    VotingState * state = new VotingState("", "", VotingState::START);
    state->setLogicalVoterGroups ( logicalVoterGroups );
    state->setCustomAttributeDefinitions ( customAttributeDefinitions );
    state->setContestByContestClass ( contestByContestClass );

    /*set contest group*/
    std::list < VotingDevice::Logical_voter_group >::iterator itl;

    for ( itl = logicalVoterGroups.begin();
          itl != logicalVoterGroups.end();
          itl++ )
    {
        Election::Contest_group cg = electoralConfiguration->getContestGroup ( (*itl).getContest_group_code() );
        Election::Contest_group::Contest_codeSequence & sequence (cg.getContest_code());

        int size = sequence.size();

        for (int i = 0; i < size ;i++)
        {
            state->addContestByContestGroup ( (*itl).getContest_group_code(), sequence[i] );
        }
    }

    originator->setState ( state );
    memento = originator->createMemento();
    caretaker.push_back( memento );

    /*second configuration - filter from card data*/
    if (!filterFromCardData ( cardData ))
    {
    	logger->Debug("ERROR - filter from card data");
		logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.StartVotingExperienceFailture"));
        return false;
    }

    /*third configuration - filter custom attribute definitions*/
    filterEmptyCustomAttributeDefinition ();

    /*find contest fixed*/
    findFixedContests();

	logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.StartedVotingExperience"));
    return true;
}

void VotingExperienceController::dispose ()
{
    this->voteCode = "";
    this->operationModeCode = "";
    this->votingBoothCode = "";
    this->vdCode = "";
    this->regionCode = "";
    this->allContestsFixed.clear();
    this->allContests.clear();
    this->isBlankVote = false;
    this->checksumCode = "";
    this->activationCode = "";
    this->newRecoveryType = false;

    int size = caretaker.size();

    for ( int i = 0;i < size ;i++)
    {
         VotingMemento * vm = caretaker[i];
         delete vm;
    }

    caretaker.clear();
    memento = NULL;

    if (vote)
    {
    	delete vote;
    	vote = NULL;
    }

    this->votingMode = VoteMode::VOTE_O;
}

bool VotingExperienceController::validateCardData( VotingDevice::Card_data & cardData )
{
   VotingExperienceControllerValidateCardDataType type;
   type = SAESFunctionalityConfigurationManager::Current()->getVotingExperienceControllerConfiguration().getValidateCardDataType();

   if ( type == VotingExperienceControllerValidateCardDataType::CONFIGURATION_ALL )
   {
       return validateLogicalVoterGroupCardData ( cardData ) && validateCustomAttributeDefinitionCardData ( cardData );
   }

   if ( type == VotingExperienceControllerValidateCardDataType::CONFIGURATION_LOGICAL_VOTER_GROUP_ONLY )
   {
       return validateLogicalVoterGroupCardData ( cardData );
   }

   return true;
}

bool VotingExperienceController::validateLogicalVoterGroupCardData ( VotingDevice::Card_data & cardData )
{
    VotingDevice::Logical_voter_group lvgcd = cardData.getLogical_voter_group ();

    std::list <VotingDevice::Logical_voter_group> & logicalVoterGroups (electoralConfiguration->getLogicalVoterGroupList());
    std::list <VotingDevice::Logical_voter_group>::iterator itlvg;

    for ( itlvg = logicalVoterGroups.begin();
          itlvg != logicalVoterGroups.end();
          itlvg++ )
    {
        VotingDevice::Logical_voter_group & lvg (*itlvg);

        if ( lvgcd.getOperation_mode_code() == lvg.getOperation_mode_code() &&
             lvgcd.getVoting_booth_code () == lvg.getVoting_booth_code () &&
             lvgcd.getRegion_code () == lvg.getRegion_code () )
        {
            return true;
        }
    }

    std::stringstream ss;
	ss<< "ERROR - " << __func__ << " Info CardData not found.";
    ss<< " operation-mode-code =" << lvgcd.getOperation_mode_code();
    ss<< " voting-booth-code=" << lvgcd.getVoting_booth_code ();
    ss<< "region-code=" << lvgcd.getRegion_code ();
	logger->Debug(ss.str());
    return false;
}

bool VotingExperienceController::validateCustomAttributeDefinitionCardData ( VotingDevice::Card_data & cardData )
{
    VotingDevice::Voting_device votingDevice = votingDeviceWrapper->getFirstVotingDevice();
    VotingDevice::Logical_voter_group lvgcd = cardData.getLogical_voter_group ();

    std::list <VotingDevice::Custom_attribute_definition> cad;
    std::list <VotingDevice::Custom_attribute_definition>::iterator itcad;
    cad = votingDeviceWrapper->getCustomAttributeDefinitionList( votingDevice, VotingDevice::Machine_type::VOTING_DEVICES_PM );
    
    if ( lvgcd.getCustom_attributes () == NULL )
    {
        return true;
    }

    unsigned int count = 0;

    VotingDevice::Custom_attributes & ca ( lvgcd.getCustom_attributes ().get () );
    for (VotingDevice::Custom_attributes::Custom_attributeConstIterator
        c (ca.getCustom_attribute ().begin ());
        c != ca.getCustom_attribute ().end ();
        ++c)
    {
       bool found = false;

       std::string code = (*c).getCode ();
       std::string value = (*c).getValue ();
        
       for ( itcad = cad.begin();
             itcad != cad.end();
             itcad++ )
       {
            if ( code == (*itcad).getCode() )
            {
                VotingDevice::Custom_attribute_definition::ValueSequence &v ((*itcad).getValue());

                for ( unsigned int i = 0; i < v.size();i++ )
                {
                    if ( value == v[i] )
                    {
                        found = true;
                        count++;
                    }
                }

               if (found)break;
            }
       }

       if (!found)
		{
            std::stringstream ss;
			ss << "ERROR - " << __func__ << " Info CardData not found.";
        	ss << " code=" << code;
        	ss << " value=" << value;
			logger->Debug(ss.str());
       }
    }

    return count == cad.size();
}

bool VotingExperienceController::filterFromCardData( VotingDevice::Card_data & cardData ) throw (VotingDeviceException)
{
    VotingDevice::Logical_voter_group lvg;
    VotingDevice::Voting_device votingDevice = votingDeviceWrapper->getFirstVotingDevice();
    vdCode = votingDevice.getCode();

    if ( votingMode == VoteMode::VOTE_R )
    {
        voteCode = cardData.getCode();

        if (!Smartmatic::SAES::Voting::Vote::VoteCode::validateCode(voteCode))
        {
			logger->Debug("ERROR - vote code no valid");
            dispose();
            return false;
        }

        Smartmatic::System::SafeBuffer checksumBuffer;
        Smartmatic::SAES::Voting::Vote::VoteCode::getChecksum(voteCode, checksumBuffer);
        checksumCode = checksumBuffer.GetBase64Data();

        std::string lvgCode = cardData.getLogical_voter_group ().getCode();
        std::string lvgDummyCode = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();

        isBlankVote = (lvgCode == lvgDummyCode);

        if (!isBlankVote)
        {
            try
            {
                lvg = votingDeviceWrapper->getLogicalVoterGroup( votingDevice , lvgCode );
            }
            catch (VotingDeviceException & ex)
            {
                std::stringstream ss;
                ss  << "FATAL - " << __func__ << " " << ex.what();
                logger->Debug(ss.str());
                dispose();
                return false;
            }
        }
    }
    else
    {
       voteCode = "";
       lvg = cardData.getLogical_voter_group ();
    }

    activationCode = cardData.getActivation_code();
    operationModeCode = lvg.getOperation_mode_code ();
    votingBoothCode = lvg.getVoting_booth_code ();
    regionCode = lvg.getRegion_code ();

    if ( !isBlankVote && lvg.getCustom_attributes () != NULL )
    {
        VotingDevice::Custom_attributes & ca ( lvg.getCustom_attributes ().get () );
       for (VotingDevice::Custom_attributes::Custom_attributeConstIterator
           c (ca.getCustom_attribute ().begin ());
           c != ca.getCustom_attribute ().end ();
           ++c)
       {
          std::string code = (*c).getCode ();
          std::string value = (*c).getValue ();
          setResponse( code, value, VotingState::START );
       }
    }

    return true;
}

void VotingExperienceController::filterEmptyCustomAttributeDefinition()
{
    std::list < VotingDevice::Custom_attribute_definition >::iterator it;
    std::list < VotingDevice::Custom_attribute_definition > customAttributeDefinitions = memento->getState()->getCustomAttributeDefinitions();

    for ( it = customAttributeDefinitions.begin();
          it != customAttributeDefinitions.end();
          it++ )
    {
        VotingDevice::Custom_attribute_definition::ValueSequence v = (*it).getValue ();
        int sizeLVG = memento->getState()->getLogicalVoterGroups().size();

        if ( v.size () == 1 && sizeLVG > 1 )
        {
           std::string code = (*it).getCode();
           std::string value = *(v.begin());
           setResponse ( code, value, VotingState::AUTOMATIC_RESPONSE );
        }
        else
        {
            return;
        }
    }
}

std::list<VotingDevice::Logical_voter_group> VotingExperienceController::filterLogicalVoterGroup( std::string code, std::string value )
{
    std::list<VotingDevice::Logical_voter_group>::iterator itl;
    std::list<VotingDevice::Logical_voter_group> logicalVoterGroups;
    std::list<VotingDevice::Logical_voter_group> templvg = memento->getState()->getLogicalVoterGroups();

    for (itl = templvg.begin();
         itl != templvg.end();
         itl++)
    {
        VotingDevice::Logical_voter_group logical = (*itl);

       if (!( logical.getOperation_mode_code() == operationModeCode &&
            logical.getVoting_booth_code() == votingBoothCode &&
            logical.getRegion_code() == regionCode )) continue;

       if ( logical.getCustom_attributes() == NULL ) continue;

       VotingDevice::Custom_attributes attributes = logical.getCustom_attributes().get();
       VotingDevice::Custom_attributes::Custom_attributeSequence sequence;
       VotingDevice::Custom_attributes attributesTemp;

       bool remove = false;

       for (VotingDevice::Custom_attributes::Custom_attributeIterator
           ca (attributes.getCustom_attribute ().begin ());
           ca != attributes.getCustom_attribute ().end ();
           ++ca)
       {
           std::string customCode = (*ca).getCode();
           std::string customValue = (*ca).getValue();

           if (code == customCode && value != customValue)
           {
              remove = true;
              break;
           }

           sequence.push_back((*ca));
       }

       if (!remove)
       {
           attributesTemp.setCustom_attribute(sequence);
           logical.setCustom_attributes(attributesTemp);
           logicalVoterGroups.push_back(logical);
       }
    }

    return logicalVoterGroups;
}

bool VotingExperienceController::findCustomAttribute ( std::list<VotingDevice::Logical_voter_group> & logicalVoterGroups, std::string code )
{
    std::list < VotingDevice::Logical_voter_group >::iterator itl;

    /*check logical voter group value in custom attribute*/
    for (itl = logicalVoterGroups.begin();
         itl != logicalVoterGroups.end();
         itl++)
    {
        VotingDevice::Custom_attributes attributes = (*itl).getCustom_attributes().get();

        for (VotingDevice::Custom_attributes::Custom_attributeIterator
            ca (attributes.getCustom_attribute ().begin ());
            ca != attributes.getCustom_attribute ().end ();
            ++ca)
        {
            std::string aCode = (*ca).getCode();
            if (code == aCode)
            {
                return true;
            }
        }
    }

    return false;
}

std::list < VotingDevice::Custom_attribute_definition >
VotingExperienceController::filterCustomAttributeDefinitionByLogicalVoterGroup (
    std::list<VotingDevice::Logical_voter_group> & logicalVoterGroups, std::string code )
{
    std::list < VotingDevice::Custom_attribute_definition >::iterator it;
    std::list < VotingDevice::Custom_attribute_definition > customAttributeDefinitions;
    std::list < VotingDevice::Custom_attribute_definition > list = memento->getState()->getCustomAttributeDefinitions();

    /*clear custom attribute definition by response*/
    for ( it = list.begin();
          it != list.end();
          it++ )
    {
       std::string customAttributeCode = (*it).getCode();
       if ( code == customAttributeCode || !findCustomAttribute ( logicalVoterGroups , customAttributeCode )) continue;
       customAttributeDefinitions.push_back(*it);
    }

    return customAttributeDefinitions;
}

void VotingExperienceController::findFixedContests () throw (ElectionException)
{
    findContests( true );
}

void VotingExperienceController::findNewContests () throw (ElectionException)
{
    findContests( false );
}

void VotingExperienceController::findContests ( bool fixeds ) throw (ElectionException)
{
    if (memento == NULL)
    {
        logger->Error("Current memento is NULL.");
        return;
    }

    std::list < std::string > contestGroups;
    std::list < std::string >::iterator it;
    std::list < VotingDevice::Logical_voter_group >::iterator itl;

    std::map < std::string, int > contestMap;
    std::map < std::string, int >::iterator itMap;

    std::list < std::string > temp = memento->getState()->getContestGroups();

    for ( it = temp.begin();
          it != temp.end();
          it++ )
    {
        std::list < std::string > sequence = memento->getState()->getContestsByContestGroup (*it);
        std::list < std::string >::iterator its;

        for ( its = sequence.begin();
              its != sequence.end();
              its++ )
        {
            std::string code = (*its);
            contestMap[ code ] = ( contestMap.find( code ) != contestMap.end() ) ? contestMap[ code ] + 1: 1;
        }
    }

    int size = temp.size();

    for ( itMap = contestMap.begin();
          itMap != contestMap.end();
          itMap++ )
    {
        int count = (*itMap).second;

        if ( size == count )
        {
            if ( fixeds )
            {
               allContestsFixed.push_back ( (*itMap).first );
            }
            else
            {
               allContests.push_back ( (*itMap).first );
            }

            /*clear contest of contest group*/
            std::list < std::string > temp = memento->getState()->getContestGroups();

            for (it = temp.begin();
                 it != temp.end();
                 it++)
            {
                std::list < std::string > sequence = memento->getState()->getContestsByContestGroup (*it);
                std::list < std::string >::iterator its;

                for ( its = sequence.begin();
                      its != sequence.end();
                      its++ )
                {
                    std::string scode = (*its);
                    if ( scode != (*itMap).first ) continue;
                    memento->getState()->removeContestByContestGroup ( (*it), scode );
                }
            }
        }
    }
}

VotingExperienceController::VotingExperienceType VotingExperienceController::getNextTypeAction()
{
	
    if (memento == NULL)
    {
        std::stringstream ss;
		ss<< __func__ << " - ERROR current memento is NULL.";
        logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceClose"));
        return VOTING_CONTROLLER_CLOSE;
    }

    if (isBlankVote)
    {
		logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceClose"));
        return VOTING_CONTROLLER_CLOSE;
    }

    if (vote)
    {
        logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceClose"));
        return VOTING_CONTROLLER_CLOSE;
    }

    VotingExperienceType type;
//    ALTERNATE_FIRST_QUESTIONS /**<operation type alternate questions, first questions and last contests fixed*/
//    ALTERNATE_FIRST_CONTESTS_FIXED /**<operation type alternate questions, first contests fixed*/
//    ALL_QUESTIONS_FIRST_QUESTIONS /**<operation type all questions, first questions and last contests*/
//    ALL_QUESTIONS_FIRST_CONTESTS_FIXED /**<operation type all questions, first contests fixed, all questions and last constest*/

    findNewContests();

    switch ( SAESFunctionalityConfigurationManager::Current()->getVotingExperienceControllerConfiguration().getOperationType() )
    {
        case VotingExperienceControllerOperationType::CONFIGURATION_ALTERNATE_FIRST_QUESTIONS:
            type = alternateFirstQuestions();
			break;
        case VotingExperienceControllerOperationType::CONFIGURATION_ALTERNATE_FIRST_CONTESTS_FIXED:
            type = alternateFirstContestsFixed();
			break;
        case VotingExperienceControllerOperationType::CONFIGURATION_ALL_QUESTIONS_FIRST_QUESTIONS:
            type = allQuestionsFirstQuestions();
			break;
        case VotingExperienceControllerOperationType::CONFIGURATION_ALL_QUESTIONS_FIRST_CONTESTS_FIXED:
            type = allQuestionsFirstContestsFixed();
			break;
        case VotingExperienceControllerOperationType::CONFIGURATION_PRIORITY_BY_CONTEST_CLASS:
            type = priorityByContestClass();
            break;
        default:
            type = VOTING_CONTROLLER_CLOSE;
			break;
    }

	switch (type)
	{
		case VOTING_CONTROLLER_CONTEST:
			logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceContest"));
			break;
		case VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION:
			logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceCustomAttributeDefinition"));
			break;
		case VOTING_CONTROLLER_CLOSE:
			logger->Audit(N_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextActionVotingExperienceClose"));
			break;
	}
	
	return type;

}

VotingExperienceController::VotingExperienceType VotingExperienceController::alternateFirstQuestions()
{
    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCAD = memento->getState()->getCustomAttributeDefinitions().size();
    int sizeC = allContests.size();
    int sizeCF = allContestsFixed.size();

    if ( sizeC > 0 )
    {
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCF > 0 && sizeCAD == 0 )
    {
        allContests.insert(allContests.end(), allContestsFixed.begin(), allContestsFixed.end());
        allContestsFixed.clear();
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCAD > 0 && sizeLVG > 1 )
    {
        return VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION;
    }
    
    return VOTING_CONTROLLER_CLOSE;
}

VotingExperienceController::VotingExperienceType VotingExperienceController::alternateFirstContestsFixed()
{
    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCAD = memento->getState()->getCustomAttributeDefinitions().size();
    int sizeC = allContests.size();
    int sizeCF = allContestsFixed.size();

    if ( sizeCF > 0 )
    {
        allContests.insert(allContests.end(), allContestsFixed.begin(), allContestsFixed.end());
        allContestsFixed.clear();
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeC > 0 )
    {
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCAD > 0 && sizeLVG > 1 )
    {
        return VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION;
    }

    return VOTING_CONTROLLER_CLOSE;
}

VotingExperienceController::VotingExperienceType VotingExperienceController::allQuestionsFirstQuestions()
{
    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCAD = memento->getState()->getCustomAttributeDefinitions().size();
    int sizeC = allContests.size();
    int sizeCF = allContestsFixed.size();

    if ( sizeCAD > 0 && sizeLVG > 1 )
    {
        return VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION;
    }
    if ( sizeC > 0 )
    {
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCF > 0 )
    {
        allContests.insert(allContests.end(), allContestsFixed.begin(), allContestsFixed.end());
        allContestsFixed.clear();
        return VOTING_CONTROLLER_CONTEST;
    }

    return VOTING_CONTROLLER_CLOSE;
}

VotingExperienceController::VotingExperienceType VotingExperienceController::allQuestionsFirstContestsFixed()
{
    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCAD = memento->getState()->getCustomAttributeDefinitions().size();
    int sizeC = allContests.size();
    int sizeCF = allContestsFixed.size();

    if ( sizeCF > 0 )
    {
        allContests.insert(allContests.end(), allContestsFixed.begin(), allContestsFixed.end());
        allContestsFixed.clear();
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeC > 0 )
    {
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCAD > 0 && sizeLVG > 1 )
    {
        return VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION;
    }

    return VOTING_CONTROLLER_CLOSE;
}

VotingExperienceController::VotingExperienceType VotingExperienceController::priorityByContestClass()
{
    /*filter contest by contest class*/
    std::list <std::string> contestByContestGroup = memento->getState()->getAllContestsByContestGroup();
    std::list <std::string> contestFixed = allContestsFixed;

    contestFixed.insert(contestFixed.end(), allContests.begin(), allContests.end());
    allContests.clear();

    std::list <std::string> contestByContestClass;

    std::list <std::string> tempContestByContestClass = memento->getState()->getContestByContestClass();
    std::list <std::string>::iterator it;

    contestByContestGroup.insert(contestByContestGroup.end(), contestFixed.begin(), contestFixed.end());

    for (it = tempContestByContestClass.begin();
         it != tempContestByContestClass.end();
         it++)
    {
        std::list <std::string>::iterator itc;

        for (itc = contestByContestGroup.begin();
             itc != contestByContestGroup.end();
             itc++)
        {
            if ((*it) == (*itc))
            {
                contestByContestClass.push_back((*it));
                contestByContestGroup.remove((*itc));
                break;
            }
        }
    }

    bool next = false;

    /*order list contest by contest class*/

    do
    {
        next = false;

        if (contestByContestClass.size() > 0)
        {
            std::string c = (*(contestByContestClass.begin()));

            for (it = contestFixed.begin();
                 it != contestFixed.end();
                 it++)
            {
                if ((*it) == c)
                {
                    allContests.push_back((*it));
                    contestFixed.remove((*it));
                    contestByContestClass.remove((*it));
                    next = true;
                    break;
                }
            }
        }

    } while(next);

    memento->getState()->setContestByContestClass(contestByContestClass);

    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCAD = memento->getState()->getCustomAttributeDefinitions().size();
    int sizeC = allContests.size();

    if ( sizeC > 0 )
    {
        return VOTING_CONTROLLER_CONTEST;
    }
    if ( sizeCAD > 0 && sizeLVG > 1 )
    {
        return VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION;
    }

    return VOTING_CONTROLLER_CLOSE;
}

VotingDevice::Custom_attribute_definition & VotingExperienceController::getPreviousCustomAttributeDefinition () throw (VotingDeviceException)
{
    throw VotingDeviceException(_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.UnderConstruction"),
                                "Smartmatic.SAES.Operation.Voting.VotingExperienceController.UnderConstruction",
                                logger);
}

VotingDevice::Custom_attribute_definition & VotingExperienceController::getNextCustomAttributeDefinition () throw (VotingDeviceException)
{
    int size = memento->getState()->getCustomAttributeDefinitions().size();

    if ( size > 0 )
    {
        currentCustomAttributeDefinition = memento->getState()->getCustomAttributeDefinitions().front();
        return getCurrentCustomAttributeDefinition();
    }

    throw VotingDeviceException( _("Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextCustomAttributeDefinitionNotFound"),
                                "Smartmatic.SAES.Operation.Voting.VotingExperienceController.NextCustomAttributeDefinitionNotFound",
                                logger);
}

VotingDevice::Custom_attribute_definition & VotingExperienceController::getCurrentCustomAttributeDefinition ()
{
    return currentCustomAttributeDefinition;
}

void VotingExperienceController::setCustomAttributeDefinitionResponse ( std::string code, std::string value ) throw (VotingDeviceException)
{
    setResponse( code, value, VotingState::USER_RESPONSE );
    filterEmptyCustomAttributeDefinition ();
}

void VotingExperienceController::sendBlankVoteResponse()
{
    isBlankVote = true;
}

void VotingExperienceController::setNullPartyResponse(Smartmatic::SAES::Voting::Election::Contest & contest)
{
    memento->getState()->addBallotOption ( contest.getCode(), "", "" );
}

void VotingExperienceController::setResponse( std::string code, std::string value, VotingState::TypeResponse response )
{
    if (memento == NULL)
    {
        std::stringstream ss;
        ss << __func__ << " - ERROR current memento is NULL.";
		logger->Debug(ss.str());
        return;
    }

    /*filter logical voter group*/
    std::list < VotingDevice::Logical_voter_group > logicalVoterGroups = filterLogicalVoterGroup ( code, value );
    /*filter custom attribute definitions*/
    std::list < VotingDevice::Custom_attribute_definition > customAttributeDefinitions = filterCustomAttributeDefinitionByLogicalVoterGroup ( logicalVoterGroups, code );
    std::list <std::string> contestByContestClass = memento->getState()->getContestByContestClass();

    /*filter contest of contest class*/
    VotingState * state = new VotingState( code, value, response );
    state->setLogicalVoterGroups ( logicalVoterGroups );
    state->setCustomAttributeDefinitions ( customAttributeDefinitions );
    state->setContestByContestClass( contestByContestClass );

    /*filter contest group*/
    std::list < std::string > tempContestGroups = memento->getState()->getContestGroups();
    std::list<VotingDevice::Logical_voter_group>::iterator itl;

    for ( itl = logicalVoterGroups.begin();
          itl != logicalVoterGroups.end();
          itl++ )
    {
        std::list < std::string >::iterator itcg;

        for (itcg = tempContestGroups.begin();
             itcg != tempContestGroups.end();
             itcg++)
        {
             if ((*itl).getContest_group_code() == (*itcg))
             {
                 std::list < std::string > sequence = memento->getState()->getContestsByContestGroup( (*itcg) );
                 std::list < std::string >::iterator its;

                 for ( its = sequence.begin();
                       its != sequence.end();
                       its++)
                 {
                     state->addContestByContestGroup(*itcg, *its);
                 }
             }
        }
    }

    originator->setState ( state );
    memento = originator->createMemento();
    caretaker.push_back( memento );
}

Smartmatic::SAES::Voting::Vote::Vote * VotingExperienceController::getVote () throw (ElectionException)
{
	if (vote)
	{
		return vote;
	}
	else
	{
		vote = new Smartmatic::SAES::Voting::Vote::Vote();
	}

    if (memento == NULL)
    {
        std::stringstream ss;
		ss<< __func__ << " - ERROR current memento is NULL.";
		logger->Debug(ss.str());
        vote->setCode("");
        vote->setVotingDeviceCode("");
        vote->setLogicalVoterGroup("");
        return vote;
    }

    int contestCount, ballotOptionCount;

    std::string currentLanguageCode;
	std::string	currentCountryCode;

	Smartmatic::SAES::Voting::SetLanguageFunctionality::getCurrentLanguageCountry ( currentLanguageCode, currentCountryCode );

	std::transform(currentLanguageCode.begin(), currentLanguageCode.end(),currentLanguageCode.begin(), ::tolower);
	std::transform(currentCountryCode.begin(), currentCountryCode.end(),currentCountryCode.begin(), ::toupper);

    vote->setVotingDeviceCode( vdCode );
	vote->setLan_code(currentLanguageCode + "_" + currentCountryCode);
	vote->setMode(votingMode);

	if (isBlankVote)
    {
        fillVote->fillBlankVote( *vote, contestCount, ballotOptionCount, memento );
    }
    else
    {
        fillVote->fillNormalVote( *vote, contestCount, ballotOptionCount, caretaker );
    }

    bool fill = SAESFunctionalityConfigurationManager::Current()->getVoteConfiguration().getFillVote();

    if (fill)
    {
        fillVote->fillVote( *vote, contestCount, ballotOptionCount );
    }

    if (voteCode.empty())
    {
        voteCode = Smartmatic::SAES::Voting::Vote::VoteWrapper::generateCode(*vote);
    }

    vote->setCode( voteCode );
    return vote;
}

void VotingExperienceController::setBallotOptionState (
    std::string contestCode,
    std::string partyCode,
    std::string ballotOptionCode,
    bool state)
{
    if (memento == NULL)
    {

        std::stringstream ss;
        ss << __func__ << " - ERROR current memento is NULL.";
		logger->Debug(ss.str());
        return;
    }

    if ( state )
    {
        memento->getState()->addBallotOption ( contestCode, partyCode, ballotOptionCode );
    }
    else
    {
        memento->getState()->removeBallotOption ( contestCode, partyCode, ballotOptionCode );
    }
}

std::list < Smartmatic::SAES::Voting::Election::Contest >
    VotingExperienceController::getCurrentContestList ()
    throw (Smartmatic::System::Exception::ElectionException)
{
	std::list < Smartmatic::SAES::Voting::Election::Contest > list;
    electionWrapper->getContestByContestClass ( allContests, list );
    return list;
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option >
    VotingExperienceController::getBallotOptionsSelectedByContest (
    Smartmatic::SAES::Voting::Election::Contest & contest)
{
    std::list < Smartmatic::SAES::Voting::Election::Ballot_option > b;
    return b;
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option >
    VotingExperienceController::getBallotOptionsSelectedByContestParty (
    Smartmatic::SAES::Voting::Election::Contest & contest,
    Smartmatic::SAES::Voting::Election::Party & party )
    throw (Smartmatic::System::Exception::ElectionException)
{
	std::list < Smartmatic::SAES::Voting::Election::Ballot_option > list;
    std::list < std::string > codes = memento->getState()->getBallotOptions ( contest.getCode(), party.getCode() );
    electionWrapper->getBallotOptionsByContestParty( contest, party, codes, list );
    return list;
}

void VotingExperienceController::clearBallotOptionsSelectedByContest (
    Smartmatic::SAES::Voting::Election::Contest & contest)
{
    memento->getState()->removeContest ( contest.getCode() );
}

void VotingExperienceController::resetVotingExperience ()
{
	init(cardData);
}

void VotingExperienceController::clearBallotOptionsSelectedByContestParty (
    Smartmatic::SAES::Voting::Election::Contest & contest,
    Smartmatic::SAES::Voting::Election::Party & party )
{
    memento->getState()->removePartyByContest ( contest.getCode(), party.getCode() );
}

Smartmatic::SAES::Voting::Election::Party
    VotingExperienceController::getPartySelectedFromContest (
    Smartmatic::SAES::Voting::Election::Contest & contest)
    throw (Smartmatic::System::Exception::ElectionException)
{
    std::list < std::string > partys;
    partys = memento->getState()->getPartys( contest.getCode() );

    if ( partys.size () > 0 )
    {
        std::string partyCode = partys.front();
        return electionWrapper->getPartyByContest( contest, partyCode );
    }

    throw Smartmatic::System::Exception::ElectionException(
            _("Smartmatic.SAES.Operation.Voting.VotingExperienceController.PartyNotFound"),
            _("Smartmatic.SAES.Operation.Voting.VotingExperienceController.PartyNotFound"),
            logger);
}

bool VotingExperienceController::isThereAnyPartySelectedFromContest (
    Smartmatic::SAES::Voting::Election::Contest & contest)
{
    return memento->getState()->getPartys( contest.getCode() ).size () > 0;
}

bool VotingExperienceController::moveContestListForward()
{
    allContests.clear();
    return true;
}

bool VotingExperienceController::canMoveBack(std::string contestCode)
{
    bool navigateBetweenContest =
            SAESFunctionalityConfigurationManager::Current()->getVotingExperienceControllerConfiguration().getNavigateBetweenContest();

    bool canMove;

    if ( navigateBetweenContest )
    {
        canMove = !firstContest(contestCode) || canMoveContestListBack();
    }
    else
    {
        canMove = firstContest(contestCode) && canMoveContestListBack();
    }

    return canMove;
}

bool VotingExperienceController::firstContest(std::string contestCode)
{
    return allContests.size() > 0 && (*(allContests.begin())) == contestCode;
}

bool VotingExperienceController::canMoveContestListBack()
{
    std::vector < VotingMemento * >::reverse_iterator rit;
    bool skipCustomAttributeAutomatic =
            SAESFunctionalityConfigurationManager::Current()->getVotingExperienceControllerConfiguration().getSkipCustomAttributeAutomatic();

    for (rit = caretaker.rbegin();
         rit != caretaker.rend();
         ++rit)
    {
        VotingMemento * m = (*rit);

        if (!skipCustomAttributeAutomatic &&
            m->getState()->getResponse() == VotingState::AUTOMATIC_RESPONSE)
        {
            return false;
        }
        else if (m->getState()->getResponse() == VotingState::USER_RESPONSE)
        {
            return true;
        }
    }

    return false;
}

bool VotingExperienceController::moveContestListBack()
{
    if ( !canMoveContestListBack() )
    {
        return false;
    }

    /*delete current memento*/

    std::vector < VotingMemento * >::reverse_iterator rit;
    std::vector < VotingMemento * > tempCaretaker = caretaker;

    int position = 0;
    bool moveForware = false;

    for (rit = tempCaretaker.rbegin();
         rit != tempCaretaker.rend();
         ++rit)
    {
        VotingMemento * m = (*rit);
        position = m->getPosition();

        if (moveForware) break;

        if (m->getState()->getResponse() == VotingState::START)
        {
            // no move forware one position
            break;
        }
        else if (m->getState()->getResponse() == VotingState::USER_RESPONSE)
        {
            // move forware one position
            moveForware = true;
        }
    }

    for (rit = tempCaretaker.rbegin();
         rit != tempCaretaker.rend();
         ++rit)
    {
        VotingMemento * m = (*rit);

        if (m->getPosition() > position)
        {
           delete m;
            caretaker.pop_back();
        }
        else
        {
            memento = m;
            break;
        }
    }

    allContests.clear();

    return true;
}

Smartmatic::SAES::Voting::Vote::VoteMode VotingExperienceController::getVotingMode()
{
    return votingMode;
}

void VotingExperienceController::setVotingMode(Smartmatic::SAES::Voting::Vote::VoteMode mode)
{
    votingMode = mode;
}

std::string VotingExperienceController::getChecksumVote()
{
    return checksumCode;
}

std::string VotingExperienceController::getActivationCode()
{
    return this->activationCode;
}

bool VotingExperienceController::isNewRecoveryType()
{
	return newRecoveryType;
}
