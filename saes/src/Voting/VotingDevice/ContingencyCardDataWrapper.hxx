/*
 * ContingencyCardDataWrapper.hxx
 *
 *  Created on: 16/10/2011
 *      Author: soto
 */

#ifndef CONTINGENCYCARDDATAWRAPPER_HXX_
#define CONTINGENCYCARDDATAWRAPPER_HXX_

#include <Voting/VotingDevice/contingency-card-data-schema.hxx>
#include <System/SafeBuffer.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace Voting
		{
			namespace VotingDevice
			{
				class ContingencyCardDataWrapper
				{
				protected:
					ContingencyCardDataWrapper();

				public:
					virtual ~ContingencyCardDataWrapper();
					static bool cardDataToString(ContingencyCardData & cardData, std::string & dataOut);
					static bool stringToCardData(std::string & data, ContingencyCardData & cardDataOut);
					static bool cardDataToBuffer(ContingencyCardData & cardData, Smartmatic::System::SafeBuffer & bufferOut);
					static bool bufferToCardData(Smartmatic::System::SafeBuffer & buffer, ContingencyCardData & cardDataOut);

				private:

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* CONTINGENCYCARDDATAWRAPPER_HXX_ */
