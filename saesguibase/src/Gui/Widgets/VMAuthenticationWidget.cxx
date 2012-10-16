/**
 * @file VMAuthenticationWidget.cxx
 * @brief Body class vm authentication widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#include "VMAuthenticationWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/label-configuration.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
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
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* VMAuthenticationWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.VMAuthenticationWidget",GETTEXT_PACKAGE);

VMAuthenticationWidget::VMAuthenticationWidget(PollingPlaceInfoWidget * info)
: AuthenticationWidget(N_("Smartmatic.SAES.GUI.Windows.AuthenticationWindow.Title"), info)
{
	Glib::RefPtr<Gtk::Builder> builder;

	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/VMAuthenticationWidget.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("info-frame", infoFrame);
	builder->get_widget("top-label", topLabel);
	builder->get_widget("key-frame", keyFrame);
	builder->get_widget("bottom-label", bottomLabel);
	builder->get_widget("alarm-label", alarmLabel);
	builder->get_widget("alignment-keypad", alignmentKeypad);

	if (info)
	{
		infoFrame->set_name("infoFrame");
		infoFrame->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
		infoFrame->add(*info);
		infoFrame->show_all_children();
	}
	else
	{
		infoFrame->set_shadow_type(Gtk::SHADOW_NONE);
	}

	infoFrame->show();

	keyFrame->add(*keypadTest);
	keypadTest->show();
    config();

    alarmLabel->show();
    setWidget(mainFrame);
}

VMAuthenticationWidget::~VMAuthenticationWidget()
{
	remove();

	if (alignmentKeypad)
	{
		delete alignmentKeypad;
		alignmentKeypad = NULL;
	}

	AuthenticationWidget::dispose();
}

