//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : Oct 27, 2021
// Last Edit   : Nov 09, 2025
//============================================================================

#ifndef _CONSOLE_UTILITY_H_
#define _CONSOLE_UTILITY_H_

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <format>

#include "IConsole.hpp"
#include "UnixConsole.h"
#include "DefaultConsole.h"

#ifdef _WIN32
	#include "WindowsConsole.h"
#endif

/**
 * This class helps with console interactions
 */
namespace ConsoleLib
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
	template <typename T> static T getInput()
	{
		T x;
		while(true)
		{
			std::cin >> x;
			std::cin.get();
			if (!std::cin.fail())
				break;
			std::cerr << "Bad input.\n";
			std::cout << "Input again: ";
			std::cin.clear();
			std::cin.ignore(10,'\n');
		}
		return x;
	}
	static void header(std::string);
	static void header(std::string text, IConsole& console);
	[[deprecated("Redundant color attribute")]]
	static void header(std::string text, IConsole& console, Color textColor);
	static int basicMenu(int lenght, const char* menu[]);
	static int basicMenu(std::vector<const char*>& menu);
	static int basicMenu(std::vector<std::string>& menu, IConsole& console);
	static void createManual(std::string* args, int lenght);
	static std::string createTable(std::string* args, int lenght);
	static void listFilesInFolder(std::string workspacePath);
};
}
#endif
