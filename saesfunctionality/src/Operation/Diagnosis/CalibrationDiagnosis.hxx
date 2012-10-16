/*
 * CalibrationDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef CALIBRATIONDIAGNOSIS_HXX_
#define CALIBRATIONDIAGNOSIS_HXX_

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
				class CalibrationDiagnosis : public IDiagnosis
				{
				public:
					CalibrationDiagnosis(int numberPoints);
					virtual ~CalibrationDiagnosis();

					virtual void test();

				private:
					int numberPoints;
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				protected:
					virtual void updateMessage();
				};
			}
		}
	}
}

#endif /* CALIBRATIONDIAGNOSIS_HXX_ */
