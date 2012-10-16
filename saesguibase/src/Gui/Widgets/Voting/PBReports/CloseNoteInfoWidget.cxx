/**
 * @file CloseNoteInfoWidget.cxx
 * @brief Body class close note info widget
 * @date 24/05/2012
 * @author Yadickson Soto
 */

#include "CloseNoteInfoWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/ValidateWidget.hxx>

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
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Operation;

CloseNoteInfoWidget::CloseNoteInfoWidget()
: IDCardWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.WriterInfo"),"",true)
{
	ButtonConfiguration buttonConf = SAESGUIConfigurationManager::Current()->getCloseNoteRegisterFunctionalityConfiguration().getAddCancelButtonConf();

	widget = NULL;

	HideAcceptTitle();
	SetShowAcept(false);

	backButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.Back")));
	backButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseNoteInfoWidget::backClicked));
	backButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);
	backButton->ModifyFontSize(buttonConf.getFontSize());

	acceptButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.AddNote")));
	acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseNoteInfoWidget::checkInfo));
	acceptButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	acceptButton->SetButtonType(SmartmaticButton::Ok);
	acceptButton->WidgetsPosition(5,6,0);
	acceptButton->ModifyFontSize(buttonConf.getFontSize());

	check = manage(new Gtk::CheckButton());
	check->set_size_request(entryWidth, entryHeight);

	checkLabel = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.PresidentNote")));
	checkLabel->set_alignment(0.0, 0.5);
	checkLabel->set_size_request(labelWidth, entryHeight);
	checkLabel->set_line_wrap(true);
	checkLabel->set_line_wrap_mode(Pango::WRAP_WORD);

    Pango::FontDescription fontDesc = checkLabel->get_style()->get_font();
    fontDesc.set_size(12*Pango::SCALE);
    checkLabel->modify_font(fontDesc);

    textView = manage(new Smartmatic::GUI::Widgets::SmartmaticTextView());
	textView->set_size_request(entryWidth, entryHeight);

	labelComment = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterWidget.WriteNote")));
	labelComment->set_size_request(labelWidth, entryHeight);
	labelComment->modify_font(fontDesc);
	labelComment->set_alignment(0.0, 0.0);

	if(removeCardLabel)
	{
		removeCardLabel->hide();
	}

	if(buttonAccept != NULL)
	{
		buttonBox->remove(*buttonAccept);
		delete buttonAccept;
	}

	buttonBox->pack_start(*backButton, false, false);
	buttonBox->pack_start(*acceptButton, false, false);

	idConfig = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getCloseNoteRegister();

	initialize();
	refresh();
}

CloseNoteInfoWidget::~CloseNoteInfoWidget()
{
	dispose();
}

bool CloseNoteInfoWidget::ShowEntryDataAndEmitSignal(int timer)
{
	acceptButton->show();
	backButton->show();
	return IDCardWidget::ShowEntryDataAndEmitSignal(timer);
}

void CloseNoteInfoWidget::backClicked()
{
	dispose();
	signalCancel.emit();
}

void CloseNoteInfoWidget::checkInfo()
{
	if(CheckCompleteData())
	{
		dispose();

		Smartmatic::SAES::EID::CitizenInfo citizen = getCitizenInfo();

		IDCardInfo idInfo;
		IDCardInfoWrapper::generateIdCardInfoWrapper(citizen, idInfo);

		widget->getCloseNote().setWriter_name(idInfo);
		widget->getCloseNote().setContent(textView->getText());
		widget->getCloseNote().setPresident_note(check->get_active());

		signalSave.emit();
	}
	else
	{
		acceptButton->hide();
		backButton->hide();
		ShowInCompleteData();
	}
}

bool CloseNoteInfoWidget::CheckCompleteData()
{
	bool result = true;

	IDProperties idp(true);

	if(!IDCardWidget::CheckCompleteData())
	{
		result = false;
	}
	else if (!ValidateWidget::validate(idp, textView))
	{
		result = false;
	}

	return result;
}

sigc::signal<void> CloseNoteInfoWidget::getSignalSaveInfoButton()
{
	return signalSave;
}

sigc::signal<void> CloseNoteInfoWidget::getSignalCancelInfoButton()
{
	return signalCancel;
}

void CloseNoteInfoWidget::setRegisterInfoWidget(CloseNoteRegisterInfoWidget * widget)
{
	initialize();
	this->widget = widget;
	refresh();
}

CloseNoteRegisterInfoWidget * CloseNoteInfoWidget::getRegisterInfoWidget()
{
	return this->widget;
}

void CloseNoteInfoWidget::ShowElements()
{
	IDCardWidget::ShowElements();

	dataTable->put(checkLabel, countElement, 0);
	dataTable->put(check, countElement++, 1);

	dataTable->put(labelComment, countElement, 0);
	dataTable->put(textView, countElement++, 1);

	IDProperties idp(true);
	ValidateWidget::setProperties(idp, textView);
}

void CloseNoteInfoWidget::refresh()
{
	textView->setText("");

	ShowElements();
	ClearNames();

	if (widget)
	{
		CloseNote & closeNote (widget->getCloseNote());
		IDCardInfo & info(closeNote.getWriter_name());

		CitizenInfo citizen;

		IDCardInfoWrapper::generateCitizenInfo(info, citizen);
		setCitizenInfo(citizen);

		check->set_active(closeNote.getPresident_note());
		textView->setText(closeNote.getContent());
	}
}
