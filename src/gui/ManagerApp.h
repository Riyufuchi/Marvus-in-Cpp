//==============================================================================
// File       : ManagerApp.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUSTWO_HPP
#define MARVUSTWO_HPP

#include <wx/wx.h>

#include "MainFrame.h"
#include "ArgumentParser.h"

namespace wxw
{
class ManagerApp : public wxApp
{
	private:
		MainFrame* frame;
		bool areArgs;
		std::string text;
		consolelib::argVector args;
	public:
		ManagerApp();
		ManagerApp(int argc, char** argv);
		~ManagerApp();
		virtual bool OnInit() override;
};
}
#endif /* MARVUSTWO_HPP */ 
