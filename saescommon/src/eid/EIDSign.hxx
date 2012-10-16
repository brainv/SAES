/*
 * EIDSign.hxx
 *
 *  Created on: 20/07/2011
 *      Author: soto
 */

#ifndef EIDSIGN_HXX_
#define EIDSIGN_HXX_

#include <System/SafeBuffer.h>

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
			class EIDSign
			{
			protected:
				EIDSign();

			public:
				~EIDSign();

				static bool singPCKS11( Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & dataOut );

			private:
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* EIDSIGN_HXX_ */
