/**
 * @file	time-functionality.cc
 *
 * @brief	time functionality class.
 */

#include "time-functionality.h"
#include <stdio.h>
#include <sstream>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::Log;
using namespace std;
using namespace Smartmatic::Functionality;

ISMTTLog* TimeFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.Functionality.TimeFunctionality",GETTEXT_PACKAGE);
timespec TimeFunctionality::time1; ///< The first time functionality time

timespec TimeFunctionality::GetDifference(timespec& start, timespec& end)
{
	timespec temp;
	if((end.tv_nsec - start.tv_nsec) < 0) 
	{
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} 
	else 
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}


string TimeFunctionality::GetCurrentTime()
{
	return ConvertTimeToString(GetTime());
}


string TimeFunctionality::StartTime()
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	//clock_gettime(CLOCK_REALTIME, &time1);
	return ConvertTimeToString(time1);
}


string TimeFunctionality::GetStartTimeDifference()
{
	timespec temp;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &temp);
	string returnString = ConvertTimeToString(GetDifference(time1, temp));
	time1 = temp;
	return returnString;
}


string TimeFunctionality::ConvertTimeToString(timespec timestring)
{
	stringstream ss;
	ss << timestring.tv_sec;
	ss << ":";
	ss << timestring.tv_nsec/ 1000;
	return ss.str();
}


timespec TimeFunctionality::GetTime()
{
	timespec temp;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &temp);
	return temp;
}


void TimeFunctionality::GetDateTime(string& strDateTime)
{
	time_t t = time(0);
	struct tm* lt = localtime(&t);
	char time_str[15];
	sprintf(time_str, "%04d%02d%02d%02d%02d%02d",
	        lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
	        lt->tm_hour, lt->tm_min, lt->tm_sec);

	strDateTime = time_str;
}


void TimeFunctionality::StartTimePrintOut()
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

	stringstream ss;
	ss << time1.tv_sec << ":" << time1.tv_nsec/ 1000;

	logger->Debug(ss.str());
}


void TimeFunctionality::GetStartTimeDifferencePrintOut()
{
	timespec temp, temp2;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &temp);
	//clock_gettime(CLOCK_REALTIME, &temp);
	temp2 = GetDifference(time1, temp);
	time1 = temp;

	stringstream ss;
	ss << temp2.tv_sec << ":" << temp2.tv_nsec/ 1000 << endl;

	logger->Debug(ss.str());
}

