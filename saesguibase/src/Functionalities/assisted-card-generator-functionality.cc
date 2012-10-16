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
#include "Functionalities/assisted-card-generator-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/Card/CardController.hxx>
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

using namespace std;
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

ISMTTLog* AssistedCardGeneratorFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality",GETTEXT_PACKAGE);

AssistedCardGeneratorFunctionality* AssistedCardGeneratorFunctionality::current_instance = NULL;

AssistedCardGeneratorFunctionality* AssistedCardGeneratorFunctionality::Current()
{
	if (!current_instance)
		current_instance = new AssistedCardGeneratorFunctionality();

	return current_instance;
};

AssistedCardGeneratorFunctionality::AssistedCardGeneratorFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>(),recoveryInfo("","")
{
	framePrincipal = NULL;
	assistedAlignment = NULL;
	frame1 = NULL;
	frame2 = NULL;
	frame4 = NULL;
	hbox1 = NULL;
	vbox2 = NULL;
	vbuttonbox1 = NULL;
	imageCard = NULL;
	labelResult = NULL;
	buttonActivate = NULL;
	buttonStartWizard = NULL;
	comboSelections = NULL;
	eventboxCardActivator = NULL;
	checkbuttonIsAudio = NULL;
	assistedManager = NULL;
	assistedPreviewInfo = NULL;
	scrolled = NULL;
	alignmentBack = NULL;
	vboxBack = NULL;
	buttonBack = NULL;
	labelBack = NULL;
	comboWidget = NULL;
	eventWidget = NULL;
	wizardIsReady = false;
}

AssistedCardGeneratorFunctionality::~AssistedCardGeneratorFunctionality()
{
	deleteElement();
}

void AssistedCardGeneratorFunctionality::deleteElement()
{
	if(framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(assistedAlignment != NULL)
	{
		delete(assistedAlignment);
		assistedAlignment = NULL;
	}
	if(frame1 != NULL)
	{
		delete(frame1);
		frame1 = NULL;
	}
	if(frame2 != NULL)
	{
		delete(frame2);
		frame2 = NULL;
	}
	if(frame4 != NULL)
	{
		delete(frame4);
		frame4 = NULL;
	}
	if(hbox1 != NULL)
	{
		delete(hbox1);
		hbox1 = NULL;
	}
	if(vbox2 != NULL)
	{
		delete(vbox2);
		vbox2 = NULL;
	}
	if(vbuttonbox1 != NULL)
	{
		delete(vbuttonbox1);
		vbuttonbox1 = NULL;
	}
	if(imageCard != NULL)
	{
		delete(imageCard);
		imageCard = NULL;
	}
	if(labelResult != NULL)
	{
		delete(labelResult);
		labelResult = NULL;
	}
	if(buttonStartWizard != NULL)
	{
		delete(buttonStartWizard);
		buttonStartWizard = NULL;
	}
	if(buttonActivate != NULL)
	{
		delete(buttonActivate);
		buttonActivate = NULL;
	}
	if(comboSelections != NULL)
	{
		delete(comboSelections);
		comboSelections = NULL;
	}
	if(eventboxCardActivator != NULL)
	{
		delete(eventboxCardActivator);
		eventboxCardActivator = NULL;
	}
	if(checkbuttonIsAudio != NULL)
	{
		delete(checkbuttonIsAudio);
		checkbuttonIsAudio = NULL;
	}
	if(assistedManager)
	{
		delete assistedManager;
		assistedManager = NULL;
	}
	if(assistedPreviewInfo)
	{
		delete(assistedPreviewInfo);
		assistedPreviewInfo = NULL;
	}
	if(scrolled)
	{
		delete(scrolled);
		scrolled = NULL;
	}
	if (alignmentBack)
	{
		delete alignmentBack;
		alignmentBack = NULL;
	}
	if (labelBack)
	{
		delete labelBack;
		labelBack = NULL;
	}
	if (vboxBack)
	{
		delete vboxBack;
		vboxBack = NULL;
	}
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
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
}

void AssistedCardGeneratorFunctionality::cleanAttributes()
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

void AssistedCardGeneratorFunctionality::Initialize()
{
	buttonActivate->set_sensitive(false);
	buttonStartWizard->set_sensitive(true);

	if(SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("SelectionWindows")==0)
	{
		GoToSelectionWindow();
	}

	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getAssistedCardGeneratorFunctionality();

	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			   &AssistedCardGeneratorFunctionality::Refresh), 0);
	conn = Glib::signal_timeout().connect(my_slot,timerRefresh);

	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.FillData"));

	wasPresent = false;
	isAssistedActivation = false;
	cardJustActivated = false;

	framePrincipal->remove();
	framePrincipal->add(*hbox1);

	enableExitButton();
};

void AssistedCardGeneratorFunctionality::GoToSelectionWindow()
{
	cleanAttributes();

	for(list<Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		vector<ChooseDialogButtonInfo*> choices;
		for ( Custom_attribute_definition::ValueIterator
		 c ((*l).getValue().begin());
		 c != (*l).getValue().end();
		 ++c)
		{
			ChooseDialogButtonInfo* info = new ChooseDialogButtonInfo((*c), "",(*c),(*c));
			choices.push_back (info);
		}
		ChooseDialogInfo *infoDiag = NULL;
		infoDiag = new ChooseDialogInfo(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CustomAttributeSelection"),"",l->getName_key(), choices,false);

		ChooseOptionWindow optionWindow(infoDiag, "");
		optionWindow.signal_detected.connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::onOptionButton));
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

void AssistedCardGeneratorFunctionality::onOptionButton(ChooseDialogButtonInfo* info)
{
	temporalValue.clear();
	temporalValue.append(info->getName());
}

std::string AssistedCardGeneratorFunctionality::getCodeByName(std::string optionName)
{
	//std::list < Custom_attribute_definition > listCAD = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, Machine_type::VOTING_DEVICES_PM);
	for(list<Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		if((*l).getName_key().compare(optionName)==0)
	   {
		   return (*l).getCode();
	   }
	}

	logger->Debug("Assited Act: CustomAttrCode " + optionName + " not found");
	return "";
}

std::string AssistedCardGeneratorFunctionality::getNameByCode(std::string optionCode)
{
	//std::list < Custom_attribute_definition > listCAD = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, Machine_type::VOTING_DEVICES_PM);
	for(list<Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		if((*l).getCode().compare(optionCode)==0)
	   {
		   return (*l).getName_key();
	   }
	}

	logger->Debug("Assited Act: CustomAttrName " + optionCode + " not found");
	return "";
}

bool AssistedCardGeneratorFunctionality::Refresh(int time_num)
{
	if(wizardIsReady)
	{
		bool present = CardController::getInstance()->isCardPresent();
		if(present && !wasPresent)
		{
			//Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getVotingDevice("342");
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
			buttonActivate->set_sensitive(true);
			wasPresent = true;

		}
		else if (!present && wasPresent)
		{
			buttonActivate->set_sensitive(false);
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.InsertCardToActivate"));

			frame4->remove();
			frame4->add(*vbuttonbox1);
			wasPresent = false;
		}
	}
	else
	{
		if(cardJustActivated)
		{
			bool present = CardController::getInstance()->isCardPresent();
			if(!present && wasPresent)
			{
				labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.FillData"));
				cardJustActivated = false;
				wasPresent = false;
			}
		}
	}
	return true;
}

void AssistedCardGeneratorFunctionality::on_buttonBack_clicked()
{
	GoToSelectionWindow ();
}

void AssistedCardGeneratorFunctionality::on_buttonGenerate_clicked()
{
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.AreYouCompletelySureYouWantToActivate"));
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

void AssistedCardGeneratorFunctionality::on_buttonStartWizard_clicked()
{
	framePrincipal->remove();
	framePrincipal->add(*assistedAlignment);
	framePrincipal->show_all_children ();
	assistedManager->Start();
}

void AssistedCardGeneratorFunctionality::on_buttonOk_clicked()
{
	
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
	   CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes,cardData, true, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD, checkbuttonIsAudio->get_active());

		if (!CardController::getInstance()->writeCardData(cardData))
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
			buttonActivate->set_sensitive(false);
		}
		else
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CardWasActivated"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CardWasActivatedSuccessfully"));
			wizardIsReady = false;
			cardJustActivated = true;
			buttonActivate->set_sensitive(false);
			buttonStartWizard->set_sensitive(true);
			Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper* wrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAssistedActivation();
			wrapper->AddActivation(this->activation);
			Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->RefreshStats(cardData);
			wrapper->Persist();
			scrolled->remove();
			frame2->set_shadow_type(Gtk::SHADOW_IN);

		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
	}
	catch(...)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
	}

	cleanAttributes();

	if(SAESGUIConfigurationManager::Current()->getShowConfirmationButtons())
	{
		frame4->remove();
		frame4->add(*vbuttonbox1);
	}

}

void AssistedCardGeneratorFunctionality::on_buttonCancel_clicked()
{
	frame4->remove();
	frame4->add(*vbuttonbox1);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
}

void AssistedCardGeneratorFunctionality::on_AssistedOk(Smartmatic::SAES::Voting::PBReports::Activation activation)
{
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.InsertCardToActivate"));

	this->activation = activation;
	framePrincipal->remove();
	framePrincipal->add(*hbox1);
	if(assistedPreviewInfo)
	{
		delete(assistedPreviewInfo);
		assistedPreviewInfo = NULL;
	}	
	assistedPreviewInfo = new Smartmatic::SAES::GUI::Widgets::AssistedActivationIDCardWidgetViewer(activation);
	scrolled->add(*assistedPreviewInfo);
	scrolled->show_all_children ();
	frame2->show_all_children ();
	frame2->set_visible(true);
	frame2->set_shadow_type(Gtk::SHADOW_NONE);
	isAssistedActivation = true;

	buttonActivate->set_sensitive(false);
	buttonStartWizard->set_sensitive(true);
	wizardIsReady = true;
	CardController::getInstance()->initialize();
}

Gtk::Widget* AssistedCardGeneratorFunctionality::GetFrame()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/assisted-card-activator.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - AssistedCardGeneratorFunctionality GetFrame");
	}

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("frame1", frame1);
	builder->get_widget("frame2", frame2);
	builder->get_widget("frame4", frame4);
	builder->get_widget("hbox1", hbox1);
	builder->get_widget("vbuttonbox1", vbuttonbox1);
	builder->get_widget("eventboxCardActivator",eventboxCardActivator);
	builder->get_widget("CardActivatorMessageEventBox",cardActivatorMessageEventBox);
	builder->get_widget("CardActivatorValuesEventBox",cardActivatorValuesEventBox);
	//builder->get_widget("vbox2", vbox2);
	builder->get_widget("checkbuttonIsAudio", checkbuttonIsAudio);
	builder->get_widget("imageCard", imageCard);
	builder->get_widget("labelResult", labelResult);
	builder->get_widget_derived("buttonActivate", buttonStartWizard);
	builder->get_widget_derived("buttonAssistedActivate", buttonActivate);
	labelResult->set_size_request(200, 50);

	checkbuttonIsAudio->set_label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.IsAudio"));
	checkbuttonIsAudio->set_sensitive (false);
	buttonActivate->SetLabel(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.ActivateCard"));
	buttonActivate->WidgetsPosition (5,0,0);
	buttonActivate->set_size_request (190,60);
	buttonActivate->signal_clicked ().connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::on_buttonGenerate_clicked));
	
	buttonStartWizard->set_size_request (190,60);
	buttonStartWizard->WidgetsPosition (5,0,0);
	buttonStartWizard->SetLabel(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.FillInfo"));
	buttonStartWizard->signal_clicked ().connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::on_buttonStartWizard_clicked));

	assistedAlignment = new Gtk::HButtonBox();
	scrolled = new Gtk::ScrolledWindow ();
	//scrolled->set_shadow_type(Gtk::SHADOW_NONE);
	scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	assistedManager = new AssistedActivationManagerWidget();
	assistedManager->on_activation_signal_emit().connect(sigc::mem_fun(*this, &AssistedCardGeneratorFunctionality::on_AssistedOk));

	assistedAlignment->add(*assistedManager);

	frame2->set_size_request (300,-1);
	frame2->add(*scrolled);
	int counter = 0;

	buttonOk.SetLabel(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.Ok"));
	buttonOk.set_size_request (70,50);

	buttonCancel.SetLabel(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.Cancel"));
	buttonCancel.set_size_request (70,50);

	buttonOk.signal_clicked ().connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::on_buttonOk_clicked));
	buttonCancel.signal_clicked ().connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::on_buttonCancel_clicked));

	buttonBox.set_spacing (5);
	buttonBox.pack_start(buttonOk);
	buttonBox.pack_start(buttonCancel);

	frame4->set_size_request (150,100);
	eventboxCardActivator->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityMessageName());
	cardActivatorMessageEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorMessageEventboxName());
	//cardActivatorFunctionalityEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityEventboxName());
	cardActivatorValuesEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorValuesEventboxName());
	frame1->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityCenterFrameName());
	//eventboxCardActivator->set_size_request (200,50);
	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0)
	{
		comboSelections = new CustomAttributesComboSelectionsWidget(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CustomAttributeSelection"),"",false);
		
		frame1->add(*comboSelections);
	}
	else if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
	{
		comboSelections = new CustomAttributesComboSelectionsWidget(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CustomAttributeSelection"),"",true);

		frame1->add(*comboSelections);
	}
	else if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("SelectionWindows")==0)
	{
		alignmentBack = new Gtk::Alignment();
		vboxBack= new Gtk::VBox(50);
		labelBack= new Gtk::Label(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.GoBackToTheSelections"));

		labelBack->set_padding(0, 250);
		labelBack->set_alignment (Gtk::ALIGN_CENTER);
		Pango::FontDescription fontBack = labelBack->get_style()->get_font();
		fontBack.set_size(12*Pango::SCALE);
		labelBack->set_justify (Gtk::JUSTIFY_CENTER);
		fontBack.set_weight(Pango::WEIGHT_BOLD);
		labelBack->modify_font(fontBack);
		labelBack->set_size_request(250, -1);

		buttonBack = new Smartmatic::GUI::Widgets::SmartmaticButton ();
		buttonBack->SetLabel(_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.BackToSelections"));

		buttonBack->WidgetsPosition (5,0,0);
		buttonBack->set_size_request (100,50);
		buttonBack->signal_clicked ().connect(sigc::mem_fun(*this,&AssistedCardGeneratorFunctionality::on_buttonBack_clicked));
		labelBack->set_visible (true);
		buttonBack->set_visible (true);
		vboxBack->show_all_children ();
		vboxBack->set_visible (true);
		vboxBack->pack_start (*labelBack,Gtk::PACK_SHRINK);
		vboxBack->pack_start (*buttonBack,Gtk::PACK_SHRINK);
		alignmentBack->set_padding (260, 5,10, 10);
		alignmentBack->show_all_children ();
		alignmentBack->set_visible (true);
		alignmentBack->add(*vboxBack);
		frame1->show_all_children ();
		frame1->set_visible (true);
		frame1->add(*alignmentBack);
	}

	//vbox2->add(*);
	imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif"));

	///Here Comes the initialization of many Widgets, which can be translated to Initialize if needed to "refresh" the status every time the window is opened
	Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
	listCAD = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, Machine_type::VOTING_DEVICES_PM);
	for(list<Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		vector<ChooseDialogButtonInfo*> choices;
		for ( Custom_attribute_definition::ValueIterator
		 c ((*l).getValue().begin());
		 c != (*l).getValue().end();
		 ++c)
		{
			ChooseDialogButtonInfo* info = new ChooseDialogButtonInfo(ElectionStringResourcesManager::Current()->getResource(*c), "",*c,*c);
			counter++;
			choices.push_back (info);
		}
		ChooseDialogInfo *infoDiag = NULL;
		//ChooseDialogInfo *infoCounter= NULL;

		//infoCounter = new ChooseDialogInfo(ElectionStringResourcesManager::Current()->getResource(l->getName_key()),l->getName_key(),"","", choices,false);
		//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (infoCounter);
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
	//Lets calculate the option widgets size
	if(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("ComboBoxes")==0
	   || Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCustomAttributesPresentation().compare("EventBoxes")==0)
	{
		if(counter == 0)
		{
			logger->Debug("Custom attribute not found");
			counter = 1;
		}
		comboSelections->ResizeOptionsWidgets (150,300/counter);
	}
	return framePrincipal;
};

void AssistedCardGeneratorFunctionality::RefreshCounter(std::string optionName, std::string optionValue)
{

}

bool AssistedCardGeneratorFunctionality::Enable()
{
	bool enableFunctionality = true;

	if (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated()
			< Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getMinimumDemoCounterToAllowActivation())
	{
		enableFunctionality = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.UnableKeyMessageDemostrationVoteNotPrinted"));
	}

	return enableFunctionality;
};

string AssistedCardGeneratorFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.CardActivatorFunctionality");

};

MenuOptionDescriptor AssistedCardGeneratorFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MAssistedCardGeneratorFunctionality,false);
};

void AssistedCardGeneratorFunctionality::Dispose()
{
	CardController::getInstance()->dispose();

	cleanAttributes();
	conn.disconnect();
	frame4->remove();
	frame4->add(*vbuttonbox1);

	if(assistedManager)
		assistedManager->Dispose();

	Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAssistedActivation()->Persist();
};

Smartmatic::Log::ISMTTLog* AssistedCardGeneratorFunctionality::getLogger()
{
	return logger;
}
Glib::ustring AssistedCardGeneratorFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.LogStartFunctionality");
}

Glib::ustring AssistedCardGeneratorFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AssistedCardGeneratorFunctionality.LogCloseFunctionality");
}
