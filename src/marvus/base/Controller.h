//==============================================================================
// File       : Controller.h
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Dec 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_CONTROLLER_H_
#define MARVUS_CONTROLLER_H_

// Local
#include "../database/MarvusDB.h"
#include "../InlineSQL.h"
#include "../tools/ToolsIO.h"
#include "../tools/ConfigJSON.h"
// ConsoleLib
#include "ArgumentParser.h"
#include "FileUtils.h"
#include "ConsoleLib.h"

#define _COPYRIGHT_HEADER "Riyufuchi (c) 2025\n"

#define _APP_NAME "Marvus in C++"
#define _APP_VERSION "0.5 - Beta"

#ifdef DEBUG
	#define _MARVUS_VERSION _APP_NAME " v" _APP_VERSION " (debug)"
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
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	std::unordered_map<marvus::TableView, std::string> views;
	ConfigJSON configFile;
	MarvusDB marvusDB;
	errorFunctionSignature errorHandler;
public:
	Controller(errorFunctionSignature errorHandler = [](const std::string& title, const std::string& message) { std::cerr << title << ": " << message << "\n"; });
	virtual ~Controller() = default;
	void configure(consolelib::argVector& config);
	// Database file IO
	bool initDB(std::string& errorMsg);
	void dropDB();
	void autoloadDatabase();
	bool connectToDB(const std::string& name);
	bool createNewDatabase(const std::string& name);
	bool isDatabaseConnected() const;
	// Database interaction
	bool insertEntity(const Establishment& e);
	bool insertCategory(const Category& c);
	bool insertPayment(const Payment& p);
	bool insertPaymentMacro(const PaymentMacro& pm);
	tableHeaderAndData obtainDataFromView(TableView view, const insertVector& data = {});
	// Other IO
	void setShowErrorFunction(errorFunctionSignature func);
	bool importFromZIP(const std::string& path, std::string& errorMessage);
	bool exportToZIP(const std::string& path, std::string& errorMessage);
	// Static
	static std::string aboutApplication();
};

} /* namespace marvus */

#endif /* MARVUS_CONTROLLER_H_ */
