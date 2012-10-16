/*
 * PMPollingPlaceInfoWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef PMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_
#define PMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_

#include "PollingPlaceInfoWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class PMAuthenticationPollingPlaceInfoWidget : public PollingPlaceInfoWidget
				{
				public:
					PMAuthenticationPollingPlaceInfoWidget();
					virtual ~PMAuthenticationPollingPlaceInfoWidget();
					virtual void fillKey();
				};
			}
		}
	}
}

#endif /* PMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_ */
