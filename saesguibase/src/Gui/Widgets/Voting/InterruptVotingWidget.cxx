/**
 * @file InterruptVotingWidget.cxx
 * @brief Body class interrupt voting widget
 * @date 17/04/2012
 * @author Yadickson Soto
 */

#include "InterruptVotingWidget.hxx"
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

ISMTTLog* InterruptVotingWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.InterruptVotingWidget",GETTEXT_PACKAGE);

InterruptVotingWidget::InterruptVotingWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/InterruptVotingWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - InterruptVotingWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("center-frame", centerFrame);
	builder->get_widget("hbox-button", hboxButton);
	builder->get_widget_derived("button", button);

	button->WidgetsPosition (5,0,0);
	button->set_size_request (300,100);
	button->set_no_show_all();

	centerFrame->add(*progress);

	setTitle(false);
	setShowBorder(true);

	changeState(INTERRUPTVOTING_CARDCOUNTER);
}

InterruptVotingWidget::~InterruptVotingWidget()
{
	remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (centerFrame)
	{
		delete centerFrame;
		centerFrame = NULL;
	}
	if (hboxButton)
	{
		delete hboxButton;
		hboxButton = NULL;
	}
	if (button)
	{
		delete button;
		button = NULL;
	}
}

void InterruptVotingWidget::refresh()
{
	changeState(currentState);
}

void InterruptVotingWidget::changeState(InterrupVotingState state)
{
	currentState = state;
	button->SetLabel(_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.CancelVoteStr"));

	switch(state)
	{
		case INTERRUPTVOTING_CARDCOUNTER:
			progress->setText(_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.ExtractionStr"));
			progress->setImage("ui/InterruptExtractVoterCard.gif");
			button->hide();
			break;
		case INTERRUPTVOTING_CANCELPROCESS:
			progress->setText(_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.WrongCardStr"));
			progress->setImage("ui/InterruptExtractVoterCard.gif");
			button->show();
			break;
	}

	setWidget(mainFrame);
}

Glib::SignalProxy0<void> InterruptVotingWidget::getSignalClick()
{
	return button->signal_clicked();
}
