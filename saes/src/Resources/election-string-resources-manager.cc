/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "election-string-resources-manager.h"

using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace std;

ElectionStringResourcesManager * ElectionStringResourcesManager::singleton_instance = NULL;

ElectionStringResourcesManager::ElectionStringResourcesManager()
{

}

ElectionStringResourcesManager::~ElectionStringResourcesManager()
{

}

ElectionStringResourcesManager *ElectionStringResourcesManager::Current ()
{ 
	if ( ! singleton_instance )
	{	
		singleton_instance = new ElectionStringResourcesManager ();
		singleton_instance->Initialize();
	}
	return singleton_instance;
}

void  ElectionStringResourcesManager::init(Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDir,
		Smartmatic::SAES::Common::Configuration::BasePathType type)
{
    fileName = saesDir->getElectionResourcesFileName();
    folderPath = saesDir->getElectoralResourceFullFolderPath(type);
    Initialize();
}

string &  ElectionStringResourcesManager::getFileName()
{
	return fileName;
}

string &  ElectionStringResourcesManager::getFullFolderPath()
{
	return folderPath;
}
