/**
 * @file PoliceNoteRegisterWidget.cxx
 * @brief Body class voting for disabled
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNoteRegisterWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

PoliceNoteRegisterWidget::PoliceNoteRegisterWidget()
: Smartmatic::GUI::Widgets::RegisterActionWidget<PoliceNoteRegisterInfoWidget *>()
{
	registerWidget = NULL;
	addInfoButton = NULL;

	initialize();

	add(*registerWidget);
	show_all_children();
}

PoliceNoteRegisterWidget::~PoliceNoteRegisterWidget()
{
	dispose();
}

void PoliceNoteRegisterWidget::initialize()
{
	dispose();

	ButtonConfiguration addConfig = SAESGUIConfigurationManager::Current()->getPoliceNoteRegisterFunctionalityConfiguration().getAddButtonConf();

	addInfoButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.CreateNote"));
	addInfoButton->set_size_request(addConfig.getButtonWidth(), addConfig.getButtonHeight());
	addInfoButton->ModifyFontSize(addConfig.getFontSize());

	Gtk::HButtonBox* hbox = manage(new Gtk::HButtonBox());
	hbox->pack_start(*addInfoButton);
	hbox->set_layout(Gtk::BUTTONBOX_SPREAD);
	hbox->set_spacing(5);

	RegisterWidgetConfiguration registerConfig = SAESGUIConfigurationManager::Current()->getPoliceNoteRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();

	int row = registerConfig.getMaxRow();
	int col = registerConfig.getMaxColumn();
	int spacing = registerConfig.getSpacingBox();
	int width = registerConfig.getWidthBox();
	int height = registerConfig.getHeigthBox();
	bool verticalFilling = registerConfig.getVerticalFilling();

	registerWidget = new RegisterWidget(false, hbox);
	registerWidget->setConfig(row, col, spacing, spacing, width, height, verticalFilling);
}

void PoliceNoteRegisterWidget::dispose()
{
	remove();

	if (registerWidget)
	{
		delete registerWidget;
		registerWidget = NULL;
	}
	if (addInfoButton)
	{
		delete addInfoButton;
		addInfoButton = NULL;
	}
}

Glib::SignalProxy0< void > PoliceNoteRegisterWidget::getSignalAddInfoButton()
{
	return addInfoButton->signal_clicked();
}
