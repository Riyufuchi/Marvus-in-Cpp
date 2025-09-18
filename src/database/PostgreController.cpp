//==============================================================================
// File       : PostgreController.cpp
// Author     : riyufuchi
// Created on : Sep 18, 2025
// Last edit  : Sep 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "PostgreController.h"

namespace riyufuchi
{

PostgreController::PostgreController(const std::string& conninfo) : result(0), sqlScriptsPath("sql")
{
	conn = PQconnectdb(conninfo.c_str());
	if (PQstatus(conn) != CONNECTION_OK)
	{
		printError();
		PQfinish(conn);
		conn = nullptr;
	}
}

PostgreController::~PostgreController()
{
}

bool PostgreController::isConnected() const
{
	return conn != nullptr;
}

bool PostgreController::executeSQL(const std::string& sql)
{
	if (!conn)
		return false;
	PGresult* res = PQexec(conn, sql.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		printError();
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

bool PostgreController::checkForSuccess(int expectedResult)
{
	if (result != expectedResult)
	{
		wxMessageBox(wxString::Format("%s",  PQerrorMessage(conn)), "PostgreDB output", wxOK | wxICON_ERROR);
		return true;
	}
	return false;
}

void PostgreController::printError()
{
	wxMessageBox(wxString::Format("%s",  PQerrorMessage(conn)), "PostgreDB output", wxOK | wxICON_ERROR);
}

bool PostgreController::initializeDatabase()
{
	if (!sqlScriptFiles.loadScripts(sqlScriptsPath))
		return false;
	return executeSQL(sqlScriptFiles.getScript(INIT_DB_SQL));
}

bool PostgreController::initializeViews()
{
	for (const auto& [scriptFile, fileContent] : sqlScriptFiles.getScriptMap())
		if (scriptFile.find("view") != std::string::npos)
			if (!executeSQL(fileContent))
				return false;
	return true;
}

tableHeaderAndData PostgreController::obtainTableHeaderAndData(const std::string& viewSQL)
{
	tableRowStructure header;
	tableStructure tableData;

	if (!conn)
		return tableHeaderAndData(header, tableData);

	PGresult* res = PQexec(conn, viewSQL.c_str());
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		printError();
		PQclear(res);
		return tableHeaderAndData(header, tableData);
	}

	int nCols = PQnfields(res);
	int nRows = PQntuples(res);

	// Print column names
	for (int i = 1; i < nCols; ++i)
	{
		header.emplace_back(PQfname(res, i));
	}

	tableRowStructure rowData;

	for (int r = 0; r < nRows; ++r)
	{
		for (int c = 0; c < nCols; ++c)
		{
			rowData.emplace_back(PQgetvalue(res, r, c));
		}
		tableData.emplace_back(rowData);
		rowData.clear();
	}
	PQclear(res);
	return tableHeaderAndData(header, tableData);
}

} /* namespace sdl */
