//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-08
// Last edit  : 2026-01-08
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "menu_bar_builder.h"

namespace gtk
{
MenuBarBuilder::MenuBarBuilder() : menu(g_menu_new())
{}

MenuBarBuilder::~MenuBarBuilder()
{
	if (menu)
		g_object_unref(menu);
}

MenuBarBuilder& MenuBarBuilder::add_item(const char* label, const char* action)
{
	g_menu_append(menu, label, action);
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
