/*
 * LanguageInstallWidget.cxx
 *
 *  Created on: 19/10/2011
 *      Author: soto
 */

#include "LanguageInstallWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Voting/set-language-functionality.h>

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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::GUI::Widgets;

ISMTTLog* LanguageInstallWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.LanguageInstallWidget",GETTEXT_PACKAGE);

LanguageInstallWidget::LanguageInstallWidget()
: StepWidget()
{
	this->languageWidget = NULL;

	this->initialize();

	setWidget(languageWidget);
}

LanguageInstallWidget::~LanguageInstallWidget()
{
	dispose();
}

void LanguageInstallWidget::initialize()
{
	dispose();

	languageWidget = new ChangeLanguageWidget();
	languageWidget->SetSaveFile(false);
	languageWidget->LanguageChanged().connect(sigc::mem_fun(*this, &LanguageInstallWidget::end));
}

void LanguageInstallWidget::dispose()
{
	this->remove();

	if (languageWidget)
	{
		delete languageWidget;
		languageWidget = NULL;
	}
}

void LanguageInstallWidget::start()
{
	this->remove();

	std::list<Election::Language> languages;
	bool firstTime = !VotingCenters::VotingCentersWrapper::getInstance()->isInstall();

	if (firstTime)
	{
		logger->Debug("load language election");
		languages = MachineOperationManager::getInstance()->getLanguagesElection();
	}
	else
	{
		logger->Debug("load language install");
		languages = MachineOperationManager::getInstance()->getLanguagesInstall();
	}

	if (languages.size() > 1) // If there is more than one language in the list display the language selection)
	{
		logger->Debug("Show selected language");
		languageWidget->init(MachineOperationManager::getInstance()->getSaesDirectories());
		languageWidget->initialize(languages, false);
		this->add(*languageWidget);
		this->show_all_children();
	}
	else if (languages.size() == 1)
	{
		logger->Debug("Set language");
		Election::ElectionInstalationLanguages::getInstance()->setInstallationLanguages(languages.front());
		SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(languages.front().getLanguage() , languages.front().getCountry());
		end();
	}
	else
	{
		logger->Debug("Language set enabled");
		end();
	}
}

void LanguageInstallWidget::end()
{
	signalEnd.emit();
}
