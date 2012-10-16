/**
 * @file PoliceNoteRegisterInfoWidget.cxx
 * @brief Body close note register info widget
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNoteRegisterInfoWidget.hxx"
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
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* PoliceNoteRegisterInfoWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget",GETTEXT_PACKAGE);

PoliceNoteRegisterInfoWidget::PoliceNoteRegisterInfoWidget(PoliceNote & policeNote)
: RegisterInfoWidget()
{
	this->policeNote = policeNote;
	getSignalClick().connect(sigc::mem_fun(*this, &PoliceNoteRegisterInfoWidget::clicked));

	RegisterWidgetConfiguration config = SAESGUIConfigurationManager::Current()->getPoliceNoteRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();
	showHeader(config.getShowHeader());
	showCenter(config.getShowCenter());
	showBottom(config.getShowBottom());

	refresh();
}

PoliceNoteRegisterInfoWidget::~PoliceNoteRegisterInfoWidget()
{

}

void PoliceNoteRegisterInfoWidget::refresh()
{
	clearAll();

	std::string titleName = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.Title");

	std::string fnameText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.FirstName");
	fnameText.append(" :");
	std::string snameText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.LastName");
	snameText.append(" :");
	std::string actionOne = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.ActionOne");
	actionOne.append(" :");
	std::string actionTwo = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.ActionTwo");
	actionTwo.append(" :");
	std::string actionThree = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.ActionThree");
	actionThree.append(" :");

	std::string yes = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.Yes");
	std::string no = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteRegisterInfoWidget.No");

	addHeader("", titleName);
	addCenter(fnameText, policeNote.getPersonal_info().getFirstName());
	addCenter(snameText, policeNote.getPersonal_info().getSurname());
	addCenter(actionOne, policeNote.getAction_one() ? yes : no);
	addCenter(actionTwo, policeNote.getAction_two() ? yes : no);
	addCenter(actionThree, policeNote.getAction_three() ? yes : no);
}

PoliceNote & PoliceNoteRegisterInfoWidget::getPoliceNote()
{
	return policeNote;
}

void PoliceNoteRegisterInfoWidget::clicked(bool state)
{
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &PoliceNoteRegisterInfoWidget::emitClicked), 0);
}

void PoliceNoteRegisterInfoWidget::emitClicked()
{
	signalClicked.emit(this);
}

sigc::signal<void, PoliceNoteRegisterInfoWidget *> PoliceNoteRegisterInfoWidget::getSignalClicked()
{
	return signalClicked;
}
