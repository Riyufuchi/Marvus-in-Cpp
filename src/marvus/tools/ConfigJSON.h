//==============================================================================
// File       : ConfigJSON.h
// Author     : riyufuchi
// Created on : Dec 14, 2025
// Last edit  : Dec 15, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_TOOLS_CONFIGJSON_H_
#define MARVUS_TOOLS_CONFIGJSON_H_

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
	boost::property_tree::ptree propTree;
	void writeDefualtConfig();
public:
	ConfigJSON();
	explicit ConfigJSON(const std::string& path);
	virtual ~ConfigJSON();
	// Setters

	// Getters
	int getPort() const;
	bool getAutoloadDB() const;
	std::string getDatabaseFilePath() const;
	std::string getServerIPv4() const;
};

} /* namespace marvus */

#endif /* MARVUS_TOOLS_CONFIGJSON_H_ */
