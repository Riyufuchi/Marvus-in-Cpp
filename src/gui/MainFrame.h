#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../../assets/icon.xpm"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#include "../wxw/FactoryWxW.h"

// KEO
#include "../keodb/KeoDB.h"
#include "../keodb/KeoDefaultDB.hpp"
// Tribal
#include "../tribalDB/TribeDB.h"
#include "../dialogs/tw/VillageDialog.h"
#include "../dialogs/tw/BattleDialog.h"
#include "../dialogs/tw/UnitDialog.h"
// Other
#include "ArgumentParser.h"


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
	ID_InserTestData,
	ID_InsertNewVillage,
	ID_InsertNewBattle,
	ID_NotImplementedYet
};

enum class Tabs
{
	CAMPAIGN_OVERVIEW,
	BATTLES,
	VILLAGES
};

class MainFrame : public wxFrame
{
	private:
		std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
		std::unordered_map<Table, wxGrid*> grids;
		std::unordered_map<Tabs, wxGrid*> grids2;
		std::unordered_map<Tabs, std::string> views;
		KeoDB db;
		twdb::TribeDB tribedb;
		wxNotebook* notebook; // Tabbed pane
		void configure(ConsoleLib::argVector& config);
		void loadViewToGrid(keo::Table table);
		void loadViewToGrid(Tabs tab);
		wxMenuBar* createMenuBar();
		void initTribeDB();
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onAddJobTitle(wxCommandEvent& event);
		void onAddEmployee(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		void onAddNewVillage(wxCommandEvent& event);
		void onAddNewBattle(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(const wxString& title, ConsoleLib::argVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
