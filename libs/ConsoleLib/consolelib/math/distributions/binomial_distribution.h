//==============================================================================
// File       : BinomalDistribution.h
// Author     : riyufuchi
// Created on : Oct 22, 2024
// Last edit  : Jan 13, 2026
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLELIB_BINOMIALDISTRIBUTION_H_
#define CONSOLELIB_BINOMIALDISTRIBUTION_H_

#include "../base/distribution.h"

namespace consolelib
{
class BinomialDistribution : public Distribution
{
private:
	int n; // n from binomial distribution formula
	bigDouble p; // chance
public:
	BinomialDistribution();
	BinomialDistribution(int n, bigDouble p);
	~BinomialDistribution();
	u_bigInt partial_factorial(int number, int steps);
	u_bigInt combination_number(int n, int k);
	bigDouble distribute(int k) override; // Not normalized to %
	bigDouble distribute(int k, bigDouble p, int n);
	// Overrides
	bigDouble ex() override;
	bigDouble varX() override;
	// Setters
	void set_P(bigDouble p);
	void set_N(int n);
	// Getters
	bigDouble get_P() const;
	int get_N() const;
};
}
#endif
