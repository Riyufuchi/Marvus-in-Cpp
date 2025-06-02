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

#include "../abstract/DialogKEO.h"

namespace twdb
{

class UnitDialog : public keo::DialogKEO
{
private:
	const int BATTLE_ID;
	std::vector<std::pair<wxSpinCtrl*, wxSpinCtrl*>> unitSpinCtrls;
public:
	UnitDialog(wxWindow* parent, int battleID, const marvus::tableStructure& unitNames);
	virtual ~UnitDialog();
	std::vector<marvus::insertVector> getUnitsData();
};

} /* namespace twdb */

#endif /* DIALOGS_TW_UNITDIALOG_H_ */
