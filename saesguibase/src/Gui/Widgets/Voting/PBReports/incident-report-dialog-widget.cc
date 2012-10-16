/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#include "incident-report-dialog-widget.h"
#include "incident-report-tree-view.h"
#include <iostream>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Voting/PBReports/id-card-info-schema.hxx>

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
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;

IncidentReportDialogWidget::IncidentReportDialogWidget()
{
	Initialize();
}

IncidentReportDialogWidget::IncidentReportDialogWidget(Report report)
{
	Initialize();
	SetParams(report);
}

IncidentReportDialogWidget::~IncidentReportDialogWidget()
{
	if (idWidget)
	{
		delete idWidget;
		idWidget = NULL;
	}
	if (descLabel)
	{
		delete descLabel;
		descLabel = NULL;
	}
	if (nameTechLabel)
	{
		delete nameTechLabel;
		nameTechLabel = NULL;
	}
	if (lastnameTechLabel)
	{
		delete lastnameTechLabel;
		lastnameTechLabel = NULL;
	}
	if (activityTechLabel)
	{
		delete activityTechLabel;
		activityTechLabel = NULL;
	}
	if (additionalLabel)
	{
		delete additionalLabel;
		additionalLabel = NULL;
	}
	if (notificationDateLabel)
	{
		delete notificationDateLabel;
		notificationDateLabel = NULL;
	}
	if (personalDateLabel)
	{
		delete personalDateLabel;
		personalDateLabel = NULL;
	}
	if (incidentDateLabel)
	{
		delete incidentDateLabel;
		incidentDateLabel = NULL;
	}
	if (descEntry)
	{
		delete descEntry;
		descEntry = NULL;
	}
	if (nameTechEntry)
	{
		delete nameTechEntry;
		nameTechEntry = NULL;
	}
	if (activityTechEntry)
	{
		delete activityTechEntry;
		activityTechEntry = NULL;
	}
	if (lastnameTechEntry)
	{
		delete lastnameTechEntry;
		lastnameTechEntry = NULL;
	}
	if (notificationDateEntry)
	{
		delete notificationDateEntry;
		notificationDateEntry = NULL;
	}
	if (personalDateEntry)
	{
		delete personalDateEntry;
		personalDateEntry = NULL;
	}
	if (incidentDateEntry)
	{
		delete incidentDateEntry;
		incidentDateEntry = NULL;
	}
	if (additionalText)
	{
		delete additionalText;
		additionalText = NULL;
	}
	if (alignID)
	{
		delete alignID;
		alignID = NULL;
	}
}

void IncidentReportDialogWidget::InitializeBEID()
{
	if(idWidget)
	{
		idWidget->dispose();
		idWidget->initialize();
		idWidget->setIDConfig(SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getIncidentReport());
	}
}

void IncidentReportDialogWidget::Initialize()
{
	descLabel = NULL;
	nameTechLabel = NULL;
	lastnameTechLabel = NULL;
	activityTechLabel = NULL;
	additionalLabel = NULL;
	notificationDateLabel = NULL;
	personalDateLabel = NULL;
	incidentDateLabel = NULL;
	descEntry = NULL;
	nameTechEntry = NULL;
	activityTechEntry = NULL;
	lastnameTechEntry = NULL;
	notificationDateEntry = NULL;
	personalDateEntry = NULL;
	incidentDateEntry = NULL;
	additionalText = NULL;
	idWidget = NULL;
	alignID = NULL;

	customCode = "";
	complete = false;

	string sDescription = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.Description");
	string sIncidentDate = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.IncidentDate");
	string sTechnicians = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.Technicians");
	string sTechniciansLast = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.TechniciansLast");
	string sActivity = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.Activity");
	string sAdditionalInfo = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.AdditionalInfo");
	string sPersonalArrival = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.PersonalArrival");
	string sIncidentSolution = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportDialogWidget.IncidentSolution");

	bool  newLayout = SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getShowID();
	
	if(!newLayout)
	{
		//TODO configuration label sizes
		int labelWidth = -1;
		int labelAlign = 0;

		descLabel = new Label(sDescription);
		descLabel->set_size_request(labelWidth,-1);
		descLabel->set_alignment(labelAlign, 0.5);

		nameTechLabel = new Label(sTechnicians);
		nameTechLabel->set_size_request(labelWidth,-1);
		nameTechLabel->set_alignment(labelAlign, 0.5);

		lastnameTechLabel = new Label(sTechniciansLast);
		lastnameTechLabel->set_size_request(labelWidth,-1);
		lastnameTechLabel->set_alignment(labelAlign, 0.5);

		activityTechLabel = new Label(sActivity);
		activityTechLabel->set_size_request(labelWidth,-1);
		activityTechLabel->set_alignment(labelAlign, 0.5);

		additionalLabel = new Label(sAdditionalInfo);
		additionalLabel->set_size_request(labelWidth,-1);
		additionalLabel->set_alignment(labelAlign, 0.5);

		notificationDateLabel = new Label(sIncidentDate);
		notificationDateLabel->set_size_request(labelWidth,-1);
		notificationDateLabel->set_alignment(labelAlign, 0.5);

		personalDateLabel = new Label(sPersonalArrival);
		personalDateLabel->set_size_request(labelWidth,-1);
		personalDateLabel->set_alignment(labelAlign, 0.5);

		incidentDateLabel = new Label(sIncidentSolution);
		incidentDateLabel->set_size_request(labelWidth,-1);
		incidentDateLabel->set_alignment(labelAlign, 0.5);

		descEntry = new SmartmaticEntry();
		descEntry->set_text("");

		nameTechEntry = new SmartmaticEntry();
		nameTechEntry->set_text("");

		lastnameTechEntry = new SmartmaticEntry();
		lastnameTechEntry->set_text("");

		activityTechEntry = new SmartmaticEntry();
		activityTechEntry->set_text("");

		notificationDateEntry = new SmartmaticEntryDateTime(false, 50, 5);
	
		personalDateEntry = new SmartmaticEntryDateTime(false, 50, 5);

		incidentDateEntry = new SmartmaticEntryDateTime(false, 50, 5);
	
		additionalText = new SmartmaticTextView();
		additionalText->set_size_request(200, 60);

		AttachOptions xOption = FILL;
		AttachOptions yOption = FILL|EXPAND;
		int xpad = 0;
		int ypad = 0;

		attach(*descLabel, 0,1,0,1, xOption, yOption, xpad, ypad);
		attach(*activityTechLabel, 0,1,1,2, xOption, yOption, xpad, ypad);
		attach(*additionalLabel, 0,1,2,4, xOption, yOption, xpad, ypad);
		attach(*notificationDateLabel, 0,1,4,5, xOption, yOption, xpad, ypad);
		attach(*personalDateLabel, 0,1,5,6, xOption, yOption, xpad, ypad);
		attach(*incidentDateLabel, 0,1,6,7, xOption, yOption, xpad, ypad);

		attach(*descEntry, 1,2,0,1);
		attach(*activityTechEntry, 1,2,1,2);
		attach(*additionalText, 1,2,2,4);
		attach(*notificationDateEntry, 1,2,4,5);
		attach(*personalDateEntry, 1,2,5,6);
		attach(*incidentDateEntry, 1,2,6,7);

		idWidget = new IDCardWidget(sTechnicians,"",false);
		idWidget->HideAcceptTitle();
		idWidget->HideConfirmationBeid();

		alignID = new Alignment();
		alignID->set(0.0,0.5,0,0);
		alignID->add(*idWidget);

		attach(*alignID, 0,4,8,10);

		set_col_spacings(10);
		set_row_spacings(10);

		show_all_children();
	}
	else
	{
		//TODO configuration label sizes
		int labelWidth = -1;
		int labelAlign = 0;

		descLabel = new Label(sDescription);
		descLabel->set_size_request(labelWidth,-1);
		descLabel->set_alignment(labelAlign, 0.5);

		nameTechLabel = new Label(sTechnicians);
		nameTechLabel->set_size_request(labelWidth,-1);
		nameTechLabel->set_alignment(labelAlign, 0.5);

		activityTechLabel = new Label(sActivity);
		activityTechLabel->set_size_request(labelWidth,-1);
		activityTechLabel->set_alignment(labelAlign, 0.5);

		additionalLabel = new Label(sAdditionalInfo);
		additionalLabel->set_size_request(labelWidth,-1);
		additionalLabel->set_alignment(0.5, 0.5);

		notificationDateLabel = new Label(sIncidentDate);
		notificationDateLabel->set_size_request(labelWidth,-1);
		notificationDateLabel->set_alignment(labelAlign, 0.5);

		personalDateLabel = new Label(sPersonalArrival);
		personalDateLabel->set_size_request(labelWidth,-1);
		personalDateLabel->set_alignment(labelAlign, 0.5);

		incidentDateLabel = new Label(sIncidentSolution);
		incidentDateLabel->set_size_request(labelWidth,-1);
		incidentDateLabel->set_alignment(labelAlign, 0.5);

		descEntry = new SmartmaticEntry();
		descEntry->set_text("");
		descEntry->set_size_request(250, -1);

		nameTechEntry = new SmartmaticEntry();

		activityTechEntry = new SmartmaticEntry();
		activityTechEntry->set_text("");

		notificationDateEntry = new SmartmaticEntryDateTime(false, 40, 3);
	
		personalDateEntry = new SmartmaticEntryDateTime(false, 40, 3);

		incidentDateEntry = new SmartmaticEntryDateTime(false, 40, 3);
	
		additionalText = new Smartmatic::GUI::Widgets::SmartmaticTextView();

		AttachOptions xOption = FILL;
		AttachOptions yOption = FILL|EXPAND;
		int xpad = 0;
		int ypad = 0;

		attach(*descLabel, 0,1,0,1, xOption, yOption, xpad, ypad);
		attach(*activityTechLabel, 0,1,1,2, xOption, yOption, xpad, ypad);
		attach(*additionalLabel, 0,2,2,3, xOption, yOption, xpad, ypad);

		attach(*descEntry, 1,2,0,1);
		attach(*activityTechEntry, 1,2,1,2);
		//attach(*textFrame, 0,2,3,6);

		
		attach(*notificationDateLabel, 2,3,0,1, xOption, yOption, xpad, ypad);  
		attach(*personalDateLabel, 2,3,1,2, xOption, yOption, xpad, ypad);
		attach(*incidentDateLabel, 2,3,2,3, xOption, yOption, xpad, ypad);

		attach(*notificationDateEntry, 3,4,0,1);
		attach(*personalDateEntry, 3,4,1,2);
		attach(*incidentDateEntry, 3,4,2,3);

		set_col_spacings(20);
		set_row_spacings(5);

		idWidget = new IDCardWidget(sTechnicians,"",false);
		idWidget->HideAcceptTitle();

		alignID = new Alignment();
		alignID->set_padding(10, 50, 10, 10);
		alignID->add(*idWidget);

		attach(*alignID, 0, 4, 5, 12, SHRINK, SHRINK);
		
		show_all_children();
	}
}

void IncidentReportDialogWidget::SetParams(Report report)
{
	descEntry->set_text(report.getDescription());

	struct tm structtm;
	
	structtm = IncidentReportTreeView::GetStructTmFromDateTime(report.getNotificationDate());
	if(structtm.tm_sec == 0 && structtm.tm_min == 0 && structtm.tm_hour == 0 &&
	   structtm.tm_mday == 0 && structtm.tm_mon == 0 && structtm.tm_year == 0)
		notificationDateEntry->Clear();
	else
		notificationDateEntry->SetTime(structtm);

	nameTechEntry->set_text(report.getNamesOfTechnicians().getFirstName());

	if(idWidget)
	{
		string firstName = report.getNamesOfTechnicians().getFirstName();
		string lastName = report.getNamesOfTechnicians().getSurname();
		idWidget->SetNames(firstName, lastName);
	}

	structtm = IncidentReportTreeView::GetStructTmFromDateTime(report.getPersonalArrivalDate());
	if(structtm.tm_sec == 0 && structtm.tm_min == 0 && structtm.tm_hour == 0 &&
	   structtm.tm_mday == 0 && structtm.tm_mon == 0 && structtm.tm_year == 0)
		personalDateEntry->Clear();
	else
		personalDateEntry->SetTime(structtm);

	activityTechEntry->set_text(report.getActivityOfTechnicians());

	if(report.getAdditionalObservations())
	{
		additionalText->setText(report.getAdditionalObservations().get());
	}

	structtm = IncidentReportTreeView::GetStructTmFromDateTime(report.getIncidentSolutionDate());

	if(structtm.tm_sec == 0 && structtm.tm_min == 0 && structtm.tm_hour == 0 &&
	   structtm.tm_mday == 0 && structtm.tm_mon == 0 && structtm.tm_year == 0)
	{
		incidentDateEntry->Clear();
	}
	else
	{
		incidentDateEntry->SetTime(structtm);
	}

	customCode = report.getCustom_code();
	
	this->complete = report.getIsComplete();

	SetVisualizeMode(false);
}

void IncidentReportDialogWidget::dispose()
{
	if(idWidget)
	{
		idWidget->dispose();
	}
}

void IncidentReportDialogWidget::GetParams(Report& report)
{
	report.setDescription((string)descEntry->get_text());

	IDCardInfo idCard;
	idCard.setFirstName((string)nameTechEntry->get_text());
	idCard.setSurname(" ");

	if(idWidget)
	{
		string firstName, lastName;
		idWidget->GetNames(firstName, lastName);

		idCard.setFirstName(firstName);
		idCard.setSurname(lastName);
	}

	report.setNamesOfTechnicians(idCard);
	
	report.setActivityOfTechnicians((string)activityTechEntry->get_text());
	
	report.setAdditionalObservations((string)additionalText->getText());

	report.setNotificationDate(
		IncidentReportTreeView::GetDateTimeFomStructTm(notificationDateEntry->GetTime()));
	
	report.setPersonalArrivalDate(
		IncidentReportTreeView::GetDateTimeFomStructTm(personalDateEntry->GetTime()));
	
	report.setIncidentSolutionDate(
		IncidentReportTreeView::GetDateTimeFomStructTm(incidentDateEntry->GetTime()));

	report.setCustom_code(customCode);

	report.setIsComplete(complete);
}

bool IncidentReportDialogWidget::CanBeSaved()
{
	bool returnVariable = true;
	errorInHours = false;

	string s1 = descEntry->get_text();
	struct tm structtm = notificationDateEntry->GetTime();

	if(s1 == "")
	{
		returnVariable = false;
	}
	else if(structtm.tm_sec == 0 && structtm.tm_min == 0 && structtm.tm_hour == 0)
	{
		returnVariable = false;
		errorInHours = true;
	}
	else
	{
		struct tm notification_tm = notificationDateEntry->GetTime();
		struct tm personal_tm = personalDateEntry->GetTime();
		struct tm solution_tm = incidentDateEntry->GetTime();

		returnVariable = returnVariable && CompareTimes(notification_tm, solution_tm);
		returnVariable = returnVariable && CompareTimes(personal_tm, solution_tm);

		if(!returnVariable)
			errorInHours = true;
	}

	return returnVariable;
}

bool IncidentReportDialogWidget::CanBeCompleted()
{
	bool returnVariable = CanBeSaved();
	errorInHours = false;
	if(returnVariable)
	{
		IncidentReportFunctionalityConfiguration::CompleteReportParametersSequence seq = 
			SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getCompleteReportParameters();

		IncidentReportFunctionalityConfiguration::CompleteReportParametersIterator iter;

		for(iter = seq.begin(); iter != seq.end(); iter++)
		{
			switch(*iter)
			{
				case IncidentReportColumn::CONFIGURATION_DESCRIPTION:
				{
					string s1 = descEntry->get_text();
					if(s1 == "")
						returnVariable = false;
				}
					break;
				case IncidentReportColumn::CONFIGURATION_NOTIFICATIONDATE:
				{
					struct tm structtm = notificationDateEntry->GetTime();
					if(structtm.tm_sec == 0 && structtm.tm_min == 0 &&
		                 structtm.tm_hour == 0)
						returnVariable = false;
				}
					break;
				case IncidentReportColumn::CONFIGURATION_NAMESOFTECHNICIANS:
				{
					if(idWidget)
					{
						returnVariable = idWidget->CheckCompleteData();
					}
					else
					{
						string s1 = nameTechEntry->get_text();
						if(s1 == "")
							returnVariable = false;
					}
				}
					break;
				case IncidentReportColumn::CONFIGURATION_ACTIVITYOFTECHNICIANS:
				{
					string s1 = activityTechEntry->get_text();
					if(s1 == "")
						returnVariable = false;
				}
					break;
				case IncidentReportColumn::CONFIGURATION_ADDITIONALOBSERVATIONS:
				{
					string s1 = additionalText->getText();
					if(s1 == "")
						returnVariable = false;
				}
					break;
				case IncidentReportColumn::CONFIGURATION_PERSONALARRIVALDATE:
				{
					struct tm structtm = personalDateEntry->GetTime();
					if(structtm.tm_sec == 0 && structtm.tm_min == 0 &&
		                 structtm.tm_hour == 0)
						returnVariable = false;
				}
					break;
				case IncidentReportColumn::CONFIGURATION_INCIDENTSOLUTIONDATE:
				{
					struct tm structtm = incidentDateEntry->GetTime();
					if(structtm.tm_sec == 0 && structtm.tm_min == 0 &&
		                 structtm.tm_hour == 0)
						returnVariable = false;
				}
					break;
				default:
					break;
			}
		}
		
		if(returnVariable)
		{
			string s1 = descEntry->get_text();
			struct tm structtm = notificationDateEntry->GetTime();

			if(s1 == "" ||  (structtm.tm_sec == 0 && structtm.tm_min == 0 &&
							 structtm.tm_hour == 0))
			{
				returnVariable = false;
			}
			else
			{
				struct tm notification_tm = notificationDateEntry->GetTime();
				struct tm personal_tm = personalDateEntry->GetTime();
				struct tm solution_tm = incidentDateEntry->GetTime();

				returnVariable = returnVariable && CompareTimes(notification_tm, solution_tm);
				returnVariable = returnVariable && CompareTimes(personal_tm, solution_tm);

				if(!returnVariable)
					errorInHours = true;
			}
		}
	}
	return returnVariable;
}

bool IncidentReportDialogWidget::getErrorInHours()
{
	return errorInHours;
}

bool IncidentReportDialogWidget::CompareTimes(struct tm minor, struct tm mayor)
{
	if(mayor.tm_sec == 0 && mayor.tm_min == 0 && mayor.tm_hour == 0)
		return true;

	bool returnVariable = true;

	if(minor.tm_hour > mayor.tm_hour)
	{
		returnVariable = false;
	}
	else if(minor.tm_hour == mayor.tm_hour)
	{
		if(minor.tm_min > mayor.tm_min)
		{
			returnVariable = false;
		}
		else if(minor.tm_min == mayor.tm_min)
		{
			if (minor.tm_sec > mayor.tm_sec)
			{
				returnVariable = false;
			}
		}
	}

	return returnVariable;
}

void IncidentReportDialogWidget::Clean()
{
	descEntry->set_text("");
	
	notificationDateEntry->Clear();
	
	nameTechEntry->set_text("");
	
	personalDateEntry->Clear();
	
	activityTechEntry->set_text("");

	additionalText->setText("");

	incidentDateEntry->Clear();

	if(idWidget)
	{
		idWidget->ClearNames();
		idWidget->setIDConfig(SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getIncidentReport());
	}

	customCode = "";
	
	complete = false;
}

void IncidentReportDialogWidget::CompleteReport(bool complete)
{
	this->complete = complete;	
}

void IncidentReportDialogWidget::SetVisualizeMode(bool visualizeMode)
{
	descEntry->set_sensitive(!visualizeMode);
	descEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	notificationDateEntry->SetSensitive(!visualizeMode);
	
	nameTechEntry->set_sensitive(!visualizeMode);
	nameTechEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	
	personalDateEntry->SetSensitive(!visualizeMode);
	
	activityTechEntry->set_sensitive(!visualizeMode);
	activityTechEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));

	additionalText->set_sensitive(!visualizeMode);

	incidentDateEntry->SetSensitive(!visualizeMode);

	if(idWidget)
	{
		idWidget->SetVisualizeMode(visualizeMode);
	}
}
