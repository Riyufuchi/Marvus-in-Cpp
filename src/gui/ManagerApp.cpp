//==============================================================================
// File       : ManagerApp.cpp
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 04, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "ManagerApp.h"

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
	this->frame = new MainFrame("Marvus in C++", args);
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
