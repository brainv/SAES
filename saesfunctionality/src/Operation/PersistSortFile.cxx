/**
 * @file PersistSort.cxx
 * @brief Body class persist votes sort
 * @date 24/08/2011
 * @author Yadickson Soto
 */

#include "PersistSortFile.hxx"
#include <System/IO/Directory.h>
#include <System/IO/File.h>
#include <System/IO/Path.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <glibmm/timeval.h>
#include <iomanip>
#include <vector>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Voting/Vote/VoteWrapper.hxx>
#include <System/Utils/StringUtils.hxx>
#include <System/Runtime/ProcessMonitor.h>
#include <System/Runtime/ProcessLauncher.h>

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

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::System::Runtime;

ISMTTLog* PersistSortFile::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.PersistSortFile",GETTEXT_PACKAGE);

PersistSortFile::PersistSortFile(BasePathType type, std::string markFile, bool sortFile)
{
	this->type = type;
	this->markFile = markFile;
	this->sortFile = sortFile;
}

PersistSortFile::~PersistSortFile()
{
	files.clear();
}

std::string PersistSortFile::getFolder()
{
	return directories.getVotesFolderFullPath(type);
}

std::string PersistSortFile::getMarkFile()
{
	return Path::Combine(getFolder(), markFile);
}

bool PersistSortFile::isSortFile()
{
	return sortFile;
}

void PersistSortFile::updateDate(std::string date)
{
	this->date = date;
}

void PersistSortFile::addFile(std::string file)
{
	if (sortFile)
	{
		files.push_back(file);
	}
}

void PersistSortFile::persistFiles()
{
	if (sortFile)
	{
		std::string folder = getFolder();
		std::string markFileFullPath = getMarkFile();

		if (Directory::DirectoryExists(folder) &&
			!File::canOpenFile(markFileFullPath) &&
			files.size() > 0)
		{
			logger->Debug("Start persistence file system vote in " + folder);

			std::string listFile = getListFile();
			int maxfiles = SAESCommonConfigurationManager::Current()->getFileSystemVoteConfiguration().getMaxfiles();

			std::stringstream command;
			command << SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getScriptRunDSortVote();
			command << " -d " << folder;
			command << " -n " << maxfiles;
			command << " -l '" << listFile << "'";
			command << " -a " << markFile;

			if (!date.empty())
			{
				Glib::TimeVal timeVal;
				timeVal.assign_from_iso8601(date);
				// [[CC]YY]MMDDhhmm[.ss]
				time_t tim = (time_t)timeVal.as_double();
				struct tm * timeStruct =  localtime(&tim);

				command << " -t ";
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_year +1900;
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_mon +1;
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_mday;
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_hour;
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_min;
				command << ".";
				command << std::setw(2) << std::setfill('0') << (unsigned int)timeStruct->tm_sec;
			}

			command << " & ";

			logger->Debug ("Run command :   " + command.str());

			(void)ProcessLauncher::RunProcessThroughSystem (command.str().c_str());
		}
	}
}

std::string PersistSortFile::getListFile()
{
	std::string text;

	while (files.begin() != files.end())
	{
		text.append(files.front());
		text.append(" ");
		files.erase(files.begin());
	}

	return text;
}

void PersistSortFile::getVoteFile(std::list <std::string> & listTmp)
{
	std::vector<std::string> list;
	std::vector<std::string>::iterator it;

	Directory::GetFiles(getFolder(), list, false, true);

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		std::string file = *it;
		std::string ext = Path::GetFileExtension(file);

		if (ext == ".tmp")
		{
			listTmp.push_back(file);
		}
	}
}

void PersistSortFile::validateVotes(std::list <std::string> & votes)
{
	std::list <std::string>::iterator it;
	std::list <std::string> list;

	for (it = votes.begin();
		 it != votes.end();
		 it++)
	{
		std::string file = Path::Combine(getFolder(), (*it));
		Vote::Vote vote;

		if (Vote::VoteWrapper::voteFileToVote(file, vote))
		{
			list.push_back(*it);
		}
		else
		{
			logger->Debug("Delete vote file - " + file);
			File::DeleteFile(file);
		}
	}

	votes = list;
}

void PersistSortFile::renameVotes(std::list <std::string> & listTmp)
{
	std::list <std::string>::iterator it;
	std::string folder = getFolder();

	for (it = listTmp.begin();
		 it != listTmp.end();
		 it++)
	{
		std::string fileTmp = Path::Combine(folder, (*it));
		std::string fileWithOutTmp = StringUtils::replaceAll((*it), ".tmp", "");
		std::string file = Path::Combine(folder, fileWithOutTmp);
		logger->Debug("Delete file " + file);
		File::DeleteFile(file);
		logger->Debug("Rename vote file - " + (*it) + " to " + fileWithOutTmp);
		File::renameFile(fileTmp, file);
	}
}

bool PersistSortFile::recoverVotes()
{
	bool validate = true;

	if (sortFile)
	{
		std::string folder = getFolder();
		std::string markFileFullPath = getMarkFile();

		if (Directory::DirectoryExists(folder))
		{
			std::string fileName = Path::GetFileName(SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getScriptRunDSortVote());

			std::stringstream ss;
			ss << "Kill process " + fileName + " in " << type;
			logger->Debug(ss.str());
			ProcessMonitor::KillProcessAndWait(fileName);

			logger->Debug("Recover Votes in Path " + folder);

			std::list<std::string> listTmp;

			getVoteFile(listTmp);
			validateVotes(listTmp);
			renameVotes(listTmp);

			logger->Debug("Remove mark file " + markFileFullPath);
			File::DeleteFile(markFileFullPath);
		}
		else
		{
			std::stringstream ss;
			ss << "Not recover votes in " << type;
			logger->Debug(ss.str());

			validate = false;
		}
	}

	return validate;
}
