//==============================================================================
// File       : StatementSQL.cpp
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "statement_sql.h"

namespace marvus
{

StatementSQL::StatementSQL() : stmt(0)
{
}

StatementSQL::~StatementSQL()
{
	if (stmt)
		sqlite3_finalize(stmt);
}

} /* namespace marvus */
