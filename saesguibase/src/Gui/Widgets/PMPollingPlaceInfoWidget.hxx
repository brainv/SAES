/*
 * PMPollingPlaceInfoWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef PMPOLLINGPLACEINFOWIDGET_HXX_
#define PMPOLLINGPLACEINFOWIDGET_HXX_

#include "PollingPlaceInfoWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class PMPollingPlaceInfoWidget : public PollingPlaceInfoWidget
				{
				public:
					PMPollingPlaceInfoWidget();
					virtual ~PMPollingPlaceInfoWidget();
					virtual void fillKey();
				};
			}
		}
	}
}

#endif /* PMPOLLINGPLACEINFOWIDGET_HXX_ */
