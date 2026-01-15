//==============================================================================
// File       : ScriptMap.h
// Author     : riyufuchi
// Created on : Mar 28, 2025
// Last edit  : Jan 13, 2026
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
	bool load_scripts(const std::string& path = "");
	bool load_scripts_recursive(const std::string& path = "");
	const std::string&  get_script(const std::string& scriptname) const;
	std::unordered_map<std::string, std::string>& get_script_map();
};
}
#endif /* SRC_INC_SCRIPTMAP_H_ */
