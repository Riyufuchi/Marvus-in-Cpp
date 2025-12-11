//==============================================================================
// File       : ToolsWxW.cpp
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "../wxTools/ToolsWxW.h"

namespace wxtools
{

void ToolsWxW::updateFontSizeInGrid(wxGrid* grid, int size)
{
	wxFont font = grid->GetDefaultCellFont();
	font.SetPointSize(size);
	grid->SetDefaultCellFont(font);
	grid->ForceRefresh();
}

void ToolsWxW::informationDialog(const std::string& title, const std::string& text)
{
	wxMessageBox(text, title, wxOK | wxICON_INFORMATION, this);
}

} /* namespace consolelib */
