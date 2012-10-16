/**
 * @file DataUtilsValidatorWidget.hxx
 * @brief Header class data util validator
 * @date 24/07/2012
 * @author Yadickson Soto
 */

#ifndef DATAUTILSVALIDATORWIDGET_HXX_
#define DATAUTILSVALIDATORWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include <Gui/Widgets/ProgressWidget.hxx>
#include <Gui/Widgets/ListResultWidget.hxx>
#include <Gui/Widgets/DataUtilsResultWidget.hxx>
#include <Widgets/notebook-container.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class DataUtilsValidatorWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					DataUtilsValidatorWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget);
					virtual ~DataUtilsValidatorWidget();

					void setCenter(std::string center);
					void addResult(std::string key);
					void addFailResult(std::string key);

					void showProgress(std::string center, int current, int total);
					void showError(std::string key);
					void showResult();

				private:

					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget; ///< progress widget
					Smartmatic::GUI::Widgets::NotebookContainer * conteinerWidget; ///< conteiner widget

					Smartmatic::SAES::GUI::Widgets::DataUtilsResultWidget * resultWidget; ///< result statistics widget
					Smartmatic::SAES::GUI::Widgets::ListResultWidget * listResultSuccessWidget; ///< result success widget
					Smartmatic::SAES::GUI::Widgets::ListResultWidget * listResultFailWidget; ///< result faild widget

					std::string currentCenter; ///< current center
					std::map <std::string, std::list <Smartmatic::SAES::GUI::Widgets::ResultWidget::Result> > resultMap; ///< result map
				};
			}
		}
	}
}

#endif /* DATAUTILSVALIDATORWIDGET_HXX_ */
