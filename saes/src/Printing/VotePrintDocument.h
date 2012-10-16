/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _VOTEPRINTDOCUMENT_H_
#define _VOTEPRINTDOCUMENT_H_

#include "Printing/BasePrintDocument.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include "Printing/DocumentOptions.h"
#include "Voting/Election/election-schema.hxx"
#include "Voting/Vote/vote-schema.hxx"

#include <iostream>
#include "Voting/Vote/vote-schema.hxx"
#include <Voting/ElectoralConfiguration.hxx>
#include <System/SafeBuffer.h>


namespace Smartmatic
{
	namespace
	{
		class Log;
	}

	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @brief	Vote print document. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class VotePrintDocument : public BasePrintDocument
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	electoralConfiguration	The electoral configuration.
   				 * @param [in,out]	voteRecovery			The vote recovery transformer.
				 * @param	vote						  	The vote.
				 * @param	forceGtkPrinting			  	true to force gtk printing.
				 */

				VotePrintDocument ( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, 
				                   const Smartmatic::SAES::Voting::Vote::Vote & vote, bool forceGtkPrinting = false,
				                   bool showBarCode = true, bool screenPreview = false);

				/**
				 * @brief	Print vote.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	vote	The vote.
				 */

				void PrintVote(const Smartmatic::SAES::Voting::Vote::Vote & vote);

				/**
				 * @brief	Gets a qr code vote.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	vote		   	The vote.
				 * @param	useBase64	   	true to use base 64.
				 * @param	pixelSize	   	Size of the pixel.
				 * @param	margin		   	The margin.
				 * @param	version		   	The version.
				 * @param	correctionLevel	The correction level.
				 *
				 * @return	The qr code vote.
				 */

				Glib::RefPtr<Gdk::Pixbuf> GetQRCodeVote(const Smartmatic::SAES::Voting::Vote::Vote & vote );

				void CommandPrintQRCode (const Smartmatic::SAES::Voting::Vote::Vote & vote);

				static void calculateMax(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

			protected:

				/**
				 * @brief	Print thread.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void PrintThread();

				/**
				 * @brief	Print document.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void PrintDoc();

				/**
				 * @brief	Begins a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void BeginPrint();

				/**
				 * @brief	Ends a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void EndPrint();

				//Glib::ustring CompressVote(const Smartmatic::SAES::Voting::Vote::Vote & vote );

				/**
				 * @brief	Gets a qr code vote internal.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	vote		   	The vote.
				 * @param	useBase64	   	true to use base 64.
				 * @param	pixelSize	   	Size of the pixel.
				 * @param	margin		   	The margin.
				 * @param	version		   	The version.
				 * @param	correctionLevel	The correction level.
				 *
				 * @return	The qr code vote internal.
				 */

				Glib::RefPtr<Gdk::Pixbuf> GetQRCodeVoteInternal(const Smartmatic::SAES::Voting::Vote::Vote & vote, bool useBase64, Smartmatic::SAES::Configuration::QRCodeConfig & config );
				Glib::RefPtr<Gdk::Pixbuf> pixbufptrThread;  ///< The pixbufptr thread
				Glib::RefPtr<Gdk::Drawable> drwptrThread;   ///< The drwptr thread
				gint widthThread;   ///< The width thread
				gint heightThread;  ///< The height thread

				/**
				 * @brief	Adds a vote header. 
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	vote	The vote.
				 */

				void AddVoteHeader(const Smartmatic::SAES::Voting::Vote::Vote & vote);

				/**
				 * @brief	method to add a text line to the document.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	toCompose		 	text resource with place holders and translated.
				 * @param	textConfiguration	configurations of the text block.
				 * @param	vParam			 	vector of parameters, are taken into account the first 9.
				 */

				void AddVoteText(Glib::ustring toCompose,
				                 Smartmatic::SAES::Configuration::TextConfiguration textConfiguration,
				                 std::vector<Glib::ustring> & vParam);

				/**
				 * @brief	Adds final spaces.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void AddFinalSpaces();

				/**
				 * @brief	Adds custom attributes header.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void addCustomAttributesHeader(const Smartmatic::SAES::Voting::Vote::Vote & vote);

				/**
				 * @brief	Process the text ballot option.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	isPrincipal			true if is principal.
				 * @param	code				The code.
				 * @param	fullName			Name of the full.
				 * @param	maxLastNameChars	The maximum last name characters.
				 * @param	maxNameChars		The maximum name characters.
				 * @param	maxCodeChars		The maximum code characters.
				 *
				 * @return	.
				 */

				Glib::ustring ProcessTextBallotOption(
						bool isPrincipal,
						Glib::ustring code,
						Glib::ustring fullName,
						int maxLastNameChars = 0,
						int maxNameChars = 0,
						int maxCodeChars = 0);

				/**
				 * @brief	Gets a custom attribute value.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	contestWrapper	The contest wrapper.
				 * @param	vote		  	The vote.
				 *
				 * @return	The custom attribute value.
				 */

				Glib::ustring GetCustomAttributeValue(
						const Smartmatic::SAES::Voting::Election::Contest & contestWrapper,
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						const Smartmatic::SAES::Voting::Election::Contest_class & contestClass);

				/**
				 * @brief	Evaluate text.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	key	The key.
				 *
				 * @return	.
				 */

				Glib::ustring EvaluateText(Glib::ustring key);

				Glib::RefPtr<Gdk::Pixbuf> pixbufBarCode;	///< The pixbuf bar code

			private:

                Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;  ///< The electoral configuration
                const Smartmatic::SAES::Voting::Vote::Vote & _vote;
				std::map <std::string, std::string> recoveryVoteMap; ///< Contest->Binary Map

				Smartmatic::SAES::Voting::VotingDevice::Voting_booth votingBooth;
				std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > customAttributeDefinition;

				int countContest; ///< counter current contest
				int countLinesList; ///< counter lines of ballot option list in current vote
				int countLinesBallotOption; ///< counter lines of ballot option in current vote
				int countLinesTotalList; ///< counter lines of total ballot option in current vote
				int countLinesTotalBallotOption; ///< counter lines of total ballot option in current vote

				int countContestName1;
				int countContestName2;
				int countContestName3;

				bool viewPrincipalTitle; ///< flag view principal title
				bool viewStandInTitle; ///< flag view stand in title

				int _maxBallotOptionLastNameChars;  ///< The maximum ballot option last name characters
				int _maxBallotOptionNameChars;  ///< The maximum ballot option name characters
				int _maxBallotOptionCodeChars;  ///< The maximum ballot option code characters
				
				Glib::ustring strContestClassName;
				Glib::ustring strContestClassDescription;
				Glib::ustring strContestTitle;
				Glib::ustring strContestAbstract;
				Glib::ustring strContestHelp;
				Glib::ustring strContestBinaryRecovery;
				Glib::ustring customAttributeValue;
				Glib::ustring strEligibleOptionBallotName;
				Glib::ustring strBallotOptionPartyName;
				Glib::ustring strBallotOptionPartyAbbreviation;

				Glib::ustring strElectionName; ///< Election name
				Glib::ustring strElectoralOrg; ///< ElectoralOrganization
				Glib::ustring strPollingPlaceName; ///< Polling Place Name
				Glib::ustring strPollingPlaceAddres; ///< Polling Place Addres

				bool showBarCode;  ///< The show barcode

				DocumentTextOptions _textOptionGeneric; ///< The text option generic

				Glib::ustring _charPadding; ///< The character padding

				void getQRCodeData (const Smartmatic::SAES::Voting::Vote::Vote & vote, Smartmatic::System::SafeBuffer & dataOut);

				/**
				 * @brief Method set ballot title in print vote
				 * @param ballot
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setBallotTitle( const Smartmatic::SAES::Voting::Election::Ballot & ballot );

				/**
				 * @brief Method set top element in print vote
				 * @param vote vote
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setTopVote( const Smartmatic::SAES::Voting::Vote::Vote & vote);

				/**
				 * @brief Method set center element in print vote
				 * @param vote
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setCenterVote( const Smartmatic::SAES::Voting::Vote::Vote & vote);

				/**
				 * @brief Method set bottom element in print vote
				 * @param vote
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setBottomVote( const Smartmatic::SAES::Voting::Vote::Vote & vote);

				void setSuperNull();

				void setContest(
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						Smartmatic::SAES::Voting::Election::Contest & contest,
						const Smartmatic::SAES::Voting::Vote::Selection & selection);

				void setBallotOptionInfo(
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						Smartmatic::SAES::Voting::Election::Contest & contest,
						const Smartmatic::SAES::Voting::Vote::Selection & selection);

				void setContestTitle(
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						Smartmatic::SAES::Voting::Election::Contest & contest);

				Glib::ustring getComposeMessage( Glib::ustring messageToCompose );

				void setTitleReferendum();

				void setContestList(
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						Smartmatic::SAES::Voting::Election::Contest & contest,
						std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & list,
						const Smartmatic::SAES::Voting::Vote::Selection & selection );

				void setContestBallotOption(
						const Smartmatic::SAES::Voting::Vote::Vote & vote,
						Smartmatic::SAES::Voting::Election::Contest & contest,
						const Smartmatic::SAES::Voting::Vote::Selection & selection,
						std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & listBallotOptionPrincipal,
						std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & listBallotOptionStandIn,
						bool isQuestion);

				void setBallotOptions(Smartmatic::SAES::Voting::Election::Contest & contest,
						std:: vector < Smartmatic::SAES::Voting::Election::Ballot_option > & list,
						Smartmatic::SAES::Configuration::LayoutContestConfiguration & layout,
						bool isPrincipal,
						bool isQuestion);

				/**
				 * @brief Method set blank space in end contest
				 * @param contestCode contest code
				 * @param addEndSpace add end space contest
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestBlankSpace( Glib::ustring contestCode, bool addEndSpace );

				/**
				 * @brief Method set blank space by title principal config
				 * @param count count line space, default 1
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestTitlePrincipalSpace( int count = 1 );

				/**
				 * @brief Method set blank space by title stand in config
				 * @param count count line space, default 1
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestTitleStandInSpace( int count = 1 );

				/**
				 * @brief Method set blank space by end config
				 * @param count count line space, default 1
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestEndSpace( int count = 1 );

				/**
				 * @brief Method set blank space by list config
				 * @param countList
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestListSpace(int countList);

				/**
				 * @brief Method set blank space bay ballot config
				 * @param countBallot
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setContestBallotSpace(int countBallot);

				/**
				 * @brief Method set blank space in end vote
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				void setBlankSpaceVote();
				/**
				 * @brief Method translate text languages
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 19-04-2012
				 */
				void translateText();
				/**
				 * @brief Method clear text languages
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 19-04-2012
				 */
				void clearText();
				/**
				 * @brief Method concatenate all text languages
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 19-04-2012
				 */
				void concatenateText();
				/**
				 * @brief Method concatenate all text languages
				 * @param text text
				 * @param result result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 19-04-2012
				 */
				void concatenateText(Glib::ustring text, Glib::ustring & result);
				/**
				 * @brief Method set resource text all languages
				 * @param key key name
				 * @return text resource
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 19-04-2012
				 */
				Glib::ustring getResource(Glib::ustring key);

				/**
				 * @brief Method calculate max ballot by simple layout
				 * @param electoralConfiguration electoral configuration
				 *
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				static void calculateMaxBySimpleLayout(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

				/**
				 * @brief Method calculate max ballot by truncate layout
				 * @param electoralConfiguration electoral configuration
				 *
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 29-07-2011
				 */
				static void calculateMaxByTruncateLayout(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

				bool isMultiLanguage; ///< flag multi language vote
				Glib::ustring separatorLanguage; ///< separator for multi language
				unsigned maxCharByLanguage; ///< max char by language

				Glib::ustring strDemoTitle; ///< demo title
				Glib::ustring strRecoveryTitle; ///< recovery title
				Glib::ustring strSimulatedTitle; ///< simulated title

				Glib::ustring strNullReferendum; ///< null referendum
				Glib::ustring strNullVote; ///< null vote
				Glib::ustring strTitleReferendum; ///< title referendum

				Glib::ustring strParentOptionMessage; ///< parent option message
				Glib::ustring strParentOptionWasSelected; ///< parent option selected

				Glib::ustring strPrincipalTitleReferendum; ///< principal title referendum
				Glib::ustring strPrincipalNoSelectectedMessage; ///< principal no selected message
				Glib::ustring strPrincipalMessage; ///< principal message

				Glib::ustring strStandInTitleReferendum; ///< stand in title referendum
				Glib::ustring strStandInNoSelectedMessage; ///< stand in no selected message
				Glib::ustring strStandInMessage; ///< stand in message

				Glib::ustring strDemoEnd; ///< demo end
				Glib::ustring strRecoveryEnd; ///< recovery end
				Glib::ustring strSimulatedEnd; ///< simulate end

				Glib::ustring separatorName; ///< separator name config
				static int maxList; ///<max list count
				static int maxBallotOptions; ///< max ballot option count
				static std::map < std::string, int > maxLineListOptions; ///< map max line list options
				static std::map < std::string, int > maxLineBallotOptions; ///< map max line ballot options
				static Smartmatic::Log::ISMTTLog* logger; ///<logger
                                
				Smartmatic::SAES::Configuration::ConfigurationVote printConfiguration;
				Smartmatic::SAES::Configuration::LayoutContestConfiguration layout;
			};
		}
	}
}

#endif // _VOTEPRINTDOCUMENT_H_
