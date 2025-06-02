//==============================================================================
// File       : TribeDB.h
// Author     : riyufuchi
// Created on : May 31, 2025
// Last edit  : May 31, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#ifndef TRIBALDB_TRIBEDB_H_
#define TRIBALDB_TRIBEDB_H_

#include "../database/Database.h"

namespace twdb
{

class TribeDB : public marvus::Database
{
public:
	TribeDB();
	virtual ~TribeDB();
	bool insertNewVillage(const marvus::insertVector& data);
};

} /* namespace twdb */

#endif /* TRIBALDB_TRIBEDB_H_ */
