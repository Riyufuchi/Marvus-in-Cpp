//==============================================================================
// File       : ManagerApp.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "ManagerApp.h"

namespace wxw
{
ManagerApp::ManagerApp(int argc, char** argv) : wxApp(), frame(nullptr), areArgs(false)
{
	this->args = consolelib::ArgumentParser::analyzeInOrder(argc, argv, areArgs, text);
}

ManagerApp::~ManagerApp()
{
}

bool ManagerApp::OnInit()
{
	if (!areArgs)
		return false;
	this->frame = new MainFrame("Marvus in C++", args);
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
