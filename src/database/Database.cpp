#include "Database.h"

namespace MarvusDB
{
Database::Database(std::string databaseFile) : Database(databaseFile, "")
{
}

Database::Database(std::string databaseFile, std::string sqlScripts) : stmt(nullptr), sqlScripts(sqlScripts), result(0)
{
	// Open the SQLite database and create the table
	sqlite3_open(databaseFile.c_str(), &db);
}

Database::~Database()
{
	if (db)
		sqlite3_close(db);
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

bool Database::initializeDatabase()
{
	if (!sql.loadScripts(sqlScripts))
		return false;
	std::string sqlScript = sql.getScript(INIT_DB_SQL);
	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("SQL error: %s", errMsg), "Error", wxOK | wxICON_ERROR);
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

bool Database::executeSQL(const std::string& sqlScript)
{
	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sqlScript.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("%s", errMsg), "SQL error", wxOK | wxICON_ERROR);
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

void Database::setSQL_Scripts(std::string path)
{
	this->sqlScripts = path;
}

}
