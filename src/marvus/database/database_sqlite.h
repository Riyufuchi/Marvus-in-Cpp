//==============================================================================
// File       : DatabaseSQLite.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef DATABASE_H
#define DATABASE_H

#include <variant>
#include <vector>
#include <functional>

// Local - Marvus
#include "statement_sql.h"
#include "../inline_sql.h"
// SQLite
#include "../../external/sqlite/sqlite3.h"
// ConsoleLib
#include "consolelib/tools/script_map.h"

namespace marvus
{

using valueForDB = std::variant<std::monostate, int, long long, double, std::string>;

using insertData = valueForDB;
using insertVector = std::vector<insertData>;
using tableRow = std::vector<std::string>;
using tableRowVector = std::vector<tableRow>;
using tableHeaderAndData = std::pair<tableRow, tableRowVector>;

using ShowErrorFunction = std::function<void(const std::string&, const std::string&)>;

class DatabaseSQLite
{
	protected:
		consolelib::ScriptMap sql_script_files_map;
		sqlite3* db; // SQLite database connection
		std::string sql_script_files_path;
		char* c_error_message;
		ShowErrorFunction show_error_function;
		bool check_success(int result, int expected_result = SQLITE_OK);
	private:
		tableRowVector table_data;
		int row_callback(void* data, int argc, char** argv, char** azColName); // Callback function to handle each row of the result
		int bind_values_to_sql(const insertVector& data, StatementSQL& stmt_sql);
	public:
		DatabaseSQLite(const ShowErrorFunction& show_error_function);
		DatabaseSQLite(const std::string& sql_scripts, const ShowErrorFunction& show_error_function);
		virtual ~DatabaseSQLite();
		// Functions
		bool is_connected() const;
		bool create_new_database_file(const std::string& database_file_path);
		bool initialize_views();
		bool initialize_database();
		bool reconnect(const std::string& databaseFile);
		bool execute_sql_from_file(const std::string& sql);
		bool prepare_sql_script(const std::string& sql, StatementSQL& statement, const insertVector& data = {});
		int insert_new_row(const insertVector& data, const std::string& insert_sql);
		tableRowVector obtain_data_from_table(const std::string& selectSQL);
		tableHeaderAndData obtain_data_from_filtered_view(const std::string& viewSQL, const insertVector& data = {});
		// Setters
		void set_path_to_sql_scripts_files(std::string path);
		void set_show_error_function(const ShowErrorFunction& func);
		// Getters
		const std::string& get_sql_script(const std::string& scrpipt_file_name);
};
}
#endif /* DATABASE_H */ 
