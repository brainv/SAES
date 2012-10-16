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

#include "brightness-diagnosis-widget.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Configuration/label-configuration.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Devices/p168-a-device.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <queue>

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
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Voting;	
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation;

ISMTTLog* BrightnessDiagnosisWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget",GETTEXT_PACKAGE);

BrightnessDiagnosisWidget::BrightnessDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
: BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::ScreenContrast, hasOk,hasCancel,hasMessage,showButtons)
{
	framePrincipal = NULL;
	bottomBox = NULL;
	label1 = NULL;
	label2 = NULL;
	label3 = NULL;
	label4 = NULL;
	mensaje = NULL;
	buttonOk = NULL;
	buttonCalibrate = NULL;
	buttonMas = NULL;
	buttonMenos = NULL;
	frameBrillo = NULL;
	buttonClose = NULL;
	labelMas = NULL;
	labelMenos = NULL;
	hscale = NULL;
	adjustment = NULL;
}

BrightnessDiagnosisWidget::~BrightnessDiagnosisWidget()
{
	deleteElement();
}

void BrightnessDiagnosisWidget::deleteElement()
{
	if(framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(bottomBox != NULL)
	{
		delete(bottomBox);
		bottomBox = NULL;
	}
	if(label1 != NULL)
	{
		delete(label1);
		label1 = NULL;
	}
	if(label2 != NULL)
	{
		delete(label2);
		label2 = NULL;
	}
	if(label3 != NULL)
	{
		delete(label3);
		label3 = NULL;
	}
	if(label4 != NULL)
	{
		delete(label4);
		label4 = NULL;
	}
	if(mensaje != NULL)
	{
		delete(mensaje);
		mensaje = NULL;
	}
	if(buttonOk != NULL)
	{
		delete(buttonOk);
		buttonOk = NULL;
	}
	if(buttonCalibrate != NULL)
	{
		delete(buttonCalibrate);
		buttonCalibrate = NULL;
	}
	if(buttonMas != NULL)
	{
		delete(buttonMas);
		buttonMas = NULL;
	}
	if(buttonMenos != NULL)
	{
		delete(buttonMenos);
		buttonMenos = NULL;
	}
	if(frameBrillo != NULL)
	{
		delete(frameBrillo);
		frameBrillo = NULL;
	}
	if(buttonClose != NULL)
	{
		delete(buttonClose);
		buttonClose = NULL;
	}
	if(labelMas != NULL)
	{
		delete(labelMas);
		labelMas = NULL;
	}
	if(labelMenos != NULL)
	{
		delete(labelMenos);
		labelMenos = NULL;
	}
	if(hscale != NULL)
	{
		delete(hscale);
		hscale = NULL;
	}
	if(adjustment != NULL)
	{
		delete(adjustment);
		adjustment = NULL;
	}
}

void BrightnessDiagnosisWidget::Initialize()
{
	try
	{
		builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/show_brightness.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - BrightnessDiagnosisWidget Initialize");
	}

	builder->get_widget("frame",framePrincipal);
	builder->get_widget("vbox",bottomBox);
	builder->get_widget("label1",label1);
	builder->get_widget("label2",label2);
	builder->get_widget("label3",label3);
	builder->get_widget("label4",label4);
	builder->get_widget("mensaje",mensaje);
	builder->get_widget_derived("buttonOk",buttonOk);
	builder->get_widget_derived("buttonCal",buttonCalibrate);


	label1->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.ReadHere"));
	label2->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.ReadHere"));
	label3->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.ReadHere"));
	label4->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.ReadHere"));
	buttonOk->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.Ok"));
	buttonCalibrate->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.Calibrate"));
	buttonOk->set_sensitive (true);
	buttonOk->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	buttonCalibrate->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	mensaje->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.AskForStatusLabelsShown"));
	Pango::FontDescription font = mensaje->get_style()->get_font();
	font.set_size(16*Pango::SCALE);
	mensaje->modify_font(font);

	connOk = buttonOk->signal_clicked().connect(sigc::mem_fun(this, &BrightnessDiagnosisWidget::on_buttonOk_clicked));
	connCalibrate = buttonCalibrate->signal_clicked().connect(sigc::mem_fun(this, &BrightnessDiagnosisWidget::on_buttonCalibrate_clicked));
	setDiagnosticFrame(*framePrincipal);
};

void BrightnessDiagnosisWidget::GetFrameCalibrarBrillo()
{
	try
	{
		builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/calibrate_brightness.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	if(frameBrillo)
		delete frameBrillo;
	if(labelMas)
		delete labelMas;
	if(labelMenos)
		delete labelMenos;
	if(buttonClose)
		delete buttonClose;
	if(hscale)
		delete hscale;
	if(buttonMas)
		delete buttonMas;
	if(buttonMenos)
		delete buttonMenos;

	builder->get_widget("frame1",frameBrillo);
	builder->get_widget("labelMas",labelMas);
	builder->get_widget("labelMenos",labelMenos);
	builder->get_widget_derived("buttonClose",buttonClose);
	builder->get_widget("hscale",hscale);
	builder->get_widget_derived("buttonMas",buttonMas);
	builder->get_widget_derived("buttonMenos",buttonMenos);
	buttonMenos->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.LessBright"));
	buttonMas->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.MoreBright"));

	labelMas->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.More"));
	labelMenos->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.Less"));
	buttonClose->set_label(_("Smartmatic.SAES.GUI.Widgets.BrightnessDiagnosisWidget.Close"));

	framePrincipal->remove();
	framePrincipal->add(*frameBrillo);
	if(brightSelected < 0 || brightSelected > 16)
	{
		brightSelected = 8;
	}

	if (adjustment) delete adjustment;
	adjustment = new Gtk::Adjustment(brightSelected, 0, 16);
	hscale->set_adjustment(*adjustment);
	hscale->set_digits(0);
	connAdjustment = adjustment->signal_value_changed().connect(sigc::mem_fun(*this,&BrightnessDiagnosisWidget::on_adjustment_value_changed));
	buttonMenos->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	buttonMas->SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	connMinus = buttonMenos->signal_clicked().connect(sigc::mem_fun(this, &BrightnessDiagnosisWidget::on_buttonMinus_clicked));
	connPlus = buttonMas->signal_clicked().connect(sigc::mem_fun(this, &BrightnessDiagnosisWidget::on_buttonPlus_clicked));
	buttonClose->signal_clicked().connect(sigc::mem_fun(this, &BrightnessDiagnosisWidget::on_buttonClose_clicked));
}

void BrightnessDiagnosisWidget::on_buttonMinus_clicked()
{
	if(adjustment->get_value() >0)
	{
		adjustment->set_value(adjustment->get_value() - 1);

		buttonMenos->set_sensitive(false);
		sigc::slot<bool> my_slot_minus = sigc::bind(sigc::mem_fun(*this,
			&BrightnessDiagnosisWidget::WaitButtonMinusOff), 0);
		int time = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getTimeDelayButtons();
		connMinusOff = Glib::signal_timeout().connect(my_slot_minus,time);
	}
}

bool BrightnessDiagnosisWidget::WaitButtonMinusOff(int time_num)
{
	buttonMenos->set_sensitive(true);
	connMinusOff.disconnect();
	return false;
}

void BrightnessDiagnosisWidget::on_buttonPlus_clicked()
{
	if(adjustment->get_value() <16)
	{
		adjustment->set_value(adjustment->get_value() + 1);

		buttonMas->set_sensitive(false);
		sigc::slot<bool> my_slot_plus = sigc::bind(sigc::mem_fun(*this,
			&BrightnessDiagnosisWidget::WaitButtonPlusOff), 0);
		int time = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getTimeDelayButtons();
		BrightnessDiagnosisWidget::connPlusOff = Glib::signal_timeout().connect(my_slot_plus,time);
	}
}

bool BrightnessDiagnosisWidget::WaitButtonPlusOff(int time_num)
{
	buttonMas->set_sensitive(true);
	connPlusOff.disconnect();
	return false;
}

void BrightnessDiagnosisWidget::on_adjustment_value_changed()
{
	brightSelected = adjustment->get_value();
	if(brightSelected == 0)
	{
			P168ADevice::Current()->setBrightness(0);
	}
	else
	{
		P168ADevice::Current()->setBrightness((brightSelected*16)-1);
	}
}


void BrightnessDiagnosisWidget::on_buttonOk_clicked()
{
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::ScreenContrast, OperationStatus::Ok);
	buttonOk->set_sensitive (false);
	signalOk_detected.emit();
}

void BrightnessDiagnosisWidget::on_buttonCalibrate_clicked()
{
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::ScreenContrast, OperationStatus::Error);
	GetFrameCalibrarBrillo();
}

void BrightnessDiagnosisWidget::getBacktoInitialFrame()
{
	connAdjustment.disconnect();
	connPlus.disconnect();
	connMinus.disconnect();
	framePrincipal->remove();
	framePrincipal->add(*bottomBox);
	framePrincipal->set_visible(true);
}

void BrightnessDiagnosisWidget::on_buttonClose_clicked()
{
	getBacktoInitialFrame();
}

void BrightnessDiagnosisWidget::Dispose()
{
	connOk.disconnect();
	connCalibrate.disconnect();
};

