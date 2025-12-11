//==============================================================================
// File       : Controller.h
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_CONTROLLER_H_
#define MARVUS_CONTROLLER_H_

// wxWidgets
#include <wx/wx.h>
// Local
#include "database/MarvusDB.h"
#include "InlineSQL.h"
#include "tools/ToolsIO.h"
// ConsoleLib
#include "ArgumentParser.h"
#include "FileUtils.h"
#include "ConsoleLib.h"

#define _COPYRIGHT_HEADER "Riyufuchi (c) 2025\n"

#define _APP_NAME "Marvus in C++"
#define _APP_VERSION "1.6 - Alpha"

#ifdef DEBUG
	#define _MARVUS_VERSION _APP_NAME " v" _APP_VERSION " (debug)"
#else
	#define _MARVUS_VERSION _APP_NAME " v" _APP_VERSION
#endif

namespace marvus
{
inline const std::string DATABASE_FILE = "marvus.db";

enum class Table
{
	PAYMENTS,
	ENUM_TABLE,
	STAT_TABLE
};

enum class TableView
{
	PAYMENTS_VIEW,
	ESTABLISHMENTS_VIEW,
	CATEGORIES_VIEW,
	PAYMENTS_VIEW_FOR_MONTH,
	PAYMENT_MACRO_VIEW,
	STAT_PAYMENT_SUMMARY
};

class Controller
{
private:
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	std::unordered_map<marvus::TableView, std::string> views;
	MarvusDB marvusDB;
public:
	Controller(errorFunctionSignature errorHandler = [](const std::string& title, const std::string& message) { std::cerr << title << ": " << message << "\n"; });
	virtual ~Controller() = default;
	void configure(consolelib::argVector& config);
	// Database file IO
	bool initDB(std::string& errorMsg);
	void dropDB();
	bool connectToDB(const std::string& name);
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
