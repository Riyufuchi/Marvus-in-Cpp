//==============================================================================
// File       : FactoryWxW.cpp
// Author     : riyufuchi
// Created on : Apr 1, 2025
// Last edit  : Apr 1, 2025
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

} /* namespace wxw */
