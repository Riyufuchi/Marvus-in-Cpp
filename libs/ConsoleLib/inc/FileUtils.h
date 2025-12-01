//==============================================================================
// File       : FileUtils.h
// Author     : riyufuchi
// Created on : Nov 28, 2025
// Last edit  : Nov 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_FILEUTILS_H_
#define SRC_INC_FILEUTILS_H_

#include <string>
#include <vector>

namespace consolelib
{

class FileUtils
{
public:
	FileUtils() = default;
	virtual ~FileUtils() = default;
	static std::vector<std::string> splitCSV(const std::string& line, char delimeter, size_t expectedCount = 2);
};

} /* namespace consolelib */

#endif /* SRC_INC_FILEUTILS_H_ */
