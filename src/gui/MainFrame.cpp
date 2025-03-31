#include "MainFrame.h"

namespace keo
{

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title), db(DATABASE_FILE)
{
	if (!db.initializeDatabase())
	{
		wxMessageBox("Database initialization failed.\nExiting program!", "Database Error", wxOK | wxICON_ERROR, this);
		Close(true);
		return;
	}
	
	SetMenuBar(createMenuBar()); // Set the menu bar for this frame

	this->notebook = new wxNotebook(this, wxID_ANY);
	
	wxPanel* tab1 = new wxPanel(notebook, wxID_ANY);
	wxPanel* tab2 = new wxPanel(notebook, wxID_ANY);
	
	notebook->AddPage(tab1, "People", true); // First tab (selected by default)
	notebook->AddPage(tab2, "Farmlands", false); // Second tab

	// Create a grid and add to tab1
	this->grid = new wxGrid(tab1, wxID_ANY, wxPoint(0, 0), wxSize(500, 300));
	this->grid->CreateGrid(0, KeoDefaults::PEOPLE_TABLE_HEADER.size());
	int x = 0;
	for (const auto& heading : KeoDefaults::PEOPLE_TABLE_HEADER)
	{
		grid->SetColLabelValue(x, heading);
		x++;
	}
	
	wxBoxSizer* tab1Sizer = new wxBoxSizer(wxVERTICAL);
	tab1Sizer->Add(grid, 1, wxEXPAND | wxALL, 0);
	tab1->SetSizer(tab1Sizer);
	
	// Tab 2
	this->farmladGrid = new wxGrid(tab2, wxID_ANY, wxPoint(0, 0), wxSize(500, 300));
	this->farmladGrid->CreateGrid(0, KeoDefaults::FARMLANDS_TABLE_HEADER.size());
	x = 0;
	for (const auto& heading : KeoDefaults::FARMLANDS_TABLE_HEADER)
	{
		farmladGrid->SetColLabelValue(x, heading);
		x++;
	}
	
	wxBoxSizer* tab2Sizer = new wxBoxSizer(wxVERTICAL);
	tab2Sizer->Add(farmladGrid, 1, wxEXPAND | wxALL, 0);
	tab2->SetSizer(tab2Sizer);
	
	// Layout the notebook
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 0);
	SetSizerAndFit(mainSizer);
	// Attempt to load data
	loadDataToGrid();
	loadFarmlandsToGrid();
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

	wxMenu* addEmpMenu = new wxMenu();
	addEmpMenu->Append(ID_Add_Emp, "&Add");

	wxMenu* addJobTitleMenu = new wxMenu();
	addJobTitleMenu->Append(ID_Add_Job_Title, "&Add Job Title");

	wxMenu* refresh = new wxMenu();
	refresh->Append(ID_Refresh, "&Refresh");

	// Create a menu bar and add menu sections
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(addEmpMenu, "&People");
	menuBar->Append(addJobTitleMenu, "&Enums");
	menuBar->Append(refresh, "&Window");
	menuBar->Append(helpMenu, "&Help");
	
	return menuBar;
}

void MainFrame::loadFarmlandsToGrid()
{
	std::vector<keo::Farmland> farms;

	try {
		farms = db.getFarmlands();
	} catch (std::exception& e) {
		wxMessageBox(wxString::Format("%s", e.what()), "Error during data fetch", wxOK | wxICON_ERROR);
		return;
	}

	if (farms.empty())
	{
		wxMessageBox("No data in the farmlands table", "Farmland view result", wxOK | wxICON_INFORMATION, this);
		return;
	}

	if (farmladGrid->GetNumberRows() > 0)
		farmladGrid->DeleteRows(0, farmladGrid->GetNumberRows()); // Remove old rows
	farmladGrid->AppendRows(farms.size());

	int row = 0;
	for (const keo::Farmland& farm : farms)
	{
		farmladGrid->SetCellValue(row, 0, std::to_string(farm.size));
		farmladGrid->SetCellValue(row, 1, farm.crop_type);
		farmladGrid->SetCellValue(row, 2, farm.overseer_name);
		farmladGrid->SetCellValue(row, 3, farm.overseer_role);
		row++;
	}
	
	this->farmladGrid->AutoSizeColumns(); // Auto-size column headers
	this->farmladGrid->AutoSizeRows();
	this->farmladGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::loadDataToGrid()
{
	std::vector<keo::Employee> employees;

	try {
		employees = db.getEmployees(); // Get data from DB
	} catch (std::exception& e) {
		wxMessageBox(wxString::Format("%s", e.what()), "Error during data fetch", wxOK | wxICON_ERROR);
		return;
	}

	if (employees.empty())
	{
		wxMessageBox("No data in the employee table", "Employee view result", wxOK | wxICON_INFORMATION, this);
		return;
	}

	if (grid->GetNumberRows() > 0)
		grid->DeleteRows(0, grid->GetNumberRows()); // Remove old rows
	grid->AppendRows(employees.size());

	int row = 0;
	for (const keo::Employee& emp : employees)
	{
		grid->SetCellValue(row, 0, emp.name);
		grid->SetCellValue(row, 1, emp.middle_name);
		grid->SetCellValue(row, 2, emp.last_name);
		grid->SetCellValue(row, 3, emp.jobTitle);
		row++;
	}

	this->grid->AutoSizeColumns(); // Auto-size column headers
	this->grid->AutoSizeRows();
	this->grid->SetRowLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::onRefreshWindow(wxCommandEvent&)
{
	loadDataToGrid();
	loadFarmlandsToGrid();
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

void MainFrame::onAddEmployee(wxCommandEvent&)
{
	keo::Employee emp;
	emp.name = "Jeff";
	emp.middle_name = "John";
	emp.last_name = "Berkley";
	emp.jobTitle = "2";
	db.insertEmployee(emp);
}

void MainFrame::onAddJobTitle(wxCommandEvent&)
{

}

void MainFrame::onInsertTestData(wxCommandEvent&)
{
	KeoDefaults::KeoInserter inserter(db);
	inserter.fillEnums();
	inserter.fillTables();
}

void MainFrame::onDropDatabase(wxCommandEvent&)
{
	std::filesystem::remove(DATABASE_FILE);
	db.reconnect(DATABASE_FILE);
}

// Event table to link menu actions with functions
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_Exit, MainFrame::onExit)
	EVT_MENU(ID_About, MainFrame::onAbout)
	EVT_MENU(ID_Add_Emp, MainFrame::onAddEmployee)
	EVT_MENU(ID_Add_Job_Title, MainFrame::onAddJobTitle)
	EVT_MENU(ID_Refresh, MainFrame::onRefreshWindow)
	EVT_MENU(ID_DropDB, MainFrame::onDropDatabase)
	EVT_MENU(ID_InserTestData, MainFrame::onInsertTestData)
wxEND_EVENT_TABLE()

}
