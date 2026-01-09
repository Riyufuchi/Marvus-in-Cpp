//==============================================================================
// File       : MainSource.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "gui/main_window.h"

int main(int argc, char** argv)
{
	marvus::MainWindow main_window;
	if (main_window.analyze_arguments(argc, argv))
		main_window.configure();
	return main_window.run_application(argc, argv);
}




