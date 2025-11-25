//==============================================================================
// File       : Output.hpp
// Author     : riyufuchi
// Created on : Nov 24, 2025
// Last edit  : Nov 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleLib
//==============================================================================

#ifndef SRC_INC_OUTPUT_HPP_
#define SRC_INC_OUTPUT_HPP_

#include <iostream>
#include <vector>
#include <iomanip> // std::setprecision

#include "IConsole.hpp"

namespace ConsoleLib
{
class Output
{
public:
	static void configStream(int precision)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(precision);
	}
	template <typename K, typename T>
	static void printResults(const std::vector<std::pair<K, T>>& data)
	{
		for (const std::pair<K, T>& dataPair : data)
			std::cout << dataPair.first << " " << dataPair.second << "\n";
		std::cout << "\n";
	}
	template <typename K, typename T>
	static void printResults(const std::vector<std::pair<K, T>>& data, const IConsole& console)
	{
		std::ostringstream stringStream;
		for (const std::pair<K, T>& dataPair : data)
		{
			stringStream << dataPair.first << " "  << dataPair.second << "\n";
		}
		stringStream << "\n";
		console.out(stringStream.str());
	}
};
}
#endif /* SRC_INC_OUTPUT_HPP_ */
