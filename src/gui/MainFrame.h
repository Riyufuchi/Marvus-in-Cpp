#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../../assets/icon.xpm"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#include "../wxw/FactoryWxW.h"

#include "../keodb/KeoDB.h"
#include "../keodb/KeoDefaultDB.hpp"

#include "ConsoleUtils.h"


namespace keo
{

inline const std::string DATABASE_FILE = "keo-main.db";

enum
{
	ID_Exit = 1,
	ID_About,
	ID_Add_Emp,
	ID_Add_Job_Title,
	ID_Refresh,
	ID_DropDB,
	ID_InserTestData
};

class MainFrame : public wxFrame
{
	private:
		std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
		KeoDB db;
		wxNotebook* notebook; // Tabbed pane
		wxGrid* empGrid; // wxGrid for displaying data
		wxGrid* farmladGrid;
		wxGrid* minesGrid;
		void configure(ConsoleLib::argumentVector& config);
		void loadDataToGrid(wxGrid& grid, keo::Table table);
		wxMenuBar* createMenuBar();
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onAddJobTitle(wxCommandEvent& event);
		void onAddEmployee(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(const wxString& title, ConsoleLib::argumentVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
