//==============================================================================
// File       : BattleDialog.h
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef DIALOGS_TW_BATTLEDIALOG_H_
#define DIALOGS_TW_BATTLEDIALOG_H_

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "../../database/Database.h"

namespace twdb
{

class BattleDialog : public wxDialog
{
private:
	bool confirmed;
	wxComboBox* campaignBox;
	wxComboBox* targetVillageBox;
	wxComboBox* sourceVillageBox;
	wxCheckBox* checkBox;
	wxSpinCtrl* woodLootCtrl;
	wxSpinCtrl* clayLootCtrl;
	wxSpinCtrl* ironLootCtrl;
	void onOK(wxCommandEvent& event);
	void onCancel(wxCommandEvent& event);
public:
	BattleDialog(wxWindow* parent, const marvus::tableStructure& campaigns, const marvus::tableStructure& villages);
	virtual ~BattleDialog();
	bool isConfirmed() const;
	marvus::insertVector getBattleData() const;
	int getCampaignID() const;
private:
	wxDECLARE_EVENT_TABLE();
};

} /* namespace twdb */

#endif /* DIALOGS_TW_BATTLEDIALOG_H_ */
