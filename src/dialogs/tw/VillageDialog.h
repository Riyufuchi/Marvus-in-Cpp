//==============================================================================
// File       : VillageDialog.h
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef VILLAGEDIALOG_H_
#define VILLAGEDIALOG_H_

#include "../abstract/DialogKEO.h"

namespace twdb
{

class VillageDialog : public keo::DialogKEO
{
private:
	wxTextCtrl* villageNameCtrl;
	wxComboBox* ownerComboBox;
public:
	VillageDialog(wxWindow* parent, const std::vector<std::vector<std::string>>& players);
	virtual ~VillageDialog();
	std::string getVillageName() const;
	int getOwnerID() const;
};

} /* namespace twdb */

#endif /* VILLAGEDIALOG_H_ */
