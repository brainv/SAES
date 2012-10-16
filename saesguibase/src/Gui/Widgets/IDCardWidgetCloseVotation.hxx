/**
 * @file IDCardWidgetCloseVotation.hxx
 * @brief Header class id card close voting
 * @date 04/05/2012
 * @author Yadickson Soto
 */

#ifndef _ID_CARD_WIDGET_CLOSE_VOTATION_H_
#define _ID_CARD_WIDGET_CLOSE_VOTATION_H_

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
				 * @class	IDCardWidgetCloseVotation
				 * @brief	Identifier card widget close voting
				 * @date 04/05/2012
				 * @author Yadickson Soto
				 */
				class IDCardWidgetCloseVotation: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
				{
				public:

					/**
					 * @brief	Class constructor.
					 * @date 04/05/2012
					 * @author Yadickson Soto
					 */
					IDCardWidgetCloseVotation();
					/**
					 * @brief	Class destroy.
					 * @date 04/05/2012
					 * @author Yadickson Soto
					 */
					~IDCardWidgetCloseVotation();

				protected:

				private:
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

				};
			}
		}
	}
}



#endif // _ID_CARD_WIDGET_CLOSE_VOTATION_H_
