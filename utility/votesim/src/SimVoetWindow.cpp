/*
 * SimVoetWindow.cpp
 *
 *  Created on: Aug 17, 2011
 *      Author: fgomez
 */

#include <config.h>
#include "SimVoetWindow.h"
#include <Security/SecretKey.h>
#include "smartmatic/System/Exception/SecretKeyException.h"
#include <Security/Encryption.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Voting/Vote/vote-schema.hxx>
#include <Voting/Vote/VoteWrapper.hxx>
#include "Printing/VotePrintDocument.h"
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Voting/set-language-functionality.h>

#define UI_FILE DATADIR"/"PACKAGE_NAME"/ui/votesim.ui"

using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Common::Configuration;


using namespace Smartmatic::SAES::Operation;
//using namespace Smartmatic::SAES::GUI::Windows;
//using namespace Smartmatic::SAES::GUI::Configuration;
//using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::System::Exception;
//using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Common::Security;
using namespace Smartmatic::System::Security;
//using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
//using namespace Smartmatic::SAES::Resources;
//using namespace Smartmatic::SAES::Configuration;
//using namespace Smartmatic::SAES::Operation;
//using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting::Vote;

SimVoteWindow::SimVoteWindow(): BasicWindow (false,true),
		fixedContainer(NULL),
		buttonLoad(NULL),
		buttonRun(NULL),
		entryPassPhrase(NULL),
		entryNumber(NULL),
		labelCenter(NULL),
		textviewOut(NULL),
		simulationThread(NULL)
{

	start = true;
	configLoaded = false;
	exitThread = false;
	// TODO Auto-generated constructor stub
	set_size_request(1024, 768);
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}
	//exit
	exit.set_label("Exit");
	exit.signal_clicked().connect( sigc::mem_fun(*this,
			&SimVoteWindow::on_exit_clicked) );
	exit.set_visible(true);


	//title
	title_label.set_text("VOTE SIMULATOR");
	title_label.set_visible(true);


	hbox.pack_end(exit);
	hbox.pack_start(title_label);
	hbox.set_visible(true);

	setTitle(&hbox);

	builder->get_widget("fixedContainer",this->fixedContainer);
	builder->get_widget("buttonLoad",this->buttonLoad);
	builder->get_widget("buttonRun",this->buttonRun);

	builder->get_widget("entryPassPhrase",this->entryPassPhrase);

	builder->get_widget("entryNumber",this->entryNumber);
	builder->get_widget("labelCenter",this->labelCenter);

	builder->get_widget("textviewOut",this->textviewOut);
	builder->get_widget("full-vote",this->fullVote);

	this->setWidget(fixedContainer);


	buttonLoad->signal_clicked().connect( sigc::mem_fun(*this,
			&SimVoteWindow::on_load_clicked) );
	buttonRun->signal_clicked().connect( sigc::mem_fun(*this,
			&SimVoteWindow::on_run_clicked) );

	signal_printVote.connect(sigc::mem_fun(*this, &SimVoteWindow::PrintVote));


}

SimVoteWindow::~SimVoteWindow() {
	// TODO Auto-generated destructor stub
	if(fixedContainer)
		delete(fixedContainer);
	if(buttonLoad)
		delete(	buttonLoad);
	if(buttonRun)
		delete(buttonRun);
	if(entryPassPhrase)
		delete(entryPassPhrase);
	if(entryNumber)
		delete(entryNumber);
	if(labelCenter)
		delete(labelCenter);
	if(textviewOut)
		delete(textviewOut);
}


void SimVoteWindow::on_exit_clicked()
{
	hide();
}

void SimVoteWindow::on_run_clicked()
{
	if(configLoaded)
	{
		if(start)
		{
			start = false;
			buttonRun->set_sensitive(false);
			exitThread = false;
			VotesToSimulate = atoi(this->entryNumber->get_text().c_str());
			simulationThread = Glib::Thread::create(sigc::mem_fun(*this, &SimVoteWindow::RunSimulation), true);
		}
		else
		{
			exitThread = true;
			buttonRun->set_sensitive(true);
			simulationThread->join();
			simulationThread = NULL;
			start = true;
		}
	}
}



void SimVoteWindow::on_load_clicked()
{
	electoralConfiguration = MachineOperationManager::getInstance()->getElectoralConfiguration();

	std::string localFileFullPath = directories.getVotingCentersLocalFileFullPath();

	Smartmatic::SAES::Voting::VotingCenters::VotingCentersWrapper::getInstance()->LoadFile(localFileFullPath);

	votingCenters = Smartmatic::SAES::Voting::VotingCenters::VotingCentersWrapper::getInstance()->getVotingCenters();
	using namespace Smartmatic::SAES::Common::Configuration;
	std::string passphrase =this->entryPassPhrase->get_text();


	bool parametersOk = loadConfiguration(passphrase);

	if(parametersOk)
	{
		configLoaded = true;
		this->labelCenter->set_text("Voting Center: "+ votingCenterName);
	}
	else
	{
		configLoaded = false;
		this->labelCenter->set_text("Cannot Load Data.. Check Password or files" );
	}

}


bool SimVoteWindow::loadConfiguration(std::string pass)
{
	bool loginOk = false;

	if (VotingCentersWrapper::getInstance()->isInstall())
	{
		VotingCenter votingCenter;
		VotingCentersWrapper::getInstance()->getInstallationVotingCenter(votingCenter);
		votingCenterName = votingCenter.getCode();
	}

	std::cout << "Center : " << votingCenterName << std::endl;

	loginOk = MachineOperationManager::getInstance()->authentication(votingCenterName, pass, true);

	//Load precalculate other info needed for the VM
	try
	{
		if(loginOk)

		{

		loginOk = false;

		electoralConfiguration->loadAllData();
		Smartmatic::SAES::Printing::VotePrintDocument::calculateMax(electoralConfiguration);

		std::string openingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getOpening_date_time();
		std::string closingDateTime = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getClosing_date_time();

		Glib::TimeVal openingTime;
		Glib::TimeVal closingTime;

		openingTime.assign_from_iso8601(openingDateTime);
		double openingD = openingTime.as_double();

		closingTime.assign_from_iso8601(closingDateTime);
		double closingD = closingTime.as_double();

		Smartmatic::SAES::Security::Encryption::getInstance()->setMachineTime(openingD + (openingD + closingD)/2);

		Smartmatic::SAES::Voting::OperationStatus::Current()->init();
		Glib::ustring openingCode = Smartmatic::SAES::Voting::OperationStatus::Current()->getElectionStatusWrapper()->getOpeningCode();
		Smartmatic::System::GuidClass openCodeGUID = Smartmatic::System::GuidClass::Parse(openingCode);
		Smartmatic::SAES::Security::Encryption::getInstance()->setOpeningCode(openCodeGUID);

		//Clear previous language
		ElectionInstalationLanguages::getInstance()->clearLanguage();

		Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & sequence (electoralConfiguration->getLanguages().getLanguage());

		for (Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it = sequence.begin(); it != sequence.end(); ++it)
		{
			ElectionInstalationLanguages::getInstance()->addInstallationLanguages((*it));
			Smartmatic::SAES::Voting::SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(it->getLanguage(),it->getCountry());
			break;
		}


		loginOk = true;
		}
	}
	catch(ElectionException & ex)
	{

		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;

	}
	catch(VotingDeviceException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(CryptoException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(SignedException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(XmlException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(GuIdException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(FileSystemException & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(std::exception & ex)
	{
		std::cout << "FATAL "<<__func__<< ex.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "FATAL "<<__func__<< "Unknown exception" << std::endl;
	}



	return loginOk;
}

void SimVoteWindow::RunSimulation()
{
	//Get the list of LVG
	Voting_device votingDevice = electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
	std::list < Logical_voter_group > & lvgs (electoralConfiguration->getLogicalVoterGroupList());
	std::list < Logical_voter_group >::iterator itlvg;

	std::vector < Logical_voter_group > logicalVoterGroups;
	std::map < std::string, std::vector < std::string > > contestByContestGroup;
	std::map < std::string, std::vector < std::string > > partiesByContest;

	bool full = fullVote->get_active();

	for (itlvg = lvgs.begin();
			itlvg != lvgs.end();
			itlvg++)
	{
		Logical_voter_group lvg = (*itlvg);
		logicalVoterGroups.push_back(lvg);
		std::string contestGroupCode = lvg.getContest_group_code();

		std::list < Contest > & contestList (electoralConfiguration->getListContestByContestGroupCode(contestGroupCode));
		std::list < Contest >::iterator itcontest;

		std::cout << "contestGroupCode : " << contestGroupCode << std::endl;

		for (itcontest = contestList.begin();
				itcontest != contestList.end();
				itcontest++)
		{
			Contest contest = (*itcontest);
			std::string contestCode = contest.getCode();
			contestByContestGroup[contestGroupCode].push_back(contestCode);

			std::list < Party > & parties (electoralConfiguration->getListPartyByContestCode (contestCode));
			std::list < Party >::iterator itparty;

			std::cout << " - contest " << contestCode << std::endl;

			for (itparty = parties.begin();
					itparty != parties.end();
					itparty++)
			{
				partiesByContest[contestCode].push_back((*itparty).getCode());
				std::cout << " - party " << (*itparty).getCode() << std::endl;
			}
		}

	}

	Glib::ustring msg;

	for(int i = 0; (i < VotesToSimulate) &&  (exitThread == false) ; i++)
	{
		int maxLVG = logicalVoterGroups.size();
		int lvgoffset = rand() % maxLVG;

		Logical_voter_group lvgSim = logicalVoterGroups[lvgoffset];

		currVote.setVotingDeviceCode( votingDevice.getCode());
		currVote.setLan_code("fr_BE" );
		currVote.setMode (Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O);
		currVote.setLogicalVoterGroup(lvgSim.getCode());
		currVote.getSelections().clear();

		Smartmatic::SAES::Voting::Vote::Vote::SSequence sseq;

		for(unsigned int j=0; j < contestByContestGroup[lvgSim.getContest_group_code()].size() ; j++ )
		{
			std::string contSim = contestByContestGroup[lvgSim.getContest_group_code()][j];

			int maxParties = partiesByContest[contSim].size();
			int partyOffset = rand() % maxParties;

			std::string partySim = (partiesByContest[contSim])[partyOffset];

			std::list < Ballot_option > & eligibleOptionList (electoralConfiguration->getBallotOptionsListByContestParty(contSim, partySim));
			std::list < Ballot_option > & eligibleOptionPrincipal (electoralConfiguration->getBallotOptionsPrincipalByContestParty(contSim, partySim));
			std::list < Ballot_option > & eligibleOptionStandIn (electoralConfiguration->getBallotOptionsStandInByContestParty(contSim, partySim));


			std::cout << "----------------" << std::endl;
			std::cout << "Count list : " << eligibleOptionList.size () << std::endl;
			std::cout << "Count principal : " << eligibleOptionPrincipal.size () << std::endl;
			std::cout << "Count stand in : " << eligibleOptionStandIn.size () << std::endl;
			std::cout << "----------------" << std::endl;

			std::list < Ballot_option >::iterator iteo;
			std::vector<std::string> boCodes;

			for (iteo = eligibleOptionList.begin();
					iteo != eligibleOptionList.end();
					iteo++)
			{
				if (full || rand() % (eligibleOptionList.size()+1) % 2 == 0)
				{
					boCodes.push_back((*iteo).getCode());
				}
			}

			for (iteo = eligibleOptionPrincipal.begin();
					iteo != eligibleOptionPrincipal.end();
					iteo++)
			{
				if (full || rand() % (eligibleOptionPrincipal.size()+1) % 2 == 0)
				{
					boCodes.push_back((*iteo).getCode());
				}
			}

			for (iteo = eligibleOptionStandIn.begin();
					iteo != eligibleOptionStandIn.end();
					iteo++)
			{
				if (full || rand() % (eligibleOptionStandIn.size()+1) % 2 == 0)
				{
					boCodes.push_back((*iteo).getCode());
				}
			}

			std::cout << "contest = " << contSim << " party = " << partySim << " count = " << boCodes.size() << std::endl;
			std::cout << "----------------" << std::endl;

			Smartmatic::SAES::Voting::Vote::Selection::BSequence bseq;
			Smartmatic::SAES::Voting::Vote::Selection selection;
			selection.setContest ( contSim );

			for (std::vector<std::string>::iterator boI (boCodes.begin ());
					boI != boCodes.end (); ++boI)
			{
				bseq.push_back( *boI );
			}

			selection.setBallotOptions( bseq );
			sseq.push_back( selection );
		}

		currVote.setSelections(sseq);
		std::string voteCode = Smartmatic::SAES::Voting::Vote::VoteWrapper::generateCode(currVote);
		currVote.setCode(voteCode);
		//Print the vote
		votePrinted = false;

		signal_printVote();
		usleep(500000);
		std::cout << "Waiting for the vote to be printed" << std::endl;
		while (votePrinted == false)
		{

			print_cond.wait(cond_mutex);
			std::cout << "Continue to next vote" << std::endl;
		}
	}

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &SimVoteWindow::on_run_clicked), 100);
}

void SimVoteWindow::PrintVote()
{
	Glib::Mutex::Lock lock (cond_mutex);

	Smartmatic::SAES::Printing::VotePrintDocument voteReceipt(electoralConfiguration,currVote );

	std::cout << " *****************   Printing Vote   ****************  " << std::endl;
	voteReceipt.Print();
	std::cout << " *****************   Vote Printed  ****************  " << std::endl;
	votePrinted = true;
	print_cond.signal();
}
