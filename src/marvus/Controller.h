//==============================================================================
// File       : Controller.h
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Dec 01, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_CONTROLLER_H_
#define MARVUS_CONTROLLER_H_

#include <wx/wx.h>

#include "database/MarvusDB.h"
#include "InlineSQL.h"
// consolelib
#include "ArgumentParser.h"
#include "FileUtils.h"
// miniZ
#include "../include/miniz.h"

namespace marvus
{
inline const std::string DATABASE_FILE = "marvus.db";

enum class Table
{
	PAYMENTS,
	ESTABLISHMENTS,
	CATEGORIES
};

enum class TableViews
{
	PAYMENTS_VIEW,
	ESTABLISHMENTS_VIEW,
	CATEGORIES_VIEW,
	PAYMENTS_VIEW_FOR_MONTH
};

class Controller
{
private:
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	std::unordered_map<marvus::TableViews, std::string> views;
	MarvusDB marvusDB;
	bool importEnties(const std::string& source);
	bool importCategories(const std::string& source);
	bool importData(const std::string& source);
public:
	Controller();
	virtual ~Controller() = default;
	void configure(consolelib::argVector& config);
	bool initDB(std::string& errorMsg);
	void dropDB();
	bool insertEntity(const Establishment& e);
	bool insertCategory(const Category& c);
	bool insertPayment(const Payment& p);
	bool importFromZIP(const std::string& path, std::string& errorMessage);
	tableHeaderAndData obtainDataFromView(TableViews view);
	tableHeaderAndData obtainDataFromView(TableViews view, const insertVector& data);
};

} /* namespace marvus */

#endif /* MARVUS_CONTROLLER_H_ */
