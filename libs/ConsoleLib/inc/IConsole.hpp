//============================================================================
// Name        : IConsole
// Author      : Riyufuchi
// Created on  : Oct 13, 2023
// Last Edit   : Nov 24, 2025
// Description : This a base class Classes working with console
//============================================================================

#ifndef SRC_INC_ICONSOLE_HPP_
#define SRC_INC_ICONSOLE_HPP_

#include <iostream>
#include <string>

#include "ColorUtils.h"

namespace consolelib
{
class IConsole
{
public:
	virtual ~IConsole() = default;
	// Procedures
	virtual void disableCustomFG() const = 0;
	virtual void enableCustomFG() const = 0;
	virtual void enableCustomFG(const Color& color) const = 0;
	virtual void enableCustomBG(const Color& color) const = 0;
	virtual void disableCustomBG() const = 0;
	// Output methods
	virtual void out(const std::string& text) const = 0;
	virtual void outHighlighted(const std::string& text) const = 0;
	virtual void out(const Color& color, const std::string& text) const = 0;
	virtual void out(short int r, short int g, short int b, const std::string& text) const = 0;
	virtual void err(const std::string& text) const = 0;
	virtual void err(const Color& color, const std::string& text) const = 0;
	virtual void err(short int r, short int g, short int b, const std::string& text) const = 0;
	// Setters
	virtual void setDefaultTextColor(Color color) = 0;
	// Getters
	virtual Color getDefaultTextColor() const
	{
		return Color{211, 215, 207};
	}
};
}
#endif /* CONSOLEUTILS_ICONSOLE_HPP_ */
