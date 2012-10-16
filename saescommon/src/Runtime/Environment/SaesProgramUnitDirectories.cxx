/**
 * @file SaesProgramUnitDirectory.cxx
 * @brief Body class saes directories for up structure
 * @date 14/11/2011
 * @author Yadickson Soto
 */

#include "SaesProgramUnitDirectories.hxx"
#include <System/IO/Path.h>

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;

SaesProgramUnitDirectories::SaesProgramUnitDirectories()
: SaesInstallDirectories()
{

}

SaesProgramUnitDirectories::~SaesProgramUnitDirectories()
{

}

std::string SaesProgramUnitDirectories::getWorkingDirectoryFolderName()
{
	return Path::Combine( getProgramUnitNamePath(), workingPath);
}

std::string SaesProgramUnitDirectories::getElectionFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine( getProgramUnitPath(type), ElectionFileName);
}

std::string SaesProgramUnitDirectories::getProgramUnitNamePath()
{
	return Path::Combine(SaesDirectories::getProjectName(), programUnitName);
}

std::string SaesProgramUnitDirectories::getProgramUnitPath( Smartmatic::SAES::Common::Configuration::BasePathType type )
{
	return Path::Combine( getDevicePath(type), getProgramUnitNamePath());
}
