/**
 * @file VotingForDisabledQuestionWidget.cxx
 * @brief Header class voting for disabled question
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#include "VotingForDisabledQuestionWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* VotingForDisabledQuestionWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledQuestionWidget",GETTEXT_PACKAGE);

VotingForDisabledQuestionWidget::VotingForDisabledQuestionWidget()
: Gtk::EventBox()
{
	mainFrame = NULL;
	mainVBox = NULL;
	labelTitle = NULL;
	assistedButton = NULL;
	accompaniedButton = NULL;

	initialize();

	add(*mainFrame);
	show_all_children();
}

VotingForDisabledQuestionWidget::~VotingForDisabledQuestionWidget()
{
	dispose();
}

void VotingForDisabledQuestionWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/VotingForDisabledQuestionWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - VotingForDisabledQuestionWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("label-title", labelTitle);
	builder->get_widget("hbox1", hbox1);
	builder->get_widget("hbox2", hbox2);
	builder->get_widget_derived("button1", assistedButton);
	builder->get_widget_derived("button2", accompaniedButton);

	labelTitle->set_label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledQuestionWidget.Question"));
	assistedButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledQuestionWidget.Assisted"));
	accompaniedButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledQuestionWidget.Accompanied"));

	LabelConfiguration labelConfig = SAESGUIConfigurationManager::Current()->getVotingForDisabledQuestionTitleConfiguration();
	LabelConfiguration::SetLabelConfiguration(labelTitle, labelConfig);

	ButtonConfiguration buttonConfig = SAESGUIConfigurationManager::Current()->getVotingForDisabledFunctionalityConfiguration().getQuestionButtonConf();

	assistedButton->set_size_request(buttonConfig.getButtonWidth(), buttonConfig.getButtonHeight());
	assistedButton->ModifyFontSize(buttonConfig.getFontSize());

	accompaniedButton->set_size_request(buttonConfig.getButtonWidth(), buttonConfig.getButtonHeight());
	accompaniedButton->ModifyFontSize(buttonConfig.getFontSize());
}

void VotingForDisabledQuestionWidget::dispose()
{
	remove();

	if (assistedButton)
	{
		delete assistedButton;
		assistedButton = NULL;
	}
	if(accompaniedButton)
	{
		delete accompaniedButton;
		accompaniedButton = NULL;
	}
}

Glib::SignalProxy0< void > VotingForDisabledQuestionWidget::getSignalAssistedButton()
{
	return assistedButton->signal_clicked();
}

Glib::SignalProxy0< void > VotingForDisabledQuestionWidget::getSignalAccompaniedButton()
{
	return accompaniedButton->signal_clicked();
}
