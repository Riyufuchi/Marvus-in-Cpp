#ifndef KEO_DEFAULT_DB_HPP
#define KEO_DEFAULT_DB_HPP

#include <string>
#include <vector>

#include "KeoDB.h"
#include "ScriptMap.h"

namespace KeoDefaults
{
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
