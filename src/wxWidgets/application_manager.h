//==============================================================================
// File       : ManagerApp.h
// Author     : riyufuchi
// Created on : Mar 31, 2025
// Last edit  : Dec 04, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUSTWO_HPP
#define MARVUSTWO_HPP

#include <wx/wx.h>

#include "ArgumentParser.h"

#include "main_frame.h"

namespace wxtools
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
		~ManagerApp();
		virtual bool OnInit() override;
};
}
#endif /* MARVUSTWO_HPP */ 
