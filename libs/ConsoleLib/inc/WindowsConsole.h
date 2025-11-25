//============================================================================
// Name        : WindowsConsole
// Author      : Riyufuchi
// Created on  : Feb 28, 2024
// Last Edit   : Mar 31, 2025
//============================================================================

#ifdef _WIN32
#ifndef _WINDOWS_CONSOLE_H_
#define _WINDOWS_CONSOLE_H_

#include <iostream>
#include <windows.h>
#include <io.h>

#include "UnixConsole.h"

namespace ConsoleLib
{
class WindowsConsole : public UnixConsole
{
	public:
		WindowsConsole();
		~WindowsConsole();
		enableVirtualTerminalProcessing();
	};
}
#endif
#endif
