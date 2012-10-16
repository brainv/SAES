/*
 * FillAssistedActivationInfoFunctionality.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: Juan.Delgado
 */

#include "FillAssistedActivationInfoFunctionality.h"
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

using namespace Smartmatic::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;

FillAssistedActivationInfoFunctionality* FillAssistedActivationInfoFunctionality::current_instance = NULL;

Smartmatic::Log::ISMTTLog* FillAssistedActivationInfoFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.FillAssistedActivationInfoFunctionality",GETTEXT_PACKAGE);

FillAssistedActivationInfoFunctionality* FillAssistedActivationInfoFunctionality::Current()
{
	if (!current_instance)
		current_instance = new FillAssistedActivationInfoFunctionality();

	return current_instance;
};

FillAssistedActivationInfoFunctionality::~FillAssistedActivationInfoFunctionality()
{

}

FillAssistedActivationInfoFunctionality::FillAssistedActivationInfoFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	notebookContainer = NULL;
	assistedManager = NULL;
	alignWizard = NULL;
	outsideBox = NULL;
	addInfoButton = NULL;
	hboxBtn = NULL;

	box = NULL; /// not delete
}

Gtk::Widget* FillAssistedActivationInfoFunctionality::CreateNewPage()
{
	box = new Gtk::HBox();
	box->show();
	vectorWidget.push_back(box);
	return box;
}

Gtk::Widget* FillAssistedActivationInfoFunctionality::GetFrame()
{
	tablePos = 1;

	assistedManager = new AssistedActivationManagerWidget();
	assistedManager->on_activation_signal_emit().connect(sigc::mem_fun(*this, &FillAssistedActivationInfoFunctionality::on_AssistedManagerFinish));

	alignWizard = new Gtk::Alignment();
	alignWizard->set(0.5,0.5,1,1);
	alignWizard->add(*assistedManager);
	alignWizard->show_all_children();
	alignWizard->set_no_show_all();
	alignWizard->hide();

	addInfoButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.FillAssistedActivationInfoFunctionality.AddInfoButton"));
	addInfoButton->signal_clicked().connect(sigc::mem_fun(*this, &FillAssistedActivationInfoFunctionality::on_addInfoButton_clicked));
	addInfoButton->set_size_request(320, 50);

	hboxBtn = new Gtk::HButtonBox();
	hboxBtn->pack_start(*addInfoButton,false,false);
	hboxBtn->set_layout(Gtk::BUTTONBOX_CENTER);
	hboxBtn->set_size_request(350,-1);

	std::vector<std::string> emptyVectorString;
	CreateNewPage();

	notebookContainer = new NotebookContainer(vectorWidget, emptyVectorString);
	notebookContainer->ShowTabs(false);
	notebookContainer->AddBottomWidget(hboxBtn);

	outsideBox = new Gtk::HBox();
	outsideBox->add(*notebookContainer);
	outsideBox->add(*alignWizard);
	outsideBox->show_all_children();

	return outsideBox;
};

void FillAssistedActivationInfoFunctionality::on_AssistedManagerFinish(Activation activation)
{
	if(!isLoading)
	{
		Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAssistedActivation()->AddActivation(activation);
		Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAssistedActivation()->Persist();
	}

	AssistedActivationWidget * assistedViewerWidget = new AssistedActivationWidget(activation);
	assistedViewerWidget->show_all_children();
	assistedViewerWidget->show();

	assistedManagerList.push_back(assistedViewerWidget);

	if(tablePos == 3)
	{
		currentPage++;

		notebookContainer->AppendPage(CreateNewPage());
		notebookContainer->SetCurrentPage(currentPage);

		tablePos = 1;
	}

	box->pack_start(*assistedViewerWidget,false,false,12);

	tablePos++;

	notebookContainer->show();
	alignWizard->hide();
}

void FillAssistedActivationInfoFunctionality::on_addInfoButton_clicked()
{
	notebookContainer->hide();
	assistedManager->Start();
	alignWizard->show();
}

void FillAssistedActivationInfoFunctionality::Dispose()
{
}

void FillAssistedActivationInfoFunctionality::Initialize()
{
	currentPage = 2;

	Activations activations = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAssistedActivation()->getActivations();
	Activations::ActivationIterator iter;

	isLoading = true;

	for(iter = activations.getActivation().begin(); iter != activations.getActivation().end(); iter++)
	{
		on_AssistedManagerFinish(*iter);
	}

	isLoading = false;
	enableExitButton();
}

std::string FillAssistedActivationInfoFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FillAssistedActivationInfoFunctionality.FillAssistedActivationInfo");
}

Smartmatic::Functionality::MenuOptionDescriptor FillAssistedActivationInfoFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MFillAssistedActivationInfo,false);
}

Smartmatic::Log::ISMTTLog* FillAssistedActivationInfoFunctionality::getLogger()
{
	return logger;
}

Glib::ustring FillAssistedActivationInfoFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FillAssistedActivationInfoFunctionality.FillAssistedActivationStartFunctionality");
}

Glib::ustring FillAssistedActivationInfoFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FillAssistedActivationInfoFunctionality.FillAssistedActivationCloseFunctionality");
}

void FillAssistedActivationInfoFunctionality::deleteElement()
{
	if (notebookContainer)
	{
		delete notebookContainer;
		notebookContainer = NULL;
	}
	if (assistedManager)
	{
		delete assistedManager;
		assistedManager = NULL;
	}
	if(alignWizard)
	{
		delete alignWizard;
		alignWizard = NULL;
	}
	if (outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
	if (addInfoButton)
	{
		delete addInfoButton;
		addInfoButton = NULL;
	}
	if (hboxBtn)
	{
		delete hboxBtn;
		hboxBtn = NULL;
	}

	std::vector <Gtk::Widget *>::iterator itv;

	for (itv = vectorWidget.begin();
			itv != vectorWidget.end();
			itv++)
	{
		Gtk::Widget * widget = (*itv);
		delete widget;
		widget = NULL;
	}

	std::vector<AssistedActivationWidget* >::iterator ita;

	for (ita = assistedManagerList.begin();
			ita != assistedManagerList.end();
			ita++)
	{
		AssistedActivationWidget * widget = (*ita);
		delete widget;
		widget = NULL;
	}

	vectorWidget.clear();
	assistedManagerList.clear();
}
