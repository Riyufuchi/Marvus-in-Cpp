//==============================================================================
// File       : DefaultConsole.h
// Author     : Riyufuchi
// Created on : Feb 19, 2024
// Last edit  : Jan 13, 2026
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_DEFAULTCONSOLE_H_
#define SRC_INC_DEFAULTCONSOLE_H_

#include <iostream>
#include <sstream>

#include "iconsole.hpp"

namespace consolelib
{
class DefaultConsole : public IConsole
{
private:
public:
	DefaultConsole();
	~DefaultConsole();
	virtual void disable_custom_fg() const override;
	virtual void enable_custom_fg() const override;
	virtual void disable_custom_bg() const override;
	virtual void enable_custom_bg(const Color& color) const override;
	// Setters
	virtual void set_default_fg_color([[maybe_unused]] Color color) override;
	virtual void enable_custom_fg([[maybe_unused]] const Color& color) const override;
	// Write methods
	virtual void out(const std::string& text) const override;
	virtual void out_highlighted(const std::string& text) const override;
	virtual void out(const Color& color, const std::string& text) const override;
	virtual void out(short int r, short int g, short int b, const std::string& text) const override;
	virtual void err(const std::string& text) const override;
	virtual void err(const Color& color, const std::string& text) const override;
	virtual void err(short int r, short int g, short int b, const std::string& text) const override;
};
}
#endif /* SRC_INC_DEFAULTCONSOLE_H_ */
