//==============================================================================
// File       : ToolsWxW.h
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef WXTOOLS_TOOLS_WX_H_
#define WXTOOLS_TOOLS_WX_H_

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textdlg.h>

namespace wxtools
{
void updateFontSizeInGrid(wxGrid* grid, int size);
}
#endif
