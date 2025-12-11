//==============================================================================
// File       : Controller.cpp
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "Controller.h"

namespace marvus
{

Controller::Controller(errorFunctionSignature errorHandler) : marvusDB(DATABASE_FILE, errorHandler)
{
	this->argumentMethods["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; marvusDB.setPathToSQL_Scripts(vector[0]); };

	views[TableView::ESTABLISHMENTS_VIEW] = InlineSQL::SELECT_ESTABLISHMENTS;
	views[TableView::CATEGORIES_VIEW] = InlineSQL::SELECT_CATEGORIES;
	views[TableView::PAYMENTS_VIEW] = InlineSQL::SELECT_PAYMENTS;
	views[TableView::PAYMENTS_VIEW_FOR_MONTH] = InlineSQL::SELECT_PAYMENTS_WHERE_MONTH;
	views[TableView::PAYMENT_MACRO_VIEW] = InlineSQL::SELECT_PAYMENT_MACROS;
	views[TableView::STAT_PAYMENT_SUMMARY] = InlineSQL::SELECT_PAYMENT_SUMMARY;
}

void Controller::configure(consolelib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const consolelib::argVectorItem& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
	}
}

bool Controller::initDB(std::string& errorMsg)
{
	if (!marvusDB.initializeDatabase())
	{
		errorMsg = "Database initialization failed.\nExiting program!";
		return true;
	}

	std::vector<std::string> views;
	views.emplace_back(InlineSQL::INITIALIZE_VIEWS);
	views.emplace_back(InlineSQL::STAT_YEAR_SUMMARY);

	for (const std::string& view : views)
	{
		if (!marvusDB.executeFileSQL(marvusDB.getScriptSQL(view)))
		{
			errorMsg = "View " + view + " initialization failed.\nExiting program!";
			return true;
		}
	}

	return false;
}

bool Controller::connectToDB(const std::string& name)
{
	std::filesystem::path databaseFile(name);
	if (databaseFile.extension() != ".db")
	{
		return marvusDB.reconnect(databaseFile.generic_string() + ".db");
	}
	return marvusDB.reconnect(databaseFile.generic_string());
}

void Controller::dropDB()
{
	marvusDB.executeFileSQL(marvusDB.getScriptSQL(InlineSQL::DROP_DATABASE));
	marvusDB.initializeDatabase();
	marvusDB.initializeViews();
}

tableHeaderAndData Controller::obtainDataFromView(TableView view, const insertVector& data)
{
	auto viewPair = views.find(view);
	if (viewPair == views.end())
		return {};
	return marvusDB.obtainFromFilterView(marvusDB.getScriptSQL(viewPair->second), data);
}

bool Controller::insertEntity(const Establishment& e)
{
	return marvusDB.insertEstablishment(e);
}

bool Controller::insertCategory(const Category& c)
{
	return marvusDB.insertCategory(c);
}

bool Controller::insertPayment(const Payment& p)
{
	return marvusDB.insertPayment(p);
}

bool Controller::importFromZIP(const std::string& path, std::string& errorMessage)
{
	ToolsIO io(*this);
	return io.importDataFromZip(path, errorMessage);
}

bool Controller::exportToZIP(const std::string& path, std::string& errorMessage)
{
	return false;
}

void Controller::setShowErrorFunction(errorFunctionSignature func)
{
	marvusDB.setShowErrorFunction(func);
}

std::string Controller::aboutApplication()
{
	std::stringstream aboutStringStream;
	aboutStringStream << _MARVUS_VERSION << "\n\n";
	aboutStringStream << _COPYRIGHT_HEADER;
	aboutStringStream << "This version was compiled on: " << __DATE__ << " " << __TIME__ << "\n";
	aboutStringStream << "C++ version: " << __cplusplus << "\n\n";

	aboutStringStream << consolelib::ConsoleLib::aboutLibrary();
	return aboutStringStream.str();
}

bool Controller::insertPaymentMacro(const PaymentMacro& pm)
{
	return marvusDB.insertPaymentMacro(pm);
}

} /* namespace marvus */
