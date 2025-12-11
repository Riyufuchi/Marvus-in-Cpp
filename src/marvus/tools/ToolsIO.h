//==============================================================================
// File       : ToolsIO.h
// Author     : riyufuchi
// Created on : Dec 7, 2025
// Last edit  : Dec 7, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_TOOLS_TOOLSIO_H_
#define MARVUS_TOOLS_TOOLSIO_H_

// Local - Marvus
#include "../base/Controller.h"
// miniZ
#include "../../external/miniz.h"


namespace marvus
{

class Controller; // Forward declaration

class ToolsIO
{
private:
	Controller& controller;
	tableHeaderAndData ents;
	tableHeaderAndData cats;
	std::unordered_map<std::string, int> entMap;
	std::unordered_map<std::string, int> catMap;
	bool importEnties(const std::string& source);
	bool importCategories(const std::string& source);
	bool importData(const std::string& source);
	bool importMacros(const std::string& source);
public:
	ToolsIO(Controller& controller);
	virtual ~ToolsIO();
	bool importDataFromZip(const std::string& path, std::string& errorMessage);
};

} /* namespace sdl */

#endif /* MARVUS_TOOLS_TOOLSIO_H_ */
