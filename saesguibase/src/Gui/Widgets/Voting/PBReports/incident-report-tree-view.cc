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

#include "incident-report-tree-view.h"
#include <iostream>
#include <sstream>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Voting/PBReports/id-card-info-schema.hxx>
#include <System/Utils/StringUtils.hxx>

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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::Utils;

IncidentReportTreeView::IncidentReportTreeView()
{
	currentCustomCode = "";
	refListStore = ListStore::create(incidentReportTreeModel);

	set_model(refListStore);

	string sDescription = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.Description");
	string sIncidentDate = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.IncidentDate");
	string sTechnicians = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.Technicians");
	string sIncidentSolved = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.IncidentSolved");
	string sActivity = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.Activity");
	string sAdditionalInfo = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.AdditionalInfo");
	string sPersonalArrival = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.PersonalArrival");
	string sIncidentSolution = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportTreeView.IncidentSolution");

	IncidentReportFunctionalityConfiguration::IncidentReportConfigurationSequence seq = 
		SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getIncidentReportConfiguration();

	IncidentReportFunctionalityConfiguration::IncidentReportConfigurationIterator iter;

	for(iter = seq.begin(); iter != seq.end(); iter++)
	{
		TreeViewColumn* column = NULL;

		switch(iter->getIncidentReportColumn())
		{
			case IncidentReportColumn::CONFIGURATION_DESCRIPTION:
				column = new TreeViewColumn(sDescription, incidentReportTreeModel.description);
				break;
			case IncidentReportColumn::CONFIGURATION_NOTIFICATIONDATE:
				column = new TreeViewColumn(sIncidentDate, incidentReportTreeModel.notificationDate);
				break;
			case IncidentReportColumn::CONFIGURATION_NAMESOFTECHNICIANS:
				column = new TreeViewColumn(sTechnicians, incidentReportTreeModel.namesOfTechnicians);
				break;
			case IncidentReportColumn::CONFIGURATION_ACTIVITYOFTECHNICIANS:
				column = new TreeViewColumn(sActivity, incidentReportTreeModel.activityOfTechnicians);
				break;
			case IncidentReportColumn::CONFIGURATION_ADDITIONALOBSERVATIONS:
				column = new TreeViewColumn(sAdditionalInfo, incidentReportTreeModel.additionalObservations);
				break;
			case IncidentReportColumn::CONFIGURATION_PERSONALARRIVALDATE:
				column = new TreeViewColumn(sPersonalArrival, incidentReportTreeModel.personalArrivalDate);
				break;
			case IncidentReportColumn::CONFIGURATION_INCIDENTSOLUTIONDATE:
				column = new TreeViewColumn(sIncidentSolution, incidentReportTreeModel.incidentSolutionDate);
				break;
			case IncidentReportColumn::CONFIGURATION_COMPLETE:
				column = new TreeViewColumn(sIncidentSolved, incidentReportTreeModel.complete);
				break;
			default:
				column = NULL;
				break;
		}

		if (column)
		{
			treeViewColumns.push_back(column);

			column->set_resizable(iter->getIncidentColumnConfiguration().getResizable());
			column->set_min_width(iter->getIncidentColumnConfiguration().getMinWidth());
			column->set_max_width(iter->getIncidentColumnConfiguration().getMaxWidth());
			column->set_alignment(iter->getIncidentColumnConfiguration().getAlignment());
			append_column(*column);
		}
	}
}

IncidentReportTreeView::~IncidentReportTreeView()
{
	std::vector <Gtk::TreeViewColumn *>::iterator it;

	for (it = treeViewColumns.begin();
			it != treeViewColumns.end();
			it++)
	{
		Gtk::TreeViewColumn * column = (*it);
		delete column;
		column = NULL;
	}

	treeViewColumns.clear();
}

void IncidentReportTreeView::AddRow(Report report)
{
	TreeModel::Row row;
	row = *(refListStore->append());

	row[incidentReportTreeModel.description] = report.getDescription();
	row[incidentReportTreeModel.namesOfTechnicians] =
			report.getNamesOfTechnicians().getFirstName() + " " +
			report.getNamesOfTechnicians().getSurname();
	row[incidentReportTreeModel.activityOfTechnicians] = report.getActivityOfTechnicians();

	if(report.getAdditionalObservations())
		row[incidentReportTreeModel.additionalObservations] = report.getAdditionalObservations().get();
	
	row[incidentReportTreeModel.notificationDate] = GetStringFromDateTime(report.getNotificationDate());
	row[incidentReportTreeModel.personalArrivalDate] = GetStringFromDateTime(report.getPersonalArrivalDate());
	row[incidentReportTreeModel.incidentSolutionDate] = GetStringFromDateTime(report.getIncidentSolutionDate());
	row[incidentReportTreeModel.complete] = report.getIsComplete();
	row[incidentReportTreeModel.customCode] = report.getCustom_code();

	row[incidentReportTreeModel.firstName] = report.getNamesOfTechnicians().getFirstName();
	row[incidentReportTreeModel.surName] = report.getNamesOfTechnicians().getSurname();
	row[incidentReportTreeModel.complete] = report.getIsComplete();
}

bool IncidentReportTreeView::GetRow(string customCode, Report& report)
{
	TreeModel::Children children = refListStore->children();
	TreeModel::Children::iterator iter;
	Glib::ustring param;

	for(iter = children.begin(); iter != children.end() ; iter++)
	{
		Gtk::TreeModel::Row row = *iter;
		string toCompare = (string)row[incidentReportTreeModel.customCode];
		if(toCompare.compare(customCode) == 0)
		{
			IDCardInfo idCard;
			idCard.setFirstName((string)(ustring)row[incidentReportTreeModel.firstName]);
			idCard.setSurname((string)(ustring)row[incidentReportTreeModel.surName]);
			
			report.setDescription((string)(ustring)row[incidentReportTreeModel.description]);
			report.setNamesOfTechnicians(idCard);
			report.setActivityOfTechnicians((string)(ustring)row[incidentReportTreeModel.activityOfTechnicians]);
			report.setAdditionalObservations((string)(ustring)row[incidentReportTreeModel.additionalObservations]);
			report.setNotificationDate(GetDateTimeFromUstring(row[incidentReportTreeModel.notificationDate]));
			report.setPersonalArrivalDate(GetDateTimeFromUstring(row[incidentReportTreeModel.personalArrivalDate]));
			report.setIncidentSolutionDate(GetDateTimeFromUstring(row[incidentReportTreeModel.incidentSolutionDate]));
			report.setCustom_code((string)row[incidentReportTreeModel.customCode]);
			report.setIsComplete(row[incidentReportTreeModel.complete]);
			return true;
		}
	}
	return false;
}

void IncidentReportTreeView::ModifyRow(Report report)
{
	TreeModel::Children children =  refListStore->children();
	TreeModel::Children::iterator iter;
	
	for(iter = children.begin(); iter != children.end() ; iter++)
	{
		Gtk::TreeModel::Row row = *iter;

		string toCompare = (string)row[incidentReportTreeModel.customCode];
		
		if(toCompare.compare(report.getCustom_code()) == 0)
		{
			row[incidentReportTreeModel.description] = report.getDescription();
			row[incidentReportTreeModel.namesOfTechnicians] =
					report.getNamesOfTechnicians().getFirstName() + " " +
					report.getNamesOfTechnicians().getSurname();
			row[incidentReportTreeModel.activityOfTechnicians] = report.getActivityOfTechnicians();

			if(report.getAdditionalObservations())
				row[incidentReportTreeModel.additionalObservations] = report.getAdditionalObservations().get();
			
			row[incidentReportTreeModel.notificationDate] = GetStringFromDateTime(report.getNotificationDate());
			row[incidentReportTreeModel.personalArrivalDate] = GetStringFromDateTime(report.getPersonalArrivalDate());
			row[incidentReportTreeModel.incidentSolutionDate] = GetStringFromDateTime(report.getIncidentSolutionDate());
			row[incidentReportTreeModel.complete] = report.getIsComplete();

			row[incidentReportTreeModel.firstName] = report.getNamesOfTechnicians().getFirstName();
			row[incidentReportTreeModel.surName] = report.getNamesOfTechnicians().getSurname();
			row[incidentReportTreeModel.complete] = report.getIsComplete();
		}
	}
}

DateTime IncidentReportTreeView::GetDateTimeFomStructTm(struct tm structtm)
{
	DateTime returnValue(1900, 0, 0, 0, 0, 0);

	if(structtm.tm_sec == 0 &&
	   structtm.tm_min == 0 &&
	   structtm.tm_hour == 0 &&
	   structtm.tm_mday == 0 &&
	   structtm.tm_mon == 0 &&
	   structtm.tm_year == 0)
	{
		return returnValue;
	}
	else if(structtm.tm_mday == 0 &&
	        structtm.tm_mon == 0 &&
	        structtm.tm_year == 0)
	{
		time_t rawtime;
		struct tm * timeinfo;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		structtm.tm_mday = timeinfo->tm_mday;
		structtm.tm_mon = timeinfo->tm_mon;
		structtm.tm_year = timeinfo->tm_year;
	}

	returnValue.year(1900 + structtm.tm_year);
	returnValue.month(structtm.tm_mon);
	returnValue.day(structtm.tm_mon);
	returnValue.hours(structtm.tm_hour);
	returnValue.minutes(structtm.tm_min);
	returnValue.seconds(structtm.tm_sec);

	return returnValue;
}

struct tm IncidentReportTreeView::GetStructTmFromDateTime(DateTime time)
{
	struct tm structtm;
	structtm.tm_sec = time.seconds();
	structtm.tm_min = time.minutes();
	structtm.tm_hour = time.hours();
	structtm.tm_mday = time.day();
	structtm.tm_mon = time.month();
	structtm.tm_year = time.year() - 1900;
	return structtm;
}

ustring IncidentReportTreeView::GetUstringFromStrucTm(struct tm structtm)
{
//Example return 01/01/2011 00:00:00
	ustring returnValue = "";
	stringstream out;
	
	out.str("");

	if(structtm.tm_mday < 10)
		out << "0" << structtm.tm_mday << "/";
	else
		out << structtm.tm_mday << "/";

	if(structtm.tm_mon < 10)
		out << "0" << structtm.tm_mon << "/";
	else
		out << structtm.tm_mon << "/";

	if(structtm.tm_year > 1900)
		out << structtm.tm_year << " ";
	else
		out << structtm.tm_year + 1900 << " ";

	if(structtm.tm_hour < 10)
		out << "0" << structtm.tm_hour << ":";
	else
		out << structtm.tm_hour << ":";

	if(structtm.tm_min < 10)
		out << "0" << structtm.tm_min << ":";
	else
		out << structtm.tm_min << ":";

	if(structtm.tm_sec < 10)
		out << "0" << structtm.tm_sec;
	else
		out << structtm.tm_sec;

	returnValue = out.str();


	return returnValue;
}

struct tm IncidentReportTreeView::GetStructTmFromUstring(ustring utime)
{
//Example time 0 1 / 0 1 / 2 0 1 1    0  0  :  0  0  :  0  0
//             0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
	string time = utime;
	struct tm returnTm;

	if(isdigit(time[0]) && isdigit(time[1]) && isdigit(time[3]) &&
	   isdigit(time[4]) && isdigit(time[6]) && isdigit(time[7]) &&
	   isdigit(time[8]) && isdigit(time[9]) && isdigit(time[11]) &&
	   isdigit(time[12]) && isdigit(time[14]) && isdigit(time[15]) &&
	   isdigit(time[17]) && isdigit(time[18]) && time[10] == ' ' &&
	   time[2] == '/' && time[5] == '/' && time[13] == ':' &&  time[16] == ':')
	{
		string str_day (time, 0, 2);
		string str_month (time, 3, 2);
		string str_year (time, 6, 4);
		string str_hour (time, 11, 2);
		string str_min (time, 14, 2);
		string str_sec (time, 17, 2);

		int day = StringUtils::stringToInt(str_day);
		int month = StringUtils::stringToInt(str_month);
		int year = StringUtils::stringToInt(str_year) - 1900;
		int hour = StringUtils::stringToInt(str_hour);
		int min = StringUtils::stringToInt(str_min);
		int sec = StringUtils::stringToInt(str_sec);
		
		returnTm.tm_sec = sec;
		returnTm.tm_min = min;
		returnTm.tm_hour = hour;
		returnTm.tm_mday = day;
		returnTm.tm_mon = month;
		returnTm.tm_year = year;
	}

	return returnTm;
}

string IncidentReportTreeView::GetStringFromDateTime(DateTime time)
{
	return GetUstringFromStrucTm( GetStructTmFromDateTime(time) );
}

DateTime IncidentReportTreeView::GetDateTimeFromUstring(ustring time)
{
	return GetDateTimeFomStructTm( GetStructTmFromUstring(time) );
}

void IncidentReportTreeView::SelectionChanged()
{
	currentCustomCode = "";
	TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter)
	{
		TreeModel::Row row = *iter;
		currentCustomCode = (string)row[incidentReportTreeModel.customCode];
	}
}

string IncidentReportTreeView::GetCustomCodeSelected()
{
	return 	currentCustomCode;
}

void IncidentReportTreeView::SetReports(Reports reports)
{
	Reports::ReportIterator p;
	
	for(p = reports.getReport().begin(); p != reports.getReport().end(); ++p)
	{
		AddRow(*p);
	}
}
