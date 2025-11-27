//==============================================================================
// File       : MainFrame.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../../assets/icon.xpm"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/textfile.h>

#include "../wxw/FactoryWxW.h"

#include "../marvus/Controller.h"
#include "../marvus/wxw/PaymentDialog.h"

namespace keo
{

enum
{
	ID_Exit = 1,
	ID_About,
	ID_Refresh,
	ID_DropDB,
	ID_InserTestData,
	ID_NotImplementedYet,
	ID_INSERT_PAYMENT,
	ID_Import
};

class MainFrame : public wxFrame
{
	private:
		std::unordered_map<marvus::Table, wxGrid*> grids;
		wxNotebook* notebook; // Tabbed pane
		marvus::Controller controller;
		void loadViewToGrid(marvus::Table table, marvus::TableViews view);
		wxMenuBar* createMenuBar();
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onInsertPayment(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		void onImport(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(const wxString& title, ConsoleLib::argVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
