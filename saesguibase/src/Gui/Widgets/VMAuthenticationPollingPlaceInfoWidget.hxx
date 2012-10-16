/*
 * VMPollingPlaceInfoWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef VMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_
#define VMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_

#include "PollingPlaceInfoWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class VMAuthenticationPollingPlaceInfoWidget : public PollingPlaceInfoWidget
				{
				public:
					VMAuthenticationPollingPlaceInfoWidget();
					virtual ~VMAuthenticationPollingPlaceInfoWidget();
					virtual void fillKey();
				};
			}
		}
	}
}

#endif /* VMAUTHENTICATIONPOLLINGPLACEINFOWIDGET_HXX_ */
