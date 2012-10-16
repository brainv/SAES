/**
 * @file PrintTimeOutWidget.cxx
 * @brief Body class print time out widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#include "PrintTimeOutWidget.hxx"
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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;

PrintTimeOutWidget::PrintTimeOutWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	refresh();

	setTitle(false);
	setShowBorder(true);
	setWidget(progress);
}

PrintTimeOutWidget::~PrintTimeOutWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void PrintTimeOutWidget::refresh()
{
	progress->setText(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.WaitPrintingTicket"));
	progress->setImage("ui/time-out-end-voting-experience.img");
}

void PrintTimeOutWidget::setText(std::string text)
{
	progress->setText(text);
}
