//==============================================================================
// File       : Delegate.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2025
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: This class mimics C#'s delegate, although C# uses more complex function
// tracking algorithm I will here use simple function pointers
//==============================================================================

#ifndef SRC_INC_DELEGATE_HPP_
#define SRC_INC_DELEGATE_HPP_

#include <vector>
#include <algorithm>

namespace consolelib
{
template <typename K, typename T>
class Delegate
{
private:
	using FuncType = K(*)(T);
	std::vector<FuncType> functions;
public:
	Delegate()
	{}
	~Delegate() = default;

	K operator()(T arg) const
	{
		if (functions.empty())
			throw new std::exception;
		for (size_t i = 0; i < functions.size() - 1; i++)
			functions[i](arg);
		return functions[functions.size() - 1](arg);
	}

	Delegate& operator += (FuncType other)
	{
		if (other)
			functions.emplace_back(other);
		return *this;
	}

	Delegate& operator -= (FuncType other)
	{
		if (other)
			functions.erase(std::remove(functions.begin(), functions.end(), other), functions.end());
		return *this;
	}

	std::vector<K> getInvocationList(T arg)
	{
		std::vector<K> data;
		for (FuncType func : functions)
		{
			data.emplace_back(func(arg));
		}
		return data;
	}

};
}
#endif /* SRC_INC_DELEGATE_HPP_ */
