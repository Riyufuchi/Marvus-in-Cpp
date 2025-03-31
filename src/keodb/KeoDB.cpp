#include "KeoDB.h"

namespace keo
{

KeoDB::KeoDB() : KeoDB("database.db")
{
}

KeoDB::KeoDB(std::string database) : MarvusDB::Database(database, "../sql/")
{
}

KeoDB::~KeoDB()
{
}

bool KeoDB::insertJobTitle(std::string title)
{
	if (title == "")
		return false;

	std::string sqlTemplate = sql.getScript(INSERT_JOB_TITLE);
	if (sqlTemplate == "")
		return false;

	result = sqlite3_prepare_v2(db, sqlTemplate.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return false;

	// Bind the title to the placeholder in the SQL
	result = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
	if (checkSuccessFor("SQL binding"))
		return false;

	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution of job title insert", SQLITE_DONE))
		return false;

	sqlite3_finalize(stmt);
	return true;
}

bool KeoDB::insertCropType(std::string type)
{
	if (type == "")
		return false;

	std::string sqlTemplate = sql.getScript(INSERT_CROP_TYPE);
	if (sqlTemplate == "")
		return false;

	result = sqlite3_prepare_v2(db, sqlTemplate.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return false;

	// Bind the title to the placeholder in the SQL
	result = sqlite3_bind_text(stmt, 1, type.c_str(), -1, SQLITE_STATIC);
	if (checkSuccessFor("SQL binding"))
		return false;

	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution of insert", SQLITE_DONE))
		return false;

	sqlite3_finalize(stmt);
	return true;
}

bool KeoDB::insertFarmland(int farmSize, int cropID, int overseerID)
{
	std::string sqlTemplate = sql.getScript(INSERT_FARMLAND);
	if (sqlTemplate == "")
		return false;
	result = sqlite3_prepare_v2(db, sqlTemplate.c_str(), -1, &stmt, nullptr);
	if (checkSuccessFor("Statement preparation"))
		return false;

	sqlite3_bind_int(stmt, 1, farmSize);
	sqlite3_bind_int(stmt, 2, cropID);
	sqlite3_bind_int(stmt, 3, overseerID);

	result = sqlite3_step(stmt);
	if (checkSuccessFor("SQL execution", SQLITE_DONE))
		return false;
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

std::vector<Farmland> KeoDB::getFarmlands()
{
	std::vector<Farmland> lands;

	std::string sqlTemp = sql.getScript(BASIC_FARMLANDS_VIEW);
	char* errMsg = nullptr;
	if (sqlite3_exec(db, sqlTemp.c_str(), callbackFarmland, &lands, &errMsg) != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

	return lands;
}

// Callback function to handle each row of the result
int callback(void* data, int /*argc*/, char** argv, char** /*azColName*/)
{
	std::vector<Employee>* employees = reinterpret_cast<std::vector<Employee>*>(data);
	employees->push_back(Employee{std::stoi(argv[0]), argv[1], argv[2], argv[3], argv[4]});
	return 0; // Continue processing
}

std::vector<Employee> KeoDB::getEmployees()
{
	std::vector<Employee> employees;

	std::string sqlTemp = sql.getScript(BASIC_EMP_VIEW);

	// Use sqlite3_exec to execute the query and handle the results via callback
	char* errMsg = nullptr;
	if (sqlite3_exec(db, sqlTemp.c_str(), callback, &employees, &errMsg) != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

	return employees;
}

}
