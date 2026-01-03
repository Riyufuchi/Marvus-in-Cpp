//==============================================================================
// File       : MainFrame.h
// Author     : riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Jan 03, 2026
//==============================================================================

#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#include <thread>
// Boost
#include "boost/asio.hpp"
#include "boost/endian.hpp"
#include "boost/system.hpp"
#include "boost/version.hpp"
// Local - Marvus
#include "../../database/database_sqlite.h"

namespace marvus
{
class NetworkBase
{
private:
	std::jthread network_thread;
	void internal_run(std::stop_token st);
protected:
	boost::system::error_code ec;
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket;
	unsigned short port;
	errorFunctionSignature error_callback;
	virtual void run(std::stop_token st) = 0;
public:
	NetworkBase(unsigned short port, errorFunctionSignature& efs);
	virtual ~NetworkBase();
	void start();
};
}
#endif // NETWORK_BASE_H
