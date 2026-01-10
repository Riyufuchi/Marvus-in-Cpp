//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-10
// Last edit  : 2026-01-10
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef GRID_VIEW_GTK_H
#define GRID_VIEW_GTK_H

#include <gtk/gtk.h>
#include <gtk/gtkcolumnview.h>
// STL
#include <vector>
#include <string>

namespace gtk
{
class GridViewSimpleGtk
{
private:
	GtkWidget* m_grid;
	GtkWidget* m_scrolled ;
	std::vector<GtkWidget*> m_labels; // Keep track to destroy when clearing
	int m_columns;
public:
	GridViewSimpleGtk();
	virtual ~GridViewSimpleGtk();
	// Clear functions
	void clear_grid_view();
	// Add functions
	void add_columns(const std::vector<std::string>& column_labels);
	void add_rows(const std::vector<std::vector<std::string>>& rows);
	// Widget functions
	GtkWidget* get_widget() const;
};
}
#endif // GRID_VIEW_GTK_H
