//==============================================================================
// File       : DatabaseSQLite.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 14, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "database_sqlite.h"

namespace marvus
{
DatabaseSQLite::DatabaseSQLite(errorFunctionSignature showError) : DatabaseSQLite("", showError)
{
}

DatabaseSQLite::DatabaseSQLite(std::string sqlScriptsPath, errorFunctionSignature showError) : db(nullptr), sqlScriptsPath(sqlScriptsPath), c_ErrorMessage(nullptr), showError(showError)
{

}

DatabaseSQLite::~DatabaseSQLite()
{
	if (db)
		sqlite3_close(db);
}

int DatabaseSQLite::rowCallback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRow rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	tableData.push_back(std::move(rowData));
	return 0; // Continue processing
}

int DatabaseSQLite::bindValuesToSQL(const insertVector& data, StatementSQL& stmtSQL)
{
	int x = 1;
	static int result;
	for (const insertData& dataToInsert : data)
	{
		// Handle NULL early
		if (std::holds_alternative<std::monostate>(dataToInsert))
		{
			result = sqlite3_bind_null(stmtSQL, x);
		}
		else
		{
			// Use std::visit for correct bind
			result = std::visit([&](auto&& val) -> int
			{
				using T = std::decay_t<decltype(val)>;

				if constexpr (std::is_same_v<T, std::string>)
				{
					return sqlite3_bind_text(stmtSQL, x, val.c_str(), -1, SQLITE_TRANSIENT);
				}
				else if constexpr (std::is_same_v<T, int>)
				{
					return sqlite3_bind_int(stmtSQL, x, val);
				}
				else if constexpr (std::is_same_v<T, long long>)
				{
					return sqlite3_bind_int64(stmtSQL, x, val);
				}
				else if constexpr (std::is_same_v<T, double>)
				{
					return sqlite3_bind_double(stmtSQL, x, val);
				}
				else
				{
					return SQLITE_MISUSE;
				}
			}, dataToInsert);
		}

		if (checkSuccess(result))
			return 0;
		x++;
	}
	return 1;
}

int DatabaseSQLite::insertNewData(const insertVector& data, const std::string& insertSQL)
{
	static int result;
	if (insertSQL == "")
	{
		std::cerr << "Invalid or missing SQL statement.\n";
		return 0;
	}

	StatementSQL stmtSQL;

	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, stmtSQL, nullptr);
	if (checkSuccess(result))
		return 0;


	bindValuesToSQL(data, stmtSQL);

	result = sqlite3_step(stmtSQL);
	if (checkSuccess(result, SQLITE_DONE))
		return 0;

	return sqlite3_last_insert_rowid(db);
}

tableRowVector DatabaseSQLite::obtainTableData(const std::string& selectSQL)
{
	tableData.clear();
	static int result = sqlite3_exec(db, selectSQL.c_str(),
		[](void* data, int argc, char** argv, char** azColName) -> int {
			return static_cast<DatabaseSQLite*>(data)->rowCallback(data, argc, argv, azColName);
		},
		this, &c_ErrorMessage);
	if (checkSuccess(result))
		tableData.clear();
	return tableData;
}

tableHeaderAndData DatabaseSQLite::obtainFromFilterView(const std::string& viewSQL, const insertVector& data)
{
	tableRow header;
	tableRowVector tableData;

	StatementSQL stmt;

	if (!prepareScriptSQL(viewSQL, stmt, data))
		return {};

	int colCount = sqlite3_column_count(stmt);

	if (!colCount)
		return {};

	int i = 0;
	const char* value = nullptr;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		tableRow rowData;
		rowData.reserve(colCount); // Optimize vector allocation
		for (i = 0; i < colCount; i++)
		{
			value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
			rowData.push_back(value ? std::string(value) : "NULL");
		}
		tableData.push_back(std::move(rowData));
	}

	header.reserve(colCount);
	for (int i = 0; i < colCount; i++)
	{
		header.push_back(sqlite3_column_name(stmt, i));
	}

	return tableHeaderAndData(header, tableData);
}

bool DatabaseSQLite::checkSuccess(int result, int expectedResult)
{
	if (result != expectedResult)
	{
		showError("SQLite  error", sqlite3_errmsg(db));
		return true;
	}
	return false;
}

bool DatabaseSQLite::createNewDatabaseFile(const std::string& databaseFilePath)
{
	return checkSuccess(sqlite3_open_v2(databaseFilePath.c_str(), &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr));
}

bool DatabaseSQLite::reconnect(const std::string& databaseFile)
{
	if (db)
		sqlite3_close(db);
	return checkSuccess(sqlite3_open_v2(databaseFile.c_str(), &db,  SQLITE_OPEN_READWRITE, nullptr));
}

bool DatabaseSQLite::initializeViews()
{
	if (!db)
		return false;
	for (const auto& [scriptFile, fileContent] : sqlScriptFiles.getScriptMap())
		if (scriptFile.find("view") != std::string::npos)
			if (!executeFileSQL(fileContent))
				return false;
	return true;
}

bool DatabaseSQLite::initializeDatabase()
{
	if (!db)
		return false;
	if (!sqlScriptFiles.loadScriptsRecursive(sqlScriptsPath))
		return false;
	return executeFileSQL(sqlScriptFiles.getScript(InlineSQL::INITIALIZE_DATABASE_SQL));
}

bool DatabaseSQLite::executeFileSQL(const std::string& sqlScript)
{
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &c_ErrorMessage);
	if (rc != SQLITE_OK)
	{
		showError("SQL script file execution", c_ErrorMessage);
		sqlite3_free(c_ErrorMessage);
		return false;
	}
	return true;
}

bool DatabaseSQLite::prepareScriptSQL(const std::string& sql, StatementSQL& statement, const insertVector& data)
{
	if (checkSuccess(sqlite3_prepare_v2(db, sql.c_str(), -1, statement, nullptr)))
	{
		return false;
	}

	if (!bindValuesToSQL(data, statement))
	{
		return false;
	}

	return true;
}

void DatabaseSQLite::setPathToSQL_Scripts(std::string path)
{
	this->sqlScriptsPath = path;
}

void DatabaseSQLite::setShowErrorFunction(errorFunctionSignature func)
{
	showError = func;
}

const std::string& DatabaseSQLite::getScriptSQL(const std::string& scrpiptFileName)
{
	return sqlScriptFiles.getScript(scrpiptFileName);
}

bool DatabaseSQLite::isConnected() const
{
	return db;
}

}
