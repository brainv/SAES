/**
 * @file	saes-menu-option-type.h
 *
 * @brief	Declares the SAES menu option type class.
 */

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

#ifndef _SAES_MENU_OPTION_TYPE_H_
#define _SAES_MENU_OPTION_TYPE_H_

namespace Smartmatic
{
	namespace SAES
	{
		namespace Functionality
		{
			namespace MenuType
			{
				enum SaesMenuOptionType
				{
					Menu,
					MOpenElectionFunctionality,
					MCloseElectionFunctionality,
					MDiagnosisFunctionality,
					MSCReaderDiagnosisFunctionality,
					MPrinterDiagnosisFunctionality,
					MAlarmBoxDiagnosisFunctionality,
					MCalibrationDiagnosisFunctionality,
					MBrightnessDiagnosisFunctionality,
					MBarcodeDiagnosisFunctionality,
					MAllDiagnosisFunctionality,
					MFlashDiagnosisFunctionality,
					MChangeHourFunctionality,
					MCardGeneratorFunctionality,
					MAssistedCardGeneratorFunctionality,
					MRecoveryCardGeneratorFunctionality,
					MVotingMachineInstallationFunctionality,
					MVoteProcessDemoFunctionality,
					MPrintPreviewFunctionality,
					MChangeLanguageFunctionality,
					MIncidentReportFunctionality,
					MStatisticsReportFunctionality,
					MVotingExperienceValidationFunctionality,
					MPollWorkerRegisterFunctionality,
					MCloseVotationFunctionality,
					MVoteConsolidationFunctionality,
					MRegisterPresidentNotesFunctionality,
					MReportPrintingFunctionality,
					MLogReportFunctionality,
					MShutdownMachine,
					MFillAssistedActivationInfo,
					MActivationConsolidation,
					VOTING_FOR_DISABLED, ///< voting for disabled
					POLICE_NOTES, ///< police notes
					DATA_UTILS_VALIDATOR ///< data utils validator
				};
			}
		}
	}
}

#endif // _SAES_MENU_OPTION_TYPE_H_
