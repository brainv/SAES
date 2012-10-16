/**
 * @file PrintVoteErrorWidget.cxx
 * @brief Body class print vote error widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#include "PrintVoteErrorWidget.hxx"
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

PrintVoteErrorWidget::PrintVoteErrorWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	refresh();

	setTitle(false);
	setShowBorder(true);
	setWidget(progress);
}

PrintVoteErrorWidget::~PrintVoteErrorWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void PrintVoteErrorWidget::refresh()
{
	progress->setText(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.ErrorPrinting"));
	progress->setImage("ui/printer_voting_error.img");
}

void PrintVoteErrorWidget::setText(std::string text)
{
	progress->setText(text);
}
