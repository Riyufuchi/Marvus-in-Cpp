//==============================================================================
// File       : Controller.cpp
// Author     : riyufuchi
// Created on : Nov 26, 2025
// Last edit  : Nov 29, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "Controller.h"

namespace marvus
{

Controller::Controller() : marvusDB(DATABASE_FILE)
{
	this->argumentMethods["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; marvusDB.setPathToSQL_Scripts(vector[0]); };

	views[TableViews::ESTABLISHMENTS_VIEW] = InlineSQL::ESTABLISHMENTS_VIEW;
	views[TableViews::CATEGORIES_VIEW] = InlineSQL::CATEGORIES_VIEW;
	views[TableViews::PAYMENTS_VIEW] = InlineSQL::PAYMENTS_VIEW_CURR_MONTH;
}

void Controller::configure(ConsoleLib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const ConsoleLib::argVectorItem& argument : config)
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
	if (!marvusDB.initializeViews())
	{
		errorMsg = "Views initialization failed.\nExiting program!";
		return true;
	}
	return false;
}

void Controller::dropDB()
{
	std::filesystem::remove(DATABASE_FILE);
	marvusDB.reconnect(DATABASE_FILE);
	marvusDB.initializeViews();
}

tableHeaderAndData Controller::obtainDataFromView(Table table, TableViews view)
{
	selectedViews[table] = view;
	auto viewPair = views.find(view);
	if (viewPair == views.end())
		return {};
	return marvusDB.obtainTableHeaderAndData(viewPair->second);
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

bool Controller::importEnties(const std::string& source)
{
	marvus::Establishment est;

	std::istringstream ss(source);

	while (std::getline(ss, est.name))
	{
		if (!insertEntity(est))  // convert each line to UTF-8
			return false;
	}
	return true;
}

bool Controller::importCategories(const std::string& source)
{
	marvus::Category cat;

	std::istringstream ss(source);

	while (std::getline(ss, cat.name))
	{
		if (!insertCategory(cat))  // convert each line to UTF-8
			return false;
	}
	return true;
}

bool Controller::importData(const std::string& source)
{
	const tableHeaderAndData ents = obtainDataFromView(Table::ESTABLISHMENTS, TableViews::ESTABLISHMENTS_VIEW);
	const tableHeaderAndData cats = obtainDataFromView(Table::CATEGORIES, TableViews::CATEGORIES_VIEW);

	std::unordered_map<std::string, int> entMap;
	std::unordered_map<std::string, int> catMap;

	for (const marvus::tableRow& row : ents.second)
	{
		entMap[row[1]] = std::stoi(row[0]);
	}

	for (const marvus::tableRow& row : cats.second)
	{
		catMap[row[1]] = std::stoi(row[0]);
	}

	std::vector<std::string> parsedCSV;
	auto findData = entMap.find("0");
	std::vector<std::string> parsedDate;

	Payment payment;

	std::istringstream ss(source);
	std::string line;

	while (std::getline(ss, line))
	{
		parsedCSV = ConsoleLib::FileUtils::splitCSV(line, ';', 6);
		findData = entMap.find(parsedCSV[0]);
		if (findData != entMap.end())
			payment.ent_key = findData->second;
		else
			continue;
		findData = catMap.find(parsedCSV[1]);
		if (findData != catMap.end())
			payment.category_key = findData->second;
		else
			continue;
		payment.value = parsedCSV[2];
		// Currency isn't implemented yet
		parsedDate = ConsoleLib::FileUtils::splitCSV(parsedCSV[4], '.', 3);
		payment.date = parsedDate[2] + "-" + parsedDate[1] + "-" + parsedDate[0];
		payment.note = parsedCSV[5];
		if (!insertPayment(payment))  // convert each line to UTF-8
			return false;
	}

	return true;
}


bool Controller::importFromZIP(const std::string& path, std::string& errorMessage)
{
	mz_zip_archive zip;
	mz_zip_zero_struct(&zip);

	if (!mz_zip_reader_init_file(&zip, path.c_str(), 0))
	{
		errorMessage = "Failed to open ZIP\n";
		return false;
	}

	int fileCount = mz_zip_reader_get_num_files(&zip);

	if (fileCount != 3)
	{
		errorMessage = "Import need 3 filed (entities.csv, categories.csv, data.csv)\n";
		return false;
	}

	size_t size;

	std::string categories;
	std::string entities;
	std::string dataFile;

	for (int i = 0; i < fileCount; i++)
	{
		mz_zip_archive_file_stat stat;
		mz_zip_reader_file_stat(&zip, i, &stat);

		size = 0;
		void* data = mz_zip_reader_extract_file_to_heap(&zip, stat.m_filename, &size, 0);

		if (std::string(stat.m_filename) == "entities.csv")
			entities.assign((char*)data, size);
		else if (std::string(stat.m_filename) == "categories.csv")
			categories.assign((char*)data, size);
		else if (std::string(stat.m_filename) == "data.csv")
			dataFile.assign((char*)data, size);
		else
		{
			mz_free(data);
			errorMessage = "Unknown file [" + std::string(stat.m_filename) + "] expected: entities.csv, categories.csv, data.csv\n";
			return false;
		}

		mz_free(data);
	}

	mz_zip_reader_end(&zip);

	if (importEnties(entities) && importCategories(categories))
		return importData(dataFile);
	return false;
}

} /* namespace marvus */
