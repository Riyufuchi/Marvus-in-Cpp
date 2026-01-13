//==============================================================================
// File       : ConsoleLib.h
// Author     : Riyufuchi
// Created on : Dec 22, 2025
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _CONSOLES_HPP_
#define _CONSOLES_HPP_

#include "consoles/iconsole.hpp"
#include "consoles/default_console.h"
#include "consoles/unix_console.h"
#ifdef _WIN32
	#include "consoles/windows_console.h"
#endif

#endif 
