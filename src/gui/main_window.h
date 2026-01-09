//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-08
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../tools_gtk/application_gtk.h"
#include "../tools_gtk/menu_bar_builder.h"
// Local - Marvus
#include "../marvus/base/controller.h"

namespace marvus
{
class MainWindow : public gtk::ApplicationGTK
{
private:
	Controller controller;
	void create_menu_bar(GtkApplication* app);
	// Menu bar events
	static void on_quit_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data);
public:
	MainWindow();
	// ApplicationGTK interface
protected:
	virtual void create_window(GtkApplication *app) override;
};
}

#endif // MAIN_WINDOW_H
