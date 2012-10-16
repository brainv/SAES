/**
 * @file CloseNoteRegisterInfoWidget.cxx
 * @brief Body close note register info widget
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#include "CloseNoteRegisterInfoWidget.hxx"
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

ISMTTLog* CloseNoteRegisterInfoWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteRegisterInfoWidget",GETTEXT_PACKAGE);

CloseNoteRegisterInfoWidget::CloseNoteRegisterInfoWidget(CloseNote & closeNote)
: RegisterInfoWidget()
{
	this->closeNote = closeNote;
	getSignalClick().connect(sigc::mem_fun(*this, &CloseNoteRegisterInfoWidget::clicked));

	RegisterWidgetConfiguration config = SAESGUIConfigurationManager::Current()->getCloseNoteRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();
	showHeader(config.getShowHeader());
	showCenter(config.getShowCenter());
	showBottom(config.getShowBottom());

	refresh();
}

CloseNoteRegisterInfoWidget::~CloseNoteRegisterInfoWidget()
{

}

void CloseNoteRegisterInfoWidget::refresh()
{
	clearAll();

	std::string titleName;
	std::string name;

	titleName = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteWidget.Name");
	titleName.append(" :");

	name = closeNote.getWriter_name().getFirstName();
	name.append(" ");
	name.append(closeNote.getWriter_name().getSurname());

	addHeader(titleName, name);
	putWrapMessage(closeNote.getContent());

	if(closeNote.getPresident_note())
	{
		addBottom(" ", _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteWidget.PresidentNote"));
	}
	else
	{
		addBottom(" ", _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteWidget.NormalNote"));
	}
}

CloseNote & CloseNoteRegisterInfoWidget::getCloseNote()
{
	return closeNote;
}

void CloseNoteRegisterInfoWidget::clicked(bool state)
{
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &CloseNoteRegisterInfoWidget::emitClicked), 0);
}

void CloseNoteRegisterInfoWidget::emitClicked()
{
	signalClicked.emit(this);
}

sigc::signal<void, CloseNoteRegisterInfoWidget *> CloseNoteRegisterInfoWidget::getSignalClicked()
{
	return signalClicked;
}
