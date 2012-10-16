/**
 * @file OpenNoteWidget.cxx
 * @brief Body class open note widget
 * @date 10/05/2012
 * @author Yadickson Soto
 */

#include "OpenNoteWidget.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* OpenNoteWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.OpenNoteWidget",GETTEXT_PACKAGE);

OpenNoteWidget::OpenNoteWidget()
: WizardWidgetBase()
{
	message = NULL;
	align = NULL;
	pollOpenNoteWidget = NULL;

	std::string sOpenElection = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.OpenElectionButton");
	std::string sAddNote = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.AddNote");
	std::string sSaveNote = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.SaveNote");
	std::string sBack = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.BackButton");
	std::string sTitle = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.Title");
	std::string sNoteRegister = _("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.NoteRegister");

	OpenElectionFunctionalityConfiguration config = SAESGUIConfigurationManager::Current()->GetOpenElectionFunctionalityConfiguration();

	int buttonWidth = config.getButtonConfiguration().getButtonWidth();
	int buttonHeight = config.getButtonConfiguration().getButtonHeight();

	pollOpenNoteWidget = new PollWorkerNoteWidget(sTitle, sNoteRegister, sSaveNote, sBack, buttonWidth, buttonHeight, config.getShowTitle());
	pollOpenNoteWidget->signal_noteSaved_clicked().connect(sigc::mem_fun(this, &OpenNoteWidget::addNote));
	pollOpenNoteWidget->signal_titleEmpty().connect(sigc::mem_fun(this, &OpenNoteWidget::addedTitleEmpty));
	pollOpenNoteWidget->signal_contentEmpty().connect(sigc::mem_fun(this, &OpenNoteWidget::addedContentEmpty));

	align = new Gtk::Alignment();
	align->set_padding(10,10,80,80);
	align->add(*pollOpenNoteWidget);
	align->show_all_children();
	align->show();

	message = new Gtk::Label();
	message->show();

	Pango::FontDescription fontTitle = message->get_style()->get_font();
	fontTitle.set_size(18*Pango::SCALE);
	message->modify_font(fontTitle);

	showNote();
}

OpenNoteWidget::~OpenNoteWidget()
{
	remove();

	if (align)
	{
		delete align;
		align = NULL;
	}
	if (message)
	{
		delete message;
		message = NULL;
	}
	if (pollOpenNoteWidget)
	{
		delete pollOpenNoteWidget;
		pollOpenNoteWidget = NULL;
	}
}

void OpenNoteWidget::initialize()
{

}

void OpenNoteWidget::dispose()
{

}

Glib::ustring OpenNoteWidget::GetWidgetName()
{
	return "";
}

void OpenNoteWidget::showNote()
{
	setWidget(align);
}

void OpenNoteWidget::showMessage(std::string text)
{
	message->set_text(text);
	setWidget(message);
}

void OpenNoteWidget::addNote()
{
	try
	{
		pollOpenNoteWidget->Persist();
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.SuccessfullyNoteAdded"));
		m_done_signal.emit();
	}
	catch(...)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.OpenElectionFunctionality.Fail"));
		m_stop_signal.emit();
	}
}

void OpenNoteWidget::addedTitleEmpty()
{
	showMessage(_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.TitleEmpty"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &OpenNoteWidget::showNote), 3000);
}

void OpenNoteWidget::addedContentEmpty()
{
	showMessage(_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ContentEmpty"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &OpenNoteWidget::showNote), 3000);
}
