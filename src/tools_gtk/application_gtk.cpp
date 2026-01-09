//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-07
// Last edit  : 2026-01-07
// Copyright  : Copyright (c) 2026, riyufuchi
// Project    : %PROJECT%
//==============================================================================
#include "application_gtk.h"

namespace gtk
{

ApplicationGTK::ApplicationGTK(const std::string& app_id, const std::string& window_title) : window_title(window_title), application_id(app_id), application(nullptr), window(nullptr)
{
	this->application = gtk_application_new(application_id.c_str(), G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(application, "activate", G_CALLBACK(ApplicationGTK::on_activate), this);
}

void ApplicationGTK::on_activate(GtkApplication* app, gpointer user_data)
{
	auto* self = static_cast<ApplicationGTK*>(user_data);
	// Now you are back in C++ land
	self->create_window(app);
}

bool ApplicationGTK::analyze_arguments(int, char**)
{
	return false;
}

void ApplicationGTK::configure()
{
}

int ApplicationGTK::run_application(int argc, char** argv)
{
	int status = g_application_run(G_APPLICATION(application), argc, argv);
	g_object_unref(application);
	return status;
}

// Setters
void ApplicationGTK::set_window_title(const std::string& title)
{
	window_title = title;
	gtk_window_set_title(GTK_WINDOW(window), window_title.c_str());
}
// Getters
const std::string& ApplicationGTK::get_window_title() const
{
	return window_title;
}

}
