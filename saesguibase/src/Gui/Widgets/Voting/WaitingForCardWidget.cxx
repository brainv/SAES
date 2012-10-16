/**
 * @file WaitingForCardWidget.cxx
 * @brief Body class waiting card widget
 * @date 11/04/2012
 * @author Yadickson Soto
 */

#include "WaitingForCardWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/FormatLabel.hxx>
#include <Devices/barcode-device.h>
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
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;

ISMTTLog* WaitingForCardWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.WaitingForCardWidget",GETTEXT_PACKAGE);

WaitingForCardWidget::WaitingForCardWidget(ProgressWidget * progress)
: StepWidget()
{
	this->mainFrame = NULL;
	this->mainVBox = NULL;
	this->infoFrame = NULL;
	this->buttonBox = NULL;
	this->buttonSim = NULL;
	this->buttonBack = NULL;
	this->progress = progress;
	this->alarmLabel = NULL;

	initialize();
	viewOnlyCard();

	setTitle(false);
	setShowBorder(true);
	setWidget(mainFrame);
	setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName());
}

WaitingForCardWidget::~WaitingForCardWidget()
{
	remove();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (infoFrame)
	{
		delete infoFrame;
		infoFrame = NULL;
	}
	if (buttonBox)
	{
		delete buttonBox;
		buttonBox = NULL;
	}
	if (buttonSim)
	{
		delete buttonSim;
		buttonSim = NULL;
	}
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if (alarmLabel)
	{
		delete alarmLabel;
		alarmLabel = NULL;
	}
}

void WaitingForCardWidget::initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/WaitingForCardWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ProgressWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("info-frame", infoFrame);
	builder->get_widget("hbuttonbox", buttonBox);
	builder->get_widget("alarm-label", alarmLabel);
	builder->get_widget_derived("buttonSim", buttonSim);
	builder->get_widget_derived("buttonBack", buttonBack);

	buttonSim->set_no_show_all();
	buttonBack->set_no_show_all();
	alarmLabel->set_no_show_all();

	hideButtons();

	progress->setTextConfig(SAESGUIConfigurationManager::Current()->GetVotingWindowEndMessagelabelConfig());

	Pango::FontDescription fontTitle = alarmLabel->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	alarmLabel->modify_font(fontTitle);
	alarmLabel->set_alignment(Gtk::ALIGN_CENTER);
	alarmLabel->set_justify(Gtk::JUSTIFY_CENTER);

	mainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	infoFrame->add(*progress);

	buttonSim->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
	buttonBack->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
}

void WaitingForCardWidget::viewOnlyCard()
{
	state = ONLY_CARD;
	update();
}

void WaitingForCardWidget::viewCardAndBarcode()
{
	state = CARD_AND_BARCODE;
	update();
}

void WaitingForCardWidget::viewErrorCardAndBarcode()
{
	state = ERRRO_CARD_AND_BARCODE;
	update();
}

void WaitingForCardWidget::viewReconfigureBarcode()
{
	state = RECONFIGURE_BARCODE;
	update();
}

void WaitingForCardWidget::viewCardValidate()
{
	state = CARD_VALIDATE;
	update();
}

void WaitingForCardWidget::viewErrorCardValidate()
{
	state = ERROR_CARD_VALIDATE;
	update();
}

void WaitingForCardWidget::update()
{
	buttonSim->SetLabel(_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.SimulateCard"));
	buttonBack->SetLabel(_("Smartmatic.SAES.GUI.Widgets.PartySelectionWidget.Back"));

	switch(state)
	{
		case ONLY_CARD:
			progress->setImage("ui/waitingForVoterCard.gif");
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCard")));
			alarmLabel->show();
			showButtons();
			break;

		case CARD_AND_BARCODE:
			progress->setImage("ui/waitingForVoterCardOrVoteScan.gif");
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardOrScanVote")));
			alarmLabel->show();
			showButtons();
			break;

		case ERRRO_CARD_AND_BARCODE:
			progress->setImage("ui/waitingForVoterCardScannerNotFound.gif");
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PleaseInsertCardAndBarcodeNotFound")));
			alarmLabel->show();
			showButtons();
			break;

		case RECONFIGURE_BARCODE:
			progress->setImage("ui/waitingForVoterReconfigureBarcode.gif");
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ReconfigureBarcode")));
			alarmLabel->hide();
			hideButtons();
			break;

		case CARD_VALIDATE:
			progress->setImage(ProgressWidget::PROGRESS);
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ValidatingCardInserted")));
			alarmLabel->hide();
			hideButtons();
			break;

		case ERROR_CARD_VALIDATE:
			progress->setImage("ui/IncorrectCardInsertion.gif");
			progress->setText(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardCorrectInsertionIndication")));
			alarmLabel->set_text(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardNotProperlyInserted")));
			showButtons();
			break;
	}
}

void WaitingForCardWidget::hideButtons()
{
	buttonSim->hide();
	buttonBack->hide();
}

void WaitingForCardWidget::showButtons()
{
	if(SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getShowSimulateButton())
	{
		buttonSim->set_sensitive(true);
		buttonSim->WidgetsPosition (5,0,0);
		buttonSim->set_size_request (300,80);
		buttonSim->show();
	}
	if(SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getShowBackButton())
	{
		buttonBack->set_sensitive(true);
		buttonBack->WidgetsPosition (5,0,0);
		buttonBack->set_size_request (300,80);
		buttonBack->show();
	}
}

void WaitingForCardWidget::refresh()
{
	if(SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getAllowVotePreview())
	{
		if(BarcodeDevice::Current()->sendPing())
		{
			viewCardAndBarcode();
		}
		else
		{
			viewErrorCardAndBarcode();
		}
	}
	else
	{
		viewOnlyCard();
	}

	alarmLabel->set_text(FormatLabel::format(MachineOperationManager::getInstance()->getAlarmController()->getMessage()));
}

Glib::SignalProxy0< void > WaitingForCardWidget::getSignalSim()
{
	return buttonSim->signal_clicked();
}

Glib::SignalProxy0< void > WaitingForCardWidget::getSignalBack()
{
	return buttonBack->signal_clicked();
}
