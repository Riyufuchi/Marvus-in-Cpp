//==============================================================================
// File       : ToolsWxW.cpp
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "tools_wx.h"

namespace wxtools
{

void updateFontSizeInGrid(wxGrid* grid, int size)
{
	wxFont font = grid->GetDefaultCellFont();
	font.SetPointSize(size);
	grid->SetDefaultCellFont(font);
	grid->ForceRefresh();
}

}
