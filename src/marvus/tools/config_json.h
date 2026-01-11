//==============================================================================
// File       : ConfigJSON.h
// Author     : riyufuchi
// Created on : Dec 14, 2025
// Last edit  : Jan 11, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_TOOLS_CONFIG_JSON_H_
#define MARVUS_TOOLS_CONFIG_JSON_H_

#include <string>
#include <filesystem>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

namespace marvus
{

class ConfigJSON
{
	static inline const std::string DEFAULT_FILE = "config.json";
	static inline const std::string PATH_TO_DB = "database.path";
	static inline const std::string AUTOLOAD_DB = "database.autoload";
	static inline const std::string NETWORK_PORT = "network.port";
	static inline const std::string NETWORK_IPv4 = "network.ipv4";
private:
	boost::property_tree::ptree property_tree;
	void write_defualt_config();
public:
	ConfigJSON();
	explicit ConfigJSON(const std::string& path);
	virtual ~ConfigJSON();
	// Setters

	// Getters
	int get_port() const;
	bool get_auto_load_database() const;
	std::string get_database_file_path() const;
	std::string get_server_ipv4() const;
};

} /* namespace marvus */

#endif /* MARVUS_TOOLS_CONFIG_JSON_H_ */
