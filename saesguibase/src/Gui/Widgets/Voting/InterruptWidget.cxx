/**
 * @file InterruptWidget.cxx
 * @brief Body class interrupt voting widget
 * @date 17/04/2012
 * @author Yadickson Soto
 */

#include "InterruptWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include "FactoryVotingWidget.hxx"

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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;

InterruptWidget::InterruptWidget()
: StepWidget()
{
	setTitle(false);
	setShowBorder(true);

	interruptVotingWidget = FactoryVotingWidget::createInterruptVotingWidget();
	keypassWidget = FactoryVotingWidget::createKeypadVotingPasswordWidget();
	endVotingWidget = FactoryVotingWidget::createEndVotingWidget();

	interruptVotingWidget->getSignalClick().connect(sigc::mem_fun(this, &InterruptWidget::onActionClicked));
	keypassWidget->getSignalOk().connect(sigc::mem_fun(this, &InterruptWidget::showEnd));

	setWidget(interruptVotingWidget);
}

InterruptWidget::~InterruptWidget()
{
	remove();

	if (interruptVotingWidget)
	{
		delete interruptVotingWidget;
		interruptVotingWidget = NULL;
	}
	if (keypassWidget)
	{
		delete keypassWidget;
		keypassWidget = NULL;
	}
	if (endVotingWidget)
	{
		delete endVotingWidget;
		endVotingWidget = NULL;
	}
}

void InterruptWidget::refresh()
{
	interruptVotingWidget->refresh();
	keypassWidget->refresh();
	endVotingWidget->refresh();

	setWidget(interruptVotingWidget);
}

void InterruptWidget::showCardCounter()
{
	interruptVotingWidget->changeState(InterruptVotingWidget::INTERRUPTVOTING_CARDCOUNTER);
}

void InterruptWidget::showCancelProcess()
{
	interruptVotingWidget->changeState(InterruptVotingWidget::INTERRUPTVOTING_CANCELPROCESS);
}

void InterruptWidget::onActionClicked()
{
	setWidget(keypassWidget);
}

void InterruptWidget::showEnd()
{
	setWidget(endVotingWidget);
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &InterruptWidget::close), 1000);
}

void InterruptWidget::close()
{
	signalEnd.emit();
}

