//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-15
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "menu_bar_builder.h"

namespace gtk
{
MenuBarBuilder::MenuBarBuilder(GtkWidget* window) : window(window), menu(g_menu_new())
{}

MenuBarBuilder::~MenuBarBuilder()
{
	if (menu)
		g_object_unref(menu);
}

void MenuBarBuilder::bind_action_to_item(const char* name, std::function<void()> fn)
{
	auto* action = g_simple_action_new(name, nullptr);

	auto* heap_fn = new std::function<void()>(std::move(fn));

	g_signal_connect(action, "activate", G_CALLBACK(action_trampoline), heap_fn);

	// cleanup when action is destroyed
	g_object_set_data_full(G_OBJECT(action), "cpp-fn", heap_fn, [](gpointer p)
	{
		delete static_cast<std::function<void()>*>(p);
	});

	g_action_map_add_action(G_ACTION_MAP(window), G_ACTION(action));
}

MenuBarBuilder& MenuBarBuilder::add_item(const char* label, const char* action)
{
	g_menu_append(menu, label, action);
	return *this;
}

MenuBarBuilder& MenuBarBuilder::add_item(const char* label, const char* action, std::function<void()> fn)
{
	return add_item(label, action, nullptr, fn);
}

MenuBarBuilder& MenuBarBuilder::add_item(const char* label, const char* action, const char* accelerator, std::function<void()> fn)
{
	g_menu_append(menu, label, action);
	const char* action_name = strrchr(action, '.');
	if (action_name)
		bind_action_to_item(action_name + 1, fn);
	if (accelerator)
	{
		const char* const accelerators[] = { accelerator, nullptr };
		gtk_application_set_accels_for_action(gtk_window_get_application(GTK_WINDOW(window)), action, accelerators);
	}
	return *this;
}

MenuBarBuilder& MenuBarBuilder::add_submenu(const char* label, MenuBarBuilder& sub)
{
	g_menu_append_submenu(menu, label, G_MENU_MODEL(sub.build()));
	return *this;
}

MenuBarBuilder& MenuBarBuilder::add_section(MenuBarBuilder& section)
{
	g_menu_append_section(menu, nullptr, G_MENU_MODEL(section.build()));
	return *this;
}

GMenu* MenuBarBuilder::build()
{
	return g_steal_pointer(&menu);
}
}
