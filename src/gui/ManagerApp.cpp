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

#ifdef _WIN32
void SetCustomWindowsTheme()
{
	wxColour bg(64, 64, 64);                 // DEFAULT_PANE_BACKGROUND
	wxColour fg(192, 192, 192);              // LIGHT_LABEL
	wxColour buttonBg(214, 217, 223);        // DEFAULT_BUTTON_BACKGROUND
	wxColour buttonHighlight(75, 75, 78);    // Darker for button highlights
	wxColour buttonShadow(30, 30, 33);       // Shadow color
	wxColour highlight(255, 105, 180);       // FOCUS / selection pink
	wxColour highlightText(255, 255, 255);   // Text on highlighted selection

	// Override standard system colors
	wxSystemOptions::SetOption("msw.window.themed", 1);

	wxSystemSettings::SetColour(wxSYS_COLOUR_WINDOW, bg);
	wxSystemSettings::SetColour(wxSYS_COLOUR_WINDOWTEXT, fg);

	wxSystemSettings::SetColour(wxSYS_COLOUR_BTNFACE, buttonBg);
	wxSystemSettings::SetColour(wxSYS_COLOUR_BTNHIGHLIGHT, buttonHighlight);
	wxSystemSettings::SetColour(wxSYS_COLOUR_BTNSHADOW, buttonShadow);

	wxSystemSettings::SetColour(wxSYS_COLOUR_HIGHLIGHT, highlight);
	wxSystemSettings::SetColour(wxSYS_COLOUR_HIGHLIGHTTEXT, highlightText);

	// Optional: override menus and text controls
	wxSystemSettings::SetColour(wxSYS_COLOUR_MENU, bg);
	wxSystemSettings::SetColour(wxSYS_COLOUR_MENUTEXT, fg);

	wxSystemSettings::SetColour(wxSYS_COLOUR_LISTBOX, wxColour(102, 102, 102)); // LIST_BACKGROUND
	wxSystemSettings::SetColour(wxSYS_COLOUR_LISTBOXTEXT, fg);
	//wxSystemSettings::SetColour(wxSYS_COLOUR_LISTBOXHIGHLIGHT, highlight);
	wxSystemSettings::SetColour(wxSYS_COLOUR_LISTBOXHIGHLIGHTTEXT,
			highlightText);

	wxSystemSettings::SetColour(wxSYS_COLOUR_BTNHIGHLIGHT, highlight); // optional for focused button
}
#endif


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
