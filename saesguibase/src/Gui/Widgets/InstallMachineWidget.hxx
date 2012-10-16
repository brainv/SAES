/**
 * @file InstallMachineWidget.hxx
 * @brief Header class install machine widget
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#ifndef INSTALLMACHINEWIDGET_HXX_
#define INSTALLMACHINEWIDGET_HXX_

#include <Widgets/StepWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class InstallMachineWidget
				 * @brief Class install machine widget
				 * @date 02/11/2011
				 * @author Yadickson Soto
				 */
				class InstallMachineWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					InstallMachineWidget();
					/**
					 * @brief Class destroy
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual ~InstallMachineWidget();
					/**
					 * @brief virtual method stop widget
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual void stop() = 0;
				};
			}
		}
	}
}

#endif /* INSTALLMACHINEWIDGET_HXX_ */
