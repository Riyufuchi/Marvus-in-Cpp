//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-09
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MENU_BAR_BUILDER_H
#define MENU_BAR_BUILDER_H

#include <gtk/gtk.h>
#include <gtk/gtkmenubutton.h>

namespace gtk
{
class MenuBarBuilder
{
private:
	GMenu* menu;
public:
	MenuBarBuilder();
	~MenuBarBuilder();
	//
	MenuBarBuilder& operator=(MenuBarBuilder&) = delete;
	MenuBarBuilder& operator=(MenuBarBuilder&&) = delete;
	//
	MenuBarBuilder& add_item(const char* label, const char* action);
	MenuBarBuilder& add_submenu(const char* label, MenuBarBuilder& sub);
	MenuBarBuilder& add_section(MenuBarBuilder& section);
	//
	GMenu* build();
};
}
#endif // MENU_BAR_BUILDER_H
