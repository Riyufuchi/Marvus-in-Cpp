//==============================================================================
// File       : MarvusDB.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Jan 15, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "marvus_db.h"

namespace marvus
{

MarvusDB::MarvusDB(const ShowErrorFunction& show_error_function) : DatabaseSQLite(InlineSQL::SQL_ROOT_FOLDER, show_error_function)
{
}

bool MarvusDB::insert_establishment(const Establishment& establishment)
{
	static const std::string SQL_INSERT = MarvusDB::sql_script_files_map.get_script(InlineSQL::INSERT_ESTABLISHMENT);
	return insert_new_row({ establishment.name }, SQL_INSERT);
}

bool MarvusDB::insert_category(const Category& category)
{
	static const std::string SQL_INSERT = MarvusDB::sql_script_files_map.get_script(InlineSQL::INSERT_CATEGORY);
	return insert_new_row({ category.name }, SQL_INSERT);
}

bool MarvusDB::insert_payment(const Payment& payment)
{
	static const std::string SQL_INSERT_PAYMENT = MarvusDB::sql_script_files_map.get_script(InlineSQL::INSERT_PAYMENT);
	insertVector data;
	data.emplace_back(payment.ent_key);
	data.emplace_back(payment.category_key);
	data.emplace_back(payment.value);
	data.emplace_back(payment.date);
	data.emplace_back(payment.note);

	return insert_new_row(data, SQL_INSERT_PAYMENT);
}

bool MarvusDB::insert_payment_macro(const PaymentMacro& payment_macro)
{
	static const std::string SQL_INSERT_PAYMENT_MACRO = MarvusDB::sql_script_files_map.get_script(InlineSQL::INSERT_PAYMENT_MACRO);
	insertVector data;
	data.emplace_back(payment_macro.ent_key);
	data.emplace_back(payment_macro.category_key);
	data.emplace_back(payment_macro.value);
	data.emplace_back(payment_macro.note);

	return insert_new_row(data, SQL_INSERT_PAYMENT_MACRO);
}

} /* namespace marvus */
