//==============================================================================
// File       : FinanceGraphPanel.h
// Author     : riyufuchi
// Created on : Dec 13, 2025
// Last edit  : Dec 16, 2025
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
public:
	struct GraphInfo
	{
		double maxValue;
		double minValue;
		wxSize panelSize;
		wxColour lineColor {wxColour(0, 200, 255)};
		wxColour ballColor {wxColour(255, 0, 0)};
		std::vector<double> values;
		std::vector<std::string> xAxisLabels;
	};
private:
	wxTimer m_timer;
	double m_animPos = 0.0; // 0.0 – 1.0 animation progress
	GraphInfo graphInfo;
	void OnPaint(wxPaintEvent& evt);
	void OnTimer(wxTimerEvent& evt);
public:
	FinanceGraphPanel(wxWindow* parent);
	virtual ~FinanceGraphPanel();
	void refreshData(const tableRowVector& stringValues);
};

} /* namespace marvus */

#endif /* MARVUS_WXWIDGETS_PANELS_FINANCEGRAPHPANEL_H_ */
