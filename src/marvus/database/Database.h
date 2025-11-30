//==============================================================================
// File       : Database.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef DATABASE_H
#define DATABASE_H

#include <variant>
#include <vector>

#include <sqlite3.h>

#include "ScriptMap.h"
#include "StatementSQL.h"

namespace marvus
{

inline const std::string INIT_DB_SQL = "initialize_database.sql";

using valueForDB = std::variant<std::monostate, int, long long, double, std::string>;

using insertData = valueForDB;
using insertVector = std::vector<insertData>;
using tableRow = std::vector<std::string>;
using tableRowVector = std::vector<tableRow>;
using tableHeaderAndData = std::pair<tableRow, tableRowVector>;

class Database
{
	protected:
		ConsoleLib::ScriptMap sqlScriptFiles;
		sqlite3* db; // SQLite database connection
		std::string sqlScriptsPath;
		int result;
		char* c_ErrorMessage;
		bool checkSuccessFor(const std::string& action, int expectedResult = SQLITE_OK);
	private:
		tableRowVector tableData;
		int rowCallback(void* data, int argc, char** argv, char** azColName); // Callback function to handle each row of the result
		int bindValuesToSQL(const insertVector& data, StatementSQL& stmtSQL);
	public:
		Database(std::string databaseFile);
		Database(std::string databaseFile, std::string sqlScripts);
		virtual ~Database();
		// Functions
		bool initializeViews();
		bool initializeDatabase();
		bool reconnect(const std::string& databaseFile);
		bool executeFileSQL(const std::string& sql);
		StatementSQL prepareScriptSQL(const std::string& sql, bool& success, const insertVector& data = {});
		int insertNewData(const insertVector& data, const std::string& insertSQL);
		tableRowVector obtainTableData(const std::string& selectSQL);
		tableHeaderAndData obtainTableHeaderAndData(const std::string& viewSQL);
		tableHeaderAndData obtainFromFilterView(const std::string& viewSQL, const insertVector& data);
		// Setters
		void setPathToSQL_Scripts(std::string path);
};
}
#endif /* DATABASE_H */ 
