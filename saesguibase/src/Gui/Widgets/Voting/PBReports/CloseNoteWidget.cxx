/**
 * @file CloseNoteWidget.cxx
 * @brief Header class close note
 * @data 24/05/2012
 * @author Yadickson Soto
 */

#include "CloseNoteWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::Log;

ISMTTLog* CloseNoteWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.CloseNoteWidget",GETTEXT_PACKAGE);

CloseNoteWidget::CloseNoteWidget()
: WizardWidgetBase()
{
	closeNoteRegisterWidget = NULL;
	closeNoteInfoWidget = NULL;

	minimunNotesToRegister = SAESGUIConfigurationManager::Current()->GetMinimunNotesToRegisterConfiguration();

	closeNoteRegisterWidget = new CloseNoteRegisterWidget();
	closeNoteRegisterWidget->getSignalAddInfoButton().connect(sigc::mem_fun(*this, &CloseNoteWidget::addInfo));
	closeNoteRegisterWidget->getSignalNextButton().connect(sigc::mem_fun(*this, &CloseNoteWidget::nextClicked));
	closeNoteRegisterWidget->getSignalClicked().connect(sigc::mem_fun(*this, &CloseNoteWidget::editInfo));

	closeNoteInfoWidget = new CloseNoteInfoWidget();
	closeNoteInfoWidget->getSignalCancelInfoButton().connect(sigc::mem_fun(*this, &CloseNoteWidget::cancelInfo));
	closeNoteInfoWidget->getSignalSaveInfoButton().connect(sigc::mem_fun(*this, &CloseNoteWidget::saveInfo));

	load();
}

CloseNoteWidget::~CloseNoteWidget()
{
	remove();

	if (closeNoteRegisterWidget)
	{
		delete closeNoteRegisterWidget;
		closeNoteRegisterWidget = NULL;
	}
	if (closeNoteInfoWidget)
	{
		delete closeNoteInfoWidget;
		closeNoteInfoWidget = NULL;
	}
}

void CloseNoteWidget::initialize()
{

}

void CloseNoteWidget::dispose()
{

}

void CloseNoteWidget::load()
{
	CloseNotes notes = MachineOperationManager::getInstance()->getClosingNotes()->getNotes();
	CloseNotes::CloseNoteIterator it;

	for (it = notes.getCloseNote().begin();
			it != notes.getCloseNote().end();
			it++)
	{
		CloseNote closeNote = (*it);
		closeNoteRegisterWidget->addWidget(manage(new CloseNoteRegisterInfoWidget(closeNote)));
	}

	closeNoteRegisterWidget->enableNextButton(MachineOperationManager::getInstance()->getClosingNotes()->getNotes().getCloseNote().size() >= minimunNotesToRegister);
	closeNoteRegisterWidget->setCurrentPage(0);
	setWidget(closeNoteRegisterWidget);
}

void CloseNoteWidget::addInfo()
{
	signalDisabled.emit();
	logger->Debug("addInfo");

	CloseNote closeNote;
	createCloseNote(closeNote);
	closeNoteInfoWidget->setRegisterInfoWidget(manage(new CloseNoteRegisterInfoWidget(closeNote)));

	setWidget(closeNoteInfoWidget);
}

void CloseNoteWidget::nextClicked()
{
	m_done_signal.emit();
}

void CloseNoteWidget::saveInfo()
{
	try
	{
		bool modify = MachineOperationManager::getInstance()->getClosingNotes()->modifyNote(closeNoteInfoWidget->getRegisterInfoWidget()->getCloseNote());
		MachineOperationManager::getInstance()->getClosingNotes()->Persist();
		closeNoteInfoWidget->getRegisterInfoWidget()->refresh();
		closeNoteRegisterWidget->enableNextButton(MachineOperationManager::getInstance()->getClosingNotes()->getNotes().getCloseNote().size() >= minimunNotesToRegister);

		if (!modify)
		{
			closeNoteRegisterWidget->addWidget(closeNoteInfoWidget->getRegisterInfoWidget());
			closeNoteInfoWidget->setRegisterInfoWidget(NULL);
		}
	}
	catch(...)
	{
		logger->Debug("ERROR save info");
	}

	setWidget(closeNoteRegisterWidget);
	signalEnabled.emit();
}

void CloseNoteWidget::cancelInfo()
{
	logger->Debug("cancelInfo");
	closeNoteInfoWidget->setRegisterInfoWidget(NULL);
	setWidget(closeNoteRegisterWidget);
	signalEnabled.emit();
}

void CloseNoteWidget::editInfo(CloseNoteRegisterInfoWidget * widget)
{
	closeNoteInfoWidget->setRegisterInfoWidget(widget);
	setWidget(closeNoteInfoWidget);
	signalDisabled.emit();
}

void CloseNoteWidget::createCloseNote(Smartmatic::SAES::Voting::PBReports::CloseNote & closeNote)
{
	IDCardInfo info("", "");
	closeNote.setCustom_code("");
	closeNote.setCreate_date("");
	closeNote.setContent("");
	closeNote.setPresident_note(false);
	closeNote.setWriter_name(info);
}

sigc::signal<void> CloseNoteWidget::getSignalEnabled()
{
	return signalEnabled;
}

sigc::signal<void> CloseNoteWidget::getSignalDisabled()
{
	return signalDisabled;
}

Glib::ustring CloseNoteWidget::GetWidgetName()
{
	return "";
}

void CloseNoteWidget::showNextButton()
{
	closeNoteRegisterWidget->showNextButton();
}
