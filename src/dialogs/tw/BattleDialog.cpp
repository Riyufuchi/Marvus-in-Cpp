//==============================================================================
// File       : BattleDialog.cpp
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "BattleDialog.h"

namespace twdb
{

BattleDialog::BattleDialog(wxWindow* parent, const marvus::tableStructure& campaigns, const marvus::tableStructure& villages) : wxDialog(parent, wxID_ANY, "Add new battle", wxDefaultPosition, wxSize(300, 300)), confirmed(false)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(new wxStaticText(this, wxID_ANY, "Campaign:"), 0, wxALL, 5);

	wxArrayString wxCampaigns;
	for (const std::vector<std::string>& row : campaigns)
	{
		wxCampaigns.Add(row[1]);
	}

	campaignBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxCampaigns, wxCB_READONLY);
	if (!wxCampaigns.empty())
		campaignBox->SetSelection(0);

	sizer->Add(campaignBox, 0, wxEXPAND | wxALL, 5);

	wxArrayString wxVillages;
	for (const std::vector<std::string>& row : villages)
	{
		wxVillages.Add(row[1]);
	}

	sourceVillageBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxVillages, wxCB_READONLY);
	targetVillageBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxVillages, wxCB_READONLY);
	if (wxVillages.size() > 1)
	{
		sourceVillageBox->SetSelection(0);
		targetVillageBox->SetSelection(1);
	}

	sizer->Add(new wxStaticText(this, wxID_ANY, "Source village:"), 0, wxALL, 5);
	sizer->Add(sourceVillageBox, 0, wxEXPAND | wxALL, 5);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Target village:"), 0, wxALL, 5);
	sizer->Add(targetVillageBox, 0, wxEXPAND | wxALL, 5);

	sizer->Add(new wxStaticText(this, wxID_ANY, "Is offense:"), 0, wxALL, 5);
	checkBox = new wxCheckBox(this, wxID_ANY, "");
	checkBox->SetValue(true);
	sizer->Add(checkBox, 0, wxALL, 5);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Wood looted:"), 0, wxALL, 5);
	woodLootCtrl = new wxSpinCtrl(this, wxID_ANY);
	sizer->Add(woodLootCtrl, 0, wxALL | wxEXPAND, 5);
	woodLootCtrl->SetRange(0, 9999999);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Clay looted:"), 0, wxALL, 5);
	clayLootCtrl = new wxSpinCtrl(this, wxID_ANY);
	clayLootCtrl->SetRange(0, 9999999);
	sizer->Add(clayLootCtrl, 0, wxALL | wxEXPAND, 5);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Iron looted:"), 0, wxALL, 5);
	ironLootCtrl = new wxSpinCtrl(this, wxID_ANY);
	ironLootCtrl->SetRange(0, 9999999);
	sizer->Add(ironLootCtrl, 0, wxALL | wxEXPAND, 5);

	sizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxEXPAND, 10);
	SetSizerAndFit(sizer);
}

BattleDialog::~BattleDialog()
{
}

void BattleDialog::onOK(wxCommandEvent& event)
{
	confirmed = true;
	EndModal(wxID_OK);
}

void BattleDialog::onCancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

bool BattleDialog::isConfirmed() const
{
	return confirmed;
}

int BattleDialog::getCampaignID() const
{
	return campaignBox->GetCurrentSelection() + 1;
}

marvus::insertVector BattleDialog::getBattleData() const
{
	marvus::insertVector data;
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(1)));
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(woodLootCtrl->GetValue())));
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(clayLootCtrl->GetValue())));
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(ironLootCtrl->GetValue())));
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(sourceVillageBox->GetCurrentSelection() + 1)));
	data.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(targetVillageBox->GetCurrentSelection() + 1)));
	return data;
}

wxBEGIN_EVENT_TABLE(BattleDialog, wxDialog)
	EVT_BUTTON(wxID_OK, BattleDialog::onOK)
	EVT_BUTTON(wxID_CANCEL, BattleDialog::onCancel)
wxEND_EVENT_TABLE()

} /* namespace twdb */
