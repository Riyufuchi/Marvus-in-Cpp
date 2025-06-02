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

int TribeDB::insertNewBattle(const marvus::insertVector& battleData, int campaignID)
{
	if (battleData.empty())
		return 0;
	const int BATTLE_ID = insertNewData(battleData, sqlScriptFiles.getScript("insert_battle.sql"));
	if (!BATTLE_ID)
		return 0;
	// Connect battle to campaign
	marvus::insertVector intersection;
	intersection.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(BATTLE_ID)));
	intersection.emplace_back(marvus::insertPair(marvus::DataType::INTEGER, std::to_string(campaignID))); // Campaign ID
	if (insertNewData(intersection, sqlScriptFiles.getScript("insert_battle_to_campaign.sql")))
		return BATTLE_ID;
	return 0;
}

int TribeDB::insertNewUnit(const marvus::insertVector& unitData)
{
	if (unitData.empty())
		return 0;
	return insertNewData(unitData, sqlScriptFiles.getScript("insert_unit.sql"));
}

} /* namespace twdb */
