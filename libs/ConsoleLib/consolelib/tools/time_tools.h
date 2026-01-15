//==============================================================================
// File       : TimeUtils.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Jan 13, 2026
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: consoleart
//==============================================================================

#ifndef _OTHER_TIME_UTILS_H_
#define _OTHER_TIME_UTILS_H_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace consolelib::time_tools
{
struct TimeStamp
{
	long seconds {0};
	long minutes {0};
	long hours {0};
};
struct Date
{
	int day;
	int month;
	int year;
};
TimeStamp convert_millis(long millis);
long convert_to_minutes(const TimeStamp& timeStamp);
long convert_to_hours(const TimeStamp& timeStamp);
Date today_date();
std::string date_to_string(const Date& date);
}
#endif
