//==============================================================================
// File       : main.cpp
// Author     : riyufuchi
// Created on : Sep 18, 2025
// Last edit  : Sep 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "gui/MarvusApp.h"

int main(int argc, char** argv)
{
	wxApp::SetInstance(new riyufuchi::MarvusApp(argc, argv));
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
}
