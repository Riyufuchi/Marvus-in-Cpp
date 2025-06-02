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

#include <wx/wx.h>

namespace twdb
{

class VillageDialog : public wxDialog
{
private:
	bool confirmed;
	wxTextCtrl* villageNameCtrl;
	wxComboBox* ownerComboBox;
	void onOK(wxCommandEvent& event);
	void onCancel(wxCommandEvent& event);
public:
	VillageDialog(wxWindow* parent, const std::vector<std::vector<std::string>>& players);
	virtual ~VillageDialog();
	std::string getVillageName() const;
	int getOwnerID() const;
	bool isConfirmed() const;
private:
	wxDECLARE_EVENT_TABLE();
};

} /* namespace twdb */

#endif /* VILLAGEDIALOG_H_ */
