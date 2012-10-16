/**
 * @file VMAuthenticationWidget.hxx
 * @brief Header class vm authentication widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#ifndef VMAUTHENTICATIONWIDGET_HXX_
#define VMAUTHENTICATIONWIDGET_HXX_

#include "AuthenticationWidget.hxx"

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
				 * @class PMAuthenticationWidget
				 * @brief Class pm authentication widget
				 * @date 31/03/2012
				 * @author Yadickson Soto
				 */
				class VMAuthenticationWidget : public AuthenticationWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param info info authentication
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					VMAuthenticationWidget(PollingPlaceInfoWidget * info);
					/**
					 * @brief Class destroy
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~VMAuthenticationWidget();

				private:

					Gtk::Alignment * alignmentKeypad; ///< align
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* VMAUTHENTICATIONWIDGET_HXX_ */
