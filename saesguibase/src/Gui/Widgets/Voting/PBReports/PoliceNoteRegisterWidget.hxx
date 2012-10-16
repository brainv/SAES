/**
 * @file PoliceNoteRegisterWidget.hxx
 * @brief Header class police note
 * @data 25/05/2012
 * @author Yadickson Soto
 */

#ifndef POLICENOTEREGISTERWIDGET_HXX_
#define POLICENOTEREGISTERWIDGET_HXX_

#include <Widgets/smartmatic-button.h>
#include <Widgets/RegisterWidget.hxx>
#include <Widgets/RegisterActionWidget.hxx>
#include "PoliceNoteRegisterInfoWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					namespace PBReports
					{
						/**
						 * @class PoliceNoteRegisterWidget
						 * @brief class police note
						 * @data 25/05/2012
						 * @author Yadickson Soto
						 */
						class PoliceNoteRegisterWidget : public Smartmatic::GUI::Widgets::RegisterActionWidget<PoliceNoteRegisterInfoWidget *>
						{
						public:
							/**
							 * @brief class constructor
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							PoliceNoteRegisterWidget();
							/**
							 * @brief class destroy
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~PoliceNoteRegisterWidget();
							/**
							 * @brief virtual method init
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();
							/**
							 * @brief method getter signal add info
							 * @return signal add info
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalAddInfoButton();

						private:

							Smartmatic::GUI::Widgets::SmartmaticButton * addInfoButton; ///< add info
						};
					}
				}
			}
		}
	}
}

#endif /* POLICENOTEREGISTERWIDGET_HXX_ */
