/*
 * BarCodeDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef BARCODEDIAGNOSIS_HXX_
#define BARCODEDIAGNOSIS_HXX_

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
				class BarCodeDiagnosis : public IDiagnosis
				{
				public:
					BarCodeDiagnosis(std::string command);
					virtual ~BarCodeDiagnosis();
					virtual void test();

				private:
					std::string command;
					bool runcommand;
					bool flagEnd;
					sigc::connection connSend; ///< connection send commands
					sigc::connection connDisconnect; ///< connection disconnect BCR
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					void end(bool status);
					void disconnect();

				protected:
					virtual void updateMessage();
				};
			}
		}
	}
}

#endif /* BARCODEDIAGNOSIS_HXX_ */
