/**
 * @file PersistAllResultWidget.cxx
 * @brief Body class persist all result files widget
 * @date 17/02/2012
 * @author Yadickson Soto
 */

#include "PersistAllResultWidget.hxx"
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

ISMTTLog* PersistAllResultWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PersistAllResultWidget", GETTEXT_PACKAGE);

PersistAllResultWidget::PersistAllResultWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::WizardWidgetBase(), progress(progress)
{
	this->progress->setImage("ui/persist-all-result-files.gif");
	this->progress->setText(N_("Smartmatic.SAES.GUI.Widgets.PersistAllResultWidget.PersistAllResult"));
	setWidget(progress);
}

PersistAllResultWidget::~PersistAllResultWidget()
{
	this->remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void PersistAllResultWidget::initialize()
{
	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &PersistAllResultWidget::start), false);
}

void PersistAllResultWidget::dispose()
{

}

Glib::ustring PersistAllResultWidget::GetWidgetName()
{
	return "";
}

void PersistAllResultWidget::start()
{
	bool validate = false;

	try
	{
		MachineOperationManager::getInstance()->persistAllResult();
		validate = true;
	}
	catch(CryptoException & ex)
	{
		logger->Debug("PersistAllResultWidget CryptoException");
	}
	catch(SignedException & ex)
	{
		logger->Debug("PersistAllResultWidget SignedException");
	}
	catch(XmlException & ex)
	{
		logger->Debug("PersistAllResultWidget XmlException");
	}
	catch(CodiException & ex)
	{
		logger->Debug("PersistAllResultWidget CodiException");
	}
	catch(...)
	{
		logger->Debug("PersistAllResultWidget AnyException");
	}

	sleep(3);

	if(validate)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PersistAllResultWidget::end), 500);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &PersistAllResultWidget::updateLabel),
				N_("Smartmatic.SAES.GUI.Widgets.PersistAllResultWidget.ErrorMessage")), 500);
	}
}

void PersistAllResultWidget::end()
{
	m_done_signal.emit();
}

void PersistAllResultWidget::updateLabel(std::string text)
{
	progress->hideTitle();
	progress->hideImage();
	progress->setText(text);
	m_stop_signal.emit();
}

bool PersistAllResultWidget::isEnabledButtonExitWizard()
{
	return false;
}
