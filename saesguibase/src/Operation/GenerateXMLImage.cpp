/*
 * GenerateXMLImage.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: Juan.Delgado
 */

#include "GenerateXMLImage.h"
#include "Runtime/Environment/saes-temporal-directories.h"
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include "Resources/election-string-resources-manager.h"
#include "System/IO/Path.h"
#include "System/IO/Directory.h"
#include <Log/SMTTLogManager.h>
#include <Voting/set-language-functionality.h>
#include "Functionalities/voting-experience-validation-functionality.h"
#include <Voting/VotingDevice/card-data-wrapper.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <System/ZenityWrapper.hxx>
#include <string>
#include <sstream>
#include <Functionalities/voting-experience-validation-functionality.h>

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
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::Voting::Screen;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::System;

ISMTTLog* GenerateXMLImage::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Operation.GenerateXMLImage",GETTEXT_PACKAGE);

GenerateXMLImage::GenerateXMLImage()
{
	imagesWrapper = NULL;
}

GenerateXMLImage::~GenerateXMLImage()
{
	dispose();
}

void GenerateXMLImage::dispose()
{
	if (imagesWrapper)
	{
		delete imagesWrapper;
		imagesWrapper = NULL;
	}
}

void GenerateXMLImage::init()
{
	dispose();

	machineOperationManager = Smartmatic::SAES::Operation::MachineOperationManager::getInstance();
	questionConfig = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration();
	screenConfig = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration();
	imagesWrapper = new GeneratedImagesWrapper();
	electoralConfiguration = machineOperationManager->getElectoralConfiguration();
	votingDeviceWrapper = electoralConfiguration->getVotingDevice();
	electionWrapper = electoralConfiguration->getElection();

	logger->Debug("Generating info XML image for: " + votingDeviceWrapper->getFirstVotingDevice().getCustom_code());

	imagesWrapper->getGeneratedImages().setVoting_center(votingDeviceWrapper->getFirstVotingDevice().getCustom_code());
	imagesWrapper->getGeneratedImages().setElection_name(ElectionStringResourcesManager::Current()->getResource(electionWrapper->getElection().getName_key()));

	setWelcomeScreen("","","");
	setLanguageScreen("","","");
	setSuperNull("","","");
	setSuperNullConfirmation("","","");
	setNullVoteConfirmation("","","");
	setPrintVote("","","");
	setCardRemoved("","","");
	setRemoveCard("","","");
	setEndPrintVote("","","");
}

void GenerateXMLImage::persist(std::string folderName)
{
	imagesWrapper->Persist(folderName);
	logger->Debug("Successfully created XML image for: " + votingDeviceWrapper->getFirstVotingDevice().getCustom_code() + " (" + folderName + ")");

}
BasicImage GenerateXMLImage::GetBasicImage(std::string fileName, std::string language, std::string country)
{
	BasicImage basicImage;
	basicImage.setFile_name(fileName);
	basicImage.setLanguage_code(language);
	basicImage.setCountry_code(country);

	return basicImage;
}

void GenerateXMLImage::setWelcomeScreen(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setWelcomeScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::setLanguageScreen(std::string fileName, std::string language, std::string country)
{
	LanguageScreen languageScreen;

	languageScreen.setFile_name(fileName);
	languageScreen.setCountry_code(country);
	languageScreen.setLanguage_code(language);

	LanguageScreen::Confirmation_dialogSequence seq;
	languageScreen.setConfirmation_dialog(seq);

	imagesWrapper->getGeneratedImages().setLanguageScreen(languageScreen);
}

void GenerateXMLImage::addToLanguageScreen(std::string fileName, std::string language, std::string country)
{
	Confirmation_dialog confDialog;

	confDialog.setFile_name(fileName);
	confDialog.setCountry_code(country);
	confDialog.setLanguage_code(language);
	confDialog.setLanguage(language);

	imagesWrapper->getGeneratedImages().getLanguageScreen().getConfirmation_dialog().push_back(confDialog);
}

void GenerateXMLImage::setSuperNull(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setNullScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::setSuperNullConfirmation(std::string fileName, std::string language, std::string country)
{
	if (imagesWrapper->getGeneratedImages().getSuperNullScreen().present())
	{
		imagesWrapper->getGeneratedImages().getSuperNullScreen().get().setConfirmation_dialog(GetBasicImage(fileName, language, country));
	}
}

void GenerateXMLImage::setNullVoteConfirmation(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setNullScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::setPrintVote(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setPrintScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::setCardRemoved(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setSmartCardScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::setRemoveCard(std::string fileName, std::string language, std::string country)
{

}

void GenerateXMLImage::setEndPrintVote(std::string fileName, std::string language, std::string country)
{
	imagesWrapper->getGeneratedImages().setFoldVoteScreen(GetBasicImage(fileName, language, country));
}

void GenerateXMLImage::addCustomAttributes(std::string fileName, std::string language, std::string country)
{
	GeneratedImages::ContestScreenSequence contest;
	imagesWrapper->getGeneratedImages().setContestScreen(contest);
}

void GenerateXMLImage::addToCustomAttributes(std::string fileName, std::string language, std::string country)
{

}

void GenerateXMLImage::addParty(std::string fileName, std::string language, std::string country)
{

}

void GenerateXMLImage::addBallot(std::string fileName, std::string language, std::string country)
{

}

void GenerateXMLImage::SaveContestsScreens()
{
	allContestList = MachineOperationManager::getInstance()->getElectoralConfiguration()->getContestList();

	Contest_classes::Contest_classSequence contestClassSeq = electionWrapper->getContestClasses().getContest_class();

	for(unsigned int i = 0; i < contestClassSeq.size(); i++)
	{
		Contest_class & contestClass = contestClassSeq[i];

		try
		{
			Custom_attribute_definition cad = GetCustomAttributeDefinitionFromContestClass(contestClass);

			list < Contest > contestList = GetContestListFromContestClass(contestClass);

			CreateContestImage(cad, contestList);
		}
		catch (Smartmatic::System::Exception::VotingDeviceException & ex)
		{
			ZenityWrapper::showError(_("Smartmatic.SAES.GUI.Operation.GenerateXMLImage.MessageErrorCustomAttributeDefinitionFromContestClass"),
					_("Smartmatic.SAES.GUI.Operation.GenerateXMLImage.TitleErrorCustomAttributeDefinitionFromContestClass"));

			machineOperationManager->exitMachine();
		}
	}

	imagesWrapper->getGeneratedImages().setContestScreen(contestSequence);
}

Custom_attribute_definition GenerateXMLImage::GetCustomAttributeDefinitionFromContestClass(Contest_class & contestClass)
	throw (Smartmatic::System::Exception::VotingDeviceException)
{
	Voting_device votingDevice = votingDeviceWrapper->getFirstVotingDevice();
	std::list < Custom_attribute_definition > customAttributeDefinitions = votingDeviceWrapper->getCustomAttributeDefinitionList(votingDevice);
	std::list < Custom_attribute_definition >::iterator iter;

	for(iter = customAttributeDefinitions.begin(); iter != customAttributeDefinitions.end(); iter++)
	{
		if(contestClass.getCustom_code())
		{
			string s = contestClass.getCustom_code().get();
			if(s == iter->getCode())
			{
				return *iter;
			}
		}
	}

	logger->Debug("Error matching custom attribute. ContestClass->Code: " + contestClass.getCode());
	throw Smartmatic::System::Exception::VotingDeviceException(_(""),N_(""),logger);
}

list < Contest > GenerateXMLImage::GetContestListFromContestClass(Contest_class & contestClass)
{
	list < Contest > matchingContests;
	list < Contest >::iterator iter;

	for(iter = allContestList.begin(); iter != allContestList.end(); iter++)
	{
		if(iter->getContest_class_code() == contestClass.getCode())
		{
			matchingContests.push_back(*iter);
		}
	}

	for(iter = matchingContests.begin(); iter != matchingContests.end(); iter++)
	{
		allContestList.remove(*iter);
	}

	return matchingContests;
}

void GenerateXMLImage::CreateContestImage(Custom_attribute_definition cad, list < Contest > contestList)
{
/*	ContestImage contestImage;

	contestImage.setCustom_attribute_name(ElectionStringResourcesManager::Current()->getResource(cad.getName_key()));
	contestImage.setCustom_attribute_code(cad.getCode());
	contestImage.setCustom_attribute_description_key(ElectionStringResourcesManager::Current()->getResource(cad.getDescription_key()));

	std::string formattedNameKey = cad.getName_key();
	VotingExperienceValidationFunctionality::FormatName(formattedNameKey);

	Glib::ustring customAttrSelFileName =
			Glib::ustring::compose(VotingExperienceValidationFunctionality::Current()->getCustomAttrSelImage(),language, country, formattedNameKey, contestClassIndex);

	if(cad.getValue().size() > 1)
	{
		contestImage.setCustomAttributeDialog(GetBasicImage(imageMapName[customAttrSelFileName]));
	}

	//TODO custom attribute confirmation

	ContestImage::PartySelectionDialogsSequence partySelectionDialogsSequence;
	list < Contest >::iterator iter;
	for(iter = contestList.begin(); iter != contestList.end(); iter++)
	{
		PartySelectionDialogs partySelectionDialogs;
		FillPartyInfoFromContest(*iter, partySelectionDialogs);
		FillBallotOptionInfo(*iter, partySelectionDialogs);
		partySelectionDialogsSequence.push_back(partySelectionDialogs);
	}

	contestImage.setPartySelectionDialogs(partySelectionDialogsSequence);
	contestSequence.push_back(contestImage);

	imagesWrapper->getGeneratedImages().setContestScreen(contestSequence);
	*/
}

void GenerateXMLImage::FillPartyInfoFromContest(Contest &contest, PartySelectionDialogs & partyDialog)
{
/*	string contestCode = contest.getCode();

	string partyFileName =
			Glib::ustring::compose(VotingExperienceValidationFunctionality::Current()->getPartySelImage(),language, country, contestCode, contestClassIndex);

	partyDialog.setFile_name(imageMapName[partyFileName]);
	partyDialog.setLanguage_code(language);
	partyDialog.setCountry_code(country);
	partyDialog.setContest_code(contest.getCode());
	partyDialog.setContest_custom_code(contest.getCustom_code());
	partyDialog.setContest_title_key(ElectionStringResourcesManager::Current()->getResource(contest.getTitle_key()));
	partyDialog.setContest_abstract_key(ElectionStringResourcesManager::Current()->getResource(contest.getAbstract_key()));
	partyDialog.setContest_help_key(ElectionStringResourcesManager::Current()->getResource(contest.getHelp_key()));
	partyDialog.setDistrict_custom_code(contest.getDistrict().getCustom_code());
	partyDialog.setDistrict_description_key(ElectionStringResourcesManager::Current()->getResource(contest.getDistrict().getDescription_key()));
	partyDialog.setDistrict_name_key(ElectionStringResourcesManager::Current()->getResource(contest.getDistrict().getName_key()));
	partyDialog.setCustom_attribute_value(ElectionStringResourcesManager::Current()->getResource(contest.getHelp_key()));
	*/
}


void GenerateXMLImage::FillBallotOptionInfo(Contest &contest, PartySelectionDialogs & partyDialog)
{
/*	std::list < Party > & partyList = MachineOperationManager::getInstance()->getElectoralConfiguration()->getListPartyByContestCode (contest.getCode());;
	std::list < Party >::iterator iter;

	PartySelectionDialogs::BallotSelectionDialogsSequence ballotSeq;

	for(iter = partyList.begin(); iter != partyList.end(); iter++)
	{
		BallotSelectionDialogs ballotDialog;

		string ballotFileName =
				Glib::ustring::compose(VotingExperienceValidationFunctionality::Current()->getOptionSelImage(),language, country, contest.getCode(), iter->getCode(), contestClassIndex);

		ballotDialog.setFile_name(imageMapName[ballotFileName]);
		ballotDialog.setLanguage_code(language);
		ballotDialog.setCountry_code(country);
		ballotDialog.setParty_name(iter->getName());
		ballotDialog.setParty_abbreviation(iter->getAbbreviation());
		ballotDialog.setParty_code(iter->getCode());
		ballotDialog.setParty_custom_code(iter->getCustom_code());

		ballotSeq.push_back(ballotDialog);
	}

	partyDialog.setBallotSelectionDialogs(ballotSeq);
	*/
}
