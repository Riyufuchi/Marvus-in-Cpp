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

TribeDB::TribeDB() : marvus::Database("tribalWars.db", "../sql/tribal/")
{
}

TribeDB::~TribeDB()
{
}

bool TribeDB::insertNewVillage(const marvus::insertVector& data)
{
	return insertNewData(data, sqlScriptFiles.getScript("insert_village.sql"));
}

} /* namespace twdb */
