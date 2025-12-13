//==============================================================================
// File       : FinanceGraphPanel.h
// Author     : riyufuchi
// Created on : Dec 13, 2025
// Last edit  : Dec 13, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WXWIDGETS_PANELS_FINANCEGRAPHPANEL_H_
#define MARVUS_WXWIDGETS_PANELS_FINANCEGRAPHPANEL_H_

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/graphics.h>

#include "../../base/Controller.h"

namespace marvus
{

class FinanceGraphPanel : public wxPanel
{
private:
	wxTimer m_timer;
	double m_animPos = 0.0; // 0.0 – 1.0 animation progress
	std::vector<double> values; // 365/366 daily values
	std::vector<std::string> dates;
	void OnPaint(wxPaintEvent& evt);
	void OnTimer(wxTimerEvent& evt);
public:
	FinanceGraphPanel(wxWindow* parent);
	virtual ~FinanceGraphPanel();
	void refreshData(Controller& controller);
};

} /* namespace marvus */

#endif /* MARVUS_WXWIDGETS_PANELS_FINANCEGRAPHPANEL_H_ */
