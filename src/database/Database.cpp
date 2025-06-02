#include "Database.h"

namespace marvus
{
Database::Database(std::string databaseFile) : Database(databaseFile, "")
{
}

Database::Database(std::string databaseFile, std::string sqlScriptsPath) : stmt(nullptr), sqlScriptsPath(sqlScriptsPath), result(0), c_ErrorMessage(nullptr)
{
	// Open the SQLite database and create the table
	sqlite3_open(databaseFile.c_str(), &db);
}

Database::~Database()
{
	if (db)
		sqlite3_close(db);
}

int Database::rowCallback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRowStructure rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	tableData.push_back(std::move(rowData));
	return 0; // Continue processing
}

int Database::insertNewData(const insertVector& data, const std::string& insertSQL)
{
	if (insertSQL == "")
		return 0;

	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return 0;

	int x = 1;
	StatementGuard sg(stmt);

	for (const insertPair& dataPair : data)
	{
		if (dataPair.second == "")
			result = sqlite3_bind_null(stmt, x);
		else
			switch (dataPair.first)
			{
				case DataType::TEXT: result = sqlite3_bind_text(stmt, x, dataPair.second.c_str(), -1, SQLITE_STATIC); break;
				case DataType::INTEGER: result = sqlite3_bind_int(stmt, x, std::stoi(dataPair.second)); break;
			}

		if (checkSuccessFor("SQL binding"))
			return 0;
		x++;
	}

	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution of insert", SQLITE_DONE))
		return 0;

	return sqlite3_last_insert_rowid(db);
}

tableStructure Database::obtainTableData(const std::string& selectSQL)
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

tableHeaderAndData Database::obtainTableHeaderAndData(const std::string& viewSQL)
{
	tableRowStructure header;
	tableStructure tableData;

	if (!sqlite3_prepare_v2(db, viewSQL.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
	{
		std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
	}

	int colCount = sqlite3_column_count(stmt);
	int i = 0;
	const char* value = nullptr;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		tableRowStructure rowData;
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

	sqlite3_finalize(stmt);
	return tableHeaderAndData(header, tableData);
}

bool Database::checkSuccessFor(std::string action, int expectedResult)
{
	if (result != expectedResult)
	{
		wxMessageBox(wxString::Format("%s", sqlite3_errmsg(db)), action, wxOK | wxICON_ERROR);
		return true;
	}
	return false;
}

bool Database::reconnect(std::string databaseFile)
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
			if (!executeSQL(fileContent))
				return false;
	return true;
}

bool Database::initializeDatabase()
{
	if (!sqlScriptFiles.loadScripts(sqlScriptsPath))
		return false;
	std::string sqlScript = sqlScriptFiles.getScript(INIT_DB_SQL);
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &c_ErrorMessage);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("SQL error: %s", c_ErrorMessage), "Error", wxOK | wxICON_ERROR);
		sqlite3_free(c_ErrorMessage);
		return false;
	}
	return true;
}

bool Database::executeSQL(const std::string& sqlScript)
{
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &c_ErrorMessage);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("%s", c_ErrorMessage), "SQL error", wxOK | wxICON_ERROR);
		sqlite3_free(c_ErrorMessage);
		return false;
	}
	return true;
}

bool Database::executeSQL_script(const std::string& sqlScript)
{
	int rc = sqlite3_prepare_v2(db, sqlScript.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("%s", c_ErrorMessage), "SQL error", wxOK | wxICON_ERROR);
		sqlite3_free(c_ErrorMessage);
		return false;
	}
	return true;
}

void Database::setSQL_Scripts(std::string path)
{
	this->sqlScriptsPath = path;
}

}
