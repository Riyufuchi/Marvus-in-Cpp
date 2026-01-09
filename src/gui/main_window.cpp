//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-09
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"

namespace marvus
{

marvus::MainWindow::MainWindow() : gtk::ApplicationGTK("com.riyufuchi.marvus")
{}

void MainWindow::on_quit_activated(GSimpleAction*, GVariant*, gpointer user_data)
{
	g_application_quit(G_APPLICATION(user_data));
}

void MainWindow::create_menu_bar(GtkApplication* app)
{
	gtk::MenuBarBuilder file_menu_section_1;
	file_menu_section_1
		.add_item("New", "app.new")
		.add_item("Open", "app.open")
		.add_item("Import", "app.open")
		.add_item("Open", "app.open");

	gtk::MenuBarBuilder file_menu_section_2;
	file_menu_section_2.add_item("Exit", "app.exit");

	gtk::MenuBarBuilder file_menu;
	file_menu.add_section(file_menu_section_1);
	file_menu.add_section(file_menu_section_2);

	gtk::MenuBarBuilder payment_menu;
	payment_menu.add_item("Add Payment", "app.add_payment");

	gtk::MenuBarBuilder overview_menu;
	overview_menu.add_item("Year Summary", "app.year_summary");

	gtk::MenuBarBuilder help_menu;
	help_menu.add_item("About", "app.about");

	gtk::MenuBarBuilder menu_bar;
	menu_bar.add_submenu("File", file_menu);
	menu_bar.add_submenu("Payment", payment_menu);
	menu_bar.add_submenu("Overview summary", overview_menu);
	menu_bar.add_submenu("Help", help_menu);

	gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menu_bar.build()));
	gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

	GSimpleAction* quit_action = g_simple_action_new("exit", NULL);
	g_signal_connect(quit_action, "activate", G_CALLBACK(MainWindow::on_quit_activated), app);
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
}

void MainWindow::create_window(GtkApplication* app)
{
	// Main window
	window = gtk_application_window_new(app);
	set_window_title(std::string(_MARVUS_VERSION));
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	// Other UI
	create_menu_bar(app);
	// Finalize
	gtk_window_present(GTK_WINDOW(window));
}

}

