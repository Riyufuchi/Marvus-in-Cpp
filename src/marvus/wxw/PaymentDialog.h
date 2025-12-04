//==============================================================================
// File       : PaymentDialog.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Dec 05, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef VILLAGEDIALOG_H_
#define VILLAGEDIALOG_H_

#include <wx/datectrl.h>
#include <wx/dateevt.h>

#include "../../gui/base/DialogKEO.h"
#include "../../wxw/FactoryWxW.h"

#include "../database/MarvusDB.h"

#include "DataUtils.h"

namespace marvus
{

class PaymentDialog : public keo::DialogKEO
{
public:
	struct InputData
	{
		wxw::enumVector establishments;
		wxw::enumVector categories;
		std::string date;
	};
private:
	wxComboBox* establishmentComboBox;
	wxComboBox* categoryComboBox;
	wxSpinCtrlDouble* valueCtrl;
	wxDatePickerCtrl* datePicker;
	wxTextCtrl* note_txtbox;
public:
	PaymentDialog(wxWindow* parent, const InputData& inputData);
	virtual ~PaymentDialog();
	marvus::Payment getUserInput();
};

} /* namespace */

#endif
