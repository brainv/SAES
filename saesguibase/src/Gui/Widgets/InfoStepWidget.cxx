/**
 * @file InfoStepWidget.cxx
 * @brief Body exit widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#include "InfoStepWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/label-configuration.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;

InfoStepWidget::InfoStepWidget()
: StepWidget()
{
	this->labelInfo = NULL;
	this->info = " ";
	this->timeout = 0;

	initialize();
	setWidget(labelInfo);
}

InfoStepWidget::InfoStepWidget(std::string info, int timeout)
: StepWidget()
{
	this->labelInfo = NULL;
	this->info = info;
	this->timeout = timeout;

	initialize();
	setWidget(labelInfo);
}

InfoStepWidget::~InfoStepWidget()
{
	dispose();
}

void InfoStepWidget::initialize()
{
	labelInfo = new Gtk::Label();
	labelInfo->show();

	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->GetExitMessageLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(labelInfo, labelConf);
}

void InfoStepWidget::dispose()
{
	this->remove();

	if (labelInfo)
	{
		delete labelInfo;
		labelInfo = NULL;
	}
}

void InfoStepWidget::setInfo(std::string info)
{
	this->info = info;
}

void InfoStepWidget::setTimeout(int timeout)
{
	this->timeout = timeout;
}

int InfoStepWidget::getTimeout()
{
	return timeout;
}

void InfoStepWidget::refresh()
{
	labelInfo->set_text(_(info.c_str()));
}
