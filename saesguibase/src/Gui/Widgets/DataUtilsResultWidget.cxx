/*
 * DataUtilsResultWidget.cxx
 *
 *  Created on: 24/07/2012
 *      Author: yadickson
 */

#include "DataUtilsResultWidget.hxx"
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
using namespace Smartmatic::SAES::GUI::Configuration;

DataUtilsResultWidget::DataUtilsResultWidget()
: Gtk::EventBox()
{
	int columns = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getColumns();
	int width = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getWidth();
	int height = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getHeight();

	listResultWidget = new ListResultWidget(1, columns * width, height);
	add(*listResultWidget);
}

DataUtilsResultWidget::~DataUtilsResultWidget()
{
	remove();

	if (listResultWidget)
	{
		delete listResultWidget;
		listResultWidget = NULL;
	}
}

void DataUtilsResultWidget::setResult(int success, int fail)
{
	int width = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getWidth();
	int height = SAESGUIConfigurationManager::Current()->getDataUtilsValidatorFunctionalityConfiguration().getHeight();

	{
		ResultWidget * widget = new ResultWidget();
		std::stringstream ss;
		ss << _("Smartmatic.SAES.GUI.Widgets.DataUtilsResultWidget.Success") << success;
		widget->set_size_request(width, height);
		widget->setText(ss.str());
		widget->setStatus(true);
		listResultWidget->addWidget(widget);
	}

	{
		ResultWidget * widget = new ResultWidget();
		std::stringstream ss;
		ss << _("Smartmatic.SAES.GUI.Widgets.DataUtilsResultWidget.Fail") << fail;
		widget->set_size_request(width, height);
		widget->setText(ss.str());
		widget->setStatus(false);
		listResultWidget->addWidget(widget);
	}
}
