/**
 * @file AlarmBoxMonitor.cxx
 * @brief Body class alarm box monitor
 * @date 16/05/2012
 * @author Yadickson Soto
 */

#include "AlarmBoxMonitor.hxx"
#include <Devices/alarm-device.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::SAES::Operation::Alarm;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::HW::Devices;

ISMTTLog* AlarmBoxMonitor::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.AlarmBoxMonitor",GETTEXT_PACKAGE);
AlarmBoxMonitor * AlarmBoxMonitor::instance = NULL;

AlarmBoxMonitor::AlarmBoxMonitor()
{
	this->flagRun = false;
	this->flagThreadRun = false;
	this->flagConnect = false;
	this->monitoringTime = 0;
	this->searchTime = 0;
}

AlarmBoxMonitor::~AlarmBoxMonitor()
{

}

void AlarmBoxMonitor::check()
{
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &AlarmBoxMonitor::checkThread), false);
}

void AlarmBoxMonitor::checkThread()
{
	flagConnect = AlarmDevice::Current()->sendPing();
}

void AlarmBoxMonitor::start(unsigned int monitoringTime, unsigned int searchTime)
{
	this->monitoringTime = monitoringTime;
	this->searchTime = searchTime;

	if (!flagRun && !flagThreadRun)
	{
		logger->Debug("Start alarm box monitor.");
		flagRun = true;
		if(!Glib::thread_supported()) Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &AlarmBoxMonitor::run), false);
	}
}

void AlarmBoxMonitor::stop()
{
	logger->Debug("Stop alarm box monitor.");
	flagThreadRun = false;
}

void AlarmBoxMonitor::run()
{
	flagThreadRun = true;
	bool emitConnect = false;
	bool emitDisconnect = false;
	static bool first = true;

	try
	{
		while(flagThreadRun)
		{
			flagConnect = AlarmDevice::Current()->sendPing();

			if ((!emitConnect && flagConnect) && emitDisconnect)
			{
				logger->Debug("Alarm Box Connected");
				emitConnect = true;
				emitDisconnect = false;
				AlarmDevice::Current()->ShutDownAlarm();

				if (!first)
				{
					signalConnect();
				}

				first = false;
			}
			if (((emitConnect && !emitDisconnect) || first) && !flagConnect)
			{
				logger->Debug("Alarm Box Disconnected");
				emitDisconnect = true;
				emitConnect = false;
				first = false;
				signalDisconnect();
			}

			if (flagConnect)
			{
				int count = 0;
				while (flagThreadRun && count++ < 1000)
				{
					usleep(monitoringTime);
				}
			}
			else
			{
				int count = 0;
				while (flagThreadRun && count++ < 1000)
				{
					usleep(searchTime);
				}
			}
		}
	}
	catch(...)
	{
		logger->Debug("ERROR - Alarm Box Monitor.");
	}

	flagRun = false;
	flagThreadRun = false;
	logger->Debug("Exit thread alarm box monitor");
}

bool AlarmBoxMonitor::isRunning()
{
	return flagRun;
}

bool AlarmBoxMonitor::isConnect()
{
	return flagConnect;
}

AlarmBoxMonitor * AlarmBoxMonitor::getInstance()
{
	if (!instance)
	{
		instance = new AlarmBoxMonitor();
	}

	return instance;
}
