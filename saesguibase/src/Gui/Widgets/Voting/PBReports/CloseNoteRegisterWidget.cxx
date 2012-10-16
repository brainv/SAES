/**
 * @file CloseNoteRegisterWidget.cxx
 * @brief Body class voting for disabled
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#include "CloseNoteRegisterWidget.hxx"
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

CloseNoteRegisterWidget::CloseNoteRegisterWidget()
: Smartmatic::GUI::Widgets::RegisterActionWidget<CloseNoteRegisterInfoWidget *>()
{
	registerWidget = NULL;
	addInfoButton = NULL;
	nextButton = NULL;
	registerNotesLabel = NULL;

	initialize();

	Gtk::VBox * vboxOut = manage(new Gtk::VBox());
	vboxOut->pack_start(*registerNotesLabel,false,false);
	vboxOut->pack_start(*registerWidget);
	vboxOut->show();
	vboxOut->show_all_children();

	enableNextButton(false);

	add(*vboxOut);
	show_all_children();
}

CloseNoteRegisterWidget::~CloseNoteRegisterWidget()
{
	dispose();
}

void CloseNoteRegisterWidget::initialize()
{
	dispose();

	ButtonConfiguration addConfig = SAESGUIConfigurationManager::Current()->getCloseNoteRegisterFunctionalityConfiguration().getAddButtonConf();

	addInfoButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.CreateNote"));
	addInfoButton->set_size_request(addConfig.getButtonWidth(), addConfig.getButtonHeight());
	addInfoButton->ModifyFontSize(addConfig.getFontSize());

	ButtonConfiguration nextConfig = SAESGUIConfigurationManager::Current()->getCloseNoteRegisterFunctionalityConfiguration().getNextButtonConf();

	nextButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.ConfirmNotes"));
	nextButton->set_size_request(nextConfig.getButtonWidth(), nextConfig.getButtonHeight());
	nextButton->ModifyFontSize(nextConfig.getFontSize());
	nextButton->set_sensitive(false);
	nextButton->set_no_show_all();

	Gtk::HButtonBox* hbox = manage(new Gtk::HButtonBox());
	hbox->pack_start(*addInfoButton);
	hbox->pack_start(*nextButton);
	hbox->set_layout(Gtk::BUTTONBOX_SPREAD);
	hbox->set_spacing(5);

	RegisterWidgetConfiguration registerConfig = SAESGUIConfigurationManager::Current()->getCloseNoteRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();

	int row = registerConfig.getMaxRow();
	int col = registerConfig.getMaxColumn();
	int spacing = registerConfig.getSpacingBox();
	int width = registerConfig.getWidthBox();
	int height = registerConfig.getHeigthBox();
	bool verticalFilling = registerConfig.getVerticalFilling();

	registerWidget = new RegisterWidget(false, hbox);
	registerWidget->setConfig(row, col, spacing, spacing, width, height, verticalFilling);

	int minimunNotesToRegister = SAESGUIConfigurationManager::Current()->GetMinimunNotesToRegisterConfiguration();

	std::string titleText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.RegisterMinimunNotes"), minimunNotesToRegister);
	registerNotesLabel = new Gtk::Label(titleText);

	Pango::FontDescription fontSuperNull = registerNotesLabel->get_style()->get_font();
	fontSuperNull.set_size(16*Pango::SCALE);
	fontSuperNull.set_weight(Pango::WEIGHT_ULTRABOLD);
	registerNotesLabel->modify_font(fontSuperNull);
	registerNotesLabel->set_no_show_all();
	registerNotesLabel->set_size_request(-1, 40);
	registerNotesLabel->set_visible(true);
}

void CloseNoteRegisterWidget::dispose()
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
	if (nextButton)
	{
		delete nextButton;
		nextButton = NULL;
	}
	if (registerNotesLabel)
	{
		delete registerNotesLabel;
		registerNotesLabel = NULL;
	}
}

Glib::SignalProxy0< void > CloseNoteRegisterWidget::getSignalAddInfoButton()
{
	return addInfoButton->signal_clicked();
}

Glib::SignalProxy0< void > CloseNoteRegisterWidget::getSignalNextButton()
{
	return nextButton->signal_clicked();
}

void CloseNoteRegisterWidget::showNextButton()
{
	nextButton->show();
}

void CloseNoteRegisterWidget::enableNextButton(bool sensitive)
{
	registerNotesLabel->set_visible(!sensitive);
	nextButton->set_sensitive(sensitive);
}
