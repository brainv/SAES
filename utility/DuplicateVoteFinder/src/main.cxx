/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Yadickson Soto 2011 <yadickson.soto@smartmatic.com>
 * 
 * barcode-vote is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * barcode-vote is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <gtkmm.h>
#include <config.h>

#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/MemoryPathController.h>
	
#include "Barcode.hxx"
#include "VoteRecorder.hxx"
#include "MyHelpers.hxx"

#define LOG_CONF_FILENAME LOGDATADIR"/log4-configuration.xml"

using namespace Smartmatic::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;

/**
*	-o for output directory
*	-i for input directory
*	-D for debug information
*	-v for verbose mode
*	-L for output file for vote's codes
*	-h for help
**/
struct duplicateVoteArgs_t 
{
	std::string outputDirectory;
	std::string inputDirectory;
	bool debug;
	bool verbose;
	bool help;
	bool logVoteCode;
	std::string voteCodeLogFile;
} args;
static const char *optString = "o:i:DvhL";

bool writeToVoteCodeLog(std::string msg)
{
	std::ofstream file;
	file.open(args.voteCodeLogFile.c_str(), std::ios::out | std::ios::app);
	if(file.fail())
		return false;
	file << msg << std::endl;
	file.close();
	return true;
}

void printVoteRecorderInfo() 
{
	static int last;
	const int total = VoteRecorder::getInstance()->getTotalReaded();
	if(last == total) 
		return;
	const int valid = VoteRecorder::getInstance()->getTotalValid();
	const int duplicated = total - valid;
	std::stringstream stream;
	if(args.verbose)
	{
		stream << "-------------------------------------------------" << std::endl;
		stream << "*\tTotal\tValid\tDuplicated\t\t*" << std::endl;
		stream << "*\t  " << total << "\t  " << valid << "\t     " << duplicated << "\t\t\t*" << std::endl;
		stream << "-------------------------------------------------" << std::endl;
		std::cerr << stream.str();

		std::vector<std::string> lastRepeatedVotes = VoteRecorder::getInstance()->getLastRepeatedVotes();
		if(lastRepeatedVotes.empty() == false)
		{
			for(unsigned int i=0; i<lastRepeatedVotes.size(); ++i)
			{
				std::cerr << "Duplicated vote found with code " << lastRepeatedVotes[i] << " has " << VoteRecorder::getInstance()->getVoteCount(lastRepeatedVotes[i]) << " appearances" << std::endl;
			}
		}

	}
	if(args.logVoteCode)
	{
		std::vector<std::string> lastVotes =  VoteRecorder::getInstance()->getLastVoteCodes();
		for(unsigned int i=0; i<lastVotes.size(); ++i)
		{
	    	if(writeToVoteCodeLog(lastVotes[i]+MyHelpers::getCurrentTime())==false)
				if(args.verbose)
					std::cerr << "Unable to log vote code " << lastVotes[i] << " in " << args.voteCodeLogFile << " file" << std::endl;
		}
	}
	last = total;
}

void InfiniteBarcodeReading() 
{
	Barcode barcode;
	while(true)
	{
		usleep(100);
		printVoteRecorderInfo();
	}
}

bool createOutputDirectory() {
	bool returnValue = false;
	int ecode = mkdir(args.outputDirectory.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(ecode == -1) 
	{
		if(opendir(args.outputDirectory.c_str())!=NULL)
		{
			std::cerr << "Output directory \"" << args.outputDirectory << "\" already exist" << std::endl;
			returnValue = true;
		}
		else
		{
			std::cerr << "Unable to create votelog directory" << std::endl;
		}
	}
	else
	{
		std::cerr << "Output directory \"" << args.outputDirectory << "\" successfully created" << std::endl;
		returnValue = true;
	}
	return returnValue;
}

int showHelp() {
	std::cerr << crappyHelp;
	return 0;
}

int init()
{
	if(args.help)
		return showHelp();
	if(!Glib::thread_supported())
	{
		Glib::thread_init();
	}
	if(!createOutputDirectory())
	{
		std::cerr << "No valid output directory for scanned votes. Will not be saved any scanned vote information" << std::endl;
	}
	else
	{
		VoteRecorder::getInstance()->setOutputDirectory(args.outputDirectory);	
	}
	if(writeToVoteCodeLog("New run on " + MyHelpers::getCurrentTime())==false)
		std::cerr << "Unable to set breakpoint on voteCodeLog.log file" << std::endl;

	if(args.inputDirectory!="")
	{
		VoteRecorder::getInstance()->setInputDirectory(args.inputDirectory);
		if(!VoteRecorder::getInstance()->loadVotes())
			std::cerr << "Unable to load stored data. Initial data set will be empty" << std::endl;
		else if(args.verbose)
			std::cerr << "Votes successfully loaded from input directory" << std::endl;
	}

	if(args.debug)
	{
		SMTTLogManager::Configure(LOG_CONF_FILENAME);


		PrinterBackendType & backend (SAESCommonConfigurationManager::Current()->getPrinterBackendType());
		backend = PrinterBackendType::CONFIGURATION_DIRECTPRINTING;

		/*ConfigurationBasePath & basePath (SAESCommonConfigurationManager::Current()->getConfigBasePath());
		basePath.setRulesBasePath(RulesBasePathType::CONFIGURATION_VM_RULE);		*/
	}

	return 0;
}

void set_args(int argc, char *argv[]) 
{
	char buff[1024];
	args.outputDirectory = std::string(getcwd(buff, 1024)) + "/votelog";
	args.inputDirectory = "";
	args.voteCodeLogFile = std::string(getcwd(buff, 1024)) + "/votelog/voteCodeLog.log";
	args.debug = true; //should be false by default...
	args.verbose = false;
	args.help = false;
	args.logVoteCode = true; //should be false by default
	
	int opt = getopt( argc, argv, optString );
    while( opt != -1 ) 
	{
        switch( opt ) 
		{
            case 'o':
                args.outputDirectory = optarg;
                break;
                
            case 'i':
                args.inputDirectory = optarg;
                break;
                
            case 'D':
                args.debug = true;
                break;
                
            case 'v':
                args.verbose = true;
                break;
                
            case 'h':
				args.help = true;
                break;
                
			case 'L':
				args.logVoteCode = true;
                break;

            default:
                /* You won't actually get here... */
                break;
        }        
        opt = getopt( argc, argv, optString );
    }
}

int main(int argc, char *argv[])
{
	set_args(argc, argv);
	if(init()==0)
		return 0;
	InfiniteBarcodeReading();
	return 0;
}
