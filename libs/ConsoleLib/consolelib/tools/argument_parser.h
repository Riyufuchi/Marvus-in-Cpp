//==============================================================================
// File       : ArgumentParser.h
// Author     : riyufuchi
// Created on : Apr 06, 2025
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_ARGUMENTPARSER_H_
#define SRC_INC_ARGUMENTPARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace consolelib
{

using argVectorItem = std::pair<std::string, std::vector<std::string>>;
using argVector = std::vector<argVectorItem>;
using argMap = std::map<std::string, std::vector<std::string>>;

class ArgumentParser
{
public:
	ArgumentParser() = default;
	virtual ~ArgumentParser() = default;
	static void printArgumentPairs(const argMap& argPairs);
	static void printArgumentPairs(const argVector& argPairs);
	static bool contains(const argVector& argPairs, const std::string& value);
	static bool remove(argVector& argPairs, const std::string& value);
	static argMap analyze(int argc, char** argv, bool& success, std::string& message);
	static argVector analyzeInOrder(int argc, char** argv, bool& success, std::string& message);

};

} /* namespace consolelib */

#endif /* SRC_INC_ARGUMENTPARSER_H_ */
