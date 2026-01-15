//==============================================================================
// File       : ConsoleLib.h
// Author     : Riyufuchi
// Created on : Mar 27, 2024
// Last edit  : Jan 13, 2026
// Copyright  : Copyright (c) Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _CONSOLE_LIB_LIBRARY_H_
#define _CONSOLE_LIB_LIBRARY_H_

#include <iostream>
#include <string>
#include <format>

namespace consolelib
{
inline constexpr const char* VERSION = "7.3";
inline constexpr const char* COPYRIGHT_HEADER = "Riyufuchi (c) 2023 - 2026";
std::string aboutLibrary();
}
#endif
