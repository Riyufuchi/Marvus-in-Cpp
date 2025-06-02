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

#include "../abstract/DialogKEO.h"

namespace twdb
{

class BattleDialog : public keo::DialogKEO
{
private:
	wxComboBox* campaignBox;
	wxComboBox* targetVillageBox;
	wxComboBox* sourceVillageBox;
	wxCheckBox* checkBox;
	wxSpinCtrl* woodLootCtrl;
	wxSpinCtrl* clayLootCtrl;
	wxSpinCtrl* ironLootCtrl;
public:
	BattleDialog(wxWindow* parent, const marvus::tableStructure& campaigns, const marvus::tableStructure& villages);
	virtual ~BattleDialog();
	marvus::insertVector getBattleData() const;
	int getCampaignID() const;
};

} /* namespace twdb */

#endif /* DIALOGS_TW_BATTLEDIALOG_H_ */
