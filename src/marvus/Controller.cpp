//==============================================================================
// File       : Controller.cpp
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Nov 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "Controller.h"

namespace marvus
{

Controller::Controller() : marvusDB(DATABASE_FILE)
{
	this->argumentMethods["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; marvusDB.setSQL_Scripts(vector[0]); };
}

void Controller::configure(ConsoleLib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const ConsoleLib::argVectorItem& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
	}
}

bool Controller::initDB(std::string& errorMsg)
{
	if (!marvusDB.initializeDatabase())
	{
		errorMsg = "Database initialization failed.\nExiting program!";
		return true;
	}
	if (!marvusDB.initializeViews())
	{
		errorMsg = "Views initialization failed.\nExiting program!";
		return true;
	}
	return false;
}

void Controller::dropDB()
{
	std::filesystem::remove(DATABASE_FILE);
	marvusDB.reconnect(DATABASE_FILE);
	marvusDB.initializeViews();
}

MarvusDB& Controller::getDB()
{
	return marvusDB;
}

} /* namespace marvus */
