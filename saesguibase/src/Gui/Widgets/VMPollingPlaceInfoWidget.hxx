/*
 * VMPollingPlaceInfoWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef VMPOLLINGPLACEINFOWIDGET_HXX_
#define VMPOLLINGPLACEINFOWIDGET_HXX_

#include "PollingPlaceInfoWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class VMPollingPlaceInfoWidget : public PollingPlaceInfoWidget
				{
				public:
					VMPollingPlaceInfoWidget();
					virtual ~VMPollingPlaceInfoWidget();
					virtual void fillKey();
				};
			}
		}
	}
}

#endif /* VMPOLLINGPLACEINFOWIDGET_HXX_ */
