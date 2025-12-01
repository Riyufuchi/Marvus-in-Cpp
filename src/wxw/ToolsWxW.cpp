//==============================================================================
// File       : ToolsWxW.cpp
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "ToolsWxW.h"

namespace wxw
{

void ToolsWxW::updateFontSizeInGrid(wxGrid* grid, int size)
{
	wxFont font = grid->GetDefaultCellFont();
	font.SetPointSize(size);
	grid->SetDefaultCellFont(font);
	grid->ForceRefresh();
}

} /* namespace consolelib */
