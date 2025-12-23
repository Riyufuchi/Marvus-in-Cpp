//==============================================================================
// File       : DialogKEO.cpp
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "../../wx_widgets/base/dialog_base.h"

namespace keo
{

DialogKEO::DialogKEO(wxWindow* parent, std::string title) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300)), confirmed(false)
{
}

DialogKEO::~DialogKEO()
{
}

void DialogKEO::onOK(wxCommandEvent&)
{
	confirmed = true;
	EndModal(wxID_OK);
}

void DialogKEO::onCancel(wxCommandEvent&)
{
	EndModal(wxID_CANCEL);
}

bool DialogKEO::isConfirmed() const
{
	return confirmed;
}

wxBEGIN_EVENT_TABLE(DialogKEO, wxDialog)
	EVT_BUTTON(wxID_OK, DialogKEO::onOK)
	EVT_BUTTON(wxID_CANCEL, DialogKEO::onCancel)
wxEND_EVENT_TABLE()

} /* namespace twdb */
