//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-15
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MENU_BAR_BUILDER_H
#define MENU_BAR_BUILDER_H

#include <gtk/gtk.h>
#include <gtk/gtkmenubutton.h>
// STL
#include <functional>
#include <string.h>

namespace gtk
{
class MenuBarBuilder
{
private:
	GtkWidget* window;
	GMenu* menu;
	static void action_trampoline(GSimpleAction*, GVariant*, gpointer user_data)
	{
		auto* fn = static_cast<std::function<void()>*>(user_data);
		(*fn)();
	}
public:
	MenuBarBuilder(GtkWidget* window);
	~MenuBarBuilder();
	void bind_action_to_item(const char* name, std::function<void()> fn);
	//
	MenuBarBuilder& operator=(MenuBarBuilder&) = delete;
	MenuBarBuilder& operator=(MenuBarBuilder&&) = delete;
	//
	MenuBarBuilder& add_item(const char* label, const char* action);
	MenuBarBuilder& add_item(const char* label, const char* action, std::function<void()> fn);
	MenuBarBuilder& add_item(const char* label, const char* action, const char* accelerator, std::function<void()> fn);
	MenuBarBuilder& add_submenu(const char* label, MenuBarBuilder& sub);
	MenuBarBuilder& add_section(MenuBarBuilder& section);
	//
	GMenu* build();
};
}
#endif // MENU_BAR_BUILDER_H
