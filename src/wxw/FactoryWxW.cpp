//==============================================================================
// File       : FactoryWxW.cpp
// Author     : riyufuchi
// Created on : Apr 01, 2025
// Last edit  : Dec 05, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "FactoryWxW.h"

namespace wxw
{

wxBoxSizer* FactoryWxW::newMaxSizer(wxWindow* component)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(component, 1, wxEXPAND | wxALL, 0);
	return sizer;
}

wxGrid* FactoryWxW::newGrid(wxWindow* parent, wxWindowID id)
{
	wxGrid* grid = new wxGrid(parent, id, wxPoint(0, 0), wxSize(400, 300));
	grid->CreateGrid(0, 0);
	return grid;
}

wxGrid* FactoryWxW::newGrid(wxWindow* parent, wxWindowID id, const std::vector<std::string>& header)
{
	wxGrid* grid = new wxGrid(parent, id, wxPoint(0, 0), wxSize(400, 300));
	grid->CreateGrid(0, header.size());
	int x = 0;
	for (const std::string& heading : header)
	{
		grid->SetColLabelValue(x, heading);
		x++;
	}
	return grid;
}

wxComboBox* FactoryWxW::newComboBox(wxWindow* parent, const enumVector& data)
{
	wxArrayString wxPlayerNames;
	if (data.empty()) // This insures that empty CB will not crash the application
		wxPlayerNames.Add("NULL");
	else
		for (const std::vector<std::string>& row : data)
		{
			wxPlayerNames.Add(wxString::FromUTF8(row[1]));
		}
	// Create the combo box (parent, id, default, pos, size, choices, style)
	wxComboBox* cb = new wxComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxPlayerNames, wxCB_READONLY);
	cb->SetSelection(0);
	return cb;
}

} /* namespace wxw */
