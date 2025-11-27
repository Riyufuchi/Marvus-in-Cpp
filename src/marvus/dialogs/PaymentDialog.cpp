//==============================================================================
// File       : PaymentDialog.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "PaymentDialog.h"

namespace marvus
{

PaymentDialog::PaymentDialog(wxWindow* parent, const InputData& inputData) : keo::DialogKEO(parent, "Add new Payment")
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);

	establishmentComboBox = wxw::FactoryWxW::newComboBox(this, inputData.establishments);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Establishment:"), 0, wxTOP | wxLEFT, 5);
	gridSizer->Add(establishmentComboBox, 0, wxEXPAND | wxALL, 5);

	categoryComboBox = wxw::FactoryWxW::newComboBox(this, inputData.categories);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Category:"), 0, wxTOP | wxLEFT, 5);
	gridSizer->Add(categoryComboBox, 0, wxEXPAND | wxALL, 5);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Value:"), 0, wxTOP | wxLEFT, 5);
	valueCtrl = new wxSpinCtrl(this, wxID_ANY);
	gridSizer->Add(valueCtrl, 0, wxALL | wxEXPAND, 5);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxTOP | wxLEFT, 5);
	// Current date
	wxDateTime current;
	current.ParseDate(inputData.date);

	picker = new wxDatePickerCtrl(this, wxID_ANY, current.IsValid() ? current : wxDateTime::Today(),
		wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	gridSizer->Add(picker, 0, wxALL | wxEXPAND, 5);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Note:"), 0, wxTOP | wxLEFT, 5);
	note_txtbox = new wxTextCtrl(this, wxID_ANY);
	gridSizer->Add(note_txtbox, 0, wxALL | wxEXPAND, 5);

	sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
	// OK / Cancel buttons
	sizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxEXPAND, 10);
	SetSizerAndFit(sizer);
	// Set focus after dialog is fully created
	CallAfter([this]() {
		establishmentComboBox->SetFocus();
	});
}

PaymentDialog::~PaymentDialog()
{
}
/*
void PaymentDialog::onDateButtonClick(wxCommandEvent&)
{
	wxDateTime current;
	current.ParseDate(dateButton->GetLabel());

	wxDialog dlg(this, wxID_ANY, "Choose Date");

	// Popup date picker dialog


	// Show it modally through a simple dialog

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(picker, 1, wxALL | wxEXPAND, 10);

	// OK button
	wxButton* okBtn = new wxButton(&dlg, wxID_OK, "OK");
	sizer->Add(okBtn, 0, wxALL | wxALIGN_CENTER, 10);

	dlg.SetSizerAndFit(sizer);

	if (dlg.ShowModal() == wxID_OK)
	{
		wxDateTime selected = picker->GetValue();
		wxString newDate = selected.Format("%d.%m.%Y");
		dateButton->SetLabel(newDate);
	}
}*/

} /* namespace */
