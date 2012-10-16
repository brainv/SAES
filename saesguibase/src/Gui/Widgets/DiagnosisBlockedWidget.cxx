/**
 * @file DiagnosisBlockedWidget.cxx
 * @brief Body class diagnosis blocked
 * @date 12/06/2012
 * @author Yadickson Soto
 */

#include "DiagnosisBlockedWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;

ISMTTLog* DiagnosisBlockedWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.DiagnosisBlockedWidget",GETTEXT_PACKAGE);

DiagnosisBlockedWidget::DiagnosisBlockedWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	button = NULL;
	mainVBox = NULL;
	mainEventBox = NULL;
	hbuttonbox = NULL;

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/DiagnosisBlockedWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ProgressWidget Initialize");
	}

	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("main-eventbox", mainEventBox);
	builder->get_widget("hbuttonbox", hbuttonbox);
	builder->get_widget_derived("button", button);

	button->SetButtonType(SmartmaticButton::Ok);
	button->WidgetsPosition(5,6,0);

	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->getBlockDiagnosticTitle();
	ButtonConfiguration buttonConf = SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getBlockDiagnosticButton();

	progress->setTitleConfig(labelConf);
	mainEventBox->add(*progress);

	button->ModifyFontSize(buttonConf.getFontSize());
	button->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());

	refresh();
	setWidget(mainVBox);
}

DiagnosisBlockedWidget::~DiagnosisBlockedWidget()
{
	remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (mainEventBox)
	{
		delete mainEventBox;
		mainEventBox = NULL;
	}
	if (hbuttonbox)
	{
		delete hbuttonbox;
		hbuttonbox = NULL;
	}
	if (button)
	{
		delete button;
		button = NULL;
	}
}

void DiagnosisBlockedWidget::refresh()
{
	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.DiagnosisBlockedWidget.TitleMessage"));
	progress->setImage(ProgressWidget::AUTO_DIAGNOSIS_DEVICES);
	button->SetLabel(_("Smartmatic.SAES.GUI.Widgets.DiagnosisBlockedWidget.Ok"));
}

Glib::SignalProxy0<void> DiagnosisBlockedWidget::getSignalClicked()
{
	return button->signal_clicked();
}
