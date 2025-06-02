//==============================================================================
// File       : UnitDialog.h
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef DIALOGS_TW_UNITDIALOG_H_
#define DIALOGS_TW_UNITDIALOG_H_

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "../../database/Database.h"

namespace twdb
{

class UnitDialog : public wxDialog
{
private:
	bool confirmed;
	const int BATTLE_ID;
	std::vector<std::pair<wxSpinCtrl*, wxSpinCtrl*>> unitSpinCtrls;
	void onOK(wxCommandEvent& event);
	void onCancel(wxCommandEvent& event);
public:
	UnitDialog(wxWindow* parent, int battleID, const marvus::tableStructure& unitNames);
	virtual ~UnitDialog();
	bool isConfirmed() const;
	std::vector<marvus::insertVector> getUnitsData();
private:
	wxDECLARE_EVENT_TABLE();
};

} /* namespace twdb */

#endif /* DIALOGS_TW_UNITDIALOG_H_ */
