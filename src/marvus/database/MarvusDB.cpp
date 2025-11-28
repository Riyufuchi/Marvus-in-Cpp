//==============================================================================
// File       : MarvusDB.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 27, 2025
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
	return insertNewData({ insertPair {DataType::TEXT, true, establishment.name} }, InlineSQL::INSERT_ESTABLISHMENT);

}

bool MarvusDB::insertCategory(const Category& category)
{
	return insertNewData({ insertPair{DataType::TEXT, true, category.name} }, InlineSQL::INSERT_CATEGORY);
}

bool MarvusDB::insertPayment(const Payment& payment)
{
	insertVector data;
	data.emplace_back(insertPair{DataType::INTEGER, true, std::to_string(payment.ent_key)});
	data.emplace_back(insertPair{DataType::INTEGER, true, std::to_string(payment.category_key)});
	data.emplace_back(insertPair{DataType::TEXT, true, payment.value});
	data.emplace_back(insertPair{DataType::TEXT, true, payment.date});
	data.emplace_back(insertPair{DataType::TEXT, false, payment.note});

	return insertNewData(data, InlineSQL::INSERT_PAYMENT);
}

} /* namespace marvus */
