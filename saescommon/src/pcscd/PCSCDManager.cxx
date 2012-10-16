/*
 * PCSCDManager.cxx
 *
 *  Created on: 16/08/2011
 *      Author: soto
 */


#include "PCSCDManager.hxx"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/Runtime/ProcessLauncher.h>

using namespace Smartmatic::SAES::PCSCD;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Runtime;

void PCSCDManager::start(bool force)
{
	bool startPCSCD = SAESCommonConfigurationManager::Current()->getPCSCDConfiguration().getStartService();

	if (startPCSCD || force)
	{
		(void)ProcessLauncher::RunProcessThroughSystem("/etc/init.d/pcscd start");
	}
}

void PCSCDManager::kill()
{
	bool stopPCSCD = SAESCommonConfigurationManager::Current()->getPCSCDConfiguration().getStopService();

	if (stopPCSCD)
	{
		(void)ProcessLauncher::RunProcessThroughSystem("pkill -9 pcscd");
	}
}

void PCSCDManager::stop(bool force)
{
	bool stopPCSCD = SAESCommonConfigurationManager::Current()->getPCSCDConfiguration().getStopService();

	if (stopPCSCD || force)
	{
		(void)ProcessLauncher::RunProcessThroughSystem("/etc/init.d/pcscd stop");
	}
}
