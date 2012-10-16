/**
 * @file TestPrinting.hxx
 * @brief Header class test printing
 * @date 24/10/2011
 * @author Yadickson Soto
 */

#ifndef TESTPRINTING_HXX_
#define TESTPRINTING_HXX_

#include <glibmm.h>
#include <Printing/BasePrintDocument.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class TestPrinting
			 * @brief Class test printing
			 * @date 24/10/2011
			 * @author Yadickson Soto
			 * @see BasePrintDocument
			 */
			class TestPrinting : public Smartmatic::SAES::Printing::BasePrintDocument
			{
			public:
				/**
				 * @brief Class constructor
				 * @param data string data to print
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				TestPrinting(std::string data);
				/**
				 * @brief Class constructor
				 * @param pixBuff image data to print
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				TestPrinting(Glib::RefPtr<Gdk::Pixbuf> pixBuff);
				/**
				 * @brief Class destroy
				 * @date 24/10/2011
				 * @author Yadickson Soto
				 */
				virtual ~TestPrinting();

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
				Glib::RefPtr<Gdk::Pixbuf> pixBuff; ///< image to print
			};
		}
	}
}

#endif /* TESTPRINTING_HXX_ */
