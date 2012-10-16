/**
 * @file PoliceNoteInfoWidget.cxx
 * @brief Body class police note info widget
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNoteInfoWidget.hxx"
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

PoliceNoteInfoWidget::PoliceNoteInfoWidget()
: IDCardWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.Title"),"",true)
{
	widget = NULL;

	HideAcceptTitle();
	SetShowAcept(false);

	ButtonConfiguration buttonConf = SAESGUIConfigurationManager::Current()->getPoliceNoteRegisterFunctionalityConfiguration().getAddCancelButtonConf();

	backButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.Back")));
	backButton->signal_clicked().connect(sigc::mem_fun(*this, &PoliceNoteInfoWidget::backClicked));
	backButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);
	backButton->ModifyFontSize(buttonConf.getFontSize());

	acceptButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.Accept")));
	acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &PoliceNoteInfoWidget::checkInfo));
	acceptButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	acceptButton->SetButtonType(SmartmaticButton::Ok);
	acceptButton->WidgetsPosition(5,6,0);
	acceptButton->ModifyFontSize(buttonConf.getFontSize());

	checkOne = manage(new Gtk::CheckButton());
	checkOne->set_size_request(entryWidth, entryHeight);

	actionOne = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.ActionOne")));
	actionOne->set_alignment(0.0, 0.5);
	actionOne->set_size_request(labelWidth, entryHeight);

    Pango::FontDescription fontDesc = actionOne->get_style()->get_font();
    fontDesc.set_size(12*Pango::SCALE);
    actionOne->modify_font(fontDesc);
    actionOne->set_line_wrap(true);
    actionOne->set_line_wrap_mode(Pango::WRAP_WORD);

	checkTwo = manage(new Gtk::CheckButton());
	checkTwo->set_size_request(entryWidth, entryHeight);

	actionTwo = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.ActionTwo")));
	actionTwo->set_alignment(0.0, 0.5);
	actionTwo->set_size_request(labelWidth, entryHeight);
    actionTwo->modify_font(fontDesc);
    actionTwo->set_line_wrap(true);
    actionTwo->set_line_wrap_mode(Pango::WRAP_WORD);

	checkThree = manage(new Gtk::CheckButton());
	checkThree->set_size_request(entryWidth, entryHeight);

	actionThree = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.ActionThree")));
	actionThree->set_alignment(0.0, 0.5);
	actionThree->set_size_request(labelWidth, entryHeight);
    actionThree->modify_font(fontDesc);
    actionThree->set_line_wrap(true);
    actionThree->set_line_wrap_mode(Pango::WRAP_WORD);

    textView = manage(new Smartmatic::GUI::Widgets::SmartmaticTextView());
	textView->set_size_request(entryWidth, entryHeight);

	labelComment = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterWidget.Comment")));
	labelComment->set_size_request(labelWidth, entryHeight);
	labelComment->modify_font(fontDesc);
	labelComment->set_alignment(0.0, 0.0);
	labelComment->set_line_wrap(true);
	labelComment->set_line_wrap_mode(Pango::WRAP_WORD);

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

	idConfig = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getPoliceNote();

	initialize();
	refresh();
}

PoliceNoteInfoWidget::~PoliceNoteInfoWidget()
{
	dispose();
}

void PoliceNoteInfoWidget::backClicked()
{
	dispose();
	signalCancel.emit();
}

void PoliceNoteInfoWidget::checkInfo()
{
	if(CheckCompleteData())
	{
		dispose();

		Smartmatic::SAES::EID::CitizenInfo citizen = getCitizenInfo();

		IDCardInfo idInfo;
		IDCardInfoWrapper::generateIdCardInfoWrapper(citizen, idInfo);

		widget->getPoliceNote().setPersonal_info(idInfo);
		widget->getPoliceNote().setAction_one(checkOne->get_active());
		widget->getPoliceNote().setAction_two(checkTwo->get_active());
		widget->getPoliceNote().setAction_three(checkThree->get_active());
		widget->getPoliceNote().setComment(textView->getText());

		signalSave.emit();
	}
	else
	{
		acceptButton->hide();
		backButton->hide();
		ShowInCompleteData();
	}
}

bool PoliceNoteInfoWidget::CheckCompleteData()
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

bool PoliceNoteInfoWidget::ShowEntryDataAndEmitSignal(int timer)
{
	acceptButton->show();
	backButton->show();
	return IDCardWidget::ShowEntryDataAndEmitSignal(timer);
}

sigc::signal<void> PoliceNoteInfoWidget::getSignalSaveInfoButton()
{
	return signalSave;
}

sigc::signal<void>  PoliceNoteInfoWidget::getSignalCancelInfoButton()
{
	return signalCancel;
}

void PoliceNoteInfoWidget::setRegisterInfoWidget(PoliceNoteRegisterInfoWidget * widget)
{
	initialize();
	this->widget = widget;
	refresh();
}

PoliceNoteRegisterInfoWidget * PoliceNoteInfoWidget::getRegisterInfoWidget()
{
	return this->widget;
}

void PoliceNoteInfoWidget::ShowElements()
{
	IDCardWidget::ShowElements();

	dataTable->put(actionOne, countElement, 0);
	dataTable->put(checkOne, countElement++, 1);

	dataTable->put(actionTwo, countElement, 0);
	dataTable->put(checkTwo, countElement++, 1);

	dataTable->put(actionThree, countElement, 0);
	dataTable->put(checkThree, countElement++, 1);

	dataTable->put(labelComment, countElement, 0);
	dataTable->put(textView, countElement++, 1);

	IDProperties idp(true);
	ValidateWidget::setProperties(idp, textView);
}

void PoliceNoteInfoWidget::refresh()
{
	ShowElements();
	ClearNames();

	textView->setText("");

	if (widget)
	{
		PoliceNote & policeNote (widget->getPoliceNote());
		IDCardInfo & info(policeNote.getPersonal_info());

		CitizenInfo citizen;

		IDCardInfoWrapper::generateCitizenInfo(info, citizen);
		setCitizenInfo(citizen);

		checkOne->set_active(policeNote.getAction_one());
		checkTwo->set_active(policeNote.getAction_two());
		checkThree->set_active(policeNote.getAction_three());

		textView->setText(policeNote.getComment());
	}
}
