//==============================================================================
// File       : MarvusDB.h
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_MARVUSDB_H_
#define MARVUS_MARVUSDB_H_

#include "Database.h"

namespace marvus
{

class MarvusDB : public Database
{
public:
	MarvusDB();
	MarvusDB(std::string database);
	virtual ~MarvusDB() = default;
};

} /* namespace marvus */

#endif /* MARVUS_MARVUSDB_H_ */
