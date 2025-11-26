//==============================================================================
// File       : PaymentDialog.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef VILLAGEDIALOG_H_
#define VILLAGEDIALOG_H_

#include <wx/datectrl.h>
#include <wx/dateevt.h>

#include "../../gui/base/DialogKEO.h"
#include "../../wxw/FactoryWxW.h"

namespace marvus
{

class PaymentDialog : public keo::DialogKEO
{
public:
	struct InputData
	{
		wxw::enumVector establishments;
		wxw::enumVector categories;
	};
private:
	wxComboBox* establishmentComboBox;
	wxComboBox* categoryComboBox;
	wxSpinCtrl* valueCtrl;
	wxButton* dateButton;

	void onDateButtonClick(wxCommandEvent& event);
public:
	PaymentDialog(wxWindow* parent, const InputData& inputData);
	virtual ~PaymentDialog();
};

} /* namespace twdb */

#endif /* VILLAGEDIALOG_H_ */
