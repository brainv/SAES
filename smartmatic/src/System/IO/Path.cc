/**
 * @file Path.cc
 * @brief Body class Path
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

#include "System/IO/Path.h"
#include "System/IO/File.h"
#include "System/IO/Directory.h"
#include <iostream>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd ///< macro get current dir for windows
#else
#include <unistd.h>
#define GetCurrentDir getcwd ///< macro get current dir for linux
#endif


using namespace Smartmatic::System::IO;

std::string Path::Combine(const std::string & path1, const std::string & path2)
{
	std::string strCombine1 = path1;
	std::string strCombine2 = path2;

	if(strCombine1[strCombine1.size()-1]!='/')
		strCombine1.append("/");

	if(strCombine2[0]=='/')
		strCombine2.erase(0,1);

	strCombine1.append(strCombine2);

	
	return strCombine1;
}

std::string Path::GetFileName(const std::string& path)
{
	size_t found;
	found=path.find_last_of("/\\");
	
	if (found != std::string::npos)
	{
	    return path.substr(found+1);
	}

	return path;
}

std::string Path::GetFileNameWithOutExtension(const std::string path)
{
	size_t found;
	std::string file = GetFileName(path);
	found = file.find_last_of(".");

	if (found != std::string::npos)
	{
	    return file.substr(0,found);
	}

	return file;
}

std::string Path::GetFullFileNameWithOutExtension(const std::string path)
{
	std::string strCombine1 = GetDirectory(path);
	std::string strCombine2 = GetFileNameWithOutExtension(path);
	return Combine(strCombine1, strCombine2);
}

std::string Path::GetFileExtension(const std::string path)
{
	size_t found;
	std::string file = GetFileName(path);
	found = file.find_last_of(".");

	if (found != std::string::npos)
    {
        return file.substr(found);
    }

	return "";
}

std:: string Path::GetDirectory(const std::string& path)
{
	size_t found;
	found=path.find_last_of("/\\");
	return path.substr(0,found+1);
}

std::string Path::GetCurrentDirectory()
{
	char cCurrentPath[FILENAME_MAX];
	char* success = GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	std::string currentDirectory = std::string(cCurrentPath);	
	if(success != NULL)
	{
	}
	currentDirectory.append("/");
	return currentDirectory;
}

std::string Path::combineFileName( std::string file, std::string combine )
{
	return Path::GetFullFileNameWithOutExtension(file) + combine + Path::GetFileExtension(file);
}

void Path::combineFileName( std::string file, std::list < std::string > & combine, std::list < std::string > & result )
{
	std::list < std::string >::iterator it;

	for (it = combine.begin();
		 it != combine.end();
		 it++)
	{
		combine.push_back(Path::combineFileName (file, (*it)));
	}
}
