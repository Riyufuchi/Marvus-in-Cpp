#include "network_base.h"

namespace marvus
{
NetworkBase::NetworkBase(unsigned short port, errorFunctionSignature& efs) : socket(io_context), port(port), error_callback(efs)
{}

NetworkBase::~NetworkBase()
{
}

void NetworkBase::start()
{
	networkThread = std::jthread(&NetworkBase::internal_run, this);
}

void NetworkBase::internal_run(std::stop_token st)
{
	run(st);
}

}
