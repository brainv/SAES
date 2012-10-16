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

#include "functionality-initiator.h"
#include "Functionalities/saes-functionality-manager.h"
#include "Functionalities/close-election-functionality.h"
#include "Functionalities/open-election-functionality.h"
#include "Functionalities/diagnosis-functionality.h"
#include "Functionalities/alarm-box-diagnosis-functionality.h"
#include "Functionalities/printer-diagnosis-functionality.h"
#include "Functionalities/s-c-reader-diagnosis-functionality.h"
#include "Functionalities/calibration-diagnosis-functionality.h"
#include "Functionalities/brightness-diagnosis-functionality.h"
#include "Functionalities/barcode-diagnosis-functionality.h"
#include "Functionalities/all-diagnosis-functionality.h"
#include "Functionalities/flash-diagnosis-functionality.h"
#include "Functionalities/change-hour-functionality.h"
#include "Functionalities/card-generator-functionality.h"
#include "Functionalities/assisted-card-generator-functionality.h"
#include "Functionalities/recovery-card-generator-functionality.h"
#include "Functionalities/change-language-functionality.h"
#include "Functionalities/voting-machine-installation-functionality.h"
#include "Functionalities/vote-demo-functionality.h"
#include "Functionalities/print-preview-functionality.h"
#include "Functionalities/incident-report-functionality.h"
#include "Functionalities/statistics-report-functionality.h"
#include "Functionalities/voting-experience-validation-functionality.h"
#include "Functionalities/poll-worker-register-functionality.h"
#include "Functionalities/close-votation-functionality.h"
#include "Functionalities/register-president-notes-functionality.h"
#include "Functionalities/vote-consolidation-functionality.h"
#include "Functionalities/ReportPrintingFunctionality.h"
#include "Functionalities/LogReportFunctionality.h"
#include "Functionalities/ShutdownMachineFunctionality.h"
#include "Functionalities/FillAssistedActivationInfoFunctionality.h"
#include "Functionalities/ActivationConsolidationFunctionality.h"
#include "Functionalities/VotingForDisabledFunctionality.hxx"
#include "Functionalities/PoliceNotesFunctionality.hxx"
#include "Functionalities/DataUtilsValidatorFunctionality.hxx"

using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Functionality;

void FunctionalityInitiator::Register()
{
	Smartmatic::SAES::GUI::Functionality::DiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::OpenElectionFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::CloseElectionFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::AlarmBoxDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::SCReaderDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::CalibrationDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::BrightnessDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::BarcodeDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::AllDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::FlashDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::ChangeHourFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::CardGeneratorFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::AssistedCardGeneratorFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::RecoveryCardGeneratorFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::ChangeLanguageFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::VotingMachineInstallationFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::VoteProcessDemoFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::PrintPreviewFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::IncidentReportFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::StatisticsReportFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::VotingExperienceValidationFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::PollWorkerRegisterFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::VoteConsolidationFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::CloseVotationFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::ReportPrintingFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::RegisterPresidentNotesFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::LogReportFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::PrinterDiagnosisFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::ShutdownMachineFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::FillAssistedActivationInfoFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::ActivationConsolidationFunctionality::Current()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::VotingForDisabledFunctionality::getInstance()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::PoliceNotesFunctionality::getInstance()->Register(SaesFunctionalityManager::Current());
	Smartmatic::SAES::GUI::Functionality::DataUtilsValidatorFunctionality::getInstance()->Register(SaesFunctionalityManager::Current());
}

