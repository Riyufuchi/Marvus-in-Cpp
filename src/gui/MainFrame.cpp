#include "MainFrame.h"

namespace keo
{

MainFrame::MainFrame(const wxString& title, ConsoleLib::argVector& config) : wxFrame(NULL, wxID_ANY, title), db(DATABASE_FILE)
{
	wxIcon icon(icon_xpm);
	SetIcon(icon);
	//(void*)icon_gui_db2_xpm;

	this->argumentMethods["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; db.setSQL_Scripts(vector[0]); };

	configure(config);

	if (!db.initializeDatabase())
	{
		wxMessageBox("Database initialization failed.\nExiting program!", "Database Error", wxOK | wxICON_ERROR, this);
		Close(true);
		return;
	}
	
	if (!db.initializeViews())
	{
		wxMessageBox("Views initialization failed.\nExiting program!", "Database Error", wxOK | wxICON_ERROR, this);
		Close(true);
		return;
	}

	SetMenuBar(createMenuBar()); // Set the menu bar for this frame

	this->notebook = new wxNotebook(this, wxID_ANY);
	
	wxPanel* mainTab = new wxPanel(notebook);
	wxPanel* farmsTab = new wxPanel(notebook);
	wxPanel* minesTab = new wxPanel(notebook);
	
	notebook->AddPage(mainTab, "People", true); // First tab (selected by default)
	notebook->AddPage(farmsTab, "Farmlands"); // Second tab
	notebook->AddPage(minesTab, "Mines");

	// Create a grid and add to tab1
	wxGrid* tempGrid = wxw::FactoryWxW::newGrid(mainTab, wxID_ANY);
	mainTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[keo::Table::PEOPLE] = tempGrid;

	// Tab 2
	tempGrid = wxw::FactoryWxW::newGrid(farmsTab, wxID_ANY);
	farmsTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[keo::Table::FARMLANDS] = tempGrid;

	// Tab 3
	tempGrid = wxw::FactoryWxW::newGrid(minesTab, wxID_ANY);
	minesTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[keo::Table::MINES] = tempGrid;

	// Layout the notebook
	SetSizerAndFit(wxw::FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	loadViewToGrid(keo::Table::PEOPLE);
	loadViewToGrid(keo::Table::FARMLANDS);
	loadViewToGrid(keo::Table::MINES);
	SetSize(800, 600);
}

MainFrame::~MainFrame()
{
	Unbind(wxEVT_MENU, &MainFrame::onExit, this, ID_Exit);
	Unbind(wxEVT_MENU, &MainFrame::onAbout, this, ID_About);
}

void MainFrame::configure(ConsoleLib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const ConsoleLib::argVectorItem& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
		//else
			//messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Invalid argument [" + argument.first + "]\n");
	}
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

void MainFrame::loadDataToGrid(keo::Table table)
{
	keo::tableStructure tableData = db.obtainTableData(table);

	if (tableData.empty() || !grids.contains(table))
	{
		wxMessageBox("No data in the table", "Table view result", wxOK | wxICON_INFORMATION, this);
		return;
	}

	wxGrid& grid = *grids.find(table)->second;

	if (grid.GetNumberRows() > 0)
		grid.DeleteRows(0, grid.GetNumberRows()); // Remove old rows
	grid.AppendRows(tableData.size());

	int row = 0;
	int rowX = 0;
	int dataX = 1;
	const int ROW_SIZE = tableData[0].size();
	for (const keo::tableRowStructure& rowData : tableData)
	{
		for (dataX = 1, rowX = 0; dataX < ROW_SIZE; dataX++, rowX++)
		{
			grid.SetCellValue(row, rowX, rowData[dataX]);
		}
		row++;
	}
	grid.AutoSizeColumns(); // Auto-size column headers
	grid.AutoSizeRows();
	grid.SetRowLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::loadViewToGrid(keo::Table table)
{
	keo::tableHeaderAndData tableData = db.obtainTableHeaderAndData(table);

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
	for (const keo::tableRowStructure& rowData : tableData.second)
	{
		for (dataX = 1, rowX = 0; dataX < ROW_SIZE; dataX++, rowX++)
		{
			grid.SetCellValue(row, rowX, rowData[dataX]);
		}
		row++;
	}
	grid.AutoSizeColumns(); // Auto-size column headers
	grid.AutoSizeRows();
	grid.SetRowLabelSize(wxGRID_AUTOSIZE);
}

void MainFrame::onRefreshWindow(wxCommandEvent&)
{
	loadViewToGrid(keo::Table::PEOPLE);
	loadViewToGrid(keo::Table::FARMLANDS);
	loadViewToGrid(keo::Table::MINES);
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

void MainFrame::onInsertTestData(wxCommandEvent& event)
{
	KeoDefaults::KeoInserter inserter(db);
	inserter.fillEnums();
	inserter.fillTables();
	onRefreshWindow(event);
}

void MainFrame::onDropDatabase(wxCommandEvent&)
{
	std::filesystem::remove(DATABASE_FILE);
	db.reconnect(DATABASE_FILE);
	db.initializeViews();
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
