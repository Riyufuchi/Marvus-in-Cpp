//==============================================================================
// File       : MainSource.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "gui/ManagerApp.h"

//wxIMPLEMENT_APP(keo::ManagerApp);

int main(int argc, char** argv)
{
	wxApp::SetInstance(new keo::ManagerApp(argc, argv));
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
}


