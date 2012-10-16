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

#include "voting-machine-installation-wizard-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/id-card-widget.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/Card/CardController.hxx>
#include "System/IO/Directory.h"
#include "Security/Encryption.hxx"
#include "System/IO/Path.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "Security/SecretKey.h"
#include <Log/SMTTLogManager.h>
#include <Runtime/Environment/MemoryPathController.h>
#include "Functionalities/voting-machine-installation-functionality.h"
#include <eid/EIDManager.hxx>
#include <Configuration/SaesGUIConfiguration-schema.hxx>

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

#define CARD_HEADER_LEN 2

using namespace Gtk;
using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Common::Security;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* VotingMachineInstallationWizardWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.VotingMachineInstallationWizardWidget",GETTEXT_PACKAGE);

VotingMachineInstallationWizardWidget::VotingMachineInstallationWizardWidget()
{
	set_shadow_type(Gtk::SHADOW_NONE);

	CardActivatorFunctionalityConfiguration* config = SAESGUIConfigurationManager::Current()->GetCardActivatorWidgetConfiguration();
	
	imageStep.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/0_60x60.png"));
	imageStep.set_size_request (100,70);

	imageStepColor.set_rgb(config->getSelectedColor().getRed(), config->getSelectedColor().getGreen(), config->getSelectedColor().getBlue());
	
	eventBoxImageStep.set_name ("EventBoxImageStepInstallationWizard");
	eventBoxImageStep.add(imageStep);
	eventBoxImageStep.set_size_request (100,70);
	eventBoxImageStep.modify_bg(Gtk::STATE_NORMAL, imageStepColor);

	Pango::FontDescription fontTitle = labelStep.get_style()->get_font();
	fontTitle.set_size(15*Pango::SCALE);
	labelStep.set_alignment(0.0, 0.5);
	labelStep.set_padding(5, 0);
	labelStep.modify_font(fontTitle);
	labelStep.set_size_request(800, 50);
	labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.AcceptInstallation"));
	
	hboxStep.set_spacing (10);
	hboxStep.set_size_request (900,70);
	hboxStep.pack_start (eventBoxImageStep,Gtk::PACK_SHRINK);
	hboxStep.pack_start (labelStep,Gtk::PACK_SHRINK);

	imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/000.gif"));

	Pango::FontDescription fontMessage = labelMessage.get_style()->get_font();
	fontMessage.set_size(13*Pango::SCALE);
	labelMessage.modify_font(fontMessage);	
	labelMessage.set_size_request(700, 50);
	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.LabelMessageInitial"));
	
	nextButton.set_sensitive(true);
	nextButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.NextButton"));
	nextButton.WidgetsPosition (5,0,0);		
	nextButton.set_size_request (300,50);
	nextButton.signal_clicked().connect( sigc::mem_fun(this, &VotingMachineInstallationWizardWidget::on_buttonNext_clicked));
	nextButton.set_no_show_all();
	hboxButton.add(nextButton);

	hboxStepColor.set_rgb(config->getUnSelectedColor().getRed(), config->getUnSelectedColor().getGreen(), config->getUnSelectedColor().getBlue());

	eventBoxStep.set_size_request (900,70);
	eventBoxStep.set_name ("EventBoxStepInstallationWizard");
	eventBoxStep.modify_bg(Gtk::STATE_NORMAL, hboxStepColor);
	eventBoxStep.add(hboxStep);

	vboxPrincipal.set_spacing (3);
	vboxPrincipal.pack_start (eventBoxStep,false,false);
	vboxPrincipal.add (imageMessage);
	vboxPrincipal.add (labelMessage);
	vboxPrincipal.add (hboxButton);

	add(vboxPrincipal);
	set_visible (true);
	show_all_children ();

	if(SAESGUIConfigurationManager::Current()->getAskForId ())
	{
		m_StepSequence.push_back(WIZ_ASK_FOR_ID_INFO); //only belgian Id
	}
	
	if(SAESGUIConfigurationManager::Current()->getIncomePassphrase() == IncomePassphraseEnum::CONFIGURATION_TOKEN)
	{
		m_StepSequence.push_back(WIZ_REQUEST_IDENTITY_CARD);//only token
		m_StepSequence.push_back(WIZ_WRITE_IDENTITY_CARD);//only token
		m_StepSequence.push_back(WIZ_EXTRACT_IDENTITY_CARD);//only token
	}
	
	m_StepSequence.push_back(WIZ_EXTRACT_MEDIA);
	m_StepSequence.push_back(WIZ_INSTALL_MEDIA);
	m_StepSequence.push_back(WIZ_VERIFY_MEDIA);
	m_StepSequence.push_back(WIZ_FINALIZE);
	m_StepSequence.push_back(WIZ_END);
	
	imagePath.push_back("ui/InstallationWizardStep0.png");
	imagePath.push_back("ui/InstallationWizardStep1.png");
	imagePath.push_back("ui/InstallationWizardStep2.png");
	imagePath.push_back("ui/InstallationWizardStep3.png");
	imagePath.push_back("ui/InstallationWizardStep4.png");
	imagePath.push_back("ui/InstallationWizardStep5.png");
	imagePath.push_back("ui/InstallationWizardStep6.png");
	imagePath.push_back("ui/InstallationWizardStep7.png");
	imagePath.push_back("ui/InstallationWizardStep8.png");
	imagePath.push_back("ui/InstallationWizardStep9.png");
}

void VotingMachineInstallationWizardWidget::IdCardFinished()
{
	Smartmatic::SAES::EID::CitizenInfo citizenInfo = idCardWidget.getCitizenInfo ();
	try
	{
		Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->PersistenceInstallerData(citizenInfo);
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		std::stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
        logger->Debug(ss.str());
	}
    catch(Smartmatic::System::Exception::SignedException & ex)
	{
		std::stringstream ss;
        ss<< "FATAL "<<__func__<< ex.what();
        logger->Debug(ss.str());
	}
    catch(Smartmatic::System::Exception::XmlException & ex)
	{
		std::stringstream ss;
		ss<< "FATAL "<<__func__<< ex.what();
		logger->Debug(ss.str());
	}

    idCardWidget.dispose();

	vboxPrincipal.remove(idCardWidget);
	vboxPrincipal.add(labelMessage);
	vboxPrincipal.add(imageMessage);	
	vboxPrincipal.add(hboxButton);

	on_buttonNext_clicked_signal();
}

void VotingMachineInstallationWizardWidget::mForwardProcess()
{
	DisconnectConnections();

    try
    {
        if(imagePath.size()>counterImage)
        {
            imageStep.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,imagePath[counterImage]));
        }
    }
    catch (...)
    {
    }

	WizardStepType current_step = *m_ProcessTracker;
	int timerRefresh = 0;

	switch(current_step)
	{
	case WIZ_ASK_FOR_ID_INFO:

		idCardWidget.initialize();
		connIdCardFinished = idCardWidget.signal_accept_clicked().connect(sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::IdCardFinished));

		labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.RequestIDCard"));

		vboxPrincipal.remove(labelMessage);
		vboxPrincipal.remove(imageMessage);
		vboxPrincipal.remove(hboxButton);
		vboxPrincipal.add(idCardWidget);
		break;
			
	case WIZ_REQUEST_IDENTITY_CARD:

		nextButton.hide();

		CardController::getInstance()->initialize();

		labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.RequestLoginCard"));
		labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.WaitForLoginCard"));
		imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_request_identity_card.gif"));

		timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getVotingMachineInstallationWidgetInsert();
		mconn_InsertCard = Glib::signal_timeout ().connect (sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::DetectCard), timerRefresh);
		break;

	case WIZ_WRITE_IDENTITY_CARD:

		labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.WriteActionLoginCard"));
		labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.WritingLoginCard"));
		imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_write_identity_card.gif"));

		mconn_WritingCard = Glib::signal_timeout ().connect (sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::WriteCard), 500);
		break;

	case WIZ_EXTRACT_IDENTITY_CARD:

		labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.ExtractLoginCard"));
		labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.ExtractTokenMessage"));
		imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card.gif"));

		timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getVotingMachineInstallationWidgetExtract();
		mconn_ExtractCard = Glib::signal_timeout ().connect (sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::WaitForCardExtraction), timerRefresh);
		break;

	case WIZ_EXTRACT_MEDIA:

        Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->StopDetection();
        VotingMachineInstallationFunctionality::Current()->setExitButtonSensitive(false);

		labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.PleaseExtractDevice"));
		labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.LabelMessageExtractMedia"));
		imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_media.gif"));
		
		connExtract = Glib::signal_timeout ().connect (sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::Extract), 1000);
		break;

	case WIZ_INSTALL_MEDIA:

        labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.InstallDevice"));
        labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.InstallAndReturn"));
        imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_install_media.gif"));

        connDetect = Glib::signal_timeout ().connect (sigc::mem_fun(*this, &VotingMachineInstallationWizardWidget::Detect), 3000);
		break;

	case WIZ_VERIFY_MEDIA:

        labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.VerifyDataDevice"));
        labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.VerifyDataAndFinalize"));
        imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/check-flash-structure.gif"));

        if(!Glib::thread_supported()) Glib::thread_init();
        Glib::Thread::create(sigc::mem_fun(*this, &VotingMachineInstallationWizardWidget::checkData), false);
        break;

	case WIZ_FINALIZE:

		nextButton.show();
		nextButton.set_sensitive(true);
		nextButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.FinishButton"));

        labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.FinalizeStep"));
        labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.Finalize"));
        imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_finalize.gif"));

        try
        {
        	MachineOperationManager::getInstance()->installMachine();
        }
        catch (...)
        {
        	logger->Debug("ERROR - Install machine");
		}

		break;

	case WIZ_END:

        signalHide_detected.emit();
		break;

	default:

		break;
	}
}

void VotingMachineInstallationWizardWidget::checkData()
{
	bool validate = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getMachineInitiator()->checkData();

	if (validate)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingMachineInstallationWizardWidget::processCheckDataOk), 500);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingMachineInstallationWizardWidget::processCheckDataError), 500);
	}

	sleep(1);
}

void VotingMachineInstallationWizardWidget::processCheckDataOk()
{
    Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->StartDetection();

    labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.VerifyDataOk"));
    imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/check-flash-structure-success.gif"));

    NextStep(1000);
}

void VotingMachineInstallationWizardWidget::processCheckDataError()
{
    labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.VerifyDataError"));
    imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/check-flash-structure-failed.gif"));
}

void VotingMachineInstallationWizardWidget::on_buttonNext_clicked()
{
	counterImage++;
	if (m_ProcessTracker != m_StepSequence.end ())
	{
		mForwardProcess ();
		m_ProcessTracker++;
	}
}

bool VotingMachineInstallationWizardWidget::DetectCard ()
{
	bool card_detected = CardController::getInstance()->isCardPresent();

	if (card_detected)
	{
		NextStep(100);
	}

	return !card_detected;
}


bool VotingMachineInstallationWizardWidget::WriteCard ()
{
	bool data_written = false;

	try
	{
		data_written = CardController::getInstance()->writeToken();
	}
	catch (...)
	{
		logger->Debug("ERROR write card data");
		data_written = false;
	}

	int time_delay = 2000;

    if (!data_written)
    {
    	connRefreshLabel.disconnect();
    	connRefreshLabel = Glib::signal_timeout ().connect(sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::RefreshLabel), 500);

    	m_ProcessTracker--;
    	m_ProcessTracker--;
    	counterImage -= 2;
    	time_delay = 5000;
    }

    NextStep(time_delay);

	return false;
}

bool VotingMachineInstallationWizardWidget::RefreshLabel()
{
	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.ErrorWritingToken"));
	return false;
}

void VotingMachineInstallationWizardWidget::NextStep(int timer)
{
	connNextButton.disconnect();
	connNextButton = Glib::signal_timeout ().connect (sigc::mem_fun (*this, &VotingMachineInstallationWizardWidget::on_buttonNext_clicked_signal), timer);
}

bool VotingMachineInstallationWizardWidget::on_buttonNext_clicked_signal()
{
	on_buttonNext_clicked();
	return false;
}

bool VotingMachineInstallationWizardWidget::WaitForCardExtraction ()
{
	bool card_extracted = ! CardController::getInstance()->isCardPresent();

	if (card_extracted)
	{
		CardController::getInstance()->dispose();
		NextStep(500);
	}

	return !card_extracted;
}

void VotingMachineInstallationWizardWidget::Dispose()
{
	DisconnectConnections();

	idCardWidget.dispose();

	CardController::getInstance()->dispose();

    Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->StartDetection();
}

void VotingMachineInstallationWizardWidget::Initialize()
{
	m_ProcessTracker = m_StepSequence.begin();
	counterStep = 0;
	counterImage = 0;
	counterUnmount = 0;
	nothingMounted = false;
	
	labelStep.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.AcceptInstallation"));

	imageStep.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/0_60x60.png"));

	imageMessage.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/000.gif"));

	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.LabelMessageInitial"));

	nextButton.show();
	nextButton.set_sensitive(true);
	nextButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.VotingMachineInstallationWizardWidget.NextButton"));

    VotingMachineInstallationFunctionality::Current()->setExitButtonSensitive(true);
};

bool VotingMachineInstallationWizardWidget::Extract()
{
	std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();
	std::string domMedia = MemoryPathController::getInstance()->getDomMemoryBasePath();

	if (flashMedia.empty() || domMedia.empty())
	{
        VotingMachineInstallationFunctionality::Current()->setExitButtonSensitive(false);

        NextStep(500);
		return false;
	}
	return true;
}

bool VotingMachineInstallationWizardWidget::Detect()
{
	std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();
	std::string domMedia = MemoryPathController::getInstance()->getDomMemoryBasePath();

	if (Directory::DirectoryExists(flashMedia) && Directory::DirectoryExists(domMedia))
	{
	    NextStep(500);
		return false;
	}
	return true;
}

void VotingMachineInstallationWizardWidget::DisconnectConnections()
{
	if(mconn_InsertCard.connected())
		mconn_InsertCard.disconnect();

	if(mconn_WritingCard.connected())
		mconn_WritingCard.disconnect();

	if(mconn_ExtractCard.connected())
		mconn_ExtractCard.disconnect();

	if(connDetect.connected())
		connDetect.disconnect();

	if(connExtract.connected())
		connExtract.disconnect();

    if(connVerifyData.connected())
        connVerifyData.disconnect();

    if(connIdCardFinished.connected())
		connIdCardFinished.disconnect();

	if(connNextButton.connected())
		connNextButton.disconnect();

	if(connRefreshLabel.connected())
		connRefreshLabel.disconnect();
}
