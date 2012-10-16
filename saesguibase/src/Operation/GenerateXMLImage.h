/*
 * GenerateXMLImage.h
 *
 *  Created on: Jul 21, 2011
 *      Author: Juan.Delgado
 */

#ifndef GENERATEXMLIMAGE_H_
#define GENERATEXMLIMAGE_H_

#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
#include <Voting/Screen/GeneratedImagesWrapper.hxx>
#include <Voting/Screen/generated-images-schema.hxx>
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include "Operation/Voting/VotingExperienceController.hxx"
#include <Voting/VotingDevice/VotingDeviceWrapper.hxx>
#include <Voting/Election/ElectionWrapper.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				class GenerateXMLImage
				{
				public:

					GenerateXMLImage();
					virtual ~GenerateXMLImage();

					/**
					 * @brief 	method clear
					 * @date 	24/05/2012
					 * @author 	Yadickson Soto
					 */
					void init();
					/**
					 * @brief	persist in folder
					 * @param 	folderName folder name
					 * @author	Yadickson Soto
					 * @date	24/05/2012
					 */
					void persist(std::string folderName);

					void setWelcomeScreen(std::string fileName, std::string language, std::string country);

					void setLanguageScreen(std::string fileName, std::string language, std::string country);

					void addToLanguageScreen(std::string fileName, std::string language, std::string country);

					void setSuperNull(std::string fileName, std::string language, std::string country);

					void setSuperNullConfirmation(std::string fileName, std::string language, std::string country);

					void setNullVoteConfirmation(std::string fileName, std::string language, std::string country);

					void setPrintVote(std::string fileName, std::string language, std::string country);

					void setCardRemoved(std::string fileName, std::string language, std::string country);

					void setRemoveCard(std::string fileName, std::string language, std::string country);

					void setEndPrintVote(std::string fileName, std::string language, std::string country);

					void addCustomAttributes(std::string fileName, std::string language, std::string country);

					void addToCustomAttributes(std::string fileName, std::string language, std::string country);

					void addParty(std::string fileName, std::string language, std::string country);

					void addBallot(std::string fileName, std::string language, std::string country);

				private:

					void dispose();

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
					Smartmatic::SAES::Voting::ElectoralConfiguration *electoralConfiguration;   ///< The electoral configuration
					Smartmatic::SAES::Operation::MachineOperationManager * machineOperationManager; ///< Manager for machine operation
					Smartmatic::SAES::Voting::Screen::GeneratedImagesWrapper* imagesWrapper;	///< Images wrapper
					Smartmatic::SAES::Configuration::CustomAtributtesWindowConfiguration questionConfig;	///< The question configuration
					Smartmatic::SAES::Configuration::VotingExperienceValidationScreensFunctionalityConfiguration screenConfig;	/// The screen configuration
					Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* votingDeviceWrapper;	/// The voting device wrapper
					Smartmatic::SAES::Voting::Election::ElectionWrapper* electionWrapper;		// The election wrapper
					std::list < Smartmatic::SAES::Voting::Election::Contest > allContestList;	/// List of all contest
					Smartmatic::SAES::Voting::Screen::GeneratedImages::ContestScreenSequence contestSequence; 	///The contest sequence

					/**
					 * @brief	Get the basic image configuration
					 *
					 * @author	Juan.Delgado
					 * @date	19/07/2011
					 *
					 * @param	fileName the file name
					 * @return	BasicImage element configuration
					 */
					Smartmatic::SAES::Voting::Screen::BasicImage GetBasicImage(std::string fileName = "", std::string language = "", std::string country = "");

					/**
					 * @brief	Save contests screens
					 *
					 * @author	Juan.Delgado
					 * @date	19/07/2011
					 */
					void SaveContestsScreens();

					/**
					 * @brief	Fill custom attribute dialog
					 *
					 * @author	Juan.Delgado
					 * @date	19/07/2011
					 *
					 * @param	contestImage node to save custom attribute information
					 */
					void FillCustomAttributeDialog();//Smartmatic::SAES::Voting::Screen::ContestImage& contestImage);

					/**
					 * @brief	Fill party info from contest
					 *
					 * @author	Juan.Delgado
					 * @date	19/07/2011
					 *
					 * @param	contest The contest
					 * @param	partyDialog Party to fill info
					 */
					void FillPartyInfoFromContest(Smartmatic::SAES::Voting::Election::Contest& contest, Smartmatic::SAES::Voting::Screen::PartySelectionDialogs & partyDialog);

					/**
					 * @brief	Fill ballot option info
					 *
					 * @author	Juan.Delgado
					 * @date	19/07/2011
					 *
					 * @param	contest The contest
					 * @param	partyDialog Party to fill info
					 */
					void FillBallotOptionInfo(Smartmatic::SAES::Voting::Election::Contest& contest, Smartmatic::SAES::Voting::Screen::PartySelectionDialogs & partyDialog);

					/**
					 * @brief	Save super null screens
					 *
					 * @author	Juan.Delgado
					 * @date	21/07/2011
					 */
					void SaveSuperNullScreens();

					/**
					 * @brief	Get custom attribute definition from contest class
					 *
					 * @author	Juan.Delgado
					 * @date	20/07/2011
					 *
					 * @param	contestClass The contest class
					 *
					 * @return	The custom attribute definition associated to the contest class
					 */
					Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition GetCustomAttributeDefinitionFromContestClass(Smartmatic::SAES::Voting::Election::Contest_class & contestClass)
						throw (Smartmatic::System::Exception::VotingDeviceException);


					/**
					 * @brief	Get contest list from contest class
					 *
					 * @author	Juan.Delgado
					 * @date	20/07/2011
					 *
					 * @param	contestClass The contest class
					 *
					 * @return	A contest list
					 */
					std::list < Smartmatic::SAES::Voting::Election::Contest > GetContestListFromContestClass(Smartmatic::SAES::Voting::Election::Contest_class & contestClass);

					/**
					 * @brief	Get contest list from contest class
					 *
					 * @author	Juan.Delgado
					 * @date	20/07/2011
					 *
					 * @param	cad The custom attribute definition
					 * @param	contestList The contest list
					 */
					void CreateContestImage(Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition cad, std::list < Smartmatic::SAES::Voting::Election::Contest > contestList);
				};
			}
		}
	}
}

#endif /* GENERATEXMLIMAGE_H_ */
