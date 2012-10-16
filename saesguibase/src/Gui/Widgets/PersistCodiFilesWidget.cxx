/**
 * @file PersistCodiFilesWidget.cxx
 * @brief Body class persist codi files widget
 * @date 16/02/2012
 * @author Yadickson Soto
 */

#include "PersistCodiFilesWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>

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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* PersistCodiFilesWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PersistCodiFilesWidget", GETTEXT_PACKAGE);

PersistCodiFilesWidget::PersistCodiFilesWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
	this->progress->setImage("ui/persist-codi-files.gif");
	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.PersistCodiFilesWidget.PersistCodiFiles"));
	setWidget(progress);
}

PersistCodiFilesWidget::~PersistCodiFilesWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void PersistCodiFilesWidget::initialize()
{
	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &PersistCodiFilesWidget::start), false);
}

void PersistCodiFilesWidget::dispose()
{

}

Glib::ustring PersistCodiFilesWidget::GetWidgetName()
{
	return "";
}

void PersistCodiFilesWidget::start()
{
	bool validate = false;

	try
	{
		//MachineOperationManager::getInstance()->persistCodiFiles();
		validate = true;
	}
	catch(CryptoException & ex)
	{
		logger->Debug("PersistCodiFilesWidget CryptoException");
	}
	catch(SignedException & ex)
	{
		logger->Debug("PersistCodiFilesWidget SignedException");
	}
	catch(XmlException & ex)
	{
		logger->Debug("PersistCodiFilesWidget XmlException");
	}

	sleep(3);

	if(validate)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PersistCodiFilesWidget::end), 500);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &PersistCodiFilesWidget::updateLabel),
				N_("Smartmatic.SAES.GUI.Widgets.PersistCodiFilesWidget.ErrorMessage")), 500);
	}
}

void PersistCodiFilesWidget::end()
{
	m_done_signal.emit();
}

void PersistCodiFilesWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

bool PersistCodiFilesWidget::isEnabledButtonExitWizard()
{
	return false;
}
