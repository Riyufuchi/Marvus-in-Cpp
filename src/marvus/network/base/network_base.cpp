//==============================================================================
// File       : network_base.cpp
// Author     : Riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Jan 11, 2026
//==============================================================================
#include "network_base.h"

namespace marvus
{
NetworkBase::NetworkBase(unsigned short port, const ShowErrorFunction& efs) : socket(io_context), acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), port(port), error_callback(efs)
{}

NetworkBase::~NetworkBase()
{
	stop();
}

void NetworkBase::stop()
{
	if (network_thread.joinable())
	{
		network_thread.request_stop();
		acceptor.cancel(ec);
		acceptor.close(ec);
		socket.cancel(ec);
		socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		socket.close(ec);
		io_context.stop();
		network_thread.join();
	}
}

void NetworkBase::start()
{
	network_thread = std::jthread(&NetworkBase::internal_run, this);
}

void NetworkBase::internal_run(std::stop_token st)
{
	run(st);
}

}
