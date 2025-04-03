#ifndef DATABASE_H
#define DATABASE_H

#include <wx/wx.h>
#include <sqlite3.h>

#include "ScriptMap.h"

namespace MarvusDB
{

inline const std::string INIT_DB_SQL = "initialize_database.sql";

class Database
{
	protected:
		ConsoleLib::ScriptMap sql;
		sqlite3* db; // SQLite database connection
		sqlite3_stmt* stmt;
		std::string sqlScripts;
		int result;
		bool checkSuccessFor(std::string action, int expectedResult = SQLITE_OK);
	public:
		Database(std::string databaseFile);
		Database(std::string databaseFile, std::string sqlScripts);
		virtual ~Database();
		bool initializeDatabase();
		bool reconnect(std::string databaseFile);
		bool executeSQL(const std::string& sql);
		void setSQL_Scripts(std::string path);
};
}
#endif /* DATABASE_H */ 
