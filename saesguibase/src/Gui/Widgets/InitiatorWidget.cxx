/**
 * @file InitiatorWidget.cxx
 * @brief Body class initiator widget
 * @date 24/10/2011
 * @author Yadickson Soto
 */

#include "InitiatorWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/functionality-initiator.h>
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
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Operation;

ISMTTLog* InitiatorWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.InitiatorWidget",GETTEXT_PACKAGE);

InitiatorWidget::InitiatorWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::StepWidget(), progress(progress)
{
	initialize();
	this->setWidget(progress);

	conn = MachineOperationManager::getInstance()->getMachineInitiator()->signal_detected.connect(sigc::mem_fun(*this, &InitiatorWidget::statusReport));
}

InitiatorWidget::~InitiatorWidget()
{
	dispose();
}

void InitiatorWidget::start()
{
	progress->setTitle(_("Smartmatic.SAES.GUI.Windows.InitializationWindow.Initializing"));
	progress->setText(" ");
	MachineOperationManager::getInstance()->getMachineInitiator()->start();
}

void InitiatorWidget::initialize()
{
	progress->setImage("ui/check-directory-structure.gif");
}

void InitiatorWidget::dispose()
{
	this->remove();

	conn.disconnect();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void InitiatorWidget::end()
{
	FunctionalityInitiator::Register();

	dispose();
	signalEnd.emit();
}

void InitiatorWidget::statusReport(InitializationStatus & status, bool finalized)
{
	this->status = status;

	if (!finalized)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &InitiatorWidget::showMessage), 50);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &InitiatorWidget::showEndMessage), 50);
	}
}

void InitiatorWidget::showMessage()
{
	progress->setImage(status.getImageFileName());
	progress->setText(status.getMessage());
}

void InitiatorWidget::showEndMessage()
{
	if (status.getSuccess())
	{
		progress->hideImage();
		progress->hideText();
		progress->hideFooter();
		progress->setTitle(status.getMessage());

		int timeout = MachineOperationManager::getInstance()->getMachineInitiator()->getSuccessMessageTime();
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &InitiatorWidget::end), timeout);
	}
	else
	{
		progress->setImage(status.getImageErrorFileName());
		progress->setTitle(status.getMessage());
		progress->setText(" ");
	}
}

std::string InitiatorWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.InitializationWindow.Title");
}
