//==============================================================================
// File       : MarvusDB.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2025
// Last edit  : Nov 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "MarvusDB.h"

namespace marvus
{
MarvusDB::MarvusDB() : MarvusDB("database.db")
{
}

MarvusDB::MarvusDB(std::string database) : Database(database, "../sql/")
{
}

} /* namespace marvus */
