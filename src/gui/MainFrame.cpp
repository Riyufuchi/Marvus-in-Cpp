//==============================================================================
// File       : MainFrame.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 25, 2025
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
	grids[Table::ESTABLISHMENTS] = tempGrid;

	// Tab 2
	tempGrid = wxw::FactoryWxW::newGrid(paymentsTab, wxID_ANY);
	paymentsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[keo::Table::PAYMENTS] = tempGrid;

	// Tab 3
	tempGrid = wxw::FactoryWxW::newGrid(categoriesTab, wxID_ANY);
	categoriesTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[keo::Table::CATEGORIES] = tempGrid;

	// Views

	views[TableViews::ESTABLISHMENTS_VIEW] = "SELECT * FROM ESTABLISHMENT_VIEW;";
	views[TableViews::CATEGORIES_VIEW] = "SELECT * FROM CATEGORY_VIEW;";
	views[TableViews::PAYMENTS_VIEW] = "SELECT * FROM PAYMENT_VIEW;";

	// Layout the notebook
	SetSizerAndFit(wxw::FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	loadViewToGrid(Table::ESTABLISHMENTS, TableViews::ESTABLISHMENTS_VIEW);
	loadViewToGrid(Table::CATEGORIES, TableViews::CATEGORIES_VIEW);
	loadViewToGrid(keo::Table::PAYMENTS, TableViews::PAYMENTS_VIEW);
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
	fileMenu->Append(ID_DropDB, "&Reset database");
	fileMenu->Append(ID_InserTestData, "&Insert test data");
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

	// Create a menu bar and add menu sections
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(payment, "&Payment");
	menuBar->Append(overviews, "&Overview mode");
	menuBar->Append(tools, "&Tools");
	menuBar->Append(window, "&Window");
	menuBar->Append(helpMenu, "&Help");
	
	return menuBar;
}

void MainFrame::loadViewToGrid(Table table, TableViews view)
{
	selectedViews[table] = view;
	auto viewPair = views.find(view);
	if (viewPair == views.end())
		return;
	marvus::tableHeaderAndData tableData = controller.getDB().obtainTableHeaderAndData(viewPair->second);

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
	for (const marvus::tableRowStructure& rowData : tableData.second)
	{
		for (dataX = 1, rowX = 0; dataX < ROW_SIZE; dataX++, rowX++)
		{
			grid.SetCellValue(row, rowX, rowData[dataX]);
		}
		row++;
	}
	grid.AutoSizeRows();
	grid.SetRowLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::onRefreshWindow(wxCommandEvent&)
{
	for (const auto& view : selectedViews)
	{
		loadViewToGrid(view.first, view.second);
	}
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
wxEND_EVENT_TABLE()

}
