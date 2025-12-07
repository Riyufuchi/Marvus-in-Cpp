//==============================================================================
// File       : Database.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 07, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef DATABASE_H
#define DATABASE_H

#include <variant>
#include <vector>
#include <functional>

// Local - Marvus
#include "StatementSQL.h"
#include "../InlineSQL.h"
// SQLite
#include "../../external/sqlite/sqlite3.h"
// ConsoleLib
#include "ScriptMap.h"

namespace marvus
{

using valueForDB = std::variant<std::monostate, int, long long, double, std::string>;

using insertData = valueForDB;
using insertVector = std::vector<insertData>;
using tableRow = std::vector<std::string>;
using tableRowVector = std::vector<tableRow>;
using tableHeaderAndData = std::pair<tableRow, tableRowVector>;

using errorFunctionSignature = std::function<void(const std::string&, const std::string&)>;

class Database
{
	protected:
		consolelib::ScriptMap sqlScriptFiles;
		sqlite3* db; // SQLite database connection
		std::string sqlScriptsPath;
		char* c_ErrorMessage;
		errorFunctionSignature showError;
		bool checkSuccess(int result, int expectedResult = SQLITE_OK);
	private:
		tableRowVector tableData;
		int rowCallback(void* data, int argc, char** argv, char** azColName); // Callback function to handle each row of the result
		int bindValuesToSQL(const insertVector& data, StatementSQL& stmtSQL);
	public:
		Database(std::string databaseFile, errorFunctionSignature showError);
		Database(std::string databaseFile, std::string sqlScripts, errorFunctionSignature showError);
		virtual ~Database();
		// Functions
		bool initializeViews();
		bool initializeDatabase();
		bool reconnect(const std::string& databaseFile);
		bool executeFileSQL(const std::string& sql);
		bool prepareScriptSQL(const std::string& sql, StatementSQL& statement, const insertVector& data = {});
		int insertNewData(const insertVector& data, const std::string& insertSQL);
		tableRowVector obtainTableData(const std::string& selectSQL);
		tableHeaderAndData obtainTableHeaderAndData(const std::string& viewSQL);
		tableHeaderAndData obtainFromFilterView(const std::string& viewSQL, const insertVector& data);
		// Setters
		void setPathToSQL_Scripts(std::string path);
		void setShowErrorFunction(errorFunctionSignature func);
		// Getters
		const std::string& getScriptSQL(const std::string& scrpiptFileName);
};
}
#endif /* DATABASE_H */ 
