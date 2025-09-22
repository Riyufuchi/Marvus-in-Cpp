//==============================================================================
// File       : PostgreController.h
// Author     : riyufuchi
// Created on : Sep 18, 2025
// Last edit  : Sep 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef SRC_DATABASE_POSTGRECONTROLLER_H_
#define SRC_DATABASE_POSTGRECONTROLLER_H_

#include <string>
#include <libpq-fe.h>
#include <vector>
#include <wx/wx.h>

#include "ScriptMap.h"

namespace riyufuchi
{

inline const std::string INIT_DB_SQL = "initialize_database.sql";

using tableRowStructure = std::vector<std::string>;
using tableStructure = std::vector<tableRowStructure>;
using tableHeaderAndData = std::pair<std::vector<std::string>, tableStructure>;

class PostgreController
{
private:
	ConsoleLib::ScriptMap sqlScriptFiles;
	int result;
	std::string sqlScriptsPath;
	PGconn* conn;
public:
	PostgreController(const std::string& conninfo);
	virtual ~PostgreController();
	void printError();
	void setSQL_Scripts(std::string path);
	bool initializeDatabase();
	bool initializeViews();
	bool isConnected() const;
	bool executeSQL(const std::string& sql);
	tableHeaderAndData obtainTableHeaderAndData(const std::string& viewSQL);
};

} /* namespace sdl */

#endif /* SRC_DATABASE_POSTGRECONTROLLER_H_ */
