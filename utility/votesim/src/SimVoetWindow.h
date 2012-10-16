/*
 * SimVoetWindow.h
 *
 *  Created on: Aug 17, 2011
 *      Author: fgomez
 */

#ifndef SIMVOETWINDOW_H_
#define SIMVOETWINDOW_H_

#include <gtkmm.h>
#include <Windows/basic-window.h>
#include "Voting/VotingCenters/voting-centers-schema.hxx"
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <System/Exception/CryptoException.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/Election/ElectionWrapper.hxx>
#include <Voting/VotingDevice/VotingDeviceWrapper.hxx>
#include <map>
#include <vector>

class SimVoteWindow : public Smartmatic::GUI::Windows::BasicWindow
{
public:
	SimVoteWindow();
	virtual ~SimVoteWindow();

private:
	void on_exit_clicked();
	void on_load_clicked();
	void on_run_clicked();
	void RunSimulation();
	void PrintVote();

	bool loadConfiguration(std::string pass);
	Gtk::Label title_label;
	Gtk::HBox 	hbox;
	Gtk::Button 	exit;

	Gtk::Fixed* fixedContainer;
	Gtk::Button* buttonLoad;
	Gtk::Button* buttonRun;
	Gtk::Entry* entryPassPhrase;
	Gtk::Entry* entryNumber;
	Gtk::Label* labelCenter;
	Gtk::TextView* textviewOut;
	Gtk::CheckButton * fullVote;

	std::string votingCenterName;
	Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
	std::list< Smartmatic::SAES::Voting::VotingCenters::VotingCenter > votingCenters;   ///< The voting centers
	Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;

	Glib::Thread* simulationThread;

	bool start;
	bool configLoaded;
	int VotesToSimulate;
	bool exitThread;

	Smartmatic::SAES::Voting::Vote::Vote currVote;

	Glib::Dispatcher signal_printVote;

	Glib::Mutex cond_mutex;

	Glib::Cond print_cond;

	bool votePrinted;


};

#endif /* SIMVOETWINDOW_H_ */
