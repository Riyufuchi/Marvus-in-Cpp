//==============================================================================
// File       : ToolsIO.h
// Author     : riyufuchi
// Created on : Dec 07, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_TOOLS_IO_TOOLS_H_
#define MARVUS_TOOLS_IO_TOOLS_H_

// Local - Marvus
#include "../../external/miniz.h"
#include "../base/controller.h"


namespace marvus
{

class Controller; // Forward declaration

class ToolsIO
{
private:
	Controller& controller;
	tableHeaderAndData ents;
	tableHeaderAndData cats;
	std::unordered_map<std::string, int> entity_map;
	std::unordered_map<std::string, int> category_map;
	bool import_enties(const std::string& source);
	bool import_categories(const std::string& source);
	bool import_data(const std::string& source);
	bool import_macros(const std::string& source);
public:
	ToolsIO(Controller& controller);
	virtual ~ToolsIO();
	bool import_from_zip(const std::string& path, std::string& error_message);
};

} /* namespace sdl */

#endif /* MARVUS_TOOLS_IO_TOOLS_H_ */
