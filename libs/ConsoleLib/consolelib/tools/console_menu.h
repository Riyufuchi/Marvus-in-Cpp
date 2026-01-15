//==============================================================================
// File       : ConsoleCallbackMenu.h
// Author     : riyufuchi
// Created on : Mar 15, 2025
// Last edit  : Jan 13, 2026
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

#include "../consoles/iconsole.hpp"

#define CLEAR_SCREEN "\x1B[3J\x1B[H\x1B[2J"

namespace consolelib
{
class ConsoleMenu
{
private:
	enum class KeyType
	{
		UNKNOWN,
		ENTER,
		ARROW_UP,
		ARROW_DOWN
	};
	IConsole& console;
	std::vector<std::string>& menu;
	std::function<void()> print_header_function;
	bool run_menu;
	size_t highlighted_option_id;
	unsigned char key;
	void clear_console();
	void print_menu();
	char getch();
	void flush_input_buffer();
	KeyType obtain_key_type();
public:
	ConsoleMenu(IConsole& console, std::vector<std::string>& menu, std::function<void()> print_header_function);
	virtual ~ConsoleMenu();
	void exit_menu_loop();
	int run_menu_loop();
	void disable_line_buffering();
	void enable_line_buffering();
};

} /* namespace consoleart */

#endif /* SRC_CONSOLEUTILS_CONSOLEMENU_H_ */
