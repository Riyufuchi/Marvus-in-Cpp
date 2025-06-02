//==============================================================================
// File       : VillageDialog.cpp
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "VillageDialog.h"

namespace twdb
{

VillageDialog::VillageDialog(wxWindow* parent, const std::vector<std::vector<std::string>>& players) : keo::DialogKEO(parent, "Add new village")
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(new wxStaticText(this, wxID_ANY, "Village name:"), 0, wxALL, 5);
	villageNameCtrl = new wxTextCtrl(this, wxID_ANY);
	sizer->Add(villageNameCtrl, 0, wxALL | wxEXPAND, 5);

	wxArrayString wxPlayerNames;
	for (const std::vector<std::string>& row : players)
	{
		wxPlayerNames.Add(row[1]);
	}
	// Create the combo box (parent, id, default, pos, size, choices, style)
	ownerComboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxPlayerNames, wxCB_READONLY);
	if (!players.empty())
		ownerComboBox->SetSelection(0);

	sizer->Add(new wxStaticText(this, wxID_ANY, "Village Owner:"), 0, wxTOP | wxLEFT, 5);
	sizer->Add(ownerComboBox, 0, wxEXPAND | wxALL, 5);

	// OK / Cancel buttons
	sizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxEXPAND, 10);
	SetSizerAndFit(sizer);
	// Set focus after dialog is fully created
	CallAfter([this]() {
		villageNameCtrl->SetFocus();
	});
}

VillageDialog::~VillageDialog()
{
}

std::string VillageDialog::getVillageName() const
{
	return std::string(villageNameCtrl->GetValue().mb_str(wxConvUTF8));
}

// DB IDs starts at number 1, while combobox indexes from 0
int VillageDialog::getOwnerID() const
{
	return ownerComboBox->GetCurrentSelection() + 1;
}

} /* namespace */
