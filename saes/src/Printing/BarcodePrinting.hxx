/*
 * BarcodePrinting.hxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#ifndef BARCODEPRINTING_HXX_
#define BARCODEPRINTING_HXX_

#include <glibmm.h>
#include <Printing/BasePrintDocument.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			class BarcodePrinting : public Smartmatic::SAES::Printing::BasePrintDocument
			{
			public:
				BarcodePrinting(std::string data);
				BarcodePrinting(Glib::RefPtr<Gdk::Pixbuf> pixBuff);
				virtual ~BarcodePrinting();

			protected:
				void PrintDoc();
				void BeginPrint();
				void EndPrint();

			private:
				Glib::RefPtr<Gdk::Pixbuf> pixBuff;
			};
		}
	}
}

#endif /* BARCODEPRINTING_HXX_ */
