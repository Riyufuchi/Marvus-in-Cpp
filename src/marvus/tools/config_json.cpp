//==============================================================================
// File       : ConfigJSON.cpp
// Author     : riyufuchi
// Created on : Dec 14, 2025
// Last edit  : Jan 11, 2026
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
		boost::property_tree::read_json(path, property_tree);
	else
		write_defualt_config();
}

ConfigJSON::~ConfigJSON()
{
}

void ConfigJSON::write_defualt_config()
{
	property_tree.put(NETWORK_PORT, 6969);
	property_tree.put(NETWORK_IPv4, "192.168.0.170");
	property_tree.put(PATH_TO_DB, "marvus.db");
	property_tree.put(AUTOLOAD_DB, true);
	boost::property_tree::write_json(DEFAULT_FILE, property_tree);
}

bool ConfigJSON::get_auto_load_database() const
{
	return property_tree.get<bool>(AUTOLOAD_DB);
}

std::string ConfigJSON::get_server_ipv4() const
{
	return property_tree.get<std::string>(NETWORK_IPv4);
}

int ConfigJSON::get_port() const
{
	return property_tree.get<int>(NETWORK_PORT);
}

std::string ConfigJSON::get_database_file_path() const
{
	return property_tree.get<std::string>(PATH_TO_DB);
}

} /* namespace marvus */
