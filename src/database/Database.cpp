#include "Database.h"

namespace MarvusDB
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

std::vector<std::string> Database::obtainTableHeader(const std::string& sql)
{
	std::vector<std::string> texts;
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &c_ErrorMessage);
	if (rc != SQLITE_OK)
	{
		wxMessageBox(wxString::Format("%s", c_ErrorMessage), "SQL error", wxOK | wxICON_ERROR);
		sqlite3_free(c_ErrorMessage);
		return texts;
	}



	return texts;
}

}
