/**
 * @file EndPrintVoteWidget.cxx
 * @brief Body class end print vote widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#include "EndPrintVoteWidget.hxx"
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

EndPrintVoteWidget::EndPrintVoteWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	refresh();

	setTitle(false);
	setShowBorder(true);
	setWidget(progress);
}

EndPrintVoteWidget::~EndPrintVoteWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void EndPrintVoteWidget::refresh()
{
	if (SAESGUIConfigurationManager::Current()->getVotingExperienceConfiguration().getRemoveCardFirst())
	{
		progress->setText(N_("Smartmatic.SAES.GUI.Widgets.Voting.EndPrintVoteWidget.BendPrintedTicket"));
	}
	else
	{
		progress->setText(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BendPrintedTicket"));
	}

	progress->setImage("ui/voting-experience-finalization-image.gif");
}

void EndPrintVoteWidget::setText(std::string text)
{
	progress->setText(text);
}
