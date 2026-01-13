//==============================================================================
// File       : Controller.h
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_CONTROLLER_H_
#define MARVUS_CONTROLLER_H_

// Local
#include "../database/marvus_db.h"
#include "../tools/io_tools.h"
#include "../tools/config_json.h"
// ConsoleLib
#include "ArgumentParser.h"
#include "FileUtils.h"
#include "ConsoleLib.h"
#include "../inline_sql.h"

#define _COPYRIGHT_HEADER "Riyufuchi (c) 2025 - 2026\n"

#define _APP_NAME "Marvus in C++"
#define _APP_VERSION "0.8 - Alpha"

#ifdef DEBUG
	#define _MARVUS_VERSION _APP_NAME " v" _APP_VERSION " (debug)" __DATE__ __TIME__
#else
	#define _MARVUS_VERSION _APP_NAME " v" _APP_VERSION
#endif

namespace marvus
{

enum class Table
{
	PAYMENTS,
	ENUM_TABLE,
	STAT_TABLE,
	GRAPH
};

enum class TableView
{
	PAYMENTS_VIEW,
	ESTABLISHMENTS_VIEW,
	CATEGORIES_VIEW,
	PAYMENTS_VIEW_FOR_MONTH,
	PAYMENT_MACRO_VIEW,
	STAT_PAYMENT_SUMMARY,
	STAT_DAILY_TOTAL
};

class Controller
{
protected:
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argument_functions_map;
	std::unordered_map<marvus::TableView, std::string> table_views_map;
	ConfigJSON config_json_file;
	MarvusDB marvus_database;
	ShowErrorFunction show_error_function;
public:
	Controller(const ShowErrorFunction& show_error_function = [](const std::string& message, const std::string& title) { std::cerr << title << ": " << message << "\n"; });
	virtual ~Controller() = default;
	void configure(consolelib::argVector& config);
	// Database file IO
	bool initialize_database(std::string& error_message);
	void drop_database();
	void load_and_init_database();
	bool connect_to_database(const std::string& name);
	bool create_new_database(const std::string& name);
	bool is_database_connected() const;
	// Database interaction
	bool insert_entity(const Establishment& e);
	bool insert_category(const Category& c);
	bool insert_payment(const Payment& p);
	bool insert_payment_macro(const PaymentMacro& pm);
	tableHeaderAndData obtain_data_from_view(TableView view, const insertVector& data = {});
	// Other IO
	void set_show_error_function(const ShowErrorFunction& show_error_function);
	bool import_from_zip(const std::string& path, std::string& error_message);
	bool export_to_zip(const std::string& path, std::string& error_message);
	// Static
	static std::string obtain_about_application_string();
};

} /* namespace marvus */

#endif /* MARVUS_CONTROLLER_H_ */
