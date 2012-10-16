/**
 * @file RemoveCardWidget.cxx
 * @brief Body class card removed widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#include "RemoveCardWidget.hxx"
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

RemoveCardWidget::RemoveCardWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	refresh();

	setTitle(false);
	setShowBorder(true);
	setWidget(progress);
}

RemoveCardWidget::~RemoveCardWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void RemoveCardWidget::refresh()
{
	if (SAESGUIConfigurationManager::Current()->getVotingExperienceConfiguration().getRemoveCardFirst())
	{
		progress->setText(N_("Smartmatic.SAES.GUI.Widgets.Voting.RemoveCardWidget.PleaseRemoveTheCard"));
	}
	else
	{
		progress->setText(_("Smartmatic.SAES.GUI.Windows.VotingWindow.PleaseRemoveTheCard"));
	}
	progress->setImage("ui/RemoveTheCard.gif");
}

