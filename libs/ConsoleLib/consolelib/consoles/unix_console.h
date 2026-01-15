//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : Jul 20, 2020
// Last Edit   : Jan 13, 2026
// Description : This class contains methods for working with a Linux console
//============================================================================

#ifndef _UNIXCONSOLE_H_
#define _UNIXCONSOLE_H_

#include <iostream>
#include <sstream>

#include "iconsole.hpp"

#define HIGHLIGHT "\x1B[7m"
#define RESET "\x1B[0m"

namespace consolelib
{
class UnixConsole : public IConsole
{
private:
	Color defaultColor;
	std::string defColorEscCode;
public:
	UnixConsole();
	~UnixConsole();
	virtual void disable_custom_fg() const override;
	virtual void enable_custom_fg() const override;
	virtual void disable_custom_bg() const override;
	// Out methods
	virtual void out(const std::string& text) const override;
	virtual void out_highlighted(const std::string& text) const override;
	virtual void out(const Color& color, const std::string& text) const override;
	virtual void out(short int r, short int g, short int b, const std::string& text) const override;
	virtual void err(const std::string& text) const override;
	virtual void err(const Color& color, const std::string& text) const override;
	virtual void err(short int r, short int g, short int b, const std::string& text) const override;
	// Setters
	virtual void set_default_fg_color(Color color) override;
	virtual void enable_custom_fg(const Color& color) const override;
	virtual void enable_custom_bg(const Color& color) const override;
	// Getters
	virtual Color get_default_fg_color() const override;
};
}
#endif
