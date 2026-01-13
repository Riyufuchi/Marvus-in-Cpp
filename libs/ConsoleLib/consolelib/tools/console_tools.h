//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : Oct 27, 2021
// Last Edit   : Dec 23, 2025
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
	IConsole* createPlatformConsole();
	bool repeat();
	bool waitForEnter();
	bool yesNo(const char* text);
	int getIntSafe();
	int getIntSafe(int min, int max);
	std::optional<int> obtainInt();
	std::optional<int> obtainInt(int min, int max);
	template <typename T>
	std::optional<T> getInput()
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
	int basicMenu(int lenght, const char* menu[]);
	int basicMenu(std::vector<const char*>& menu);
	int basicMenu(std::vector<std::string>& menu, IConsole& console);
	void createManual(std::string* args, int lenght);
	std::string createTable(std::string* args, int lenght);
	void listFilesInFolder(const std::string& workspacePath = "");
}
#endif
