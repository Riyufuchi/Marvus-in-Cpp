//==============================================================================
// File       : MainSource.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "gui/main_window.h"
#include "gui/marvus_config.hpp"

int main(int argc, char** argv)
{
	marvus::MarvusConfig config = marvus::load_config();
	if (config.dark_mode)
		g_setenv("GTK_THEME", "Adwaita:dark", true);
	marvus::MainWindow main_window;
	if (main_window.analyze_arguments(argc, argv))
		main_window.configure();
	return main_window.run_application(argc, argv);
}




