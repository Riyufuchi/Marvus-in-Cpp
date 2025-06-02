//==============================================================================
// File       : StatementGuard.cpp
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "StatementGuard.h"

namespace marvus
{

StatementGuard::StatementGuard(sqlite3_stmt* s) : stmt(s)
{
}

StatementGuard::~StatementGuard()
{
	if (stmt)
		sqlite3_finalize(stmt);
}

} /* namespace marvus */
