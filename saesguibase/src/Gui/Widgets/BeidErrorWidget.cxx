/**
 * @file BeidErrorWidget.cxx
 * @brief Body class beid error widget
 * @date 23/04/2012
 * @author Yadickson Soto
 */

#include "BeidErrorWidget.hxx"
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

BeidErrorWidget::BeidErrorWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTitleConfig(SAESGUIConfigurationManager::Current()->getBEIDCardWidgetTitleErrorConfiguration());
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->getBEIDCardWidgetTextErrorConfiguration());

	refresh();
	setWidget(progress);
}

BeidErrorWidget::~BeidErrorWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void BeidErrorWidget::refresh()
{
	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.BeidErrorWidget.BeidErrorWidgetTitle"));
	progress->setText(_("Smartmatic.SAES.GUI.Widgets.BeidErrorWidget.ExtractCardInfo"));
	progress->setImage("ui/BEIDWrongCard.gif");
}

void BeidErrorWidget::start()
{
	unsigned int timeout = SAESGUIConfigurationManager::Current()->getBEIDCardWidgetTimeoutError();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &BeidErrorWidget::end), timeout);
}

void BeidErrorWidget::end()
{
	signalEnd.emit();
}
