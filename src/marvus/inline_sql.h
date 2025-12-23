//==============================================================================
// File       : InlineSQL.h
// Author     : riyufuchi
// Created on : Nov 27, 2025
// Last edit  : Dec 10, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_INLINE_SQL_H_
#define MARVUS_INLINE_SQL_H_

#include <string>

namespace marvus
{
class InlineSQL
{
public:
	static inline const std::string SQL_ROOT_FOLDER = "sql/";
	static inline const std::string SQL_SELECT_FOLDER ="selects/";
	static inline const std::string SQL_INSERT_FOLDER = "inserts/";
	static inline const std::string SQL_TOOLS_FOLDER = "tools/";
	static inline const std::string SQL_VIEWS_FOLDER = "views/";
	static inline const std::string SQL_STATS_FOLDER = "stats/";
	// SELECTS
	static inline const std::string SELECT_ESTABLISHMENTS = SQL_SELECT_FOLDER + "establishment_select.sql";
	static inline const std::string SELECT_CATEGORIES = SQL_SELECT_FOLDER + "category_select.sql";
	static inline const std::string SELECT_PAYMENTS = SQL_SELECT_FOLDER + "payment_select.sql";
	static inline const std::string SELECT_PAYMENTS_WHERE_MONTH = SQL_SELECT_FOLDER + "payment_select_where_month.sql";
	static inline const std::string SELECT_PAYMENT_MACROS = SQL_SELECT_FOLDER + "payment_macro_select.sql";
	static inline const std::string SELECT_PAYMENT_SUMMARY = SQL_SELECT_FOLDER + "payment_summary_select.sql";
	static inline const std::string SELECT_DAILY_TOTAL = SQL_SELECT_FOLDER + "select_daily_total.sql";
	// VIEWS
	static inline const std::string INITIALIZE_VIEWS = SQL_VIEWS_FOLDER + "init_views.sql";
	// INSERTS
	static inline const std::string INSERT_ESTABLISHMENT = SQL_INSERT_FOLDER + "insert_establishment.sql";
	static inline const std::string INSERT_CATEGORY = SQL_INSERT_FOLDER + "insert_category.sql";
	static inline const std::string INSERT_PAYMENT = SQL_INSERT_FOLDER + "insert_payment.sql";
	static inline const std::string INSERT_PAYMENT_MACRO = SQL_INSERT_FOLDER + "insert_payment_macro.sql";
	// STATS VIEWS
	static inline const std::string STAT_YEAR_SUMMARY = SQL_STATS_FOLDER + "payment_summary.sql";
	static inline const std::string STAT_DAILY_TOTAL = SQL_STATS_FOLDER + "daily_total.sql";
	// DATABASE TOOLS
	static inline const std::string DROP_DATABASE = SQL_TOOLS_FOLDER + "drop_db.sql";
	static inline const std::string INITIALIZE_DATABASE_SQL = SQL_TOOLS_FOLDER + "initialize_database.sql";
	InlineSQL() = default;
	virtual ~InlineSQL() = default;
};

} /* namespace marvus */

#endif /* MARVUS_INLINE_SQL_H_ */
