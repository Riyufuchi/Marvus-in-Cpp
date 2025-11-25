//==============================================================================
// File       : DataUtils.h
// Author     : riyufuchi
// Created on : Mar 8, 2024
// Last edit  : Jan 29, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleLib
//==============================================================================

#ifndef _DATA_UTILS_H_
#define _DATA_UTILS_H_

#include <string>

namespace ConsoleLib
{
class DataUtils
{
private:
public:
	DataUtils();
	~DataUtils();
	static bool isNumber(const std::string& s);
	static bool isDouble(const std::string& s);
	static std::string boolToString(bool value);
};
}
#endif
