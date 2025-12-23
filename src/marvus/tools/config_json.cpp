//==============================================================================
// File       : ConfigJSON.cpp
// Author     : riyufuchi
// Created on : Dec 14, 2025
// Last edit  : Dec 15, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "config_json.h"

namespace marvus
{

ConfigJSON::ConfigJSON() : ConfigJSON(DEFAULT_FILE)
{
}

ConfigJSON::ConfigJSON(const std::string& path)
{
	if (std::filesystem::exists(path))
		boost::property_tree::read_json(path, propTree);
	else
		writeDefualtConfig();
}

ConfigJSON::~ConfigJSON()
{
}

void ConfigJSON::writeDefualtConfig()
{
	propTree.put(NETWORK_PORT, 6969);
	propTree.put(NETWORK_IPv4, "192.168.0.170");
	propTree.put(PATH_TO_DB, "marvus.db");
	propTree.put(AUTOLOAD_DB, true);
	boost::property_tree::write_json(DEFAULT_FILE, propTree);
}

bool ConfigJSON::getAutoloadDB() const
{
	return propTree.get<bool>(AUTOLOAD_DB);
}

std::string ConfigJSON::getServerIPv4() const
{
	return propTree.get<std::string>(NETWORK_IPv4);
}

int ConfigJSON::getPort() const
{
	return propTree.get<int>(NETWORK_PORT);
}

std::string ConfigJSON::getDatabaseFilePath() const
{
	return propTree.get<std::string>(PATH_TO_DB);
}

} /* namespace marvus */
