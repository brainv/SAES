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

#include "calibration-diagnosis-widget.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Configuration/label-configuration.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <queue>
#include <System/IO/File.h>
#include <System/Runtime/ProcessLauncher.h>

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
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Runtime;

ISMTTLog* CalibrationDiagnosisWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUi.Widgets.CalibrationDiagnosisWidget",GETTEXT_PACKAGE);

	void CalibrationDiagnosisWidget::Initialize()
	{		
		timeout = 0;
		//
		//Get the builder from the XML file.
		framePrincipal = NULL;	

		//Glib::RefPtr<Gtk::Builder> builder;
		try
		{
			builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/calibration_diagnosis.glade"));
		}
		catch (const Glib::FileError & ex)
		{
	        std::stringstream ss;
	        ss  << "FATAL - " << __func__ << " " << ex.what();
	        logger->Debug(ss.str());
		}

		builder->get_widget("frame",framePrincipal);
		builder->get_widget("hbox1",bottomBox);
		builder->get_widget("vbox1",vbox1);
		builder->get_widget("vbox2",vbox2);
		builder->get_widget("side1",side1);
		builder->get_widget("side2",side2);
		builder->get_widget("middle",middle);
		builder->get_widget("labelCal",labelCal);
		builder->get_widget("hbuttonbox1",hbuttonbox1);
		builder->get_widget("hbuttonbox2",hbuttonbox2);
		builder->get_widget_derived("button1",button1);
		builder->get_widget_derived("button2",button2);
		builder->get_widget_derived("button3",button3);
		builder->get_widget_derived("button4",button4);		
		builder->get_widget_derived("button5",button5);
		
		
		button1->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_button1_clicked));
		button2->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_button2_clicked));
		button3->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_button3_clicked));
		button4->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_button4_clicked));
		button5->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_button5_clicked));
		
		button1->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		button2->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		button3->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		button4->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		button5->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		
		side1->set_events(Gdk::BUTTON_PRESS_MASK);
		side2->set_events(Gdk::BUTTON_PRESS_MASK);
		middle->set_events(Gdk::BUTTON_PRESS_MASK);
		side1->signal_button_press_event().connect(sigc::mem_fun(*this, &CalibrationDiagnosisWidget::on_zone_clicked));
		side2->signal_button_press_event().connect(sigc::mem_fun(*this, &CalibrationDiagnosisWidget::on_zone_clicked));
		middle->signal_button_press_event().connect(sigc::mem_fun(*this, &CalibrationDiagnosisWidget::on_zone_clicked));
		LabelConfiguration diagConf =  SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(labelCal, diagConf);

		hbuttonbox2->set_size_request (40,40);

		middle->show_all_children();
		middle->set_visible(true);
		
		click_counter=0;
		fail_Cal=false;
		button1->set_visible (true);
		labelCal->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.PressButtonToTestCalibration"));
		framePrincipal->remove ();
		framePrincipal->add(*bottomBox);
		button1->set_visible (true);
		button2->set_visible (false);
		button3->set_visible (false);
		button4->set_visible (false);
		button5->set_visible (false);

		button1->set_no_show_all();
		button2->set_no_show_all();
		button3->set_no_show_all();
		button4->set_no_show_all();
		button5->set_no_show_all();

		int HeightOfButton =SAESGUIConfigurationManager::Current()->getHeightOfButtons();
		int WidthOfButton =SAESGUIConfigurationManager::Current()->getWidthOfButtons();

		vbox1->set_size_request (WidthOfButton,-1);
		vbox2->set_size_request (WidthOfButton,-1);
		
		button1->set_size_request(WidthOfButton,HeightOfButton);
		button2->set_size_request(WidthOfButton,HeightOfButton);
		button3->set_size_request(WidthOfButton,HeightOfButton);
		button4->set_size_request(WidthOfButton,HeightOfButton);
		button5->set_size_request(WidthOfButton,HeightOfButton);

		button1->SetLabel("");
		button2->SetLabel("");
		button3->SetLabel("");
		button4->SetLabel("");
		button5->SetLabel("");
		setDiagnosticFrame(*framePrincipal);
	};

	bool CalibrationDiagnosisWidget::AutoDiag(int time_num)
	{
		int numberOfPoints = SAESGUIConfigurationManager::Current()->getTouchScreenCalibrationNumberOfPoints();

		stringstream ss;
		ss << numberOfPoints;
		std::string fullCommand("gCal ");
		fullCommand.append(ss.str());
		int result = ProcessLauncher::RunProcessThroughSystem(fullCommand.c_str());
		
		if(result == 0)
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.AutoCalibrationSucceded"));
			MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Ok);
			signalContinue_detected.emit();
		}
		else
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.AutoCalibrationFailed"));
			MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Error);
			signalContinue_detected.emit();
		}		
		return false;
	}


	bool  CalibrationDiagnosisWidget::RefreshTimeout(int time_num)
	{
		timeout++;
		if(timeout==3)
		{
			on_buttonCalibrate_clicked ();
			timeout = 0;
			return false;
		}
		return true;
	}

	void CalibrationDiagnosisWidget::GetFrameFracaso()
	{
		click_counter=0;
		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			       &CalibrationDiagnosisWidget::RefreshTimeout), 0);
		connRefreshTimeout = Glib::signal_timeout().connect(my_slot,1000);
		try
		{
			builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/calibration_failure.glade"));
		}
		catch (const Glib::FileError & ex)
		{
	        std::stringstream ss;
	        ss  << "FATAL - " << __func__ << " " << ex.what();
	        logger->Debug(ss.str());
		}
		
		builder->get_widget("frame1",frameFailure);
		builder->get_widget_derived("buttonCalibrate",buttonCalibrate);
		builder->get_widget("mensajeFracaso",mensajeFracaso);
		
		
		mensajeFracaso->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.CalibrationFailed"));
		if(!isOpeningMachine)
		{
			MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Error);
		}
		buttonCalibrate->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.Calibrate"));
		LabelConfiguration diagConf =  SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(mensajeFracaso, diagConf);
		
		framePrincipal->remove();
		framePrincipal->add(*frameFailure);
		//framePrincipal->show_all_children();
		buttonCalibrate->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		buttonCalibrate->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_buttonCalibrate_clicked));
	}

	void CalibrationDiagnosisWidget::GetFrameSuccess()
	{
		click_counter=0;
		try
		{
			builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/calibration_success.glade"));
		}
		catch (const Glib::FileError & ex)
		{
	        std::stringstream ss;
	        ss  << "FATAL - " << __func__ << " " << ex.what();
	        logger->Debug(ss.str());
		}
		
		builder->get_widget("frameSuccess",frameSuccess);
		builder->get_widget_derived("buttonOk",buttonOk);
		builder->get_widget_derived("buttonCalSuc",buttonCalSuc);
		builder->get_widget("mensajeSuccess",mensajeSuccess);

		mensajeSuccess->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.CalibrationSucceded"));
		if(!isOpeningMachine)
		{
			MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Ok);
		}
		buttonCalSuc->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.Calibrate"));
		buttonOk->set_label(_("Smartmatic.SAES.GUI.Widgets.CalibrationDiagnosisWidget.Ok"));
		buttonOk->set_sensitive(true);
		LabelConfiguration diagConf =  SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
		LabelConfiguration::SetLabelConfiguration(mensajeSuccess, diagConf);
		
		framePrincipal->remove();
		framePrincipal->add(*frameSuccess);
		buttonCalSuc->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		buttonOk->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
		buttonCalSuc->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::on_buttonCalibrate_clicked));
		buttonOk->signal_clicked().connect(sigc::mem_fun(this, &CalibrationDiagnosisWidget::onbuttonokclicked));
	}

	void CalibrationDiagnosisWidget::onbuttonokclicked()
	{
		connRefreshTimeout.disconnect();
		if(!isOpeningMachine)
		{
			MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Ok);
		}
		buttonOk->set_sensitive(false);
		signalOk_detected.emit();
	}

	void CalibrationDiagnosisWidget::on_buttonCalibrate_clicked()
	{
		connRefreshTimeout.disconnect();
		int numberOfPoints = SAESGUIConfigurationManager::Current()->getTouchScreenCalibrationNumberOfPoints();
		stringstream ss;
		ss << numberOfPoints;
		std::string fullCommand("gCal ");
		fullCommand.append(ss.str());

		int result = ProcessLauncher::RunProcessThroughSystem(fullCommand.c_str());
		if(result > -1)
		{
			if(!isOpeningMachine)
			{
				MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::TouchScreenCalibration, OperationStatus::Ok);
			}
		}

		getBacktoInitialFrame();
	}

	void CalibrationDiagnosisWidget::getBacktoInitialFrame()
	{
		click_counter=0;
		fail_Cal=false;
		framePrincipal->remove();
		framePrincipal->add(*bottomBox);
		//framePrincipal->show_all_children();
		framePrincipal->set_visible(true);
		button1->set_visible (true);
		button2->set_visible (false);
		button3->set_visible (false);
		button4->set_visible (false);
		button5->set_visible (false);
	}

	void CalibrationDiagnosisWidget::on_button1_clicked()
	{
		click_counter++;
		button1->set_visible (false);
		button2->set_visible (true);
		
		
	}
	void CalibrationDiagnosisWidget::on_button2_clicked()
	{
		click_counter++;
		button2->set_visible (false);
		button3->set_visible (true);
		
	}
	void CalibrationDiagnosisWidget::on_button3_clicked()
	{
		click_counter++;
		button3->set_visible (false);
		button4->set_visible (true);	
	}

	void CalibrationDiagnosisWidget::on_button4_clicked()
	{
		click_counter++;
		button4->set_visible (false);
		middle->remove();
		middle->add(*hbuttonbox1);
		middle->set_visible(true);
		button5->set_visible (true);
		
	}

	void  CalibrationDiagnosisWidget::on_button5_clicked()
	{
		click_counter++;

		button5->set_visible (false);
		if (fail_Cal)
			GetFrameFracaso();
		else
			GetFrameSuccess();
	}

	bool  CalibrationDiagnosisWidget::on_zone_clicked(GdkEventButton* event )
	{
		click_counter++;
		fail_Cal=true;

		switch(click_counter){
			case 1:
				//button1->set_visible (false);
				//button2->set_visible (true);
				GetFrameFracaso();
				break;
			case 2:
				//button2->set_visible (false);
				//button3->set_visible (true);
				GetFrameFracaso();
				break;
			case 3:
				//button3->set_visible (false);
				//button4->set_visible (true);
				GetFrameFracaso();
				break;
			case 4:
				//button4->set_visible (false);
				//button5->set_visible (true);
				GetFrameFracaso();
				break;	
			case 5:
				//button4->set_visible (false);
				GetFrameFracaso();
				break;	
		}
		return true;
	};



	void CalibrationDiagnosisWidget::Dispose()
	{
		connAuto.disconnect();
	};

CalibrationDiagnosisWidget::CalibrationDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons, bool isOpeningMachine)
: BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::TouchScreenCalibration, hasOk,hasCancel,hasMessage,showButtons)
{
	click_counter=0;
	this->isOpeningMachine = isOpeningMachine;
	labelCal = NULL;
	framePrincipal = NULL;
	bottomBox = NULL;
	side1 = NULL;
	side2 = NULL;
	middle = NULL;
	button1 = NULL;
	button2 = NULL;
	button3 = NULL;
	button4 = NULL;
	button5 = NULL;
	hbuttonbox1 = NULL;
	hbuttonbox2 = NULL;
	frameFailure = NULL;
	buttonCalibrate = NULL;
	mensajeFracaso = NULL;
	frameSuccess = NULL;
	buttonCalSuc = NULL;
	buttonOk = NULL;
	mensajeSuccess = NULL;
	labelResult = NULL;
	imageCalib = NULL;

}

CalibrationDiagnosisWidget::~CalibrationDiagnosisWidget()
{
	remove();

	if(framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(labelCal != NULL)
	{
		delete(labelCal);
		labelCal = NULL;
	}
	if(labelResult != NULL)
	{
		delete(labelResult);
		labelResult = NULL;
	}
	if(hbuttonbox1 != NULL)
	{
		delete(hbuttonbox1);
		hbuttonbox1 = NULL;
	}
	if(hbuttonbox2 != NULL)
	{
		delete(hbuttonbox2);
		hbuttonbox2 = NULL;
	}
	
	if(imageCalib != NULL)
	{
		delete(imageCalib);
		imageCalib = NULL;
	}
	if(bottomBox != NULL)
	{
		delete(bottomBox);
		bottomBox = NULL;
	}
	if(side1 != NULL)
	{
		delete(side1);
		side1 = NULL;
	}
	if(side2 != NULL)
	{
		delete(side2);
		side2 = NULL;
	}
	if(middle != NULL)
	{
		delete(middle);
		middle = NULL;
	}
	if(button1 != NULL)
	{
		delete(button1);
		button1 = NULL;
	}
	if(button2 != NULL)
	{
		delete(button2);
		button2 = NULL;
	}
	if(button3 != NULL)
	{
		delete(button3);
		button3 = NULL;
	}
	if(button4 != NULL)
	{
		delete(button4);
		button4 = NULL;
	}
	if(button5 != NULL)
	{
		delete(button5);
		button5 = NULL;
	}
	if(frameFailure != NULL)
	{
		delete(frameFailure);
		frameFailure = NULL;
	}
	if(buttonCalibrate != NULL)
	{
		delete(buttonCalibrate);
		buttonCalibrate = NULL;
	}
	if(mensajeFracaso != NULL)
	{
		delete(mensajeFracaso);
		mensajeFracaso = NULL;
	}
	if(frameSuccess != NULL)
	{
		delete(frameSuccess);
		frameSuccess = NULL;
	}
	if(buttonCalSuc != NULL)
	{
		delete(buttonCalSuc);
		buttonCalSuc = NULL;
	}
	if(buttonOk != NULL)
	{
		delete(buttonOk);
		buttonOk = NULL;
	}
	if(mensajeSuccess != NULL)
	{
		delete(mensajeSuccess);
		mensajeSuccess = NULL;
	}
}

