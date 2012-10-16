/**
 * @file VotingExperienceValidationWidget.cxx
 * @brief Body class voting experience validation widget
 * @date 25/04/2012
 * @author Yadickson Soto
 */

#include "VotingExperienceValidationWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Environment/Configurations/resource-path-provider.h>
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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;

ISMTTLog* VotingExperienceValidationWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.VotingExperienceValidationWidget",GETTEXT_PACKAGE);

VotingExperienceValidationWidget::VotingExperienceValidationWidget()
: StepWidget()
{
	mainFrame = NULL;
	vBox = NULL;
	hBox1 = NULL;
	hBox2 = NULL;
	allButton = NULL;
	ballotButton = NULL;

	initialize();
	refresh();
}

VotingExperienceValidationWidget::~VotingExperienceValidationWidget()
{
	dispose();
}

void VotingExperienceValidationWidget::initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;

	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/VotingExperienceValidationWidget.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("vbox", vBox);
	builder->get_widget("hbox1", hBox1);
	builder->get_widget("hbox2", hBox2);
	builder->get_widget_derived("button1", ballotButton);
	builder->get_widget_derived("button2", allButton);

	ButtonConfiguration conf = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getScreensButtonConf();

	int width = conf.getButtonWidth();
	int height = conf.getButtonHeight();

	ballotButton->set_size_request(width, height);
	ballotButton->ModifyFontSize(conf.getFontSize());

	allButton->set_size_request(width, height);
	allButton->ModifyFontSize(conf.getFontSize());

	setWidget(mainFrame);
}

void VotingExperienceValidationWidget::dispose()
{
	remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (vBox)
	{
		delete vBox;
		vBox = NULL;
	}
	if (hBox1)
	{
		delete hBox1;
		hBox1 = NULL;
	}
	if (hBox2)
	{
		delete hBox2;
		hBox2 = NULL;
	}
	if (ballotButton)
	{
		delete ballotButton;
		ballotButton = NULL;
	}
	if (allButton)
	{
		delete allButton;
		allButton = NULL;
	}
}

void VotingExperienceValidationWidget::refresh()
{
	ballotButton->set_label(_("Smartmatic.SAES.GUI.Widgets.Voting.VotingExperienceValidationWidget.GeneratePartyAndBallot"));
	allButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality.GenerateAll"));
}

Glib::SignalProxy0< void > VotingExperienceValidationWidget::getSignalBallot()
{
	return ballotButton->signal_clicked();
}

Glib::SignalProxy0< void > VotingExperienceValidationWidget::getSignalAll()
{
	return allButton->signal_clicked();
}
