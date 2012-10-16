/**
 * @file PMWindow.hxx
 * @brief Header class pm window
 * @date 19/10/2011
 * @author Yadickson Soto
 */

#ifndef PMWINDOW_HXX_
#define PMWINDOW_HXX_

#include "RunMachineWindow.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @class PMWindow
				 * @brief class president machine window
				 * @date 02/11/2011
				 * @author Yadickson Soto
				 */
				class PMWindow : public RunMachineWindow
				{
				public:
					/**
					 * @brief class constructor
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					PMWindow();
					/**
					 * @brief class destroy
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual ~PMWindow();

				protected:

					/**
					 * @brief method initialize step widget
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void initialize();
				};
			}
		}
	}
}

#endif /* PMWINDOW_HXX_ */
