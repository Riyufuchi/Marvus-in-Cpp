//============================================================================
// Name        : IConsole
// Author      : Riyufuchi
// Created on  : Oct 13, 2023
// Last Edit   : Jan 13, 2026
// Description : This a base class Classes working with console
//============================================================================

#ifndef SRC_INC_ICONSOLE_HPP_
#define SRC_INC_ICONSOLE_HPP_

#include <iostream>
#include <string>

#include "../tools/color_tools.h"

namespace consolelib
{
class IConsole
{
public:
	virtual ~IConsole() = default;
	// Procedures
	virtual void disable_custom_fg() const = 0;
	virtual void enable_custom_fg() const = 0;
	virtual void enable_custom_fg(const Color& color) const = 0;
	virtual void enable_custom_bg(const Color& color) const = 0;
	virtual void disable_custom_bg() const = 0;
	// Output methods
	virtual void out(const std::string& text) const = 0;
	virtual void out_highlighted(const std::string& text) const = 0;
	virtual void out(const Color& color, const std::string& text) const = 0;
	virtual void out(short int r, short int g, short int b, const std::string& text) const = 0;
	virtual void err(const std::string& text) const = 0;
	virtual void err(const Color& color, const std::string& text) const = 0;
	virtual void err(short int r, short int g, short int b, const std::string& text) const = 0;
	// Setters
	virtual void set_default_fg_color(Color color) = 0;
	// Getters
	virtual Color get_default_fg_color() const
	{
		return Color{211, 215, 207};
	}
};
}
#endif /* CONSOLEUTILS_ICONSOLE_HPP_ */
