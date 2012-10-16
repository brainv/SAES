/**
 * @file HelpPrinting.hxx
 * @brief Header class barcode config printing
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#ifndef HELPPRINTING_HXX_
#define HELPPRINTING_HXX_

#include <gtkmm.h>
#include <Printing/LPSpooler.h>

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
			 * @class HelpPrinting
			 * @brief Class barcode config printing
			 * @date 29/03/2012
			 * @author Yadickson Soto
			 * @see BasePrintDocument
			 */
			class HelpPrinting
			{
			public:
				/**
				 * @brief Class constructor
				 * @param file fine name
				 * @date 29/03/2012
				 * @author Yadickson Soto
				 */
				HelpPrinting(std::string file);
				/**
				 * @brief Class destroy
				 * @date 29/03/2012
				 * @author Yadickson Soto
				 */
				virtual ~HelpPrinting();
				/**
				 * @brief Method print doc
				 * @date 29/03/2012
				 * @author Yadickson Soto
				 */
				void Print();

				Glib::Dispatcher signalPrintFinished; ///< The signal print finished
				Glib::Dispatcher signalErrorDetected; ///< The signal error detected

			private:

				std::string file; ///< file name
				Smartmatic::SAES::Printing::LPSpooler spooler;	///< The spooler
				static Smartmatic::Log::ISMTTLog * logger; ///< logger
			};
		}
	}
}

#endif /* BARCODECONFIGPRINTING_HXX_ */
