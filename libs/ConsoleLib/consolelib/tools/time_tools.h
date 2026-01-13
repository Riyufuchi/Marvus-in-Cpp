//==============================================================================
// File       : TimeUtils.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Dec 22, 2025
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
TimeStamp convertMillis(long millis);
long convertToMinutes(TimeStamp& timeStamp);
long convertToHours(TimeStamp& timeStamp);
Date todaysDate();
std::string dateToString(const Date& date);
}
#endif
