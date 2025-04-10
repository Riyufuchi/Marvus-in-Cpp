#ifndef KEO_DB_H
#define KEO_DB_H

#include <unordered_map>

#include "../database/Database.h"

namespace keo
{

// VIEWS
inline const std::string BASIC_EMP_VIEW = "basic_emp_view.sql";
inline const std::string BASIC_FARMLANDS_VIEW = "basic_farmlands_view.sql";
inline const std::string BASIC_MINES_VIEW = "basic_mine_view.sql";
// INSERTS
inline const std::string INSERT_EMPLOYEE = "insert_employee.sql";
inline const std::string INSERT_FARMLAND = "insert_farmland.sql";

using tableRowStructure = std::vector<std::string>;
using tableStructure = std::vector<tableRowStructure>;
using tableHeaderAndData = std::pair<std::vector<std::string>, tableStructure>;

enum class Table
{
	PEOPLE,
	FARMLANDS,
	MINES
};

enum class TypeTables
{
	JOBS,
	CROPS,
	ORES
};

struct Employee
{
	int id {0};
	std::string name {""};
	std::string middle_name {""};
	std::string last_name {""};
	std::string jobTitle {"1"};
};

struct Farmland
{
	int id {0};
	int size {0};
	std::string crop_type {""};
	std::string overseer_name {""};
	std::string overseer_role {""};
};

class KeoDB : public MarvusDB::Database
{
	private:
		tableStructure tableData;
		std::unordered_map<TypeTables, std::string> typeTableSQLs;
		int rowCallback(void* data, int argc, char** argv, char** azColName); // Callback function to handle each row of the result
	public:
		KeoDB();
		KeoDB(std::string database);
		virtual ~KeoDB();
		bool initializeViews();
		bool insertEnumValue(TypeTables typeTable, const std::string& value);
		// Entities insert
		bool insertEmployee(Employee emp);
		//bool insertFarmland(int farmSize, int cropID, int overseerID);
		tableStructure obtainTableData(Table table);
		tableHeaderAndData obtainTableHeaderAndData(Table table);
};
}
#endif /* EMPLOYEEDB_H */
