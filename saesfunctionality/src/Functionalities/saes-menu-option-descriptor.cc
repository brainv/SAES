/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "saes-menu-option-descriptor.h"

using namespace Smartmatic::SAES::Functionality;

SaesMenuOptionDescriptor::SaesMenuOptionDescriptor(MenuType::SaesMenuOptionType type, bool isMenuItem)
{
	isMenu = isMenuItem;
	menuDescriptor.clear();
	switch(type)
	{
		case MenuType::MOpenElectionFunctionality:
			menuDescriptor.append("SAES:OpenElectionFunctionality");
			break;
		case MenuType::MCloseElectionFunctionality:
			menuDescriptor.append("SAES:CloseElectionFunctionality");
			break;
		case MenuType::MDiagnosisFunctionality:
			menuDescriptor.append("SAES:DiagnosisFunctionality");
			break;
		case MenuType::MSCReaderDiagnosisFunctionality:
			menuDescriptor.append("SAES:SCReaderDiagnosisFunctionality");
			break;
		case MenuType::MPrinterDiagnosisFunctionality:
			menuDescriptor.append("SAES:PrinterDiagnosisFunctionality");
			break;
		case MenuType::MAlarmBoxDiagnosisFunctionality:
			menuDescriptor.append("SAES:AlarmBoxDiagnosisFunctionality");
			break;
		case MenuType::MCalibrationDiagnosisFunctionality:
			menuDescriptor.append("SAES:CalibrationDiagnosisFunctionality");
			break;
		case MenuType::MBrightnessDiagnosisFunctionality:
			menuDescriptor.append("SAES:BrightnessDiagnosisFunctionality");
			break;
		case MenuType::MBarcodeDiagnosisFunctionality:
			menuDescriptor.append("SAES:BarcodeDiagnosisFunctionality");
			break;
		case MenuType::MAllDiagnosisFunctionality:
			menuDescriptor.append("SAES:AllDiagnosisFunctionality");
			break;
		case MenuType::MFlashDiagnosisFunctionality:
			menuDescriptor.append("SAES:FlashDiagnosisFunctionality");
			break;
		case MenuType::MChangeHourFunctionality:
			menuDescriptor.append("SAES:ChangeHourFunctionality");
			break;
		case MenuType::MCardGeneratorFunctionality:
			menuDescriptor.append("SAES:CardGeneratorFunctionality");
			break;
		case MenuType::MAssistedCardGeneratorFunctionality:
			menuDescriptor.append("SAES:AssistedCardGeneratorFunctionality");
			break;
		case MenuType::MRecoveryCardGeneratorFunctionality:
			menuDescriptor.append("SAES:RecoveryCardGeneratorFunctionality");
			break;
		case MenuType::MVotingMachineInstallationFunctionality:
			menuDescriptor.append("SAES:VotingMachineInstallationFunctionality");
			break;	
		case MenuType::MChangeLanguageFunctionality:
			menuDescriptor.append("SAES:ChangeLanguageFunctionality");
			break;
		case MenuType::MVoteProcessDemoFunctionality:
			menuDescriptor.append("SAES:VoteProcessDemoFunctionality");
			break;	
		case MenuType::MPrintPreviewFunctionality:
			menuDescriptor.append("SAES:PrintPreviewFunctionality");
			break;
		case MenuType::MIncidentReportFunctionality:
			menuDescriptor.append("SAES:IncidentReportFunctionality");
			break;
		case MenuType::MStatisticsReportFunctionality:
			menuDescriptor.append("SAES:StatisticsReportFunctionality");
			break;
		case MenuType::MVotingExperienceValidationFunctionality:
			menuDescriptor.append("SAES:VotingExperienceValidationConfiguration");
			break;
		case MenuType::MPollWorkerRegisterFunctionality:
			menuDescriptor.append("SAES:PollWorkerRegisterFunctionality");
			break;
		case MenuType::MReportPrintingFunctionality:
			menuDescriptor.append("SAES:ReportPrintingFunctionality");
			break;
		case MenuType::MCloseVotationFunctionality:
			menuDescriptor.append("SAES:CloseVotationFunctionality");
			break;
		case MenuType::MRegisterPresidentNotesFunctionality:
			menuDescriptor.append("SAES:RegisterPresidentNotesFunctionality");
			break;
		case MenuType::MVoteConsolidationFunctionality:
			menuDescriptor.append("SAES:VoteConsolidationFunctionality");
			break;
		case MenuType::MLogReportFunctionality:
			menuDescriptor.append("SAES:LogReportFunctionality");
			break;
		case MenuType::MShutdownMachine:
			menuDescriptor.append("SAES:ShutdownMachineMaFunctionality");
			break;
		case MenuType::Menu:
			menuDescriptor.append("Menu");
			break;
		case MenuType::MFillAssistedActivationInfo:
			menuDescriptor.append("SAES:FillAssistedActivationInfoFunctionality");
			break;
		case MenuType::MActivationConsolidation:
			menuDescriptor.append("SAES:ActivationConsolidationFunctionality");
			break;
		case MenuType::VOTING_FOR_DISABLED:
			menuDescriptor.append("SAES:VotingForDisabledFunctionality");
			break;
		case MenuType::POLICE_NOTES:
			menuDescriptor.append("SAES:PoliceNotesFunctionality");
			break;
		case MenuType::DATA_UTILS_VALIDATOR:
			menuDescriptor.append("SAES:DataUtilsValidatorFunctionality");
			break;
	}
	setMenuOption(menuDescriptor);
}

MenuType::SaesMenuOptionType SaesMenuOptionDescriptor::getSaesMenuOptionType(std::string typeString)
{
	MenuType::SaesMenuOptionType type = MenuType::MShutdownMachine;

	if(typeString.compare("SAES:OpenElectionFunctionality" ) == 0)
		type = MenuType::MOpenElectionFunctionality;
	else if(typeString.compare("SAES:CloseElectionFunctionality") == 0)
		type = MenuType::MCloseElectionFunctionality;
	else if(typeString.compare("SAES:DiagnosisFunctionality") == 0)
		type = MenuType::MDiagnosisFunctionality;
	else if(typeString.compare("SAES:SCReaderDiagnosisFunctionality") == 0)
		type = MenuType::MSCReaderDiagnosisFunctionality;
	else if(typeString.compare("SAES:PrinterDiagnosisFunctionality") == 0)
		type = MenuType::MPrinterDiagnosisFunctionality;
	else if(typeString.compare("SAES:AlarmBoxDiagnosisFunctionality") == 0)
		type = MenuType::MAlarmBoxDiagnosisFunctionality;
	else if(typeString.compare("SAES:CalibrationDiagnosisFunctionality") == 0)
		type = MenuType::MCalibrationDiagnosisFunctionality;
	else if(typeString.compare("SAES:BrightnessDiagnosisFunctionality") == 0)
		type = MenuType::MBrightnessDiagnosisFunctionality;
	else if(typeString.compare("SAES:BarcodeDiagnosisFunctionality") == 0)
		type = MenuType::MBarcodeDiagnosisFunctionality;
	else if(typeString.compare("SAES:AllDiagnosisFunctionality") == 0)
		type = MenuType::MAllDiagnosisFunctionality;
	else if(typeString.compare("SAES:FlashDiagnosisFunctionality") == 0)
		type = MenuType::MFlashDiagnosisFunctionality;
	else if(typeString.compare("SAES:ChangeHourFunctionality") == 0)
		type = MenuType::MChangeHourFunctionality;
	else if(typeString.compare("SAES:CardGeneratorFunctionality") == 0)
		type = MenuType::MCardGeneratorFunctionality;
	else if(typeString.compare("SAES:AssistedCardGeneratorFunctionality") == 0)
		type = MenuType::MAssistedCardGeneratorFunctionality;
	else if(typeString.compare("SAES:RecoveryCardGeneratorFunctionality") == 0)
		type = MenuType::MRecoveryCardGeneratorFunctionality;
	else if(typeString.compare("SAES:VotingMachineInstallationFunctionality") == 0)
		type = MenuType::MVotingMachineInstallationFunctionality;
	else if(typeString.compare("SAES:ChangeLanguageFunctionality") == 0)
		type = MenuType::MChangeLanguageFunctionality;
	else if(typeString.compare("SAES:VoteProcessDemoFunctionality") == 0)
		type = MenuType::MVoteProcessDemoFunctionality;
	else if(typeString.compare("SAES:PrintPreviewFunctionality") == 0)
		type = MenuType::MPrintPreviewFunctionality;
	else if(typeString.compare("SAES:IncidentReportFunctionality") == 0)
		type = MenuType::MIncidentReportFunctionality;
	else if(typeString.compare("SAES:StatisticsReportFunctionality") == 0)
		type = MenuType::MStatisticsReportFunctionality;
	else if(typeString.compare("SAES:VotingExperienceValidationConfiguration") == 0)
		type = MenuType::MVotingExperienceValidationFunctionality;
	else if(typeString.compare("SAES:PollWorkerRegisterFunctionality") == 0)
		type = MenuType::MPollWorkerRegisterFunctionality;
	else if(typeString.compare("SAES:ReportPrintingFunctionality") == 0)
		type = MenuType::MReportPrintingFunctionality;
	else if(typeString.compare("SAES:CloseVotationFunctionality") == 0)
		type = MenuType::MCloseVotationFunctionality;
	else if(typeString.compare("SAES:RegisterPresidentNotesFunctionality") == 0)
		type = MenuType::MRegisterPresidentNotesFunctionality;
	else if(typeString.compare("SAES:VoteConsolidationFunctionality") == 0)
		type = MenuType::MVoteConsolidationFunctionality;
	else if(typeString.compare("SAES:LogReportFunctionality") == 0)
		type = MenuType::MLogReportFunctionality;
	else if(typeString.compare("SAES:Menu") == 0)
		type = MenuType::Menu;
	else if(typeString.compare("SAES:ShutdownMachineMaFunctionality") == 0)
		type = MenuType::MShutdownMachine;
	else if(typeString.compare("SAES:FillAssistedActivationInfoFunctionality") == 0)
		type = MenuType::MFillAssistedActivationInfo;
	else if(typeString.compare("SAES:ActivationConsolidationFunctionality") == 0)
		type = MenuType::MActivationConsolidation;
	else if(typeString.compare("SAES:VotingForDisabledFunctionality") == 0)
		type = MenuType::VOTING_FOR_DISABLED;
	else if(typeString.compare("SAES:PoliceNotesFunctionality") == 0)
		type = MenuType::POLICE_NOTES;
	else if(typeString.compare("SAES:DataUtilsValidatorFunctionality") == 0)
		type = MenuType::DATA_UTILS_VALIDATOR;

	return type;
}

