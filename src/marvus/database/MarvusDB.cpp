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
	return insertNewData({ insertData {DataType::TEXT, true, establishment.name} }, InlineSQL::INSERT_ESTABLISHMENT);

}

bool MarvusDB::insertCategory(const Category& category)
{
	return insertNewData({ insertData{DataType::TEXT, true, category.name} }, InlineSQL::INSERT_CATEGORY);
}

bool MarvusDB::insertPayment(const Payment& payment)
{
	static const std::string SQL = sqlScriptFiles.getScript(InlineSQL::INSERT_PAYMENT);
	insertVector data;
	data.emplace_back(insertData{DataType::INTEGER, true, std::to_string(payment.ent_key)});
	data.emplace_back(insertData{DataType::INTEGER, true, std::to_string(payment.category_key)});
	data.emplace_back(insertData{DataType::TEXT, true, payment.value});
	data.emplace_back(insertData{DataType::TEXT, true, payment.date});
	data.emplace_back(insertData{DataType::TEXT, false, payment.note});

	return insertNewData(data, SQL);
}

} /* namespace marvus */
