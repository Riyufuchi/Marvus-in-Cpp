//==============================================================================
// File       : MainFrame.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <iostream>
#include <format>
#include <random>
//wxWidgets
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/textfile.h>
#include <wx/textdlg.h>
// ConsoleLib
#include "FileUtils.h"
// Other
#include "../../assets/icon.xpm"
#include "../marvus/wx_widgets/controller_wx.h"
#include "../marvus/wx_widgets/dialogs/file_transfer_dialog.h"
#include "../marvus/wx_widgets/dialogs/payment_dialog.h"
#include "../marvus/wx_widgets/panels/finance_graph_panel.h"
#include "../wx_tools/factory_wx.h"
#include "../wx_tools/tools_wx.h"

namespace wxtools
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
	ID_SendFile,
	ID_RecieveFile,
	ID_YearSummary,
	ID_ViewEstablishment,
	ID_ViewCategories,
	ID_ViewMacros,
	ID_DrawGraph
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
		marvus::FinanceGraphPanel* financeGraphPanel;
		// Backend
		marvus::ControllerWxW controller;
		// UI
		wxMenuBar* createMenuBar();
		void createToolBar();
		// Data handlers
		void loadViewToGrid(marvus::Table table, marvus::TableView view, marvus::insertVector data = {});
		void fillGrid(marvus::Table table, const marvus::tableHeaderAndData& data);
		//
		void displayError(const std::string& title, const std::string& message);
		// Events
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onNotImplemented(wxCommandEvent& event);
		void onInsertPayment(wxCommandEvent& event);
		void onRefreshWindow(wxCommandEvent& event);
		void onDropDatabase(wxCommandEvent& event);
		void onDateFilterChanged(wxCommandEvent& event);
		void onViewChanged(wxCommandEvent& event);
		void onSendFile(wxCommandEvent& event);
		void onRecieveFile(wxCommandEvent& event);
		void onShowGraph(wxCommandEvent& event);
		// Database file IO
		void onNewDB(wxCommandEvent& event);
		void onLoadDB(wxCommandEvent& event);
		void onImport(wxCommandEvent& event);
		#ifdef DEBUG
			void onInsertTestData(wxCommandEvent& event);
		#endif
		//
		wxDECLARE_EVENT_TABLE();
	public:
		MainFrame(consolelib::argVector& config);
		virtual ~MainFrame();
};
}
#endif /* MAINFRAME_H */ 
