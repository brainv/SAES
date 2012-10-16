/**
 * @file PMAuthenticationWidget.hxx
 * @brief Header class pm authentication widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#ifndef PMAUTHENTICATIONWIDGET_HXX_
#define PMAUTHENTICATIONWIDGET_HXX_

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
				class PMAuthenticationWidget : public AuthenticationWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param info info authentication
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					PMAuthenticationWidget(PollingPlaceInfoWidget * info);
					/**
					 * @brief Class destroy
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~PMAuthenticationWidget();
					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();

				private:

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* PMAUTHENTICATIONWIDGET_HXX_ */
