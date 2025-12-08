//==============================================================================
// File       : MainFrame.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 07, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MainFrame.h"

namespace wxw
{

MainFrame::MainFrame(const wxString&, consolelib::argVector& config) : wxFrame(NULL, wxID_ANY, _MARVUS_VERSION), controller([this](const std::string& title, const std::string& message) { displayError(title, message); })
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
	wxPanel* macrosTab = new wxPanel(notebook);
	
	notebook->AddPage(establishmentsTab, "Establishments");
	notebook->AddPage(categoriesTab, "Categories");
	notebook->AddPage(paymentsTab, "Payments", true);
	notebook->AddPage(macrosTab, "Payment macros");

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

	// Tab 3
	tempGrid = FactoryWxW::newGrid(macrosTab, wxID_ANY);
	macrosTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[marvus::Table::PAYMENT_MACROS] = tempGrid;

	for (const auto& grid : grids)
	{
		ToolsWxW::updateFontSizeInGrid(grid.second, 10);
	}
	// Layout the notebook
	SetSizerAndFit(FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	selectedViewForTable[marvus::Table::ESTABLISHMENTS] = {marvus::TableView::ESTABLISHMENTS_VIEW, {}};
	selectedViewForTable[marvus::Table::CATEGORIES] = {marvus::TableView::CATEGORIES_VIEW, {}};
	selectedViewForTable[marvus::Table::PAYMENT_MACROS] = {marvus::TableView::PAYMENT_MACRO_VIEW, {}};
	monthChoice->SetSelection(0);
	wxCommandEvent e;
	onDateFilterChanged(e);
	onRefreshWindow(e);
	SetSize(800, 600);
}

void MainFrame::displayError(const std::string& title, const std::string& message)
{
	wxMessageBox(message, title, wxICON_ERROR);
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
	fileMenu->Append(ID_NewDB, "&New");
	fileMenu->Append(ID_OpenDB, "&Open");
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
	overviews->Append(ID_TableListView, "&Table list");

	wxMenu* network = new wxMenu();
	network->Append(ID_SendFile, "&Send data");
	network->Append(ID_RecieveFile, "&Recieve data");

	wxMenu* tools = new wxMenu();
	tools->Append(ID_NotImplementedYet, "&Entity manager");

	wxMenu* debug = new wxMenu();
	debug->Append(ID_DropDB, "&Reset database");
	debug->Append(ID_InserTestData, "&Insert test data");

	// Create a menu bar and add menu sections
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(payment, "&Payment");
	menuBar->Append(overviews, "&Overview mode");
	menuBar->Append(network, "&Network");
	menuBar->Append(tools, "&Tools");
	menuBar->Append(window, "&Window");
	menuBar->Append(helpMenu, "&Help");
	menuBar->Append(debug, "&Debug");
	
	return menuBar;
}

void MainFrame::fillGrid(marvus::Table table, const marvus::tableHeaderAndData& tableData)
{
	if (!grids.contains(table))
		return;

	wxGrid& grid = *grids.find(table)->second;

	if (tableData.second.empty())
	{
		wxMessageBox("No data received from the database.", "Table view result", wxOK | wxICON_INFORMATION, this);
		if (grid.GetNumberRows() > 0)
			grid.DeleteRows(0, grid.GetNumberRows()); // Remove old rows
		return;
	}

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
	grid.AutoSizeColumns();
	grid.AutoSizeRows();
}

void MainFrame::loadViewToGrid(marvus::Table table, marvus::TableView view, marvus::insertVector data)
{
	selectedViewForTable[table] = {view, data};
	fillGrid(table, controller.obtainDataFromView(view, data));
}

// Events

void MainFrame::onViewChanged(wxCommandEvent& event)
{
	loadViewToGrid(marvus::Table::PAYMENTS, marvus::TableView::PAYMENTS_VIEW);
}

void MainFrame::onDateFilterChanged(wxCommandEvent&)
{
	loadViewToGrid(marvus::Table::PAYMENTS, marvus::TableView::PAYMENTS_VIEW_FOR_MONTH, { std::format("{:02}", monthChoice->GetSelection() + 1) });
}

void MainFrame::onRefreshWindow(wxCommandEvent&)
{
	if (selectedViewForTable.empty())
		return;
	for (const auto& view : selectedViewForTable)
	{
		loadViewToGrid(view.first, view.second.first, view.second.second);
	}
}

void MainFrame::onNotImplemented(wxCommandEvent&)
{
	wxMessageBox("This function have not been implemented yet!.", "Implementation info", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::onExit(wxCommandEvent&)
{
	Close(true); // Close the window
}

void MainFrame::onAbout(wxCommandEvent&)
{
	wxMessageBox(marvus::Controller::aboutApplication(), "About", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::onInsertPayment(wxCommandEvent& event)
{
	marvus::PaymentDialog::InputData data;

	data.establishments = controller.obtainDataFromView(marvus::TableView::ESTABLISHMENTS_VIEW).second;
	if (data.establishments.empty())
	{
		displayError("ESTABLISHMENTS_VIEW", "No data recieved from the table.");
		return;
	}
	data.categories = controller.obtainDataFromView(marvus::TableView::CATEGORIES_VIEW).second;
	if (data.categories.empty())
	{
		displayError("CATEGORIES_VIEW", "No data recieved from the table.");
		return;
	}

	marvus::PaymentDialog dialog(this, data);
	if (dialog.ShowModal() == wxID_OK && dialog.isConfirmed())
	{
		if (controller.insertPayment(dialog.getUserInput()))
			onDateFilterChanged(event);
	}
}

void MainFrame::onInsertTestData(wxCommandEvent& event)
{
	marvus::Establishment e { .name = "Gusto's" };
	marvus::Establishment e1 { .name = "Luigi's" };
	marvus::Establishment e2 { .name = "Red Rocket" };

	marvus::Category c { .name = "Food" };
	marvus::Category c1 { .name = "Fuel" };
	marvus::Category c2 { .name = "Tires" };

	controller.insertEntity(e);
	controller.insertEntity(e1);
	controller.insertEntity(e2);
	controller.insertCategory(c);
	controller.insertCategory(c1);
	controller.insertCategory(c2);

	int valueInt = 100;
	marvus::Payment p {0, 1, 1, "100", "2025-10-10", ""};
	size_t pos = 5;

	for (int i = 1; i < 13; ++i)
	{
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << i; // format as 2 digits

		p.value = std::to_string(valueInt + i);
		p.date.replace(pos, 2, oss.str());

		controller.insertPayment(p);
	}
	onDateFilterChanged(event); // Updates grid by current selection
	onRefreshWindow(event);
}

void MainFrame::onSendFile(wxCommandEvent& event)
{
	marvus::FileTransferDialog networkDialog(this, "Send data");
	wxString ipAddress = "192.168.0.100";
	wxTextEntryDialog taxtDialog(this, "IPv4 address:", "Network setup", ipAddress);
	if (taxtDialog.ShowModal() == wxID_OK)
	{
		networkDialog.startClient(taxtDialog.GetValue(), 6969, "data.zip");
	}
}

void MainFrame::onRecieveFile(wxCommandEvent& event)
{
	marvus::FileTransferDialog dialog(this, "Recieve data");
	dialog.startServer(6969, "recievedData.zip");
}

void MainFrame::onLoadDB(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, "Select a database file", "", "", "Database |*.db", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	controller.connectToDB(openFileDialog.GetPath().ToStdString());
	onRefreshWindow(event);
}

void MainFrame::onNewDB(wxCommandEvent& event)
{
	wxString defaultValue = "database";
	wxTextEntryDialog dialog(this, "Database name:", "New database", defaultValue);
	if (dialog.ShowModal() == wxID_OK)
	{
		controller.connectToDB(dialog.GetValue().ToStdString());
		std::string msg;
		if (controller.initDB(msg))
		{
			displayError("New DB creation", msg);
			return;
		}
		onRefreshWindow(event);
	}
}

void MainFrame::onDropDatabase(wxCommandEvent& event)
{
	controller.dropDB();
	onRefreshWindow(event);
}

void MainFrame::onImport(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, "Select a zip file",
		"", "", "Marvus zip |*.zip", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxString path = openFileDialog.GetPath();

	std::string msg;

	if (controller.importFromZIP(std::string(path), msg))
	{
		onRefreshWindow(event);
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
	EVT_MENU(ID_NewDB, MainFrame::onNewDB)
	EVT_MENU(ID_OpenDB, MainFrame::onLoadDB)
	EVT_MENU(ID_TableListView, MainFrame::onViewChanged)
	EVT_MENU(ID_SendFile, MainFrame::onSendFile)
	EVT_MENU(ID_RecieveFile, MainFrame::onRecieveFile)
wxEND_EVENT_TABLE()

}
