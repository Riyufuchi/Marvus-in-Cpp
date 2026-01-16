//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-12
// Last edit  : 2026-01-12
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MARVUS_ICON_HELPER_HPP
#define MARVUS_ICON_HELPER_HPP

#include <gio/gio.h>
#include <gtk/gtk.h>

#ifdef _WIN32
#include <windows.h>
#endif

extern "C"
{
GResource* marvus_get_resource(void);
}

namespace marvus
{

inline void update_icon_to_custom(GtkWidget* window)
{
	GtkIconTheme* theme = gtk_icon_theme_get_for_display(gdk_display_get_default());
	gtk_icon_theme_add_resource_path(theme, "/com/riyufuchi/marvus/icons/hicolor/48x48/apps");

	gtk_window_set_default_icon_name("marvus");
	gtk_window_set_icon_name(GTK_WINDOW(window), "marvus");

	// Debug
	//GtkWidget* img = gtk_image_new_from_icon_name("marvus");
	//gtk_window_set_child(GTK_WINDOW(window), img);
}
#ifdef _WIN32
inline void set_window_icon(HWND hwnd)
{
	HICON hIcon = (HICON) LoadImage(GetModuleHandle(nullptr), "assets/marvus.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	if (hIcon)
	{
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}
}
#endif

}

#endif // MARVUS_ICON_HELPER_HPP
