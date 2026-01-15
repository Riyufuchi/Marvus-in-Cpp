//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-11
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"

namespace marvus
{

marvus::MainWindow::MainWindow() : gtk::ApplicationGTK("com.riyufuchi.marvus"), controller([&](const std::string& message, const std::string& title) { show_error_dialog(message, title); })
{
	this->main_grid_view = nullptr;
	controller.load_and_init_database();
}

void MainWindow::fill_data_grid_view_event()
{
	main_grid_view->clear_grid_view();
	tableHeaderAndData data;
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(check_month_filter)))
		data = controller.obtain_data_from_view(marvus::TableView::PAYMENTS_VIEW_FOR_MONTH, { std::format("{:02}", gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown_month_filter)) + 1) });
	else
		data = controller.obtain_data_from_view(marvus::TableView::PAYMENTS_VIEW);
	main_grid_view->add_columns(data.first);
	main_grid_view->add_rows(data.second);
}

void MainWindow::on_quit_activated(GSimpleAction*, GVariant*, gpointer user_data)
{
	g_application_quit(G_APPLICATION(user_data));
}

void MainWindow::on_update_grid_view(GSimpleAction*, GVariant*, gpointer user_data)
{
	MainWindow* window = static_cast<MainWindow*>(user_data);
	window->fill_data_grid_view_event();
}

void MainWindow::create_menu_bar(GtkApplication* app)
{
	gtk::MenuBarBuilder file_menu_section_1;
	file_menu_section_1
		.add_item("New", "app.new")
		.add_item("Open", "app.open")
		.add_item("Import", "app.import")
		.add_item("Export", "app.export");

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

void MainWindow::create_tool_bar(GtkWidget* root_box)
{
	gtk_window_set_child(GTK_WINDOW(window), root_box);

	GtkWidget* action_bar = gtk_action_bar_new();
	gtk_box_append(GTK_BOX(root_box), action_bar);

	check_month_filter = gtk_check_button_new_with_label("Month filter");

	g_signal_connect(check_month_filter, "toggled", G_CALLBACK(+[](GtkToggleButton*, gpointer user_data)
	{
		MainWindow* window = static_cast<MainWindow*>(user_data);
		window->fill_data_grid_view_event();
	}), this);

	const char* items[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "November", "December", nullptr };
	GtkStringList* model = gtk_string_list_new(items);

	dropdown_month_filter = gtk_drop_down_new(G_LIST_MODEL(model), nullptr);

	g_signal_connect(dropdown_month_filter, "notify::selected", G_CALLBACK(MainWindow::on_update_grid_view), this);

	gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown_month_filter), 0);

	gtk_action_bar_pack_start(GTK_ACTION_BAR(action_bar), check_month_filter);
	gtk_action_bar_pack_start(GTK_ACTION_BAR(action_bar), dropdown_month_filter);
}

void MainWindow::create_notebook(GtkWidget* root_box)
{
	GtkWidget* notebook = gtk_notebook_new();
	gtk_box_append(GTK_BOX(root_box), notebook);

	GtkWidget* tab_label = gtk_label_new("Data");
	GtkWidget* tab_content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

	main_grid_view = new gtk::GridViewSimpleGtk();
	gtk_widget_set_hexpand(main_grid_view->get_widget(), TRUE);
	gtk_widget_set_vexpand(main_grid_view->get_widget(), TRUE);
	gtk_box_append(GTK_BOX(tab_content), main_grid_view->get_widget());

	GtkWidget* tab_label_graph = gtk_label_new("Graph");
	GtkWidget* tab_graph = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab_content, tab_label);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab_graph, tab_label_graph);
}

void MainWindow::create_window(GtkApplication* app)
{
	g_resources_register(marvus_get_resource());
	// Main window
	window = gtk_application_window_new(app);
	set_window_title(std::string(_MARVUS_VERSION));
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

	update_icon_to_custom(window);

	// Other UI
	create_menu_bar(app);
	GtkWidget* root_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	create_tool_bar(root_box);
	create_notebook(root_box);
	// Finalize
	gtk_window_present(GTK_WINDOW(window));
}

void MainWindow::show_error_dialog(const std::string& error_message, const std::string& error_title)
{
	GtkAlertDialog* dialog = gtk_alert_dialog_new("%s", error_title.c_str());

	gtk_alert_dialog_set_detail(dialog, error_message.c_str());
	gtk_alert_dialog_set_modal(dialog, TRUE);
	gtk_alert_dialog_show(dialog, GTK_WINDOW(window));

	g_object_unref(dialog);
}

}

