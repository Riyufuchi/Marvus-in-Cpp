//==============================================================================
// File       : FactoryWxW.h
// Author     : riyufuchi
// Created on : Apr 01, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef WXTOOLS_FACTORY_WX_H_
#define WXTOOLS_FACTORY_WX_H_

#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/grid.h>

namespace wxtools
{
using enumVector = std::vector<std::vector<std::string>>;
}

namespace wxtools::factory_wx
{
wxBoxSizer* newMaxSizer(wxWindow* component);
wxGrid* newGrid(wxWindow* parent, wxWindowID id);
wxGrid* newGrid(wxWindow* parent, wxWindowID id, const std::vector<std::string>& header);
wxComboBox* newComboBox(wxWindow* parent, const enumVector& data);
}
#endif
