//==============================================================================
// File       : ToolsIO.cpp
// Author     : riyufuchi
// Created on : Dec 7, 2025
// Last edit  : Dec 7, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "ToolsIO.h"
#include "../base/Controller.h"

namespace marvus
{

ToolsIO::ToolsIO(Controller& controller) : controller(controller)
{
}

ToolsIO::~ToolsIO()
{
}

bool ToolsIO::importEnties(const std::string& source)
{
	marvus::Establishment est;

	std::istringstream ss(source);

	while (std::getline(ss, est.name))
	{
		if (!controller.insertEntity(est))  // convert each line to UTF-8
			return false;
	}
	return true;
}

bool ToolsIO::importCategories(const std::string& source)
{
	Category cat;

	std::istringstream ss(source);

	while (std::getline(ss, cat.name))
	{
		if (!controller.insertCategory(cat))
			return false;
	}
	return true;
}

bool ToolsIO::importMacros(const std::string& source)
{
	std::vector<std::string> parsedCSV;
	auto findData = entMap.find("0");
	std::vector<std::string> parsedDate;

	PaymentMacro payment;

	std::istringstream ss(source);
	std::string line;

	while (std::getline(ss, line))
	{
		parsedCSV = consolelib::FileUtils::splitCSV(line, ';', 5);
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
		payment.note = parsedCSV[4];
		if (!controller.insertPaymentMacro(payment))
			return false;
	}
	return true;
}

bool ToolsIO::importData(const std::string& source)
{
	ents = controller.obtainDataFromView(TableView::ESTABLISHMENTS_VIEW);
	cats = controller.obtainDataFromView(TableView::CATEGORIES_VIEW);

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
		parsedCSV = consolelib::FileUtils::splitCSV(line, ';', 6);
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
		parsedDate = consolelib::FileUtils::splitCSV(parsedCSV[4], '.', 3);
		payment.date = parsedDate[2] + "-" + parsedDate[1] + "-" + parsedDate[0];
		payment.note = parsedCSV[5];
		if (!controller.insertPayment(payment))  // convert each line to UTF-8
			return false;
	}
	return true;
}

bool ToolsIO::importDataFromZip(const std::string& path, std::string& errorMessage)
{
	mz_zip_archive zip;
	mz_zip_zero_struct(&zip);

	if (!mz_zip_reader_init_file(&zip, path.c_str(), 0))
	{
		errorMessage = "Failed to open ZIP\n";
		return false;
	}

	int fileCount = mz_zip_reader_get_num_files(&zip);

	if (fileCount != 4)
	{
		errorMessage = "Import need 4 filed (entities.csv, categories.csv, data.csv, macros.csv)\n";
		return false;
	}

	size_t size;

	std::string categories;
	std::string entities;
	std::string dataFile;
	std::string macros;

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
		else if (std::string(stat.m_filename) == "macros.csv")
			macros.assign((char*)data, size);
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
		if (importData(dataFile))
			return importMacros(macros);
	return false;
}

} /* namespace sdl */
