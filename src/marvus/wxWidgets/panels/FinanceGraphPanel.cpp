//==============================================================================
// File       : FinanceGraphPanel.cpp
// Author     : riyufuchi
// Created on : Dec 13, 2025
// Last edit  : Dec 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "FinanceGraphPanel.h"

namespace marvus
{

FinanceGraphPanel::FinanceGraphPanel(wxWindow* parent) : wxPanel(parent), m_timer(this)
{
	Bind(wxEVT_PAINT, &FinanceGraphPanel::OnPaint, this);
	Bind(wxEVT_TIMER, &FinanceGraphPanel::OnTimer, this);

	m_timer.Start(16); // ~60 FPS
}

FinanceGraphPanel::~FinanceGraphPanel()
{
}

void FinanceGraphPanel::OnPaint(wxPaintEvent&)
{
	if (graphInfo.values.empty())
		return;
	wxPaintDC dc(this);
	auto gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	graphInfo.panelSize = GetClientSize();

	// Background
	gc->SetBrush(*wxBLACK_BRUSH);
	gc->DrawRectangle(0, 0, graphInfo.panelSize.x, graphInfo.panelSize.y);

	// Axes margins
	const int margin = 40;
	const int w = graphInfo.panelSize.x - 2 * margin;
	const int h = graphInfo.panelSize.y - 2 * margin;

	// Draw line
	gc->SetPen(wxPen(graphInfo.lineColor, 2));

	for (size_t i = 1; i < graphInfo.values.size(); ++i)
	{
		double x1 = margin + (i - 1) * w / double(graphInfo.values.size() - 1);
		double y1 = margin + h * (1.0 - (graphInfo.values[i - 1] - graphInfo.minValue) / (graphInfo.maxValue - graphInfo.minValue));

		double x2 = margin + i * w / double(graphInfo.values.size() - 1);
		double y2 = margin + h * (1.0 - (graphInfo.values[i] - graphInfo.minValue) / (graphInfo.maxValue - graphInfo.minValue));

		gc->StrokeLine(x1, y1, x2, y2);
	}

	// Draw animated ball
	size_t idx = size_t(m_animPos * (graphInfo.values.size() - 1));
	double x = margin + idx * w / double(graphInfo.values.size() - 1);
	double y = margin + h * (1.0 - (graphInfo.values[idx] - graphInfo.minValue) / (graphInfo.maxValue - graphInfo.minValue));

	gc->SetBrush(graphInfo.ballColor);
	gc->DrawEllipse(x - 4, y - 4, 8, 8);

	delete gc;
}

void FinanceGraphPanel::OnTimer(wxTimerEvent&)
{
	m_animPos += 0.002; // speed
	if (m_animPos > 1.0)
		m_animPos = 0.0;

	Refresh(); // triggers repaint
}

void FinanceGraphPanel::refreshData(const tableRowVector& stringValues)
{
	if (stringValues.empty())
		return;
	graphInfo.xAxisLabels.clear();
	graphInfo.values.clear();
	for (const tableRow& data : stringValues)
	{
		graphInfo.xAxisLabels.emplace_back(data[0]);
		graphInfo.values.emplace_back(std::stod(data[1]));
	}

	// Find min/max
	auto [minIt, maxIt] = std::minmax_element(graphInfo.values.begin(), graphInfo.values.end());
	graphInfo.maxValue = *maxIt;
	graphInfo.minValue = *minIt;

	Refresh();
}

} /* namespace marvus */
