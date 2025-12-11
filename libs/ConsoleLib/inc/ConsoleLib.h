//==============================================================================
// File       : ConsoleLib.h
// Author     : Riyufuchi
// Created on : Mar 27, 2024
// Last edit  : Nov 17, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _CONSOLE_LIB_LIBRARY_H_
#define _CONSOLE_LIB_LIBRARY_H_

#include <iostream>
#include <string>
#include <format>

#define _VERSION "6.9e"

namespace consolelib
{
class ConsoleLib
{
public:
	static constexpr const char* VERSION = _VERSION;
	ConsoleLib();
	~ConsoleLib();
	static std::string aboutLibrary();
};
} /* namespace consolelib */
#endif /* _CONSOLE_LIB_LIBRARY_H_ */
