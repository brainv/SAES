/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Gui/Widgets/id-card-widget.h>
#include <Operation/Card/CardController.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <eid/EIDManager.hxx>
#include "Environment/Configurations/resource-path-provider.h"
#include <System/IO/File.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include "AbstractFactoryWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
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

using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Operation;

ISMTTLog* IDCardWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.IDCardWidget",GETTEXT_PACKAGE);

IDCardWidget::IDCardWidget(string title1, string title2,bool showAccept, bool blockButton)
{
	this->title1 = title1;
	this->title2 = title2;
	this->showError = false;

	this->showAccept = showAccept;
	this->blockButton = blockButton;
	flagCardPresent = false;

	beidWidget = NULL;
	alignBeidExternal = NULL;
	alignDataGlobal = NULL;
	firstNameEntry = NULL;
	surNameEntry = NULL;
	genderEntry = NULL;
	nationalityEntry = NULL;
	natNumberEntry = NULL;
	firstNameLabel = NULL;
	surNameLabel = NULL;
	genderLabel = NULL;
	nationalityLabel = NULL;
	natNumberLabel = NULL;
	dataTable = NULL;
	alignLoad = NULL;
	beidLabel = NULL;
	incompleteAlign = NULL;
	buttonAccept = NULL;
	showBeid = true;
	visualizeMode = false;
	maintainInfo = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBeidCardShowRemoveMessage();
	showBeidEntry = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetShowBeidEntry();

	entryWidth = 200;
	entryHeight = -1;
	labelWidth = 150;

	firstNameEntry = new SmartmaticEntry(SmartmaticEntry::AllWithoutNumber);
	firstNameEntry->set_size_request(entryWidth, entryHeight);
	firstNameEntry->signal_inserted().connect(sigc::mem_fun(*this, &IDCardWidget::TextInserted));

	surNameEntry = new SmartmaticEntry(SmartmaticEntry::AllWithoutNumber);
	surNameEntry->set_size_request(entryWidth, entryHeight);
	surNameEntry->signal_inserted().connect(sigc::mem_fun(*this, &IDCardWidget::TextInserted));

	genderEntry = new GenderComboBox();
	genderEntry->set_size_request(entryWidth, entryHeight);

	nationalityEntry = new SmartmaticEntry(SmartmaticEntry::AllWithoutNumber);
	nationalityEntry->set_size_request(entryWidth, entryHeight);
	nationalityEntry->signal_inserted().connect(sigc::mem_fun(*this, &IDCardWidget::TextInserted));

	natNumberEntry = new SmartmaticEntry(SmartmaticEntry::AllWithoutAlphabetic);
	natNumberEntry->set_size_request(entryWidth, entryHeight);
	nationalityEntry->signal_inserted().connect(sigc::mem_fun(*this, &IDCardWidget::TextInserted));

	firstNameLabel = new Label();
	firstNameLabel->set_alignment(0.0, 0.5);
	firstNameLabel->set_size_request(labelWidth, entryHeight);

	Pango::FontDescription fontDesc = firstNameLabel->get_style()->get_font();
	fontDesc.set_size(12*Pango::SCALE);
	firstNameLabel->modify_font(fontDesc);

	surNameLabel = new Label();
	surNameLabel->set_alignment(0.0, 0.5);
	surNameLabel->set_size_request(labelWidth, entryHeight);
	surNameLabel->modify_font(fontDesc);

	genderLabel = new Label();
	genderLabel->set_alignment(0.0, 0.5);
	genderLabel->set_size_request(labelWidth, entryHeight);
	genderLabel->modify_font(fontDesc);

	nationalityLabel = new Label();
	nationalityLabel->set_alignment(0.0, 0.5);
	nationalityLabel->set_size_request(labelWidth, entryHeight);
	nationalityLabel->modify_font(fontDesc);

	natNumberLabel = new Label();
	natNumberLabel->set_alignment(0.0, 0.5);
	natNumberLabel->set_size_request(labelWidth, entryHeight);
	natNumberLabel->modify_font(fontDesc);

	removeCardLabel = new Label();
	removeCardLabel->set_alignment(0.5, 0.5);
	removeCardLabel->set_size_request(labelWidth + entryWidth, entryHeight);
	removeCardLabel->modify_font(fontDesc);
	removeCardLabel->set_no_show_all();
	removeCardLabel->hide();

	alignDataTable = manage(new Alignment());
	alignDataTable->set(0.5, 0.5, 0, 0);

	int buttonWidth = 150;
	int buttonHeight = 50;

	buttonAccept = manage(new SmartmaticButton());
	buttonAccept->signal_clicked().connect(sigc::mem_fun(this, &IDCardWidget::on_buttonAccept_clicked));
	buttonAccept->set_size_request(buttonWidth, buttonHeight);
	buttonAccept->set_sensitive(false);
	
	//buttonCancel.set_label(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.CancelButtonMessage"));
	//buttonCancel.set_size_request(buttonWidth, buttonHeight);

	buttonBox = manage(new HButtonBox());
	buttonBox->set_spacing(30);
	buttonBox->set_layout(BUTTONBOX_CENTER);
	//buttonBox.pack_start(buttonCancel, false, false);
	buttonBox->pack_start(*buttonAccept, false, false);

	labelMessage = manage(new Label());
		Pango::FontDescription fontTitle = labelMessage->get_style()->get_font();
		fontTitle.set_size(16*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelMessage->modify_font(fontTitle);

	entryVBox = manage(new VBox());
	entryVBox->set_spacing(30);
	entryVBox->pack_start(*labelMessage,false,false);
	entryVBox->pack_start(*alignDataTable, false, false);

	if(showAccept)
		entryVBox->pack_start(*buttonBox, false, false);

	//beid box
	beidLabel = new Label();

		fontTitle = beidLabel->get_style()->get_font();
		fontTitle.set_size(14*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	beidLabel->modify_font(fontTitle);

	beidButtonAccept = manage(new SmartmaticButton());
	beidButtonAccept->signal_clicked().connect(sigc::mem_fun(this, &IDCardWidget::on_beidButtonAccept_clicked));
	beidButtonAccept->set_size_request(buttonWidth, buttonHeight);
	beidButtonAccept->SetButtonType(SmartmaticButton::Ok);
	beidButtonAccept->WidgetsPosition(5,6,0);

	beidButtonCancel = manage(new SmartmaticButton());
	beidButtonCancel->signal_clicked().connect(sigc::mem_fun(this, &IDCardWidget::on_beidButtonCancel_clicked));
	beidButtonCancel->set_size_request(buttonWidth, buttonHeight);
	beidButtonCancel->SetButtonType(SmartmaticButton::Cancel);
	beidButtonCancel->WidgetsPosition(5,6,0);


	VButtonBox* beidButtonBox = manage(new VButtonBox());
	beidButtonBox->set_spacing(30);
	beidButtonBox->set_layout(BUTTONBOX_CENTER);
	beidButtonBox->pack_start(*beidButtonCancel, false, false);
	beidButtonBox->pack_start(*beidButtonAccept, false, false);

	beidFrame = new Frame();
	beidFrame->set_shadow_type(Gtk::SHADOW_NONE);
	
	Alignment* alignBeid = manage(new Alignment());
	alignBeid->set(0.5, 0.5, 0, 0);
	alignBeid->add(*beidFrame);

	beidVBox = manage(new VBox());
	beidVBox->set_spacing(10);
	beidVBox->pack_start(*beidLabel,false,false);
	beidVBox->pack_start(*alignBeid,false,false);

	Gtk::HBox* hboxBeidCard = manage(new HBox(false, 40));
	hboxBeidCard->pack_start(*beidVBox);
	hboxBeidCard->pack_start(*beidButtonBox,false,false);

	alignBeidExternal = new Alignment();
	alignBeidExternal->set(0.5, 0.5, 0, 0);
	alignBeidExternal->add(*hboxBeidCard);
	alignBeidExternal->show_all_children();
	alignBeidExternal->set_no_show_all();
	
	incompleteDataLabel = manage(new Label());
		fontTitle = incompleteDataLabel->get_style()->get_font();
		fontTitle.set_size(18*Pango::SCALE);
	incompleteDataLabel->modify_font(fontTitle);

	incompleteAlign = new Alignment();
	incompleteAlign->set(0.5, 0.5, 0.0, 0.0);
	incompleteAlign->add(*incompleteDataLabel);
	incompleteAlign->set_size_request(350, 200);
	incompleteAlign->show_all_children();
	incompleteAlign->set_no_show_all();


	string fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/id_card_widget_load.gif");
	
	if(!File::canOpenFile(fileImage))
		fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");

	loadImage = manage(new Gtk::Image());
	loadImage->set(Gdk::PixbufAnimation::create_from_file(fileImage));
	
	loadingLabel = manage(new Label());
		fontTitle = loadingLabel->get_style()->get_font();
		fontTitle.set_size(14*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	loadingLabel->modify_font(fontTitle);

	Gtk::VBox* loadBox = manage(new VBox(false, 5));
	loadBox->pack_start(*loadImage, false, false);
	loadBox->pack_start(*loadingLabel, false, false);

	alignLoad = new Alignment();
	alignLoad->set(0, 0.5, 0, 0);
	alignLoad->add(*loadBox);
	alignLoad->show_all_children();
	alignLoad->set_no_show_all();

	dataHbox = manage(new HBox(false, 20));
	dataHbox->pack_start(*entryVBox);
	dataHbox->pack_start(*alignLoad,false,false);
	dataHbox->show_all_children();
	
	alignDataGlobal = new Alignment();
	alignDataGlobal->set(0.5, 0.5, 0, 0);
	alignDataGlobal->add(*dataHbox);
	alignDataGlobal->show_all_children();
	alignDataGlobal->set_no_show_all();

	outsideBox = new HBox();
	outsideBox->pack_start(*alignDataGlobal);
	outsideBox->pack_start(*alignBeidExternal);
	outsideBox->pack_start(*incompleteAlign);
	//outsideBox->pack_start(*alignLoad);

	firstNameLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.FirstName"));
	surNameLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.SurName"));
	genderLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.Gender"));
	nationalityLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.Nationality"));
	natNumberLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.NationalityNumber"));
	removeCardLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.RemoveCard"));

	if(title1 == "")
	{
		this->title1 = N_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.Message.PleaseInsertCard");
	}
	if(title2 == "")
	{
		this->title2 = N_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.Message.AcceptCurrentBeid");
	}

	incompleteDataLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.IncompleteData"));
	loadingLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.LoadingData"));
	removeCardLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.RemoveCard"));

	buttonAccept->set_label(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.AcceptButtonMessage"));
	beidButtonAccept->set_label(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.AcceptButtonMessage"));
	beidButtonCancel->set_label(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.CancelButtonMessage"));

	beidErrorWidget = AbstractFactoryWidget::createBeidErrorWidget();
	beidErrorWidget->getSignalEnd().connect(sigc::mem_fun(*this, &IDCardWidget::on_beidButtonCancel_clicked));

	firstNameLabel->set_no_show_all();
	firstNameEntry->set_no_show_all();

	surNameLabel->set_no_show_all();
	surNameEntry->set_no_show_all();

	genderLabel->set_no_show_all();
	genderEntry->set_no_show_all();

	nationalityLabel->set_no_show_all();
	nationalityEntry->set_no_show_all();

	natNumberLabel->set_no_show_all();
	natNumberEntry->set_no_show_all();

	dataTable = new TableWidget();

	dataTable->getTable()->set_row_spacings(10);
	dataTable->getTable()->set_col_spacings(20);

	alignDataTable->remove();
	alignDataTable->add(*dataTable);

	idConfig = SAESGUIConfigurationManager::Current()->getPollWorkerIDConfiguration(WorkerMemberType::POLLWORKERS_ASSISTENT);
	ShowElements();

	refresh();

	setWidget(outsideBox);
	show();
}

void IDCardWidget::TextInserted()
{
	if(showAccept && buttonAccept->get_visible() && buttonAccept->get_realized() && !buttonAccept->get_sensitive())
		buttonAccept->set_sensitive(true);
}

void IDCardWidget::SetShowAcept(bool showAccept)
{
	this->showAccept = showAccept;
}

void IDCardWidget::SetNames(std::string firstName, std::string lastName)
{
	firstNameEntry->set_text(firstName);
	surNameEntry->set_text(lastName);
}

void IDCardWidget::GetNames(std::string& firstName, std::string& lastName)
{
	GetData();
	firstName = citizenInfo.getFirstName();
	lastName = citizenInfo.getSurname();
}

void IDCardWidget::ClearNames()
{
	citizenInfo.ClearData();
	firstNameEntry->setText("");
	surNameEntry->setText("");
}

void IDCardWidget::setIDConfig(IDConfig idConfig)
{
	this->idConfig = idConfig;
	ShowElements();
}

void IDCardWidget::ShowElements()
{
	dataTable->clear();

	countElement = 0;
	dataTable->resize(5,2);

	firstNameLabel->set_visible(idConfig.getName().present());
	firstNameEntry->set_visible(idConfig.getName().present());

	surNameLabel->set_visible(idConfig.getLastName().present());
	surNameEntry->set_visible(idConfig.getLastName().present());

	genderLabel->set_visible(idConfig.getGender().present());
	genderEntry->set_visible(idConfig.getGender().present());

	nationalityLabel->set_visible(idConfig.getNationality().present());
	nationalityEntry->set_visible(idConfig.getNationality().present());

	natNumberLabel->set_visible(idConfig.getNationalityNumber().present());
	natNumberEntry->set_visible(idConfig.getNationalityNumber().present());

	if (idConfig.getName().present())
	{
		dataTable->put(firstNameLabel, countElement, 0);
		dataTable->put(firstNameEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getName().get(), firstNameEntry);
	}

	if (idConfig.getLastName().present())
	{
		dataTable->put(surNameLabel, countElement, 0);
		dataTable->put(surNameEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getLastName().get(), surNameEntry);
	}

	if (idConfig.getGender().present())
	{
		dataTable->put(genderLabel, countElement, 0);
		dataTable->put(genderEntry, countElement++, 1);

		genderEntry->setValue(GenderComboBox::None);
	}

	if (idConfig.getNationality().present())
	{
		dataTable->put(nationalityLabel, countElement, 0);
		dataTable->put(nationalityEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getNationality().get(), nationalityEntry);
	}

	if (idConfig.getNationalityNumber().present())
	{
		dataTable->put(natNumberLabel, countElement, 0);
		dataTable->put(natNumberEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getNationalityNumber().get(), natNumberEntry);
	}

	dataTable->show_all_children();

	ShowEntryData();
}

void IDCardWidget::HideAcceptTitle()
{
	beidVBox->remove(*beidLabel);
}

void IDCardWidget::HideConfirmationBeid()
{
	showBeid = false;

	std::string fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/id_card_widget_load_small.gif");

	if(!File::canOpenFile(fileImage))
		fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");

	loadingLabel->set_line_wrap(true);
	loadingLabel->set_justify(JUSTIFY_CENTER);
	loadingLabel->set_size_request(160, -1);

	loadImage->set(Gdk::PixbufAnimation::create_from_file(fileImage));
}

void IDCardWidget::on_beidButtonAccept_clicked()
{
	logger->Debug("Setting Data.");
	SetData();
	logger->Debug("Show Entry Data.");
	ShowEntryData();

	bool cardIsPresent = EIDManager::isCardPresent();
	logger->Debug("Card is present: " + cardIsPresent);

	if(blockButton && cardIsPresent && showAccept && buttonAccept->get_visible() && buttonAccept->get_realized() && buttonAccept->get_sensitive())
	{
		logger->Debug("Button accept sensitive false.");
		buttonAccept->set_sensitive(false);
		logger->Debug("Button accept sensitive false done.");
	}

	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBeidCardShowRemoveMessage() &&
			cardIsPresent)
	{
		logger->Debug("Show remove card label.");
		removeCardLabel->show();
		logger->Debug("Show remove card label done.");
	}

	logger->Debug("on_beidButtonAccept_clicked OUT.");

}

void IDCardWidget::on_beidButtonCancel_clicked()
{
	showError = false;
	ShowElements();
	ClearData();
	ShowEntryData();
	alignLoad->hide();
	removeCardLabel->hide();

	if(showAccept && buttonAccept->get_visible() && buttonAccept->get_realized() && !buttonAccept->get_sensitive())
		buttonAccept->set_sensitive(true);
	//Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::init),100);
}

void IDCardWidget::on_buttonAccept_clicked()
{
	GetData();

	if(CheckCompleteData())
	{
		m_accept_clicked.emit();
	}
	else
	{
		ShowInCompleteData();
	}
}

void IDCardWidget::ShowInCompleteData()
{
	incompleteAlign->show();
	alignDataGlobal->hide();
	alignBeidExternal->hide();
	alignLoad->hide();
	show_all_children();

	incompleteConnection.disconnect();

	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			&IDCardWidget::ShowEntryDataAndEmitSignal), 0);

	incompleteConnection = Glib::signal_timeout().connect(my_slot,3000);
}

bool IDCardWidget::ShowEntryDataAndEmitSignal(int timer)
{
	m_signal_backIncomplete_emitted.emit();
	ShowEntryData();
	return false;
}

IDCardWidget::signal_void IDCardWidget::signal_backIncomplete_emitted()
{
	return m_signal_backIncomplete_emitted;
}

void IDCardWidget::ShowLoadingLabel()
{
	incompleteAlign->hide();
	alignDataGlobal->show();
	alignBeidExternal->hide();
	alignLoad->show();
	entryVBox->hide();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::CreateBeidWidget), 500);
}

void IDCardWidget::SetVisualizeMode(bool visualizeMode)
{
	firstNameEntry->set_sensitive(!visualizeMode);
	firstNameEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	surNameEntry->set_sensitive(!visualizeMode);
	surNameEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	genderEntry->set_sensitive(!visualizeMode);
	genderEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	nationalityEntry->set_sensitive(!visualizeMode);
	nationalityEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	natNumberEntry->set_sensitive(!visualizeMode);
	natNumberEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	this->visualizeMode = visualizeMode;
}

void IDCardWidget::GetData()
{
	citizenInfo.setFirstName(firstNameEntry->get_text());
	citizenInfo.setSurname(surNameEntry->get_text());

	if (genderEntry->is_visible())
	{
		citizenInfo.setGender(genderEntry->getValue());
	}

	if(nationalityEntry->get_text() != "")
	{
		citizenInfo.setNationality(nationalityEntry->get_text());
	}

	if(natNumberEntry->get_text() != "")
	{
		citizenInfo.setNationalNumber(natNumberEntry->get_text());
	}
}

bool IDCardWidget::CheckCompleteData()
{
	bool returnVariable = true;

	if (idConfig.getName().present() && !ValidateWidget::validate(idConfig.getName().get(), firstNameEntry))
	{
		returnVariable = false;
	}
	else if (idConfig.getLastName().present() && !ValidateWidget::validate(idConfig.getLastName().get(), surNameEntry))
	{
		returnVariable = false;
	}
	else if (idConfig.getGender().present() && idConfig.getGender().get().getMandatory() && genderEntry->getValue() == GenderComboBox::None)
	{
		returnVariable = false;
	}
	else if (idConfig.getNationality().present() && !ValidateWidget::validate(idConfig.getNationality().get(), nationalityEntry))
	{
		returnVariable = false;
	}
	else
	{
		switch (showBeidEntry)
		{
			case ShowBeidEntryTypeConfiguration::CONFIGURATION_SHOWWITHSECURITY:
			case ShowBeidEntryTypeConfiguration::CONFIGURATION_SHOW:
				if (idConfig.getNationalityNumber().present() && !ValidateWidget::validate(idConfig.getNationalityNumber().get(), natNumberEntry))
				{
					returnVariable = false;
				}
			break;
			default:
				break;
		}
	}

	return returnVariable;
}	

IDCardWidget::signal_void IDCardWidget::signal_accept_clicked()
{
	return m_accept_clicked;
}

IDCardWidget::signal_void IDCardWidget::signal_cardRemoved_detected()
{
	return signalCardRemoved_detected;
}

void IDCardWidget::initialize()
{
	static bool launchThread = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetLaunchThreadBeid();

	if(launchThread)
	{
		if(!Glib::thread_supported()) Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &IDCardWidget::init_Thread), false);
	}
	else
	{
		init_Thread();
	}

	connCardChange.disconnect();
	flagCardPresent = false;

	bool useCallback  = SAESCommonConfigurationManager::Current()->getBEIDConfiguration().getUseCallbackEvent();

	if (!useCallback)
	{
		int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getBEIDCardWidget();
		sigc::slot<bool> connectedSlot = sigc::bind(sigc::mem_fun(*this, &IDCardWidget::CardChange), 0);
		connCardChange = Glib::signal_timeout().connect(connectedSlot, timerRefresh);
	}

	ClearData();
	ShowEntryData();
}

void IDCardWidget::init_Thread()
{
	EIDManager::init(this);

	static bool launchThread = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetLaunchThreadBeid();
	if(launchThread)
	{
		sleep(2);
	}
}

Smartmatic::SAES::EID::CitizenInfo IDCardWidget::getCitizenInfo()
{
	GetData();
	return citizenInfo;
}

void IDCardWidget::setCitizenInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
{
	this->citizenInfo = citizenInfo;
	SetData();
}

void IDCardWidget::SetData()
{
	firstNameEntry->set_text(citizenInfo.getFirstName());
	surNameEntry->set_text(citizenInfo.getSurname());
	genderEntry->setValue(citizenInfo.getGender());
	nationalityEntry->set_text(citizenInfo.getNationality());
	switch (showBeidEntry) {
	case ShowBeidEntryTypeConfiguration::CONFIGURATION_SHOWWITHSECURITY:
		natNumberEntry->set_text(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.natNumberEntryMask"));
		break;
	case ShowBeidEntryTypeConfiguration::CONFIGURATION_NOSHOW:
		natNumberEntry->set_text("");
		break;
	case ShowBeidEntryTypeConfiguration::CONFIGURATION_SHOW:
		natNumberEntry->set_text(citizenInfo.getNationalNumber());
		break;
	}

}

void IDCardWidget::ClearData()
{
	firstNameEntry->set_text("");
	surNameEntry->set_text("");
	nationalityEntry->set_text("");
	natNumberEntry->set_text("");
}

void IDCardWidget::cardInserted()
{
	logger->Debug("Card inserted.");
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &IDCardWidget::CardDetected), 100);
}

void IDCardWidget::cardExtracted()
{
	logger->Debug("Card extracted.");
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &IDCardWidget::CardExtracted), 100);
}

bool IDCardWidget::CardChange(int time_num)
{
	bool present = EIDManager::isCardPresent();

	if (present && !flagCardPresent)
	{
		cardInserted();
		flagCardPresent = true;
	}
	else if (!present && flagCardPresent)
	{
		cardExtracted();
		flagCardPresent = false;
	}

	return true;
}

void IDCardWidget::CardDetected()
{
	if(!visualizeMode)
	{
		if(showBeid)
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::ShowLoadingLabel), 500);
		else
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::ShowSecondLoadingLabel), 500);
	}
}

void IDCardWidget::ShowSecondLoadingLabel()
{
	//alignLoad->set_padding(10,10,10,10);

	alignLoad->show();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::GetCitizenAndData), 1000);
}

void IDCardWidget::GetCitizenAndData()
{
	alignLoad->hide();

	bool citizenInfoResult = false;
	citizenInfo = EIDManager::getData(citizenInfoResult);

	if(citizenInfoResult)
	{
		LogCardInfo(citizenInfo);
		SetData();
		if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBeidCardShowRemoveMessage())
		{
			if (EIDManager::isCardPresent())
			{
				removeCardLabel->show();

				if(blockButton && showAccept && buttonAccept->get_visible() && buttonAccept->get_realized() && buttonAccept->get_sensitive())
					buttonAccept->set_sensitive(false);
			}
		}
	}
	else
	{
		on_beidButtonCancel_clicked();
	}
}

void IDCardWidget::CreateBeidWidget()
{
	bool citizenInfoResult = false;

	citizenInfo = EIDManager::getData(citizenInfoResult);

	if(citizenInfoResult)
	{
		LogCardInfo(citizenInfo);

		if(beidWidget)
		{
			beidFrame->remove();
			delete(beidWidget);
		}

		beidWidget = new BeidWidget(citizenInfo, EIDManager::getPicture(),
				Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBeidShowIdCard());
		beidWidget->show();

		ShowBeidWidget();
	}
	else
	{
		showBeidError();
	}
}

void IDCardWidget::ShowEntryData()
{
	alignDataGlobal->show();
	alignDataGlobal->show_all_children();
	incompleteAlign->hide();
	alignBeidExternal->hide();
	alignLoad->hide();

	setWidget(outsideBox);
}

void IDCardWidget::ShowBeidWidget()
{
	alignDataGlobal->hide();
	alignBeidExternal->show();

	beidFrame->remove();
	beidFrame->add(*beidWidget);
	setWidget(outsideBox);
}

void IDCardWidget::showBeidError()
{
	showError = true;
	beidErrorWidget->refresh();
	beidErrorWidget->start();
	setWidget(beidErrorWidget);
}

void IDCardWidget::LogCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
{
	/*std::string log_info;
	log_info.append(citizenInfo.getFirstName());
	log_info.append("  ");
	log_info.append(citizenInfo.getSurname());
	log_info.append("  ");
	log_info.append(citizenInfo.getGender());
	log_info.append("  ");
	log_info.append(citizenInfo.getDateOfBirth());
	log_info.append("  ");
	log_info.append(citizenInfo.getLocationOfBirth());
	log_info.append("  ");
	log_info.append(citizenInfo.getNationality());
	log_info.append("  ");
	log_info.append(citizenInfo.getNationalNumber());
	log_info.append("  ");
	log_info.append(citizenInfo.getSpecialOrganization());
	log_info.append("  ");
	log_info.append(citizenInfo.getMemberOfFamily());
	log_info.append("  ");
	log_info.append(citizenInfo.getAddressVersion());
	log_info.append("  ");
	log_info.append(citizenInfo.getStreet());
	log_info.append("  ");
	log_info.append(citizenInfo.getZipCode());
	log_info.append("  ");
	log_info.append(citizenInfo.getMunicipality());
	log_info.append("  ");
	log_info.append(citizenInfo.getCountry());
	log_info.append("  ");
	log_info.append(citizenInfo.getSpecialStatus());

	logger->Debug(log_info);*/
}

void IDCardWidget::MaintainInfo()
{
	maintainInfo = true;
}

void IDCardWidget::CardExtracted()
{
	if (showError)
	{
		return;
	}

	if(!maintainInfo && !visualizeMode)
	{
		/*EIDManager::getInstance()->Stop();
		connCardInserted.disconnect();
		connCardExtracted.disconnect();*/
		signalCardRemoved_detected.emit();
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &IDCardWidget::on_beidButtonCancel_clicked), 500);
	}

	if(showAccept && buttonAccept->get_visible() && buttonAccept->get_realized() && !buttonAccept->get_sensitive())
	{
		logger->Debug("Button accept sensitive true.");
		buttonAccept->set_sensitive(true);
		logger->Debug("Button accept sensitive true done.");
	}

	removeCardLabel->hide();

	setWidget(outsideBox);
}

Glib::ustring IDCardWidget::GetWidgetName()
{
	Glib::ustring widgetName("IDCardWidget");
	return widgetName;
}

void IDCardWidget::dispose()
{
	if(beidWidget)
	{
		beidFrame->remove();
		delete(beidWidget);
	}

	beidWidget = NULL;
	connCardChange.disconnect();
	incompleteConnection.disconnect();

	EIDManager::stop();
}

IDCardWidget::~IDCardWidget()
{
	dispose();

	if (outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
	if(firstNameEntry)
	{
		delete firstNameEntry;
		firstNameEntry = NULL;
	}
	if(surNameEntry) delete surNameEntry;
	if(firstNameLabel) delete firstNameLabel;
	if(surNameLabel) delete surNameLabel;
	if(dataTable) delete dataTable;
	if(removeCardLabel) delete removeCardLabel;
	if(beidWidget) delete beidWidget;
	if(beidFrame) delete beidFrame;
	if(incompleteAlign) delete incompleteAlign;
	if(alignBeidExternal) delete alignBeidExternal;
	if(alignDataGlobal) delete alignDataGlobal;
	if(nationalityEntry) delete nationalityEntry;
	if(genderLabel) delete genderLabel;
	if(genderEntry) delete genderEntry;
	if(natNumberLabel) delete natNumberLabel;
	if(nationalityLabel) delete nationalityLabel;
	if(natNumberEntry) delete natNumberEntry;
	if(alignLoad) delete alignLoad;
	if(beidLabel) delete beidLabel;
	if (beidErrorWidget)
	{
		delete beidErrorWidget;
		beidErrorWidget = NULL;
	}
}

void IDCardWidget::setTitles(std::string title1, std::string title2)
{
	this->title1 = title1;
	this->title2 = title2;
	refresh();
}

void IDCardWidget::refresh()
{
	labelMessage->set_label(_(title1.c_str()));
	beidLabel->set_label(_(title2.c_str()));
}

void IDCardWidget::setTitleConfiguration(LabelConfiguration & labelConf)
{
	LabelConfiguration::SetLabelConfiguration(labelMessage, labelConf);
	LabelConfiguration::SetLabelConfiguration(beidLabel, labelConf);
}

void IDCardWidget::setLabelConfiguration(LabelConfiguration & labelConf)
{
	LabelConfiguration::SetLabelConfiguration(firstNameLabel, labelConf);
	LabelConfiguration::SetLabelConfiguration(surNameLabel, labelConf);
	LabelConfiguration::SetLabelConfiguration(genderLabel, labelConf);
	LabelConfiguration::SetLabelConfiguration(nationalityLabel, labelConf);
	LabelConfiguration::SetLabelConfiguration(natNumberLabel, labelConf);
}
