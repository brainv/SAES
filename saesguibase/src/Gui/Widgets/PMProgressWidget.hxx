/**
 * @file PMProgressWidget.hxx
 * @brief Header class president machine progress widget
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#ifndef PMPROGRESSWIDGET_HXX_
#define PMPROGRESSWIDGET_HXX_

#include <Gui/Widgets/ProgressWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class PMProgressWidget
				 * @brief Class president machine progress widget
				 * @date 02/11/2011
				 * @author Yadickson Soto
				 * @see ProgressWidget
				 */
				class PMProgressWidget: public ProgressWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					PMProgressWidget();
					/**
					 * @brief Class destroy
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual ~PMProgressWidget();
					/**
					 * @brief Virtual method setter image type
					 * @param image image type
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual void setImage(ProgressImage image);
				};
			}
		}
	}
}

#endif /* PMPROGRESSWIDGET_HXX_ */
