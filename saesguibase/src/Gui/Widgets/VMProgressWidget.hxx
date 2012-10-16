/*
 * VMProgressWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef VMPROGRESSWIDGET_HXX_
#define VMPROGRESSWIDGET_HXX_

#include <Gui/Widgets/ProgressWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class VMProgressWidget : public ProgressWidget
				{
				public:
					VMProgressWidget();
					virtual ~VMProgressWidget();
					virtual void setImage(ProgressImage image);
				};
			}
		}
	}
}

#endif /* VMPROGRESSWIDGET_HXX_ */
