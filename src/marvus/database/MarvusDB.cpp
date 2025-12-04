//==============================================================================
// File       : MarvusDB.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Dec 04, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MarvusDB.h"

namespace marvus
{

MarvusDB::MarvusDB(errorFunctionSignature errorHandler) : MarvusDB("database.db", errorHandler)
{
}

MarvusDB::MarvusDB(std::string database, errorFunctionSignature errorHandler) : Database(database, "sql/", errorHandler)
{
}

bool MarvusDB::insertEstablishment(const Establishment& establishment)
{
	static const std::string SQL_INSERT = MarvusDB::sqlScriptFiles.getScript(InlineSQL::INSERT_ESTABLISHMENT);
	return insertNewData({ establishment.name }, SQL_INSERT);
}

bool MarvusDB::insertCategory(const Category& category)
{
	static const std::string SQL_INSERT = MarvusDB::sqlScriptFiles.getScript(InlineSQL::INSERT_CATEGORY);
	return insertNewData({ category.name }, SQL_INSERT);
}

bool MarvusDB::insertPayment(const Payment& payment)
{
	static const std::string SQL_INSERT_PAYMENT = MarvusDB::sqlScriptFiles.getScript(InlineSQL::INSERT_PAYMENT);
	insertVector data;
	data.emplace_back(payment.ent_key);
	data.emplace_back(payment.category_key);
	data.emplace_back(payment.value);
	data.emplace_back(payment.date);
	data.emplace_back(payment.note);

	return insertNewData(data, SQL_INSERT_PAYMENT);
}

} /* namespace marvus */
