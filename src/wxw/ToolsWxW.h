//==============================================================================
// File       : ToolsWxW.h
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef WXW_TOOLSWXW_H_
#define WXW_TOOLSWXW_H_

#include <wx/wx.h>
#include <wx/grid.h>

namespace wxw
{

class ToolsWxW
{
public:
	ToolsWxW() = default;
	virtual ~ToolsWxW() = default;
	static void updateFontSizeInGrid(wxGrid* grid, int size);
};

} /* namespace consolelib */

#endif /* WXW_TOOLSWXW_H_ */
