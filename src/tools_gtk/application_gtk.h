//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-07
// Last edit  : 2026-01-07
// Copyright  : Copyright (c) 2026, riyufuchi
// Project    : %PROJECT%
//==============================================================================
#ifndef APPLICATION_GTK_H
#define APPLICATION_GTK_H

#include <string>
// GTK
#include <gtk/gtk.h>
#include <gtk/gtkmenubutton.h>

namespace gtk
{
class ApplicationGTK
{
private:
	std::string window_title;
	const std::string application_id;
	GtkApplication* application;
	static void on_activate(GtkApplication* app, gpointer);
protected:
	GtkWidget* window;
	virtual void create_window(GtkApplication* app) = 0;
public:
	ApplicationGTK(const std::string& app_id, const std::string& window_title = "An GTK 4 application");
	bool analyze_arguments(int argc, char** argv);
	void configure();
	int run_application(int argc, char** argv);
	// Setters
	void set_window_title(const std::string& title);
	// Getters
	const std::string& get_window_title() const;
};
}
#endif // APPLICATION_GTK_H
