//==============================================================================
// File       : DefaultConsole.h
// Author     : Riyufuchi
// Created on : Feb 19, 2024
// Last edit  : Nov 24, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef SRC_INC_DEFAULTCONSOLE_H_
#define SRC_INC_DEFAULTCONSOLE_H_

#include <iostream>
#include <sstream>

#include "IConsole.hpp"

namespace consolelib
{
class DefaultConsole : public IConsole
{
private:
public:
	DefaultConsole();
	~DefaultConsole();
	virtual void disableCustomFG() const override;
	virtual void enableCustomFG() const override;
	virtual void disableCustomBG() const override;
	virtual void enableCustomBG(const Color& color) const override;
	// Setters
	virtual void setDefaultTextColor([[maybe_unused]] Color color) override;
	virtual void enableCustomFG([[maybe_unused]] const Color& color) const override;
	// Write methods
	virtual void out(const std::string& text) const override;
	virtual void outHighlighted(const std::string& text) const override;
	virtual void out(const Color& color, const std::string& text) const override;
	virtual void out(short int r, short int g, short int b, const std::string& text) const override;
	virtual void err(const std::string& text) const override;
	virtual void err(const Color& color, const std::string& text) const override;
	virtual void err(short int r, short int g, short int b, const std::string& text) const override;
};
}
#endif /* SRC_INC_DEFAULTCONSOLE_H_ */
