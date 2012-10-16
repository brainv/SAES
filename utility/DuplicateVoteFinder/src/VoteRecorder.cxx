/*
 * ProcessVote.cxx
 *
 *  Created on: 17/07/2012
 *      Author: Ampuero
 */

#include <time.h>

#include <sys/types.h>
#include <dirent.h>
	
#include <fstream>
#include <iostream>
#include <list>

#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/MemoryPathController.h>
#include <Runtime/Environment/filename-hasher.h>
#include <System/Compression/compression-class.h>
#include <Voting/Vote/VoteWrapper.hxx>

#include <gtkmm.h>
#include <config.h>

#include "VoteRecorder.hxx"
#include "SaveVote.hxx"
#include "MyHelpers.hxx"

using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::Log;


VoteRecorder::VoteRecorder()
{
	totalReadedVotes = 0;
  totalBadVotes = 0;
  logger = SMTTLogManager::GetLogger("DuplicateFinder.VoteRecorder", "DuplicateFinder");
}

VoteRecorder::~VoteRecorder() { }

VoteRecorder* VoteRecorder::instance;

VoteRecorder* VoteRecorder::getInstance()
{
	if(instance == NULL)
		instance = new VoteRecorder();
	return instance;
}

std::string VoteRecorder::getOutputDirectory()
{
	return outputDirectory;
}

std::string VoteRecorder::getInputDirectory() 
{
	return inputDirectory;
}

void VoteRecorder::setInputDirectory(std::string inputDirectory) 
{
	this->inputDirectory = inputDirectory;
}

void VoteRecorder::setOutputDirectory(std::string outputDirectory)
{
	this->outputDirectory = outputDirectory;
}

std::vector<std::string> VoteRecorder::getLastVoteCodes()
{
	return lastVoteCodes;
}

std::vector<std::string> VoteRecorder::getLastRepeatedVotes()
{
  return lastRepeatedVotes;
}

int VoteRecorder::getVoteCount(const std::string voteCode)
{
	if(voteCounter.count(voteCode)==0)
		return 0;
	return voteCounter[voteCode];
}

int VoteRecorder::getTotalReaded(void)
{
	return totalReadedVotes;
}

int VoteRecorder::getTotalValid(void)
{
	return voteCounter.size();
}

int VoteRecorder::getTotalBad(void)
{
  return totalBadVotes;
}

int VoteRecorder::getTotalDuplicated(void)
{
  return getTotalReaded() - getTotalValid() - getTotalBad();
}

bool VoteRecorder::RecordVote(SafeBuffer & bufferIn, bool saveInFile, bool fromFile)
{
	bool validate = false;

	std::list<Smartmatic::System::SafeBuffer*> inflateData;
	CompressionClass::Inflate(bufferIn, inflateData);
  std::vector<std::string> repeatedVotes;

	if(inflateData.size() > 0)
	{
    logger->Info("Starting processing vote(s)");
    if(inflateData.size()>1)
    {
      char buff[32]; sprintf(buff, "%d", inflateData.size());
      logger->Warn(std::string(buff) + " votes were received\n");    
    }
    lastVoteCodes.clear();
		validate = true;
		for(std::list<Smartmatic::System::SafeBuffer*>::iterator iter = inflateData.begin(); iter != inflateData.end(); iter++) 
		{
      totalReadedVotes++;
			std::string inflatedString;
			inflatedString.append((const char *)(*iter)->GetData(), (*iter)->GetSize());
      unsigned int idx = inflatedString.find(",");
      if(idx == std::string::npos) 
      {
        ++totalBadVotes;
        continue;
      }
			std::string lastVoteCode = inflatedString.substr(0, idx);
      if(lastVoteCode.size()==0)
      {
        ++totalBadVotes;
        continue;
      }
      lastVoteCodes.push_back(lastVoteCode);
      if(fromFile)
        logger->Info("Vote " + lastVoteCode + " readed from input directory");
      else
        logger->Info("Vote " + lastVoteCode + " readed from barcode device");
      if(voteCounter.count(lastVoteCode)>0) {
        repeatedVotes.push_back(lastVoteCode);
        logger->Error("Duplicated vote code found: " + lastVoteCode);
        logger->Error("Last stored vote with code " + lastVoteCode + " was readed on " + voteTime[lastVoteCode].back()); 
      }
			voteCounter[lastVoteCode]++;
      voteTime[lastVoteCode].push_back(MyHelpers::getCurrentTime());
			FileNameHasher hasher;
			std::string file = outputDirectory + "/" + hasher.GetFileNameHasher(lastVoteCode) + ".vt";
      //logger->Info("Saving vote in " + file);
			if(SaveVote::save(file, bufferIn)==false)
        logger->Warn("Vote file " + file + " was not saved");
		}
    lastRepeatedVotes = repeatedVotes;
    logger->Info("End processing vote(s)");
    std::stringstream stream1;
	  stream1 << "Total: " << getTotalReaded() <<" Valid: " << getTotalValid() << " Duplicated: " << getTotalDuplicated() << " Bad: " << getTotalBad();
    logger->Debug(stream1.str());
	}
	else
	{
		validate = false;
	}
	return validate;
}

bool VoteRecorder::loadVote(std::string fileName) 
{
	SafeBuffer rawVote;
	if(SaveVote::open(fileName, rawVote)==false) 
	{
		logger->Warn("Unable to open " + fileName + " file");
		return false;
	}
	if(RecordVote(rawVote, false)==false) 
	{
		logger->Warn("Unable to load raw vote from " + fileName + " file");
		return false;
	}
	return true;
}

bool VoteRecorder::loadVotes() 
{
	DIR * dip = opendir(inputDirectory.c_str());
	if(dip == NULL) {
    logger->Warn("Unable to find input directory");
		return false;
  }
	struct dirent *dit;
	while ((dit = readdir(dip)) != NULL)
	{
		const std::string fileName = std::string(dit->d_name);
		if(fileName == "." || fileName == "..")
			continue;
		if(loadVote(inputDirectory+fileName) == false)
			logger->Warn("Unable to load vote file " + fileName);
	}
	return closedir(dip)==0;
}


