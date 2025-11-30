//==============================================================================
// File       : Database.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "Database.h"

namespace marvus
{
Database::Database(std::string databaseFile) : Database(databaseFile, "")
{
}

Database::Database(std::string databaseFile, std::string sqlScriptsPath) : sqlScriptsPath(sqlScriptsPath), result(0), c_ErrorMessage(nullptr)
{
	sqlite3_open(databaseFile.c_str(), &db);
}

Database::~Database()
{
	if (db)
		sqlite3_close(db);
}

int Database::rowCallback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRow rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	tableData.push_back(std::move(rowData));
	return 0; // Continue processing
}

int Database::bindValuesToSQL(const insertVector& data, StatementSQL& stmtSQL)
{
	int x = 1;
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

		if (checkSuccessFor("SQL binding"))
			return 0;
		x++;
	}
	return 1;
}

int Database::insertNewData(const insertVector& data, const std::string& insertSQL)
{
	if (insertSQL == "")
	{
		std::cerr << "Invalid or missing SQL statement.\n";
		return 0;
	}

	StatementSQL stmtSQL;

	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, stmtSQL, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return 0;


	bindValuesToSQL(data, stmtSQL);

	result = sqlite3_step(stmtSQL);
	if (checkSuccessFor("SQL execution of insert", SQLITE_DONE))
		return 0;

	return sqlite3_last_insert_rowid(db);
}

tableRowVector Database::obtainTableData(const std::string& selectSQL)
{
	tableData.clear();
	result = sqlite3_exec(db, selectSQL.c_str(),
		[](void* data, int argc, char** argv, char** azColName) -> int {
			return static_cast<Database*>(data)->rowCallback(data, argc, argv, azColName);
		},
		this, &c_ErrorMessage);
	if (checkSuccessFor("SQL execution of SELECT", SQLITE_OK))
		tableData.clear();
	return tableData;
}

tableHeaderAndData Database::obtainFromFilterView(const std::string& viewSQL, const insertVector& data)
{
	tableRow header;
	tableRowVector tableData;
	bool ok;
	StatementSQL stmt = prepareScriptSQL(viewSQL, ok, data);

	if (!ok)
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

	header.reserve(colCount - 1);
	for (int i = 1; i < colCount; ++i) // As we don't need ID column header
	{
		header.push_back(sqlite3_column_name(stmt, i));
	}

	return tableHeaderAndData(header, tableData);
}

tableHeaderAndData Database::obtainTableHeaderAndData(const std::string& viewSQL)
{
	tableRow header;
	tableRowVector tableData;

	StatementSQL stmt;

	if (!sqlite3_prepare_v2(db, viewSQL.c_str(), -1, stmt, nullptr) == SQLITE_OK)
	{
		std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
	}

	int colCount = sqlite3_column_count(stmt);
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

	header.reserve(colCount - 1);
	for (int i = 1; i < colCount; ++i) // As we don't need ID column header
	{
		header.push_back(sqlite3_column_name(stmt, i));
	}

	return tableHeaderAndData(header, tableData);
}

bool Database::checkSuccessFor(const std::string& action, int expectedResult)
{
	if (result != expectedResult)
	{
		std::cerr << action << ": " << sqlite3_errmsg(db) << "\n";
		return true;
	}
	return false;
}

bool Database::reconnect(const std::string& databaseFile)
{
	if (db)
		sqlite3_close(db);
	sqlite3_open(databaseFile.c_str(), &db);
	return initializeDatabase();
}

bool Database::initializeViews()
{
	for (const auto& [scriptFile, fileContent] : sqlScriptFiles.getScriptMap())
		if (scriptFile.find("view") != std::string::npos)
			if (!executeFileSQL(fileContent))
				return false;
	return true;
}

bool Database::initializeDatabase()
{
	if (!sqlScriptFiles.loadScripts(sqlScriptsPath))
		return false;
	return executeFileSQL(sqlScriptFiles.getScript(INIT_DB_SQL));
}

bool Database::executeFileSQL(const std::string& sqlScript)
{
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &c_ErrorMessage);
	if (rc != SQLITE_OK)
	{
		std::cerr << c_ErrorMessage << "\n";
		sqlite3_free(c_ErrorMessage);
		return false;
	}
	return true;
}

StatementSQL Database::prepareScriptSQL(const std::string& sql, bool& success, const insertVector& data)
{
	StatementSQL stmt;
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
	{
		success = false;
		return stmt;
	}

	if (!bindValuesToSQL(data, stmt))
	{
		success = false;
		return stmt;
	}

	success = true;
	return stmt;
}

void Database::setPathToSQL_Scripts(std::string path)
{
	this->sqlScriptsPath = path;
}

}
