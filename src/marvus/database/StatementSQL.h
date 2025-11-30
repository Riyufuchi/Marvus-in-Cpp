//==============================================================================
// File       : StatementSQL.h
// Author     : riyufuchi
// Created on : Nov 30, 2025
// Last edit  : Nov 30, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef DATABASE_STATEMENT_SQL_H_
#define DATABASE_STATEMENT_SQL_H_

#include <sqlite3.h>

namespace marvus
{

class StatementSQL
{
private:
	sqlite3_stmt* stmt;
public:
	StatementSQL();
	~StatementSQL();

	operator sqlite3_stmt*() const
	{
		return stmt;
	}

	operator sqlite3_stmt**()
	{
		return &stmt;
	}
};

} /* namespace marvus */

#endif /* DATABASE_STATEMENTGUARD_H_ */
