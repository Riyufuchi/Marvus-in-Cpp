//==============================================================================
// File       : Statistics.h
// Author     : riyufuchi
// Created on : Jan 14, 2025
// Last edit  : Nov 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLELIB_STATISTICSGENERIC_H_
#define CONSOLELIB_STATISTICSGENERIC_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric> // For std::accumulate

namespace consolelib
{
template <typename T>
class Statistic
{
private:
	std::vector<T> data; // Store the dataset
	void sortData();
public:
	Statistic(); // Creates empty vector
	Statistic(const std::vector<T>& dataset);
	~Statistic();
	void addValue(T value);
	void addValues(const std::vector<T>& values); // Add multiple values
	T mean() const; // Calculate the mean (average) or expected value E(X) in this context
	T median(); // Calculate the median (middle value)
	T variance(bool sampleVarinace) const; // Calculate the variance (not standardized)
	T varianceWelford(bool sampleVarinace) const; // Calculate the variance using Welford's method (not standardized)
	T stadardizeVarX(T variance2) const; // Just square root, for better code readability
	std::vector<T> mode() const; // Calculate the mode (most frequent value)
	std::vector<std::pair<std::string, T>> calculateStatistics(bool sampleData);
};
}
#include "Statistic.tpp"
#endif
