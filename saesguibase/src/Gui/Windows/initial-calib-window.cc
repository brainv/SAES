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

#include "initial-calib-window.h"
#include "Functionalities/all-diagnosis-functionality.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <System/Runtime/ProcessLauncher.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///< macro for gettext
#else
#define _(String) (String) ///< macro without gettext
#endif

#define N_(String) (String) ///< macro not translate

using namespace std;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::System::Runtime;

InitialCalibWindow::InitialCalibWindow()
:EmptyWindow(NULL,N_("Smartmatic.SAES.GUI.Windows.InitialCalibWindow.Title"), true, false, true)
{
		int numberOfPoints = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getTouchScreenCalibrationNumberOfPoints();
		stringstream ss;
		ss << numberOfPoints;
		std::string fullCommand("gCal ");
		fullCommand.append(ss.str());
		(void)ProcessLauncher::RunProcessThroughSystem(fullCommand.c_str());

		calibrationWidget = new Smartmatic::SAES::GUI::Widgets::CalibrationDiagnosisWidget("",false, false, false,false,true);
		BuildAutomatic();
		setWidget(calibrationWidget);
};

InitialCalibWindow::~InitialCalibWindow()
{
	if(calibrationWidget != NULL)
	{
		delete(calibrationWidget);
	}

};

void InitialCalibWindow::OnLoad()
{

}

void InitialCalibWindow::BuildAutomatic()
{
	calibrationWidget->Initialize();
	calibrationWidget->signalOk_detected.connect(sigc::mem_fun(*this,&InitialCalibWindow::on_CalibDiagFinished));
	calibrationWidget->signalContinue_detected.connect( sigc::mem_fun(this, &InitialCalibWindow::on_CalibDiagFinished));
}

void InitialCalibWindow::on_CalibDiagFinished()
{
	calibrationWidget->Dispose();
	QuitDialog();
}
