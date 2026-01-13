//==============================================================================
// File       : PoissonsDistribution.h
// Author     : riyufuchi
// Created on : Nov 01, 2024
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef OTHER_POISSONSDISTRIBUTION_H_
#define OTHER_POISSONSDISTRIBUTION_H_

#include "../base/distribution.h"

namespace consolelib
{
class PoissonsDistribution : public Distribution
{
private:
	int lambda; //λ;
public:
	PoissonsDistribution(int lambda);
	~PoissonsDistribution();
	virtual bigDouble distribute(int k) override;
	virtual bigDouble ex() override;
	virtual bigDouble varX() override;
};
}
#endif
