//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-10
// Last edit  : 2026-01-10
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "grid_view_simple_gtk.h"

namespace gtk
{

GridViewSimpleGtk::GridViewSimpleGtk()
{
	// Create grid
	m_grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(m_grid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(m_grid), 20);

	// Wrap in scrolled window
	m_scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(m_scrolled), m_grid);

	// Make grid visible
	gtk_widget_set_visible(m_grid, TRUE);
	gtk_widget_set_visible(m_scrolled, TRUE);
}

GridViewSimpleGtk::~GridViewSimpleGtk()
{}

void GridViewSimpleGtk::clear_grid_view()
{
	GtkWidget* child = gtk_widget_get_first_child(m_grid);
	GtkWidget* next;
	while (child != nullptr)
	{
		// Store the next sibling BEFORE removing the current child
		next = gtk_widget_get_next_sibling(child);

		// Use gtk_grid_remove to detach the child from the grid
		gtk_grid_remove(GTK_GRID(m_grid), child);

		child = next;
	}
}

void GridViewSimpleGtk::add_columns(const std::vector<std::string>& headers)
{
	m_columns = static_cast<int>(headers.size());

	int col = 0;
	GtkWidget* label;
	for (const auto& h : headers)
	{
		label = gtk_label_new(h.c_str());
		gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
		gtk_grid_attach(GTK_GRID(m_grid), label, col++, 0, 1, 1);
		m_labels.push_back(label);
	}
	gtk_widget_set_visible(m_grid, true);
}

void GridViewSimpleGtk::add_rows(const std::vector<std::vector<std::string>>& rows)
{
	int row_index = 1; // start after header
	int col_index;
	GtkWidget* label;
	for (const auto& row : rows)
	{
		col_index = 0;
		for (const auto& value : row)
		{
			label = gtk_label_new(value.c_str());
			gtk_label_set_xalign(GTK_LABEL(label), 0.0f);
			gtk_grid_attach(GTK_GRID(m_grid), label, col_index++, row_index, 1, 1);
			m_labels.push_back(label);
		}
		row_index++;
	}
	gtk_widget_set_visible(m_grid, true);
}


GtkWidget* GridViewSimpleGtk::get_widget() const
{
	return m_scrolled;
}

}
