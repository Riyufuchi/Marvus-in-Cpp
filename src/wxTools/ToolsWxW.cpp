//==============================================================================
// File       : ToolsWxW.cpp
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 30, 2025
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
	tinyfd_messageBox(title.c_str(), text.c_str(), "ok", "info", 1);
}

} /* namespace consolelib */
