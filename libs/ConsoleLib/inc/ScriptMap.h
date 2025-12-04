//==============================================================================
// File       : ScriptMap.h
// Author     : riyufuchi
// Created on : Mar 28, 2025
// Last edit  : Nob 01, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_SCRIPTMAP_H_
#define SRC_INC_SCRIPTMAP_H_

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <filesystem>

namespace consolelib
{
class ScriptMap
{
private:
	std::unordered_map<std::string, std::string> scripts;
public:
	ScriptMap();
	~ScriptMap();
	bool loadScripts(const std::string& path = "");
	const std::string&  getScript(const std::string& scriptname) const;
	std::unordered_map<std::string, std::string>& getScriptMap();
};
}
#endif /* SRC_INC_SCRIPTMAP_H_ */
