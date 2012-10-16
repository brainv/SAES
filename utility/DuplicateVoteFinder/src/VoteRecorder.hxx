/*
 * ProcessVote.hxx
 *
 *  Created on: 17/07/2012
 *      Author: Ampuero
 */

#ifndef VOTERECORDER_HXX_
#define VOTERECORDER_HXX_

#include <Voting/Vote/vote-schema.hxx>
#include <System/SafeBuffer.h>
#include "Log/ISMTTLog.h"

#include <map>
#include <string>
#include <vector>

/**
*	Class for processing and register scanned votes. It should be used as a tool
*	for find duplicated votes.
*	In order to avoid errors counting, this class is implemented as a Singleton.
*	WARNING: 
*		This class IS NOT thread safe
*	@author Daniel Ampuero
*/
class VoteRecorder
{
private:
	/**
	*	Static reference for VoteRecorder class.
	*/
	static VoteRecorder* instance;

protected:
  /**
  * Stores the count of repeated votes by vote code
  **/
	std::map<std::string, int> voteCounter;

  /**
  * Stores the time when each vote was stored
  */
  std::map<std::string, std::vector<std::string> >voteTime;

  /**
  * The output directory where the vote files will be written
  */
	std::string outputDirectory;

  /**
  * The input directory where the stored votes on previous scannings
  * will be loaded.
  */
	std::string inputDirectory;

  /**
  * Last scanned vote codes
  */
	std::vector<std::string> lastVoteCodes;

  /**
  * Last repeated scanned votes
  */
  std::vector<std::string> lastRepeatedVotes;

  /**
  * Total counting of votes readed either by scanning or loading from
  * the input directory
  */
	int totalReadedVotes;

  /**
  * Total bad formed votes
  */
  int totalBadVotes;

  /**
  * Log
  */
  Smartmatic::Log::ISMTTLog* logger;

  /**
  * Default constructor
  */
	VoteRecorder();

  /**
  * Default destructor
  */
	~VoteRecorder();

  /**
  * Loads a sigle vote
  */
	bool loadVote(std::string fileName);

public:
  /**
  * Receive a data stream and records the votes inside it. It also prints several log
  * messages.
  * @param bufferIn Input data stream
  * @param saveInFile Optional parameter for save votes inside bufferIn in a file in outputDirectory
  * @param fromFile Optional parameter to control log message showing.
  * @param A boolean value wheter the stream was successfully recorded.
  */
	bool RecordVote(Smartmatic::System::SafeBuffer & bufferIn, bool saveInFile=true, bool fromFile=false);
  
  /**
  * Returns the number of votes readed.
  */
	int getTotalReaded(void);
  
  /**
  * Returns the number of valid votes.
  */
	int getTotalValid(void);

  /**
  * Returns the number of bad formed votes.
  */
  int getTotalBad(void);
  
  /**
  * Returns the number of duplicated votes.
  */
  int getTotalDuplicated(void);
  
  /**
  * Returns the last vote codes recordered
  */
	std::vector<std::string> getLastVoteCodes();
  
  /**
  * Returns the last repeated vote codes 
  */
  std::vector<std::string> getLastRepeatedVotes();
  
  /**
  * Returns the appereance counting for a given vote
  * @param vote The vote code requested
  */
	int getVoteCount(std::string vote);
  
  /**
  * Returns the output directory where vote files are being written
  */
	std::string getOutputDirectory();

  /**
  * Returns the output directory where vote files are being loaded
  */
	std::string getInputDirectory();

  /**
  * Sets the output directory where vote files are being loaded
  */ 
	void setInputDirectory(std::string inputDirectory);

  /**
  * Sets the output directory where vote files are being written
  */
	void setOutputDirectory(std::string outputDirectory);
  
  /**
  * Loads votes from a the input directory.
  * WARNING:
  *   If you call this function twice for the same directory,
  *   it will record and count as repeated the loaded votes 
  *   regardless they are not.
  * @return A boolean value on success
  */
	bool loadVotes();

  /**
  * Interface for get the singleto static pointer.
  */
	static VoteRecorder *getInstance();

};

#endif /* VOTERECORDER_HXX_ */
