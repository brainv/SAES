/**
 * @file ScreenVotingWidget.cxx
 * @brief Body class screen info voting widget
 * @date 30/04/2012
 * @author Yadickson Soto
 */

#include "ScreenVotingWidget.hxx"
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

ScreenVotingWidget::ScreenVotingWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	centerName = " ";
	totalCenters = 0;
	currentCenter = -1;

	progress->setTitleConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());
	progress->setImage("ui/cargando.gif");

	setTitle(false);
	setShowBorder(true);
	setWidget(progress);
}

ScreenVotingWidget::~ScreenVotingWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void ScreenVotingWidget::setCenterName(std::string centerName)
{
	this->centerName = centerName;
}

void ScreenVotingWidget::setCurrentCenter(int currentCenter)
{
	this->currentCenter = currentCenter;
}

void ScreenVotingWidget::setTotalCenter(int totalCenters)
{
	this->totalCenters = totalCenters;
}

void ScreenVotingWidget::setImageError()
{
	progress->setImage("ui/screen-error.png");
}

void ScreenVotingWidget::setImageOk()
{
	progress->setImage("ui/screen-ok.png");
}

void ScreenVotingWidget::refresh()
{
	progress->setTitle(centerName);

	if (currentCenter >= 0)
	{
		std::stringstream ss;
		ss << currentCenter << "/" << totalCenters;
		progress->setText(ss.str());
	}
	else
	{
		progress->setText(" ");
	}
}
