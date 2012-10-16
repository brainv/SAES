/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "s-a-e-s-hardware-conf-manager.h"
#include <glibmm.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>

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
using namespace Smartmatic::Configuration;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

#define LOGGER_PROJECT "Smartmatic.Configuration.SAESHardwareConfigurationManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* SAESHardwareConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* SAESHardwareConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

SAESHardwareConfigurationManager::SAESHardwareConfigurationManager()
{
	configuration = NULL;
	Initialize();
}

SAESHardwareConfigurationManager::~SAESHardwareConfigurationManager()
{
	if(configuration != NULL)
	{
		delete(configuration);
		configuration = NULL;
	}
}

auto_ptr<SaesHardwareConfiguration>* SAESHardwareConfigurationManager::getConfiguration()
{
	return configuration;
}

void SAESHardwareConfigurationManager::Initialize()
{
	try
	{
        string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SAESHardware"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new auto_ptr<SaesHardwareConfiguration>(parseSaesHardwareConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
		}
		else
		{
			LoadDefault();
			Initialize();
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESHW Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESHW Error", "Error");
		exit (0);
	}
}

std::vector<std::string> SAESHardwareConfigurationManager::getListOfBarcodePorts()
{
	std::vector<std::string> list;
	::xsd::cxx::tree::sequence< ::Smartmatic::ConfigurationTypes::String > pathsSequence = (*configuration)->getBarcodeDeviceConfiguration().getPortToLook ();
	for(unsigned int i = 0;i < pathsSequence.size();i++)
	{
		list.push_back(pathsSequence[i]) ;
	}
	return list;
}

CardReaderType SAESHardwareConfigurationManager::getSmartCardReaderType()
{
	return (*configuration)->getSmartcardConfiguration().getSmartCardReaderType();
}

BarcodeCommands::CommandSequence SAESHardwareConfigurationManager::getBarcodeConfigurationCommands(const std::string& commandBlock, const std::string& barcodeModel)
{
	BarcodeCommands::CommandSequence commandsSeq;

	string primarySearch = commandBlock + "-" + barcodeModel;

	bool commandsFound = false;

	for(BarcodeDeviceConfiguration::ConfigurationCommandsIterator iter =
			(*configuration)->getBarcodeDeviceConfiguration().getConfigurationCommands().begin();
			iter != (*configuration)->getBarcodeDeviceConfiguration().getConfigurationCommands().end();
			iter++)
	{
		if(iter->getCommandBlockName() == primarySearch)
		{
			logger->Debug("Commands sent: " + primarySearch);
			commandsSeq = iter->getCommand();
			commandsFound = true;
			break;
		}
	}

	if(!commandsFound)
	{
		for(BarcodeDeviceConfiguration::ConfigurationCommandsIterator iter =
				(*configuration)->getBarcodeDeviceConfiguration().getConfigurationCommands().begin();
				iter != (*configuration)->getBarcodeDeviceConfiguration().getConfigurationCommands().end();
				iter++)
		{
			if(iter->getCommandBlockName() == commandBlock)
			{
				logger->Debug("Commands sent: " + commandBlock);
				commandsSeq = iter->getCommand();
				break;
			}
		}
	}

	return commandsSeq;
}

void SAESHardwareConfigurationManager::LoadDefault()
{
	SaesHardwareConfiguration *configSAESHardware = new SaesHardwareConfiguration();

	try
	{
        stringstream ss;
        Smartmatic::ConfigurationTypes::NamespaceInfomap map;

#ifdef NAMESPACE_SAES_HARDWARE_CONFIGURATION
        map[""].name = NAMESPACE_SAES_HARDWARE_CONFIGURATION;
#endif
        map[""].schema = "";

        SmartcardConfiguration smartCardConf;
        smartCardConf.setSmartCardReaderType("AU9520");
        smartCardConf.setExtended(false);
        configSAESHardware->setSmartcardConfiguration(smartCardConf);

		BarcodeDeviceConfiguration barcodeConf;
		BarcodeDeviceConfiguration::PortToLookSequence portsSeq;
		portsSeq.push_back("ttyUSB0");
		portsSeq.push_back("ACM0");
		barcodeConf.setPortToLook(portsSeq);
		barcodeConf.setSerialPollingTime(1000);

		/**
		 * baseconfiguration-mb2028
		 */

        BarcodeCommands::CommandSequence barcodeCommandsSeq;
        BarcodeCommand command;

        command.setRetries(2);
        command.setDelayResponse(3000);
        command.setMandatorySent(true);

			//1. Desabilitar todos los códigos de barra: NLS0001010
			command.setCommand("NLS0001010");
			barcodeCommandsSeq.push_back(command);
			//2. Apagar el envio de información de settings: NLS0002000
			command.setCommand("NLS0002000");
			barcodeCommandsSeq.push_back(command);
			//3. Apagar posibilidad de configuración con códigos: NLS0006000
			command.setCommand("NLS0006000");
			barcodeCommandsSeq.push_back(command);
			//4. Apagar el envio de información cuando se enciende la lectora: NLS0007000
			command.setCommand("NLS0007000");
			barcodeCommandsSeq.push_back(command);
			//5. Asignar modo de Light a LedOnWhenScan: NLS0200030
			command.setCommand("NLS0200030");
			barcodeCommandsSeq.push_back(command);
			//6. Asignar modo de Aiming a FlashWhenScan: NLS0201000
			command.setCommand("NLS0201000");
			barcodeCommandsSeq.push_back(command);
			//7. Desabilitar el Beep de lectura: NLS0203000 = off NLS0203010 = on
			command.setCommand("NLS0203010");
			barcodeCommandsSeq.push_back(command);
			//8. Apagar el uso de cualquier prefijo o sufijo en la comunicación: NLS0311000
			command.setCommand("NLS0311000");
			barcodeCommandsSeq.push_back(command);
			//9. Apagar el empaquetado de datos: NLS0314000
			command.setCommand("NLS0314000");
			barcodeCommandsSeq.push_back(command);
			//10. Apagar intercepción de mensajes: NLS0315000
			command.setCommand("NLS0315000");
			barcodeCommandsSeq.push_back(command);
			//11. Apagar terminador NLS0309000
			command.setCommand("NLS0309000");
			barcodeCommandsSeq.push_back(command);
			//12. Asingnar el modo de lectura a Auto Scan: NLS0302010
			command.setCommand("NLS0302010");
			barcodeCommandsSeq.push_back(command);
			//13. Asignar la sensibilidad como la más alta: NLS0312030
			command.setCommand("NLS0312030");
			barcodeCommandsSeq.push_back(command);
			//14. Asignar el delay entre lecturas a 0: NLS0313000=0
			command.setCommand("NLS0313000=0");
			barcodeCommandsSeq.push_back(command);
			//15. Asignar el delay entre lecturas del mismo código de barras a 10 segundos (o mas): NLS0313010=10000
			command.setCommand("NLS0313010=10000");
			barcodeCommandsSeq.push_back(command);
			//16. Asignar el tipo de delay a completely: NLS0313030
			command.setCommand("NLS0313030");
			barcodeCommandsSeq.push_back(command);
			//17. Apagar el motor de vibración: NLS1216000
			command.setCommand("NLS1216000");
			barcodeCommandsSeq.push_back(command);
			//18. Habilitar el código de barras QR: NLS0502020
			command.setCommand("NLS0502020");
			barcodeCommandsSeq.push_back(command);
			//19. Asignar el tamaño del mensaje QR al máximo : NLS0502040
			command.setCommand("NLS0502040");
			barcodeCommandsSeq.push_back(command);
			//20. Indicar que la lectora sólo debe aceptar códigos QR simples: NLS0502070
			command.setCommand("NLS0502070");
			barcodeCommandsSeq.push_back(command);

        BarcodeCommands barcodeCommands;
        barcodeCommands.setCommandBlockName("baseconfiguration");
        barcodeCommands.setCommand(barcodeCommandsSeq);

		/**
		 * baseconfiguration-hr200
		 */
        BarcodeCommands barcodeCommands1;
        barcodeCommands1.setCommandBlockName("baseconfiguration-hr200");

        barcodeCommandsSeq.clear();
			command.setCommand("NLS0001010");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0002000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0006000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0007000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0200030");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0201000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0203010");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0311000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0314000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0315000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0309000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0302000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0312030");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0313000=0");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0313010=10000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0313030");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS1216000");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0502020");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0502040");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0502070");
			barcodeCommandsSeq.push_back(command);
		barcodeCommands1.setCommand(barcodeCommandsSeq);

		/**
		 * LightsON
		 */
		BarcodeCommands barcodeCommands2;
		barcodeCommands2.setCommandBlockName("LightsON");

		barcodeCommandsSeq.clear();
			command.setCommand("NLS0200030");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("NLS0201000");
			barcodeCommandsSeq.push_back(command);
		barcodeCommands2.setCommand(barcodeCommandsSeq);

		/**
		 * LightsOFF
		 */
		BarcodeCommands barcodeCommands3;
		barcodeCommands3.setCommandBlockName("LightsOFF");

		barcodeCommandsSeq.clear();
			command.setCommand("nls0200020");
			barcodeCommandsSeq.push_back(command);
			command.setCommand("nls0201020");
			barcodeCommandsSeq.push_back(command);
		barcodeCommands3.setCommand(barcodeCommandsSeq);

        BarcodeDeviceConfiguration::ConfigurationCommandsSequence confCommandsSeq;
        confCommandsSeq.push_back(barcodeCommands);
        confCommandsSeq.push_back(barcodeCommands1);
        confCommandsSeq.push_back(barcodeCommands2);
        confCommandsSeq.push_back(barcodeCommands3);

        barcodeConf.setConfigurationCommands(confCommandsSeq);
		configSAESHardware->setBarcodeDeviceConfiguration (barcodeConf);
		
		serializeSaesHardwareConfiguration(ss,*configSAESHardware, map, "UTF-8");
		//ss << saes_hw_defaultmisc;
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SAESHardware",ss.str());
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESHW Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESHW Error", "Error");
		exit (0);
	}

	delete(configSAESHardware);
}

BarcodeDeviceConfiguration & SAESHardwareConfigurationManager::getBarcodeDeviceConfiguration()
{
	return (*configuration)->getBarcodeDeviceConfiguration();
}

SAESHardwareConfigurationManager * SAESHardwareConfigurationManager::singleton_instance = NULL;

SAESHardwareConfigurationManager *SAESHardwareConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SAESHardwareConfigurationManager ();

	return singleton_instance;
}
