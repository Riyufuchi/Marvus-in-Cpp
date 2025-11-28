#ifndef DATABASE_H
#define DATABASE_H

#include <variant>

#include <wx/wx.h>
#include <sqlite3.h>

#include "ScriptMap.h"
#include "StatementGuard.h"

namespace marvus
{

inline const std::string INIT_DB_SQL = "initialize_database.sql";

using valueForDB = std::variant<std::monostate, int, double, std::string>;

struct InsertData
{
	bool catchNull { true };
	valueForDB value;
};

using insertData = InsertData;
using insertVector = std::vector<insertData>;
using tableRow = std::vector<std::string>;
using tableRowVector = std::vector<tableRow>;
using tableHeaderAndData = std::pair<tableRow, tableRowVector>;

class Database
{
	protected:
		ConsoleLib::ScriptMap sqlScriptFiles;
		sqlite3* db; // SQLite database connection
		sqlite3_stmt* stmt;
		std::string sqlScriptsPath;
		int result;
		char* c_ErrorMessage;
		bool checkSuccessFor(const std::string& action, int expectedResult = SQLITE_OK);
	private:
		tableRowVector tableData;
		int rowCallback(void* data, int argc, char** argv, char** azColName); // Callback function to handle each row of the result
	public:
		Database(std::string databaseFile);
		Database(std::string databaseFile, std::string sqlScripts);
		virtual ~Database();
		// Procedures
		void setSQL_Scripts(std::string path);
		// Functions
		bool initializeViews();
		bool initializeDatabase();
		bool reconnect(const std::string& databaseFile);
		bool executeSQL(const std::string& sql);
		bool executeSQL_script(const std::string& sql);
		int insertNewData(const insertVector& data, const std::string& insertSQL);
		tableRowVector obtainTableData(const std::string& selectSQL);
		tableHeaderAndData obtainTableHeaderAndData(const std::string& viewSQL);
};
}
#endif /* DATABASE_H */ 
