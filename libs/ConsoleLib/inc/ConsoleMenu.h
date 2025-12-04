//==============================================================================
// File       : ConsoleCallbackMenu.h
// Author     : riyufuchi
// Created on : Mar 15, 2025
// Last edit  : Apr 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_CONSOLEUTILS_CONSOLEMENU_H_
#define SRC_CONSOLEUTILS_CONSOLEMENU_H_

#include <utility>
#ifdef _WIN32
	#include <conio.h>  // For _kbhit() and _getch() on Windows
#else
	#include <unistd.h>
	#include <termios.h>
	#include <stdio.h>
#endif

#include <vector>
#include <functional>

#include "IConsole.hpp"

#define CLEAR_SCREEN "\x1B[3J\x1B[H\x1B[2J"

namespace consolelib
{
class ConsoleMenu
{
private:
	IConsole& console;
	std::vector<std::string>& menu;
	std::function<void()> printHeader;
	bool runMenu;
	size_t highlightedOptionID;
	char key;
	void clearConsole();
	void printMenu();
	char getch();
	void flushInputBuffer();
public:
	ConsoleMenu(IConsole& console, std::vector<std::string>& menu, std::function<void()> printHeader);
	virtual ~ConsoleMenu();
	void exitMenuLoop();
	int runMenuLoop();
	void disableLineBuffering();
	void enableLineBuffering();
};

} /* namespace consoleart */

#endif /* SRC_CONSOLEUTILS_CONSOLEMENU_H_ */
