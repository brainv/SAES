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
#include <sstream>
#include "Functionalities/card-generator-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <Operation/Card/CardController.hxx>

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* CardGeneratorFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality",GETTEXT_PACKAGE);

CardGeneratorFunctionality* CardGeneratorFunctionality::current_instance = NULL;

CardGeneratorFunctionality* CardGeneratorFunctionality::Current()
{
	if (!current_instance)
		current_instance = new CardGeneratorFunctionality();

	return current_instance;
}

CardGeneratorFunctionality::CardGeneratorFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	framePrincipal = NULL;
	frame1 = NULL;
	frame4 = NULL;
	frame5 = NULL;
	eventboxCardActivator = NULL;
	cardActivatorMessageEventBox = NULL;
	cardActivatorValuesEventBox = NULL;
	hbox1 = NULL;
	vboxBack = NULL;
	vbox3 = NULL;
	imageCard = NULL;
	alignmentBack = NULL;
	vbuttonbox1 = NULL;
	checkbuttonIsAudio = NULL;
	labelBack = NULL;
	labelResult = NULL;
	buttonBack = NULL;
	buttonActivate = NULL;
	counters = NULL;
	comboSelections = NULL;
	comboWidget = NULL;
	eventWidget = NULL;
}

void CardGeneratorFunctionality::deleteElement()
{
	if(framePrincipal)
	{
		delete framePrincipal;
		framePrincipal = NULL;
	}
	if(frame1)
	{
		delete frame1;
		frame1 = NULL;
	}
	if(frame4)
	{
		delete frame4;
		frame4 = NULL;
	}
	if(frame5)
	{
		delete frame5;
		frame5 = NULL;
	}
	if(eventboxCardActivator)
	{
		delete eventboxCardActivator;
		eventboxCardActivator = NULL;
	}
	if(cardActivatorMessageEventBox)
	{
		delete cardActivatorMessageEventBox;
		cardActivatorMessageEventBox = NULL;
	}
	if(cardActivatorValuesEventBox)
	{
		delete cardActivatorValuesEventBox;
		cardActivatorValuesEventBox = NULL;
	}
	if(hbox1)
	{
		delete hbox1;
		hbox1 = NULL;
	}
	if(vboxBack)
	{
		delete vboxBack;
		vboxBack = NULL;
	}
	if(vbox3)
	{
		delete vbox3;
		vbox3 = NULL;
	}
	if(imageCard)
	{
		delete imageCard;
		imageCard = NULL;
	}
	if(alignmentBack)
	{
		delete alignmentBack;
		alignmentBack = NULL;
	}
	if(vbuttonbox1)
	{
		delete vbuttonbox1;
		vbuttonbox1 = NULL;
	}
	if(checkbuttonIsAudio)
	{
		delete checkbuttonIsAudio;
		checkbuttonIsAudio = NULL;
	}
	if (labelBack)
	{
		delete labelBack;
		labelBack = NULL;
	}
	if(labelResult)
	{
		delete labelResult;
		labelResult = NULL;
	}
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if(buttonActivate)
	{
		delete buttonActivate;
		buttonActivate = NULL;
	}
	if(counters)
	{
		delete counters;
		counters = NULL;
	}
	if(comboSelections)
	{
		delete comboSelections;
		comboSelections = NULL;
	}
	if (comboWidget)
	{
		delete comboWidget;
		comboWidget = NULL;
	}
	if (eventWidget)
	{
		delete eventWidget;
		eventWidget = NULL;
	}

	cleanAttributes();
}

CardGeneratorFunctionality::~CardGeneratorFunctionality()
{
	deleteElement();
}

void CardGeneratorFunctionality::Initialize()
{
	SetSensitivityOfButtons(false);

	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("SelectionWindows")==0)
	{
		GoToSelectionWindow();
	}

	CardController::getInstance()->initialize();
	wasPresent = false;

	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getCardGeneratorFunctionality();

	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &CardGeneratorFunctionality::Refresh), 0);
	conn = Glib::signal_timeout().connect(my_slot,timerRefresh);

	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.InsertCardToActivate"));

	framePrincipal->remove();
	framePrincipal->add(*hbox1);

	enableExitButton();
};

void CardGeneratorFunctionality::GoToSelectionWindow()
{
	cleanAttributes();

	for(list<Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
	{
		vector<ChooseDialogButtonInfo*> choices;

		for ( Custom_attribute_definition::ValueIterator c ((*l).getValue().begin());  c != (*l).getValue().end(); ++c)
		{
			ChooseDialogButtonInfo* info = new ChooseDialogButtonInfo((*c), "",(*c),(*c));
			choices.push_back (info);
		}

		ChooseDialogInfo *infoDiag = NULL;
		infoDiag = new ChooseDialogInfo(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CustomAttributeSelection"),"",l->getName_key(), choices,false);

		ChooseOptionWindow optionWindow(infoDiag, "");
		optionWindow.signal_detected.connect(sigc::mem_fun(*this,&CardGeneratorFunctionality::onOptionButton));
		optionWindow.ShowDialog();

		Custom_attribute* attribute = new Custom_attribute();
		attribute->setCode((*l).getCode());
		attribute->setValue(temporalValue);
		attributes.push_back(attribute);

		for(unsigned int i=0;i < choices.size();i++)
		{
			delete(choices[i]);
		}
		delete(infoDiag);
	}
}

void CardGeneratorFunctionality::onOptionButton(ChooseDialogButtonInfo* info)
{
	temporalValue.clear();
	temporalValue.append(info->getName());
}

std::string CardGeneratorFunctionality::getCodeByName(std::string optionName)
{
	for(list<Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
	{
		if((*l).getName_key().compare(optionName)==0)
	   {
		   return (*l).getCode();
	   }
	}

	return "";
}

std::string CardGeneratorFunctionality::getNameByCode(std::string optionCode)
{
	for(list<Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
	{
		if((*l).getCode().compare(optionCode)==0)
	   {
		   return (*l).getName_key();
	   }
	}

	return "";
}

bool CardGeneratorFunctionality::Refresh(int time_num)
{
	bool present = CardController::getInstance()->isCardPresent();

	if(present && !wasPresent)
	{
		if(SAESGUIConfigurationManager::Current()->getActivatedAfterInsertingCard())
		{
			wasPresent = true;
			on_buttonOk_clicked();
		}
		else
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
			SetSensitivityOfButtons(true);
			wasPresent = true;
		}
	}
	else if (!present && wasPresent)
	{
		SetSensitivityOfButtons(false);
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.InsertCardToActivate"));

		imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif"));

		frame4->remove();
		frame4->add(*vbuttonbox1);
		wasPresent = false;
	}

	return true;
}

void CardGeneratorFunctionality::cleanAttributes()
{
	std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute*>::iterator it;

	for(it = attributes.begin();
	    it != attributes.end();
	    it++)
	{
		delete(*it);
	}

	attributes.clear();
}

void CardGeneratorFunctionality::on_buttonBack_clicked()
{
	GoToSelectionWindow ();
}

void CardGeneratorFunctionality::on_buttonGenerate_clicked()
{
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.AreYouCompletelySureYouWantToActivate"));

	if(SAESGUIConfigurationManager::Current()->getShowConfirmationButtons())
	{
		frame4->remove();
		frame4->add(buttonBox);
		frame4->show_all_children ();
	}
	else
	{
		on_buttonOk_clicked();
	}
}
	
void CardGeneratorFunctionality::SetSensitivityOfButtons(bool sensitive)
{
	buttonActivate->set_sensitive(sensitive);
}

void CardGeneratorFunctionality::on_buttonOk_clicked()
{

	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.StatingActivateCard"));

	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0
	   || Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
	{
		std::vector<ComboInfo> listOfOptions = comboSelections->getOptionsSelected();
		for(unsigned int k=0;k<listOfOptions.size();k++)
		{
			Custom_attribute* attribute = new Custom_attribute();
			attribute->setCode(getCodeByName(listOfOptions[k].getName()));
			attribute->setValue(listOfOptions[k].getValue());
			attributes.push_back(attribute);
		}
	}

	try
	{

		std::string compressed;
		Card_data cardData;
		CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes,cardData, true, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD,checkbuttonIsAudio->get_active());

		if (!CardController::getInstance()->writeCardData(cardData))
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
			SetSensitivityOfButtons(false);
		}
		else
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardWasActivated"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardWasActivatedSuccessfully"));
			SetSensitivityOfButtons(false);
			counters->RefreshStats(cardData);
			imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card.gif"));
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
		SetSensitivityOfButtons(false);
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
		SetSensitivityOfButtons(false);
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
		SetSensitivityOfButtons(false);
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
		SetSensitivityOfButtons(false);
	}
	catch(...)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ErrorActivationCard"));
		SetSensitivityOfButtons(false);
	}

	cleanAttributes();

	if(SAESGUIConfigurationManager::Current()->getShowConfirmationButtons() && !SAESGUIConfigurationManager::Current()->getActivatedAfterInsertingCard())
	{
		frame4->remove();
		frame4->add(*vbuttonbox1);
	}
}

void CardGeneratorFunctionality::on_buttonCancel_clicked()
{
	frame4->remove();
	frame4->add(*vbuttonbox1);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
}

Gtk::Widget* CardGeneratorFunctionality::GetFrame()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/card-activator.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - CardGeneratorFunctionality GetFrame");
	}

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("frame1", frame1);
	builder->get_widget("frame4", frame4);
	builder->get_widget("frame5", frame5);
	builder->get_widget("eventboxCardActivator",eventboxCardActivator);
	builder->get_widget("CardActivatorMessageEventBox",cardActivatorMessageEventBox);
	builder->get_widget("CardActivatorValuesEventBox",cardActivatorValuesEventBox);
	builder->get_widget("hbox1", hbox1);
	builder->get_widget("vbox3", vbox3);
	builder->get_widget("imageCard", imageCard);
	builder->get_widget("vbuttonbox1", vbuttonbox1);
	builder->get_widget("checkbuttonIsAudio", checkbuttonIsAudio);
	builder->get_widget_derived("labelResult", labelResult);
	builder->get_widget_derived("buttonActivate", buttonActivate);

	if(!SAESGUIConfigurationManager::Current()->getShowAudioCheckButton())
	{
		vbox3->remove(*frame5);
	}

	if(SAESGUIConfigurationManager::Current()->getActivatedAfterInsertingCard())
	{
		vbuttonbox1->remove(*buttonActivate);
	}

	imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif"));

	labelResult->set_size_request(300, 70);
	labelResult->SetSize(15);
	labelResult->SetCustomWrapMode();

	checkbuttonIsAudio->set_label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.IsAudio"));
	checkbuttonIsAudio->set_sensitive (false);

	buttonActivate->SetLabel(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.ActivateCard"));
	buttonActivate->WidgetsPosition (5,0,0);
	buttonActivate->set_size_request (200,30);
	buttonActivate->signal_clicked ().connect(sigc::mem_fun(*this,&CardGeneratorFunctionality::on_buttonGenerate_clicked));

	buttonOk.SetLabel(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.Ok"));
	buttonOk.signal_clicked ().connect(sigc::mem_fun(*this,&CardGeneratorFunctionality::on_buttonOk_clicked));
	buttonOk.set_size_request (70,50);

	buttonCancel.SetLabel(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.Cancel"));
	buttonCancel.signal_clicked ().connect(sigc::mem_fun(*this,&CardGeneratorFunctionality::on_buttonCancel_clicked));
	buttonCancel.set_size_request (70,50);

	buttonBox.set_spacing (5);
	buttonBox.pack_start(buttonOk);
	buttonBox.pack_start(buttonCancel);

	eventboxCardActivator->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityMessageName());
	cardActivatorMessageEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorMessageEventboxName());
	cardActivatorValuesEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorValuesEventboxName());

	frame4->set_size_request (200,100);
	frame1->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityCenterFrameName());

	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0)
	{
		comboSelections = new CustomAttributesComboSelectionsWidget(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CustomAttributeSelection"),"",false);
		frame1->add(*comboSelections);
	}
	else if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
	{
		comboSelections = new CustomAttributesComboSelectionsWidget(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CustomAttributeSelection"),"",true);

		frame1->add(*comboSelections);
	}
	else if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("SelectionWindows")==0)
	{

		labelBack= new Gtk::Label(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.GoBackToTheSelections"));
		labelBack->set_padding(0, 250);
		labelBack->set_alignment (Gtk::ALIGN_CENTER);
		labelBack->set_justify (Gtk::JUSTIFY_CENTER);
		labelBack->set_size_request(250, -1);
		labelBack->set_visible (true);
		Pango::FontDescription fontBack = labelBack->get_style()->get_font();
		fontBack.set_size(12*Pango::SCALE);
		fontBack.set_weight(Pango::WEIGHT_BOLD);
		labelBack->modify_font(fontBack);

		buttonBack = new Smartmatic::GUI::Widgets::SmartmaticButton ();
		buttonBack->SetLabel(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.BackToSelections"));
		buttonBack->signal_clicked ().connect(sigc::mem_fun(*this,&CardGeneratorFunctionality::on_buttonBack_clicked));
		buttonBack->WidgetsPosition (5,0,0);
		buttonBack->set_size_request (100,50);
		buttonBack->set_visible (true);

		vboxBack= new Gtk::VBox(50);
		vboxBack->show_all_children ();
		vboxBack->set_visible (true);
		vboxBack->pack_start (*labelBack,Gtk::PACK_SHRINK);
		vboxBack->pack_start (*buttonBack,Gtk::PACK_SHRINK);

		alignmentBack = new Gtk::Alignment();
		alignmentBack->set_padding (260, 5,10, 10);
		alignmentBack->show_all_children ();
		alignmentBack->set_visible (true);
		alignmentBack->add(*vboxBack);

		frame1->add(*alignmentBack);
		frame1->show_all_children ();
		frame1->set_visible (true);
	}

	counters = new CustomAttributesCounterWidget(_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.GeneratedCards"),"",Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCardActivationStatisticsConfiguration(),
												 Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCardActivatorStatisticsTitleColor(),Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetCardActivatorStatisticsTitleLabelConfiguration());

	counters->RefreshCounter();

	cardActivatorValuesEventBox->add(*counters);

	int counter = 0;
	///Here Comes the initialization of many Widgets, which can be translated to Initialize if needed to "refresh" the status every time the window is opened
	Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
	listCAD = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, Machine_type::VOTING_DEVICES_PM);

	for(list<Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
	{
		vector<ChooseDialogButtonInfo*> choices;

		for ( Custom_attribute_definition::ValueIterator c ((*l).getValue().begin()); c != (*l).getValue().end(); ++c)
		{
			ChooseDialogButtonInfo* info = new ChooseDialogButtonInfo(ElectionStringResourcesManager::Current()->getResource(*c), "",*c,*c);
			counter++;
			choices.push_back (info);
		}

		ChooseDialogInfo *infoDiag = NULL;
		if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0)
		{
			infoDiag = new ChooseDialogInfo(l->getName_key(),"","", choices,false);
			comboWidget = new ComboBoxChooseWidget (infoDiag);
			comboSelections->addComboWidget(comboWidget);
		}
		else if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
		{
			infoDiag = new ChooseDialogInfo(ElectionStringResourcesManager::Current()->getResource(l->getName_key()),l->getName_key(),"","", choices,false);
			eventWidget = new EventBoxChooseWidget (infoDiag);
			comboSelections->addBoxWidget(eventWidget);
		}

		for(unsigned int i=0;i < choices.size();i++)
		{
			delete(choices[i]);
		}

		if (infoDiag)
		{
			delete(infoDiag);
		}
	}

	if(counter == 0)
	{
		counter = 1;
		logger->Debug("Custom attribute not found");
	}

	//Lets calculate the option widgets size
	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0
	   || Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
	{
		comboSelections->ResizeOptionsWidgets (180,365/counter);
	}

	counters->ResizeOptionsWidgets (-1,80/counter);

	return framePrincipal;
};

bool CardGeneratorFunctionality::Enable()
{
	bool enableFunctionality = true;

	if (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated()
			< Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getMinimumDemoCounterToAllowActivation())
	{
		enableFunctionality = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.UnableKeyMessageDemostrationVoteNotPrinted"));
	}

	return enableFunctionality;
};

string CardGeneratorFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.CardActivatorFunctionality");

};

MenuOptionDescriptor CardGeneratorFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MCardGeneratorFunctionality,false);
};
	
void CardGeneratorFunctionality::Dispose()
{
	CardController::getInstance()->dispose();
	conn.disconnect();
	frame4->remove();
	frame4->add(*vbuttonbox1);
};

Smartmatic::Log::ISMTTLog* CardGeneratorFunctionality::getLogger()
{
	return logger;
}
Glib::ustring CardGeneratorFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.LogStartFunctionality");
}

Glib::ustring CardGeneratorFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CardGeneratorFunctionality.LogCloseFunctionality");
}

void CardGeneratorFunctionality::block()
{
	logger->Debug("Block functionality");
}

void CardGeneratorFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void CardGeneratorFunctionality::resume()
{
	logger->Debug("Resume functionality");
	Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->RestoreFile(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration());
}
