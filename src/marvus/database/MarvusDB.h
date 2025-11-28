//==============================================================================
// File       : MarvusDB.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_MARVUSDB_H_
#define MARVUS_MARVUSDB_H_

#include "Database.h"

#include "../InlineSQL.h"

namespace marvus
{

struct Establishment
{
	int id { 0 };
	std::string name { "NULL" };
};

struct Category
{
	int id { 0 };
	std::string name { "NULL" };
};

struct Payment
{
	int id { 0 };
	int ent_key { 0 };
	int category_key { 0 };
	std::string value { "0" };
	std::string date {"1.1.2000"};
	std::string note { "" };
};

class MarvusDB : public Database
{
public:
	MarvusDB();
	MarvusDB(std::string database);
	virtual ~MarvusDB() = default;
	bool insertEstablishment(const Establishment& establishment);
	bool insertCategory(const Category& category);
	bool insertPayment(const Payment& payment);
};

} /* namespace marvus */

#endif /* MARVUS_MARVUSDB_H_ */
