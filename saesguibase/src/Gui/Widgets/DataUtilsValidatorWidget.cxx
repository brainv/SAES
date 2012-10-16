/**
 * @file DataUtilsValidatorWidget.cxx
 * @brief Body class data util validator
 * @date 24/07/2012
 * @author Yadickson Soto
 */

#include "DataUtilsValidatorWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;

DataUtilsValidatorWidget::DataUtilsValidatorWidget(ProgressWidget * progressWidget)
: progressWidget(progressWidget)
{
	progressWidget->setTitle(" ");
	progressWidget->setText(" ");
	progressWidget->setImage(ProgressWidget::PROGRESS);

	conteinerWidget = new NotebookContainer();
	conteinerWidget->ShowTabs(true);

	int columns = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getColumns();
	int width = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getWidth();
	int height = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getHeight();

	resultWidget = new DataUtilsResultWidget();
	listResultSuccessWidget = new ListResultWidget(columns, columns * width, height);
	listResultFailWidget = new ListResultWidget(columns, columns * width, height);

	setWidget(progressWidget);
}

DataUtilsValidatorWidget::~DataUtilsValidatorWidget()
{
	remove();

	if (progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
	if (conteinerWidget)
	{
		delete conteinerWidget;
		conteinerWidget = NULL;
	}
	if (resultWidget)
	{
		delete resultWidget;
		resultWidget = NULL;
	}
	if (listResultSuccessWidget)
	{
		delete listResultSuccessWidget;
		listResultSuccessWidget = NULL;
	}
	if (listResultFailWidget)
	{
		delete listResultFailWidget;
		listResultFailWidget = NULL;
	}

	resultMap.clear();
}

void DataUtilsValidatorWidget::setCenter(std::string center)
{
	currentCenter = center;
}

void DataUtilsValidatorWidget::addResult(std::string key)
{
	ResultWidget::Result result;
	result.status = true;
	result.message = key;
	resultMap[currentCenter].push_back(result);
}

void DataUtilsValidatorWidget::addFailResult(std::string key)
{
	ResultWidget::Result result;
	result.status = false;
	result.message = key;
	resultMap[currentCenter].push_back(result);
}

void DataUtilsValidatorWidget::showProgress(std::string center, int current, int total)
{
	std::stringstream ss;
	ss << current << "/" << total;

	progressWidget->setTitle(center);
	progressWidget->setText(ss.str());
}

void DataUtilsValidatorWidget::showError(std::string key)
{
	progressWidget->setText(key);
	progressWidget->setImage("ui/result-error.png");
}

void DataUtilsValidatorWidget::showResult()
{
	std::map <std::string, std::list <Smartmatic::SAES::GUI::Widgets::ResultWidget::Result> >::iterator itm;

	int width = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getWidth();
	int height = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getHeight();

	ResultWidget * widget = NULL;

	for (itm = resultMap.begin();
			itm != resultMap.end();
			itm++)
	{
		widget = new ResultWidget();
		widget->setResult((*itm).second);
		widget->setText((*itm).first);
		widget->set_size_request(width, height);

		if (widget->getStatus())
		{
			listResultSuccessWidget->addWidget(widget);
		}
		else
		{
			listResultFailWidget->addWidget(widget);
		}
	}

	resultWidget->setResult(listResultSuccessWidget->getCountWidget(), listResultFailWidget->getCountWidget());

	conteinerWidget->AppendPage(resultWidget, _("Smartmatic.SAES.GUI.Widgets.DataUtilsValidatorWidget.Statistics"));

	if (listResultSuccessWidget->getCountWidget() > 0)
	{
		conteinerWidget->AppendPage(listResultSuccessWidget, _("Smartmatic.SAES.GUI.Widgets.DataUtilsValidatorWidget.Success"));
	}

	if (listResultFailWidget->getCountWidget() > 0)
	{
		conteinerWidget->AppendPage(listResultFailWidget, _("Smartmatic.SAES.GUI.Widgets.DataUtilsValidatorWidget.Fail"));
	}

	conteinerWidget->SetCurrentPage(0);

	setWidget(conteinerWidget);
}
