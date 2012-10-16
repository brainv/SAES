/**
 * @file EIDEvent.cxx
 * @brief Body class eid event
 * @date 22/07/2011
 * @author Yadickson Soto
 */

#include "EIDEvent.hxx"
#include "EIDManager.hxx"
#include "beidlib/eidlib.h"
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

using namespace eIDMW;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;

EIDEventInterface * EIDEvent::eventManager = NULL;
EIDEvent::ReadersMap EIDEvent::readersMap;

ISMTTLog* EIDEvent::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.EID.EIDEvent",GETTEXT_PACKAGE);

void EIDEvent::init( EIDEventInterface * eventManager )
{
	EIDEvent::eventManager = eventManager;
}

void EIDEvent::callBack(long lRet, unsigned long ulState, void *pvRef)
{
	try
	{
		if (EIDEvent::eventManager != NULL)
		{
			char * readerName = (char *)(pvRef);
			ReaderRef * ref = readersMap[readerName];

			if (ref->reader->isCardPresent())
			{
				if (ref->reader->isCardChanged(ref->cardId))
				{
					EIDEvent::eventManager->cardInserted();
				}
			}
			else if (ref->cardId != 0)
			{
				EIDEvent::eventManager->cardExtracted();
			}
		}
	}
	catch(...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}
}

//*****************************************************************************
// Attach events on all readers
//*****************************************************************************
void EIDEvent::attach()
{
	try
	{
		EIDEvent::detach();

		unsigned long nrReaders  = ReaderSet.readerCount(true);

		for ( size_t readerIdx=0; readerIdx<nrReaders; readerIdx++)
		{
			EIDEvent::ReaderRef * ref = new EIDEvent::ReaderRef();

			BEID_ReaderContext * reader = &ReaderSet.getReaderByNum(readerIdx);
			std::string name = ReaderSet.getReaderName(readerIdx);

			char * readerName = new char[name.size() + 1];
			strcpy(readerName, name.c_str());

			ref->reader = reader;
			ref->eventHandle = reader->SetEventCallback(&EIDEvent::callBack, (void *) readerName );
			ref->cardId = 0;

			readersMap[readerName] = ref;
		}
	}
	catch (...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}
}

//*****************************************************************************
// Detach events on all readers
//*****************************************************************************
void EIDEvent::detach()
{
	try
	{
		ReadersMap::iterator it;

		for(it = readersMap.begin();
			it != readersMap.end();
			it++)
		{
			char * readerName = it->first;
			ReaderRef * ref = it->second;
			BEID_ReaderContext * reader = ref->reader;
			reader->StopEventCallback(ref->eventHandle);

			delete ref;
			delete[] readerName;
		}

		readersMap.clear();
		ReaderSet.readerCount(true);
		EIDEvent::eventManager = NULL;
	}
	catch (...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}
}
