//==============================================================================
// File       : UnitDialog.cpp
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "UnitDialog.h"

namespace twdb
{

UnitDialog::UnitDialog(wxWindow* parent, int battleID, const marvus::tableStructure& unitNames) : keo::DialogKEO(parent, "Add units to the battle"), BATTLE_ID(battleID)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Grid for units: Label | Sent | Lost
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(3, 5, 5); // 3 columns, 5px gaps
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Unit"), 0, wxALIGN_CENTER | wxBOTTOM, 5);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Sent"), 0, wxALIGN_CENTER | wxBOTTOM, 5);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Lost"), 0, wxALIGN_CENTER | wxBOTTOM, 5);

	for (const marvus::tableRowStructure& row : unitNames)
	{
		wxSpinCtrl* spinnerSend = new wxSpinCtrl(this, wxID_ANY);
		spinnerSend->SetRange(0, 9999999);

		wxSpinCtrl* spinnerLost = new wxSpinCtrl(this, wxID_ANY);
		spinnerLost->SetRange(0, 9999999);

		gridSizer->Add(new wxStaticText(this, wxID_ANY, row[1]), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
		gridSizer->Add(spinnerSend, 1, wxEXPAND | wxALL, 2);
		gridSizer->Add(spinnerLost, 1, wxEXPAND | wxALL, 2);

		unitSpinCtrls.emplace_back(std::make_pair(spinnerSend, spinnerLost));
	}

	gridSizer->AddGrowableCol(1); // Allow "Sent" to expand
	gridSizer->AddGrowableCol(2); // Allow "Lost" to expand

	mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
	mainSizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxEXPAND, 10);

	SetSizerAndFit(mainSizer);
}

UnitDialog::~UnitDialog()
{
}

std::vector<marvus::insertVector> UnitDialog::getUnitsData()
{
	std::vector<marvus::insertVector> data;
	marvus::insertVector row;
	int unitID = 0;
	for (const std::pair<wxSpinCtrl*, wxSpinCtrl*>& unitNum : unitSpinCtrls)
	{
		unitID++;
		if (unitNum.first->GetValue() == 0)
			continue;
		row.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(unitNum.first->GetValue())));
		row.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(unitNum.second->GetValue())));
		row.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(unitID)));
		row.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(BATTLE_ID)));
		data.emplace_back(row);
		row.clear();
	}
	return data;
}

} /* namespace twdb */
