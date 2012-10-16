/*
 * FlashDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef FLASHDIAGNOSIS_HXX_
#define FLASHDIAGNOSIS_HXX_

#include "IDiagnosis.hxx"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Operation
		{
			namespace Diagnosis
			{
				class FlashDiagnosis : public IDiagnosis
				{
				public:
					FlashDiagnosis(bool checkBoth = true);
					virtual ~FlashDiagnosis();

					virtual void test();

				private:
					bool checkBoth;
					std::string errorMessage;
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					bool getDeviceStatus(std::string device);

				protected:
					virtual void updateMessage();
				};
			}
		}
	}
}

#endif /* FLASHDIAGNOSIS_HXX_ */
