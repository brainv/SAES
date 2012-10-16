/**
 * @file BarcodeConfigPrinting.hxx
 * @brief Header class barcode config printing
 * @date 07/03/2012
 * @author Yadickson Soto
 */

#ifndef BARCODECONFIGPRINTING_HXX_
#define BARCODECONFIGPRINTING_HXX_

#include <Printing/BasePrintDocument.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class BarcodeConfigPrinting
			 * @brief Class barcode config printing
			 * @date 07/03/2012
			 * @author Yadickson Soto
			 * @see BasePrintDocument
			 */
			class BarcodeConfigPrinting : public Smartmatic::SAES::Printing::BasePrintDocument
			{
			public:
				/**
				 * @brief Class constructor
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				BarcodeConfigPrinting();
				/**
				 * @brief Class destroy
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				virtual ~BarcodeConfigPrinting();

			protected:
				/**
				 * @brief Method print doc
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				void PrintDoc();
				/**
				 * @brief Method begin print
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				void BeginPrint();
				/**
				 * @brief Method end print
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				void EndPrint();

			private:

				static Smartmatic::Log::ISMTTLog * logger; ///< logger
			};
		}
	}
}

#endif /* BARCODECONFIGPRINTING_HXX_ */
