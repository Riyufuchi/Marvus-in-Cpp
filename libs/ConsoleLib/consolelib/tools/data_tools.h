//==============================================================================
// File       : DataUtils.h
// Author     : riyufuchi
// Created on : Mar 08, 2024
// Last edit  : Jan 13, 2026
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _DATA_UTILS_H_
#define _DATA_UTILS_H_

#include <string>
#include <stdexcept>

namespace consolelib::data_tools
{
	bool is_number(const std::string& s);
	bool is_double(const std::string& s);
	std::string bool_to_string(bool value);
	std::u32string string_to_u32string(const std::string& s);
	std::string u32char_to_string(char32_t cp);
}
#endif
