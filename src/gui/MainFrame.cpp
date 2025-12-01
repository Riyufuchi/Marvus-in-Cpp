//==============================================================================
// File       : MainFrame.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 01, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MainFrame.h"

namespace wxw
{

MainFrame::MainFrame(const wxString& title, consolelib::argVector& config) : wxFrame(NULL, wxID_ANY, title)
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
	createToolBar();

	this->notebook = new wxNotebook(this, wxID_ANY);

	wxPanel* establishmentsTab = new wxPanel(notebook);
	wxPanel* paymentsTab = new wxPanel(notebook);
	wxPanel* categoriesTab = new wxPanel(notebook);
	
	notebook->AddPage(establishmentsTab, "Establishments");
	notebook->AddPage(categoriesTab, "Categories");
	notebook->AddPage(paymentsTab, "Payments", true);

	// Create a grid and add to tab1
	wxGrid* tempGrid = FactoryWxW::newGrid(establishmentsTab, wxID_ANY);
	establishmentsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::ESTABLISHMENTS] = tempGrid;

	// Tab 2
	tempGrid = FactoryWxW::newGrid(paymentsTab, wxID_ANY);
	paymentsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::PAYMENTS] = tempGrid;

	// Tab 3
	tempGrid = FactoryWxW::newGrid(categoriesTab, wxID_ANY);
	categoriesTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::CATEGORIES] = tempGrid;

	for (const auto& grid : grids)
	{
		ToolsWxW::updateFontSizeInGrid(grid.second, 10);
	}

	// Layout the notebook
	SetSizerAndFit(FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	loadViewToGrid(marvus::Table::ESTABLISHMENTS, marvus::TableViews::ESTABLISHMENTS_VIEW);
	loadViewToGrid(marvus::Table::CATEGORIES, marvus::TableViews::CATEGORIES_VIEW);
	monthChoice->SetSelection(0);
	wxCommandEvent e;
	onDateFilterChanged(e);
	SetSize(800, 600);
}

MainFrame::~MainFrame()
{
	Unbind(wxEVT_MENU, &MainFrame::onExit, this, ID_Exit);
	Unbind(wxEVT_MENU, &MainFrame::onAbout, this, ID_About);
}

void MainFrame::createToolBar()
{
	wxToolBar* tb = CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);

	wxArrayString months;
	months.Add("January");
	months.Add("February");
	months.Add("March");
	months.Add("April");
	months.Add("May");
	months.Add("June");
	months.Add("July");
	months.Add("August");
	months.Add("September");
	months.Add("October");
	months.Add("November");
	months.Add("December");

	monthFilterCheck = new wxCheckBox(tb, wxID_ANY, "Month filter");
	monthFilterCheck->SetValue(true);
	tb->AddControl(monthFilterCheck);

	monthChoice = new wxChoice(tb, wxID_ANY, wxDefaultPosition, wxDefaultSize, months);
	tb->AddControl(monthChoice);
	//
	tb->Realize();
	// Bind events
	Bind(wxEVT_CHOICE, &MainFrame::onDateFilterChanged, this, monthChoice->GetId());
	Bind(wxEVT_CHECKBOX, &MainFrame::onDateFilterChanged, this, monthChoice->GetId());
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

void MainFrame::fillGrid(marvus::Table table, const marvus::tableHeaderAndData& tableData)
{
	if (tableData.second.empty())
	{
		wxMessageBox("No data received from the database.", "Table view result", wxOK | wxICON_INFORMATION, this);
		return;
	}

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

void MainFrame::loadViewToGrid(marvus::Table table, marvus::TableViews view)
{
	fillGrid(table, controller.obtainDataFromView(view));
}

// Events

void MainFrame::onDateFilterChanged(wxCommandEvent&)
{
	//int month = m_monthChoice->GetSelection() + 1;
	fillGrid(marvus::Table::PAYMENTS,
		controller.obtainDataFromView(marvus::TableViews::PAYMENTS_VIEW_FOR_MONTH, { std::format("{:02}", monthChoice->GetSelection() + 1) }));

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
	consolelib::ScriptMap map;
	map.loadScripts("../data/");

	onRefreshWindow(event);
}

void MainFrame::onDropDatabase(wxCommandEvent&)
{
	controller.dropDB();
}

void MainFrame::onImport(wxCommandEvent&)
{
	wxFileDialog openFileDialog(this, "Select a zip file",
		"", "", "Marvus zip |*.zip", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // user pressed "Cancel"

	wxString path = openFileDialog.GetPath();

	std::string msg;

	if (controller.importFromZIP(std::string(path), msg))
	{
		loadViewToGrid(marvus::Table::ESTABLISHMENTS, marvus::TableViews::ESTABLISHMENTS_VIEW);
		loadViewToGrid(marvus::Table::CATEGORIES, marvus::TableViews::CATEGORIES_VIEW);
		loadViewToGrid(marvus::Table::PAYMENTS, marvus::TableViews::PAYMENTS_VIEW);
	}
	else
		wxMessageBox(msg, "Import error", wxICON_ERROR);
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
