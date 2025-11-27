//==============================================================================
// File       : InlineSQL.h
// Author     : riyufuchi
// Created on : Nov 27, 2025
// Last edit  : Nov 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_INLINESQL_H_
#define MARVUS_INLINESQL_H_

#include <string>

namespace marvus
{
class InlineSQL
{
public:
	static inline const std::string ESTABLISHMENTS_VIEW = "SELECT * FROM ESTABLISHMENT_VIEW;";
	static inline const std::string CATEGORIES_VIEW = "SELECT * FROM CATEGORY_VIEW;";
	static inline const std::string PAYMENTS_VIEW = "SELECT * FROM PAYMENT_VIEW;";
	InlineSQL() = default;
	virtual ~InlineSQL() = default;
};

} /* namespace marvus */

#endif /* MARVUS_INLINESQL_H_ */
