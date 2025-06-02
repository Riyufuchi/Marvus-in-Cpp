#include "KeoDB.h"

namespace keo
{

KeoDB::KeoDB() : KeoDB("database.db")
{
}

KeoDB::KeoDB(std::string database) : marvus::Database(database, "../sql/keo/")
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

	std::string sqlTemplate = sqlScriptFiles.getScript(typeTableSQLs.find(typeTable)->second);
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

	std::string sqlTemplate = sqlScriptFiles.getScript(INSERT_EMPLOYEE);
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

int KeoDB::rowCallback(void* /*data*/, int argc, char** argv, char** /*azColName*/)
{
	tableRowStructure rowData;
	rowData.reserve(argc); // Optimize vector allocation

	for (int i = 0; i < argc; i++)
		rowData.push_back(argv[i] ? std::string(argv[i]) : "NULL"); // Avoids string allocation
	tableData.push_back(std::move(rowData));
	return 0; // Continue processing
}

tableStructure KeoDB::obtainTableData(Table table)
{
	tableData.clear();
	std::string sqlView;
	switch (table)
	{
		case Table::PEOPLE: sqlView = sqlScriptFiles.getScript(BASIC_EMP_VIEW); break;
		case Table::FARMLANDS: sqlView = sqlScriptFiles.getScript(BASIC_FARMLANDS_VIEW); break;
		case Table::MINES: sqlView = sqlScriptFiles.getScript(BASIC_MINES_VIEW); break;
	}

	if (sqlite3_exec(db, sqlView.c_str(),
		[](void* data, int argc, char** argv, char** azColName) -> int {
			return static_cast<KeoDB*>(data)->rowCallback(data, argc, argv, azColName);
		},
		this, &c_ErrorMessage) != SQLITE_OK)
	{
		std::cerr << "SQL error: " << c_ErrorMessage << std::endl;
		sqlite3_free(c_ErrorMessage);
	}

	return tableData;
}

tableHeaderAndData KeoDB::obtainTableHeaderAndData(Table table)
{
	tableRowStructure header;
	tableData.clear();

	std::string sqlView = "SELECT * FROM ";
	switch (table)
	{
		case Table::PEOPLE: sqlView += "EMPLOYEE_VIEW;"; break;
		case Table::FARMLANDS: sqlView += "FARMLAND_VIEW;"; break;
		case Table::MINES: sqlView += "MINE_VIEW;"; break;
	}

	if (!sqlite3_prepare_v2(db, sqlView.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
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

} // Namespace
