/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * default-miscellaneous is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * default-miscellaneous is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <Configuration/configuration-persistence-manager.h>
#include <Configuration/smartmatic-conf-manager.h>
#include <Configuration/s-m-t-t-g-u-i-conf-manager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Configuration/s-a-e-s-hardware-conf-manager.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>

using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;

#define LOG_CONF_FILENAME "log4-configuration.xml"

int
main (int argc, char *argv[])
{

	  if(Directory::FileExists(LOG_CONF_FILENAME))
		{
			SMTTLogManager::Configure(LOG_CONF_FILENAME);
		}

  Smartmatic::Configuration::SmartmaticConfigurationManager::Current()->LoadDefault();
  Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->LoadDefault();
  Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->LoadDefault();
  Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->LoadDefault();

  Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->LoadDefault();
  Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->LoadDefault();

  Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->LoadDefault();

  Smartmatic::Configuration::ConfigurationPersistenceManager::Current().SaveFile();

  std::cout << "Archivo creado correctamente." << std::endl;
  return 0;
}
