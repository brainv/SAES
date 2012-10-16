/*
 * SaesInstallDirectories.cxx
 *
 *  Created on: 14/11/2011
 *      Author: soto
 */

#include "SaesInstallDirectories.hxx"

using namespace Smartmatic::SAES::Runtime::Environment;

SaesInstallDirectories::SaesInstallDirectories()
: SaesDirectories()
{
	this->programUnitName = "";
	this->workingPath = SaesDirectories::getWorkingDirectoryFolderName();
}

SaesInstallDirectories::~SaesInstallDirectories()
{

}

void SaesInstallDirectories::setWorkingPath( std::string workingPath )
{
	this->workingPath = workingPath;
}

void SaesInstallDirectories::setProgramUnitName( std::string programUnitName )
{
	this->programUnitName = programUnitName;
}
