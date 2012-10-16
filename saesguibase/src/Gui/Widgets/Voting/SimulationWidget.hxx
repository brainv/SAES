/**
 * @file SimulationWidget.hxx
 * @brief Header class simulation custom attributes widget
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#ifndef SIMULATIONWIDGET_HXX_
#define SIMULATIONWIDGET_HXX_

#include <Widgets/ChooseSelectionWidget.hxx>
#include <Voting/VotingDevice/card-data-schema.hxx>

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
					/**
					 * @class SimulationWidget
					 * @brief class simulation custom attributes widget
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					class SimulationWidget : public Smartmatic::GUI::Widgets::ChooseSelectionWidget
					{
					public:
						/**
						 * @brief class constructor
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						SimulationWidget();
						/**
						 * @brief class destroy
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~SimulationWidget();
						/**
						 * @brief initialize info list
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						void initialize();
						/**
						 * @brief next step
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						void next();
						/**
						 * @brief method getter option selected
						 * @return option selected
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						std::vector <Smartmatic::GUI::Widgets::ChooseDialogButtonInfo*> & getOptionsSelected();
						/**
						 * @brief method getter card data
						 * @param cardData result card data
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						void getCardData(Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData);

					private:
						/**
						 * @brief method signal option selected
						 * @param choose option selected
						 * @date 12/04/2012
						 * @author Yadickson Soto
						 */
						virtual void onSelected(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* choose);

						unsigned int currentInfo; ///< current info
						std::vector <Smartmatic::GUI::Widgets::ChooseDialogInfo *> infoList; ///< info list
						std::vector <Smartmatic::GUI::Widgets::ChooseDialogButtonInfo*> options; ///< options selected
					};
				}
			}
		}
	}
}

#endif /* SIMULATIONWIDGET_HXX_ */
