//==============================================================================
// File       : ManagerApp.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "../wxWidgets/ManagerApp.h"

namespace wxw
{
ManagerApp::ManagerApp() : wxApp(), frame(nullptr), areArgs(false)
{

}

ManagerApp::~ManagerApp()
{
}

bool ManagerApp::OnInit()
{
	this->args = consolelib::ArgumentParser::analyzeInOrder(argc, argv, areArgs, text);
	if (!areArgs)
		return false;
	#ifdef _WIN32
		SetAppearance(wxApp::Appearance::System);
	#endif
	this->frame = new MainFrame(args);
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
