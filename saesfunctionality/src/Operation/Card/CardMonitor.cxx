/*
 * CardMonitor.cxx
 *
 *  Created on: 06/03/2012
 *      Author: soto
 */

#include "CardMonitor.hxx"
#include "CardController.hxx"
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

using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::Log;

ISMTTLog* CardMonitor::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.CardMonitor",GETTEXT_PACKAGE);
CardMonitor * CardMonitor::instance = NULL;

CardMonitor::CardMonitor()
{
	this->flagRun = false;
	this->flagThreadRun = false;
	this->valueTime = 0;
	this->present = false;
}

CardMonitor::~CardMonitor()
{

}

void CardMonitor::start(unsigned int valueTime)
{
	if (!flagRun && !flagThreadRun)
	{
		this->valueTime = valueTime;
		CardController::getInstance()->initialize();

		logger->Debug("Start card monitor.");
		flagRun = true;
		if(!Glib::thread_supported()) Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &CardMonitor::run), false);
	}
}

void CardMonitor::stop()
{
	logger->Debug("Stop card monitor.");
	flagThreadRun = false;
	CardController::getInstance()->dispose();
}

void CardMonitor::run()
{
	flagThreadRun = true;
	bool emitInsert = false;
	bool emitRemove = false;

	try
	{
		while(flagThreadRun)
		{
      try 
      {
			  present = CardController::getInstance()->isCardPresent();
      } 
      catch(Smartmatic::System::Exception::CardReaderUnresponsiveException& e)
      {
        signalCardReaderUnresponsive();
      }

			if (!emitInsert && present)
			{
				logger->Debug("Card Insert");
				emitInsert = true;
				emitRemove = false;
				signalCardInsert();
			}
			if (emitInsert && !emitRemove && !present)
			{
				logger->Debug("Card Remove");
				emitRemove = true;
				emitInsert = false;
				signalCardRemove();
			}

			usleep(1000 * valueTime);
		}
	}
	catch(...)
	{
		logger->Debug("ERROR - Card monitor.");
	}

	flagRun = false;
	flagThreadRun = false;
}

bool CardMonitor::isRunning()
{
	return flagRun;
}

bool CardMonitor::isCardPresent()
{
	return present;
}

CardMonitor * CardMonitor::getInstance()
{
	if (!instance)
	{
		instance = new CardMonitor();
	}

	return instance;
}
