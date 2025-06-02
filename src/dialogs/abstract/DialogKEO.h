//==============================================================================
// File       : DialogKEO.h
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef DIALOGS_ABSTRACT_DIALOGKEO_H_
#define DIALOGS_ABSTRACT_DIALOGKEO_H_

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "../../database/Database.h"

namespace keo
{

class DialogKEO : public wxDialog
{
private:
	bool confirmed;
	void onOK(wxCommandEvent& event);
	void onCancel(wxCommandEvent& event);
public:
	DialogKEO(wxWindow* parent, std::string title);
	virtual ~DialogKEO();
	bool isConfirmed() const;
private:
	wxDECLARE_EVENT_TABLE();
};

} /* namespace */

#endif /* DIALOGS_ABSTRACT_DIALOGKEO_H_ */
