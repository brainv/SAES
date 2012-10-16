/**
 * @file PoliceNoteWidget.cxx
 * @brief Header class police note
 * @data 25/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNoteWidget.hxx"
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

ISMTTLog* PoliceNoteWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PoliceNoteWidget",GETTEXT_PACKAGE);

PoliceNoteWidget::PoliceNoteWidget()
: StepWidget()
{
	policeNoteRegisterWidget = NULL;
	policeNoteInfoWidget = NULL;

	policeNoteRegisterWidget = new PoliceNoteRegisterWidget();
	policeNoteRegisterWidget->getSignalAddInfoButton().connect(sigc::mem_fun(*this, &PoliceNoteWidget::addInfo));
	policeNoteRegisterWidget->getSignalClicked().connect(sigc::mem_fun(*this, &PoliceNoteWidget::editInfo));

	policeNoteInfoWidget = new PoliceNoteInfoWidget();
	policeNoteInfoWidget->getSignalCancelInfoButton().connect(sigc::mem_fun(*this, &PoliceNoteWidget::cancelInfo));
	policeNoteInfoWidget->getSignalSaveInfoButton().connect(sigc::mem_fun(*this, &PoliceNoteWidget::saveInfo));

	load();
}

PoliceNoteWidget::~PoliceNoteWidget()
{
	remove();

	if (policeNoteRegisterWidget)
	{
		delete policeNoteRegisterWidget;
		policeNoteRegisterWidget = NULL;
	}
	if (policeNoteInfoWidget)
	{
		delete policeNoteInfoWidget;
		policeNoteInfoWidget = NULL;
	}
}

void PoliceNoteWidget::initialize()
{

}

void PoliceNoteWidget::dispose()
{

}

void PoliceNoteWidget::load()
{
	PoliceNotes notes = MachineOperationManager::getInstance()->getPoliceNoteWrapper()->getPoliceNotes();
	PoliceNotes::PoliceNoteIterator it;

	for (it = notes.getPoliceNote().begin();
			it != notes.getPoliceNote().end();
			it++)
	{
		PoliceNote policeNote = (*it);
		policeNoteRegisterWidget->addWidget(manage(new PoliceNoteRegisterInfoWidget(policeNote)));
	}

	policeNoteRegisterWidget->setCurrentPage(0);
	setWidget(policeNoteRegisterWidget);
}

void PoliceNoteWidget::addInfo()
{
	signalDisabled.emit();
	logger->Debug("addInfo");

	PoliceNote policeNote;
	createPoliceNote(policeNote);
	policeNoteInfoWidget->setRegisterInfoWidget(manage(new PoliceNoteRegisterInfoWidget(policeNote)));

	setWidget(policeNoteInfoWidget);
}

void PoliceNoteWidget::saveInfo()
{
	try
	{
		bool modify = MachineOperationManager::getInstance()->getPoliceNoteWrapper()->modifyPoliceNote(policeNoteInfoWidget->getRegisterInfoWidget()->getPoliceNote());
		MachineOperationManager::getInstance()->getPoliceNoteWrapper()->persistence();
		policeNoteInfoWidget->getRegisterInfoWidget()->refresh();

		if (!modify)
		{
			policeNoteRegisterWidget->addWidget(policeNoteInfoWidget->getRegisterInfoWidget());
			policeNoteInfoWidget->setRegisterInfoWidget(NULL);
		}
	}
	catch(...)
	{
		logger->Debug("ERROR save info");
	}

	setWidget(policeNoteRegisterWidget);
	signalEnabled.emit();
}

void PoliceNoteWidget::cancelInfo()
{
	logger->Debug("cancelInfo");
	policeNoteInfoWidget->setRegisterInfoWidget(NULL);
	setWidget(policeNoteRegisterWidget);
	signalEnabled.emit();
}

void PoliceNoteWidget::editInfo(PoliceNoteRegisterInfoWidget * widget)
{
	policeNoteInfoWidget->setRegisterInfoWidget(widget);
	setWidget(policeNoteInfoWidget);
	signalDisabled.emit();
}

void PoliceNoteWidget::createPoliceNote(Smartmatic::SAES::Voting::PBReports::PoliceNote & policeNote)
{
	IDCardInfo info("", "");
	policeNote.setCustom_code("");
	policeNote.setCreate_date("");
	policeNote.setAction_one(false);
	policeNote.setAction_two(false);
	policeNote.setAction_three(false);
	policeNote.setPersonal_info(info);
	policeNote.setComment("");
}

sigc::signal<void> PoliceNoteWidget::getSignalEnabled()
{
	return signalEnabled;
}

sigc::signal<void> PoliceNoteWidget::getSignalDisabled()
{
	return signalDisabled;
}

Glib::ustring PoliceNoteWidget::GetWidgetName()
{
	return "";
}
