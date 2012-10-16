/**
 * @file VotingForDisabledInfoWidget.cxx
 * @brief Body class voting for disabled info widget
 * @date 18/05/2012
 * @author Yadickson Soto
 */

#include "VotingForDisabledInfoWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Widgets/BoolStatWidget.hxx>
#include <System/Utils/StringUtils.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Operation/ValidateWidget.hxx>

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Operation;

ISMTTLog* VotingForDisabledInfoWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget",GETTEXT_PACKAGE);

VotingForDisabledInfoWidget::VotingForDisabledInfoWidget()
{
	mainEventBox = NULL;
	vBoxIDOne = NULL;
	vBoxIDTwo = NULL;
	eventBoxText = NULL;
	eventBoxButton = NULL;
	mainVBox = NULL;
	hboxID = NULL;
	labelCommennts = NULL;
	idOne = NULL;
	idTwo = NULL;
	valueOptionInfoDisabled = NULL;
	valueOptionInfoApproved = NULL;
	widget = NULL;
	textview = NULL;
	labelError = NULL;

	initialize();
	refresh();
	showInfo();
}

VotingForDisabledInfoWidget::~VotingForDisabledInfoWidget()
{
	dispose();
}

void VotingForDisabledInfoWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/VotingForDisabledInfoWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - VotingForDisabledQuestionWidget Initialize");
	}

	builder->get_widget("main-eventbox", mainEventBox);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("hbox-id", hboxID);
	builder->get_widget("vbox1", vBoxIDOne);
	builder->get_widget("vbox2", vBoxIDTwo);
	builder->get_widget("label-comments", labelCommennts);
	builder->get_widget("eventbox-text", eventBoxText);
	builder->get_widget_derived("scrolled", textview);
	builder->get_widget("eventbox-button", eventBoxButton);

	labelError = new Gtk::Label();

	idOne = new IDCardWidget(" ", " ", false, false);
	idTwo = new IDCardWidget(" ", " ", false, false);

	IDConfig idConfigVoter = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getDisabledVoter();
	IDConfig idConfigVoterHelper = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getDisabledVoterHelper();

	idOne->setIDConfig(idConfigVoter);
	idTwo->setIDConfig(idConfigVoterHelper);

	valueOptionInfoDisabled = new CounterStatWidget(new BoolStatWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.InfoDisability"), "", true));
	valueOptionInfoApproved = new CounterStatWidget(new BoolStatWidget(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.InfoApproved"), "", true));

	vBoxIDOne->pack_start(*idOne, true, true);
	vBoxIDOne->pack_start(*valueOptionInfoDisabled, false, false);

	vBoxIDTwo->pack_start(*idTwo, true, true);
	vBoxIDTwo->pack_start(*valueOptionInfoApproved, false, false);

	LabelConfiguration labelInfoConf = SAESGUIConfigurationManager::Current()->getVotingForDisabledInfoTextConfiguration();

	valueOptionInfoDisabled->SetLabelConfiguration(labelInfoConf);
	valueOptionInfoApproved->SetLabelConfiguration(labelInfoConf);
	LabelConfiguration::SetLabelConfiguration(labelCommennts, labelInfoConf);

	LabelConfiguration labelIDConf = SAESGUIConfigurationManager::Current()->getVotingForDisabledInfoIDConfiguration();

	idOne->setLabelConfiguration(labelIDConf);
	idTwo->setLabelConfiguration(labelIDConf);

	LabelConfiguration labelTitleConf = SAESGUIConfigurationManager::Current()->getVotingForDisabledInfoTitleConfiguration();

	idOne->setTitleConfiguration(labelTitleConf);
	idTwo->setTitleConfiguration(labelTitleConf);

	LabelConfiguration labelErrorConf = SAESGUIConfigurationManager::Current()->getVotingForDisabledInfoErrorConfiguration();
	LabelConfiguration::SetLabelConfiguration(labelError, labelErrorConf);

	ButtonConfiguration buttonConf = SAESGUIConfigurationManager::Current()->getVotingForDisabledFunctionalityConfiguration().getAddCancelButtonConf();

	backButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.Cancel")));
	backButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);
	backButton->ModifyFontSize(buttonConf.getFontSize());

	SmartmaticButton* addCommentButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.Accept")));
	addCommentButton->set_size_request(buttonConf.getButtonWidth(), buttonConf.getButtonHeight());
	addCommentButton->SetButtonType(SmartmaticButton::Ok);
	addCommentButton->WidgetsPosition(5,6,0);
	addCommentButton->ModifyFontSize(buttonConf.getFontSize());

	addCommentButton->signal_clicked().connect(sigc::mem_fun(*this, &VotingForDisabledInfoWidget::checkInfo) );

	Gtk::HButtonBox * btnBox = manage(new Gtk::HButtonBox());
	btnBox->set_spacing(100);
	btnBox->pack_start(*backButton, false, false);
	btnBox->pack_start(*addCommentButton, false, false);
	btnBox->set_layout(Gtk::BUTTONBOX_CENTER);

	eventBoxButton->add(*btnBox);

	timeout = SAESGUIConfigurationManager::Current()->getVotingForDisabledFunctionalityConfiguration().getTimeOutInfoError();
}

void VotingForDisabledInfoWidget::dispose()
{
	remove();

	if (mainEventBox)
	{
		delete mainEventBox;
		mainEventBox = NULL;
	}
	if (vBoxIDOne)
	{
		delete vBoxIDOne;
		vBoxIDOne = NULL;
	}
	if (vBoxIDTwo)
	{
		delete vBoxIDTwo;
		vBoxIDTwo = NULL;
	}
	if (eventBoxText)
	{
		delete eventBoxText;
		eventBoxText = NULL;
	}
	if (eventBoxButton)
	{
		delete eventBoxButton;
		eventBoxButton = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (hboxID)
	{
		delete hboxID;
		hboxID = NULL;
	}
	if (labelCommennts)
	{
		delete labelCommennts;
		labelCommennts = NULL;
	}
	if (textview)
	{
		delete textview;
		textview = NULL;
	}
	if (idOne)
	{
		delete idOne;
		idOne = NULL;
	}
	if (idTwo)
	{
		delete idTwo;
		idTwo = NULL;
	}
	if (valueOptionInfoDisabled)
	{
		delete valueOptionInfoDisabled;
		valueOptionInfoDisabled = NULL;
	}
	if (valueOptionInfoApproved)
	{
		delete valueOptionInfoApproved;
		valueOptionInfoApproved = NULL;
	}
	if (labelError)
	{
		delete labelError;
		labelError = NULL;
	}
}

void VotingForDisabledInfoWidget::refresh()
{
	labelCommennts->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.Comments"));
	textview->setText("");
	labelError->set_label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledInfoWidget.IncompleteData"));

	idOne->ShowElements();
	idTwo->ShowElements();

	idOne->ClearNames();
	idTwo->ClearNames();

	IDProperties idp = SAESGUIConfigurationManager::Current()->getVotingForDisabledFunctionalityConfiguration().getCommentConfig();
	ValidateWidget::setProperties(idp, textview);

	valueOptionInfoDisabled->SetValue(BoolStatWidget::None);
	valueOptionInfoApproved->SetValue(BoolStatWidget::None);

	if (widget)
	{
		idOne->setTitles(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.InfoOfVoter"), " ");

		VotingDisabled & votingDisabled (widget->getVotingDisabled());

		switch (votingDisabled.getType())
		{
			case  VotingDisabledType::VOTING_DISABLED_ASSISTED:
				idTwo->setTitles(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.InfoOfAssistant"), " ");
				break;

			case  VotingDisabledType::VOTING_DISABLED_ACCOMPANIED:
				idTwo->setTitles(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.VotingForDisabledIDInfoWidget.InfoOfAccompanist"), " ");
				break;
		}

		IDCardInfo & idVoter(votingDisabled.getVoter());
		IDCardInfo & idHelper(votingDisabled.getHelper());

		CitizenInfo citizen;

		IDCardInfoWrapper::generateCitizenInfo(idVoter, citizen);
		idOne->setCitizenInfo(citizen);

		IDCardInfoWrapper::generateCitizenInfo(idHelper, citizen);
		idTwo->setCitizenInfo(citizen);

		valueOptionInfoDisabled->SetValue(votingDisabled.getDisabled());
		valueOptionInfoApproved->SetValue(votingDisabled.getApproved());

		textview->setText(votingDisabled.getDescription());
	}
}

void VotingForDisabledInfoWidget::checkInfo()
{
	if (widget && CheckCompleteData())
	{
		widget->getVotingDisabled().setDisabled(valueOptionInfoDisabled->GetStatValue());
		widget->getVotingDisabled().setApproved(valueOptionInfoApproved->GetStatValue());
		widget->getVotingDisabled().setDescription(textview->getText());

		IDCardInfo & idVoter(widget->getVotingDisabled().getVoter());
		IDCardInfo & idHelper(widget->getVotingDisabled().getHelper());

		CitizenInfo citizen;

		citizen = idOne->getCitizenInfo();
		IDCardInfoWrapper::generateIdCardInfoWrapper(citizen, idVoter);

		citizen = idTwo->getCitizenInfo();
		IDCardInfoWrapper::generateIdCardInfoWrapper(citizen, idHelper);

		signalSave.emit();
	}
	else
	{
		showError();
	}
}

bool VotingForDisabledInfoWidget::CheckCompleteData()
{
	bool result = true;

	if(!idOne->CheckCompleteData())
	{
		result = false;
	}
	else if (!valueOptionInfoDisabled->validate())
	{
		result = false;
	}
	else if(!idTwo->CheckCompleteData())
	{
		result = false;
	}
	else if (!valueOptionInfoApproved->validate())
	{
		result = false;
	}
	else if (!textview->validate())
	{
		result = false;
	}

	return result;
}

void VotingForDisabledInfoWidget::showInfo()
{
	remove();
	add(*mainEventBox);
	show_all_children();
}

void VotingForDisabledInfoWidget::showError()
{
	remove();
	add(*labelError);
	show_all_children();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingForDisabledInfoWidget::showInfo), timeout);
}

sigc::signal<void> VotingForDisabledInfoWidget::getSignalSaveInfoButton()
{
	return signalSave;
}

Glib::SignalProxy0< void > VotingForDisabledInfoWidget::getSignalCancelInfoButton()
{
	return backButton->signal_clicked();
}

void VotingForDisabledInfoWidget::setRegisterInfoWidget(VotingForDisabledRegisterInfoWidget * widget)
{
	this->widget = widget;
	refresh();
}

VotingForDisabledRegisterInfoWidget * VotingForDisabledInfoWidget::getRegisterInfoWidget()
{
	return this->widget;
}
