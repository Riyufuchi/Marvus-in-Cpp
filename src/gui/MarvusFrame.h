#ifndef _MARVUS_FRAME_H
#define _MARVUS_FRAME_H

//#include "../../assets/icon.xpm"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#include "../wxw/FactoryWxW.h"

// Database
#include "../database/PostgreController.h"

#include "ArgumentParser.h"


namespace riyufuchi
{

inline const std::string DATABASE_CONN = "host=localhost port=5432 dbname=marvus user=theadministrator password=secret";

enum
{
	ID_Exit = 1,
	ID_About,
	ID_NotImplementedYet
};

enum class Tabs
{
	MAIN_TAB
};

enum class Table
{
	MAIN
};

class MarvusFrame : public wxFrame
{
	private:
		std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
		std::unordered_map<Table, wxGrid*> grids;
		//std::unordered_map<Tabs, wxGrid*> grids2;
		//std::unordered_map<Tabs, std::string> views;
		PostgreController db;
		wxNotebook* notebook; // Tabbed pane
		void configure(ConsoleLib::argVector& config);
		void loadViewToGrid(Table table);
		void loadViewToGrid(Tabs tab);
		wxMenuBar* createMenuBar();
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	public:
		MarvusFrame(const wxString& title, ConsoleLib::argVector& config);
		virtual ~MarvusFrame();
};
}
#endif /* MAINFRAME_H */ 
