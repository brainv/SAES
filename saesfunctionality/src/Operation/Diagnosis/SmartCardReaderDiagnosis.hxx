/*
 * SmartCardReaderDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef SMARTCARDREADERDIAGNOSIS_HXX_
#define SMARTCARDREADERDIAGNOSIS_HXX_

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
				class SmartCardReaderDiagnosis : public IDiagnosis
				{
				public:
					SmartCardReaderDiagnosis();
					virtual ~SmartCardReaderDiagnosis();
					virtual void test();

				protected:
					virtual void updateMessage();

				private:
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* SMARTCARDREADERDIAGNOSIS_HXX_ */
