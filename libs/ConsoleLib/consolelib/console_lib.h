//==============================================================================
// File       : ConsoleLib.h
// Author     : Riyufuchi
// Created on : Mar 27, 2024
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _CONSOLE_LIB_LIBRARY_H_
#define _CONSOLE_LIB_LIBRARY_H_

#include <iostream>
#include <string>
#include <format>

#define _VERSION "7.1"
#define _COPYRIGHT_HEADER "Riyufuchi (c) 2023 - 2026"

namespace consolelib
{
inline constexpr const char* VERSION = _VERSION;
std::string aboutLibrary();
}
#endif
