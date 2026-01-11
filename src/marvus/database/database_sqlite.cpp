//==============================================================================
// File       : DatabaseSQLite.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "database_sqlite.h"

namespace marvus
{
DatabaseSQLite::DatabaseSQLite(const ShowErrorFunction& show_error_function) : DatabaseSQLite("", show_error_function)
{
}

DatabaseSQLite::DatabaseSQLite(const std::string& sql_script_path, const ShowErrorFunction& show_error_function) : db(nullptr), sql_script_files_path(sql_script_path), c_error_message(nullptr), show_error_function(show_error_function)
{

}

DatabaseSQLite::~DatabaseSQLite()
{
	if (db)
		sqlite3_close(db);
}

int DatabaseSQLite::row_callback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRow rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	table_data.push_back(std::move(rowData));
	return 0; // Continue processing
}

int DatabaseSQLite::bind_values_to_sql(const insertVector& data, StatementSQL& stmt_sql)
{
	int x = 1;
	static int result;
	for (const insertData& dataToInsert : data)
	{
		// Handle NULL early
		if (std::holds_alternative<std::monostate>(dataToInsert))
		{
			result = sqlite3_bind_null(stmt_sql, x);
		}
		else
		{
			// Use std::visit for correct bind
			result = std::visit([&](auto&& val) -> int
			{
				using T = std::decay_t<decltype(val)>;

				if constexpr (std::is_same_v<T, std::string>)
				{
					return sqlite3_bind_text(stmt_sql, x, val.c_str(), -1, SQLITE_TRANSIENT);
				}
				else if constexpr (std::is_same_v<T, int>)
				{
					return sqlite3_bind_int(stmt_sql, x, val);
				}
				else if constexpr (std::is_same_v<T, long long>)
				{
					return sqlite3_bind_int64(stmt_sql, x, val);
				}
				else if constexpr (std::is_same_v<T, double>)
				{
					return sqlite3_bind_double(stmt_sql, x, val);
				}
				else
				{
					return SQLITE_MISUSE;
				}
			}, dataToInsert);
		}

		if (check_success(result))
			return 0;
		x++;
	}
	return 1;
}

int DatabaseSQLite::insert_new_row(const insertVector& data, const std::string& insert_sql)
{
	static int result;
	if (insert_sql == "")
	{
		std::cerr << "Invalid or missing SQL statement.\n";
		return 0;
	}

	StatementSQL stmtSQL;

	result = sqlite3_prepare_v2(db, insert_sql.c_str(), -1, stmtSQL, nullptr);
	if (check_success(result))
		return 0;


	bind_values_to_sql(data, stmtSQL);

	result = sqlite3_step(stmtSQL);
	if (check_success(result, SQLITE_DONE))
		return 0;

	return sqlite3_last_insert_rowid(db);
}

tableRowVector DatabaseSQLite::obtain_data_from_table(const std::string& selectSQL)
{
	table_data.clear();
	static int result = sqlite3_exec(db, selectSQL.c_str(),
		[](void* data, int argc, char** argv, char** azColName) -> int {
			return static_cast<DatabaseSQLite*>(data)->row_callback(data, argc, argv, azColName);
		},
		this, &c_error_message);
	if (check_success(result))
		table_data.clear();
	return table_data;
}

tableHeaderAndData DatabaseSQLite::obtain_data_from_filtered_view(const std::string& view_sql, const insertVector& data)
{
	tableRow header;
	tableRowVector tableData;

	StatementSQL stmt;

	if (!prepare_sql_script(view_sql, stmt, data))
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

bool DatabaseSQLite::check_success(int result, int expected_result)
{
	if (result != expected_result)
	{
		show_error_function(sqlite3_errmsg(db), "SQLite  error");
		return true;
	}
	return false;
}

bool DatabaseSQLite::create_new_database_file(const std::string& database_file_path)
{
	return check_success(sqlite3_open_v2(database_file_path.c_str(), &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr));
}

bool DatabaseSQLite::reconnect(const std::string& databaseFile)
{
	if (db)
		sqlite3_close(db);
	return check_success(sqlite3_open_v2(databaseFile.c_str(), &db,  SQLITE_OPEN_READWRITE, nullptr));
}

bool DatabaseSQLite::initialize_views()
{
	if (!db)
		return false;
	for (const auto& [scriptFile, fileContent] : sql_script_files_map.getScriptMap())
		if (scriptFile.find("view") != std::string::npos)
			if (!execute_sql_from_file(fileContent))
				return false;
	return true;
}

bool DatabaseSQLite::initialize_database()
{
	if (!db)
		return false;
	if (!sql_script_files_map.loadScriptsRecursive(sql_script_files_path))
		return false;
	return execute_sql_from_file(sql_script_files_map.getScript(InlineSQL::INITIALIZE_DATABASE_SQL));
}

bool DatabaseSQLite::execute_sql_from_file(const std::string& sqlScript)
{
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &c_error_message);
	if (rc != SQLITE_OK)
	{
		show_error_function(c_error_message, "SQL script file execution");
		sqlite3_free(c_error_message);
		return false;
	}
	return true;
}

bool DatabaseSQLite::prepare_sql_script(const std::string& sql, StatementSQL& statement, const insertVector& data)
{
	if (check_success(sqlite3_prepare_v2(db, sql.c_str(), -1, statement, nullptr)))
	{
		return false;
	}

	if (!bind_values_to_sql(data, statement))
	{
		return false;
	}

	return true;
}

void DatabaseSQLite::set_path_to_sql_scripts_files(std::string path)
{
	this->sql_script_files_path = path;
}

void DatabaseSQLite::set_show_error_function(const ShowErrorFunction& func)
{
	show_error_function = func;
}

const std::string& DatabaseSQLite::get_sql_script(const std::string& scrpipt_file_name)
{
	return sql_script_files_map.getScript(scrpipt_file_name);
}

bool DatabaseSQLite::is_connected() const
{
	return db;
}

}
