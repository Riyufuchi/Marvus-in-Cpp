//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : Oct 27, 2021
// Last Edit   : Nov 30, 2025
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

#include "IConsole.hpp"
#include "UnixConsole.h"
#include "DefaultConsole.h"

#ifdef _WIN32
	#include "WindowsConsole.h"
#endif

/**
 * This class helps with console interactions
 */
namespace consolelib
{

class ConsoleUtils
{
public:
	ConsoleUtils();
	~ConsoleUtils();
	static IConsole* createPlatformConsole();
	static bool repeat();
	static bool waitForEnter();
	static bool yesNo(const char* text);
	static int getIntSafe();
	static int getIntSafe(int min, int max);
	static std::optional<int> obtainInt();
	static std::optional<int> obtainInt(int min, int max);
	template <typename T>
	static std::optional<T> getInput()
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
	static void header(const std::string& text);
	static void header(const std::string& text, IConsole& console);
	[[deprecated("Redundant color attribute")]]
	static void header(const std::string& text, IConsole& console, const Color& textColor);
	static int basicMenu(int lenght, const char* menu[]);
	static int basicMenu(std::vector<const char*>& menu);
	static int basicMenu(std::vector<std::string>& menu, IConsole& console);
	static void createManual(std::string* args, int lenght);
	static std::string createTable(std::string* args, int lenght);
	static void listFilesInFolder(const std::string& workspacePath = "");
};
}
#endif
