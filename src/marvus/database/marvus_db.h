//==============================================================================
// File       : MarvusDB.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_MARVUSDB_H_
#define MARVUS_MARVUSDB_H_

#include "../inline_sql.h"
#include "database_sqlite.h"

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
	std::string date { "2000-01-01" };
	std::string note { "" };
};

struct PaymentMacro
{
	int id { 0 };
	int ent_key { 0 };
	int category_key { 0 };
	std::string value { "0" };
	std::string note { "" };
};

class MarvusDB : public DatabaseSQLite
{
public:
	MarvusDB(const ShowErrorFunction& show_error_function);
	virtual ~MarvusDB() = default;
	bool insert_establishment(const Establishment& establishment);
	bool insert_category(const Category& category);
	bool insert_payment(const Payment& payment);
	bool insert_payment_macro(const PaymentMacro& payment_macro);
};

} /* namespace marvus */

#endif /* MARVUS_MARVUSDB_H_ */
