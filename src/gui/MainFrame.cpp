//==============================================================================
// File       : MainFrame.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MainFrame.h"

namespace keo
{

MainFrame::MainFrame(const wxString& title, ConsoleLib::argVector& config) : wxFrame(NULL, wxID_ANY, title)
{
	wxIcon icon(icon_xpm);
	SetIcon(icon);

	controller.configure(config);

	std::string message;

	if (controller.initDB(message))
	{
		wxMessageBox(message, "Database Error", wxOK | wxICON_ERROR, this);
		Close(true);
		return;
	}

	SetMenuBar(createMenuBar()); // Set the menu bar for this frame

	this->notebook = new wxNotebook(this, wxID_ANY);

	wxPanel* establishmentsTab = new wxPanel(notebook);
	wxPanel* paymentsTab = new wxPanel(notebook);
	wxPanel* categoriesTab = new wxPanel(notebook);
	
	notebook->AddPage(establishmentsTab, "Establishments");
	notebook->AddPage(paymentsTab, "Payments", true);
	notebook->AddPage(categoriesTab, "Categories");

	// Create a grid and add to tab1
	wxGrid* tempGrid = wxw::FactoryWxW::newGrid(establishmentsTab, wxID_ANY);
	establishmentsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::ESTABLISHMENTS] = tempGrid;

	// Tab 2
	tempGrid = wxw::FactoryWxW::newGrid(paymentsTab, wxID_ANY);
	paymentsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::PAYMENTS] = tempGrid;

	// Tab 3
	tempGrid = wxw::FactoryWxW::newGrid(categoriesTab, wxID_ANY);
	categoriesTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::CATEGORIES] = tempGrid;

	// Layout the notebook
	SetSizerAndFit(wxw::FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	loadViewToGrid(marvus::Table::ESTABLISHMENTS, marvus::TableViews::ESTABLISHMENTS_VIEW);
	loadViewToGrid(marvus::Table::CATEGORIES, marvus::TableViews::CATEGORIES_VIEW);
	loadViewToGrid(marvus::Table::PAYMENTS, marvus::TableViews::PAYMENTS_VIEW);
	SetSize(800, 600);
}

MainFrame::~MainFrame()
{
	Unbind(wxEVT_MENU, &MainFrame::onExit, this, ID_Exit);
	Unbind(wxEVT_MENU, &MainFrame::onAbout, this, ID_About);
}

wxMenuBar* MainFrame::createMenuBar()
{
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(ID_NotImplementedYet, "&New");
	fileMenu->Append(ID_NotImplementedYet, "&Open");
	fileMenu->Append(ID_Import, "&Import");
	fileMenu->Append(ID_NotImplementedYet, "&Export");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Exit, "&Exit");

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(ID_About, "&About");

	wxMenu* window = new wxMenu();
	window->Append(ID_Refresh, "&Refresh");

	wxMenu* payment = new wxMenu();
	payment->Append(ID_INSERT_PAYMENT, "&Add Payment");

	wxMenu* overviews = new wxMenu();

	wxMenu* tools = new wxMenu();

	wxMenu* debug = new wxMenu();
	debug->Append(ID_DropDB, "&Reset database");
	debug->Append(ID_InserTestData, "&Insert test data");

	// Create a menu bar and add menu sections
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(payment, "&Payment");
	menuBar->Append(overviews, "&Overview mode");
	menuBar->Append(tools, "&Tools");
	menuBar->Append(window, "&Window");
	menuBar->Append(helpMenu, "&Help");
	menuBar->Append(debug, "&Debug");
	
	return menuBar;
}

void MainFrame::loadViewToGrid(marvus::Table table, marvus::TableViews view)
{
	marvus::tableHeaderAndData tableData = controller.obtainDataFromView(table, view);

	if (!grids.contains(table))
		return;

	wxGrid& grid = *grids.find(table)->second;

	if (grid.GetNumberCols() > 0)
		grid.DeleteCols(0, grid.GetNumberCols()); // Remove old cols
	grid.AppendCols(tableData.first.size());

	int rowX = 0;
	for (const std::string& heading : tableData.first)
	{
		grid.SetColLabelValue(rowX, heading);
		rowX++;
	}

	grid.SetRowLabelSize(wxGRID_AUTOSIZE);
	grid.AutoSizeColumns(); // Auto-size column headers

	if (tableData.second.empty())
	{
		wxMessageBox("No data in the table", "Table view result", wxOK | wxICON_INFORMATION, this);
		return;
	}

	if (grid.GetNumberRows() > 0)
		grid.DeleteRows(0, grid.GetNumberRows()); // Remove old rows
	grid.AppendRows(tableData.second.size());

	int row = 0;
	rowX = 0;
	int dataX = 1;
	const int ROW_SIZE = tableData.second[0].size();
	for (const marvus::tableRow& rowData : tableData.second)
	{
		for (dataX = 1, rowX = 0; dataX < ROW_SIZE; dataX++, rowX++)
		{
			grid.SetCellValue(row, rowX, wxString::FromUTF8(rowData[dataX]));
		}
		row++;
	}
	grid.AutoSizeColumns(); // Auto-size column headers
	grid.AutoSizeRows();
}

void MainFrame::onRefreshWindow(wxCommandEvent&)
{
	/*for (const auto& view : selectedViews)
	{
		loadViewToGrid(view.first, view.second);
	}*/
}

void MainFrame::onNotImplemented(wxCommandEvent&)
{
	wxMessageBox("This function have not been implemented yet!.", "Implmentatation info", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::onExit(wxCommandEvent&)
{
	Close(true); // Close the window
}

void MainFrame::onAbout(wxCommandEvent&)
{
	wxMessageBox("This is a wxWidgets application.", "About", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::onInsertPayment(wxCommandEvent&)
{
	marvus::PaymentDialog::InputData data;

	data.establishments = {{"1", "McDonnald's"}};
	data.categories = {{"1", "Food"}};

	marvus::PaymentDialog dialog(this, data);
	if (dialog.ShowModal() == wxID_OK && dialog.isConfirmed())
	{

	}
}

void MainFrame::onInsertTestData(wxCommandEvent& event)
{
	ConsoleLib::ScriptMap map;
	map.loadScripts("../data/");

	onRefreshWindow(event);
}

void MainFrame::onDropDatabase(wxCommandEvent&)
{
	controller.dropDB();
}

void MainFrame::importCategories(wxTextFile& sourceFile)
{
	marvus::Category cat;

	for (wxString str = sourceFile.GetFirstLine(); !sourceFile.Eof(); str = sourceFile.GetNextLine() )
	{
		cat.name = std::string(str.ToUTF8().data());
		if (!controller.insertCategory(cat))  // convert each line to UTF-8
			break;
	}
	loadViewToGrid(marvus::Table::CATEGORIES, marvus::TableViews::CATEGORIES_VIEW);
}

void MainFrame::importEnties(wxTextFile& sourceFile)
{
	marvus::Establishment est;

	for (wxString str = sourceFile.GetFirstLine(); !sourceFile.Eof(); str = sourceFile.GetNextLine() )
	{
		est.name = std::string(str.ToUTF8().data());
		if (!controller.insertEntity(est))  // convert each line to UTF-8
			break;
	}
	loadViewToGrid(marvus::Table::ESTABLISHMENTS, marvus::TableViews::ESTABLISHMENTS_VIEW);
}

static std::vector<std::string> splitCSVFixed(const std::string& line, char delimeter, size_t expectedCount)
{
	std::vector<std::string> result;
	result.reserve(expectedCount);

	std::string current;
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (line[i] == delimeter)
		{
			result.push_back(current);
			current.clear();
		}
		else
		{
			current += line[i];
		}
	}

	// Add the last field
	result.push_back(current);

	// Pad with empty strings if fewer than expected
	while (result.size() < expectedCount)
		result.push_back("");

	return result;
}

void MainFrame::importPayments(wxTextFile& sourceFile)
{
	const marvus::tableHeaderAndData ents = controller.obtainDataFromView(marvus::Table::ESTABLISHMENTS, marvus::TableViews::ESTABLISHMENTS_VIEW);
	const marvus::tableHeaderAndData cats = controller.obtainDataFromView(marvus::Table::CATEGORIES, marvus::TableViews::CATEGORIES_VIEW);

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

	marvus::Payment payment;

	std::vector<std::string> parsedCSV;
	auto findData = entMap.find("0");
	std::vector<std::string> parsedDate;

	/*
	 * CSV is flat file without ID's so little mapping is needed
	 */
	for (wxString str = sourceFile.GetFirstLine(); !sourceFile.Eof(); str = sourceFile.GetNextLine() )
	{
		parsedCSV = splitCSVFixed(std::string(str.ToUTF8().data()), ';', 6);
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
		parsedDate = splitCSVFixed(parsedCSV[4], '.', 3);
		payment.date = parsedDate[2] + "-" + parsedDate[1] + "-" + parsedDate[0];
		payment.note = parsedCSV[5];
		if (!controller.insertPayment(payment))  // convert each line to UTF-8
			break;
	}
	loadViewToGrid(marvus::Table::PAYMENTS, marvus::TableViews::PAYMENTS_VIEW);

}

void MainFrame::onImport(wxCommandEvent&)
{
	static int id = 0;
	wxFileDialog openFileDialog(this, "Select a text file",
		"", "", "Text files |*.txt|All files |*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // user pressed "Cancel"

	wxString path = openFileDialog.GetPath();

	// Read the file into a vector<string>
	wxTextFile file(path);
	if (!file.Open())
	{
		wxMessageBox("Cannot open the selected file.", "Error", wxICON_ERROR);
		return;
	}

	switch (id)
	{
		case 0: importEnties(file); break;
		case 1: importCategories(file); break;
		case 2: importPayments(file); break;
	}
	id++;
}

// Event table to link menu actions with functions
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_Exit, MainFrame::onExit)
	EVT_MENU(ID_About, MainFrame::onAbout)
	EVT_MENU(ID_INSERT_PAYMENT, MainFrame::onInsertPayment)
	EVT_MENU(ID_Refresh, MainFrame::onRefreshWindow)
	EVT_MENU(ID_DropDB, MainFrame::onDropDatabase)
	EVT_MENU(ID_InserTestData, MainFrame::onInsertTestData)
	EVT_MENU(ID_NotImplementedYet, MainFrame::onNotImplemented)
	EVT_MENU(ID_Import, MainFrame::onImport)
wxEND_EVENT_TABLE()

}
