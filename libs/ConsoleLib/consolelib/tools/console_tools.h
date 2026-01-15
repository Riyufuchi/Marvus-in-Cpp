//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : Oct 27, 2021
// Last Edit   : Jan 13, 2026
//============================================================================

#ifndef _CONSOLE_UTILITY_H_
#define _CONSOLE_UTILITY_H_

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <format>
#include <limits>

#include "../consoles.hpp"

/**
 * These functions helps with console interactions
 */
namespace consolelib::console_tools
{
	IConsole* new_platform_console();
	bool repeat();
	bool wait_for_enter();
	bool yes_no(const char* text);
	int get_int_safe();
	int get_int_safe(int min, int max);
	std::optional<int> obtain_int();
	std::optional<int> obtain_int(int min, int max);
	template <typename T>
	std::optional<T> get_input()
	{
		std::string line;
		if (!std::getline(std::cin, line))
			return std::nullopt; // EOF or error

		T value;
		std::stringstream ss(line);
		// Try to parse and ensure no leftovers remain
		if (ss >> value && ss.eof())
			return value;

		return std::nullopt;
	}
	void header(const std::string& text);
	void header(const std::string& text, IConsole& console);
	int basic_menu(int lenght, const char* menu[]);
	int basic_menu(std::vector<const char*>& menu);
	int basic_menu(std::vector<std::string>& menu, IConsole& console);
	void create_manual(std::string* args, int lenght);
	std::string create_table(std::string* args, int lenght);
	void list_files_in_folder(const std::string& workspacePath = "");
}
#endif
