/*
 * LogBasePath.cxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#include "LogBasePath.hxx"
#include <Runtime/Environment/MemoryPathController.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>

using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;

LogBasePath::LogBasePath ( BasePathType type )
: Smartmatic::Log::BasePathInterface( type )
{
	this->type = type;
}

std::string LogBasePath::getFileFullPath( std::string & file )
{
    std::string basePath = directories.getLogFolderFullPath( type );
	return Path::Combine(basePath, file);
}

bool LogBasePath::canWriter()
{
    std::string basePath = directories.getDevicePath(type);
	return Directory::DirectoryExists(basePath);
}
