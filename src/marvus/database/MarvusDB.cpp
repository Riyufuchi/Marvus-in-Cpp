//==============================================================================
// File       : MarvusDB.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MarvusDB.h"

namespace marvus
{

MarvusDB::MarvusDB() : MarvusDB("database.db")
{
}

MarvusDB::MarvusDB(std::string database) : Database(database, "sql/")
{
}

bool MarvusDB::insertEstablishment(const Establishment& establishment)
{
	return insertNewData({ insertData {true, establishment.name} }, InlineSQL::INSERT_ESTABLISHMENT);

}

bool MarvusDB::insertCategory(const Category& category)
{
	static const std::string SQL_INSERT = MarvusDB::sqlScriptFiles.getScript(InlineSQL::INSERT_CATEGORY);
	return insertNewData({ insertData{true, category.name} }, SQL_INSERT);
}

bool MarvusDB::insertPayment(const Payment& payment)
{
	static const std::string SQL_INSERT_PAYMENT = MarvusDB::sqlScriptFiles.getScript(InlineSQL::INSERT_PAYMENT);
	insertVector data;
	data.emplace_back(insertData{true, payment.ent_key});
	data.emplace_back(insertData{true, payment.category_key});
	data.emplace_back(insertData{true, payment.value});
	data.emplace_back(insertData{true, payment.date});
	data.emplace_back(insertData{false, payment.note});

	return insertNewData(data, SQL_INSERT_PAYMENT);
}

} /* namespace marvus */
