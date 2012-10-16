/**
 * @file IDCardWidgetVMInstall.hxx
 * @brief Header class id card vm install
 * @date 04/05/2012
 * @author Yadickson Soto
 */

#ifndef _ID_CARD_WIDGET_VM_INSTALL_H_
#define _ID_CARD_WIDGET_VM_INSTALL_H_

#include "id-card-widget.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	IDCardWidgetVMInstall
				 * @brief	Identifier card widget vm install.
				 * @date 04/05/2012
				 * @author Yadickson Soto
				 */
				class IDCardWidgetVMInstall: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
				{
				public:

					/**
					 * @brief	Class constructor.
					 * @date 04/05/2012
					 * @author Yadickson Soto
					 */
					IDCardWidgetVMInstall();
					/**
					 * @brief	Class destroy.
					 * @date 04/05/2012
					 * @author Yadickson Soto
					 */
					~IDCardWidgetVMInstall();

				protected:

				private:
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

				};
			}
		}
	}
}



#endif // _ID_CARD_WIDGET_VM_INSTALL_H_
