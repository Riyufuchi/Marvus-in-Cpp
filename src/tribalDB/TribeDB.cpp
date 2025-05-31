//==============================================================================
// File       : TribeDB.cpp
// Author     : riyufuchi
// Created on : May 31, 2025
// Last edit  : May 31, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: KEO-manager
//==============================================================================

#include "TribeDB.h"

namespace twdb
{

TribeDB::TribeDB() : MarvusDB::Database("tribalWars.db", "../sql/tribal/")
{
}

TribeDB::~TribeDB()
{
}

} /* namespace twdb */
