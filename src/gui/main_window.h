//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-08
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define BOOST_ALL_NO_LIB

#include "../tools_gtk/application_gtk.h"
#include "../tools_gtk/menu_bar_builder.h"
#include "../tools_gtk/grid_view_simple_gtk.h"
#ifdef GDK_WINDOWING_WIN32
#include <gdk/win32/gdkwin32.h>
#endif
// Local - Marvus
#include "../marvus/base/controller.h"
#include "marvus_icon_helper.hpp"
// ConsoleLib
#include "consolelib/tools/time_tools.h"

namespace marvus
{
class MainWindow : public gtk::ApplicationGTK
{
private:
	Controller controller;
	gtk::GridViewSimpleGtk* main_grid_view;
	GtkWidget* dropdown_month_filter;
	GtkWidget* check_month_filter;
	void create_menu_bar(GtkApplication* app);
	void create_tool_bar(GtkWidget* root_box);
	void create_notebook(GtkWidget* root_box);
	// Menu bar events
	void fill_data_grid_view_event();
	// Tools
	void show_error_dialog(const std::string& error_message, const std::string& error_title = "Marvus error");
public:
	MainWindow();
	// ApplicationGTK interface
protected:
	virtual void create_window(GtkApplication *app) override;
};
}

#endif // MAIN_WINDOW_H
