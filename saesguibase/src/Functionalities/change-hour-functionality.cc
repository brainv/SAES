/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * changehourfunctionality
 * Copyright (C)  2010 <>
 * 
 * changehourfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * changehourfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Functionalities/change-hour-functionality.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Configuration/label-configuration.h>
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

using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::Runtime;

ISMTTLog* ChangeHourFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality",GETTEXT_PACKAGE);

ChangeHourFunctionality* ChangeHourFunctionality::current_instance = NULL;
ChangeHourFunctionality* ChangeHourFunctionality::Current()
{
	if (!current_instance)
		current_instance = new ChangeHourFunctionality();

	return current_instance;
}

void ChangeHourFunctionality::deleteElement()
{
	if(frameDateHour)
	{
		delete frameDateHour;
		frameDateHour = NULL;
	}
	if(vboxDateHour)
	{
		delete vboxDateHour;
		vboxDateHour = NULL;
	}
	if(labelDateTitle)
	{
		delete labelDateTitle;
		labelDateTitle = NULL;
	}
	if(labelHourTitle)
	{
		delete labelHourTitle;
		labelHourTitle = NULL;
	}
	if(labelDay)
	{
		delete labelDay;
		labelDay = NULL;
	}
	if(labelMonth)
	{
		delete labelMonth;
		labelMonth = NULL;
	}
	if(labelYear)
	{
		delete labelYear;
		labelYear = NULL;
	}
	if(labelHour)
	{
		delete labelHour;
		labelHour = NULL;
	}
	if(labelMins)
	{
		delete labelMins;
		labelMins = NULL;
	}
	if(labelSecs)
	{
		delete labelSecs;
		labelSecs = NULL;
	}
	if(labelCurrentDate)
	{
		delete labelCurrentDate;
		labelCurrentDate = NULL;
	}
	if(labelCurrentDateValue)
	{
		delete labelCurrentDateValue;
		labelCurrentDateValue = NULL;
	}
	if(imageDate)
	{
		delete imageDate;
		imageDate = NULL;
	}
	if(imageHour)
	{
		delete imageHour;
		imageHour = NULL;
	}
	if(entryDay)
	{
		delete entryDay;
		entryDay = NULL;
	}
	if(entryMonth)
	{
		delete entryMonth;
		entryMonth = NULL;
	}
	if(entryYear)
	{
		delete entryYear;
		entryYear = NULL;
	}
	if(entryHour)
	{
		delete entryHour;
		entryHour = NULL;
	}
	if(entryMin)
	{
		delete entryMin;
		entryMin = NULL;
	}
	if(entrySec)
	{
		delete entrySec;
		entrySec = NULL;
	}
	if(buttonApplyNewDateHour)
	{
		delete buttonApplyNewDateHour;
		buttonApplyNewDateHour = NULL;
	}
	if(buttonDayUp)
	{
		delete buttonDayUp;
		buttonDayUp = NULL;
	}
	if(buttonDayDown)
	{
		delete buttonDayDown;
		buttonDayDown = NULL;
	}
	if(buttonMonthUp)
	{
		delete buttonMonthUp;
		buttonMonthUp = NULL;
	}
	if(buttonMonthDown)
	{
		delete buttonMonthDown;
		buttonMonthDown = NULL;
	}
	if(buttonYearUp)
	{
		delete buttonYearUp;
		buttonYearUp = NULL;
	}
	if(buttonYearDown)
	{
		delete buttonYearDown;
		buttonYearDown = NULL;
	}
	if(buttonHourUp)
	{
		delete buttonHourUp;
		buttonHourUp = NULL;
	}
	if(buttonHourDown)
	{
		delete buttonHourDown;
		buttonHourDown = NULL;
	}
	if(buttonMinsUp)
	{
		delete buttonMinsUp;
		buttonMinsUp = NULL;
	}
	if(buttonMinsDown)
	{
		delete buttonMinsDown;
		buttonMinsDown = NULL;
	}
	if(buttonSecondsUp)
	{
		delete buttonSecondsUp;
		buttonSecondsUp = NULL;
	}
	if(buttonSecondsDown)
	{
		delete buttonSecondsDown;
		buttonSecondsDown = NULL;
	}
	if(table2)
	{
		delete table2;
		table2 = NULL;
	}
}

void ChangeHourFunctionality::Dispose()
{
	conn.disconnect();
	deleteElement();
}

bool ChangeHourFunctionality::DontAllowExit()
{
	return false;
}

std::vector<KeysActionsCode> ChangeHourFunctionality::getSeqKey()
{
	std::vector<KeysActionsCode> keySeq;
	keySeq.clear();
	return keySeq;
}

bool ChangeHourFunctionality::DontAllowHelp()
{
	return false;
}

std::vector<KeysActionsCode> ChangeHourFunctionality::getHelpSeqKey()
{
	std::vector<KeysActionsCode> keySeq;
	keySeq.clear();
	return keySeq;
}

void ChangeHourFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.HourNotChanged"));

	hourSet = false;
	firstTime = true;
	labelCurrentDate->set_text(_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.CurrentDate"));
	isComingFrom = false;
	time_t date_temp;       // Stores seconds elapsed since 01-01-1970
	struct tm *date_format; // Saves in Date format
	char date_out[15];      // Output string
	char currentDate[25]; 
  	std::string strYear;
	std::string strMonth;
	std::string strDay;
	std::string strHour;
	std::string strMin;
	std::string strSec;
	
	logger->Debug("Starting date updating.");
	time(&date_temp);
	date_format = localtime(&date_temp);
	strftime(date_out, 15, "%Y%m%d%H%M%S", date_format);
	strftime(currentDate, 25, "%d-%m-%Y, %H:%M:%S", date_format);
	std::string currentDateText(currentDate);
	
	labelCurrentDateValue->show();
	labelCurrentDateValue->set_text(currentDateText);

	std::string strtime(date_out);
	strYear = strtime.substr(0,4);
	strMonth = strtime.substr(4,2);
	strDay = strtime.substr(6,2);
	strHour = strtime.substr(8,2);
	strMin = strtime.substr(10,2);
	strSec = strtime.substr(12,2);
	
	entryDay->set_text(strDay);
	entryMonth->set_text(strMonth);
	entryYear->set_text(strYear);
	entryHour->set_text(strHour);
	entryMin->set_text(strMin);
	entrySec->set_text(strSec);

	//connecting timer
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &ChangeHourFunctionality::on_timeout), 0);
	conn = Glib::signal_timeout().connect(my_slot, 1000);

	enableExitButton();
};

std::string ChangeHourFunctionality::checkStringAndAddZero(std::string input)
{
	if(input.size()<2)
	{
		input.insert(0,"0");
	}
	return input;
}

bool ChangeHourFunctionality::on_timeout(int timer_number)
{
	if(!hourSet)
	{
		time_t date_temp;       // Stores seconds elapsed since 01-01-1970
		struct tm *date_format; // Saves in Date format
		char currentDate[25]; 
		time(&date_temp);
		
		date_format = localtime(&date_temp);
		strftime(currentDate, 25, "%d-%m-%Y, %H:%M:%S", date_format);
		std::string currentDateText(currentDate);
		labelCurrentDateValue->show();
		labelCurrentDateValue->set_text(currentDateText);
	}
	return !hourSet;
}

ChangeHourFunctionality::ChangeHourFunctionality()
{
	frameDateHour = NULL;
	vboxDateHour= NULL;		
	labelDateTitle= NULL;
	labelHourTitle= NULL;
	labelDay= NULL;
	labelMonth= NULL;
	labelYear= NULL;
	labelHour= NULL;
	labelMins= NULL;
	labelSecs= NULL;
	labelCurrentDate= NULL;
	labelCurrentDateValue= NULL;
	imageDate= NULL;
	imageHour= NULL;
	entryDay= NULL;
	entryMonth= NULL;
	entryYear= NULL;
	entryHour= NULL;
	entryMin= NULL;
	entrySec= NULL;
	buttonApplyNewDateHour= NULL;
	buttonDayUp= NULL;
	buttonDayDown= NULL;
	buttonMonthUp= NULL;
	buttonMonthDown= NULL;
	buttonYearUp= NULL;
	buttonYearDown= NULL;
	buttonHourUp= NULL;
	buttonHourDown= NULL;
	buttonMinsUp= NULL;
	buttonMinsDown= NULL;
	buttonSecondsUp= NULL;
	buttonSecondsDown= NULL;
	table2 = NULL;

	config = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetChangeHourFunctionalitConfiguration();
}

ChangeHourFunctionality::~ChangeHourFunctionality()
{
	deleteElement();
}

void ChangeHourFunctionality::on_buttonDayUp_clicked()
{
	char * pMonth;
	int	month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	char * pEnd;
    int day = strtol (entryDay->get_text().c_str(),&pEnd,10);
	char *pYear;
	int year = strtol (entryYear->get_text().c_str(),&pYear,10);
	bool isEvenYear = false;
	bool alreadySet = false;
	if ((year%4==0) && ((year%100!=0)||(year%400==0)))
	{
		isEvenYear = true;
	}
	
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(day==31)
			{
				day=1;
				alreadySet = true;
			}
			break;
		case 2:
			if(isEvenYear)
			{
				if(day==29)
				{
					day=1;
					alreadySet = true;
				}
			}
			else
			{
				if(day==28)
				{
					day=1;
					alreadySet = true;
				}
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
				if(day==30)
				{
					day=1;
					alreadySet = true;
				}
			break;
		default:
			break;
	}
	if(!alreadySet)
	{
		day++;
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonDayDown_clicked()
{
	char * pMonth;
	int month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	char * pDay;
    int day = strtol (entryDay->get_text().c_str(),&pDay,10);
	char * pYear;
	int year = strtol (entryYear->get_text().c_str(),&pYear,10);
	bool isEvenYear = false;
	bool alreadySet = false;
	if ((year%4==0) && ((year%100!=0)||(year%400==0)))
	{
		isEvenYear = true;
	}
	
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(day==1)
			{
				day=31;
				alreadySet = true;
			}
			break;
		case 2:
			if(isEvenYear)
			{
				if(day==1)
				{
					day=29;
					alreadySet = true;
				}
			}
			else
			{
				if(day==1)
				{
					day=28;
					alreadySet = true;
				}
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
				if(day==1)
				{
					day=30;
					alreadySet = true;
				}
			break;
		default:
			break;
	}
	if(!alreadySet)
	{
		day--;
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonMonthUp_clicked()
{
	char * pMonth;
    int month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	if(month==12)
	{
		month=1;
	}
	else
	{
		month++;
	}
	char monthS[5];
	sprintf(monthS,"%d",month);
	entryMonth->set_text(checkStringAndAddZero(monthS));

	char * pDay;
	int day = strtol (entryDay->get_text().c_str(),&pDay,10);
	if(month==2)
	{
		char * pYear;
		bool isEvenYear= false;
		int year = strtol (entryYear->get_text().c_str(),&pYear,10);
		if ((year%4==0) && ((year%100!=0)||(year%400==0)))
		{
			isEvenYear = true;
		}
		if(day==30||day==31||day==29)
		{
			if(isEvenYear)
			{
				day=29;
			}
			else
			{
				day=28;
			}
		}
	}
	else if((month==4||month==6||month==9||month==11)&&(day==31))
	{
		day=30;		
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonMonthDown_clicked()
{
	char * pMonth;
    int month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	if(month==1)
	{
		month=12;
	}
	else
	{
		month--;
	}
	char monthS[5];
	sprintf(monthS,"%d",month);
	entryMonth->set_text(checkStringAndAddZero(monthS));

	char * pDay;
	int day = strtol (entryDay->get_text().c_str(),&pDay,10);
	if(month==2)
	{
		char * pYear;
		bool isEvenYear = false;
		int year = strtol (entryYear->get_text().c_str(),&pYear,10);
		if ((year%4==0) && ((year%100!=0)||(year%400==0)))
		{
			isEvenYear = true;
		}
		if(day==30||day==31||day==29)
		{
			if(isEvenYear)
			{
				day=29;
			}
			else
			{
				day=28;
			}
		}
	}
	else if((month==4||month==6||month==9||month==11)&&(day==31))
	{
		day=30;		
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonYearUp_clicked()
{
	char * pYear;
    int year = strtol (entryYear->get_text().c_str(),&pYear,10);
	if(year==2100)
	{
		year=1970;
	}
	else
	{
		year++;
	}
	char yearS[5];
	sprintf(yearS,"%d",year);
	entryYear->set_text(yearS);

	char * pDay;
	int day = strtol (entryDay->get_text().c_str(),&pDay,10);
	char * pMonth;
    int month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	if(month==2)
	{
		bool isEvenYear = false;
		if ((year%4==0) && ((year%100!=0)||(year%400==0)))
		{
			isEvenYear = true;
		}
		if(day==30||day==31||day==29)
		{
			if(isEvenYear)
			{
				day=29;
			}
			else
			{
				day=28;
			}
		}
	}
	else if((month==4||month==6||month==9||month==11)&&(day==31))
	{
		day=30;		
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonYearDown_clicked()
{
	char * pYear;
    int year = strtol (entryYear->get_text().c_str(),&pYear,10);
	if(year==1970)
	{
		year=2100;
	}
	else
	{
		year--;
	}
	char yearS[5];
	sprintf(yearS,"%d",year);
	entryYear->set_text(yearS);

	char * pDay;
	int day = strtol (entryDay->get_text().c_str(),&pDay,10);
	char * pMonth;
    int month = strtol (entryMonth->get_text().c_str(),&pMonth,10);
	if(month==2)
	{
		bool isEvenYear= false;
		if ((year%4==0) && ((year%100!=0)||(year%400==0)))
		{
			isEvenYear = true;
		}
		if(day==30||day==31||day==29)
		{
			if(isEvenYear)
			{
				day=29;
			}
			else
			{
				day=28;
			}
		}
	}
	else if((month==4||month==6||month==9||month==11)&&(day==31))
	{
		day=30;		
	}
	char dayS[5];
	sprintf(dayS,"%d",day);
	entryDay->set_text(checkStringAndAddZero(dayS));
}

void ChangeHourFunctionality::on_buttonHourUp_clicked()
{
	char * pHour;
    int hour = strtol (entryHour->get_text().c_str(),&pHour,10);
	if(hour==23)
	{
		hour=0;
	}
	else
	{
		hour++;
	}
	char hourS[5];
	sprintf(hourS,"%d",hour);
	entryHour->set_text(checkStringAndAddZero(hourS));
}

void ChangeHourFunctionality::on_buttonHourDown_clicked()
{
	char * pHour;
    int hour = strtol (entryHour->get_text().c_str(),&pHour,10);
	if(hour==0)
	{
		hour=23;
	}
	else
	{
		hour--;
	}
	char hourS[5];
	sprintf(hourS,"%d",hour);
	entryHour->set_text(checkStringAndAddZero(hourS));
}

void ChangeHourFunctionality::on_buttonMinsUp_clicked()
{
	char * pMins;
    int mins = strtol (entryMin->get_text().c_str(),&pMins,10);
	if(mins==59)
	{
		mins=0;
	}
	else
	{
		mins++;
	}
	char minsS[5];
	sprintf(minsS,"%d",mins);
	entryMin->set_text(checkStringAndAddZero(minsS));
}

void ChangeHourFunctionality::on_buttonMinsDown_clicked()
{
	char * pMins;
    int mins = strtol (entryMin->get_text().c_str(),&pMins,10);
	if(mins==0)
	{
		mins=59;
	}
	else
	{
		mins--;
	}
	char minsS[5];
	sprintf(minsS,"%d",mins);
	entryMin->set_text(checkStringAndAddZero(minsS));
}

void ChangeHourFunctionality::on_buttonSecondsUp_clicked()
{
	char * pSecs;
    int secs = strtol (entrySec->get_text().c_str(),&pSecs,10);
	if(secs==59)
	{
		secs=0;
	}
	else
	{
		secs++;
	}
	char secsS[5];
	sprintf(secsS,"%d",secs);
	entrySec->set_text(checkStringAndAddZero(secsS));
}

void ChangeHourFunctionality::on_buttonSecondsDown_clicked()
{
	char * pSecs;
    int secs = strtol (entrySec->get_text().c_str(),&pSecs,10);
	if(secs==0)
	{
		secs=59;
	}
	else
	{
		secs--;
	}
	char secsS[5];
	sprintf(secsS,"%d",secs);
	entrySec->set_text(checkStringAndAddZero(secsS));
}

void ChangeHourFunctionality::on_buttonApply_clicked()
{
			char dtime[16];
			std::string yearText;
			std::string monthText;
			std::string dayText;
			std::string hourText;
			std::string minText;
			std::string secText;

			yearText =entryYear->get_text();
			monthText =checkStringAndAddZero( entryMonth->get_text());
			dayText =checkStringAndAddZero( entryDay->get_text());
			hourText =checkStringAndAddZero( entryHour->get_text());
			minText =checkStringAndAddZero( entryMin->get_text());
			secText = checkStringAndAddZero(entrySec->get_text());
			
			dtime[0] = *(monthText.substr(0,1).c_str());
			dtime[1] = *(monthText.substr(1,1).c_str());
			dtime[2] = *(dayText.substr(0,1).c_str());
			dtime[3] = *(dayText.substr(1,1).c_str());
			dtime[4] = *(hourText.substr(0,1).c_str());
			dtime[5] = *(hourText.substr(1,1).c_str());
			dtime[6] = *(minText.substr(0,1).c_str());
			dtime[7] = *(minText.substr(1,1).c_str());
			dtime[8] = *(yearText.substr(0,1).c_str());
			dtime[9] = *(yearText.substr(1,1).c_str());
			dtime[10] = *(yearText.substr(2,1).c_str());
			dtime[11] = *(yearText.substr(3,1).c_str());
			dtime[12] = '.';
			dtime[13] = *(secText.substr(0,1).c_str());
			dtime[14] = *(secText.substr(1,1).c_str());
			dtime[15] = 0x00;

			std::string command = "date ";
			std::string test = command + dtime; 

			(void)ProcessLauncher::RunProcessThroughSystem(test.c_str());

		hourSet = true;	
		labelCurrentDate->set_text(_("Smartmatic.SAES.Glade.ChangeHour.HourChanged"));
		labelCurrentDateValue->hide();

		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.HourChanged"));

		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.HourChanged"));
}

std::string ChangeHourFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.ChangeHourFunctionality");
};

MenuOptionDescriptor ChangeHourFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MChangeHourFunctionality,false);
};

 Gtk::Widget* ChangeHourFunctionality::GetFrame()
{
	SmartmaticButton test;
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/change-hour.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}
	builder->get_widget("frameDateHour",frameDateHour);
	builder->get_widget("vboxDateHour",vboxDateHour);		
	builder->get_widget("labelDateTitle",labelDateTitle);
	builder->get_widget("labelHourTitle",labelHourTitle);
	builder->get_widget("labelDay",labelDay);
	builder->get_widget("labelMonth",labelMonth);
	builder->get_widget("labelYear",labelYear);
	builder->get_widget("labelHour",labelHour);
	builder->get_widget("labelMins",labelMins);
	builder->get_widget("labelSecs",labelSecs);
	builder->get_widget("labelCurrentDate",labelCurrentDate);
	builder->get_widget("labelCurrentDateValue",labelCurrentDateValue);
	builder->get_widget("imageDate",imageDate);
	builder->get_widget("imageHour",imageHour);
	builder->get_widget_derived("entryDay",entryDay);
	builder->get_widget_derived("entryMonth",entryMonth);
	builder->get_widget_derived("entryYear",entryYear);
	builder->get_widget_derived("entryHour",entryHour);
	builder->get_widget_derived("entryMin",entryMin);
	builder->get_widget_derived("entrySec",entrySec);
	builder->get_widget_derived("buttonApplyNewDateHour",buttonApplyNewDateHour);
	builder->get_widget_derived("buttonDayUp",buttonDayUp);
	builder->get_widget_derived("buttonDayDown",buttonDayDown);
	builder->get_widget_derived("buttonMonthUp",buttonMonthUp);
	builder->get_widget_derived("buttonMonthDown",buttonMonthDown);
	builder->get_widget_derived("buttonYearUp",buttonYearUp);
	builder->get_widget_derived("buttonYearDown",buttonYearDown);
	builder->get_widget_derived("buttonHourUp",buttonHourUp);
	builder->get_widget_derived("buttonHourDown",buttonHourDown);
	builder->get_widget_derived("buttonMinsUp",buttonMinsUp);
	builder->get_widget_derived("buttonMinsDown",buttonMinsDown);
	builder->get_widget_derived("buttonSecondsUp",buttonSecondsUp);
	builder->get_widget_derived("buttonSecondsDown",buttonSecondsDown);
	builder->get_widget("table2", table2);
	
	table2->set_row_spacings(config.getTableVerticalSpacing());

	//  Buttons Up and Down configuration

	int arrowsWidth = config.getButtonArrowWidth();
	int arrowsHeight = config.getButtonArrowHeight();

	buttonDayUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonDayUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonDayUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonDayUp_clicked));

	buttonDayDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonDayDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonDayDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonDayDown_clicked));

	buttonMonthUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonMonthUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonMonthUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonMonthUp_clicked));

	buttonMonthDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonMonthDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonMonthDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonMonthDown_clicked));

	buttonYearUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonYearUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonYearUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonYearUp_clicked));

	buttonYearDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonYearDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonYearDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonYearDown_clicked));

	buttonHourUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonHourUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonHourUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonHourUp_clicked));

	buttonHourDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonHourDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonHourDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonHourDown_clicked));

	buttonMinsUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonMinsUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonMinsUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonMinsUp_clicked));

	buttonMinsDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonMinsDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonMinsDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonMinsDown_clicked));

	buttonSecondsUp->SetButtonType(SmartmaticButton::ArrowTop);
	buttonSecondsUp->set_size_request(arrowsWidth, arrowsHeight);
	buttonSecondsUp->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonSecondsUp_clicked));

	buttonSecondsDown->SetButtonType(SmartmaticButton::ArrowBottom);
	buttonSecondsDown->set_size_request(arrowsWidth, arrowsHeight);
	buttonSecondsDown->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonSecondsDown_clicked));

	//Apply button

	buttonApplyNewDateHour->set_size_request(config.getButtonValidateWidth(), config.getButtonValidateHeight());
	buttonApplyNewDateHour->SetLabel(_("Smartmatic.SAES.Glade.ChangeHour.ChangeDateHour"));
	buttonApplyNewDateHour->signal_clicked().connect( sigc::mem_fun(this, &ChangeHourFunctionality::on_buttonApply_clicked));
	buttonApplyNewDateHour->ModifyFontSize(20);

	//Entries configuration

	int entryWidth = config.getEntryWidth();
	int entryHeight = config.getEntryHeight();

	Pango::FontDescription fontDesc1;
	fontDesc1.set_size(config.getFontEntrySize() * Pango::SCALE);
	
	entryDay->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entryDay->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entryDay->set_size_request(entryWidth, entryHeight);
	entryDay->set_alignment(0.5);
	entryDay->modify_font(fontDesc1);

	entryMonth->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entryMonth->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entryMonth->set_size_request(entryWidth, entryHeight);
	entryMonth->set_alignment(0.5);
	entryMonth->modify_font(fontDesc1);

	entryYear->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entryYear->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entryYear->set_size_request(entryWidth, entryHeight);
	entryYear->set_alignment(0.5);
	entryYear->modify_font(fontDesc1);

	entryHour->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entryHour->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entryHour->set_size_request(entryWidth, entryHeight);
	entryHour->set_alignment(0.5);
	entryHour->modify_font(fontDesc1);

	entryMin->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entryMin->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entryMin->set_size_request(entryWidth, entryHeight);
	entryMin->set_alignment(0.5);
	entryMin->modify_font(fontDesc1);

	entrySec->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	entrySec->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entrySec->set_size_request(entryWidth, entryHeight);
	entrySec->set_alignment(0.5);
	entrySec->modify_font(fontDesc1);

	imageHour->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/clock.png"));
	imageDate->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/Calendar.png"));

	// Labels configuration
	Smartmatic::GUI::Configuration::LabelConfiguration labelHourTimeConf =
			Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTimeLabelConfiguration());

	labelHour->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Hour"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelHour, labelHourTimeConf);

	labelMins->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Minute"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelMins, labelHourTimeConf);

	labelSecs->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Seconds"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelSecs, labelHourTimeConf);

	labelDay->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Day"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelDay, labelHourTimeConf);

	labelMonth->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Month"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelMonth, labelHourTimeConf);

	labelYear->set_label(_("Smartmatic.SAES.Glade.ChangeHour.Year"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelYear, labelHourTimeConf);

	Smartmatic::GUI::Configuration::LabelConfiguration labelTitlesTimeConf =
		Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTitlesLabelConfiguration());

	labelHourTitle->set_label(_("Smartmatic.SAES.Glade.ChangeHour.HourChange"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelHourTitle, labelTitlesTimeConf);

	labelDateTitle->set_label(_("Smartmatic.SAES.Glade.ChangeHour.DateChange"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelDateTitle, labelTitlesTimeConf);

	Smartmatic::GUI::Configuration::LabelConfiguration labelPrincipalTitlesTimeConf =
		Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getPrincipalTitleLabelConfiguration());

	labelCurrentDate->set_label(_("Smartmatic.SAES.Glade.ChangeHour.CurrentDate"));
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelCurrentDate, labelPrincipalTitlesTimeConf);

	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(labelCurrentDateValue, labelPrincipalTitlesTimeConf);


	Gtk::Alignment* align = Gtk::manage(new Gtk::Alignment());
	align->set(0.5,0.5,0.9,1);
	align->add(*frameDateHour);
	align->show_all_children();
	align->show();

	return align;
};

Smartmatic::Log::ISMTTLog* ChangeHourFunctionality::getLogger()
{
	return logger;
}
Glib::ustring ChangeHourFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.LogStartFunctionality");
}

Glib::ustring ChangeHourFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeHourFunctionality.LogCloseFunctionality");
}

