//==============================================================================
// File       : StatementGuard.h
// Author     : riyufuchi
// Created on : Jun 2, 2025
// Last edit  : Jun 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef DATABASE_STATEMENTGUARD_H_
#define DATABASE_STATEMENTGUARD_H_

#include <sqlite3.h>

namespace marvus
{

class StatementGuard
{
private:
	sqlite3_stmt* stmt;
public:
	StatementGuard(sqlite3_stmt* s);
	~StatementGuard();
};

} /* namespace marvus */

#endif /* DATABASE_STATEMENTGUARD_H_ */
