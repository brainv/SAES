/*
 * AlarmBoxDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef ALARMBOXDIAGNOSIS_HXX_
#define ALARMBOXDIAGNOSIS_HXX_

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
				class AlarmBoxDiagnosis : public IDiagnosis
				{
				public:
					AlarmBoxDiagnosis();
					virtual ~AlarmBoxDiagnosis();

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

#endif /* ALARMBOXDIAGNOSIS_HXX_ */
