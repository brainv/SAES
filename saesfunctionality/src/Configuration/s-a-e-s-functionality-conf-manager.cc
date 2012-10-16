/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "s-a-e-s-functionality-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>

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
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

#define LOGGER_PROJECT "Smartmatic.Configuration.SAESFunctionalityConfigurationManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* SAESFunctionalityConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* SAESFunctionalityConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

SAESFunctionalityConfigurationManager::SAESFunctionalityConfigurationManager()
{
	configuration = NULL;
	Initialize();
}

SAESFunctionalityConfigurationManager::~SAESFunctionalityConfigurationManager()
{
	if(configuration != NULL)
	{
		delete(configuration);
	}
}
auto_ptr<SaesFunctionalityConfiguration>*  SAESFunctionalityConfigurationManager::getConfiguration()
{
	return configuration;
}


LaunchConfiguration& SAESFunctionalityConfigurationManager::getLaunchConfiguration()
{
	return configuration->get()->getLaunchConfiguration();
}
void SAESFunctionalityConfigurationManager::Initialize()
{

	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SAESFunctionality"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SaesFunctionalityConfiguration>(parseSaesFunctionalityConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
		}
		else
		{
			LoadDefault();
			Initialize();
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESFUNCTIONALITY Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESFUNCTIONALITY Error", "Error");
		exit (0);
	}
}

int SAESFunctionalityConfigurationManager::getMessageRemoveFlashTime()
{
	return configuration->get()->getVMachineInitiator().getMessageRemoveFlashTime();
}

int SAESFunctionalityConfigurationManager::getVMSuccesMessageTime()
{
	return configuration->get()->getVMachineInitiator().getSuccessMessageTime();
}

int SAESFunctionalityConfigurationManager::getPMSuccesMessageTime()
{
	return configuration->get()->getPMachineInitiator().getSuccessMessageTime();
}

int SAESFunctionalityConfigurationManager::getVMStepTime()
{
	return configuration->get()->getVMachineInitiator().getStepTime();
}

int SAESFunctionalityConfigurationManager::getPMStepTime()
{
	return configuration->get()->getPMachineInitiator().getStepTime();
}

CardTypeController & SAESFunctionalityConfigurationManager::getCardTypeController()
{
	return configuration->get()->getCardTypeController();
}

PVFormTransformationConfig & SAESFunctionalityConfigurationManager::getPVFormTransformation()
{
	return configuration->get()->getPVFormTransformation();
}

StructureInstallationType & SAESFunctionalityConfigurationManager::getStructureInstallationType()
{
	       return configuration->get()->getStructureInstallation();
}

EnqueueVoteConfiguration & SAESFunctionalityConfigurationManager::getEnqueueVoteConfiguration()
{
	       return configuration->get()->getEnqueueVoteConfiguration();
}

void SAESFunctionalityConfigurationManager::getCommandsOfAlarm(std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand>& list,  AlarmEnum typeOfAlarm)
{

	::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::Alarm > alarms = (*configuration)->getAlarmsConfiguration().getAlarm();

	for(unsigned int i = 0;i < alarms.size();i++)
	{
		if(alarms[i].getTypeOfAlarm() == typeOfAlarm)
		{
			::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::AlarmCommand > alarmCommand = alarms[i].getAlarmCommands ();
			for(unsigned int j = 0;j < alarmCommand.size();j++)
			{
				list.push_back(alarmCommand[j]) ;
			}
			break;
		}

	}

}

std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand> SAESFunctionalityConfigurationManager::getCommandsOfAlarm(std::string typeOfAlarm)
{
	std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand> list;
	::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::Alarm > alarms = (*configuration)->getAlarmsConfiguration().getAlarm();

	for(unsigned int i = 0;i < alarms.size();i++)
	{
		if(alarms[i].getTypeOfAlarm().compare(typeOfAlarm)==0)
		{
			::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::AlarmCommand > alarmCommand = alarms[i].getAlarmCommands ();
			for(unsigned int j = 0;j < alarmCommand.size();j++)
			{
				list.push_back(alarmCommand[j]) ;
			}
			return list;
		}

	}
	return list;
}

AlarmCategoryEnum SAESFunctionalityConfigurationManager::getCategoryOfAlarm(AlarmEnum typeOfAlarm)
{
	AlarmCategoryEnum alarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);

	std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand> list;
	::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::Alarm > alarms = (*configuration)->getAlarmsConfiguration().getAlarm();
	for(unsigned int i = 0;i < alarms.size();i++)
	{
		if(alarms[i].getTypeOfAlarm()==typeOfAlarm)
		{
			alarmCategory = alarms[i].getAlarmCategory();
			return alarmCategory;
		}

	}
	return alarmCategory;
}

AlarmBehaviorEnum SAESFunctionalityConfigurationManager::getBehaviorOfAlarm(AlarmEnum typeOfAlarm)
{
	AlarmBehaviorEnum alarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

	::xsd::cxx::tree::sequence< Smartmatic::SAES::Functionality::Configuration::Alarm > alarms = (*configuration)->getAlarmsConfiguration().getAlarm();

	for(unsigned int i = 0;i < alarms.size();i++)
	{
		if(alarms[i].getTypeOfAlarm()==typeOfAlarm)
		{
			alarmBehavior = alarms[i].getAlarmBehavior();
			return alarmBehavior;
		}
	}

	return alarmBehavior;
}

void SAESFunctionalityConfigurationManager::LoadDefault()
{

	SaesFunctionalityConfiguration *configSAESFunctionality = new SaesFunctionalityConfiguration();
	AlarmsConfiguration *alarmConf = new AlarmsConfiguration();
	VMachineInitiatorConfiguration * vmachineConf = new VMachineInitiatorConfiguration();
	PMachineInitiatorConfiguration pmachineConf;

	Alarm *alarmUnableToRead = new Alarm();
	Alarm *alarmUnableToWrite = new Alarm();
	Alarm *alarmCryptoError = new Alarm();
	Alarm *alarmInvalidContent = new Alarm();
	Alarm *alarmCardUsed = new Alarm();
	Alarm *alarmCardValidityPeriodExpired = new Alarm();
	Alarm *alarmInvalidVotingData = new Alarm();
	Alarm *alarmPaperJam = new Alarm();
	Alarm *alarmPaperOut = new Alarm();
	Alarm *alarmNeop = new Alarm();
	Alarm *alarmTimeout = new Alarm();
	Alarm *alarmUnexpectedError = new Alarm();
	Alarm *alarmCardNotRemovedAfterVoting = new Alarm();
	Alarm cardExtractionCounter;

	AlarmCommand *alarmBuzzCommand = new AlarmCommand();
	AlarmCommand *alarmGreenCommand = new AlarmCommand();
	AlarmCommand *alarmRedLedCommand = new AlarmCommand();

	int messageRemoveFlashTime = 1;

	::xsd::cxx::tree::sequence< ::Smartmatic::SAES::Functionality::Configuration::AlarmCommand> *alarmCommandSequence = new ::xsd::cxx::tree::sequence< ::Smartmatic::SAES::Functionality::Configuration::AlarmCommand>();


	::xsd::cxx::tree::sequence< ::Smartmatic::SAES::Functionality::Configuration::Alarm> *alarmsSeq = new ::xsd::cxx::tree::sequence< ::Smartmatic::SAES::Functionality::Configuration::Alarm>();

	LaunchConfiguration launch;
	//launch.setAppType(AppType::CONFIGURATION_VOTINGONLY);
	launch.setAppType(AppType::CONFIGURATION_POLLBOOKONLY);
	//launch.setAppType (AppType::CONFIGURATION_DIAGNOSTICSONLY);
	//launch.setAppType (AppType::CONFIGURATION_RUNFUNCTIONALITY);
	launch.setExecuteInitialCalibrationInAppTypeVotingOnly(false);
	launch.setExecutePMSetupInAppTypeDiagnostics(false);
	launch.setPMSetupCommand("/usr/sbin/pm-setup -s");
	launch.setSkipAutoDiagnostic(false);
	launch.setPrintInstallationReportPM(true);

	try
	{
		stringstream ss;
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");

		VotingExperienceControllerConfiguration vecc;
		VotingExperienceControllerOperationType vecot = VotingExperienceControllerOperationType::CONFIGURATION_PRIORITY_BY_CONTEST_CLASS;
		VotingExperienceControllerValidateCardDataType vcdt = VotingExperienceControllerValidateCardDataType::CONFIGURATION_ALL;
		vecc.setOperationType(vecot);
		vecc.setValidateCardDataType(vcdt);
		vecc.setSkipCustomAttributeAutomatic(true);
		vecc.setNavigateBetweenContest(false);
		configSAESFunctionality->setVotingExperienceController( vecc );

		BlankVoteConfiguration bvc;
		BlankVoteType bvt = BlankVoteType::CONFIGURATION_BLANK_VOTE_ENABLED;
		BlankVoteListContestCodeType bvlcct = BlankVoteListContestCodeType::CONFIGURATION_BLANK_VOTE_CONTEST_GROUP_ONLY;

		VoteConfiguration vc;
		vc.setFillVote(false);

		bvc.setBlankVote (bvt);
		bvc.setBlankVoteListContestCode (bvlcct);

		configSAESFunctionality->setVote( vc );
		configSAESFunctionality->setBlankVote( bvc );

		SystemRoleConfiguration src;
		SystemRoleConfiguration::RoleSequence & sequence ( src.getRole() );

		Role roleMenuActivation;
		roleMenuActivation.setKey("260780");
		roleMenuActivation.setNameKey("MenuActivation");
		roleMenuActivation.setDescriptionKey("MenuActivation");
		roleMenuActivation.setType (SystemRoleType::CONFIGURATION_MENU);

		Role roleVotingActivation;
		roleVotingActivation.setKey("210580");
		roleVotingActivation.setNameKey("VotingActivation");
		roleVotingActivation.setDescriptionKey("VotingActivation");
		roleVotingActivation.setType (SystemRoleType::CONFIGURATION_VOTING);

		Role roleElectoralActivation;
		roleElectoralActivation.setKey("abcdef");
		roleElectoralActivation.setNameKey("ElectoralActivation");
		roleElectoralActivation.setDescriptionKey("ElectoralActivation");
		roleElectoralActivation.setType (SystemRoleType::CONFIGURATION_ELECTORAL);

		Role roleVotingAudioActivation;
		roleVotingAudioActivation.setKey("abcde");
		roleVotingAudioActivation.setNameKey("VotingAudioActivation");
		roleVotingAudioActivation.setDescriptionKey("VotingAudioActivation");
		roleVotingAudioActivation.setType (SystemRoleType::CONFIGURATION_VOTING_AUDIO);

		Role roleClearAlarm;
		roleClearAlarm.setKey("00000");
		roleClearAlarm.setNameKey("ClearAlarm");
		roleClearAlarm.setDescriptionKey("ClearAlarm");
		roleClearAlarm.setType (SystemRoleType::CONFIGURATION_CLEAR_ALARM);

		sequence.push_back( roleMenuActivation );
		sequence.push_back( roleVotingActivation );
		sequence.push_back( roleElectoralActivation );
		sequence.push_back( roleVotingAudioActivation );
		sequence.push_back( roleClearAlarm);

		alarmBuzzCommand->setTypeOfCommand(AlarmCommandEnum::CONFIGURATION_BUZZER);
		alarmBuzzCommand->setPeriod(100);
		alarmBuzzCommand->setIsOff(false);

		alarmRedLedCommand->setTypeOfCommand(AlarmCommandEnum::CONFIGURATION_REDLED);
		alarmRedLedCommand->setPeriod(100);
		alarmRedLedCommand->setIsOff(false);

		alarmGreenCommand->setTypeOfCommand(AlarmCommandEnum::CONFIGURATION_GREENLED);
		alarmGreenCommand->setPeriod(100);
		alarmGreenCommand->setIsOff(false);

		alarmCommandSequence->push_back(*alarmBuzzCommand);
		alarmCommandSequence->push_back(*alarmRedLedCommand);
		alarmCommandSequence->push_back(*alarmGreenCommand);

		alarmUnableToRead->setAlarmCommands(*alarmCommandSequence);
		alarmUnableToRead->setTypeOfAlarm(AlarmEnum::CONFIGURATION_UNABLETOREAD);
		alarmUnableToRead->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmUnableToRead->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmUnableToWrite->setAlarmCommands(*alarmCommandSequence);
		alarmUnableToWrite->setTypeOfAlarm(AlarmEnum::CONFIGURATION_UNABLETOWRITE);
		alarmUnableToWrite->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmUnableToWrite->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmCryptoError->setAlarmCommands(*alarmCommandSequence);
		alarmCryptoError->setTypeOfAlarm(AlarmEnum::CONFIGURATION_CRYPTOERROR);
		alarmCryptoError->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmCryptoError->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmInvalidContent->setAlarmCommands(*alarmCommandSequence);
		alarmInvalidContent->setTypeOfAlarm(AlarmEnum::CONFIGURATION_INVALIDCONTENT);
		alarmInvalidContent->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmInvalidContent->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmCardUsed->setAlarmCommands(*alarmCommandSequence);
		alarmCardUsed->setTypeOfAlarm(AlarmEnum::CONFIGURATION_CARDUSED);
		alarmCardUsed->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		alarmCardUsed->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmCardValidityPeriodExpired->setAlarmCommands(*alarmCommandSequence);
		alarmCardValidityPeriodExpired->setTypeOfAlarm(AlarmEnum::CONFIGURATION_CARDVALIDITYPERIODEXPIRED);
		alarmCardValidityPeriodExpired->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmCardValidityPeriodExpired->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmInvalidVotingData->setAlarmCommands(*alarmCommandSequence);
		alarmInvalidVotingData->setTypeOfAlarm(AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA);
		alarmInvalidVotingData->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmInvalidVotingData->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmPaperJam->setAlarmCommands(*alarmCommandSequence);
		alarmPaperJam->setTypeOfAlarm(AlarmEnum::CONFIGURATION_PRINTERNEOPAFTERVOTE);
		alarmPaperJam->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmPaperJam->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmPaperOut->setAlarmCommands(*alarmCommandSequence);
		alarmPaperOut->setTypeOfAlarm(AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE);
		alarmPaperOut->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmPaperOut->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmNeop->setAlarmCommands(*alarmCommandSequence);
		alarmNeop->setTypeOfAlarm(AlarmEnum::CONFIGURATION_PRINTERNOTREADYFORVOTE);
		alarmNeop->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmNeop->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmTimeout->setAlarmCommands(*alarmCommandSequence);
		alarmTimeout->setTypeOfAlarm(AlarmEnum::CONFIGURATION_TIMEOUT);
		alarmTimeout->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		alarmTimeout->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmUnexpectedError->setAlarmCommands(*alarmCommandSequence);
		alarmUnexpectedError->setTypeOfAlarm(AlarmEnum::CONFIGURATION_UNEXPECTED);
		alarmUnexpectedError->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		alarmUnexpectedError->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_WAIT);


		alarmCardNotRemovedAfterVoting->setAlarmCommands(*alarmCommandSequence);
		alarmCardNotRemovedAfterVoting->setTypeOfAlarm(AlarmEnum::CONFIGURATION_CARDNOTREMOVEDAFTERVOTING);
		alarmCardNotRemovedAfterVoting->setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		alarmCardNotRemovedAfterVoting->setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		cardExtractionCounter.setAlarmCommands(*alarmCommandSequence);
		cardExtractionCounter.setTypeOfAlarm(AlarmEnum::CONFIGURATION_CARDEXTRACTIONCOUNTER);
		cardExtractionCounter.setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		cardExtractionCounter.setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		Alarm printerNeopBeforeVote;

		printerNeopBeforeVote.setAlarmCommands(*alarmCommandSequence);
		printerNeopBeforeVote.setTypeOfAlarm(AlarmEnum::CONFIGURATION_PRINTERNEOPBEFOREVOTE);
		printerNeopBeforeVote.setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_REGULARALARM);
		printerNeopBeforeVote.setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		Alarm alarmDisconnected;

		alarmDisconnected.setAlarmCommands(*alarmCommandSequence);
		alarmDisconnected.setTypeOfAlarm(AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED);
		alarmDisconnected.setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		alarmDisconnected.setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		Alarm alarmConnected;

		alarmConnected.setAlarmCommands(*alarmCommandSequence);
		alarmConnected.setTypeOfAlarm(AlarmEnum::CONFIGURATION_ALARMBOXCONNECTED);
		alarmConnected.setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		alarmConnected.setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		Alarm cardReaderUnresponsive;

		cardReaderUnresponsive.setAlarmCommands(*alarmCommandSequence);
		cardReaderUnresponsive.setTypeOfAlarm(AlarmEnum::CONFIGURATION_CARDREADERUNRESPONSIVE);
		cardReaderUnresponsive.setAlarmCategory(AlarmCategoryEnum::CONFIGURATION_CRITICALALARM);
		cardReaderUnresponsive.setAlarmBehavior(AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION);

		alarmsSeq->push_back(*alarmUnableToRead);
		alarmsSeq->push_back(*alarmUnableToWrite);
		alarmsSeq->push_back(*alarmCryptoError);
		alarmsSeq->push_back(*alarmInvalidContent);
		alarmsSeq->push_back(*alarmCardUsed);
		alarmsSeq->push_back(*alarmCardValidityPeriodExpired);
		alarmsSeq->push_back(*alarmInvalidVotingData);
		alarmsSeq->push_back(*alarmPaperJam);
		alarmsSeq->push_back(*alarmPaperOut);
		alarmsSeq->push_back(*alarmNeop);
		alarmsSeq->push_back(*alarmTimeout);
		alarmsSeq->push_back(*alarmUnexpectedError);
		alarmsSeq->push_back(*alarmCardNotRemovedAfterVoting);
		alarmsSeq->push_back(cardExtractionCounter);
		alarmsSeq->push_back(printerNeopBeforeVote);
		alarmsSeq->push_back(alarmDisconnected);
		alarmsSeq->push_back(alarmConnected);
		alarmsSeq->push_back(cardReaderUnresponsive);

		alarmConf->setAlarm(*alarmsSeq);		
		vmachineConf->setMessageRemoveFlashTime(messageRemoveFlashTime);
		vmachineConf->setSuccessMessageTime(500);
		vmachineConf->setStepTime(200);

		pmachineConf.setSuccessMessageTime(2500);
		pmachineConf.setStepTime(200);

		OperationConfiguration operationConfiguration;
		operationConfiguration.setStartOpenElection(false);
		operationConfiguration.setConfigurationReset(false);
		operationConfiguration.setDiagnosesConsideredApproved(false);
		operationConfiguration.setSimulateVotes(false);

		PVFormTransformationConfig transformationConfig;
		transformationConfig.setType(PVFormTransformationType::CONFIGURATION_FOP);
		transformationConfig.setFopConfigFile("fop.xconf");

		configSAESFunctionality->setOperationConfiguration(operationConfiguration);
		configSAESFunctionality->setVMachineInitiator(*vmachineConf);
		configSAESFunctionality->setPMachineInitiator(pmachineConf);
		configSAESFunctionality->setCardTypeController(CardTypeController::CONFIGURATION_MEMORY_CARD);
		configSAESFunctionality->setPVFormTransformation(transformationConfig);
		configSAESFunctionality->setStructureInstallation(StructureInstallationType::CONFIGURATION_GROUPED);
		configSAESFunctionality->setAlarmsConfiguration (*alarmConf);
		configSAESFunctionality->setSystemRole( src );
		configSAESFunctionality->setLaunchConfiguration(launch);
		configSAESFunctionality->setEnqueueVoteConfiguration(EnqueueVoteConfiguration(false));

		Smartmatic::ConfigurationTypes::NamespaceInfomap map;

#ifdef NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION
		map[""].name = NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION;
#endif
		map[""].schema = "";

		serializeSaesFunctionalityConfiguration(ss,*configSAESFunctionality, map, "UTF-8");
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SAESFunctionality",ss.str());
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESFUNCTIONALITY Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESFUNCTIONALITY Error", "Error");
		exit (0);
	}

	delete(alarmBuzzCommand);
	delete(alarmGreenCommand);
	delete(alarmRedLedCommand);
	delete(alarmCommandSequence);
	delete(alarmUnableToRead);
	delete(alarmUnableToWrite);
	delete(alarmCryptoError);
	delete(alarmInvalidContent);
	delete(alarmCardUsed);
	delete(alarmCardValidityPeriodExpired);
	delete(alarmInvalidVotingData);
	delete(alarmPaperJam);
	delete(alarmPaperOut);
	delete(alarmNeop);
	delete(alarmTimeout);
	delete(alarmUnexpectedError);
	delete(alarmCardNotRemovedAfterVoting);
	delete(alarmsSeq);
	delete(alarmConf);
	delete(vmachineConf);
	delete(configSAESFunctionality);

}

SystemRoleConfiguration SAESFunctionalityConfigurationManager::getSystemRoleConfiguration()
{
	return ((*configuration)->getSystemRole());
}

BlankVoteConfiguration SAESFunctionalityConfigurationManager::getBlankVoteConfiguration()
{
	return ((*configuration)->getBlankVote());
}

VoteConfiguration SAESFunctionalityConfigurationManager::getVoteConfiguration()
{
	return ((*configuration)->getVote());
}

VotingExperienceControllerConfiguration SAESFunctionalityConfigurationManager::getVotingExperienceControllerConfiguration()
{
	return ((*configuration)->getVotingExperienceController());
}

OperationConfiguration SAESFunctionalityConfigurationManager::getOperationConfiguration()
{
	return ((*configuration)->getOperationConfiguration());
}

SAESFunctionalityConfigurationManager * SAESFunctionalityConfigurationManager::singleton_instance = NULL;

SAESFunctionalityConfigurationManager *SAESFunctionalityConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SAESFunctionalityConfigurationManager ();

	return singleton_instance;
}
