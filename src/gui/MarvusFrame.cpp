#include "MarvusFrame.h"

namespace riyufuchi
{

MarvusFrame::MarvusFrame(const wxString& title, ConsoleLib::argVector& config) : wxFrame(NULL, wxID_ANY, title), db(DATABASE_CONN)
{
	/*wxIcon icon(icon_xpm);
	SetIcon(icon);*/

	//this->argumentMethods["--sqlPath"] = [&] (const std::vector<std::string>& vector) { if (vector.empty()) return; db.setSQL_Scripts(vector[0]); };

	configure(config);

	if (!db.initializeDatabase())
	{
		wxMessageBox("Database initialization failed probably during script loading.\nExiting program!", "Database Error", wxOK | wxICON_ERROR, this);
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

	// keo
	wxPanel* mainTab = new wxPanel(notebook);
	

	notebook->AddPage(mainTab, "Default tab", true); // First tab (selected by default)

	// Create a grid and add to tab1
	wxGrid* tempGrid = wxw::FactoryWxW::newGrid(mainTab, wxID_ANY);
	mainTab->SetSizer(wxw::FactoryWxW::newMaxSizer(tempGrid));
	grids[Table::MAIN] = tempGrid;

	// Layout the notebook
	SetSizerAndFit(wxw::FactoryWxW::newMaxSizer(notebook));
	// Attempt to load data
	loadViewToGrid(Table::MAIN);
	SetSize(800, 600);
}

MarvusFrame::~MarvusFrame()
{
	Unbind(wxEVT_MENU, &MarvusFrame::onExit, this, ID_Exit);
	Unbind(wxEVT_MENU, &MarvusFrame::onAbout, this, ID_About);
}

void MarvusFrame::configure(ConsoleLib::argVector& config)
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

wxMenuBar* MarvusFrame::createMenuBar()
{
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(ID_NotImplementedYet, "&New");
	fileMenu->Append(ID_NotImplementedYet, "&Open");
	fileMenu->Append(ID_NotImplementedYet, "&Import");
	fileMenu->Append(ID_NotImplementedYet, "&Export");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Exit, "&Exit");

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(ID_About, "&About");
	helpMenu->Append(ID_NotImplementedYet, "&About ConsoleLib");
	helpMenu->Append(ID_NotImplementedYet, "&License");

	wxMenu* transactionMenu = new wxMenu();
	transactionMenu->Append(ID_NotImplementedYet, "&Add");
	transactionMenu->Append(ID_NotImplementedYet, "&Backup");

	wxMenu* overviewMenu = new wxMenu();
	overviewMenu->Append(ID_NotImplementedYet, "&Table list");

	wxMenu* windowMenu = new wxMenu();
	windowMenu->Append(ID_NotImplementedYet, "&Preferences");

	// Create a menu bar and add menu sections
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(transactionMenu, "&Transactions");
	menuBar->Append(overviewMenu, "&Overviews");
	menuBar->Append(windowMenu, "&Window");
	menuBar->Append(helpMenu, "&Help");
	
	return menuBar;
}

void MarvusFrame::loadViewToGrid(Tabs tab)
{
	/*if (!views.contains(tab))
		return;

	tableHeaderAndData tableData = tribedb.obtainTableHeaderAndData(views.find(tab)->second);

	if (!grids2.contains(tab))
		return;

	wxGrid& grid = *grids2.find(tab)->second;

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
	grid.SetRowLabelSize(wxGRID_AUTOSIZE);*/
}

void MarvusFrame::loadViewToGrid(Table table)
{
	tableHeaderAndData tableData = db.obtainTableHeaderAndData("SELECT * FROM view_transactions;");

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
	for (const tableRowStructure& rowData : tableData.second)
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

void MarvusFrame::onRefreshWindow(wxCommandEvent&)
{
	/*for (const auto& tab : grids)
	{
		loadViewToGrid(tab.first);
	}

	for (const auto& tab : grids2)
	{
		loadViewToGrid(tab.first);
	}*/
}


void MarvusFrame::onNotImplemented(wxCommandEvent&)
{
	wxMessageBox("This function have not been implemented yet!.", "Implmentatation info", wxOK | wxICON_INFORMATION, this);
}

void MarvusFrame::onExit(wxCommandEvent&)
{
	Close(true); // Close the window
}

void MarvusFrame::onAbout(wxCommandEvent&)
{
	wxMessageBox("This is a wxWidgets application.", "About", wxOK | wxICON_INFORMATION, this);
}

void MarvusFrame::onInsertTestData(wxCommandEvent& event)
{
	/*KeoDefaults::KeoInserter inserter(db);
	inserter.fillEnums();
	inserter.fillTables();

	ConsoleLib::ScriptMap map;
	map.loadScripts("../data/");
	tribedb.executeSQL(map.getScript("tribal_default.sql"));
	tribedb.executeSQL(map.getScript("broken_oath_log.sql"));

	onRefreshWindow(event);*/
}

void MarvusFrame::onDropDatabase(wxCommandEvent&)
{
	//std::filesystem::remove(DATABASE_FILE);
	/*db.reconnect(DATABASE_FILE);
	db.initializeViews();

	std::filesystem::remove("tribalWars.db");
	tribedb.reconnect("tribalWars.db");
	tribedb.initializeViews();*/
}

// Event table to link menu actions with functions
wxBEGIN_EVENT_TABLE(MarvusFrame, wxFrame)
	EVT_MENU(ID_Exit, MarvusFrame::onExit)
	EVT_MENU(ID_About, MarvusFrame::onAbout)
	EVT_MENU(ID_NotImplementedYet, MarvusFrame::onNotImplemented)
	/*EVT_MENU(ID_Add_Emp, MarvusFrame::onAddEmployee)
	EVT_MENU(ID_Add_Job_Title, MarvusFrame::onAddJobTitle)
	EVT_MENU(ID_Refresh, MarvusFrame::onRefreshWindow)
	EVT_MENU(ID_DropDB, MarvusFrame::onDropDatabase)
	EVT_MENU(ID_InserTestData, MarvusFrame::onInsertTestData)
	EVT_MENU(ID_InsertNewVillage, MarvusFrame::onAddNewVillage)
	EVT_MENU(ID_InsertNewBattle, MarvusFrame::onAddNewBattle)*/
wxEND_EVENT_TABLE()

}
