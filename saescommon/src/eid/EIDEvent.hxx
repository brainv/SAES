/*
 * EIDEvent.hxx
 *
 *  Created on: 22/07/2011
 *      Author: soto
 */

#ifndef EIDEVENT_HXX_
#define EIDEVENT_HXX_

#include "EIDEventInterface.hxx"
#include "beidlib/eidlib.h"
#include <map>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace EID
		{
			class EIDEvent
			{
			protected:
				EIDEvent();

			public:
				~EIDEvent();

				static void init( EIDEventInterface * eventManager );
				static void attach();
				static void detach();

			private:

				struct ReaderRef
				{
					eIDMW::BEID_ReaderContext *reader;
					unsigned long eventHandle;
				    unsigned long cardId;
				};

				typedef std::map < char * , ReaderRef * > ReadersMap;

				static EIDEventInterface * eventManager;
				static ReadersMap readersMap;
				static void callBack(long lRet, unsigned long ulState, void *pvRef);
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* EIDEVENT_HXX_ */
