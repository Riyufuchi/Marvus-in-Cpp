#ifndef KEO_DB_H
#define KEO_DB_H

#include "../database/Database.h"

namespace keo
{

inline const std::string BASIC_EMP_VIEW = "basic_emp_view.sql";
inline const std::string BASIC_FARMLANDS_VIEW = "basic_farmlands_view.sql";
inline const std::string INSERT_JOB_TITLE = "insert_job_title.sql";
inline const std::string INSERT_EMPLOYEE = "insert_employee.sql";
inline const std::string INSERT_CROP_TYPE = "insert_crop_type.sql";
inline const std::string INSERT_FARMLAND = "insert_farmland.sql";

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
	public:
		KeoDB();
		KeoDB(std::string database);
		virtual ~KeoDB();
		bool insertJobTitle(std::string title);
		bool insertCropType(std::string type);
		// Entities insert
		bool insertEmployee(Employee emp);
		bool insertFarmland(int farmSize, int cropID, int overseerID);
		std::vector<Employee> getEmployees();
		std::vector<Farmland> getFarmlands();
};
}
#endif /* EMPLOYEEDB_H */
