//==============================================================================
// File       : FactoryWxW.h
// Author     : riyufuchi
// Created on : Apr 1, 2025
// Last edit  : Apr 1, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef WXW_FACTORYWXW_H_
#define WXW_FACTORYWXW_H_

#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/grid.h>

namespace wxw
{

using enumVector = std::vector<std::vector<std::string>>;

class FactoryWxW
{
public:
	FactoryWxW() = default;
	virtual ~FactoryWxW() = default;
	static wxBoxSizer* newMaxSizer(wxWindow* component);
	static wxGrid* newGrid(wxWindow* parent, wxWindowID id);
	static wxGrid* newGrid(wxWindow* parent, wxWindowID id, const std::vector<std::string>& header);
	static wxComboBox* newComboBox(wxWindow* parent, const enumVector& data);
};

} /* namespace wxw */

#endif /* WXW_FACTORYWXW_H_ */
