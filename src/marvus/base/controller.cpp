//==============================================================================
// File       : Controller.cpp
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "controller.h"

namespace marvus
{

Controller::Controller(const ShowErrorFunction& show_error_function) : marvus_database(show_error_function), show_error_function(show_error_function)
{
	this->argument_functions_map["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; marvus_database.set_path_to_sql_scripts_files(vector[0]); };

	table_views_map[TableView::ESTABLISHMENTS_VIEW] = InlineSQL::SELECT_ESTABLISHMENTS;
	table_views_map[TableView::CATEGORIES_VIEW] = InlineSQL::SELECT_CATEGORIES;
	table_views_map[TableView::PAYMENTS_VIEW] = InlineSQL::SELECT_PAYMENTS;
	table_views_map[TableView::PAYMENTS_VIEW_FOR_MONTH] = InlineSQL::SELECT_PAYMENTS_WHERE_MONTH;
	table_views_map[TableView::PAYMENT_MACRO_VIEW] = InlineSQL::SELECT_PAYMENT_MACROS;
	table_views_map[TableView::STAT_PAYMENT_SUMMARY] = InlineSQL::SELECT_PAYMENT_SUMMARY;
	table_views_map[TableView::STAT_DAILY_TOTAL] = InlineSQL::SELECT_DAILY_TOTAL;
}

void Controller::configure(consolelib::argVector& config)
{
	auto it = argument_functions_map.find("");
	for (const consolelib::argVectorItem& argument : config)
	{
		it = argument_functions_map.find(argument.first);
		if (it != argument_functions_map.end())
			it->second(argument.second);
	}
}

bool Controller::initialize_database(std::string& error_message)
{
	if (!marvus_database.initialize_database())
	{
		error_message = "Database initialization failed.\nExiting program!";
		return true;
	}

	std::vector<std::string> views;
	views.emplace_back(InlineSQL::INITIALIZE_VIEWS);
	views.emplace_back(InlineSQL::STAT_YEAR_SUMMARY);
	views.emplace_back(InlineSQL::STAT_DAILY_TOTAL);

	for (const std::string& view : views)
	{
		if (!marvus_database.execute_sql_from_file(marvus_database.get_sql_script(view)))
		{
			error_message = "View " + view + " initialization failed.\nExiting program!";
			return true;
		}
	}

	return false;
}

bool Controller::connect_to_database(const std::string& name)
{
	std::filesystem::path database_file(name);
	if (database_file.extension() != ".db")
	{
		return !marvus_database.reconnect(database_file.generic_string() + ".db");
	}
	return !marvus_database.reconnect(database_file.generic_string());
}

void Controller::drop_database()
{
	marvus_database.execute_sql_from_file(marvus_database.get_sql_script(InlineSQL::DROP_DATABASE));
	marvus_database.initialize_database();
	marvus_database.initialize_views();
}

void Controller::load_and_init_database()
{
	if (!config_json_file.get_auto_load_database())
		return;
	std::string msg;
	if (connect_to_database(config_json_file.get_database_file_path()))
		if (initialize_database(msg))
			show_error_function(msg, "Database initialization error");
}

tableHeaderAndData Controller::obtain_data_from_view(TableView view, const insertVector& data)
{
	auto viewPair = table_views_map.find(view);
	if (viewPair == table_views_map.end())
		return {};
	return marvus_database.obtain_data_from_filtered_view(marvus_database.get_sql_script(viewPair->second), data);
}

bool Controller::insert_entity(const Establishment& e)
{
	return marvus_database.insert_establishment(e);
}

bool Controller::insert_category(const Category& c)
{
	return marvus_database.insert_category(c);
}

bool Controller::insert_payment(const Payment& p)
{
	return marvus_database.insert_payment(p);
}

bool Controller::import_from_zip(const std::string& path, std::string& error_message)
{
	ToolsIO io(*this);
	return io.import_from_zip(path, error_message);
}

bool Controller::export_to_zip(const std::string& , std::string& )
{
	return false;
}

void Controller::set_show_error_function(const ShowErrorFunction& show_error_function)
{
	marvus_database.set_show_error_function(show_error_function);
}

bool Controller::create_new_database(const std::string& name)
{
	std::filesystem::path database_file(name);
	if (database_file.extension() != ".db")
	{
		return !marvus_database.create_new_database_file(database_file.generic_string() + ".db");
	}
	return !marvus_database.create_new_database_file(database_file.generic_string());
}

bool Controller::is_database_connected() const
{
	return marvus_database.is_connected();
}

std::string Controller::obtain_about_application_string()
{
	std::stringstream about_string_stream;
	about_string_stream << _MARVUS_VERSION << "\n\n";
	about_string_stream << _COPYRIGHT_HEADER;
	about_string_stream << "This version was compiled on: " << __DATE__ << " " << __TIME__ << "\n";
	about_string_stream << "C++ version: " << __cplusplus << "\n\n";

	about_string_stream << consolelib::aboutLibrary();
	return about_string_stream.str();
}

bool Controller::insert_payment_macro(const PaymentMacro& pm)
{
	return marvus_database.insert_payment_macro(pm);
}

} /* namespace marvus */
