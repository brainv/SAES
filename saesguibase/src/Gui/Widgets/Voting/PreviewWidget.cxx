/**
 * @file PreviewWidget.cxx
 * @brief Header class preview
 * @date 13/04/2012
 * @author Yadickson Soto
 */

#include "PreviewWidget.hxx"
#include "FactoryVotingWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Voting/set-language-functionality.h>
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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::Log;

ISMTTLog* PreviewWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PreviewWidget",GETTEXT_PACKAGE);

PreviewWidget::PreviewWidget()
{
	view = false;
	language = false;
	languageWidget = FactoryVotingWidget::createViewLanguageSelectionWidget();
	languageWidget->getSignalEnd().connect(sigc::mem_fun(*this,&PreviewWidget::viewVote));

	votePreviewWidget = FactoryVotingWidget::createVotePreviewWidget();
	votePreviewWidget->getBackClicked().connect(sigc::mem_fun(*this,&PreviewWidget::back));

	timeOutPreviewWidget = FactoryVotingWidget::createTimeOutPreviewWidget();
	timeOutPreviewWidget->getCloseClicked().connect(sigc::mem_fun(*this,&PreviewWidget::back));
	timeOutPreviewWidget->getKeepClicked().connect(sigc::mem_fun(*this,&PreviewWidget::viewVote));

	languageWidget->reload();

	setTitle(false);
	setShowBorder(true);

	setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName());
}

PreviewWidget::~PreviewWidget()
{
	remove();

	if (languageWidget)
	{
		delete languageWidget;
		languageWidget = NULL;
	}
	if (votePreviewWidget)
	{
		delete votePreviewWidget;
		votePreviewWidget = NULL;
	}
	if (timeOutPreviewWidget)
	{
		delete timeOutPreviewWidget;
		timeOutPreviewWidget = NULL;
	}
}

void PreviewWidget::preview(Vote & vote)
{
	view = true;
	this->vote = vote;
	selectionLanguage();
}

void PreviewWidget::error()
{
	view = false;
	setTimeout();
	setWidget(votePreviewWidget);
	votePreviewWidget->error();
}

void PreviewWidget::back()
{
	remove();
	language = false;
	connTimeout.disconnect();
	connTimeoutClose.disconnect();
	languageWidget->SetBackLanguage();
	signalEnd.emit();
}

void PreviewWidget::selectionLanguage()
{
	PreviewLanguageConfig config = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getPreviewLanguageConfig();

	switch (config)
	{
		case PreviewLanguageConfig::CONFIGURATION_LANGUAGE_VOTE:
			setLanguageVote();
			break;
		case PreviewLanguageConfig::CONFIGURATION_LANGUAGE_INSTALL:
			setLanguageInstall();
			break;
		case PreviewLanguageConfig::CONFIGURATION_LANGUAGE_ELECTOR:
			setLanguageElector();
			break;
	}
}

void PreviewWidget::viewVote()
{
	setTimeout();
	language = true;
	setWidget(votePreviewWidget);

	if (view)
	{
		votePreviewWidget->preview(vote);
	}
	else
	{
		votePreviewWidget->error();
	}

	show_all_children();
}

void PreviewWidget::setLanguageVote()
{
	logger->Debug("Changing language to " + vote.getLan_code());

	if(vote.getLan_code().size() == 5)
	{
		std::string newLanguage = vote.getLan_code().substr(0, 2);
		std::string newCountry = vote.getLan_code().substr(3, 5);
		Smartmatic::SAES::Voting::SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(newLanguage, newCountry);
	}

	viewVote();
	//Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &PreviewWidget::viewVote), 100);
}

void PreviewWidget::setLanguageInstall()
{
	logger->Debug("Use language install");
	viewVote();
	//Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &PreviewWidget::viewVote), 100);
}

void PreviewWidget::setLanguageElector()
{
	if(!language && languageWidget->ShowWidget())
	{
		languageWidget->initialize();
		logger->Debug("Use electoral language");
		setWidget(languageWidget);
	}
	else
	{
		viewVote();
		//Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &PreviewWidget::viewVote), 100);
	}
}

void PreviewWidget::setTimeout()
{
	connTimeout.disconnect();
	connTimeoutClose.disconnect();

	int timeout = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getTimeoutPreviewVote() * 1000;

	if(timeout > 0)
	{
		sigc::slot<bool> slot = sigc::bind(sigc::mem_fun(*this, &PreviewWidget::releaseTimeout), 0);
		connTimeout = Glib::signal_timeout().connect(slot, timeout);
	}
}

bool PreviewWidget::releaseTimeout(int time)
{
	setWidget(timeOutPreviewWidget);
	connTimeoutClose.disconnect();

	int timeout = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getTimeoutPreviewVoteClose() * 1000;

	if(timeout > 0)
	{
		sigc::slot<bool> slot = sigc::bind(sigc::mem_fun(*this, &PreviewWidget::releaseTimeoutClose), 0);
		connTimeoutClose = Glib::signal_timeout().connect(slot, timeout);
	}

	return false;
}

bool PreviewWidget::releaseTimeoutClose(int time)
{
	back();
	return false;
}
