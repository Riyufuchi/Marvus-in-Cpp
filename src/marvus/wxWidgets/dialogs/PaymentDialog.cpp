//==============================================================================
// File       : PaymentDialog.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Dec 05, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "../../wxWidgets/dialogs/PaymentDialog.h"

namespace marvus
{

PaymentDialog::PaymentDialog(wxWindow* parent, const InputData& inputData) : keo::DialogKEO(parent, "Add new Payment"), inputData(inputData)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);

	establishmentComboBox = wxtools::factory_wx::newComboBox(this, inputData.establishments);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Establishment:"), 0, wxTOP | wxLEFT, 5);
	gridSizer->Add(establishmentComboBox, 0, wxEXPAND | wxALL, 5);

	categoryComboBox = wxtools::factory_wx::newComboBox(this, inputData.categories);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Category:"), 0, wxTOP | wxLEFT, 5);
	gridSizer->Add(categoryComboBox, 0, wxEXPAND | wxALL, 5);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Value:"), 0, wxTOP | wxLEFT, 5);
	//valueCtrl = new wxTextCtrl(this, wxID_ANY);
	valueCtrl = new wxSpinCtrlDouble(this, wxID_ANY, "0.00", wxDefaultPosition,wxDefaultSize,
		wxSP_ARROW_KEYS | wxSP_WRAP, -1e9, 1e9, 0.0, 0.25);
	valueCtrl->SetDigits(2);
	gridSizer->Add(valueCtrl, 0, wxALL | wxEXPAND, 5);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxTOP | wxLEFT, 5);
	// Current date
	wxDateTime current;
	current.ParseDate(inputData.date);

	datePicker = new wxDatePickerCtrl(this, wxID_ANY, current.IsValid() ? current : wxDateTime::Today(),
		wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	gridSizer->Add(datePicker, 0, wxALL | wxEXPAND, 5);

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

marvus::Payment PaymentDialog::getUserInput()
{
	marvus::Payment payment;
	payment.ent_key = std::stoi(inputData.establishments[establishmentComboBox->GetCurrentSelection()][0]);
	payment.category_key = std::stoi(inputData.categories[categoryComboBox->GetCurrentSelection()][0]);

	payment.value = valueCtrl->GetTextValue().ToStdString();

	payment.date = datePicker->GetValue().Format("%Y-%m-%d").ToStdString();

	payment.note = std::string(note_txtbox->GetValue().ToUTF8());
	return payment;
}

} /* namespace */
