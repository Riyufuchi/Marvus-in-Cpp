//==============================================================================
// File       : FinanceGraphPanel.cpp
// Author     : riyufuchi
// Created on : Dec 13, 2025
// Last edit  : Dec 13, 2025
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

void FinanceGraphPanel::OnPaint(wxPaintEvent& evt)
{
	if (values.empty())
		return;
	wxPaintDC dc(this);
	auto gc = wxGraphicsContext::Create(dc);
	if (!gc)
		return;

	wxSize size = GetClientSize();

	// Background
	gc->SetBrush(*wxBLACK_BRUSH);
	gc->DrawRectangle(0, 0, size.x, size.y);

	// Axes margins
	const int margin = 40;
	const int w = size.x - 2 * margin;
	const int h = size.y - 2 * margin;

	// Find min/max
	auto [minIt, maxIt] = std::minmax_element(values.begin(), values.end());
	double minVal = *minIt;
	double maxVal = *maxIt;

	// Draw line
	gc->SetPen(wxPen(wxColour(0, 200, 255), 2));

	for (size_t i = 1; i < values.size(); ++i)
	{
		double x1 = margin + (i - 1) * w / double(values.size() - 1);
		double y1 = margin + h * (1.0 - (values[i - 1] - minVal) / (maxVal - minVal));

		double x2 = margin + i * w / double(values.size() - 1);
		double y2 = margin + h * (1.0 - (values[i] - minVal) / (maxVal - minVal));

		gc->StrokeLine(x1, y1, x2, y2);
	}

	// Draw animated ball (explained below)
	size_t idx = size_t(m_animPos * (values.size() - 1));
	double x = margin + idx * w / double(values.size() - 1);
	double y = margin + h * (1.0 - (values[idx] - minVal) / (maxVal - minVal));

	gc->SetBrush(*wxRED_BRUSH);
	gc->DrawEllipse(x - 4, y - 4, 8, 8);

	delete gc;
}

void FinanceGraphPanel::OnTimer(wxTimerEvent& evt)
{
	m_animPos += 0.002; // speed
	if (m_animPos > 1.0)
	m_animPos = 0.0;

	Refresh(); // triggers repaint
}

void FinanceGraphPanel::refreshData(Controller& controller)
{
	tableRowVector stringValues = controller.obtainDataFromView(TableView::STAT_DAILY_TOTAL).second;
	if (stringValues.empty())
		return;
	dates.clear();
	values.clear();
	for (const tableRow& data : stringValues)
	{
		dates.emplace_back(data[0]);
		values.emplace_back(std::stod(data[1]));
	}
	Refresh();
}

} /* namespace marvus */
