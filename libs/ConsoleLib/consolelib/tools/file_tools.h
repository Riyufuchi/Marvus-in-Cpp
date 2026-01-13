//==============================================================================
// File       : FileUtils.h
// Author     : riyufuchi
// Created on : Nov 28, 2025
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_FILEUTILS_H_
#define SRC_INC_FILEUTILS_H_

#include <string>
#include <vector>

namespace consolelib::file_tools
{
	std::vector<std::string> splitCSV(const std::string& line, char delimeter, size_t expectedCount = 2);
}

#endif
