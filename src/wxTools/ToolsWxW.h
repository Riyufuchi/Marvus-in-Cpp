//==============================================================================
// File       : ToolsWxW.h
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef WXTOOLS_TOOLSWXW_H_
#define WXTOOLS_TOOLSWXW_H_

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textdlg.h>

namespace wxtools
{

class ToolsWxW
{
public:
	ToolsWxW() = default;
	virtual ~ToolsWxW() = default;
	static void updateFontSizeInGrid(wxGrid* grid, int size);
};

} /* namespace consolelib */

#endif /* WXTOOLS_TOOLSWXW_H_ */
