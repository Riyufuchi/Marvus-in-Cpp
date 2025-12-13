//==============================================================================
// File       : PaymentDialog.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef VILLAGEDIALOG_H_
#define VILLAGEDIALOG_H_

#include <wx/datectrl.h>
#include <wx/dateevt.h>

#include "../../../wxTools/FactoryWxW.h"

#include "../../database/MarvusDB.h"

#include "DataUtils.h"
#include "../../../wxWidgets/base/DialogKEO.h"

namespace marvus
{

class PaymentDialog : public keo::DialogKEO
{
public:
	struct InputData
	{
		wxtools::enumVector establishments;
		wxtools::enumVector categories;
		std::string date;
	};
private:
	const InputData& inputData;
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
