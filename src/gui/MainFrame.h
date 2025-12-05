//==============================================================================
// File       : MainFrame.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 05, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <iostream>
#include <format>
//wxWidgets
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/textfile.h>
#include <wx/textdlg.h>
// Cutom wxWidgets tools
#include "../wxw/FactoryWxW.h"
#include "../wxw/ToolsWxW.h"
// Local
#include "../marvus/Controller.h"
#include "../marvus/wxw/PaymentDialog.h"
// ConsoleLib
#include "FileUtils.h"
#include "Library.h"
// Other
#include "../../assets/icon.xpm"

namespace wxw
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
	ID_Import,
	ID_NewDB,
	ID_OpenDB,
	ID_TableListView
};

class MainFrame : public wxFrame
{
	private:
		std::unordered_map<marvus::Table, wxGrid*> grids;
		std::unordered_map<marvus::Table, std::pair<marvus::TableView, marvus::insertVector>> selectedViewForTable;
		// Controls
		wxNotebook* notebook; // Tabbed pane
		wxChoice* monthChoice;
		wxCheckBox* monthFilterCheck;
		// Backend
		marvus::Controller controller;
		// UI
		wxMenuBar* createMenuBar();
		void createToolBar();
		// Data handlers
		void loadViewToGrid(marvus::Table table, marvus::TableView view, marvus::insertVector data = {});
		void fillGrid(marvus::Table table, const marvus::tableHeaderAndData& data);
		//
		void displayError(const std::string& title, const std::string& message);
		// Events
		void onNewDB(wxCommandEvent& event);
		void onLoadDB(wxCommandEvent& event);
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onInsertPayment(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onInsertTestData(wxCommandEvent& event);
		void onImport(wxCommandEvent& event);
		void onDateFilterChanged(wxCommandEvent& event);
		void onViewChanged(wxCommandEvent& event);
		//
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(const wxString& title, consolelib::argVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
