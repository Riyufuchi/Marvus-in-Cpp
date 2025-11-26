//==============================================================================
// File       : MainFrame.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../../assets/icon.xpm"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#include "../wxw/FactoryWxW.h"
#include "../marvus/MarvusDB.h"
#include "../dialogs/marvus/PaymentDialog.h"
// ConsoleLib
#include "ArgumentParser.h"

namespace keo
{

inline const std::string DATABASE_FILE = "keo-main.db";

enum
{
	ID_Exit = 1,
	ID_About,
	ID_Refresh,
	ID_DropDB,
	ID_InserTestData,
	ID_NotImplementedYet,
	ID_INSERT_PAYMENT
};

enum class Table
{
	PAYMENTS,
	ESTABLISHMENTS,
	CATEGORIES
};

enum class TableViews
{
	PAYMENTS_VIEW,
	ESTABLISHMENTS_VIEW,
	CATEGORIES_VIEW
};

class MainFrame : public wxFrame
{
	private:
		std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
		std::unordered_map<Table, wxGrid*> grids;
		std::unordered_map<TableViews, std::string> views;
		std::unordered_map<Table, TableViews> selectedViews;
		marvus::MarvusDB marvusDB;
		wxNotebook* notebook; // Tabbed pane
		void configure(ConsoleLib::argVector& config);
		void loadViewToGrid(Table table, TableViews view);
		wxMenuBar* createMenuBar();
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onInsertPayment(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(const wxString& title, ConsoleLib::argVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
