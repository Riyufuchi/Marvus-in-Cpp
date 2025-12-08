//==============================================================================
// File       : NetworkClientServerTool.h
// Author     : riyufuchi
// Created on : Dec 8, 2025
// Last edit  : Dec 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_NETWORK_NETWORKCLIENTSERVERTOOL_H_
#define MARVUS_NETWORK_NETWORKCLIENTSERVERTOOL_H_

#include <string>
#include <atomic>
#include <fstream>
// Boost
#include <IncludeBoost.hpp>

namespace marvus
{

class NetworkClientServerTool
{
public:
	NetworkClientServerTool();
	virtual ~NetworkClientServerTool();
	void runFileServer(unsigned short port, const std::string& output_file, std::atomic_bool& stop_flag, std::function<void(size_t, size_t)> progress_callback);
	void runFileClient(const std::string& server_ip, unsigned short port, const std::string& file_path, std::atomic_bool& stop_flag, std::function<void(size_t, size_t)> progress_callback);
};

} /* namespace marvus */

#endif /* MARVUS_NETWORK_NETWORKCLIENTSERVERTOOL_H_ */
