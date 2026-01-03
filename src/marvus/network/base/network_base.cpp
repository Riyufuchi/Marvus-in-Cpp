//==============================================================================
// File       : network_base.cpp
// Author     : Riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Jan 03, 2026
//==============================================================================
#include "network_base.h"

namespace marvus
{
NetworkBase::NetworkBase(unsigned short port, errorFunctionSignature& efs) : socket(io_context), port(port), error_callback(efs)
{}

NetworkBase::~NetworkBase()
{
	io_context.stop();
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
