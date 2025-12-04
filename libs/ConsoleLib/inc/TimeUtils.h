//==============================================================================
// File       : TimeUtils.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : May 07, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: consoleart
//==============================================================================

#ifndef _OTHER_TIME_UTILS_H_
#define _OTHER_TIME_UTILS_H_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


namespace consolelib
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
class TimeUtils
{
public:
	TimeUtils();
	~TimeUtils();
	static TimeStamp convertMillis(long millis);
	static long convertToMinutes(TimeStamp& timeStamp);
	static long convertToHours(TimeStamp& timeStamp);
	static Date todaysDate();
	static std::string dateToString(const Date& date);
};
} /* namespace */
#endif /* _OTHER_TIME_UTILS_H_ */
