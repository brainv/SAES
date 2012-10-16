/**
 * @file VotePreviewWidget.cxx
 * @brief Body class vote preview widget
 * @date 05/10/2011
 * @author Yadickson Soto
 */

#include "VotePreviewWidget.hxx"
#include <gtkmm/enums.h>
#include <Widgets/smartmatic-label.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Operation/FormatLabel.hxx>
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Voting::Vote;

ISMTTLog* VotePreviewWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.VotePreviewWidget",GETTEXT_PACKAGE);

VotePreviewWidget::VotePreviewWidget()
: StepWidget()
{
	this->vboxMagnify = NULL;
	this->scrolledMagnify = NULL;
	this->viewMagnify = NULL;
	this->buttonBack = NULL;

	this->printWidgetMagnify = NULL;
	this->partyViewerWidget = NULL;
	this->docMagnify = NULL;

	Glib::RefPtr<Gtk::Builder> builder;

	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/preview-in-waiting-widget.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - Problem get preview");
	}

	builder->get_widget("labelMessage", labelMessage);
	builder->get_widget("vboxMagnify", vboxMagnify);
	builder->get_widget("scrolledwindowMagnify", scrolledMagnify);
	builder->get_widget("viewportMagnify", viewMagnify);
	builder->get_widget_derived("buttonBack", buttonBack);

	buttonBack->WidgetsPosition (5,0,0);
	buttonBack->SetSound(SAESGUIConfigurationManager::Current()->getDiagnosisSound());

	Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConf = SAESGUIConfigurationManager::Current()->GetPreviewVoteLabelConfiguration();
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelMessage, labelTitleConf);

	ButtonConfiguration conf = SAESGUIConfigurationManager::Current()->getPreviewVoteButtonConfiguration();
	buttonBack->set_size_request (conf.getButtonWidth(), conf.getButtonHeight());
	buttonBack->ModifyFontSize(conf.getFontSize());

	viewMagnify->set_visible(true);
	scrolledMagnify->set_visible(true);
	labelMessage->set_visible(true);
	vboxMagnify->set_visible(true);

	setWidget(vboxMagnify);
}

void VotePreviewWidget::preview(Vote & vote)
{
	logger->Debug("Preview vote : " + vote.getCode());

	clear();

	if(!SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getUsePrintPreview())
	{
		bool tableVertical = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getUseVerticalTableInPreview();
		partyViewerWidget = new Smartmatic::SAES::GUI::Widgets::PartyContestViewerWidget(vote, tableVertical);
		partyViewerWidget->show();

		viewMagnify->add(*partyViewerWidget);
		viewMagnify->show_all_children ();
		viewMagnify->show();
	}
	else
	{
		bool showBarcode = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getShowBarcodeInPreview();

		docMagnify = new VotePrintDocument(MachineOperationManager::getInstance()->getElectoralConfiguration(),vote,true, showBarcode, true);

		printWidgetMagnify = new PrintPreviewWidget(docMagnify);
		printWidgetMagnify->show();

		viewMagnify->remove();
		viewMagnify->add(*printWidgetMagnify);
		viewMagnify->show_all_children ();
		viewMagnify->show();

		Gtk::Adjustment* adj = scrolledMagnify->get_vadjustment ();
		adj->set_value(0.0);
	}

	scrolledMagnify->show_all_children();

	buttonBack->SetLabel(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreview")));

	switch(vote.getMode())
	{
		case VoteMode::VOTE_D:
			labelMessage->set_label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsDemo")));
			logger->Debug("Vote is demo");
			break;
		case VoteMode::VOTE_O:
			labelMessage->set_label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsOfficial")));
			logger->Debug("Vote is official");
			break;
		case VoteMode::VOTE_R:
			labelMessage->set_label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsRecovery")));
			logger->Debug("Vote is recovery");
			break;
		case VoteMode::VOTE_S:
			labelMessage->set_label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.VoteMarkedAsSimulated")));
			logger->Debug("Vote is simulated");
			break;
	}
}

void VotePreviewWidget::error()
{
	labelMessage->set_label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Functionality.WaitingCardWidget.BarcodeErrorTryAgain")));
	buttonBack->SetLabel(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ButtonBackPreview")));
}

void VotePreviewWidget::clear()
{
	viewMagnify->remove();

	if (docMagnify)
	{
		delete docMagnify;
		docMagnify = NULL;
	}
	if (partyViewerWidget)
	{
		delete partyViewerWidget;
		partyViewerWidget = NULL;
	}
	if (printWidgetMagnify)
	{
		delete printWidgetMagnify;
		printWidgetMagnify = NULL;
	}
}

Glib::SignalProxy0< void > VotePreviewWidget::getBackClicked()
{
	return buttonBack->signal_clicked();
}

VotePreviewWidget::~VotePreviewWidget()
{
	remove();

	if(labelMessage)
	{
		delete labelMessage;
		labelMessage = NULL;
	}
	if(vboxMagnify)
	{
		delete vboxMagnify;
		vboxMagnify = NULL;
	}
	if(scrolledMagnify)
	{
		delete scrolledMagnify;
		scrolledMagnify = NULL;
	}
	if(viewMagnify)
	{
		delete viewMagnify;
		viewMagnify = NULL;
	}
	if(buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if(partyViewerWidget)
	{
		delete partyViewerWidget;
		partyViewerWidget = NULL;
	}
	if(printWidgetMagnify)
	{
		delete printWidgetMagnify;
		printWidgetMagnify = NULL;
	}
	if(docMagnify)
	{
		delete docMagnify;
		docMagnify = NULL;
	}
}
