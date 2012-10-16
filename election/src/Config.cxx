/*
 * ConfigLogger.cxx
 *
 *  Created on: 23/08/2011
 *      Author: soto
 */

#include "Config.hxx"
#include <xsec/utils/XSECPlatformUtils.hpp>
#include <Runtime/Environment/MemoryPathController.h>
#include <log4cxx/DynamicPathRollingFileAppender.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Configuration/smartmatic-language-controller.h>
#include <Configuration/smartmaticgui-language-controller.h>
#include <Configuration/saes-language-controller.h>
#include <Configuration/saes-common-language-controller.h>
#include <Configuration/saes-hardware-language-controller.h>
#include <Configuration/saes-functionality-language-controller.h>
#include <Configuration/saes-gui-language-controller.h>
#include <log4cxx/CryptoLayout.hxx>
#include <Log/LogCryptoPool.hxx>
#include <pcscd/PCSCDManager.hxx>
#include <Devices/barcode-device.h>
#include <Log/SMTTLogManager.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <Log/LogBasePath.hxx>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <glib.h>
#include <Operation/MachineOperationManager.hxx>

#ifndef XSEC_NO_XALAN
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
XALAN_USING_XALAN( XalanTransformer)
#endif

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

using namespace Smartmatic::SAES::Election;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::PCSCD;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;

void Config::start()
{
	// No eliminar, esto activa el uso de las senales del sistema operativo
	MemoryPathController::getInstance()->updatePaths();
	BarcodeDevice::Current()->enabledEvent();
	// No eliminar

	LogBasePath * basePathDom = MachineOperationManager::getInstance()->getLogBasePathDom();
	LogBasePath * basePathFlash = MachineOperationManager::getInstance()->getLogBasePathFlash();

	log4cxx::CryptoLayout::setCryptoMap(LogCryptoPool::getInstance()->getCryptoMap());
	log4cxx::DynamicPathRollingFileAppender::putBasePathInterface(basePathDom);
	log4cxx::DynamicPathRollingFileAppender::putBasePathInterface(basePathFlash);

	SMTTLogManager::Reconfigure();

	//Init rand funtion
	Glib::TimeVal time;
	time.assign_current_time();
	int seed = time.as_double();
	srand(seed);

	try
	{
		xercesc::XMLPlatformUtils::Initialize();
		#ifndef XSEC_NO_XALAN
			XalanTransformer::initialize();
		#endif
		XSECPlatformUtils::Initialise();
	}
	catch (const xercesc::XMLException &ex)
	{
	}

	PCSCDManager::kill();
	PCSCDManager::start();

	SmartmaticLanguageController smartLang;
	smartLang.InitializeLanguage();
	SmartmaticGUILanguageController smartguiLang;
	smartguiLang.InitializeLanguage();
	SAESLanguageController saesLang;
	saesLang.InitializeLanguage();
	SAESGUILanguageController saesguiLang;
	saesguiLang.InitializeLanguage();
	SAESCommonLanguageController saescommonLang;
	saescommonLang.InitializeLanguage();
	SAESFunctionalityLanguageController saesfuncLang;
	saesfuncLang.InitializeLanguage();
	SAESHardwareLanguageController saeshwLang;
	saeshwLang.InitializeLanguage();
}
