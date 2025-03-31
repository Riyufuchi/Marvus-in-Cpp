#ifndef KEO_DEFAULT_DB_HPP
#define KEO_DEFAULT_DB_HPP

#include <string>
#include <vector>

#include "KeoDB.h"

namespace KeoDefaults
{
	// Table headers
	inline const std::vector<std::string> PEOPLE_TABLE_HEADER = { "First name", "Middle name", "Last name", "Job title" };
	inline const std::vector<std::string> FARMLANDS_TABLE_HEADER = { "Size", "Planted crops", "Overseer", "Overseer role" };
	// Table enums
	inline const std::vector<std::string> JOBS = { "King", "Farmer", "Soldier", "Assistant" };
	inline const std::vector<std::string> CROPS = { "Opium poppy", "Green tea", "Wheet", "Weed" };
	inline const std::vector<std::string> PEOPLE_CSV = { "Pagan;N/A;Min;1", "John;N/A;Doe;3", "Paul;De Pleur;Harmon;4"};
	inline const std::vector<std::string> FARMLANDS_CSV = { "10;1;1", "20;2;2", "40;4;3"};

class KeoInserter
{
	public:
		KeoInserter() = default;
		~KeoInserter() = default;

		static bool insertFarmlads(keo::KeoDB& db)
		{
			const int NUM_OF_ATTRIBUTES = 3;
			std::istringstream iss;
			int x = 0;
			std::string token;
			int landSize = 0;
			int cropID = 0;
			int overseerID = 0;
			for (const auto& item : FARMLANDS_CSV)
			{
				iss = std::istringstream(item);
				for (x = 0; x < NUM_OF_ATTRIBUTES; x++)
				{
					if (std::getline(iss, token, ';'))
					{
						switch (x)
						{
							case 0: landSize = std::stoi(token); break;
							case 1: cropID = std::stoi(token); break;
							case 2: overseerID = std::stoi(token); break;
						}
					}
					else
					{
						return false;
					}
				}
				if (!db.insertFarmland(landSize, cropID, overseerID))
				{
					return false;
				}
			}
			return true;
		}
};
}
#endif
