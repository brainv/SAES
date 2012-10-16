/*
 * EIDPing.hxx
 *
 *  Created on: 21/07/2011
 *      Author: soto
 */

#ifndef EIDPIN_HXX_
#define EIDPIN_HXX_

#include "beidlib/eidlib.h"

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
			class EIDPin
			{
			protected:
				EIDPin();

			public:
				~EIDPin();

				static bool verify( eIDMW::BEID_EIDCard &card, unsigned long & count );

			private:
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* EIDPIN_HXX_ */
