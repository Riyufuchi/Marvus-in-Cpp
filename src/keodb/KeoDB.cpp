#include "KeoDB.h"

namespace keo
{

KeoDB::KeoDB() : KeoDB("database.db")
{
}

KeoDB::KeoDB(std::string database) : MarvusDB::Database(database, "../sql/")
{
	typeTableSQLs[TypeTables::JOBS] = "insert_job_title.sql";
	typeTableSQLs[TypeTables::CROPS] = "insert_crop_type.sql";
	typeTableSQLs[TypeTables::ORES] = "insert_ore_type.sql";
}

KeoDB::~KeoDB()
{
}

bool KeoDB::insertEnumValue(TypeTables typeTable, const std::string& value)
{
	if (value == "" || !typeTableSQLs.contains(typeTable))
		return false;

	std::string sqlTemplate = sql.getScript(typeTableSQLs.find(typeTable)->second);
	if (sqlTemplate == "")
		return false;

	result = sqlite3_prepare_v2(db, sqlTemplate.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return false;

	// Bind the title to the placeholder in the SQL
	result = sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
	if (checkSuccessFor("SQL binding"))
		return false;

	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution of insert", SQLITE_DONE))
		return false;

	sqlite3_finalize(stmt);
	return true;
}

bool KeoDB::insertEmployee(Employee emp)
{
	if (emp.name == "" || emp.jobTitle == "")
		return false;

	std::string sqlTemplate = sql.getScript(INSERT_EMPLOYEE);
	if (sqlTemplate == "")
		return false;

	result = sqlite3_prepare_v2(db, sqlTemplate.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return false;

	result = sqlite3_bind_text(stmt, 1, emp.name.c_str(), -1, SQLITE_STATIC);
	if (checkSuccessFor("SQL binding"))
		return false;

	if (emp.middle_name == "")
		result = sqlite3_bind_null(stmt, 2);
	else
		result = sqlite3_bind_text(stmt, 2, emp.middle_name.c_str(), -1, SQLITE_STATIC);

	if (checkSuccessFor("SQL binding"))
		return false;

	result = sqlite3_bind_text(stmt, 3, emp.last_name.c_str(), -1, SQLITE_STATIC);
	if (checkSuccessFor("SQL binding"))
		return false;

	result = sqlite3_bind_int(stmt, 4, std::stoi(emp.jobTitle));
	if (checkSuccessFor("SQL binding"))
		return false;

	// Finilize statement
	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution", SQLITE_DONE))
		return false;

	return true;
}

int callbackFarmland(void* data, int /*argc*/, char** argv, char** /*azColName*/)
{
	Farmland farmland;
	farmland.id = std::stoi(argv[0]);
	farmland.size = std::stoi(argv[1]);
	farmland.crop_type = argv[2];
	farmland.overseer_name = argv[3];
	farmland.overseer_role = argv[4];
	reinterpret_cast<std::vector<Farmland>*>(data)->push_back(farmland);
	return 0; // Continue processing
}

int KeoDB::rowCallback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRowStructure rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	tableData.push_back(std::move(rowData));
	return 0; // Continue processing
}

tableStructure KeoDB::getTableData(Table table)
{
	tableData.clear();
	std::string sqlView;
	switch (table)
	{
		case Table::PEOPLE: sqlView = sql.getScript(BASIC_EMP_VIEW); break;
		case Table::FARMLANDS: sqlView = sql.getScript(BASIC_FARMLANDS_VIEW); break;
		case Table::MINES: sqlView = sql.getScript(BASIC_MINES_VIEW); break;
	}

	char* errMsg = nullptr;
	if (sqlite3_exec(db, sqlView.c_str(),
		[](void* data, int argc, char** argv, char** azColName) -> int {
			return static_cast<KeoDB*>(data)->rowCallback(data, argc, argv, azColName);
		},
		this, &errMsg) != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

	return tableData;

}

} // Namespace
