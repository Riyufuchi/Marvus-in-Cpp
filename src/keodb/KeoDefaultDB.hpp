#ifndef KEO_DEFAULT_DB_HPP
#define KEO_DEFAULT_DB_HPP

#include <string>
#include <vector>

#include "KeoDB.h"
#include "ScriptMap.h"

namespace KeoDefaults
{
	// Table headers
	inline const std::vector<std::string> PEOPLE_TABLE_HEADER = { "First name", "Middle name", "Last name", "Job title" };
	inline const std::vector<std::string> FARMLANDS_TABLE_HEADER = { "Size", "Planted crops", "Overseer", "Overseer role" };

class KeoInserter
{
	private:
		ConsoleLib::ScriptMap sql;
		keo::KeoDB& db;
	public:
		KeoInserter(keo::KeoDB& db) : db(db)
		{
			sql.loadScripts("../data/");
		};
		~KeoInserter() = default;

		bool fillEnums()
		{
			return db.executeSQL(sql.getScript("fill_enums.sql"));
		}

		bool fillTables()
		{
			return db.executeSQL(sql.getScript("fill_tables.sql"));
		}
};
}
#endif
