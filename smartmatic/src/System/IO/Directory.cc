/**
 * @file Directory.cc
 * @brief Body class Directory
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Directory.h"
#include "Path.h"
#include "File.h"
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <string.h>
#include <stdio.h>
#include <Log/SMTTLogManager.h>
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

using namespace std;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Runtime;

ISMTTLog* Directory::logger = SMTTLogManager::GetLogger("Smartmatic.System.IO.Directory",GETTEXT_PACKAGE);

void Directory::GetFiles(const std::string & path, std::vector<std::string>& list, bool recursive, bool relative)
{
	GetFiles(path,list,recursive);
	if(relative)
	{
	    int size = list.size();
		for(int i=0;i<size;i++)
		{
			int rootSize = path.size();
			list[i] = list[i].substr(rootSize);
				if(list[i].at(0)=='/' || list[i].at(0)=='\\')
					list[i] = list[i].substr(1);
		}
    }
}

void Directory::GetFiles(const std::string & path, std::vector<std::string>& list, bool recursive)
{
	DIR *dp;
    struct dirent *dirp;

    if((dp  = opendir(path.c_str())) == NULL) {
        return;
    }

    while ((dirp = readdir(dp)) != NULL) {
		if(dirp->d_type == DT_REG)
		{
				list.push_back(Path::Combine(path,dirp->d_name));
		}
		if(recursive && dirp->d_type == DT_DIR)
		{
			if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0)
			{
				string subdir = Path::Combine(path,dirp->d_name).append ("/");
				GetFiles(subdir,list,recursive);
			}
		}
		
    }

    closedir(dp);
}

bool Directory::DirectoryExists(const std::string & path)
{
	if (path.empty())
	{
		return false;
	}

	DIR *dp;
	if((dp  = opendir(path.c_str())) == NULL) 
	{
		return false;
	}
	else
	{
		closedir(dp);
		return true;
	}
}

void Directory::GetSubDirectories(const std::string & path, std::vector<std::string>& list, bool recursive, bool relative)
{
	GetSubDirectories(path,list,recursive);
	if(relative)
    {
        int size = list.size();
		for(int i=0;i<size;i++)
		{
			int rootSize = path.size();
			list[i] = list[i].substr(rootSize);
			if(list[i].size()>=2 && (list[i].at(0)=='/' || list[i].at(0)=='\\'))
				list[i] = list[i].substr(1);
		}
    }
}

void Directory::GetSubDirectories(const std::string & path, std::vector<std::string>& list, bool recursive)
{
	DIR *dp;
    struct dirent *dirp;

    if((dp  = opendir(path.c_str())) == NULL) {
        return;
    closedir(dp);
    }

    while ((dirp = readdir(dp)) != NULL) {
		if(dirp->d_type == DT_DIR)
		{
			if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0)
			{
				string subdir = Path::Combine(path,dirp->d_name).append ("/");
				list.push_back(subdir);
				if(recursive)
				{
					GetSubDirectories(subdir,list,recursive);
				}
			}
		}
    }

    closedir(dp);
}

void Directory::Delete(const std::string & path, bool recursive)
{
	char *cpath = new char[path.size()+1];
	strcpy (cpath, path.c_str());
	
	EmptyDirectory(path,recursive);

	if( rmdir(cpath) != 0 )
	{
		delete [](cpath);
		return;
	}
}

void Directory::Mkdir(const std::string & path)
{
    std::string command = "mkdir -p " + path;
    (void)ProcessLauncher::RunProcessThroughSystem(command.c_str());
}

void Directory::EmptyDirectory(const std::string & path, bool recursive)
{
	DIR *dp;
    struct dirent *dirp;

    if((dp  = opendir(path.c_str())) == NULL) 
	{
        return;
    }
	
	
    while ((dirp = readdir(dp)) != NULL) 
	{

		if(dirp->d_type == DT_REG)
		{   
			string pathCombine = Path::Combine(path,dirp->d_name);
			char *cpath = new char[pathCombine.size()+1];
			strcpy (cpath, pathCombine.c_str());
			
			
			 if( remove(cpath) != 0 )
			 {
				 delete [](cpath);
				 closedir(dp);
				return;
			 }
			 delete [](cpath);
		}
		
		if(recursive && dirp->d_type == DT_DIR)
		{
			if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0)
			{
				string subdir = Path::Combine(path,dirp->d_name).append ("/");
				char *cdir = new char[subdir.size()+1];
				strcpy (cdir, subdir.c_str());
				
				EmptyDirectory(subdir,recursive);

				if( rmdir(cdir) != 0 )
				{
					delete [](cdir);
					closedir(dp);
					return;
				}
				delete [](cdir);
				
			}
		}
    }

    closedir(dp);
}




bool  Directory::FileExists(const std::string & path) 
{
	ifstream ifile(path.c_str());
	return ifile;
} 

bool Directory::compareDirectories(std::string & directoryOne, std::string & directoryTwo, bool full)
{
	bool validate = false;

	logger->Debug("Compare Directories " + directoryOne + " and " + directoryTwo);

	if (DirectoryExists(directoryOne) && DirectoryExists(directoryTwo))
	{
		std::vector<std::string> vOne;
		std::vector<std::string> vTwo;
		GetFiles(directoryOne, vOne, true, true);
		GetFiles(directoryTwo, vTwo, true, true);

		validate = (vOne.size() == vTwo.size());

		if (validate)
		{
			std::list<std::string> listOne;
			std::list<std::string>::iterator it;

			listOne.insert (listOne.end(), vOne.begin(), vOne.end());

			for (unsigned int i = 0;i < vTwo.size() && validate;i++)
			{
				validate = false;

				for (it = listOne.begin();
					 it != listOne.end();
					 it++)
				{
					if (vTwo[i] == (*it))
					{
						listOne.remove((*it));

						if (full)
						{
							std::string fileOne = Path::Combine(directoryOne, vTwo[i]);
							std::string fileTwo = Path::Combine(directoryTwo, *it);

							validate = File::compareFiles(fileOne, fileTwo);
						}
						else
						{
							validate = true;
						}

						break;
					}
				}
			}

			validate = listOne.size() == 0;
		}
		else
		{
			std::stringstream ss;
			ss << "Fail compare directories " << directoryOne << "(" << vOne.size() << ") and " << directoryTwo << "(" << vTwo.size() << ").";
			logger->Debug(ss.str());
		}
	}

	logger->Debug("Compare Directories " + std::string (validate ? "Success":"Fail"));

	return validate;
}

bool Directory::compareDirectoryStructure(std::string & directoryOne, std::string & directoryTwo)
{
	bool validate = false;

	logger->Debug("Compare Directory Structure " + directoryOne + " and " + directoryTwo);

	if (DirectoryExists(directoryOne) && DirectoryExists(directoryTwo))
	{
		std::vector<std::string> vOne;
		std::vector<std::string> vTwo;
		GetSubDirectories(directoryOne, vOne, true, true);
		GetSubDirectories(directoryTwo, vTwo, true, true);

		validate = (vOne.size() == vTwo.size());

		if (validate)
		{
			std::list<std::string> listOne;
			std::list<std::string>::iterator it;

			listOne.insert (listOne.end(), vOne.begin(), vOne.end());

			for (unsigned int i = 0;i < vTwo.size() && validate;i++)
			{
				validate = false;

				for (it = listOne.begin();
					 it != listOne.end();
					 it++)
				{
					if (vTwo[i] == (*it))
					{
						listOne.remove((*it));
						validate = true;
						break;
					}
				}
			}

			validate = listOne.size() == 0;
		}
		else
		{
			std::stringstream ss;
			ss << "Fail compare directory structure " << directoryOne << "(" << vOne.size() << ") and " << directoryTwo << "(" << vTwo.size() << ").";
			logger->Debug(ss.str());
		}
	}

	logger->Debug("Compare Directory Structure " + std::string (validate ? "Success":"Fail"));

	return validate;
}
